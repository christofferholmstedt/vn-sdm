//DM.cpp
/*
  The Data Manager (DM) module of the Satellite Data Model (SDM) system is responsible
for maintaining information about the data sources and service providers available
within the SDM system. The DM provides a mechanism for user applications to find data
and service providers registered with the system, subscribe to data, and issue commands.
The DM also provides a mechanism for data and service providers to register their
capabilities in the SDM system, and handle consumer application requests.

  The DM:
  - Interfaces via TCP/UDP and system calls.
  - Uses pThreads, File access,
  -
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <ctype.h>
#ifndef __VXWORKS__
#include <getopt.h>
#include <sys/poll.h>
#endif
#include <signal.h>
#include <pthread.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/ioctl.h>

#include "../common/Time/SDMTime.h"
#include "../common/task/taskdefs.h"
#ifdef __VXWORKS__
#include <ioLib.h>
#include <pipeDrv.h>
#include <vxWorks.h>
#include <time.h>
#endif

#ifdef WIN32
#include <Winsock2.h>
#else
#include <net/if.h>
#include <netdb.h>
#include <sys/stat.h>
#endif

#include "DM.h"
#include "DMxTEDS.h"


#define xsize 25
#define DM_STACK_SIZE (256000)

#ifdef PNP_BACKUP
SDMComponent_ID NetworkManager;
int dm_heartbeat_pipe[2];
#endif

Sem writeSem(1);	//Semaphore used for writing/reading from the pipe
Sem addLibrary(1);	//Semaphore used for registering/deregistering xTEDS
const int MAX_OUTSTANDING_XTEDS = 5; // The number of outstanding xTEDS registrations allowed (as a semaphore counter)

//xTEDS segment builder used to build segmented UDP xTEDS documents, all threads
//must first lock the SegmentBuilderMutex to access the class
xTEDSSegmentBuilder xTEDSBuilder;
pthread_mutex_t SegmentBuilderMutex = PTHREAD_MUTEX_INITIALIZER;

//These socket descriptors are thread safe because any problems that might occur will only occur when a SIGINT has
// happened and the DM needs to be quitting anyway
int udpSock=IP_SOCK_INVALID, tcpSock=IP_SOCK_INVALID, tcpListenSock=IP_SOCK_INVALID;

//The write operations into the pipes is protected by the writeSem semaphore variable, only the ChildFunctionCallProcess reads from the pipes
int MsgTxPushSock=IP_SOCK_INVALID;
#ifndef __VXWORKS__
int alert[2];	/*Pipes for parent/child communication*/
#else  //VxWorks doesn't support UNIX-style pipes, a named pipe must be used
int alertPipe;
#endif

//debug is only written upon initialization from command line parameters, all other accesses are reads
int debug = 0;			/*Global debug level so functions know which printf's to print*/

//spacewire is only written upon initialization from command line parameters, all other accesses are reads
bool spacewire = false;

//Each element in the list has an associated semaphore called inUse that must be held to modify or read any of the data
xTEDSLibraryList xTEDSList;

//Protected by the subscription_mutex, this mutex must be held to modify or read any data from subscribers
SubscriptionList subscribers;
pthread_mutex_t subscription_mutex = PTHREAD_MUTEX_INITIALIZER;

//Protected by the log_service_mutex, this mutex must be held to modify or read any data from log_service
MessageLogger log_service;
pthread_mutex_t log_service_mutex = PTHREAD_MUTEX_INITIALIZER;

//Queues used during the registration process, protected by mutexes.
SDMRegQueue deviceQueue;
SDMRegQueue applicationQueue;
pthread_mutex_t reg_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
bool registerNext = true;

SDMCancelQueue cancelxTEDSQueue;
pthread_mutex_t cancel_queue_mutex = PTHREAD_MUTEX_INITIALIZER;
bool cancelNext = true;

//Protected by the dm_address_mutex, this mutex must be held to modify or read any data from Address_DM
const unsigned long L_LOCAL_HOST = inet_addr("127.0.0.1");
unsigned long Address_DM = L_LOCAL_HOST;
const unsigned long DM_SENSOR_ID = 1;

//These message counters are protected by the perf_counter_mutex, it must be held to modify or read the performance counters
unsigned int total_recd = 0;		//message counter for total received for life of dm
unsigned int prevsec_recd = 0;		//message counter for total received previous second
unsigned int total_sent = 0;		//message counter for total sent for life of dm
unsigned int prevsec_sent = 0;		//message counter for total sent previous second
unsigned int droppedxTEDS = 0;		//message counter for total sent previous second
unsigned int droppedCancelxTEDS = 0;//message counter for total sent previous second
pthread_mutex_t perf_counter_mutex = PTHREAD_MUTEX_INITIALIZER;

//Sensor subscriptions
ProviderSubscriptionList g_SensorSubscriptions;
pthread_mutex_t sensor_subs_mutex = PTHREAD_MUTEX_INITIALIZER;

#ifdef PNP_BACKUP
//Protected by the dm_list_mutex, this mutex must be held to modify or read any data from dmList
bool g_bElectedDm = true;
DMBackupList backupDMList;
pthread_mutex_t dm_list_mutex = PTHREAD_MUTEX_INITIALIZER;
#endif

//extern int errno;
#include <errno.h>
/*
	Description:
		Main entry point of the program.  When started it is assumed that this is the only
		DM so it tries to hold an election.  If the election fails then it goes into backup
		mode, otherwise normal DM mode.

	Input:
		argc - The number of command line arguments
		argv - an array of the command line arguments

	Output:
		-1 - the program has terminated unexpectedly
		1 - the program has terminated successfully

	Changed:
		None

*/
int main(int argc, char** argv)
{
#ifndef WIN32
	sigset_t signal_set;
#endif
   SDM_TimeInit();

#ifndef __VXWORKS__
	static struct option long_options[] = {
		{"help",0,0,'h'},
		{"debug",1,0,'g'},
		{"spacewire",1,0,'s'},
		{0,0,0,0}
	};
	int option_index;
#endif
	int option;

	while(1)
	{
#ifdef __VXWORKS__
		option = getopt(argc,argv,"g:s:h:v");
#else
		option = getopt_long(argc,argv,"g:s:h:v", long_options, &option_index);
#endif
		if(option==-1)
			break; //no more options
		switch(option)
		{
			case 'h':
				printf("Usage: dm [options]\n");
				printf("Options:\n");
				printf("--debug=<level> -g<level>\t\tSet level of debug messages\n\t\t\t\t\t0=none, 1=moderate, 2=verbose\n");
				return 0;
			case 'g':
				debug = atoi(optarg);
				break;
			case 's':
				spacewire = !!atoi(optarg);
				break;
         case 'v':
            printf("SDM Version: %s Repo Rev: %i\n", SDM_VERSION, REVISION_NUMBER);
            return 0;
			case '?':
				break;
		}
	}

#ifdef WIN32 /*Windows will handle signals differently than the Linux implementation*/
	signal(SIGINT,SigHandler);
	sigset(SIGALRM,SigHandler);
#else /*Windows won't handle signal sets or a separate thread for signal handling*/
	//All subsequent threads block the SIGINT and SIGALRM signals so they aren't interrupted after calling pthread_mutex_lock()
	//this avoids a deadlock situation by dedicating a single thread for signal handling.
	//These signal masks are inhereted by all spawned threads
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGALRM);
	sigaddset(&signal_set, SIGINT);
	pthread_sigmask(SIG_BLOCK, &signal_set, NULL);
	pthread_t signalHandler;
	if (0 != pthread_create(&signalHandler, NULL, &SigHandler, NULL))
	{
		perror("Could not start signal handler thread.\n");
		return -1;
	}
	pthread_detach(signalHandler);
#endif

#ifdef SEND_IMA
 	if (spacewire) {
 	  SendIMA(ImaDm, debug);
 	}
#endif

	// Get the Data Manager address
	if((Address_DM = GetNodeAddress(spacewire)) == 0)
	{
		printf("Unable to get the DM's IP address, using localhost instead.\n");
		Address_DM = L_LOCAL_HOST;
	}
	else
	{
		debug_f(3,"Data Manager address is 0x%lx\n",Address_DM);
	}

	DataManager.setAddress(Address_DM);
	DataManager.setPort(PORT_DM);
	DataManager.setSensorID(DM_SENSOR_ID);

	//TODO:  Fix this for uclinux
	//CreatexTEDSDirectory();

	// Start the main listener thread
#ifdef PNP_FAKE
	NetworkManager.setAddress(inet_addr("129.123.7.128"));
	NetworkManager.setPort(3605);
	NetworkManager.setSensorID(1);
#endif

#ifdef PNP_BACKUP
	if (RunBackupListener() < 0)
		return -1;
#else
	pthread_t udpThread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr,DM_STACK_SIZE);
	if (0 != pthread_create(&udpThread, &attr, &UdpListenerProcess, NULL))
	{
		perror ("Could not create UDPListenerProcess thread: ");
		return -1;
	}
	pthread_join(udpThread,NULL);
	UdpListenerProcess(NULL);
#endif
	return 1;
}



void* RegistrationHandler(void* args)
{
   SDMRegister registerMsg;
   SDMComponent_ID componentToRegister;

   double endTime = 0;
   double timeOut = 5.0;

   debug_f(1,"Queueing incoming registrations for 5 seconds...\n");
   sleep(5);  //allow some registrations of both apps and devices to queue up
   registerNext = true;
   debug_f(1,"Now checking registration queues...\n");
   while(1)
   {
      if(GetCurTime() >= endTime)  //Check for timeouts
      {
         registerNext = true;
      }

      if(registerNext)
      {
         pthread_mutex_lock(&reg_queue_mutex);
         if(debug >= 2)
         {
            if(deviceQueue.size() > 0 || applicationQueue.size() > 0)
               debug_f(2,"Device Registration Queue: %i App Registration Queue: %li\n", deviceQueue.size(), applicationQueue.size());
         }

         if(deviceQueue.size() != 0)
         {
            componentToRegister = (SDMComponent_ID)deviceQueue.dequeue();
            if(componentToRegister.getPort() == PORT_SM || componentToRegister.getPort() == PORT_SPA1_MANAGER)
            {
               registerMsg.sensorIndex = componentToRegister.getSensorID();
               debug_f(2, "SDMRegister about to be sent to SM, sensorIndex: %i\n", registerMsg.sensorIndex);
            }
            registerMsg.SendTo(componentToRegister);

            char strTargetAddr[64];
            componentToRegister.IDToString(strTargetAddr, sizeof(strTargetAddr));
            debug_f(2,"SDMRegister sent to device at %s\n", strTargetAddr);

            endTime = GetCurTime() + timeOut;
            registerNext = false;
            //sleep(1);
         }
         else if(applicationQueue.size() != 0)
         {
            componentToRegister = applicationQueue.dequeue();
            if(componentToRegister.getSensorID() != 0)
            {
               registerMsg.sensorIndex = componentToRegister.getSensorID();
            }
            registerMsg.SendTo(componentToRegister);

            char strTargetAddr[64];
            componentToRegister.IDToString(strTargetAddr, sizeof(strTargetAddr));
            debug_f(2,"SDMRegister sent to application at %s\n", strTargetAddr);

            endTime = GetCurTime() + timeOut;
            registerNext = false;
            //sleep(1);
         }
         pthread_mutex_unlock(&reg_queue_mutex);
      }
      usleep(100000);
   }

   return NULL;
}


void* CancelRegHandler(void* args)
{
   pthread_t CancelThread;
   pthread_attr_t attr;
   pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr,DM_STACK_SIZE);
   while(1)
   {
      pthread_mutex_lock(&cancel_queue_mutex);
      if(cancelNext && cancelxTEDSQueue.size() > 0)
      {
         debug_f(2, "Pulling off the cancelxTEDS queue...\n");
         cancelNext = false;
         xTEDSParameters* toCancel = cancelxTEDSQueue.dequeue();
         pthread_mutex_unlock(&cancel_queue_mutex);
         if (0 != pthread_create(&CancelThread, &attr, CancelxTEDS, toCancel))
         {
				perror("Could not spawn CancelxTEDS thread.\n");
         }
         pthread_detach(CancelThread);
         usleep(10000);
      }
      else
      {
         pthread_mutex_unlock(&cancel_queue_mutex);
         sleep(1);
      }
   }

   return NULL;
}


double GetCurTime()
{
   unsigned int seconds;
   unsigned int uSeconds;
   double curTime;
   SDM_GetTime(&seconds, &uSeconds);
   curTime = seconds + ((double)uSeconds/1000000.0);
   return curTime;
}


/*
	Description:
		Listener for UDP on DM_PORT.  Registers the DM xTEDS.  Calls the PipeInit to set up all necessary pipes

	Input:
		None

	Output:
		None

	Changed:
		None

*/
void* UdpListenerProcess(void*)
{
	int iMessageSize = 0;
	char buf[BUFSIZE];	//Buffer for recieving incoming messages
	pthread_attr_t attr;
	pthread_t functionCallThread, tcpThread, xtedThread, registrationThread, cancelRegThread;
	int iStatus;
	int iSenderPort;
	struct sockaddr_in p;
	SDMComponent_ID SenderId;
	char SenderIdBuf[10];
	SDMComHandle ComHandle;
	SDMRegister registerMsg;

	// Bind the UDP port and obtain socket descriptor
	udpSock = UDPpassive(PORT_DM);
	if (udpSock == IP_SOCK_INVALID)
		return NULL;

	PipeInit();

	//Start the ChildFunctionCallProcess thread
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr,DM_STACK_SIZE);
	if (0 != pthread_create(&functionCallThread,&attr,ChildFunctionCallProcess,NULL))
	{
		perror("Could not start the child function call process thread.\n");
		return NULL;
	}
	pthread_detach(functionCallThread);
	if (0 != pthread_create(&tcpThread,&attr,TcpListenerProcess,NULL))
	{
		perror("Could not start the TCP listener thread.\n");
		return NULL;
	}
	pthread_detach(tcpThread);
   if (0 != pthread_create(&registrationThread,&attr,RegistrationHandler,NULL))
	{
		perror("Could not start the Registration Handle thread.\n");
		return NULL;
	}
	pthread_detach(tcpThread);
	if (0 != pthread_create(&cancelRegThread,&attr,CancelRegHandler,NULL))
	{
		perror("Could not start the Registration Handle thread.\n");
		return NULL;
	}
	pthread_detach(tcpThread);


	// DM up and running with current version
	printf ("DM SERVER %s running...\n",SDM_VERSION);
	//
	// Register the Data Manager's xTEDS
	// Fill in the xTEDS parameters


    xTEDSLibraryListNode* DMnode = MatchSID(DM_SENSOR_ID);
    if(DMnode == NULL)  //No DM previously registered
    {
        SDMxTEDS xTEDSMessage;
        xTEDSMessage.source.setPort(DataManager.getPort());
        xTEDSMessage.source.setSensorID(DataManager.getSensorID());
        strncpy(xTEDSMessage.xTEDS, dmxTED, sizeof(xTEDSMessage.xTEDS));
        iMessageSize = xTEDSMessage.Marshal(buf);
        SenderId.setAddress(Address_DM);
        xTEDS(new xTEDSParameters(buf,iMessageSize,SenderId, COM_HANDLE_INVALID));
    }
    else
    {
        DMnode->data->setAddress(DataManager);
        DMnode->data->inUse->Signal();
        printf("Updating the registered DM Address to 0x%lx\n", DataManager.getAddress());
    }

	// Initialize the IPC TCP socket with the function call process
	usleep(1000);
	int iAttemptCounter = 0;
	bool bConnected = false;
	while (!bConnected)
	{
		if ((MsgTxPushSock = TCPconnect("127.0.0.1", PORT_DM_TEMP)) == IP_SOCK_INVALID)
		{
			debug_f(3, "Error - UDPListenerProcess::Connection error with the function call process, retrying.\n");
			iAttemptCounter++;
		}
		else
		{
			debug_f(3, "Connected to the function call process.\n");
			bConnected = true;
			break;
		}

		if (iAttemptCounter >= 5)
		{
			debug_f(0, "UDPListenerProcess::Could not establish a connection with the child function call process, quitting.\n");
			return NULL;
		}
		usleep(1000);
	}
#ifdef PNP_BACKUP
	xTEDSLibraryListNode* node;
	// Tell the Task Manager to do a reset, if this is a newly elected DM
	if(TaskManager.getPort() != 0)
	{
		SDMCommand command;
		SDMComponent_ID temp_dmaddr;
//		node = xTEDSList.head;
//		while(node!=NULL)
//		{
//			node->data->inUse->Wait();
//			if(node->data->getActive() == true)
//			{
//				if(node->data->getTargetPort()!=PORT_DM && node->data->getTargetPort()!=PORT_PM && node->data->getTargetPort()!=PORT_SM && node->data->getTargetPort()!=PORT_TM)
//				{
//					node->data->setActive(false);
//				}
//			}
//			node->data->inUse->Signal();
//			node = node->next;
//		}
		temp_dmaddr = DataManager;
		command.source = TaskManager;
		command.command_id.setMessage(5);
		command.command_id.setInterface(1);
		PUT_CHAR(command.data,MODE_RESET);
		temp_dmaddr.setPort(PORT_DM);
		temp_dmaddr.Marshal(command.data,1);
		printf("Sending new DM address: 0x%lx to TM\n", temp_dmaddr.getAddress());
		command.length = HEADER_SIZE;
		command.Send(TaskManager);
	}
#endif
	// The main message receiving loop
	while(1)
	{
		// Clear the buf so there are no residual messages in it
		iMessageSize = 0;
		// Receive the next message
		iStatus = UDPserv_recv(udpSock, buf, BUFSIZE);
		// Increment performance counters
		pthread_mutex_lock(&perf_counter_mutex);
		total_recd++;
		prevsec_recd++;
		pthread_mutex_unlock(&perf_counter_mutex);
		if(iStatus != -1 && iStatus != UDP_SERV_RECV_SHUTDOWN)	//If no recieving error process message
		{
			UDPgetip(&p);
			iMessageSize = iStatus;
			debug_f(4,"iMessageSize is %d\n",iMessageSize);
			iSenderPort = (int)ntohs(p.sin_port);
			SenderId.setAddress(p.sin_addr.s_addr);
			if (SenderId.getAddress() == L_LOCAL_HOST)
				SenderId.setAddress(Address_DM);
			SenderId.setPort(iSenderPort);
			ComHandle.Set(udpSock, false, &p);

         if(buf[0] == SDM_Hello)
         {
            SDMHello helloMsg;
            if(helloMsg.Unmarshal(buf) < 0)
            {
               printf("Invalid SDMHello message!\n\n");
            }

            SDMComponent_ID sm;
            SDMComponent_ID newReg = helloMsg.source;
			if ( newReg.getAddress() == 0 )
				newReg.setAddress(SenderId.getAddress());

            char strTargetAddr[64];
            newReg.IDToString(strTargetAddr, sizeof(strTargetAddr));
            debug_f(2, "SDMHello from %s\n", strTargetAddr);

            if(helloMsg.source.getPort() == PORT_SM)
            {
			   sm = helloMsg.source;
			   if ( sm.getAddress() == 0 )
				   sm.setAddress(SenderId.getAddress());
               sm.setPort(PORT_SM);
               debug_f(2, "SDMHello was from SM, sensorIndex: %i\n", helloMsg.source.getSensorID());
            }
            switch(helloMsg.type)
            {
               case 'D':   //Device
                  pthread_mutex_lock(&reg_queue_mutex);
                  if(!deviceQueue.find(newReg))
                  {
                     debug_f(2, "Device SDMHello received, adding to the queue\n");
                     deviceQueue.add(newReg);
                  }
                  else
                  {
                     debug_f(2, "Ignoring duplicate SDMHello\n");
                  }
                  pthread_mutex_unlock(&reg_queue_mutex);

                  if(helloMsg.source.getPort() != PORT_SM && helloMsg.source.getPort() != PORT_SPA1_MANAGER)
                  {
                     SendAckMessage(SDM_OK, true, newReg, ComHandle, true);
                  }
                  else
                  {
                     SendAckMessage(helloMsg.source.getSensorID(), true, sm, ComHandle, true);
                  }

                  break;
               case 'A':  //Application
                  pthread_mutex_lock(&reg_queue_mutex);
                  if(!applicationQueue.find(newReg))
                  {
                     debug_f(2, "Application SDMHello received, adding to the queue\n");
                     applicationQueue.add(newReg);
                  }
                  else
                  {
                     debug_f(2, "Ignoring duplicate SDMHello\n");
                  }
                  pthread_mutex_unlock(&reg_queue_mutex);

                  if(helloMsg.source.getPort() != PORT_SM && helloMsg.source.getPort() != PORT_SPA1_MANAGER)
                  {
                     SendAckMessage(SDM_OK, true, newReg, ComHandle, true);
                  }
                  else
                  {
                     SendAckMessage(helloMsg.source.getSensorID(), true, sm, ComHandle, true);
                  }

                  break;
               case 'C':  //Core Component
                  SendAckMessage(SDM_OK, true, newReg, ComHandle, true);
                  registerMsg.SendTo(newReg);
                  debug_f(2, "Ack and register msgs sent to core component\n");
                  break;
               default:
                  printf("Bad SDMHello type with type: %c\n", helloMsg.type);
                  break;
            }
         }
			else if(buf[0] == SDM_xTEDS)
			{
				// Make sure we don't clog xTEDS registrations, if there are many outstanding,
				// drop this message
				if (addLibrary.GetWaitCount() < MAX_OUTSTANDING_XTEDS)
				{
					if (0 != pthread_create(&xtedThread,&attr,xTEDS,new xTEDSParameters(buf,iMessageSize,SenderId,ComHandle)))
					perror("Could not spawn xTEDS thread.\n");

					pthread_detach(xtedThread);
				}
				else
				{
					debug_f(1, "xTEDS message dropped -- too many outstanding registrations.\n");
					droppedxTEDS++;
				}
			}
			else if(buf[0] == SDM_CancelxTEDS)
			{
			   xTEDSParameters* cancelParams = new xTEDSParameters(buf,iMessageSize,SenderId,ComHandle);
			   pthread_mutex_lock(&cancel_queue_mutex);
			   cancelxTEDSQueue.add(cancelParams);
			   pthread_mutex_unlock(&cancel_queue_mutex);
			   debug_f(2, "Queueing up a CancelxTEDS msg...\n");
			}
			else
			{
				SenderId.Marshal(SenderIdBuf,0);
				writeSem.Wait();
				TCPsend(MsgTxPushSock, SenderIdBuf, sizeof(SenderIdBuf));
				TCPsend(MsgTxPushSock, &iMessageSize, 4); //Write the size of the buf into the push pipe
				TCPsend(MsgTxPushSock, buf, iMessageSize);	//Write the Consume message into the push pipe
#ifndef __VXWORKS__
				write(alert[1], &buf[0], 1);	//Write the Consume byte into the notify pipe
#else
				write(alertPipe, &buf[0], 1);
#endif
				debug_f(4,"Alert written into pipe\n");
				writeSem.Signal();
			}
		}
		else
		{
			debug_f(4, "Error with UDPserv_recv in DM main message loop.\n");
			// If udpSock is shutdown, UDPserv_recv may return UDP_SERV_RECV_SHUTDOWN before this thread can finish
			if (iStatus != UDP_SERV_RECV_SHUTDOWN)
				debug_f(4,"There was an error reading in the next message\n");
			usleep(1000);	//Small sleep to prevent processor spinning
		}
	}
	return 0;
}

/*
	Description:
		Listener for TCP on DM_PORT

	Input:
		None

	Output:
		None

	Changed:
		None

*/
void* TcpListenerProcess(void*)
{
	int iSize = 0;
	char buf[LARGE_MSG_BUFSIZE];	//Buffer for recieving incoming messages
	int iStatus;
	int iCurLength;
	unsigned short usPort;
	struct sockaddr_in p;
	pthread_attr_t attr;
	pthread_t xtedThread;
	short sSdmLength;
	SDMComponent_ID SenderId;
	char SenderIdBuf[10];
	SDMComHandle ComHandle;
	SDMRegister registerMsg;
	bool bError = false;

	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr, DM_STACK_SIZE);

	debug_f(3,"Listening for TCP message on port %hu\n", PORT_DM);

	tcpListenSock = TCPpassive(PORT_DM, MAX_TCP_CONNECTIONS);
	if (tcpListenSock == IP_SOCK_INVALID)
	{
		debug_f(0, "TCPListenerProcess:: Could not open listen socket.\n");
		return NULL;
	}
	//Start main loop
	while(1)
	{
		iSize = 0;
		tcpSock = TCPaccept(tcpListenSock, &p);
		if (tcpSock == IP_SOCK_INVALID)
			continue;
		//
		// Make sure we at least grab the SDM header
		iCurLength = 0;
		bError = false;
		do
		{
			iStatus = TCPrecv(tcpSock, &buf[iCurLength], LARGE_MSG_BUFSIZE - iCurLength);
			if (iStatus < 0)
			{
				perror("TCPrecv:");
				bError = true;
				break;
			}
			else if (iStatus == 0)
			{
				bError = true;
				break;		// Peer has shutdown, don't handle partial messages
			}
			else
				iCurLength += iStatus;
		} while(iCurLength < HEADER_SIZE);
		if (bError)
		{
			TCPclose(tcpSock);
			continue;
		}
		//
		// Get the SDM message length
		sSdmLength = GET_SHORT(&buf[9]);
		//
		// Receive the rest of the message
		while(sSdmLength > iCurLength - HEADER_SIZE)
		{
			iStatus = TCPrecv(tcpSock, &buf[iCurLength], LARGE_MSG_BUFSIZE - iCurLength);
			if (iStatus < 0)
			{
				perror("TCPrecv:");
				bError = true;
				break;
			}
			else if (iStatus == 0)
			{
				bError = true;
				break;
			}
			else
				iCurLength += iStatus;
		}
		if (bError)
		{
			TCPclose(tcpSock);
			continue;
		}
		if(sSdmLength != iCurLength - HEADER_SIZE)
			printf("Error: More bytes recv'd than expected!\n");
			// Let the Unmarshal function report the error

		pthread_mutex_lock(&perf_counter_mutex);
		total_recd++;
		prevsec_recd++;
		pthread_mutex_unlock(&perf_counter_mutex);

		iSize = iCurLength;
		debug_f(4,"TCP: Size is %d\n", iSize);
		usPort = ntohs(p.sin_port);
		SenderId.setAddress(p.sin_addr.s_addr);
		if (SenderId.getAddress() == L_LOCAL_HOST)
			SenderId.setAddress(Address_DM);
		SenderId.setPort(usPort);

		ComHandle.Set(tcpSock, true, &p);

      if(buf[0] == SDM_Hello)
      {
         SDMHello helloMsg;
         if(helloMsg.Unmarshal(buf) < 0)
         {
            printf("Invalid SDMHello message!\n\n");
         }

         SDMComponent_ID sm;
         SDMComponent_ID newReg = helloMsg.source;
		 if ( newReg.getAddress() == 0 )
			newReg.setAddress(SenderId.getAddress());

         char strTargetAddr[64];
         newReg.IDToString(strTargetAddr, sizeof(strTargetAddr));
         debug_f(2, "SDMHello from %s\n", strTargetAddr);

         if(helloMsg.source.getPort() == PORT_SM)
         {
			sm = newReg;
		    if ( sm.getAddress() == 0 )
				sm.setAddress(SenderId.getAddress());
            sm.setPort(PORT_SM);
            newReg.setSensorID(helloMsg.source.getSensorID());
            debug_f(2, "SDMHello was from SM, sensorIndex: %i\n", helloMsg.source.getSensorID());
         }

         switch(helloMsg.type)
         {
            case 'D':   //Device
               pthread_mutex_lock(&reg_queue_mutex);
               if(!deviceQueue.find(newReg))
               {
                  debug_f(2, "Device SDMHello received, adding to the queue\n");
                  deviceQueue.add(newReg);
               }
               else
               {
                  debug_f(2, "Ignoring duplicate SDMHello\n");
               }
               pthread_mutex_unlock(&reg_queue_mutex);

               if(helloMsg.source.getPort() != PORT_SM && helloMsg.source.getPort() != PORT_SPA1_MANAGER)
               {
                  SendAckMessage(SDM_OK, true, newReg, ComHandle, true);
               }
               else
               {
                  SendAckMessage(helloMsg.source.getSensorID(), true, sm, ComHandle, true);
               }

               break;
            case 'A':  //Application
               pthread_mutex_lock(&reg_queue_mutex);
               if(!applicationQueue.find(newReg))
               {
                  debug_f(2, "Application SDMHello received, adding to the queue\n");
                  applicationQueue.add(newReg);
               }
               else
               {
                  debug_f(2, "Ignoring duplicate SDMHello\n");
               }
               pthread_mutex_unlock(&reg_queue_mutex);

               if(helloMsg.source.getPort() != PORT_SM && helloMsg.source.getPort() != PORT_SPA1_MANAGER)
               {
                  SendAckMessage(SDM_OK, true, newReg, ComHandle, true);
               }
               else
               {
                  SendAckMessage(helloMsg.source.getSensorID(), true, sm, ComHandle, true);
               }

               break;
            case 'C':  //Core Component
               SendAckMessage(SDM_OK, true, newReg, ComHandle, true);
               registerMsg.SendTo(newReg);
               debug_f(2, "Ack and register msgs sent to core component\n");
               break;
            default:
               printf("Bad SDMHello type with type: %c\n", helloMsg.type);
               break;
         }
      }
      else if(buf[0] == SDM_xTEDS)
		{
			// Make sure we don't clog xTEDS registrations, if there are many outstanding,
			// drop this message
			if (addLibrary.GetWaitCount() < MAX_OUTSTANDING_XTEDS)
			{
				if (0 != pthread_create(&xtedThread,&attr,xTEDS,new xTEDSParameters(buf,iSize,SenderId,ComHandle)))
				perror("Could not spawn xTEDS thread.\n");

				pthread_detach(xtedThread);
			}
			else
			{
				debug_f(1, "xTEDS message dropped -- too many outstanding registrations.\n");
				droppedxTEDS++;
			}
		}
		else if(buf[0] == SDM_CancelxTEDS)
		{
			   xTEDSParameters* cancelParams = new xTEDSParameters(buf,iSize,SenderId,ComHandle);
			   pthread_mutex_lock(&cancel_queue_mutex);
			   cancelxTEDSQueue.add(cancelParams);
			   pthread_mutex_unlock(&cancel_queue_mutex);
			   debug_f(2, "Queueing up a CancelxTEDS msg...\n");
		}
		else
		{
			SenderId.Marshal(SenderIdBuf, 0);
			writeSem.Wait();
			TCPsend(MsgTxPushSock, SenderIdBuf, sizeof(SenderIdBuf));//Write the ip address of the reciever into the push pipe
			TCPsend(MsgTxPushSock, &iSize, 4); //Write the size of the buf into the push pipe
			TCPsend(MsgTxPushSock, buf, iSize);	//Write the Consume message into the push pipe
#ifndef __VXWORKS__
			write(alert[1], &buf[0], 1);	//Write the Consume byte into the notify pipe
#else
			write(alertPipe, &buf[0], 1);
#endif
			writeSem.Signal();
		}
		if(buf[0] != SDM_xTEDS && buf[0] != SDM_CancelxTEDS)
			TCPclose(tcpSock);
 	}
 	return 0;
}

/*
	Description:
		Handling of the SDMConsume message.  Forward a SDMSubreqst to the correct data provider.

	Input:
		buf  - the message in an array
		size  -  the length of the message in bytes
		SenderId - The sender address information

	Output:
		None

	Changed:
		None

*/
void Consume(char *buf, int size, const SDMComponent_ID& SenderId)
{
	SDMConsume msgConsumeRequest;
	SDMSubreqst msgSubRequest;
	xTEDSLibraryListNode* node;

	if(msgConsumeRequest.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMConsume message\n\n");
		return;
	}
	MessageReceived(&msgConsumeRequest);

#ifdef PNP_BACKUP
		// Send the SDMConsume msg to all backup DMs
		msgConsumeRequest.destination.setAddress(SenderId.getAddress());
		pthread_mutex_lock(&dm_list_mutex);
		backupDMList.SendMessageToAll(msgConsumeRequest);
		pthread_mutex_unlock(&dm_list_mutex);
#endif

	if (debug >= 1)
	  {
	    char strRequesterAddr[64];
	    char strTargetAddr[64];
		char strTargetName[64];
		xTEDSList.GetDeviceName(msgConsumeRequest.source, strTargetName, sizeof(strTargetName));
	    msgConsumeRequest.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	    msgConsumeRequest.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    debug_f(1, "SDMConsume from %s for %s (%s) message 0x%x\n",
		    strRequesterAddr, strTargetAddr, strTargetName,
		    msgConsumeRequest.msg_id.getInterfaceMessagePair());
	  }
	//debug_f(1,"command: Consume -- length %d port: %hu sensorID: %ld msgID: 0x%x \n",size,msgConsumeRequest.destination.getPort(),msgConsumeRequest.source.getSensorID(),msgConsumeRequest.msg_id.getInterfaceMessagePair());

	//
	// Get the node structure for the sensor requested
	node = MatchSID(msgConsumeRequest.source.getSensorID());
	if(node==NULL)	//If node is NULL reaches xsize there is no matching sensorID and request is invalid
	{
		printf("Could not find the sensor requested!\n");
		//fflush(NULL);
		return;
	}
	//
	// Put message together for the requested sensor
	msgSubRequest.destination = msgConsumeRequest.destination;
	msgSubRequest.destination.setAddress(SenderId.getAddress());
	msgSubRequest.source = msgConsumeRequest.source;
	msgSubRequest.msg_id = msgConsumeRequest.msg_id;
	//
	// If this is a request for the Data Manager, add a subscription table entry
	if(node->data->getSensorID() == DM_SENSOR_ID)
	{
		node->data->inUse->Signal();
		SDMComponent_ID SubscriberId;
		SubscriberId.setAddress(SenderId.getAddress());
		SubscriberId.setPort(msgSubRequest.destination.getPort());
		// Add a subscription entry
		Subscribe(SubscriberId, msgSubRequest.msg_id);
		debug_f(1,"\n");
		return;
	}
	// Get the fault ID for the requested message
	msgSubRequest.fault_id = node->data->xtedsTree->getNotificationFaultMsgID(msgConsumeRequest.msg_id);

	if (debug >= 1)
	  {
	    char strTargetAddr[64];
	    char strRequesterAddr[64];
	    msgSubRequest.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    msgSubRequest.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	    debug_f(1, "  SDMSubreqst sent to %s from requester %s message 0x%x.\n",
		    strTargetAddr, strRequesterAddr,
		    msgSubRequest.msg_id.getInterfaceMessagePair());
	  }
	//debug_f(1,"Msg sent to notification provider (0x%lx:%d SID=%ld) from 0x%lx:%d SID=%ld Msg=0x%x\n", node->data->getAddress(), msgSubRequest.source.getPort(), msgSubRequest.source.getSensorID(), msgSubRequest.destination.getAddress(), msgSubRequest.destination.getPort(), msgSubRequest.destination.getSensorID(), msgSubRequest.msg_id.getInterfaceMessagePair());
	//
	// Increment the number of connections to the xTEDS
	int n = node->data->getConnections();
	n++;
	node->data->setConnections(n);
	node->data->inUse->Signal();
	//
	// If the sensor ID is filled in for the subscriber, it has an xTEDS and should be marked in
	// the DM's provider subscription list so the DM can send out cancellations upon any type of failure
	if (msgSubRequest.destination.getSensorID() != 0 && msgSubRequest.destination.getSensorID() != 1)
	{
	    debug_f(3, "Adding subscription to the g_SensorSubscriptions list...\n");
		pthread_mutex_lock(&sensor_subs_mutex);
		g_SensorSubscriptions.Add(msgSubRequest.source /*provider*/,
				msgSubRequest.destination/*subscriber*/, msgSubRequest.msg_id);
		pthread_mutex_unlock(&sensor_subs_mutex);
	}
	//
	// Send the request
	msgSubRequest.Send();
	MessageSent(&msgSubRequest);
	debug_f(1, "\n");
}

/*
	Description:
		Handling of the SDMCancel message.  Forward a SDMDeletesub to the correct data provider.

	Input:
		buf  - the message in an array
		size  -  the length of the message in bytes
		SenderId - The sender address information

	Output:
		None

	Changed:
		None

*/
void Cancel(char *buf, int size, const SDMComponent_ID& SenderId)
{
	SDMCancel msgCancelRequest;
	SDMDeletesub msgDeleteSub;
	xTEDSLibraryListNode* node;

	if(msgCancelRequest.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMCancel message!\n\n");
		return;
	}
	MessageReceived(&msgCancelRequest);

	if (debug >= 1)
	  {
	    char strRequesterAddr[64];
	    char strTargetAddr[64];
	    msgCancelRequest.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	    msgCancelRequest.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    debug_f(1, "SDMCancel request from %s for %s message 0x%x\n",
		    strRequesterAddr, strTargetAddr,
		    msgCancelRequest.msg_id.getInterfaceMessagePair());
	  }

	// Get the node structure
	node = MatchSID(msgCancelRequest.source.getSensorID());
	if(node==NULL)	//If n equals xsize there was no matching sensorID and request was invalid
	{
		debug_f(3,"Could not find the sensor requested!\n");
		return;
	}

	// This request's destination will be the sender of the request
	msgDeleteSub.destination = msgCancelRequest.destination;
	msgDeleteSub.destination.setAddress(SenderId.getAddress());
	msgDeleteSub.source = msgCancelRequest.source;
	msgDeleteSub.msg_id = msgCancelRequest.msg_id;
	// If this is a request for the Data Manager, add a subscription entry
	if(node->data->getSensorID() == DM_SENSOR_ID)
	{
		node->data->inUse->Signal();
		SDMComponent_ID SubscriberId;
		SubscriberId.setAddress(SenderId.getAddress());
		SubscriberId.setPort(msgDeleteSub.destination.getPort());
		CancelSubscription(SubscriberId, msgDeleteSub.msg_id.getInterfaceMessagePair());
		debug_f(1,"\n");
		return;
	}

	if (debug >= 1)
	  {
	    char strRequesterAddr[64];
	    char strTargetAddr[64];
	    msgDeleteSub.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    msgDeleteSub.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	    debug_f(1, "  SDMDeletesub sent to %s from requester %s message 0x%x.\n",
		    strTargetAddr, strRequesterAddr,
		    msgDeleteSub.msg_id.getInterfaceMessagePair());
	  }

	//
	// Decrement the number of connections to xTEDS
	int n = node->data->getConnections();
	n--;
	if(n < 0)
		n = 0;
	node->data->setConnections(n);
	node->data->inUse->Signal();
	//
	// If the sensor ID is filled in for the subscriber, it has an xTEDS and should be removed from the
	// the DM's provider subscription list
	if (msgDeleteSub.destination.getSensorID() != 0 && msgDeleteSub.destination.getSensorID() != 1)
	{
		pthread_mutex_lock(&sensor_subs_mutex);
		g_SensorSubscriptions.Delete(msgDeleteSub.destination /*subscriber*/, msgDeleteSub.msg_id);
		pthread_mutex_unlock(&sensor_subs_mutex);
	}
	//
	// Send the delete subscription request message
	msgDeleteSub.Send();
	MessageSent(&msgDeleteSub);

	unsigned short usTPort = node->data->getTargetPort();
	if(n == 0 && usTPort != PORT_SM && usTPort != PORT_PM && usTPort != PORT_TM && usTPort != PORT_SPA1_MANAGER)	//If application has no subscribers send a kill message
	{
		debug_f(3,"A process no longer has any subscribers and may need to be killed\n");
		// FUTURE:
		// This functionality still undefined
	}
	debug_f(1, "\n");
}

/*
	Description:
		Handling of SDMCommand messages, forward it to the correct command provider.

	Input:
		buf  - the message in an array
		size  -  the length of the message in bytes
		SenderId - The address information of the requester

	Output:
		None

	Changed:
		None

*/
void Command(char *buf, int size, const SDMComponent_ID& SenderId)
{
	SDMCommand msgCommand;

	// Unmarshall the message
	if (msgCommand.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMCommand message!\n\n");
		return;
	}
	MessageReceived(&msgCommand);

	if (debug >= 1)
	  {
	    char strRequesterAddr[64];
	    char strTargetAddr[64];
	    msgCommand.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    msgCommand.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	    debug_f(1, "SDMCommand from %s for %s message 0x%x\n",
		    strRequesterAddr, strTargetAddr,
		    msgCommand.command_id.getInterfaceMessagePair());
	  }
	//
	// Get the sensor id and pull the xTEDS structure
	unsigned long RequestedSensorId = msgCommand.source.getSensorID();
	xTEDSLibraryListNode* node = MatchSID(RequestedSensorId);
	if(node==NULL)	//If sensor ID did not match
	{
		printf("Sensor ID did not match any available\n\n");
		return;
	}
	//
	// Get the command id and make sure it is valid for this data provider
	SDMMessage_ID RequestedCommandId (msgCommand.command_id);
	if (!node->data->xtedsTree->isCommandIdValid(RequestedCommandId))
	{
		printf("Invalid message id for command request.\n");
		node->data->inUse->Signal();
		return;
	}

	SDMMessage_ID CommandFaultId (node->data->xtedsTree->getCommandFaultMsgID(RequestedCommandId));
	msgCommand.fault_id = CommandFaultId;
	//
	// If this is a command for the Data Manager
	if (node->data->getSensorID() == DM_SENSOR_ID)
	{
		if (RequestedCommandId == CMD_ENABLE_LOGGING)	//Enable logging command
		{
			debug_f(1, "  DM command to enable log messages received.\n");
			pthread_mutex_lock(&log_service_mutex);
			if (log_service.NeedsInit())
				log_service.SetLogFile("Data Manager Message Log\n", "dmmessages.log");
			log_service.AddMessageType(&msgCommand);
			pthread_mutex_unlock(&log_service_mutex);
			node->data->inUse->Signal();
			return;
		}
		else if (RequestedCommandId == CMD_DISABLE_LOGGING)	//Disable logging command
		{
			debug_f(1, "  DM command to disable log messages received.\n");
			pthread_mutex_lock(&log_service_mutex);
			log_service.RemoveMessageType(&msgCommand);
			pthread_mutex_unlock(&log_service_mutex);
			node->data->inUse->Signal();
			return;
		}
		else
		{
			printf("Received invalid command of 0x%x for DataManager\n", RequestedCommandId.getInterfaceMessagePair());
			node->data->inUse->Signal();
			return;
		}
	}
	//
	// Debug output
	if (debug >= 1)
	  {
	    char strRequesterAddr[64];
	    char strTargetAddr[64];
	    msgCommand.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    msgCommand.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	    debug_f(1, "  SDMCommand sent to %s requested from %s message 0x%x\n",
		    strTargetAddr, strRequesterAddr,
		    msgCommand.command_id.getInterfaceMessagePair());
	  }

	if (debug >= 3)
	{
		debug_f(3, " Data: ");
		for (int i = 0; i < msgCommand.length; i++)
			debug_f(3, "%x ", msgCommand.data[i]);
	}
	debug_f(3, "\n");
	//
	// Send the message to the provider
	SDMComponent_ID ProviderId;
	ProviderId.setAddress(node->data->getAddress());
	ProviderId.setPort((short)node->data->getTargetPort());
	msgCommand.Send(ProviderId);
	MessageSent(&msgCommand);

	node->data->inUse->Signal();
	debug_f(1, "\n");
}

/*
	Handle service requests to the Data Manager services only.  All other service requests for
	other devices should use the SDMService interface.

*/
void Serreqst(const char* buf, int size, const SDMComponent_ID& SenderId)
{
	SDMSerreqst msgServiceRequest;
	if (msgServiceRequest.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMSerreqst message.\n");
		return;
	}

	const unsigned long REQUESTED_SENSOR_ID = msgServiceRequest.source.getSensorID();

	if (debug >= 1)
	  {
	    char strRequesterAddr[64];
	    char strTargetAddr[64];
		char strRequesterName[64];
		xTEDSList.GetDeviceName(msgServiceRequest.destination, strRequesterName, sizeof(strRequesterName));
	    msgServiceRequest.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    msgServiceRequest.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	    debug_f(1, "SDMSerreqst from %s (%s) for DataManager message 0x%x\n",
		    strRequesterAddr, strRequesterName,
		    msgServiceRequest.command_id.getInterfaceMessagePair());
	  }

	//
	// Only handle SDMSerreqst messages for the DM's services
	if (REQUESTED_SENSOR_ID != DM_SENSOR_ID)
	{
		printf("Error:  Serreqst is for a device other than the Data Manager.\n");
		return;
	}
	//
	// Get the DM's xTEDS library
	xTEDSLibraryListNode* pDmLibraryNode = MatchSID(DM_SENSOR_ID);
	if (pDmLibraryNode == NULL)
	{
		// This should never happen, but assure we're not using a null pointer
		printf("Fatal Error:  DM xTEDS library could not be found.\n");
		return;
	}

	const SDMMessage_ID idRequestedCommand(msgServiceRequest.command_id);
	const SDMMessage_ID idDataReply(pDmLibraryNode->data->xtedsTree->getServiceDataMsgID(idRequestedCommand));
	pDmLibraryNode->data->inUse->Signal();

	if(idRequestedCommand == SER_SEND_SENSOR_ID || idRequestedCommand == SER_SEND_PID
		|| idRequestedCommand == SER_SID_TO_SPANODE || idRequestedCommand == SER_SID_TO_IP
		|| idRequestedCommand == SER_COMPID_TO_COMPKEY)
	{
		//
		// Handle the request if the command id is valid
		unsigned long ulRequestedSensorId = GET_ULONG(&msgServiceRequest.data[0]);
		SDMComponent_ID RequesterId;
		RequesterId.setAddress(SenderId.getAddress());
		RequesterId.setPort(msgServiceRequest.destination.getPort());
		ServicePublish(RequesterId, ulRequestedSensorId, idDataReply, (int)msgServiceRequest.seq_num);
	}
	else if ( idRequestedCommand == SER_GET_ERRORS )
	{
		SDMComponent_ID RequesterId;
		RequesterId.setAddress(SenderId.getAddress());
		RequesterId.setPort(msgServiceRequest.destination.getPort());
		ServicePublish(RequesterId, 0, idDataReply, (int)msgServiceRequest.seq_num);
	}
	else
		printf("Command ID 0x%x does not match any Data Manager service.\n", idRequestedCommand.getInterfaceMessagePair());

	debug_f(1, "\n");
}
/*
	Description:
		Handling of SDMService messages, forward a SDMSerreqst to the correct service provider.

	Input:
		buf  - the message in an array
		size  -  the length of the message in bytes
		SenderId - The address information of the requester

	Output:
		None

	Changed:
		None

*/
void Service(char *buf, int size, const SDMComponent_ID& SenderId)
{
	SDMService msgService;			// Incoming request message
	SDMSerreqst msgRequest;			// Outgoing request message

	if(msgService.Unmarshal(buf) < 0)	//Check to see that the service message is at least the minimum correct number of bytes
	{
		printf("Invalid SDMService message\n\n");
		return;
	}
	MessageReceived(&msgService);

	if (debug >= 1)
	  {
	    char strRequesterAddr[64];
	    char strTargetAddr[64];
	    msgService.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    msgService.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	    debug_f(1, "SDMService from %s for %s message 0x%x\n",
		    strRequesterAddr, strTargetAddr,
		    msgService.command_id.getInterfaceMessagePair());
	  }

	//
	// Get the sensor id and pull the xTEDS structure
	unsigned long RequestedSensorId  = msgService.source.getSensorID();
	xTEDSLibraryListNode* node = MatchSID(RequestedSensorId);
	if(node==NULL)
	{
		printf("Sensor ID did not match any available\n\n");
		return;
	}
	//
	// Get the requested command id and make sure it is a service in the provider's xTEDS
	SDMMessage_ID RequestedCommandID (msgService.command_id);
	SDMMessage_ID SerReplyID (node->data->xtedsTree->getServiceDataMsgID(RequestedCommandID));
	if(SerReplyID == INVALID_MESSAGE_ID)
	{
		printf("CommandID 0x%x is not part of a Request\n",RequestedCommandID.getInterfaceMessagePair());
		node->data->inUse->Signal();
		return;
	}
	SDMMessage_ID SerFaultID (node->data->xtedsTree->getServiceFaultMsgID(RequestedCommandID));
	//
	// If this is a request for the Data Manager's services
	if(node->data->getSensorID() == DM_SENSOR_ID)
	{
		if(RequestedCommandID == SER_SEND_SENSOR_ID || RequestedCommandID == SER_SEND_PID
			|| RequestedCommandID == SER_SID_TO_SPANODE || RequestedCommandID == SER_SID_TO_IP
			|| RequestedCommandID == SER_COMPID_TO_COMPKEY)
		{
			RequestedSensorId = GET_LONG(&msgService.data[0]);
			node->data->inUse->Signal();
			SDMComponent_ID RequesterId;
			RequesterId.setAddress(SenderId.getAddress());
			RequesterId.setPort(msgService.destination.getPort());
			ServicePublish(RequesterId, RequestedSensorId, SerReplyID, (int)msgService.seq_num);
			debug_f(1,"\n");
			return;
		}
		else if ( RequestedCommandID == SER_GET_ERRORS )
		{
			SDMComponent_ID RequesterId;
			RequesterId.setAddress(SenderId.getAddress());
			RequesterId.setPort(msgService.destination.getPort());
			ServicePublish(RequesterId, 0, SerReplyID, (int)msgService.seq_num);
		}
		else
		{
			printf("Invalid Command ID of 0x%x for data manager service request\n", RequestedCommandID.getInterfaceMessagePair());
			node->data->inUse->Signal();
			return;
		}
	}
	// Assure the requested service is valid for this producer
	if (!node->data->xtedsTree->isServiceIdValid(RequestedCommandID))
	{
		printf("Invalid message id for service request.\n");
		node->data->inUse->Signal();
		return;
	}

	// Copy the address of the requester
	msgRequest.destination.setAddress(SenderId.getAddress());
	msgRequest.source = msgService.source;

	// Copy the command, reply, and fault message ids into the request
	msgRequest.command_id = RequestedCommandID;
	msgRequest.reply_id = SerReplyID;
	msgRequest.fault_id = SerFaultID;

	// Copy requester info into the request
	msgRequest.destination.setPort(msgService.destination.getPort());
	msgRequest.destination.setSensorID(msgService.destination.getSensorID());

	// Copy the sequence number into the request
	msgRequest.seq_num = msgService.seq_num;

	// Copy the data portion and length into the request
	memcpy(&msgRequest.data[0], &msgService.data[0], msgService.length);
	msgRequest.length = msgService.length;
	//
	// Debug output
	if (debug >= 1)
	  {
	    char strRequesterAddr[64];
	    char strTargetAddr[64];
	    msgRequest.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    msgRequest.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	    debug_f(1, "  Sent SDMSerreqst to %s from %s message 0x%x length %d\n",
		    strTargetAddr, strRequesterAddr,
		    msgRequest.command_id.getInterfaceMessagePair(), msgRequest.length);
	  }

	if (debug >= 3)
	{
		debug_f(3, " data: ");
		for(int i = 0; i < msgRequest.length; i++)
			debug_f(3,"%x ", msgRequest.data[i]);
	}
	debug_f(3,"\n");
	//
	// Send the request message to the provider
	SDMComponent_ID ProviderId;
	ProviderId.setAddress(node->data->getAddress());
	ProviderId.setPort(node->data->getTargetPort());
	msgRequest.Send(ProviderId);
	MessageSent(&msgRequest);

	node->data->inUse->Signal();
	debug_f(1, "\n");
}

/*
	Description:
		Handling of the SDMReqReg messages.  There are two forms of ReqReg calls, one to perform an exhaustive search
		of all registered xTEDS as a request of an application, and one to perform a search of only newly registered
		or unregistered xTEDS.  These cases are handled when xTEDref is -1 (exhaustive search) or the index numbered
		value of the xTEDS from which to begin.

	Input:
		MsgBuf  - the message in an array
		MsgSize  -  the length of the message in bytes
		subref - a pointer to a subscription list node
		xTEDref - an index reference to the xTEDS node, this will be -1 if all xTEDS to be searched for matches
		   if this index is >= 0, search only the xTEDS registered in that slot.  In this case, RequesterIPAddr
		   and RequesterPort are the address and port of the subscriber.
		RequesterIPAddr - the ip address in dot notation
		RequesterPort - the port to respond on if SDMReqReg.destination.port == 0 && SDMReqReg.reply == SDM_CURRENT
		xTEDSAction - One of REGISTRATION_MODIFICATION, DEREGISTRATION_MODIFICATION, or UPDATE_MODIFICATION when
		   the ReqReg is being performed on a subscription to fill the "type" in a SDMRegInfo, or MOD_NOT_APPLICABLE otherwise

	Output:
		None

	Changed:
		None

*/
void ReqReg(char *MsgBuf, int MsgSize, const int xTEDref, const SDMComponent_ID& SenderId, int xTEDSAction)	//Search xTEDS for matches of item_name and quallist and return SDMRegInfo
{
	unsigned int RegInfoCountSent=0;
	char* MessageDefString;					//Pointer to message definitions to send
	char* xTEDSSection;					//Pointer to xTEDS portion to send
	MessageDef* msgdefs = NULL;				//This is a heap-allocated object, this method must delete it
	MessageDef* cur_msgdef;
	unsigned short usPort = 0;
	bool result = false;
	bool ContinueSearch = true;
	SDMReqReg msgRequest;
	SDMRegInfo msgInfo;
	xTEDSLibraryListNode* node;
	int iRequestType = 0;
	SDMComponent_ID id;					//The component ID of the requesting application
	long dev_length = 0, interface_length = 0;

	//Copy from MsgBuf into local variable for ease of use
	if(msgRequest.Unmarshal(MsgBuf) < 0)
	{
		printf("Invalid SDMReqReg message\n\n");
		return;
	}
	MessageReceived(&msgRequest);

	//Save the requester information in "id"
	usPort = msgRequest.destination.getPort();
	if(msgRequest.reply == SDM_REQREG_CURRENT && usPort == 0)
		usPort = SenderId.getPort();
	if(msgRequest.destination.getAddress() == 0)
		id.setAddress(SenderId.getAddress());
	else
		id.setAddress(msgRequest.destination.getAddress());
	id.setPort(usPort);

	if (debug >= 1)
	  {
	    char strRequesterAddr[64];
	    char strTargetAddr[64];
	    msgRequest.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    msgRequest.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	    debug_f(1, "SDMReqReg from %s for %s %d device: \"%s\" item_name: \"%s\"\n",
		    strRequesterAddr, strTargetAddr, msgRequest.id, msgRequest.device, msgRequest.item_name);
	  }

	//If the reply style isn't SDM_REQREG_CURRENT (i.e. a subscription needs to be entered or cancelled) and this isn't already
	//a previous request corresponding to an xTEDS
	if(msgRequest.reply != SDM_REQREG_CURRENT && xTEDref == -1) //A subscription is wanted or needs to be canceled
	{
		SDMComponent_ID SubscriberId;
		SubscriberId.setAddress(SenderId.getAddress());
		SubscriberId.setPort(usPort);
		pthread_mutex_lock(&subscription_mutex);
		result = subscribers.addOrRemoveSubscription(msgRequest.reply, SubscriberId, msgRequest.source, msgRequest.device, msgRequest.interface, msgRequest.item_name, msgRequest.quallist, msgRequest.id, REQ_REG_FUTURE, debug);
		pthread_mutex_unlock(&subscription_mutex);
		if(result == false)
			return;
#ifdef PNP_BACKUP
		// Send the ReqReg subscription to all backup DMs
		pthread_mutex_lock(&dm_list_mutex);
		msgRequest.destination = SubscriberId;
		backupDMList.SendMessageToAll(msgRequest);
		pthread_mutex_unlock(&dm_list_mutex);
#endif
	}

	//Count the number of xTEDS currently registered
	int numxTEDS = 0;
	node = xTEDSList.head;
	while(node!=NULL)
	{
		numxTEDS++;
		node = node->next;
	}

	int *SensorMatches = new int[numxTEDS];		// Holds a RegInfo match count for each currently registered xTEDS
	const int SensorMatchesSize = numxTEDS;		// Number of currently registered xTEDS

	for(int i = 0; i < SensorMatchesSize; i++)		// Initialize the SensorMatches array
		SensorMatches[i] = 0;

	numxTEDS = 0;
	node = xTEDSList.head;
	debug_f(3,"Starting search for matching in xTEDS\n");

	//If the item name is empty, match only on qualifiers/device/interface
	//Type 0 has item_name, iRequestType 1 does not have item_name, iRequestType 2 is a regular expression for the item_name
	if(msgRequest.item_name[0] == '\0')
	{
		iRequestType = REQTYPE_EMPTYITEM;
	}
	else
	{
		//Determine whether this is a regular expressions-style ReqReg
		iRequestType = ParseItemName(msgRequest.item_name,debug);
	}
	//Traverse the xTEDS library to perform a RegInfo
	while(node!=NULL && ContinueSearch == true)
	{
		if(node->data->inUse->Wait() == 0)
		{
			//Try to match only xTEDS whose component ID matches the request, or if the request's
			//sensorID is zero, try to match all xTEDS
			if(node->data->getComponentID()==msgRequest.source || msgRequest.source.getSensorID() == 0)
			{
				if (node->data->getAvailable())
				{
					// If this node is not used by any xTEDS, skip over it
					// (available means it's not being used)
					node->data->inUse->Signal();
					node = node->next;
					continue;
				}
				debug_f(4, "Trying ReqReg on device %s\n",node->data->getName());
				dev_length = strlen(msgRequest.device);
				interface_length = strlen(msgRequest.interface);
				switch(iRequestType)
				{
					case REQTYPE_USEITEM:	//If this is a RegInfo related to a specific item name
						if(dev_length > 0 && interface_length > 0)
							msgdefs = node->data->xtedsTree->RegInfo(msgRequest.item_name,msgRequest.quallist,msgRequest.device,msgRequest.interface);
						else if(dev_length == 0 && interface_length == 0)
							msgdefs = node->data->xtedsTree->RegInfo(msgRequest.item_name,msgRequest.quallist,NULL,NULL);
						else if(dev_length == 0)
							msgdefs = node->data->xtedsTree->RegInfo(msgRequest.item_name,msgRequest.quallist,NULL,msgRequest.interface);
						else
							msgdefs = node->data->xtedsTree->RegInfo(msgRequest.item_name,msgRequest.quallist,msgRequest.device,NULL);
						break;
					case REQTYPE_EMPTYITEM:	//If this is a RegInfo not related to a specific item name
						if(dev_length > 0 && interface_length > 0)
							msgdefs = node->data->xtedsTree->AllRegInfo(msgRequest.quallist,msgRequest.device,msgRequest.interface);
						else if(dev_length == 0 && interface_length == 0)
							msgdefs = node->data->xtedsTree->AllRegInfo(msgRequest.quallist,NULL,NULL);
						else if(dev_length == 0)
							msgdefs = node->data->xtedsTree->AllRegInfo(msgRequest.quallist,NULL,msgRequest.interface);
						else
							msgdefs = node->data->xtedsTree->AllRegInfo(msgRequest.quallist,msgRequest.device,NULL);
						break;
					case REQTYPE_REGEX:	//If this is a regular expressions style RegInfo
						try
						{
							if(dev_length > 0 && interface_length > 0)
								msgdefs = node->data->xtedsTree->RegexRegInfo(msgRequest.item_name,msgRequest.quallist,msgRequest.device,msgRequest.interface);
							else if(dev_length == 0 && interface_length == 0)
								msgdefs = node->data->xtedsTree->RegexRegInfo(msgRequest.item_name,msgRequest.quallist,NULL,NULL);
							else if(dev_length == 0)
								msgdefs = node->data->xtedsTree->RegexRegInfo(msgRequest.item_name,msgRequest.quallist,NULL,msgRequest.interface);
							else
								msgdefs = node->data->xtedsTree->RegexRegInfo(msgRequest.item_name,msgRequest.quallist,msgRequest.device,NULL);
						}
						catch(...)
						{
							ContinueSearch = false;
							printf("Error: Invalid Regular Expression\n");
							//fflush(NULL);
						}
						break;
          default:
            break;
				}
				//If for some reason, the search failed or produced an error, stop
				if(ContinueSearch == false)
				{
					node->data->inUse->Signal();
					break;
				}
				cur_msgdef = msgdefs;
				//Put together SDMRegInfo messages
				while(cur_msgdef!=NULL)
				{
					// Increase the number of matches to this sensor
					// Do a bounds check, a device could have registered
					if (numxTEDS < SensorMatchesSize)
						SensorMatches[numxTEDS]++;

					if(node->data->getActive() == true || xTEDSAction == DEREGISTRATION_MODIFICATION)
					{
						msgInfo.id = msgRequest.id;			//Copy in the request stream ID from the ReqReg
						if(xTEDSAction != DEREGISTRATION_MODIFICATION || xTEDref == -1)
							msgInfo.type = SDM_REGINFO_REGISTRATION;
						else
							msgInfo.type = SDM_REGINFO_CANCELLATION;
						//
						//Set the source address to be the xTEDS that matched
						msgInfo.source.setSensorID(node->data->getSensorID());
						debug_f(4,"Inserted SensorID of %ld\n",node->data->getSensorID());

						msgInfo.source.setPort(node->data->getTargetPort());
						debug_f(4,"Inserted Port of %hu\n",node->data->getTargetPort());

						msgInfo.source.setAddress(node->data->getAddress());
						debug_f(4,"Inserted Address of 0x%lx\n",node->data->getAddress());

						//
						//Set the message ID to the message that matched
						msgInfo.msg_id = cur_msgdef->GetInterfaceMessageID();
						debug_f(4,"Inserted MessageID of 0x%x\n",msgInfo.msg_id.getInterfaceMessagePair());

						debug_f(5,"xTEDref is %d\n",xTEDref);
						//Save a reference to both the message def. and the xTEDS portion
						MessageDefString = cur_msgdef->GetDefinitions();
						xTEDSSection = cur_msgdef->GetxTEDSPortion();
						if((debug >= 1 && xTEDref == -1) || (debug >=1 && xTEDref == numxTEDS))	//Print the message being sent
						  {
						    if(strlen(MessageDefString) > 15)
						      {
							char strTargetAddr[64];
							char strDeviceAddr[64];
							SenderId.IDToString(strTargetAddr, sizeof(strTargetAddr));
							node->data->getComponentID().IDToString(strDeviceAddr, sizeof(strDeviceAddr));
							debug_f(1,"  SDMRegInfo match for %s (%s), message sent to %s\n", node->data->getName(), strDeviceAddr, strTargetAddr);
							debug_f(2,"    msg_def: %s xTEDS Portion %s\n", MessageDefString, xTEDSSection);
						      }
						  }
						//Copy in the message definition portion, including null terminator
						memcpy(msgInfo.msg_def,MessageDefString,strlen(MessageDefString)+1);
						msgInfo.msg_def[strlen(MessageDefString)] = '\0';
						//Copy in the xTEDS portion corresponding with the message, including null terminator
						memcpy(msgInfo.xTEDS_section,xTEDSSection,strlen(xTEDSSection)+1);
						msgInfo.xTEDS_section[strlen(xTEDSSection)] = '\0';
						//
						//Send RegInfo's if a message definitions was matched
						if(xTEDref == -1 && strlen(MessageDefString) > 15)	//If reply is wanted and subscription is entered
						{
							msgInfo.Send(id);
							MessageSent(&msgInfo);
							RegInfoCountSent++;
							debug_f(4,"Sent a reply to SDMReqReg to 0x%lx at port %hu\n",SenderId.getAddress(),usPort);
						}
						//If this is a subscription match, and a message def matched for a recent registration
						else if(numxTEDS == xTEDref && strlen(MessageDefString) > 15)
						{
							id = SenderId;
							msgInfo.Send(id);
							MessageSent(&msgInfo);
							RegInfoCountSent++;
							debug_f(4,"Sent a reply to SDMReqReg to 0x%lx at port %hu for subscription\n", SenderId.getAddress(), SenderId.getPort());
						}
					}
					cur_msgdef = cur_msgdef->next;
				}
				if(msgdefs!=NULL)
        {
					delete msgdefs;
          msgdefs = NULL;
        }
			}
			node->data->inUse->Signal();
		}
		node = node->next;

		// If xTED is not equal to -1 then this is a subscription looking for new registrations
		if(xTEDref != -1 && xTEDref == numxTEDS)
		{
			// Check to see if the new registration has the item_name and qual_list
			if(numxTEDS < SensorMatchesSize && SensorMatches[numxTEDS] == 0)
			{
				delete [] SensorMatches;
				// If no new matching info function does not need to finish
				return;
			}
		}

		numxTEDS++;
	}
	//If there were no RegInfo's sent, check to see if an inactive xTEDS will match according to the value in sensornames
	if(RegInfoCountSent == 0)
	{
		int z = 0;
		node = xTEDSList.head;
		while(node!=NULL)
		{
			// Bounds check, a device could have registered
			if (z >= SensorMatchesSize)
				break;

			node->data->inUse->Wait();
			if(SensorMatches[z] > 0 && node->data->getActive() == false && node->data->getPosted() == false)	//If sensornames is 1 or greater this xTED had matches and xTED is inactive
			{
				debug_f(1,"ReqReg match an inactive task, posting task now...\n");
				node->data->setPosted(true);
				PostTask(node);
			}
			node->data->inUse->Signal();
			z++;
			node = node->next;
		}
	}
	delete [] SensorMatches;
	//
	// Send out the terminating RegInfo message with only the command byte to signal the end of SDMRegInfo messages
	// If this is a subscription ReqReg, fill the requester's info
	if (xTEDref != -1)
		id = SenderId;
	//
	// Send the empty RegInfo message
	msgInfo.SendEmpty(id);
	MessageSent(&msgInfo);
	debug_f(1, "\n");
}

/*
	Description:
		Handling of the SDMSearch message.  There are two forms of Search calls, one for a requesting application to
		perform an exhaustive search of the xTEDS, and one for an xTEDS registration change, to check only interested
		xTEDS subscriptions.  These types of Search calls depend on the xTEDSref parameter (-1 for an exhaustive
		search, or an index reference number for a registration change.)

	Input:
		MsgBuf  - the message in an array
		size  -  the length of the message in bytes
		ipaddr - the ip address in dot notation
		xTEDref - an index reference to the xTEDS node

	Output:
		None

	Changed:
		None

*/
void Search(char *MsgBuf, int size, const SDMComponent_ID& SenderId, int xTEDref)
{
	xTEDSLibraryListNode* node;
	SDMSearch msgSearch;
	SDMSearchReply msgReply;
	SDMComponent_ID RecipientId;
	//
	// Unmarshal message
	if(msgSearch.Unmarshal(MsgBuf) < 0)
	{
		printf("Invalid SDMSearch message\n\n");
		return;
	}
	MessageReceived(&msgSearch);

	//
	// Set the recipient address information
	RecipientId.setPort(msgSearch.destination.getPort());
	if(RecipientId.getPort() == 0)
	{
		printf("Search Error:  Unable to complete SDMSearch because of invalid destination port\n");
		return;
	}
	if(msgSearch.destination.getAddress() == 0)
		RecipientId.setAddress(SenderId.getAddress());
	else
		RecipientId.setAddress(msgSearch.destination.getAddress());

	if (debug >= 1)
	  {
	    char strRequesterAddr[64];
		char strRequesterName[64];
		xTEDSList.GetDeviceName(msgSearch.destination, strRequesterName, sizeof(strRequesterName));
	    msgSearch.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	    debug_f(1, "SDMSearch from %s (%s) reg_expr: \"%s\"\n",
		    strRequesterAddr, strRequesterName, msgSearch.reg_expr);
	  }

	//
	// The reply is one of SDM_SEARCH_CURRENT_AND_FUTURE or SDM_SEARCH_CANCEL for this to match
	if(msgSearch.reply != SDM_SEARCH_CURRENT) //A subscription is wanted or needs to be canceled
	{
		SDMComponent_ID SubscriberId;
		SubscriberId.setAddress(SenderId.getAddress());
		SubscriberId.setPort(RecipientId.getPort());

		pthread_mutex_lock(&subscription_mutex);
		bool AddResult = subscribers.addOrRemoveSubscription(msgSearch.reply, SubscriberId, msgSearch.source, NULL, NULL, msgSearch.reg_expr, NULL, msgSearch.id, SEARCH_REPLY, debug);
		pthread_mutex_unlock(&subscription_mutex);
		if(AddResult == false)
		{
			return;
		}
#ifdef PNP_BACKUP
		// Send the Search subscription to all backup DMs
		pthread_mutex_lock(&dm_list_mutex);
		msgSearch.destination = SubscriberId;
		backupDMList.SendMessageToAll(msgSearch);
		pthread_mutex_unlock(&dm_list_mutex);
#endif
	}
	//
	// If this Search call is due to a recent registration, find the node of interest
	if(xTEDref != -1)
	{
		int xTEDSCount = 0;
		node = xTEDSList.head;
		while(xTEDref != xTEDSCount && node != NULL)
		{
			xTEDSCount++;
			node = node->next;
		}
		if(node == NULL)
		{
			printf("Unable to do Search due to invalid xTEDS reference\n");
			return;
		}
	}
	else
		node = xTEDSList.head;
	//
	// Perform the actual search
	RegexResult SearchResults;
	RegularExpression Pattern;
	if (!Pattern.Set(msgSearch.reg_expr))
	{
		debug_f(0, "Invalid regular expression \"%s\"\n", msgSearch.reg_expr);
		return;
	}
	while(node!=NULL)
	{
		if(node->data->inUse->Wait() == 0)
		{
			if((node->data->getComponentID()==msgSearch.source || msgSearch.source.getSensorID() == 0) && node->data->getActive() == true)
			{
				try
				{
					SearchResults = node->data->XtedsRegexSearchCapturesOnly(Pattern);
				}
				catch (SDMRegexException e)
				{
					debug_f(0, "Search Exception: %s\n", e.Message());
				}
				if (SearchResults.Matched())
				{
				  if (debug >= 1)
				    {
				      char strTargetAddr[64];
					  char strDeviceAddr[64];
					  node->data->getComponentID().IDToString(strDeviceAddr, sizeof(strDeviceAddr));
				      RecipientId.IDToString(strTargetAddr, sizeof(strTargetAddr));
				      debug_f(1, " xTEDS for %s (%s) matched %d times, sending reply to %s.\n", node->data->getName(), strDeviceAddr, SearchResults.NumMatches(), strTargetAddr);
				    }
					msgReply.source = node->data->getComponentID();
					msgReply.id = msgSearch.id;

					for (int i = 0; i < SearchResults.NumMatches(); i++)
					{
						SearchResults[i].FillMatchText(msgReply.captured_matches, sizeof(msgReply.captured_matches));
						msgReply.Send(RecipientId);
					}
				}
			}
			node->data->inUse->Signal();
		}
		if(xTEDref != -1)
			break;
		node = node->next;
	}
	//
	// Send out the terminating SDMSearchReply message
	msgReply.SendEmpty(RecipientId);
	MessageSent(&msgReply);
	debug_f(1, "\n");
}

/*
	Send an SDMAck message with the specified AckStatus.  If UseComponentId is true, send to the idDest component ID.
	Otherwise, send to the AppHandle com handle.  If we're sending to idDest, the request was sent from device
	directly on the network.  If we're sending to AppHandle, we're responding to the SDMmessage wait loop.  If this
	is not the "Active/Leader" DM, i.e., this is a backup DM, don't send an Ack.

	Input:
		sAckStatus - The status to send, check SDMmessage.h for possible values
		bUseComponentId - Whether to use the idDest to send the message, or AppHandle
		idDest - The component ID of the device to reply to
		AppHandle - The handle object representing the communication information for the waiting application class loop
	Output:
		int - Returns the status of the ack message, or 0 if sending an ACK wasn't required
 */
int SendAckMessage(short sAckStatus, bool bUseComponentId, const SDMComponent_ID& idDest, const SDMComHandle& AppHandle, bool bForceSend)
{
	SDMAck msgAck;
	int iResult;

#ifdef PNP_BACKUP
	// If this is not a "force", and we are a backup, don't send
	if (!bForceSend)
	{
		pthread_mutex_lock(&dm_list_mutex);
		bool bIsElectedDm = g_bElectedDm;
		pthread_mutex_unlock(&dm_list_mutex);

		// If we are a backup DM, an Ack has already been sent
		if (!bIsElectedDm)
			return 0;
	}
	// Otherwise, send
#endif
	debug_f(2, "Sending SDMAck message.\n");
	msgAck.error = sAckStatus;
	if (bUseComponentId)
	{
	   debug_f(2, "Sending SDMAck message with code: %i to address: 0x%lx port: %i\n", msgAck.error, idDest.getAddress(), idDest.getPort());
		iResult = msgAck.SendTo(idDest);
	}
	else
		iResult = msgAck.Send(AppHandle);

	MessageSent(&msgAck);
	return iResult;
}
/*
	Description:
		Handling of the SDMxTEDS message

	Input:
		arg - a pointer to an xTEDSParameter

	Output:
		None

	Changed:
		None

*/
void* xTEDS(void* arg)
{
	char strDeviceName[XTEDS_MAX_ITEM_NAME_SIZE];
	xTEDSLibraryListNode* flag;
	SecTime start, delay;
	SDM_GetTime(start);
	unsigned short usPort = 0;
	int iDeviceType = 0;		// One of ROBOHUB, APPLICATION, or DEVICE
	SDMxTEDS msgXteds;
	xTEDSParameters* param;
	SDMComponent_ID RequesterId;
	bool bAckUseDeviceAddress = false;
	//
	// Pull out all of the needed information from the xTEDS parameters
	param = (xTEDSParameters*) arg;
	const char* buf = param->getBuffer();
	RequesterId = param->getSenderAddress();
	const SDMComHandle& AppComHandle = param->GetComHandle();

	//
	// Unmarshal the message
	if(msgXteds.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMxTEDS message!\n\n");
		SendAckMessage(SDM_INVALID_XTEDS, bAckUseDeviceAddress, RequesterId, AppComHandle);
		delete(param);
		registerNext = true;
		return NULL;
	}
	MessageReceived(&msgXteds);

	//
	// Save the IP information about the sender
	if(msgXteds.source.getAddress() != 0)
	{
		RequesterId = msgXteds.source;
		bAckUseDeviceAddress = true;
	}
	else if(RequesterId.getAddress() == L_LOCAL_HOST && Address_DM != L_LOCAL_HOST)
	{
		RequesterId.setAddress(Address_DM);
		msgXteds.source.setAddress(Address_DM);
	}
	else
		msgXteds.source.setAddress(RequesterId.getAddress());

	if (debug >= 1)
	  {
	    char strTargetAddr[64];
	    msgXteds.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    debug_f(1, "SDMxTEDS from %s length %d PID: %ld\n",
		    strTargetAddr, strlen(msgXteds.xTEDS), msgXteds.getPID());

	    if(debug >= 1 && strlen(msgXteds.SPA_node) != 0)
		debug_f(4," SPA_node: %s\n",msgXteds.SPA_node);
	  }

	usPort = msgXteds.source.getPort();
	//
	// Determine if this is a segmented xTEDS
	pthread_mutex_lock(&SegmentBuilderMutex);
	if (xTEDSBuilder.IsSegmentedxTEDS(msgXteds))
	{
		bool xTEDSFinished = false;
		//This xTEDS is segmented, apply this segment
		if (xTEDSBuilder.ApplySegment(msgXteds))
		{
			//Check to see if the xTEDS is finished
			if (xTEDSBuilder.CheckIsFinished(msgXteds))
			{
				//Pull the xTEDS out of the segment builder
				if (xTEDSBuilder.GetFullxTEDS(msgXteds, msgXteds.xTEDS, sizeof(msgXteds.xTEDS)))
					xTEDSFinished = true;
				//Error occurred
				else
					printf("Data Manager could not retrieve the segmented xTEDS.\n\n");
			}
			debug_f(1,"xTEDS segment received.\n\n");
			//
			//Send back an SDMAck for this message
			SendAckMessage(SDM_OK, bAckUseDeviceAddress, RequesterId, AppComHandle);
		}
		//Segment apply failed for some reason
		else
		{
			printf("Error: xTEDS segment could not be stored.\n\n");
			//TODO:  Send nack or just timeout?
		}
		//
		//If the xTEDS is not finished, stop here
		if (!xTEDSFinished)
		{
			pthread_mutex_unlock(&SegmentBuilderMutex);
			delete (param);
			registerNext = true;
			return NULL;
		}
		//Otherwise, drop through and continue to parse the xTEDS
	}
	pthread_mutex_unlock(&SegmentBuilderMutex);
	//
	//These are a few simple checks to determine if a valid xTEDS document was received correctly, these operations are cheaper
	//than determining the same information during a full parse.
	iDeviceType = ParseDeviceName(msgXteds.xTEDS, strDeviceName /*return value*/, sizeof(strDeviceName), debug);	//Get the device name
	if(iDeviceType < 0)	//If the device or application name was not found
	{
		printf("Invalid xTEDS format, xTED will not be registered! Missing Device or Application name.\n\n");	//This currently happens if the device or application name cannot be found
		SendAckMessage(SDM_INVALID_XTEDS, bAckUseDeviceAddress, RequesterId, AppComHandle);
		delete(param);
		registerNext = true;
		return NULL;
	}
	if(msgXteds.xTEDS[0] != '<')
	{
		printf("Invalid xTEDS format, xTED will not be registered! Missing opening.\n\n");	//This currently happens if the xTEDS is not started properly
		SendAckMessage(SDM_INVALID_XTEDS, bAckUseDeviceAddress, RequesterId, AppComHandle);
		delete(param);
		registerNext = true;
		return NULL;
	}
	if(strstr(&msgXteds.xTEDS[0],"</xTEDS>") == NULL)
	{
		printf("Invalid xTEDS format, xTED will not be registered! Missing closing </xTEDS>\n\n");	//This currently happens if the xTEDS is not ended properly
		SendAckMessage(SDM_INVALID_XTEDS, bAckUseDeviceAddress, RequesterId, AppComHandle);
		delete(param);
		registerNext = true;
		return NULL;
	}
	addLibrary.Wait();
	int iSpot = 0;  //Reference index for xTEDSList node
	flag = AlreadyRegistered(strDeviceName, buf, usPort, RequesterId, iDeviceType, iSpot /*return value*/);
	if(iSpot == -1)
	{	// This device is already registered
    SDMID idMessage;   //Send a registration confirmation as well as inform component of its Component_ID
    idMessage.destination = RequesterId;
    idMessage.destination.setPort(usPort);
    idMessage.destination.setSensorID(flag->data->getSensorID());
    idMessage.SendTo(idMessage.destination);

		addLibrary.Signal();
		SendAckMessage(SDM_OK, bAckUseDeviceAddress, RequesterId, AppComHandle);
		delete(param);
		registerNext = true;
		return NULL;
	}

	if(flag == NULL)
	{
		if(strncmp(strDeviceName,"RoboHub",7) == 0 || strncmp(strDeviceName,"RobustHub",9) == 0)
		{
			debug_f(3,"Robust Hub being registered\n");
			iDeviceType = ROBOHUB;
		}
#ifdef BUILD_FOR_XTEDS_MERGING
		bool MergeResult = MergexTEDS(flag, false, msgXteds, iSpot, iDeviceType);
#endif

		flag = StoreInfo(strDeviceName, iSpot, RequesterId, buf, iDeviceType);

#ifdef BUILD_FOR_XTEDS_MERGING
		flag->data->setMerged(MergeResult);
		if (MergeResult == true)
			debug_f(1,"Device xTEDS successfully merged with configuration file.\n");
#endif
		debug_f(5,"Finished Storing the info about the xTEDS\n");

		if(flag->data->setxTEDS(msgXteds.xTEDS) == false)
		{
			bool IsASIM = IsPIDFromASIM(msgXteds.getPID());
			bool IsxTEDSValid = false;

			// Try DM's saved version of xTEDS for that PID, if it exists
			if (IsASIM)
			{
				//If the xTEDS exists
				if (Retrieve_xTEDS (msgXteds.getPID(), msgXteds.xTEDS))
				{
					//If the xTEDS parsed correctly
					if(flag->data->setxTEDS(msgXteds.xTEDS))
						IsxTEDSValid = true;
				}
				else
					printf("\txTEDS:  Failed to retrieve stored ASIM xTEDS!\n\n");
			}

			if (!IsxTEDSValid)
			{
				flag->data->setAvailable(true);
				flag->data->setActive(false);
				flag->data->setMerged(false);
				flag->data->inUse->Signal();
				//xTED was invalid
				printf("\txTEDS was invalid!\n\n");
				addLibrary.Signal();
				SendAckMessage(SDM_INVALID_XTEDS, bAckUseDeviceAddress, RequesterId, AppComHandle);
				delete(param);
				registerNext = true;
				return NULL;								// Found problem with xTEDS
			}
		}
		else
		{
			//If this is an ASIM, try to store the xTEDS
			if (IsPIDFromASIM(msgXteds.getPID()) && !Store_xTEDS(msgXteds.getPID(), msgXteds.xTEDS))
			{
				printf("\txTEDS:  Failed to Store xTEDS!\n\n");
			}
		}

		flag->data->inUse->Signal();
	}
#ifdef BUILD_FOR_XTEDS_MERGING
	//Check for any xTEDS that might need to be merged if this was a robohub that registered
	int n = 0;
	xTEDSLibraryListNode* node;
	if(flag->data->getHub() == ROBOHUB && flag->data->getMerged() == true)
	{
		node = xTEDSList.head;
		SDMxTEDS update;
		while(node!=NULL)		// search through the registered items non-merged xTEDS....
		{
			if(node != flag)
				node->data->inUse->Wait();
			if(node->data->getMerged() == false && node->data->getHub() == DEVICE) //Look for unmerged devices
			{
				//Try to merge due to new registration
				strncpy(update.xTEDS,node->data->getxTEDS(),sizeof(update.xTEDS));
				strncpy(update.SPA_node,node->data->getSPANode(),sizeof(update.SPA_node));
				node->data->inUse->Signal();
				if(MergexTEDS(node,true,update,n,1))
				{
					debug_f(1,"Device (%s) xTEDS successfully merged with configuration file.\n",node->data->getName());
				}
			}
			else
				node->data->inUse->Signal();
			node = node->next;
			n++;
		}
	}
#endif // #ifdef BUILD_FOR_XTEDS_MERGING
	debug_f(4,"Checking for any subscriptions\n");

	flag->data->inUse->Wait();
	bool IsActive = flag->data->getActive();
	unsigned long ulSID = flag->data->getSensorID();
	flag->data->inUse->Signal();
	//Get the index to the xTEDS node
	int iXtedsRefIndex = (ulSID >> 16) & 0xFF;

#ifdef PNP_BACKUP
    if(IAmElected())
    {
        //send the xTEDS to all known DM's
        flag->data->inUse->Wait();
        msgXteds.source.setSensorID(flag->data->getComponentID().getSensorID());
        flag->data->inUse->Signal();

        pthread_mutex_lock(&dm_list_mutex);
        backupDMList.SendMessageToAll(msgXteds);
        pthread_mutex_unlock(&dm_list_mutex);
    }
#endif

   if(usPort != PORT_DM)
   {
      SDMID idMessage;   //Send a registration confirmation as well as inform component of its Component_ID
      idMessage.destination = RequesterId;
      idMessage.destination.setPort(usPort);
      idMessage.destination.setSensorID(ulSID);
      idMessage.SendTo(idMessage.destination);
      char strTargetAddr[64];
      idMessage.destination.IDToString(strTargetAddr, sizeof(strTargetAddr));
	  SDM_GetTime(delay);
	  delay -= start;
	  debug_f(2, "after %d ms, SDMID sent to %s\n", delay.GetSeconds()*1000+delay.GetUSeconds()/1000, strTargetAddr);
   }


	SendAckMessage(SDM_OK, bAckUseDeviceAddress, RequesterId, AppComHandle);
	delete(param);
	PrintxTEDS();

	//See if there are any previously interested subscribers for this new registration
	if (IsActive && IAmElected())
	{
		PublishNotification(ulSID, NOTI_REGISTRATION);
		PublishNotification(ulSID, NOTI_REGISTRATION_CHANGE, REGISTRATION_MODIFICATION);
		PublishxTEDSModificationSubscription(ulSID, SEARCH_REPLY, MOD_NOT_APPLICABLE, iXtedsRefIndex);
		PublishxTEDSModificationSubscription(ulSID, REQ_REG_FUTURE, MOD_NOT_APPLICABLE, iXtedsRefIndex);
		PublishxTEDSModificationSubscription(ulSID, VAR_REQ_REPLY, MOD_NOT_APPLICABLE, iXtedsRefIndex);
	}

	//addLibrary must be held so that there are no state changes while handling subscriptions or printing xTEDS
	addLibrary.Signal();
	registerNext = true;
	return NULL;
}

/*
	Description:
		Handling of the SDMCancelxTEDS message

	Input:
		arg - a pointer to an xTEDSParameter

	Output:
		None

	Changed:
		None

*/
void* CancelxTEDS(void* arg)
{
	/* remove xTEDS info from storage */
	unsigned long ulTempID;
	SDMCancelxTEDS msgCancel;
	xTEDSLibraryListNode* node;
	xTEDSParameters* param;
	SDMComponent_ID RequesterId;
	bool bAckUseDeviceAddress = false;

	param = (xTEDSParameters*) arg;
	const char* buf = param->getBuffer();
	RequesterId = param->getSenderAddress();
	const SDMComHandle& AppComHandle = param->GetComHandle();

	if(msgCancel.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMCancelxTEDS message!\n\n");
		SendAckMessage(SDM_INVALID_CANCEL, bAckUseDeviceAddress, RequesterId, AppComHandle);
		delete (param);
		cancelNext = true;
		return 0;
	}
	MessageReceived(&msgCancel);

	// Copy sensor ID and port into a temp for string comparison
	unsigned long ulSID = msgCancel.source.getSensorID();
	unsigned short usPort = msgCancel.source.getPort();
	//
	// Set the address information
	if(msgCancel.source.getAddress() != 0)
	{
		RequesterId.setAddress(msgCancel.source.getAddress());
		//TODO:
		// Applications will usually fill in msgCancel.source.getAddress, how
		// to distinguish between devices and apps?
		//bAckUseDeviceAddress = true;
	}
	else if(RequesterId.getAddress() == L_LOCAL_HOST && Address_DM != L_LOCAL_HOST)
	{
		RequesterId.setAddress(Address_DM);
		msgCancel.source.setAddress(Address_DM);
	}
	else
		msgCancel.source.setAddress(RequesterId.getAddress());

	if (debug >= 1)
	  {
	    char strTargetAddr[64];
	    msgCancel.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	    debug_f(1, "SDMCancelxTEDS for %s\n", strTargetAddr);
	  }

	//
	// Start looking for the xTEDS to cancel
	node = xTEDSList.head;
	int iRemoveRef = 0;
	while(node!=NULL)
	{
		node->data->inUse->Wait();
		if(node->data->getAvailable() == false)
		{
			// PORT_PM only matches if a PID was also present, otherwise the PM may accidentally
			// cancel a persistent application's xTEDS whose SID was sent as zero, when
			// the PM cancels itself
			// Also, if the port and sensor id are zero, this is the Network Manager cancelling a
			// SPA-S ASIM's xTEDS when it detects a disconnect
			if(usPort == node->data->getTargetPort() || (usPort == PORT_PM && ulSID != 0) || (usPort == 0 && ulSID == 0))
			{
				if (RequesterId.getAddress() == node->data->getAddress())
				{
					if(node->data->getActive() == true)
					{
						ulTempID = node->data->getSensorID();	//Get sensor ID DM created
						ulTempID &= 0x000000FF;	//Change DM sensor ID to ID assigned by SM or application
						// Cancel the xTEDS corresponding to the user-specified SID
						if((ulSID&0x000000FF) == ulTempID || (usPort == PORT_PM && node->data->getTargetPort() != PORT_DM && node->data->getTargetPort() != PORT_SM && node->data->getTargetPort() != PORT_TM && node->data->getTargetPort() != PORT_SPA1_MANAGER))
						{
							if(usPort == PORT_PM)
							{
								// If the PM is cancelling an xTEDS
								if(ulSID == node->data->getPid())
								{
									debug_f(3,"Sensor name to cancel is %s\n", node->data->getName());
									node->data->inUse->Signal();
									break;
								}
							}
							else
							{
								debug_f(3,"Sensor name to cancel is %s\n", node->data->getName());
								node->data->inUse->Signal();
								break;
							}
						}
					}
				}
			}
		}
		iRemoveRef++;
		node->data->inUse->Signal();
		node = node->next;
	}
	addLibrary.Wait();
	//
	// If the xTEDS couldn't be found, report error and exit
	if(node==NULL)
	{
		debug_f(0,"Could not identify the sensor to cancel.\n");
		SendAckMessage(SDM_UNKNOWN_XTEDS, bAckUseDeviceAddress, RequesterId, AppComHandle);
		delete(param);
		PrintxTEDS();
		addLibrary.Signal();
		cancelNext = true;
		return 0;
	}

	node->data->inUse->Wait();
	const unsigned long CancelSensorID = node->data->getSensorID();
	const SDMComponent_ID CancelComponentId = node->data->getComponentID();
	msgCancel.source.setSensorID(CancelSensorID);
	if(!(node->data->getTargetPort() == PORT_SM || node->data->getTargetPort() == PORT_SPA1_MANAGER || node->data->getTargetPort() == PORT_TM || node->data->getTargetPort() == PORT_PM))
	{
		node->data->setActive(false);
		node->data->setPosted(false);
	}

	if(msgCancel.fullCancel == 1)
	{
	   node->data->setActive(true);
	}
	node->data->inUse->Signal();
	//
	// Publish any subscriptions about the cancellation
#ifdef PNP_BACKUP
	if (IAmElected())
	{
#endif
		debug_f(4,"Checking for any subscriptions\n");
		PublishxTEDSModificationSubscription(CancelSensorID, REQ_REG_CANCELLATION, DEREGISTRATION_MODIFICATION, iRemoveRef);
		PublishNotification(CancelSensorID, NOTI_DEREGISTRATION);
		PublishNotification(CancelSensorID, NOTI_REGISTRATION_CHANGE, DEREGISTRATION_MODIFICATION);
#ifdef PNP_BACKUP
	}
#endif
	//
	// Notify any devices about the cancelled application (ala SDMDeletesub)
	pthread_mutex_lock(&sensor_subs_mutex);
	g_SensorSubscriptions.SubscriberFinish(CancelComponentId);
	g_SensorSubscriptions.ProviderFinish(CancelComponentId);
	pthread_mutex_unlock(&sensor_subs_mutex);

	node->data->inUse->Wait();
	if(node->data->getTargetPort()==PORT_DM)
	{
		printf("Only the Data Manager can cancel its xTEDS!!\n\n");
		node->data->inUse->Signal();
		SendAckMessage(SDM_INVALID_CANCEL, bAckUseDeviceAddress, RequesterId, AppComHandle);
		delete (param);
		addLibrary.Signal();
		cancelNext = true;
		return 0;
	}
	if(node->data->getActive() == true)
	{
		node->data->setAvailable(true);
		node->data->setTargetPort(0);
		node->data->setConnections(0);
		node->data->setPid(0);
		node->data->setHub(0);
		node->data->setMerged(false);
		node->data->setActive(false);
	}
	node->data->inUse->Signal();

#ifdef PNP_BACKUP
	//send CancelxTEDS to all known backup DM's
	pthread_mutex_lock(&dm_list_mutex);
	backupDMList.SendMessageToAll(msgCancel);
	pthread_mutex_unlock(&dm_list_mutex);
#endif

	SendAckMessage(SDM_OK, bAckUseDeviceAddress, RequesterId, AppComHandle);
	delete(param);
	PrintxTEDS();
	addLibrary.Signal();
	cancelNext = true;
	return 0;
}

/*
	Cancel a task's xTEDS but don't mark it as unposted.  This is because a PM will restart
	the task, and any subscribers should be notified via the DM services, but the TM still
	has it scheduled to the PM node.  This prevents the task from being reposted if an
	extern application does SDMReqReg and it matches the unposted task.
 */
void TaskError(char* buf, int size, const SDMComponent_ID& RequesterId)
{
	SDMTaskError msgError;
	if (msgError.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMTaskError message.\n");
		return;
	}
	MessageReceived(&msgError);

#ifdef PNP_BACKUP
		// Send the TaskError message to all backup DMs
		SDMComponent_ID temp = RequesterId;
		msgError.source = RequesterId;
		pthread_mutex_lock(&dm_list_mutex);
		backupDMList.SendMessageToAll(msgError);
		pthread_mutex_unlock(&dm_list_mutex);
		msgError.source = temp;
#endif

		debug_f(1, "SDMTaskError for \"%s\" pid: %u",
		msgError.filename, msgError.pid);

	//
	// Start looking for the xTEDS to cancel
	xTEDSLibraryListNode* node = xTEDSList.head;
	int iRemoveRef = 0;
	while(node!=NULL)
	{
		node->data->inUse->Wait();
		if(node->data->getAvailable() == false)
		{
			if (RequesterId.getAddress() == node->data->getAddress())
			{
				if(node->data->getActive() == true)
				{
					if (node->data->getPid() == msgError.pid)
					{
						debug_f(3,"Sensor name to cancel is %s\n", node->data->getName());
						node->data->inUse->Signal();
						break;
					}
				}
			}
		}
		iRemoveRef++;
		node->data->inUse->Signal();
		node = node->next;
	}
	addLibrary.Wait();
	//
	// If the xTEDS couldn't be found, report error and exit
	if(node==NULL)
	{
		debug_f(0,"Could not identify the sensor to cancel.\n");
		addLibrary.Signal();
		return ;
	}

	node->data->inUse->Wait();
	node->data->setActive(false);
	// Keep this task posted so a ReqReg won't re-post it -- the PM will
	// immediately restart it
	node->data->setPosted(true);
	const unsigned long CancelSensorID = node->data->getSensorID();
	const SDMComponent_ID& CancelComponentId = node->data->getComponentID();
	node->data->inUse->Signal();

        //
	// Notify any devices about the cancelled application (ala SDMDeletesub)
	pthread_mutex_lock(&sensor_subs_mutex);
	g_SensorSubscriptions.SubscriberFinish(CancelComponentId);
	g_SensorSubscriptions.ProviderFinish(CancelComponentId);
	pthread_mutex_unlock(&sensor_subs_mutex);

    //Remove any subscriptions that the failed task had
    pthread_mutex_lock(&subscription_mutex);
	subscribers.removeReqRegSubscription(11, CancelComponentId, debug);
	pthread_mutex_unlock(&subscription_mutex);

	PrintxTEDS();
	//
	// Publish any subscriptions about the cancellation
	if (IAmElected())
	{
		debug_f(4,"Checking for any subscriptions\n");
		PublishxTEDSModificationSubscription(CancelSensorID, REQ_REG_CANCELLATION, DEREGISTRATION_MODIFICATION, iRemoveRef);
		PublishNotification(CancelSensorID, NOTI_DEREGISTRATION);
		PublishNotification(CancelSensorID, NOTI_REGISTRATION_CHANGE, DEREGISTRATION_MODIFICATION);
	}


	addLibrary.Signal();
	return ;
}

/*
	Description:
		Handling of the SDMReqxTEDS message

	Input:
		buf  - the message in an array
		size  -  the length of the message in bytes
		ipaddr - the ip address in dot notation
		dport - the port the message came from

	Output:
		None

	Changed:
		None

*/
void ReqxTEDS(char *buf, int size, const SDMComponent_ID& SenderId)
{
	int iSelect = 0,found = 0,length = 0;
	unsigned long sID = 0;
	char msg[LARGE_MSG_BUFSIZE];
	unsigned short usPort = 0;
	int reply = 0;
	int temp = 0;
	SDMReqxTEDS msgRequest;
	SDMxTEDSInfo msgInfo;
	xTEDSLibraryListNode* node;
	SDMComponent_ID id;

	if(msgRequest.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMReqxTEDS message!\n\n");
		return;
	}
	MessageReceived(&msgRequest);

  memset(msg, 0, LARGE_MSG_BUFSIZE);
	//Get ip address where message sent from
	iSelect = msgRequest.select;
	iSelect &= 0x01;
	reply = msgRequest.select;
	reply &= 0x02;
	usPort = msgRequest.destination.getPort();
	if(reply == 0)
		usPort = SenderId.getPort();
	if(msgRequest.destination.getAddress() == 0)
		id.setAddress(SenderId.getAddress());
	else
		id.setAddress(msgRequest.destination.getAddress());
	id.setPort(usPort);
	temp = msgRequest.select;

	if(temp > 3)
	{
		printf("Select byte is not set to a valid value, cannot complete request!\n\n");
		return;
	}
	if(iSelect == 0)		//select byte is set to use sensorID
	{
		sID = msgRequest.source.getSensorID();
		if (debug >= 1)
		  {
		    char strRequesterAddr[64];
		    char strTargetAddr[64];
		    msgRequest.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
		    msgRequest.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
		    debug_f(1, "SDMReqxTEDS for %s from %s select: %d\n",
			    strTargetAddr, strRequesterAddr, msgRequest.select);
		  }

		node = MatchSID(sID);
		if(node==NULL)
		{
			printf("No matching sensorID found\n\n");
		}
		else
			found = 1;

		if(found == 1)
		{
			msgInfo.source.setSensorID(node->data->getSensorID());
			msgInfo.source.setPort(node->data->getTargetPort());
			msgInfo.source.setAddress(node->data->getAddress());
			length = strlen(node->data->getxTEDS());	//Set the length of the xTED
			memcpy(&msgInfo.xTEDS,node->data->getxTEDS(),length);
			msgInfo.xTEDS[length] = '\0';	//Null terminate the msg
			debug_f(1,"Sending xTEDS for %s\n",node->data->getName());
			node->data->inUse->Signal();
			msgInfo.Send(id);
			MessageSent(&msgInfo);
			msgInfo.Marshal(msg);
			msgInfo.SendEmpty(id);
			MessageSent(&msgInfo);
			debug_f(1,"Message sent to app: %c on port %hu\n",msg[0],usPort);
		}
		else
		{
			msgInfo.SendEmpty(id);
			MessageSent(&msgInfo);
			debug_f(1,"Empty message sent to app: %c\n",msg[0]);
		}
	}
	else	//If xTED found with device_name
	{
	  if (debug >= 1)
	    {
	      char strRequesterAddr[64];
	      char strTargetAddr[64];
	      msgRequest.source.IDToString(strTargetAddr, sizeof(strTargetAddr));
	      msgRequest.destination.IDToString(strRequesterAddr, sizeof(strRequesterAddr));
	      debug_f(1, "SDMReqxTEDS for %s from %s select: %d device: %s\n",
		      strTargetAddr, strRequesterAddr, msgRequest.select,
		      msgRequest.device_name);
	    }
		node = xTEDSList.head;
		while(node!=NULL)	//Look at each xTED device name
		{
			node->data->inUse->Wait();
			if(node->data->getAvailable() == false)	//Check to see if there is an xTED at this array location
			{
				if(strncmp(msgRequest.device_name,node->data->getName(),strlen(node->data->getName()))==0)	//Check to see if device name matches
				{
					found = 1;	//Set found to 1
				}
			}

			if(found == 1)	//If a device name matched
			{
				msgInfo.source.setSensorID(node->data->getSensorID());
				msgInfo.source.setPort(node->data->getTargetPort());
				msgInfo.source.setAddress(node->data->getAddress());
				length = strlen(node->data->getxTEDS());	//Set the length of the xTED
				memcpy(&msgInfo.xTEDS,node->data->getxTEDS(),length);
				msgInfo.xTEDS[length] = '\0';	//Null terminate the msg
				debug_f(1,"Sending xTED for %s\n",node->data->getName());
				msgInfo.Marshal(msg);
				msgInfo.Send(id);
				MessageSent(&msgInfo);
				debug_f(1,"Message sent to app: %c on port %hu\n", msg[0], usPort);
				found = 0;	//Set found to 0
			}
			node->data->inUse->Signal();
			node = node->next;
		}
		msgInfo.SendEmpty(id);
		MessageSent(&msgInfo);
		debug_f(1,"Message sent to app: %c on port %hu\n", msg[0], usPort);
	}
}

/*
	Description:
		Handling of Subscriptions to various item the DM produces. See the DM xTEDS.

	Input:
		ipaddress - the ip address of the subscriber in dot form
		port - the port of the subscriber
		mID - the message ID of the subscription to be published

	Output:
		None

	Changed:
		None

*/
void Subscribe(const SDMComponent_ID& SubscriberId, const SDMMessage_ID& mID)
{
	xTEDSLibraryListNode* node;
	long ulSID = 0;
	SDMData msgData;
	SubscriptionListNode* result;

	// Add this subscription
	pthread_mutex_lock(&subscription_mutex);
	result = subscribers.addSubscription(SubscriberId, mID.getInterfaceMessagePair(), debug);
	pthread_mutex_unlock(&subscription_mutex);
	if(result==NULL)
		return;

   if(!IAmElected())
   {
      return;
   }

	// For subscriptions to registration events, send all currently registered devices
	if(mID == NOTI_REGISTRATION || mID == NOTI_REGISTRATION_CHANGE)
	{
		node = xTEDSList.head;
		while(node!=NULL)
		{
			node->data->inUse->Wait();
			if(node->data->getAvailable() == false)
			{
				msgData.source = DataManager;
				msgData.msg_id = mID;	//Copy the mID into msg

				ulSID = node->data->getSensorID();
				if(mID == NOTI_REGISTRATION)
				{
					PUT_ULONG(&msgData.msg[0], ulSID);	//Copy sID into msg
					msgData.Send(SubscriberId, 4);
					MessageSent(&msgData);

					debug_f(1,"Sent msg to %s at port %hu sensorID: %lu msgID: 0x%x msg data of %x %x %x %x\n",result->data->getAddress(),result->data->getPort(),msgData.source.getSensorID(), msgData.msg_id.getInterfaceMessagePair(), msgData.msg[0], msgData.msg[1],msgData.msg[2],msgData.msg[3]);
				}
				else
				{
				   unsigned char temp = REGISTRATION_MODIFICATION;
					PUT_UCHAR(&msgData.msg[0], temp);
					PUT_ULONG(&msgData.msg[1], ulSID);	//Copy sID into msg
					msgData.Send(SubscriberId, 5);
					MessageSent(&msgData);

					debug_f(1,"Sent msg to %s at port %hu sensorID: %lu msgID: 0x%x msg data of %x %x %x %x %x\n", result->data->getAddress(), result->data->getPort(), msgData.source.getSensorID(), msgData.msg_id.getInterfaceMessagePair(), msgData.msg[0], msgData.msg[1], msgData.msg[2], msgData.msg[3], msgData.msg[4]);
				}
			}
			node->data->inUse->Signal();
			node = node->next;
		}
	}
	else if(mID == NOTI_PERFORMANCE_COUNTERS)
	{
		debug_f(0, "Subscription to performance counters at 0x%lx:%hu\n", SubscriberId.getAddress(), SubscriberId.getPort());

#ifndef __VXWORKS__
		itimerval interval;
		getitimer(ITIMER_REAL, &interval);
		if (interval.it_value.tv_sec == 0 && interval.it_interval.tv_sec == 0)
		{
			//Time interval for the publish interval of the performance counter
			timeval pubInterval;
			pubInterval.tv_sec = 1;
			pubInterval.tv_usec = 0;

			itimerval timerInterval;
			timerInterval.it_interval = pubInterval;
			timerInterval.it_value = pubInterval;

			//Set the performance counter timer
			setitimer (ITIMER_REAL, &timerInterval, NULL);
		}
#else  //VxWorks has a different timer API
		itimerspec interval;
		timer_gettime(CLOCK_REALTIME, &interval);
		if (interval.it_value.tv_sec == 0 && interval.it_interval.tv_sec == 0)
		{
			//Time interval for the publish interval of the performance counter
			itimerspec timerInterval;
			timerInterval.it_value.tv_sec = 1;
			timerInterval.it_value.tv_nsec = 0;

			//Set the performance counter timer
			timer_settime(CLOCK_REALTIME, 0, &timerInterval, NULL);
		}
#endif
	}
	return;	//Function is finished
}

/*
	Description:
		Handling of canceling of a subscription that the DM publishes.  See the DM xTEDS.

	Input:
		ipaddress - the ip address of the subscriber
		port - the port of the subscriber
		mID - the message ID of the subscription

	Output:
		None

	Changed:
		None

*/
void CancelSubscription(const SDMComponent_ID& SubscriberId, int mID)
{
	SubscriptionListNode* node;

	pthread_mutex_lock(&subscription_mutex);
	node = subscribers.head;
	while(node!=NULL)  //look through subscriptions
	{
		if(node->data->getInuse() == true) //Check to see if in use
		{
			if(node->data->getDestination() == SubscriberId)
			{
				if(node->data->getmID() == mID)	//Check to see if message id matches
				{
					if(node->data->getItems() == false)
					{
						node->data->setPort(0);	//Set port to 0
						node->data->setmID(0);	//Set message id to 0
						node->data->setInuse(false);	//Set in use to false
						debug_f(2,"Canceled subscription\n\n");
						pthread_mutex_unlock(&subscription_mutex);
						return;
					}
				}
				else
				{
					debug_f(4,"Unable to cancel subscription because message ID does not match current subscriptions\n");
				}
			}
			else
			{
				debug_f(4,"Unable to cancel subscription because address does not match current subscription\n");
			}
		}
		node = node->next;
	}
	pthread_mutex_unlock(&subscription_mutex);
	printf("The DM was unable to cancel your subscription because there was no subscription matching your Cancel request\n");
}

/*
	Description:
		Handling of publishing messages that the DM generates.  This function handles the DM's subscriptions in its xTEDS as well
		as subscriptions that are generated from the FUTURE ReqReg and Search queries.  For the latter subscriptions, this function
		depends on calling again the ReqReg and Search functions in order for the publication, but sets the xTEDref variable so it
		doesn't perform an exhaustive search.

	Input:
		node - a pointer to a subscription list node
		sID - generally the sensorID of the device in question
		mID - the message ID of the subscription
		xTEDref - an index to the xTEDS node

	Output:
		None

	Changed:
		None

*/

void PublishxTEDSModificationSubscription(unsigned long SensorID, int MessageID, int ModificationAction, int xTEDSRef)
{
	char MessageBuffer[BUFSIZE];
	int MessageSize = 0;
	SDMComponent_ID SubscriberID;
	SubscriptionListNode* CurSub = NULL;

	pthread_mutex_lock(&subscription_mutex);
	CurSub = subscribers.head;
	int n = 0;
	while(CurSub!=NULL)	//Check for matching registration subscriptions
	{
		// If the current subscription node is in use and the message id matches
		if(CurSub->data->getInuse() == true && CurSub->data->getmID() == MessageID)
		{
			debug_f(4,"subscribers[%d].submID 0x%x\n", n, CurSub->data->getmID());
			debug_f(4,"Publishing message ID of 0x%x\n",MessageID);

			SubscriberID = CurSub->data->getDestination();

			if(MessageID == REQ_REG_FUTURE || MessageID == REQ_REG_CANCELLATION)	//If mID matches
			{
				//If this is a REQREG, or REQREG_CANCEL
				if(CurSub->data->getItems() == true)	//If subscription has items
				{
					debug_f(4, "Performing subscriber ReqReg with action %d\n",ModificationAction);
					// Put together a SDMReqReg message
					SDMReqReg req;
					req.reply = SDM_REQREG_CURRENT;
					req.destination = SubscriberID;
					req.id = CurSub->data->getID();
					req.source = CurSub->data->getSource();

					// Copy item_name into msg
					memcpy(req.item_name,CurSub->data->getItemName(),strlen(CurSub->data->getItemName())+1);

					// Copy qual_list into msg
					memcpy(req.quallist,CurSub->data->getQuallist(),strlen(CurSub->data->getQuallist())+1);

					// Copy device into msg
					memcpy(req.device,CurSub->data->getDevice(),strlen(CurSub->data->getDevice())+1);

					// Copy interface into msg
					memcpy(req.interface,CurSub->data->getInterface(),strlen(CurSub->data->getInterface())+1);

					MessageSize = req.Marshal(MessageBuffer);

					pthread_mutex_unlock(&subscription_mutex);
					ReqReg(MessageBuffer, MessageSize, xTEDSRef, SubscriberID, ModificationAction);
					pthread_mutex_lock(&subscription_mutex);
				}
			}
			else if(MessageID == SEARCH_REPLY)	//If submID is for a Search
			{
				debug_f(4,"Performing subscriber Search\n");
				SDMSearch sear;
				sear.reply = SDM_SEARCH_CURRENT;
				sear.destination.setPort(CurSub->data->getPort());
				sear.id = CurSub->data->getID();
				sear.source = CurSub->data->getSource();

				memcpy(sear.reg_expr, CurSub->data->getItemName(), strlen(CurSub->data->getItemName())+1);
				MessageSize = sear.Marshal(MessageBuffer);

				pthread_mutex_unlock(&subscription_mutex);
				Search(MessageBuffer, MessageSize, SubscriberID, xTEDSRef);
				pthread_mutex_lock(&subscription_mutex);
			}
			else if(MessageID == VAR_REQ_REPLY)
			{
				debug_f(4,"Performing subscriber VarInfo\n");
				SDMVarReq var;
				var.reply = SDM_VARREQ_CURRENT;
				var.destination.setPort(CurSub->data->getPort());
				var.id = CurSub->data->getID();
				var.source = CurSub->data->getSource();
				var.msg_id = atoi(CurSub->data->getInterface());

				memcpy(var.variable, CurSub->data->getItemName(), strlen(CurSub->data->getItemName())+1);
				MessageSize = var.Marshal(MessageBuffer);

				pthread_mutex_unlock(&subscription_mutex);
				VarReq(MessageBuffer, MessageSize, SubscriberID, xTEDSRef);
				pthread_mutex_lock(&subscription_mutex);
			}
		}
		CurSub = CurSub->next;
		n++;
	}
	pthread_mutex_unlock(&subscription_mutex);
}
void PublishNotification(unsigned long SensorID, SDMMessage_ID MessageID, int ModificationAction)
{
	SDMData msgData;
	msgData.msg_id = MessageID;
	msgData.source = DataManager;

	debug_f(3, "Attempting to publish a notification for interface %hhd message %hhd.\n", MessageID.getInterface(), MessageID.getMessage());

	pthread_mutex_lock(&subscription_mutex);
	SubscriptionListNode* CurSub = subscribers.head;
	while (CurSub != NULL)
	{
		if (CurSub->data->getInuse() == true && CurSub->data->getmID() == MessageID.getInterfaceMessagePair())
		{
			if (MessageID == NOTI_REGISTRATION || MessageID == NOTI_DEREGISTRATION || MessageID == NOTI_XTEDS_MODIFICATION)
			{
				debug_f(3, "  Publishing a registration, deregistration, or modification notification.\n");
				PUT_ULONG (msgData.msg, SensorID);
				msgData.Send(CurSub->data->getDestination(), sizeof(unsigned long));
				MessageSent(&msgData);
			}
			else if (MessageID == NOTI_REGISTRATION_CHANGE)
			{
				debug_f(3, "  Published a registration change notification.\n");
				unsigned char temp = (unsigned char)ModificationAction;
				PUT_UCHAR (msgData.msg, temp);
				PUT_ULONG (msgData.msg+1, SensorID);
				msgData.Send(CurSub->data->getDestination(), sizeof(unsigned long) + 1);
				MessageSent(&msgData);
			}
			else if (MessageID == NOTI_PERFORMANCE_COUNTERS)
			{
				debug_f(3, "  Publishing performance counters.\n");
				pthread_mutex_lock(&perf_counter_mutex);
				PUT_UINT(&msgData.msg[0], total_recd);
				PUT_UINT(&msgData.msg[4], prevsec_recd);
				PUT_UINT(&msgData.msg[8], total_sent);
				PUT_UINT(&msgData.msg[12], prevsec_sent);
				pthread_mutex_unlock(&perf_counter_mutex);
				msgData.Send(CurSub->data->getDestination(),16);
				MessageSent(&msgData);
			}
		}
		CurSub = CurSub->next;
	}
	pthread_mutex_unlock(&subscription_mutex);
	debug_f(4, "Finished looking for  notification subscriptions.\n");
}

/*
	Description:
		Handling of the SDMReady message

	Input:
		buf  - the message in an array
		size  -  the length of the message in bytes
		ipaddr - the ip address in dot notation

	Output:
		None

	Changed:
		None

*/
void Ready(char *buf, int size, const SDMComponent_ID& SenderId)	//Send a reply that the DM is ready
{
	unsigned short usPort = 0;
	SDMReady msgReady;
	SDMComponent_ID id;

	//Get ip address where message sent from
	if(msgReady.Unmarshal(buf) <0)
	{
		printf("Invalid SDMReady message!\n\n");
		return;
	}
	MessageReceived(&msgReady);

	usPort = msgReady.destination.getPort();  //Save the port to communicate on

	if (debug >= 1)
	  {
	    char strRequesterId[64];
	    msgReady.destination.IDToString(strRequesterId, sizeof(strRequesterId));
	    debug_f(1, "SDMReady from %s\n", strRequesterId);
	  }

	if(usPort == PORT_TM)
	{
		TaskManager = msgReady.destination;
		debug_f(1,"Setting TM ip address to 0x%lx\n",TaskManager.getAddress());


#ifdef PNP_BACKUP
		xTEDSLibraryListNode* node = xTEDSList.head;
      while(node != NULL)
      {
         node->data->inUse->Wait();
         if (strncmp(node->data->getName(), "TaskManager", 11) == 0)
         {
             printf("Updating the registered TM Address to 0x%lx\n", TaskManager.getAddress());
             node->data->setAddress(TaskManager);
         }
         node->data->inUse->Signal();
         node = node->next;
      }

     backupDMList.SendMessageToAll(msgReady);
     printf("Forwarding the TM address to backups\n");
     //backupDMList.PrintList();
#endif
	}
	id.setAddress(msgReady.destination.getAddress());
	id.setPort(usPort);
	msgReady.destination.setAddress(DataManager.getAddress());
	msgReady.destination.setPort(PORT_DM);
	if(usPort == PORT_DM_ELECTION)
	{
		if(TaskManager.getPort() != 0)
		{
			msgReady.source = TaskManager;
		}
		//msgReady.Send(id);
#ifdef PNP_BACKUP
		SDMComponent_ID BackupId = id;
		BackupId.setPort(PORT_DM_ELECTION);

		//Check if new backup DM and store the ip
		pthread_mutex_lock(&dm_list_mutex);
		bool NewAdd = backupDMList.AddIfNew(BackupId);
		pthread_mutex_unlock(&dm_list_mutex);

		//If new ip send all known xTEDS
		if(NewAdd)
		{
		    debug_f(3, "Backup added to the Backup DM List\n");
			SDMxTEDS msgxTEDS;

			xTEDSLibraryListNode* node = xTEDSList.head;
			while(node!=NULL)
			{
				// Fill the xTEDS info into the message
				node->data->inUse->Wait();
				msgxTEDS.source = node->data->getComponentID();
				PID = node->data->getPid();
				msgxTEDS.setPID();
				msgxTEDS.active = node->data->getActive();
				strncpy(msgxTEDS.xTEDS,node->data->getxTEDS(), sizeof(msgxTEDS.xTEDS));
				if(node->data->getSPANode() != NULL)
					strcpy(msgxTEDS.SPA_node,node->data->getSPANode());
				node->data->inUse->Signal();

				// Send the message
				pthread_mutex_lock(&dm_list_mutex);
				backupDMList.SendMessageTo(BackupId, msgxTEDS);
				pthread_mutex_unlock(&dm_list_mutex);

				node = node->next;
			}
		}
#endif
	}
	else
		msgReady.Send(id);
	MessageSent(&msgReady);
}

/*
	Description:
		Handling publishing the services that the DM provides.  See the DM xTEDS

	Input:
		ipaddr - the ip address in dot notation
		port - the port of the consumer
		sID - generally the sensorID of the device in question
		DataReplyId - an ID for the message ID
		seq_num - a number unique to the application that requested the service for identify which response belongs to what request

	Output:
		None

	Changed:
		None

*/
void ServicePublish(const SDMComponent_ID& RequesterId, unsigned int sID, const SDMMessage_ID& DataReplyId, int seq_num)
{
	xTEDSLibraryListNode* node;
	SDMData msgData;
	SDMComponent_ID tempID;

	msgData.source = DataManager;
	msgData.msg_id = DataReplyId;
	msgData.seq_num = seq_num;

	if(DataReplyId == RPLY_CONVERTED_DEVICE_NAME)
	{
		node = MatchSID(sID);
		if(node == NULL)
		{
 			printf("Device name not found for the given SensorID.\n");
			return;
		}

		PUT_ULONG(&msgData.msg[0],sID);
		strncpy(&msgData.msg[4],node->data->getName(),strlen(node->data->getName())+1);
		msgData.Send(RequesterId,85);
		MessageSent(&msgData);
		node->data->inUse->Signal();
		return;
	}
	else if(DataReplyId == RPLY_CONVERTED_SPANODE)	// Convert a Sensor ID to a SPANodePath
	{
		node = MatchSID(sID);
		if(node == NULL)
		{
 			printf("Physical location information not found for the given SensorID\n");
			return;
		}
		//
		// Fill the Sensor ID and the SPANodePath
		PUT_UINT(msgData.msg, sID);
		strncpy(msgData.msg + sizeof(unsigned long), node->data->getSPANode(), 79);
		msgData.msg[sizeof(unsigned long) + 79] = '\0';
		node->data->inUse->Signal();

		msgData.Send(RequesterId,84);
		MessageSent(&msgData);
		return;
	}
	else if(DataReplyId == RPLY_CONVERTED_IP)
	{
		node = MatchSID(sID);
		if(node==NULL)
		{
			printf("IP address and port not found for the given SensorID.\n");
			return;
		}

      unsigned long temp = node->data->getSensorID();
      unsigned short tempPort = node->data->getTargetPort();
		PUT_ULONG(msgData.msg, temp);
		temp = node->data->getAddress();
		PUT_ULONG(msgData.msg+4, temp);
		PUT_USHORT(msgData.msg+8,tempPort);
		msgData.Send(RequesterId,10);
		MessageSent(&msgData);
		node->data->inUse->Signal();
		return;

	}
	else if(DataReplyId == RPLY_RETURN_COMP_KEY)
	{
		const char* NOKEY = "NOKEY";
		debug_f(3,"Working on converting componentID to componentKey\n");

		node = MatchSID(sID);
		if(node==NULL)
		{
			printf("ComponentKey not found for the given SensorID.\n");
			return;
		}
		tempID.Marshal(msgData.msg,0);
		if(node->data->getComponentKey()!=NULL)
			strcpy(msgData.msg,node->data->getComponentKey());
		else
			strcpy(msgData.msg,NOKEY);
		msgData.Send(RequesterId,129);
		MessageSent(&msgData);
		node->data->inUse->Signal();
		return;
	}
	else if(DataReplyId == RPLY_ERRORS)
	{
		PUT_ULONG(msgData.msg,droppedxTEDS);
		PUT_ULONG(msgData.msg+4,droppedCancelxTEDS);
		msgData.Send(RequesterId,8);
		MessageSent(&msgData);
		return;
	}
	else
	{
		node = xTEDSList.head;
		while(node!=NULL)
		{
			node->data->inUse->Wait();
			if(node->data->getAvailable() == false)
			{
				if (node->data->getComponentID().getAddress() == RequesterId.getAddress())
				{
					if(sID == node->data->getPid()) //sID is actually the pid in the case of reply ID 9
					{
						long pID = node->data->getSensorID();
						PUT_ULONG(msgData.msg,sID);
						PUT_LONG(&msgData.msg[4],pID);
						msgData.Send(RequesterId,8);
						MessageSent(&msgData);
						debug_f(1,"Sending sensor ID of %ld for PID %u to 0x%lx at port %hu\n", pID, sID, RequesterId.getAddress(), RequesterId.getPort());
						node->data->inUse->Signal();
						return;
					}
				}
			}
			node->data->inUse->Signal();
			node = node->next;
		}
			printf("Unable to identify PID %u that sensor ID is wanted for\n",sID);
	}
}

/*
	Description:
		Handling of the SDMTat message

	Input:
		buf  - the message in an array
		size  -  the length of the message in bytes
		ipaddr - the ip address in dot notation

	Output:
		None

	Changed:
		None

*/
void TAT(char *buf, int size, const SDMComponent_ID& SenderId)
{
	SDMTat tat;
	int n = 0, i = 0;
	const unsigned int S_SIZE = xsize;
	unsigned long sentips[S_SIZE];
	int sentcount = 0;
	xTEDSLibraryListNode* node;
	SDMComponent_ID id;

	if(tat.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMTAT message!\n\n");
		return;
	}
	MessageReceived(&tat);

	debug_f(1,"SDMTat seconds: %ld useconds: %ld sensorID: %ld\n",tat.seconds,tat.useconds,tat.destination.getSensorID());

	if(tat.destination.getSensorID() == 0)
	{
		//Send tat to each SM
		node = xTEDSList.head;
		while(node!=NULL)
		{
			node->data->inUse->Wait();
			if(node->data->getHub() == 1)
			{
				for(i = 0; i < sentcount; i++)
				{
					if(sentips[i] == node->data->getAddress())
					{
						node->data->inUse->Signal();
						break;
					}
				}
				if(i == sentcount)
				{
					sentips[sentcount] = node->data->getAddress();
					id.setAddress(node->data->getAddress());
					id.setPort(PORT_SM);
					tat.Send(id);
					MessageSent(&tat);
					sentcount++;
					debug_f(1,"Sent tat of %ld %ld %ld to 0x%lx at port %hu\n", tat.seconds, tat.useconds, tat.destination.getSensorID(), node->data->getAddress(),PORT_SM);
				}
			}
			node->data->inUse->Signal();
			node = node->next;
		}
		if(sentcount == 0)
			printf("No SM found, tat could not be sent to any SM's\n");
	}
	else
	{
		//Send tat to SM that controls the sensor
		node = xTEDSList.head;
		while(node!=NULL)	//Determine which xTED this Consume corresponds to
		{
			node->data->inUse->Wait();
			if(node->data->getAvailable() != true)
			{
				if(tat.destination.getSensorID() == node->data->getSensorID())
				{
					if(node->data->getActive() == true)
					{
						if(node->data->getHub() == 1)
						{
							debug_f(4,"Found matching ID in %d\n",n);
							break;
						}
						else
						{
							printf("SensorID: %ld does not correspond to a sensor\n\n",tat.destination.getSensorID());
							node->data->inUse->Signal();
							return;
						}
					}
				}
			}
			node->data->inUse->Signal();
			node = node->next;
		}
		if(node == NULL)
		{
			printf("No matching sensorID found, tat can not be sent\n\n");
			return;
		}
		tat.Send(node->data->getComponentID());
		MessageSent(&tat);
		debug_f(1,"Sent tat of %ld %ld %ld to 0x%lx at port %hu\n", tat.seconds, tat.useconds, tat.destination.getSensorID(), node->data->getAddress(), PORT_SM);
		node->data->inUse->Signal();
	}
}

/*
	Description:
		Intialization of the pipes for passing messages through

	Input:
		None

	Output:
		None

	Changed:
		None

*/
void PipeInit()
{
#ifndef __VXWORKS__
	if(pipe(alert) < 0)
	{
		if(debug >= 2)
			fprintf (stderr, "pipe error\n"); _exit(0);         // IPC for Consume(),Service(),Cancel()
	}
#else
	if(pipeDevCreate("/pipe/alert", 10, 10) != 0)
	{
		if(debug >= 1)
			fprintf (stderr, "Pipe error\n");
	}
	alertPipe = open ("/pipe/alert", O_RDWR);
#endif
}

/*
	Description:
		Handling messages passed through the pipe

	Input:
		arg - a pointer that is not used

	Output:
		None

	Changed:
		None

*/
void* ChildFunctionCallProcess(void* arg)
{
	int size = 0;
	char buf[BUFSIZE];	//Buffer for recieving incoming messages
	char len[8];
	int BytesSoFar = 0;
	SDMComponent_ID SenderId;
	char SenderIdBuf[10];
	chdir("./Callprofile");

	debug_f(3,"Child function call process running ...\n");

	//
	//  Set up the IPC channel via TCP
	//
	// Open a TCP server socket and begin listening for connections
	int TCPSock;			// TCP listen socket
	if ((TCPSock = TCPpassive(PORT_DM_TEMP, 1)) == IP_SOCK_INVALID)
	{
		printf("Error - ChildFunctionCallProcess::Could not bind port %hu\n",PORT_DM_TEMP);
		return NULL;
	}
	sockaddr_in SIn;
	int MsgRxSock = IP_SOCK_INVALID;			// Socket for receiving messages from UDPListenerProcess
	bool Connected = false;

	// We should only receive one connection request, but just to be safe, limit the address...
	while (!Connected)
	{
 		MsgRxSock = TCPaccept(TCPSock, &SIn);
		if (SIn.sin_addr.s_addr == Address_DM || SIn.sin_addr.s_addr == L_LOCAL_HOST || Address_DM == L_LOCAL_HOST)
			Connected = true;
	}
	TCPclose(TCPSock);
	//
	// Connection up, wait for messages
	int iStatus;
	bool bError = false;
	while(1)
	{
#ifndef __VXWORKS__
		while(read(alert[0], len, 1) > 0)
#else
		while(read(alertPipe, len, 1) > 0)
#endif
		{
			iStatus = 0;
			bError = false;
			BytesSoFar = 0;
			// Receive the Sender component ID
			while (BytesSoFar < 10)
			{
				iStatus = TCPrecv(MsgRxSock, SenderIdBuf + BytesSoFar, sizeof(SenderIdBuf) - BytesSoFar);
				if (iStatus < -1)
				{
					perror("TCPrecv");
					bError = true;
					break;
				}
				else if (iStatus == 0)
				{
					bError = true;
					break;
				}
				else
					BytesSoFar += iStatus;
			}
			if (bError)
				continue;
			SenderId.Unmarshal(SenderIdBuf, 0);
			//
			// Get the message size
			debug_f(4,"Receiving size: ");
			BytesSoFar = 0;
			while (BytesSoFar < 4)
			{
				iStatus = TCPrecv(MsgRxSock, &size + BytesSoFar, 4 - BytesSoFar); //Get the size from pipe
				if (iStatus < -1)
				{
					perror("TCPrecv");
					bError = true;
					break;
				}
				else if (iStatus == 0)
				{
					bError = true;
					break;
				}
				else
					BytesSoFar += iStatus;
			}
			if (bError)
				continue;
			debug_f(4, "%d\n",size);
			//
			// Get the rest of the message
			BytesSoFar = 0;
			while (BytesSoFar < size)
			{
				iStatus = TCPrecv(MsgRxSock, &buf + BytesSoFar, size - BytesSoFar);
				if (iStatus < -1)
				{
					perror("TCPrecv");
					bError = true;
					break;
				}
				else if (iStatus == 0)
				{
					bError = true;
					break;
				}
				else
					BytesSoFar += iStatus;
			}
			if (bError)
				continue;
			//
			// Check the command message byte and send to correct function
			switch(buf[0])
			{
			case SDM_Consume:
				Consume(buf, size, SenderId);
				break;
			case SDM_Cancel:
				Cancel(buf, size, SenderId);
				break;
			case SDM_ReqReg:
				ReqReg(buf, size, -1, SenderId, MOD_NOT_APPLICABLE);
				break;
			case SDM_Service:
				Service(buf, size, SenderId);
				break;
			case SDM_Serreqst:
				Serreqst(buf, size, SenderId);
				break;
			case SDM_ReqxTEDS:
				ReqxTEDS(buf, size, SenderId);
				break;
			case SDM_Command:
				Command(buf, size, SenderId);
				break;
			case SDM_Ready:
				Ready(buf, size, SenderId);
				break;
			case SDM_Tat:
				TAT(buf, size, SenderId);
				break;
			case SDM_Search:
				Search(buf, size, SenderId, -1);
				break;
			case SDM_VarReq:
				VarReq(buf, size, SenderId, -1);
				break;
			case SDM_TaskError:
				TaskError(buf, size, SenderId);
				break;
            case SDM_Heartbeat:
#ifdef PNP_BACKUP
                //debug_f(1, "command received: Task Error\n");
                QueueHeartbeat(buf, size);
                break;
#endif
			default:
				debug_f(0,"command received: Invalid command recieved is 0x%x\n",buf[0]);
				break;
			}
		}
	}
	exit(0);
}

/*
	Description:
		Prints the active and inactive xTEDS that are registered

	Input:
		None

	Output:
		None

	Changed:
		None

*/
void PrintxTEDS()
{
	int p=0;
	int ncount = 1;
	xTEDSLibraryListNode* node;
	char* ted = NULL;

	if(xTEDSList.head != NULL)	//If any xTEDS are still registered, should always be true due to DM never deregistering its xTEDS
	{
		/*Print publish names*/
		if(debug >= 1)
		{
			printf("Publish names are ");
			node = xTEDSList.head;
			while(node!=NULL)
			{
				node->data->inUse->Wait();
				if(node->data->getAvailable() == false)
				{
					if(node->data->getName() != NULL)
					{
						if(p == 0)
						{
							printf("%s",node->data->xtedsTree->getDeviceName());
							p = 1;
						}
						else
						{
							if(node->data->getActive() == true)
								printf(", %s",node->data->getName());
							else
								printf(", *%s",node->data->getName());
						}
					}
				}
				node->data->inUse->Signal();
				node = node->next;
			}
		}

		/*Print xTEDS*/
		if(debug >= 5)
		{
			printf("xTEDs are:\n");
			node = xTEDSList.head;
			while(node!=NULL)
			{
				node->data->inUse->Wait();
				if(node->data->getAvailable() == false)
				{
					if(node->data->getxTEDS() != NULL)
					{
						if(ted!=NULL) free(ted);
						ted = strdup(node->data->getxTEDS());
						if(node->data->getActive() == true)
							printf("%d.  %s",ncount,ted);
						else
							printf("%d.* %s",ncount,ted);
						ncount++;
						if(ted[strlen(ted)-1] != '\n')
							printf("\n");
					}
				}
				node->data->inUse->Signal();
				node = node->next;
			}
		}
	}
	if(ted != NULL) free(ted);
	debug_f(1,"\n\n");
}

/*
	Description:
		Check to see if the xTEDS is already registered

	Input:
		sensor - the name of the sensor from the xTEDS
		buf  - the message in an array
		port - the port device is using to communicate on
		addr - the ip addr in dot notation
		type - 0 for application, 1 for device, 2 for robohub
		spot - a reference index for the node that contains the xTEDS of the device if already registered

	Output:
		xTEDSLibraryListNode* - a pointer to the xTEDSLibraryListNode for the xTEDS

	Changed:
		None

*/
xTEDSLibraryListNode* AlreadyRegistered(char* sensor, const char* buf, unsigned short port, SDMComponent_ID& idAddr, int type, int& spot)
{
	int temp = 0,count = 0;
	long ID;
	long tempID = 0;
	xTEDSLibraryListNode* node;
	SDMxTEDS ted;

	ted.Unmarshal(buf);
	node = xTEDSList.head;
	while(node!=NULL)	//Check to see if the xted is registered already as inactive
	{
		node->data->inUse->Wait();
		if(node->data->getAvailable() == false)
		{
			if(strncmp(node->data->getName(),sensor,strlen(sensor)) == 0)
			{
				if(node->data->getActive() == false)
				{
					node->data->setActive(true);
					node->data->setAddress(idAddr);

					ID = ted.source.getSensorID();
					node->data->setTargetPort(ted.source.getPort());
					node->data->setPid(ted.getPID());

					node->data->setHub(type);
					if(strncmp(node->data->getName(),"RoboHub",7) == 0 || strncmp(node->data->getName(),"RobustHub",9) == 0)
					{
						debug_f(3,"Robust Hub being registered\n");
						node->data->setHub(ROBOHUB);
					}

					//Create SensorID
					debug_f(4,"ID is %ld\n",ID);
					ID &= 0x0000FFFF;	//Create the unique ID
					//if(ID == 0) // cbj -- Removed, ASIMs don't set this byte when the need to re-register, I don't know
						//node->data->setActive(false); // when this has ever been used, the removal should be OK.
					debug_f(4,"ID after the and with 0x000000FF is %ld\n",ID);
					temp = count<<16;
					debug_f(4,"spot %d shifted by 16 is %hd\n",count,temp);
					ID |= (count<<16);
					debug_f(4,"ID after or is %ld\n",ID);
					node->data->setSensorID(ID);
					debug_f(1,"SensorID for %s will be %ld\n",sensor,node->data->getSensorID());
					spot = count;

					node->data->inUse->Signal();
					return node;
				}
				else if(port == node->data->getTargetPort())
				{
					if (idAddr.getAddress() == node->data->getAddress())
					{
						ID = ted.source.getSensorID(); //Copy the id from buf into local variable
						ID &= 0x0000FFFF;	//Create the unique ID
						tempID = node->data->getSensorID();	//Get sensor ID DM created
						tempID &= 0x0000FFFF;	//Change DM sensor ID to ID assigned by SM or application
						if(ID == tempID && port != PORT_TM)
						{
							printf("Device already registered\n\n");
							spot = -1;
							node->data->inUse->Signal();
							return node;
						}
						if(port == PORT_TM)
						{
							node->data->inUse->Signal();
							spot = count;
							return node;
						}
					}
				}
			}
		}
		node->data->inUse->Signal();
		node = node->next;
		count++;
	}
	debug_f(5,"Unable to find a previously registered xTED\n");
	return NULL;
}

/*
	Description:
		Handling of the SDMSearch message

	Input:
		sensor - the name of the sensor from the xTEDS
		spot - a reference index for the node the xTEDS has been stored in
		addr - the ip address of the device in dot notation
		buf  - the message in an array
		type - 0 for application, 1 for device, 2 for robohub

	Output:
		xTEDSLibraryListNode* - a pointer to the xTEDSLibraryListNode the xTEDS has been stored in

	Changed:
		None

*/
xTEDSLibraryListNode* StoreInfo(char* sensor, int &spot, const SDMComponent_ID& idAddr, const char* buf, int type)
{
	unsigned long ID;
	int count = 0;
	xTEDSLibraryListNode* node = NULL;
	xTEDSLibraryListNode* iterator;
	SDMxTEDS ted;
	int active;
	char SPAHub[128];

	if(spot > 0 || xTEDSList.head != NULL)
	{
		iterator = xTEDSList.head;
		do
		{
			count++;
			iterator = iterator->next;
		}while(iterator!=NULL && count!=spot && iterator->data->getAvailable()!=true);
		node = iterator;
	}
	if(node == NULL)
	{
		xTEDSLibrary* lib;
		lib = new xTEDSLibrary();
		xTEDSList.addLibrary(lib);
		node = xTEDSList.tail;
	}

	ted.Unmarshal(buf);
	node->data->inUse->Wait();
	node->data->setAddress(idAddr);
	node->data->setAvailable(false);

	ID = ted.source.getSensorID();                 //Copy the id from buf into local variable
	node->data->setTargetPort(ted.source.getPort());	//Save the port to communicate on
	node->data->setPid(ted.getPID());
	node->data->setSPANode(ted.SPA_node);

	node->data->setHub(type);
	if(node->data->getHub() == ROBOHUB)
	{
		if(GetSPAHub(ted.xTEDS,SPAHub,debug)==0)
			node->data->setSPAHub(SPAHub);
	}
	debug_f(4,"Type of device is %d\n",node->data->getHub());
	//Create SensorID
	debug_f(4,"ID is %ld\n",ID);
	ID &= 0x000000FF;	//Create the unique ID
	active = ted.active;
	if(active == 0)
		node->data->setActive(false);
	else
		node->data->setActive(true);
	debug_f(4,"ID after the and with 0x000000FF is %ld\n",ID);
	debug_f(4,"spot %hd shifted by 16 is %hd\n",count,(count<<16));
	ID |= (count<<16);
	debug_f(4,"ID after or is %ld\n",ID);
	node->data->setSensorID(ID);
	debug_f(1,"SensorID for %s will be %ld\n",sensor,node->data->getSensorID());
	debug_f(4,"SM connected from 0x%lx on port %hu\n",node->data->getAddress(),node->data->getTargetPort());
	spot = count;
	return node;
}

/*
	Description:
		Handling of sending a SDMPostTask message to the Task Manager

	Input:
		node - a pointer to the xTEDSLibraryList node in question

	Output:
		None

	Changed:
		None

*/
void PostTask(xTEDSLibraryListNode* node)
{
	SDMPostTask task;
	short resource;

	if(TaskManager.getAddress()==0)
	{
		printf("Unable to post task because no TM is registered!!!\n");
		return;
	}
	//This is a first test of posting Tasks and will be updated to get info from xTED for applications
#ifdef __uClinux__
	resource = SDM_MICROBLAZE | SDM_MEM128 | SDM_LINUX26;
#elif WIN32
	resource = SDM_INTEL|SDM_MEM128|SDM_WIN32;
#else
	//
	// In the future, DM will probably have to hang on to a task's resource definitions
	// This won't work if there are heterogeneous processors being used
	resource = SDM_INTEL|SDM_MEM128|SDM_LINUX26;
#endif
	task.resources = resource;
	task.priority = 1;
	const char* name = node->data->getName();
	memcpy(task.filename,name,strlen(name)+1);
	debug_f(2,"Posting Task with resources of %d priority of %d and filename of %s\n",task.resources,task.priority,task.filename);
	task.Send();
	MessageSent(&task);
	debug_f(2,"Task Posted\n");
}

/*
 * Separate thread for signal handling.  This avoids a potential deadlock situation in which the ChildFunctionCallProcess function
 * is chosen to handle the SIGALRM signal after it has called pthread_mutex_lock(&subscrition_mutex), which is also called in the
 * signal handler.
 */
#ifndef WIN32
void* SigHandler(void *arg)
{
	sigset_t signal_set;
	int sig;
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGINT);
	sigaddset(&signal_set, SIGALRM);

	while (1)
	{
		sigwait(&signal_set, &sig);
		switch(sig)
		{
			case SIGINT:
				printf("Shutting down process\n");
				if ( udpSock != IP_SOCK_INVALID )
					UDPshutdown(udpSock);
				if ( tcpListenSock != IP_SOCK_INVALID )
					TCPshutdown(tcpListenSock);
				if ( tcpSock != IP_SOCK_INVALID )
					TCPshutdown(tcpSock);
				if ( MsgTxPushSock != IP_SOCK_INVALID )
					TCPshutdown(MsgTxPushSock);
#ifdef __VXWORKS__
				close(alertPipe);
				pipeDevDelete("/pipe/alert", true);
#endif
				exit(EXIT_SUCCESS);
				break;
			case SIGALRM:		//Publish performance counter message
				PublishNotification(0, NOTI_PERFORMANCE_COUNTERS);
				pthread_mutex_lock(&perf_counter_mutex);
				prevsec_recd = 0;
				prevsec_sent = 0;
				pthread_mutex_unlock(&perf_counter_mutex);
				break;
			default:
				printf("Signal: %i received\n", sig);
		}
	}
}
#endif
#ifdef WIN32
void SigHandler(int sig)
{
	switch (sig)
	{
		case SIGINT:
			printf("Shutting down process\n");
			if ( udpSock != 0 )
				UDPshutdown(udpSock);
			if ( tcpListenSock != 0 )
				TCPshutdown(tcpListenSock);
			if ( tcpSock != 0 )
				TCPshutdown(tcpSock);
			if ( MsgTxPushSock != 0 )
				TCPshutdown(MsgTxPushSock);
			exit(EXIT_SUCCESS);
		case SIGALRM:		//Publish performance counter message
			PublishNotification(0, NOTI_PERFORMANCE_COUNTERS);
			pthread_mutex_lock(&perf_counter_mutex);
			prevsec_recd = 0;
			prevsec_sent = 0;
			pthread_mutex_unlock(&perf_counter_mutex);
			break;
	}
}
#endif

//Function to increment performance counters and alert the log service of a message sent, making the code simpler, smaller, and more readable.
void MessageSent(SDMmessage *msg)
{
	pthread_mutex_lock(&perf_counter_mutex);
	total_sent++;
	prevsec_sent++;
	pthread_mutex_unlock(&perf_counter_mutex);

	pthread_mutex_lock(&log_service_mutex);
	if (!log_service.IsEmpty())
		log_service.MessageSent(msg);
	pthread_mutex_unlock(&log_service_mutex);

}

//Function to log, but not count, the messages received.  This makes the code simpler, smaller, and more readable.
void MessageReceived(SDMmessage *msg)
{
	pthread_mutex_lock(&log_service_mutex);
	if (!log_service.IsEmpty())
		log_service.MessageReceived(msg);
	pthread_mutex_unlock(&log_service_mutex);

}

/*
	Description:
		Find an xTEDS node that has a matching sensor ID

	Input:
		sID - the sensor ID to be matched

	Output:
		xTEDSLibarayListNode* - a pointer to the node that has the sID

	Changed:
		None

*/
xTEDSLibraryListNode* MatchSID(long sID)
{
	xTEDSLibraryListNode* node = xTEDSList.head;

	while(node!=NULL)
	{
		node->data->inUse->Wait();
		if(node->data->getActive() == true)
		{
			if((unsigned long)sID == node->data->getSensorID())
			{
				return node;	//Lock must be released in calling function
			}
		}
		node->data->inUse->Signal();
		node = node->next;
	}
	return NULL;
}

/*
	Description:
		Handling of sending xTEDS to the backup DM's

	Input:
		arg - a pointer to the xTEDSParameters

	Output:
		None

	Changed:
		None

*/
void* SendxTEDS(void* arg)
{
	int size;
	xTEDSParameters* param;
	SDMxTEDS xTEDS;
	SDMComponent_ID id;

	param = (xTEDSParameters*) arg;
	const char* buf = param->getBuffer();
	size = param->getSize();

	if(xTEDS.Unmarshal(buf) < 0)
	{
		printf("Error sending xTEDS to backup DM!\n\n");
		return 0;
	}
	id = param->getSenderAddress();
	id.setPort(PORT_DM_ELECTION);

	xTEDS.SendTo(id);
	return 0;
}
#ifdef BUILD_FOR_XTEDS_MERGING
/*
	Description:
		Handling of merging sdm.config file information with xTEDS

	Input:
		flag - a pointer to the node that is to be merged into after a robohub has registered
		update - Check to see if an unmerged xTEDS can be merged after the registration of a robohub
		ted - the SDMxTEDS message
		xTEDref - the index of the xTEDSLibraryListNode
		HubType - 0 for applications, 1 for devices, 2 for robohubs

	Output:
		Returns whether the merge was successful

	Changed:
		None

*/
bool MergexTEDS(xTEDSLibraryListNode* flag, bool update, SDMxTEDS& ted, int xTEDref, int HubType)
{
	char SPAHub[128] = "";
	char SPAPort[128] = "";
	char HubAddress[MAX_USB_PATH_SIZE] = "";
	char config[BUFSIZE];
	int temp = 0,count;
	xTEDSLibraryListNode* node;
	char oldxTEDS[3 * BUFSIZE];
	unsigned long SID = 0;
	bool active = false;

	//Be sure that we aren't dealing with an application
	if(HubType > APPLICATION)		// device or hub
	{
		//Get the string length of the USB path
		temp = strlen(ted.SPA_node);
		debug_f(4,"Length of USB address string is %d (USB address is %s)\n",temp,ted.SPA_node);

		//If the USB path contains something
		if(temp > 0)
		{
			debug_f(3,"USB address registered %s\n",ted.SPA_node);
			//If this is a device (not a robohub)
			if(HubType == DEVICE)
			{
				//Find this device's hub's address in the config file
				if (!FindDevicesHubPath(ted.SPA_node, HubAddress, sizeof(HubAddress), debug))
				{
					debug_f(1,"Could not find hub information for device at %s in configuration file.\n",ted.SPA_node);
					return false;
				}
				else
					debug_f(3,"Hub path found in configuration file is %s.\n",HubAddress);
			}
			temp = -1;
			if(HubType == ROBOHUB)
				temp = 0;
			count = 0;
			node = xTEDSList.head;
			while(node!=NULL)		// search through the registered items looking for the hub....
			{
				char* SavedPortAddress = NULL;
				node->data->inUse->Wait();
				//If this item is a hub and it is active
				if(node->data->getHub() == ROBOHUB && node->data->getActive() == true)
				{
					//Pull out its saved SavedHubHumber
					SavedPortAddress = node->data->getSPANode();
					debug_f(4,"Found hub with address %s in location %d trying to match %s\n", SavedPortAddress, count, HubAddress);

					//If the device being registered is connected to a previously registered RoboHub
					if(SavedPortAddress!=NULL && strcmp(SavedPortAddress, HubAddress) == 0)
					{
						debug_f(4,"Found matching hub in location %d\n",count);
						//Save its position in the xTEDS list
						temp = count;
						break;
					}
				}
				node->data->inUse->Signal();
				count++;
				node = node->next;
			}
			if(debug >= 3)
			{
				if(node==NULL)
					debug_f(3,"No matching hub found...\n");
				else
					debug_f(3,"ConvertToHubAxis returned %d which corresponds to %s\n",temp,node->data->getSPAHub());
			}
			//If this is a device whose Robohub has been found, or a Robohub being registered
			if(temp != -1)
			{
				if(HubType == DEVICE)
				{
					strcpy(SPAPort, ted.SPA_node);
					strcpy(SPAHub, HubAddress);
				}
				else	//ROBOHUB
					strcpy(SPAHub,ted.SPA_node);
				//See if the config information about the device exists in the configuration file we will try to merge it
				if(FindConfigInfo("Device",config,SPAHub,SPAPort,debug) != -1)
				{
					//It did exist, now attempt the merge
					if(MergeConfigxTED(ted.xTEDS,sizeof(ted.xTEDS),config,debug) == 0)
					{
						debug_f(3,"Merge succeeded new xTED is %s\n",ted.xTEDS);
						if(update == false)
						{
							if(node != NULL)
								node->data->inUse->Signal();
							return true;
						}
					}
					else
					{
						printf("Merge failed!!\n");
						update = false;
					}
				}
				//Device not found in the configuration file
				else
				{
					if(node != NULL)
						printf("Could not match any info to merge with for hub: %s and port: %s\n",node->data->getSPAHub(),ted.SPA_node);
					update = false;
				}
				if(node != NULL)
					node->data->inUse->Signal();
			}
			//A device's robohub has not been registered
			else
			{
				printf("Could not match device at %s with any Robust Hub.\n",ted.SPA_node);
				update = false;
			}
		}
		//Length of USB path was empty
		else
		{
			printf("USB address for device was not sent in the msg!\n");
			update = false;
		}
	}
	//
	//If the update succeded, alert any interested subscribers about the xTEDS
	if(update == true)
	{
		if(flag == NULL)
			return false;
		//Make change to xTEDS and parse
		const char* xTEDS = flag->data->getxTEDS();
		memcpy(oldxTEDS,xTEDS,strlen(xTEDS) + 1);

		//If parse fails reparse old xTEDS and send ack with error
		if(flag->data->setxTEDS(ted.xTEDS) == false)
		{
			if(flag->data->setxTEDS(oldxTEDS) == false)
			{
				printf("Data Manager has been corrupted!!!!\n");
			}
			else
				printf("Reverting back to the old xTEDS due to the merge corrupting the xTEDS.\n");
		}
		else
		{
			flag->data->inUse->Wait();
			active = flag->data->getActive();
			SID = flag->data->getSensorID();
			flag->data->inUse->Signal();

			debug_f(4,"Checking for any subscriptions\n");
			if (active)
			{
				PublishNotification(SID, NOTI_XTEDS_MODIFICATION);
				PublishNotification(SID, NOTI_REGISTRATION_CHANGE, UPDATE_MODIFICATION);
				PublishxTEDSModificationSubscription(SID, SEARCH_REPLY, MOD_NOT_APPLICABLE, xTEDref);
				PublishxTEDSModificationSubscription(SID, REQ_REG_FUTURE, MOD_NOT_APPLICABLE, xTEDref);
				PublishxTEDSModificationSubscription(SID, VAR_REQ_REPLY, MOD_NOT_APPLICABLE, xTEDref);
			}
		}
	}
	return update;
}
#endif	// #ifdef BUILD_FOR_XTEDS_MERGING
/*
	Description:
		Handling of SDMVarReq messages

	Input:
		buf - a pointer to the array containing the messasge
		size - the length of the message
		ipaddr - the ip address of the sender in dot notation
		xTEDref - the index of the xTEDSLibraryListNode

	Output:
		None

	Changed:
		None

*/
void VarReq(char* buf, int size, const SDMComponent_ID& SenderId, int xTEDref)
{
	xTEDSLibraryListNode* node;
	SDMVarReq msgVarRequest;
	SDMVarInfo msgVarInfo;
	SDMComponent_ID ReplyId;
	VariableDef* msg = NULL;
	VariableDef* cur_msg = NULL;
	int ref = -1;

	if(msgVarRequest.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMSearch message\n\n");
		return;
	}
	MessageReceived(&msgVarRequest);

	//
	// Validate the requester's port
	if(msgVarRequest.destination.getPort() == 0)
	{
		printf("Unable to complete SDMVarReq because of invalid destination port 0.\n");
		return;
	}
	// Set the destination address if not known
	ReplyId = msgVarRequest.destination;
	if(ReplyId.getAddress() == 0)
		ReplyId.setAddress(SenderId.getAddress());

	// Set the source address if not known
	if(msgVarRequest.source.getAddress() == L_LOCAL_HOST && Address_DM != L_LOCAL_HOST)
		msgVarRequest.source.setAddress(Address_DM);

	if (debug >= 1)
	  {
	    char strRequesterId[64];
	    char strTargetId[64];
	    msgVarRequest.source.IDToString(strTargetId, sizeof(strTargetId));
	    msgVarRequest.destination.IDToString(strRequesterId, sizeof(strRequesterId));
	    debug_f(1, "SDMVarReq from %s for %s variable: \"%s\"\n",
		    strRequesterId, strTargetId, msgVarRequest.variable);
	  }

	//
	// Add a subscription entry if entered
	if(msgVarRequest.reply != SDM_VARREQ_CURRENT)
	{
		char interface_id[8] = "";
		if(msgVarRequest.msg_id.getInterfaceMessagePair() != 0 || msgVarRequest.reply != SDM_VARREQ_CANCEL)
			sprintf(interface_id,"%d",msgVarRequest.msg_id.getInterfaceMessagePair());

		pthread_mutex_lock(&subscription_mutex);
		bool result = subscribers.addOrRemoveSubscription(msgVarRequest.reply, ReplyId, msgVarRequest.source, NULL, interface_id, msgVarRequest.variable, NULL, msgVarRequest.id, VAR_REQ_REPLY, debug);
		pthread_mutex_unlock(&subscription_mutex);
		if(result == false)
		{
			return;
		}
#ifdef PNP_BACKUP
		// Send the VarReq subscription to all backup DMs
		pthread_mutex_lock(&dm_list_mutex);
		msgVarRequest.destination = ReplyId;
		backupDMList.SendMessageToAll(msgVarRequest);
		pthread_mutex_unlock(&dm_list_mutex);
#endif
	}

	node = xTEDSList.head;
	if(xTEDref != -1)
	{
		int count = 0;
		while(xTEDref != count && node != NULL)
		{
			count++;
			node = node->next;
		}
		if(node == NULL)
		{
			printf("Unable to do VarReq due to invalid xTEDS reference\n");
			return;
		}
	}
	else
	{
		if(msgVarRequest.source.getAddress() != 0)
		{
			if(msgVarRequest.source.getPort() != 0)
			{
				if(msgVarRequest.source.getSensorID() != 0)
				{
					while(node!=NULL)
					{
						if(node->data->getComponentID()==msgVarRequest.source)
						{
							ref = 1;
							break;
						}
						node = node->next;
					}
				}
			}
		}
	}
	while(node!=NULL)
	{
		if(node->data->inUse->Wait() == 0)
		{
			if(node->data->getActive() == true)
			{
				debug_f(3,"Found matching xTEDS\n");

				msg = node->data->xtedsTree->getVarInfo(msgVarRequest.variable, msgVarRequest.msg_id);
				cur_msg = msg;
				while(cur_msg != NULL)
				{
					// Fill the reply message
					msgVarInfo.source = node->data->getComponentID();
					msgVarInfo.id = msgVarRequest.id;
					strcpy(msgVarInfo.var_xTEDS,cur_msg->GetDefinitions());
					strcpy(msgVarInfo.interface,cur_msg->GetInterfaceName());
					// Send the reply message
					msgVarInfo.Send(ReplyId);
					MessageSent(&msgVarInfo);
					if (debug >= 1)
					  {
					    char strTargetAddr[64];
					    msgVarRequest.destination.IDToString(strTargetAddr, sizeof(strTargetAddr));
					    debug_f(1, " Send SDMVarInfo to %s var_xTEDS: \"%s\"\n", strTargetAddr, msgVarInfo.var_xTEDS);
					  }

					cur_msg = cur_msg->next;
				}
				if(msg != NULL)
					delete msg;
			}
			node->data->inUse->Signal();
		}
		if(ref != -1)
			break;
		node = node->next;
	}
	// Send the SDMVarInfo stream terminator message
	msgVarInfo.SendEmpty(ReplyId);
	MessageSent(&msgVarInfo);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		  The below functions pertain to the Data Manager backup feature.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
/*
 * Certain operations should only be performed if we are currently the elected DM.  If Backup is not defined,
 * this function always returns true.
*/
bool IAmElected()
{
#ifndef PNP_BACKUP
	return true;
#else
	pthread_mutex_lock(&dm_list_mutex);
	bool bResult = g_bElectedDm;
	pthread_mutex_unlock(&dm_list_mutex);
	return bResult;
#endif
}



#ifdef PNP_BACKUP
//***************************************************************************************
//Description: Starts an election by callin the NMElection function.  If elected the DM
//  will listen on Port 3505 for any other election related messages.  If not elected,
//  the NonElected function is called and does not return until another election is
//  needed.
//Input: None
//Output: None
//***************************************************************************************
int RunBackupListener(void)
{
	SDMDMLeader templeader;
	bool started = true;
	char buf[BUFSIZE];
	bool sent = false;
	MessageManager mm;
	pthread_attr_t attr;
	pthread_t udpThread;
	//Start the Message Manager listening on the DM Election port for both UDP and TCP
	if(!mm.Async_Init_Both(PORT_DM_ELECTION))
	{
		printf("Message Manager not able to start up one of the listening interfaces!\n");
		return -1;
	}

	NMElection(&mm);  //Initiates the election process with the Network Manager

	while(1)
	{

		if(g_bElectedDm == true) //This is the elected DM
		{
			pthread_attr_init(&attr);
			pthread_attr_setstacksize(&attr,DM_STACK_SIZE);
			DataManager.setAddress(GetNodeAddress());
			if (0 != pthread_create(&udpThread,&attr,UdpListenerProcess,NULL))
			{
				perror("Could not start the UDP listener thread.\n");
				return -1;
			}
			pthread_detach(udpThread);

			while(1)
			{
				mm.BlockGetMessage(buf);
				switch(buf[0])
				{
					case SDM_DMLeader:
						templeader.Unmarshal(buf);
						debug_f(3,"Received SDMDMLeader message while running with running_flag of %x\n",templeader.running_flag);
						break;
					case SDM_Election:
						//Clean up because this Data Manager has a problem and a new DM is being elected.
						printf("Data Manager is shutting down.\n");
						return -1;
						break;
					case SDM_Ready:
						break;
					default:
						debug_f(1,"Unexpected message of type %c on PORT_DM_ELECTION\n",buf[0]);
						break;
				}
			}
		}
		else  //This is a backup DM
		{
			NonElected(&mm);   //Returns when new election is needed
		}
		NMElection(&mm);  //New Election Needed
	}
}

//***************************************************************************************
//Description: Sends an IMA message to the Network Manager and then calls the AmIPrimary
//  function which returns once the election has been resolved.  The HeartBeat thread is
//  then started up.
//Input: MessageManger* - A pointer to the message managaer used in the RunBackupListener
//  function.
//Output: Global g_bElectedDm variable is set
//***************************************************************************************
void NMElection(MessageManager* mm)
{
    if(spacewire)
    {
#ifdef SEND_IMA
        SendIMA(SdmImaDm, debug);
#endif
    }
    else
    {
#ifdef PNP_FAKE
        DMSendIMA();   //Sends fake IMA to fake NM
#endif
    }
	pthread_mutex_lock(&dm_list_mutex);
	g_bElectedDm = AmIPrimary(mm);  //Resolve Election
	pthread_mutex_unlock(&dm_list_mutex);

	pthread_t HeartbeatThread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr,DM_STACK_SIZE);
	pipe(dm_heartbeat_pipe);
	if (0 != pthread_create(&HeartbeatThread, &attr, &Heartbeat, NULL))
	{
		perror("Could not create the DM heartbeat thread.\n");
		return;
	}
}

//Temporary function to fake an IMA message to our fake NM
void DMSendIMA()
{
	SDMDMLeader leader;
	leader.source.setAddress(Address_DM);
	leader.source.setSensorID(1);
	leader.source.setPort(PORT_DM_ELECTION);
	leader.SendTo(NetworkManager);  //Send a pseudo IMA message to the Network Manager
	printf("Sending IMA Msg to the Network Manager...\n");
}


//***************************************************************************************
//Description: Waits until the timeOut expires and then checks the Data Manager address
//  selected by the Network Manager to see if it matches itself.  If the addresses match
//  this instance was selected as leader, otherwise as a backup Data Manager.
//Input: MessageManger* - A pointer to the message managaer used in the RunBackupListener
//  function.
//Output: bool - true if selected as leader, false otherwise
//***************************************************************************************
bool AmIPrimary(MessageManager* mm)
{
	SDMDMLeader response;
	char buf[BUFSIZE];
	long type;
	bool isPrimary = false;
	bool resolved = false;
	unsigned int timeOut = 5;

    unsigned long addr;
    sleep(timeOut);

    debug_f(3, "Election Timer Expired...\n");
    resolved = true;
#ifdef BUILD_FOR_PNPSAT
    struct hostent *he;
    he=gethostbyname("datamanager.spacewire");
    memcpy(&addr, he->h_addr, sizeof(addr));
#endif
#ifdef PNP_FAKE
    mm->BlockGetMessage(buf);
    if(buf[0] == SDM_DMLeader)
    {
        response.Unmarshal(buf);
        addr = response.source.getAddress();
    }
#endif
    DataManager.setAddress(GetNodeAddress(spacewire));
    debug_f(3, "Leader DM Address: 0x%lx My Address: 0x%lx\n", addr, DataManager.getAddress());
    if(addr == DataManager.getAddress())
    {
        isPrimary = true;
        debug_f(1, "Selected by NM as leader\n");
    }
    else
    {
        isPrimary = false;
        printf("Data Manager running as backup...\n");
        DataManager.setAddress(addr);
        DataManager.setPort(PORT_DM);
    }
	return isPrimary;
}


//***************************************************************************************
//Description: This function allows a backup data manager to alert the leader dm of its
//  location and contains the basic listen loop for a backup data manager.  It listens
//  for xTEDS registrations and cancelations, subscription type requests as well an an
//  SDMDMLeader message from the Heartbeat thread to alert that the leader has failed.
//Input: MessageManger* - A pointer to the message managaer used in the RunBackupListener
//  function.
//Output: None
//***************************************************************************************
void NonElected(MessageManager* mm)
{
	char buf[LARGE_MSG_BUFSIZE];
	SDMReady tempready;
	SDMReady backupAlert;
	SDMDMLeader DMleader;
	SDMElection election;
	SDMComponent_ID SenderId;
	SDMAck ack;
	struct sockaddr_in s;
	s.sin_port = 0;
	s.sin_addr.s_addr = 0;

	long length;
	pthread_attr_t attr;
	pthread_t xtedThread, CancelThread;
	SDMComHandle ComHandle;

	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr,DM_STACK_SIZE);
	debug_f(1, "Running as backup..\n");

	sleep(1);  //Make sure Leader DM listen thread is up and going
    backupAlert.destination.setAddress(GetNodeAddress(spacewire));
    backupAlert.destination.setPort(PORT_DM_ELECTION);
    backupAlert.SendTo(DataManager);
    debug_f(1, "Informing leader DM of my address: 0x%lx\n", backupAlert.destination.getAddress());


	bool electionNeeded = false;
	while(!electionNeeded)
	{
		while(mm->IsReady() == true)
		{
#ifdef WIN32
			mm->GetMsg(buf /* return */,length /* return */, ComHandle /* return */);
#else
			mm->GetMessage(buf /* return */,length /* return */, ComHandle /* return */);
#endif
			// WARNING: ComHandle must be "cleaned-up" by eventually issuing ComHandle->DoCleanup(),
			// either explicitly or by destroying an xTEDSParameters that uses it (only when TCP)

			SenderId.setAddress(s.sin_addr.s_addr);
			SenderId.setPort(ntohs(s.sin_port));
			switch(buf[0])
			{
				case SDM_DMLeader:
					DMleader.Unmarshal(buf);
					debug_f(3,"Received SDMDMLeader message while running with running_flag of %x\n",DMleader.running_flag);
					if(DMleader.running_flag == 'e')
					{
						electionNeeded = true;
					}
					break;
				case SDM_Election:
					break;
             case SDM_Heartbeat:
                 QueueHeartbeat(buf, length);
                 break;
				case SDM_Ready:
					tempready.Unmarshal(buf);
                    if(tempready.destination.getPort() != 0)
                    {
                        printf("Setting TM address to: 0x%lx port: %li\n", tempready.destination.getAddress(), tempready.destination.getPort());
                        TaskManager = tempready.destination;
                    }
					break;
				case SDM_xTEDS:
				{
					SDMxTEDS temp;
					temp.Unmarshal(buf);

                    xTEDSParameters* pParam = new xTEDSParameters(buf, length, SenderId, ComHandle);

                    // In backup mode, send the Ack immediately -- the registration thread doesn't need to
                    SendAckMessage(SDM_OK, false, COMPONENT_ID_INVALID, pParam->GetComHandle(), true);
                    // Cleanup the com handle because the below thread won't use it
                    pParam->ComCleanup();
					//if(temp.source.getPort() != PORT_DM)   //Backups shouldn't register the DM, avoids getting copies
					//{
						if (0 != pthread_create(&xtedThread, &attr, xTEDS, pParam))
							perror("Could not start the xTEDS registration thread.\n");
						pthread_detach(xtedThread);
					//}
				}
                    break;
				case SDM_CancelxTEDS:
				{
					xTEDSParameters* pParam = new xTEDSParameters(buf, length, SenderId, ComHandle);

					// In backup mode, send the Ack immediately -- the cancellation thread doesn't need to
					SendAckMessage(SDM_OK, false, COMPONENT_ID_INVALID, pParam->GetComHandle(), true);
					// Cleanup the com handle because the below thread won't use it
					pParam->ComCleanup();

					if (0 != pthread_create(&CancelThread, &attr, CancelxTEDS, pParam))
						perror("Could not start the cancel xTEDS thread.\n");
					pthread_detach(CancelThread);
					break;
				}
				case SDM_ReqReg:
					BackupModifyReqRegSubscription(buf);
					break;
				case SDM_Search:
					BackupModifySearchSubscription(buf);
					break;
				case SDM_VarReq:
					BackupModifyVarReqSubscription(buf);
					break;
             case SDM_TaskError:
                 BackupTaskError(buf);
                 break;
             case SDM_Consume:
                 BackupConsume(buf);
                 break;
				default:
					break;
			}
		}
	}
}


//***************************************************************************************
//Description: This thread handles the heartbeats for Data Managers and backup DMs.
//  Sends an SDMDMLeader message to the backup listener if the leader fails.
//Input: None
//Output: None
//***************************************************************************************
void* Heartbeat (void* arg)
{
	//printf("Starting the Heatbeat Thread....sleeping for 5 secs\n");
	sleep(5);								//Give the UDPListener thread a little time
	int num_sent = 0;		                  //counter for the number of messages sent
	int num_received = 0;		            //counter for the number of messages received

	struct pollfd dm_poll_fd;		         //poll struct
	dm_poll_fd.events = POLLIN | POLLPRI;
	dm_poll_fd.fd = dm_heartbeat_pipe[0];

	int poll_res = 0;
	char buf[BUFSIZE];		               //buffer for receiving message
	long length;			                  //Length of the heartbeat message being read
	bool electionNeeded = false;

	while (!electionNeeded)
	{
	   if (!g_bElectedDm)  //Backup DM
	   {
         bool mainIsAlive = true;
         SDMHeartbeat pulse;

         while (mainIsAlive)
         {
            // send heart beat
            SDMComponent_ID tempDM;
            tempDM = DataManager;
            tempDM.setPort(PORT_DM);
            debug_f(3, "Heartbeat Sent to DM at: %0xlx port: %li\n", tempDM.getAddress(), tempDM.getPort());
            pulse.source.setAddress(GetNodeAddress());
            pulse.source.setPort(PORT_DM_ELECTION);
            pulse.SendTo(tempDM);

            // poll for response, with a 5 second timeout
            poll_res = poll (&dm_poll_fd,1,5000);
            if (poll_res < 0)
            {
               perror ("Heartbeat: Poll error.\n");
            }
            else if (poll_res == 0) // when poll returns a zero it means there was a time out
            {
               printf("Data Manager not responding!! Sending IMA message\n");
               mainIsAlive = false;
            }
            else // clear the pipe by reading the message
            {
               // Read message length from the pipe
               read(dm_heartbeat_pipe[0], &length, sizeof(long));

               // Read message from pipe
               if (length > 0 && length < BUFSIZE)
               {
                  read(dm_heartbeat_pipe[0], buf, length);
                  debug_f(3, "Response heartbeat received from DM\n");
               }
            }

            if(poll_res != 0)  //Sleep only if no
            {
                sleep(5);	// only send heart beats every 5 seconds
            }
         }//end while
		electionNeeded = true;

		//Send a message to the Backup listener thread to let it know an election is needed
		SDMComponent_ID backupDM;
		backupDM.setAddress(GetNodeAddress());
		backupDM.setPort(PORT_DM_ELECTION);
		SDMDMLeader electionNeededMsg;
		electionNeededMsg.running_flag = 'e';
		electionNeededMsg.SendTo(backupDM);
      }
	  else   //Leader DM
	  {
	      while (1)
	      {
            //respond to any heart beats we have received while sleeping
            if ((poll_res=poll(&dm_poll_fd,1,1000)) < 0)
            {
               perror ("Heartbeat: Poll error.\n");
               break;
            }
            else if (poll_res > 0)
            {
                debug_f(3, "Heartbeat received from a backup DM\n");
               // Read message length from the pipe
               read(dm_heartbeat_pipe[0], &length, sizeof(long));

               // Read message from pipe
               if (length > 0 && length < BUFSIZE)
               {
                  read(dm_heartbeat_pipe[0], buf, length);

                  // send a reply

                  SDMHeartbeat temp;
                  temp.Unmarshal(buf);

                  SDMComponent_ID backup;
                  backup = temp.source;

                  temp.source = DataManager;
                  temp.SendTo(backup);
                  debug_f(3, "Sending heartbeat to backup at: 0x%lx port: %li\n", backup.getAddress(), backup.getPort());
               }
            }
		  } //while
	   }  //else
	}  //while
	return NULL;
}

void QueueHeartbeat(char buf[], long length)
{
   SDMHeartbeat temp;
   temp.Unmarshal(buf);

    //debug_f (3, "Queuing heartbeat for DM\n");
    /* Write the heartbeat message into the heartbeat pipe for the heartbeat thread */
    // First, write the length of the message
    if (write(dm_heartbeat_pipe[1], &length, sizeof(long)) < 0)
        printf("Could not write heartbeat length to pipe\n");
    // Write the actual message
    if (write(dm_heartbeat_pipe[1], buf, length) < 0)
        printf("Could not write heartbeat msg to pipe\n");
}


void BackupModifyReqRegSubscription(const char* msgBuf)
{
	SDMReqReg msgRequest;

	if (msgRequest.Unmarshal(msgBuf) < 0)
	{
		printf("Invalid SDMReqReg message received.\n");
		return ;
	}
	MessageReceived(&msgRequest);

	debug_f(1,"command: Request Registrations Subscription Entry -- reply: %d item_name: \"%s\" quallist: \"%s\"\n", msgRequest.reply, msgRequest.item_name, msgRequest.quallist);

	// If the reply style isn't SDM_REQREG_CURRENT (i.e. a subscription needs to be entered or cancelled)
	if(msgRequest.reply != SDM_REQREG_CURRENT)
	{
	    debug_f(2,"Backing up ReqReg Subscription...\n");
		pthread_mutex_lock(&subscription_mutex);
		subscribers.addOrRemoveSubscription(msgRequest.reply, msgRequest.destination, msgRequest.source, msgRequest.device, msgRequest.interface, msgRequest.item_name, msgRequest.quallist, msgRequest.id, REQ_REG_FUTURE, debug);
		pthread_mutex_unlock(&subscription_mutex);
	}
}

void BackupModifySearchSubscription(const char* msgBuf)
{
	SDMSearch msgSearch;

	if (msgSearch.Unmarshal(msgBuf) < 0)
	{
		printf("Invalid SDMSearch message received.\n");
		return ;
	}
	MessageReceived(&msgSearch);

	debug_f(1,"command: Search Subscription Entry -- reply: %d reg_expr: \"%s\"\n", msgSearch.reply, msgSearch.reg_expr);
	//
	// The reply is one of SDM_SEARCH_CURRENT_AND_FUTURE or SDM_SEARCH_CANCEL for this to match
	if(msgSearch.reply != SDM_SEARCH_CURRENT)
	{
	    debug_f(2,"Backing up Search Subscription...\n");
		pthread_mutex_lock(&subscription_mutex);
		subscribers.addOrRemoveSubscription(msgSearch.reply, msgSearch.destination, msgSearch.source, NULL, NULL, msgSearch.reg_expr, NULL, msgSearch.id, SEARCH_REPLY, debug);
		pthread_mutex_unlock(&subscription_mutex);
	}
}

void BackupModifyVarReqSubscription(const char* msgBuf)
{
	SDMVarReq msgVarRequest;

	if (msgVarRequest.Unmarshal(msgBuf) < 0)
	{
		printf("Invalid SDMVarReq message.\n");
		return ;
	}
	MessageReceived(&msgVarRequest);

	debug_f(1,"command: Variable Request Subscription Entry -- ID: %d variable: \"%s\"\n", msgVarRequest.id, msgVarRequest.variable);
	//
	// Add a subscription entry if entered
	if(msgVarRequest.reply != SDM_VARREQ_CURRENT)
	{
	    debug_f(2,"Backing up VarReqReg Subscription...\n");
		char interface_id[8] = "";
		if(msgVarRequest.msg_id.getInterfaceMessagePair() != 0 || msgVarRequest.reply != SDM_VARREQ_CANCEL)
			sprintf(interface_id,"%d",msgVarRequest.msg_id.getInterfaceMessagePair());

		pthread_mutex_lock(&subscription_mutex);
		subscribers.addOrRemoveSubscription(msgVarRequest.reply, msgVarRequest.destination, msgVarRequest.source, NULL, interface_id, msgVarRequest.variable, NULL, msgVarRequest.id, VAR_REQ_REPLY, debug);
		pthread_mutex_unlock(&subscription_mutex);
	}
}


void BackupTaskError(const char* msgBuf)
{
	SDMTaskError msgError;
    SDMComponent_ID RequesterId;
	if (msgError.Unmarshal(msgBuf) < 0)
	{
		printf("Invalid SDMTaskError message.\n");
		return ;
	}
	MessageReceived(&msgError);
    RequesterId = msgError.source;
	debug_f(1,"command: Task Error -- TaskName: \"%s\"\n", msgError.filename);

    debug_f(2,"Backing up SDMTaskError Message...\n");


//	xTEDSLibraryListNode* tempNode = xTEDSList.head;
//	int count = 0;
//	printf("***xTEDS Library List - size: %i***\n", xTEDSList.size());
//    while(tempNode!=NULL)
//	{
//        printf("xTEDSList[%i] PID: %li Error PID: %li Add: 0x%lx Error Add: 0x%lx Active: %i\n",
//            count, tempNode->data->getPid(), msgError.pid, tempNode->data->getAddress(), RequesterId.getAddress(), tempNode->data->getActive());
//		tempNode = tempNode->next;
//		count++;
//	}
//	printf("************************************\n");

	//
	// Start looking for the xTEDS to cancel
	xTEDSLibraryListNode* node = xTEDSList.head;
	int iRemoveRef = 0;
	while(node!=NULL)
	{
		node->data->inUse->Wait();
		if(node->data->getAvailable() == false)
		{
			if (RequesterId.getAddress() == node->data->getAddress())
			{
				if(node->data->getActive() == true)
				{
					if (node->data->getPid() == msgError.pid)
					{
						debug_f(2, "Sensor name to cancel is %s\n", node->data->getName());
						node->data->inUse->Signal();
						break;
					}
				}
			}
		}
		iRemoveRef++;
		node->data->inUse->Signal();
		node = node->next;
	}
	addLibrary.Wait();

	//
	// If the xTEDS couldn't be found, report error and exit
	if(node==NULL)
	{
		debug_f(1,"Could not identify the sensor to cancel.\n");
		addLibrary.Signal();
		return ;
	}

	node->data->inUse->Wait();
	node->data->setActive(false);
	// Keep this task posted so a ReqReg won't re-post it -- the PM will
	// immediately restart it
	node->data->setPosted(true);
	const unsigned long CancelSensorID = node->data->getSensorID();
	const SDMComponent_ID& CancelComponentId = node->data->getComponentID();
	node->data->inUse->Signal();
    //
	// Notify any devices about the cancelled application (ala SDMDeletesub)
	pthread_mutex_lock(&sensor_subs_mutex);
	g_SensorSubscriptions.DeleteAll(CancelComponentId, false);
	g_SensorSubscriptions.ProviderFinish(CancelComponentId);
	pthread_mutex_unlock(&sensor_subs_mutex);
	//
    //Remove any subscriptions that the failed task had
    pthread_mutex_lock(&subscription_mutex);
	subscribers.removeReqRegSubscription(SDM_REQREG_CANCEL, CancelComponentId, debug);
	pthread_mutex_unlock(&subscription_mutex);

	PrintxTEDS();

	addLibrary.Signal();

}

void BackupConsume(const char* msgBuf)
{
	SDMConsume msgConsumeRequest;
	SDMSubreqst msgSubRequest;
	xTEDSLibraryListNode* node;

	if(msgConsumeRequest.Unmarshal(msgBuf) < 0)
	{
		printf("Invalid SDMConsume message\n\n");
		return;
	}
	MessageReceived(&msgConsumeRequest);

	debug_f(1, "command: Consume -- port: %hu sensorID: %ld msgID: 0x%x \n",msgConsumeRequest.destination.getPort(),msgConsumeRequest.source.getSensorID(),msgConsumeRequest.msg_id.getInterfaceMessagePair());
	//
	// Get the node structure for the sensor requested




//    int count = 0;
//	for(xTEDSLibraryListNode* tempNode = xTEDSList.head; tempNode != NULL; tempNode = tempNode->next)
//	{
//        printf("Node[%i] SID: %ld\n", count, tempNode->data->getSensorID());
//	    count++;
//	}



	node = MatchSID(msgConsumeRequest.source.getSensorID());
	if(node==NULL)	//If node is NULL reaches xsize there is no matching sensorID and request is invalid
	{
		printf("Could not find the sensor requested!\n");
		return;
	}
	node->data->inUse->Signal();
	//
	// Put message together for the requested sensor
	msgSubRequest.destination = msgConsumeRequest.destination;
	msgSubRequest.source = msgConsumeRequest.source;
	msgSubRequest.msg_id = msgConsumeRequest.msg_id;
	//
	// If this is a request for the Data Manager, add a subscription table entry
	if(node->data->getSensorID() == DM_SENSOR_ID)
	{
		node->data->inUse->Signal();
		SDMComponent_ID SubscriberId;
		SubscriberId.setAddress(msgSubRequest.destination.getAddress());
		SubscriberId.setPort(msgSubRequest.destination.getPort());
		// Add a subscription entry
		Subscribe(SubscriberId, msgSubRequest.msg_id);
		debug_f(1,"\n");
		return;
	}
	// Get the fault ID for the requested message
	msgSubRequest.fault_id = node->data->xtedsTree->getNotificationFaultMsgID(msgConsumeRequest.msg_id);

	//
	// Increment the number of connections to the xTEDS
	int n = node->data->getConnections();
	n++;
	node->data->setConnections(n);
	node->data->inUse->Signal();
	//
	// If the sensor ID is filled in for the subscriber, it has an xTEDS and should be marked in
	// the DM's provider subscription list so the DM can send out cancellations upon any type of failure
	if (msgSubRequest.destination.getSensorID() != 0 && msgSubRequest.destination.getSensorID() != 1)
	{
	    debug_f(3, "Adding subscription to the g_SensorSubscriptions list...\n");
		pthread_mutex_lock(&sensor_subs_mutex);
		g_SensorSubscriptions.Add(msgSubRequest.source /*provider*/,
				msgSubRequest.destination/*subscriber*/, msgSubRequest.msg_id);
		pthread_mutex_unlock(&sensor_subs_mutex);
	}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////
//
//		  End Data Manager backup functions.
//
///////////////////////////////////////////////////////////////////////////////////////////////////////
#endif  //#ifdef PNP_BACKUP
