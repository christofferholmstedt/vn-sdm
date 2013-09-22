//*********************************************************************
//Task Manager Module of the SDM
//
//This source is compilable on both a Linux and a Win32 architecture.  Throughout, there are
//compile switches as #ifdef ... #endif which conditionally add or remove functionality.
//The most notable changes for compilation is the removal of a separate signal handling thread
//under Win32, because Windows has far fewer options for process signals than Linux.
//**********************************************************************
#include "tm.h"
#include <list>
#include <algorithm>

#ifndef WIN32
#  include <net/if.h>
#  include <netdb.h>
#endif

#ifdef __VXWORKS__
#include <hostLib.h>
#include <pipeDrv.h>
#endif

int debug;							               //level of debug info to output
bool spacewire = false;
unsigned char g_ucMode = 0;	    		   //meaning TBD

#ifdef __uClinux__
#define PM_HEARTBEAT_TIMEOUT (60000)
#else
#define PM_HEARTBEAT_TIMEOUT (5000)
#endif

#ifndef __VXWORKS__				   
int pm_heartbeat_pipe[2];  	
#else
int pm_heartbeat_pipe;
#endif

#ifdef PNP_BACKUP				   	//Pipe for heartbeat messages
int tm_main_heartbeat_pipe[2];  	//Pipe for heartbeat messages
int tm_back_heartbeat_pipe[2];  	//Pipe for heartbeat messages
#endif

#ifdef __uClinux__
	const char* FILE_SDM_TASK_LIST = "/mnt/flash/etc/SdmTaskList.config";
#else
	const char* FILE_SDM_TASK_LIST = "SdmTaskList.config";
#endif

TaskList taskList;						         //the list of pending tasks
SubscriptionManager subscriptions;				//a subscription manager to handle data publication
PMRecordList pmList;					            //a list of available process managers
MessageLogger log_service;

pthread_mutex_t pid_mutex = PTHREAD_MUTEX_INITIALIZER;
static long NextPID = 1;		               // next available taskid number

unsigned long Address_TM = ADDR_LOCAL_HOST;	//TM IP address
unsigned int total_recd = 0;		            //message counter for total received for life of tm
unsigned int prevsec_recd = 0;		         //message counter for total received previous second
unsigned int total_sent = 0;		            //message counter for total sent for life of tm
unsigned int prevsec_sent = 0;		         //message counter for total sent previous second

pthread_mutex_t subscription_mutex = PTHREAD_MUTEX_INITIALIZER;	      //a mutex for the subscription manager
pthread_mutex_t list_mutex = PTHREAD_MUTEX_INITIALIZER;			         //a mutex for the task list
pthread_mutex_t mode_mutex = PTHREAD_MUTEX_INITIALIZER;			         //a mutex for mode
pthread_mutex_t perf_counter_mutex = PTHREAD_MUTEX_INITIALIZER;	      //a mutex for performance counter access permission
pthread_mutex_t log_service_mutex = PTHREAD_MUTEX_INITIALIZER;	         //a mutex for the log service
pthread_mutex_t dm_found_mutex = PTHREAD_MUTEX_INITIALIZER;	            //a mutex for a dm_found variable
#ifdef WIN32
pthread_mutex_t code_transfer_mutex = PTHREAD_MUTEX_INITIALIZER;        //a mutex for code transfers under windows
#endif

#ifdef PNP_BACKUP
bool isBackup = true;                        // defaults to true, you aren't the main until the NM tells you so
list<SDMComponent_ID> Backup_TM_List;        // list of addresses for the backups
#endif
SDMComponent_ID mainTM;	                     // main TM IP address
bool use_nm = false;
SDMComponent_ID NetworkManager;
unsigned long NM_Address;

bool g_bSchedulerReset = false;
pthread_mutex_t g_mutexSchedulerReset = PTHREAD_MUTEX_INITIALIZER;


#ifdef BUILD_FOR_PNPSAT
//
// PowerController data items
bool g_bPowerControllerFound = false;
const unsigned short REQREG_POWER_CONTROLLER_ID = 10;
MessageManipulator g_mmEndpointReset;
SDMComponent_ID g_cidPowerController;
SDMMessage_ID g_midEndpointReset;
pthread_mutex_t g_mutexPowerControllerData = PTHREAD_MUTEX_INITIALIZER;

#endif // BUILD_FOR_PNPSAT

bool ackReceived = false;
bool registerReceived = false;
bool idReceived = false;


bool dm_found = false;						      //determines whether the dm has been found
PMRecordList pending_pms;					      //vector of pending PM registrations
#define THREAD_STACK_SIZE	256000
int main(int argc,char** argv)
{
   SDM_TimeInit();
	pthread_t ListenerThread;
	pthread_t SchedulerThread;
	pthread_t SigHandlerThread;
#ifdef PNP_BACKUP
	pthread_t TMHeartbeatThread;
#endif
	pthread_t PMHeartbeatThread;
	bool DM_set = false;
	bool bDoInitialStartup = true;


#ifndef __VXWORKS__
	if((Address_TM = GetNodeAddress()) == 0)
#else
	char hostName[50];
	int hostNameLength = 50;	
	gethostname(hostName, hostNameLength);
	if((Address_TM = hostGetByName(hostName)) == 0)
#endif
	{
		printf("Unable to get the TM's IP address, using localhost instead.\n");
		Address_TM = ADDR_LOCAL_HOST;
	}
	else
	{
		debug_f(3, "Task Manager address is 0x%lx\n",Address_TM);
	}

	// Set the Task Manager's node address
	TaskManager.setAddress(Address_TM);
	TaskManager.setPort(PORT_TM);

	// parse command line options
	while(1)
	{
#ifndef __VXWORKS__
		static struct option long_options[] = {
			{"dm",1,0,'d'},
			{"nm",1,0,'n'},
			{"help",0,0,'h'},
			{"debug",1,0,'g'},
			{"spacewire",1,0,'s'},
			{"faulted",0,0,'f'},
			{"config",0,0,'c'},
			{0,0,0,0} };
		int option_index;
		int option = getopt_long(argc,argv,"d:n:hg:s:fc:", long_options, &option_index);
#else
		int option = getopt(argc,argv,"d:n:hg:s:fc:");
#endif
		if(option==-1)
			break; // no more options
		switch(option)
		{
			case 'h':
				printf("Usage: tm [options]\n");
				printf("Options:\n");
				printf("--dm=<addr> -d<addr>\t\t\tSet IP address of Data Manager\n\t\t\t\t\t<addr> should be given in dot number notation\n");
				printf("--nm=<addr> -n<addr>\t\t\tSet IP address of Network Manager\n\t\t\t\t\t<addr> should be given in dot number notation\n");
				printf("--help -h\t\t\t\tDisplay this information\n");
				printf("--spacewire=<bool> -s<bool>\t\tEnable or disable SpaceWire mode\n");
				printf("--debug=<level> -g<level>\t\tSet level of debug messages\n\t\t\t\t\t0=none, 1=moderate, 2=verbose\n");
				printf("--config=<configFile> -c<configFile>\t\tName of config file\n\t\t\t\t\tlocal name or full path to SdmTaskList.config equivalent\n");
				return 0;

			case 'd':
				DataManager.setAddress(inet_addr(optarg));
				if (((long)(DataManager.getAddress())) == -1)
				{
					printf("Error in DM address.  Be sure to use --dm= instead of -dm=\n");
					return 0;
				}
				DataManager.setPort(PORT_DM);
				DM_set = true;
				// note, this can be overridden by --spacewire
				break;

			case 'n':
				use_nm = true;
				NM_Address = inet_addr(optarg);
				break;

			case 'g':
				debug = atoi(optarg);
				break;

			case 's':
				spacewire = !!atoi(optarg);
				break;

			case 'f':
				// The restart is a result of a fault, don't load tasks
				bDoInitialStartup = false;
				break;

			case 'c':
				FILE_SDM_TASK_LIST = strdup(optarg);
				break;

			case '?':
				break;
		}
	}
#ifdef PNP_BACKUP
   // request the DM's address from the NM
	if (use_nm)
	{
      NetworkManager.setAddress (NM_Address);
      NetworkManager.setPort(1982);
	}
	else
	{
      NetworkManager.setAddress ( inet_addr("127.0.0.1") );
      NetworkManager.setPort(1982);
	}
#endif
#ifdef SEND_IMA
	if (spacewire)
	  {
	    debug_f(1, "Running in SpaceWire mode\n");
	    SendIMA(ImaTm, debug);
	  }
#endif
#ifndef __VXWORKS__
	if ((Address_TM = GetNodeAddress(spacewire)) == 0)
#else
	//TODO: The GetNodeAddress(bool) function call is causing problems
	//This work around probably is not sufficient.
	gethostname(hostName, hostNameLength);
	if((Address_TM = hostGetByName(hostName)) == 0)
#endif
	{
		debug_f(0, "Unable to get the TM's IP address, using localhost instead.\n");
		Address_TM = ADDR_LOCAL_HOST;
	}
	else
	{
		debug_f(3, "Task Manager address is 0x%lx\n",Address_TM);
	}

	// Set the Task Manager's node address
	TaskManager.setAddress(Address_TM);
	TaskManager.setPort(PORT_TM);

#ifdef PNP_FAKE
   MessageManager mm;
   mm.Async_Init_Both(PORT_TM);

	AmIBackup(&mm);
#endif

#ifdef PNP_BACKUP
	isBackup = AmIBackup();
#endif

	// If the DM's address was not specified on the command line, assume local
	if(!DM_set && !spacewire)
	{
		DataManager.setAddress(inet_addr("127.0.0.1"));
		DataManager.setPort(PORT_DM);
	}
	else if(spacewire)
	{
		long addr;
#ifndef __VXWORKS__		
		struct hostent *he;
		while ((he=gethostbyname("datamanager.spacewire")) == NULL)
		{
			sleep(1);
		}
		memcpy(&addr, he->h_addr, sizeof(addr));
#else
		while ((addr = hostGetByName("datamanager.spacewire")) == ERROR)
		{
			sleep(1);
		}
#endif
	
		DataManager.setAddress(addr);
		DataManager.setPort(PORT_DM);
		DM_set = true;
	}

#ifdef PNP_FAKE
   RequestDMInfo(&mm);
#endif

#ifdef PNP_BACKUP
   RequestDMInfo();
#endif

	// output version and debug level information
	printf("TM (Task Manager) %s\n",SDM_VERSION);
	switch(debug)
	{
		case 1:
		  printf("TM in debug 1 (moderate).\n");
		  break;
		case 2:
		  printf("TM in debug 2 (verbose).\n");
		  break;
		case 3:
		  printf("TM in debug 3 (verbose w/message echo).\n");
		  break;
    default:
      break;
	}

	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);
	pthread_attr_setstacksize(&threadAttr, THREAD_STACK_SIZE);

	// All subsequent threads block the SIGINT and SIGALRM signals so they aren't interrupted after calling pthread_mutex_lock()
	// this avoids a deadlock situation by dedicating a single thread for signal handling.
#ifndef WIN32
	sigset_t signal_set;
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGALRM);
	sigaddset(&signal_set, SIGINT);
	pthread_sigmask(SIG_BLOCK, &signal_set, NULL);

	if (0 != pthread_create(&SigHandlerThread, &threadAttr, &SigHandler, NULL))
	{
		perror("Could not create signal handler thread.\n");
		return -1;
	}

	// Set up pipe for the heartbeat thread to receive heartbeat responses
#ifndef __VXWORKS__
	pipe(pm_heartbeat_pipe);
#else
	if(pipeDevCreate("/pipe/pmHeartbeat", 10, 100) != 0)
	{
		if(debug >= 2)
			fprintf (stderr, "Pipe error\n");
	}
	pm_heartbeat_pipe = open("/pipe/pmHeartbeat", O_RDWR);
#endif


#ifdef PNP_BACKUP
	pipe(tm_back_heartbeat_pipe);
	pipe(tm_main_heartbeat_pipe);
	if (0 != pthread_create(&TMHeartbeatThread, &threadAttr, &TMHeartbeat, NULL))
	{
		perror("Could not create TM heartbeat thread.\n");
		return -1;
	}
#endif

	if (0 != pthread_create(&PMHeartbeatThread, &threadAttr, &PMHeartbeat, NULL))
	{
		perror("Could not create PM heartbeat thread.\n");
		return -1;
	}

#else
	// Windows signal handling
	signal(SIGINT,SigHandler);
	sigset(SIGALRM,SigHandler);
#endif
	if (bDoInitialStartup)
	{
		InitialStartUp();
	}

	if (0 != pthread_create(&SchedulerThread, &threadAttr, &Scheduler, NULL))
	{
		perror("Could not create scheduler thread.\n");
		return -1;
	}

#ifdef PNP_FAKE
	if (0 != pthread_create(&ListenerThread, &threadAttr, &Listener, &mm))
	{
		perror("Could not create Listen thread.\n");
		return -1;
	}
#else
	if (0 != pthread_create(&ListenerThread, &threadAttr, &Listener, NULL))
	{
		perror("Could not create Listen thread.\n");
		return -1;
	}
#endif
	// verify that DM is present
	VerifyDM();

	debug_f(2,"Finding DM at address 0x%lx\n",DataManager.getAddress());
	debug_f(2,"TM address is 0x%lx\n",Address_TM);

#ifdef PNP_BACKUP
   // at this point we should know who is leader and backup
   if (!isBackup)
   {
#endif
      SDMHello hello;
      hello.source.setPort(PORT_TM);
      hello.type = 'C';
      double endTime = 0;
      double timeOut = 5.0;
      while(!ackReceived)
      {
         if(GetCurTime() > endTime)
         {
            debug_f(1, "Sending Hello\n");
            hello.Send();
            endTime = GetCurTime() + timeOut;
         }
         usleep(10000);
      }
      while(!registerReceived)
      {
         usleep(10000);
      }
      debug_f(1, "Registering xTEDS\n");




      // post xTEDS to the DM
      SDMxTEDS msgXteds;
      msgXteds.source.setSensorID(1);
      msgXteds.source.setPort(PORT_TM);
      strcpy(msgXteds.xTEDS, STR_TASK_MANAGER_XTEDS);
      msgXteds.Send();
      MessageSent(&msgXteds);

      while (!idReceived)
      {
         usleep(10000);
      }
      debug_f(1, "SDMID received\n");

#ifdef PNP_BACKUP
   }
#endif
#ifdef BUILD_FOR_PNPSAT
	//
	// If this is a build for PnPsat, request the PowerController's interface for
	// cycling power to an endpoint
	RequestRegPowerController();
#endif // BUILD_FOR_PNPSAT

#ifndef WIN32
#ifdef PNP_BACKUP
	pthread_join(TMHeartbeatThread,NULL);
#endif
	pthread_join(PMHeartbeatThread,NULL);
	pthread_join(SigHandlerThread,NULL);
#endif
	pthread_join(ListenerThread,NULL);
	pthread_join(SchedulerThread,NULL);
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
 * Separate thread for signal handling.  This avoids a potential deadlock situation in which the ChildFunctionCallProcess function
 * is chosen to handle the SIGALRM signal after it has called pthread_mutex_lock(&subscrition_mutex), which is also called in the
 * signal handler.
 */
#ifndef WIN32
void* SigHandler(void* arg)
{
	SDMCancelxTEDS msgCancel;
	sigset_t signal_set;
	int sig;
	msgCancel.source.setSensorID(1);
	msgCancel.source.setPort(PORT_TM);
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGINT);
	sigaddset(&signal_set, SIGALRM);	
	sigaddset(&signal_set, SIGSEGV);

	while (1)
	{		
		sigwait(&signal_set, &sig);
		switch (sig)
		{
		case SIGINT:
			printf("\nShutting down\n");
			pthread_mutex_lock(&dm_found_mutex);
#ifdef PNP_BACKUP
			if (dm_found && !isBackup && Backup_TM_List.empty())	// Cancel the TM's xTEDS
#endif
			msgCancel.Send();
			pthread_mutex_unlock(&dm_found_mutex);
			MessageSent(&msgCancel);
			exit(EXIT_SUCCESS);
			break;
		case SIGALRM:
			PublishPerformanceCounterMessage();
			pthread_mutex_lock(&perf_counter_mutex);
			prevsec_recd = 0;
			prevsec_sent = 0;
			pthread_mutex_unlock(&perf_counter_mutex);
			break;
		default:
			printf("Unexpected signal received: %i\n", sig);
			break;
		}
	}
}
#else
/*Win32 version uses a SigHandler routine that handles only SIGINT.*/
void SigHandler(int signum)
{
	SDMCancelxTEDS msgCancel;
	msgCancel.source.setSensorID(1);
	msgCancel.source.setPort(PORT_TM);

	if (signum == SIGINT)
	{
		printf("\nShutting down\n");
		pthread_mutex_lock (&dm_found_mutex);
		if (dm_found)
			msgCancel.Send();
		pthread_mutex_unlock (&dm_found_mutex);
		MessageSent(&msgCancel);
		exit (EXIT_SUCCESS);
	}
	else if ( signum == SIGALRM )
	{
		PublishPerformanceCounterMessage();
		pthread_mutex_lock(&perf_counter_mutex);
		prevsec_recd = 0;
		prevsec_sent = 0;
		pthread_mutex_unlock(&perf_counter_mutex);
	}
}
#endif
/*
	PublishStatusMessage publishes the TaskManager's status message to all subscribers.  This status message is used for (possible among other
	things), notifying all SDM components if a DataManager has failed and a new one becomes elected.
	INPUTS:
		sender_buf - Contains the data to be sent in the mode changes message (new DM IP address)
	RETURNS:
		void
*/
void PublishStatusMessage(char *sender_buf)
{
	char buf[11];
	// publish status message
	debug_f(2,"Publishing Status\n");

	pthread_mutex_lock(&mode_mutex);
	buf[0] = g_ucMode;
	pthread_mutex_unlock(&mode_mutex);

	if (sender_buf == NULL)
		memset(&buf[1],0,10);
	else
		memcpy(&buf[1],sender_buf,10);

	pthread_mutex_lock(&subscription_mutex);
	if(subscriptions.Publish(NOTI_TM_STATUS,buf,11))
	{
		MessageSent(subscriptions.GetLastPublished());
		debug_f(3,"Status Message Sent\n");
	}
	else
		debug_f(3,"No Status Message Subscribers\n");
	pthread_mutex_unlock(&subscription_mutex);
}
/*
	PublishTaskQueuedMessage publishes to all subscribers, the name of a newly queued task for execution.  Any time a new task is posted
	to the TaskManager, it publishes this message.
	INPUTS:
		taskname - The name of the task posted.
	RETURNS:
		void
*/
void PublishTaskQueuedMessage(char* taskname)
{
	debug_f(2,"Publishing TaskQueued message for taskname \"%s\"\n", taskname);

	char filename[MAX_FILENAME_SIZE];
	memset(filename, '\0', sizeof(filename));
	strncpy(filename, taskname, sizeof(filename));
	filename[sizeof(filename) - 1] = '\0';

	pthread_mutex_lock(&subscription_mutex);
	if(subscriptions.Publish(NOTI_TASK_QUEUED, filename, sizeof(filename)))
	{
		MessageSent(subscriptions.GetLastPublished());
		debug_f(3,"TaskQueued Message Sent\n");
	}
	else
		debug_f(3,"No TaskQueued Message Subscribers\n");

	pthread_mutex_unlock(&subscription_mutex);
}
/*
	PublishTaskStartedMessage publishes to all subscribers, the name of any task that gets posted to a ProcessManager for execution.
	This message is published any time a task leaves the queued state and starts the running state.
	INPUTS:
		taskname - The name of the task started.
	RETURNS:
		void
*/
void PublishTaskStartedMessage(char* taskname, unsigned int uiPid)
{
  debug_f(2,"Publishing TaskStarted message for taskname \"%s\" pid=%u\n", taskname, uiPid);
	const unsigned int PUBLISH_BUFFER_SIZE = XTEDS_MAX_TASK_NAME_SIZE + sizeof(unsigned int);

	char PublishBuffer[PUBLISH_BUFFER_SIZE];
	memset(PublishBuffer, '\0', sizeof(PublishBuffer));
	strncpy(PublishBuffer, taskname, XTEDS_MAX_TASK_NAME_SIZE);
	PublishBuffer[XTEDS_MAX_TASK_NAME_SIZE - 1] = '\0';

	PUT_UINT(PublishBuffer + XTEDS_MAX_TASK_NAME_SIZE, uiPid);

	pthread_mutex_lock(&subscription_mutex);
	if(subscriptions.Publish(NOTI_TASK_STARTED, PublishBuffer, PUBLISH_BUFFER_SIZE))
	{
		MessageSent(subscriptions.GetLastPublished());
		debug_f(3,"TaskStarted Message Sent\n");
	}
	else
		debug_f(3,"No TaskStarted Message Subscribers\n");

	pthread_mutex_unlock(&subscription_mutex);
}
/*
	PublishTaskFinishedMessage publishes to all subscribers the name of any task that finishes execution on a ProcessManager.
	This message is published when a ProcessManager node informs the TaskManager that a task has completed.
	INPUTS:
		taskname - The name of the task that has finished.
		exitcode - The exit code status of the task that finished.
	RETURNS:
		void
*/
void PublishTaskFinishedMessage(char* taskname,int exitcode, unsigned int uiPid)
{
	debug_f(2,"Publishing TaskFinished message for taskname \"%s\", exit code %d\n", taskname, exitcode);
	const unsigned int PUBLISH_BUFFER_SIZE = XTEDS_MAX_TASK_NAME_SIZE +
	  sizeof (int) + sizeof(unsigned int);

	char PublishBuffer[PUBLISH_BUFFER_SIZE];
	memset(PublishBuffer, '\0', sizeof(PublishBuffer));
	strncpy(PublishBuffer, taskname, XTEDS_MAX_TASK_NAME_SIZE);
	PublishBuffer[XTEDS_MAX_TASK_NAME_SIZE - 1] = '\0';

	PUT_UINT(PublishBuffer + XTEDS_MAX_TASK_NAME_SIZE, uiPid);

	PUT_INT(PublishBuffer + XTEDS_MAX_TASK_NAME_SIZE + sizeof(unsigned int), exitcode);

	pthread_mutex_lock(&subscription_mutex);
	if(subscriptions.Publish(NOTI_TASK_FINISHED,PublishBuffer,PUBLISH_BUFFER_SIZE))
	{
		MessageSent(subscriptions.GetLastPublished());
		debug_f(3,"TaskFinished Message Sent\n");
	}
	else
		debug_f(3,"No TaskFinished Message Subscribers\n");

	pthread_mutex_unlock(&subscription_mutex);
}
/*
	PublishPerformanceCounterMessage publishes the TaskManager's message performance counters to all subscribers every second if there has
	been a subscription request to the performance counter messages.  Otherwise, the system time has not been started and the performance
	counters are not published.
	INPUTS:
		None.
	RETURNS:
		void
*/
void PublishPerformanceCounterMessage(void)
{
	debug_f(2,"Publishing Message_Count\n");

	char msg[16];
	pthread_mutex_lock(&perf_counter_mutex);
	PUT_UINT(&msg[0], total_recd);
	PUT_UINT(&msg[4], prevsec_recd);
	PUT_UINT(&msg[8], total_sent);
	PUT_UINT(&msg[12], prevsec_sent);
	pthread_mutex_unlock(&perf_counter_mutex);

	pthread_mutex_lock(&subscription_mutex);
	if (subscriptions.Publish(NOTI_PERF_COUNTERS, msg, 16))
	{
		MessageSent(subscriptions.GetLastPublished());
		debug_f(3,"Message_Count Message Sent\n");
	}
	else
		debug_f(3,"Message_Count Message Subscribers\n");

	pthread_mutex_unlock(&subscription_mutex);
}
/*
	RegPMHandler handles the registration of a ProcessManager to the system.  This routine stores the IP address and node resource
	limits in the pmList for scheduling.
	INPUTS:
		arg - The buffer containing the SDMRegPM message that was received.
	RETURNS:
		void * - Always NULL.
*/
void* RegPMHandler(void* arg)
{
	char* buf = (char*)arg;
	SDMRegPM msgReg;

	if (msgReg.Unmarshal(buf) < 0)
	{
		printf("Received invalid SDMRegPM message.\n");
		return NULL;
	}
	else
	{
		MessageReceived(&msgReg);
	}

	debug_f(1,"PM registering at ip 0x%lx\n", msgReg.source.getAddress());

	// Check to see if the PM node is already registered with the TM
	if (pmList.AlreadyRegistered(msgReg.source, msgReg.resources))
	{
		// duplicate machine there can be only one pm per ip address
		debug_f(1, "PM node already registered.\n");
		if (debug >= 3)
			pmList.PrintList();
		return NULL;
	}

	if (!pmList.RegisterPM(msgReg.source, msgReg.resources))
	{
		debug_f(0,"Error registering PM, PM list full.\n");
	}
	// See if there is an entry in pending_pms for this ProcessManager if so, copy its task number
	if (pending_pms.AlreadyRegistered(msgReg.source))
	{
		pmList.SetTasks(msgReg.source, pending_pms.GetTasks(msgReg.source));
	}

	if (debug >= 3)
	{
		pmList.PrintList();
	}

	return NULL;
}
/*
	ReqCodeHandler handles the receipt of an SDMCode message.  This function calls SendCode directly.
	INPUTS:
		arg - The buffer containing the SDMCode message.
	RETURNS:
		void * - Always NULL.
*/
void* ReqCodeHandler(void* arg)
{
	char* buf = (char*)arg;
	debug_f(1,"Request for code\n ");
	SendCode (buf);
	delete[] buf;
	return NULL;
}
/*
	PostTaskHandler handles the receipt of an SDMTask message, to post a task to a ProcessManager.
	This function calls PostTask directly.
	INPUT:
		arg - The buffer containing the SDMTask message.
	RETURNS:
		void * - Always NULL.
*/
void* PostTaskHandler(void* arg)
{
	char* buf = (char*)arg;
	debug_f(1,"Post task\n ");
	PostTask (&buf[0]);
	return NULL;
}
/*
	SubreqstHandler handles the receipt of an SDMSubreqst message.  This routine gets the subscription request's message and
	interface ID's and adds the request to the TM's subscription list.
	INPUTS:
		arg - The buffer containing the SDMSubreqst message.
	RETURNS:
		void * - Always NULL.
*/
void* SubreqstHandler(void* arg)
{
	char* buf = (char*)arg;
	SDMSubreqst msgRequest;

	// Unmarshal message
	if (msgRequest.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMSubreqst message.\n");
		return NULL;
	}
	else
	{
		MessageReceived(&msgRequest);
	}

	debug_f(1,"Subscription request (interface %hhd, message %hhd)\n", msgRequest.msg_id.getInterface(), msgRequest.msg_id.getMessage());

	// Add the subscription request to the TM's subscription list
	pthread_mutex_lock(&subscription_mutex);
	subscriptions.AddSubscription(msgRequest);
	pthread_mutex_unlock(&subscription_mutex);

#ifdef PNP_BACKUP
	// Request for TM's status notification
	if (!isBackup && msgRequest.msg_id == NOTI_TM_STATUS)
	{
		PublishStatusMessage(NULL);
	}
#else
	// Request for TM's status notification
	if (msgRequest.msg_id == NOTI_TM_STATUS)
	{
		PublishStatusMessage(NULL);
	}
#endif
	else if (msgRequest.msg_id == NOTI_PERF_COUNTERS) // Request for TM's performance counters
	{
#ifndef __VXWORKS__
		itimerval interval;
		getitimer(ITIMER_REAL, &interval);
		if (interval.it_value.tv_sec == 0 && interval.it_interval.tv_sec == 0)
		{
			// Time interval for the performance counter publish
			timeval pubInterval;
			pubInterval.tv_sec = 1;
			pubInterval.tv_usec = 0;

			itimerval timerInterval;
			timerInterval.it_interval = pubInterval;
			timerInterval.it_value = pubInterval;

			// Set the performance counter timer
			setitimer (ITIMER_REAL, &timerInterval, NULL);
		}
#else
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

	return NULL;
}
/*
	DeletesubHandler handles the receipt of an SDMDeletesub message.  This message removes the specified subscription from the
	TaskManagers subscription list.
	INPUTS:
		arg - The buffer containing the SDMDeletesub message.
	RETURNS:
		void * - Always NULL.
*/
void* DeletesubHandler(void* arg)
{
	char* buf = (char*)arg;
	SDMDeletesub msgDeleteSub;

	// Unmarshal the message
	if (msgDeleteSub.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMDeletesub message.\n");
		return NULL;
	}
	MessageReceived(&msgDeleteSub);

	debug_f(1,"Subscription cancellation (interface %d, message %d)\n", msgDeleteSub.msg_id.getInterface(), msgDeleteSub.msg_id.getMessage());

	// Remove the subscription request from the TM's subscription list
	pthread_mutex_lock(&subscription_mutex);
	subscriptions.RemoveSubscription(msgDeleteSub);
	pthread_mutex_unlock(&subscription_mutex);

	return NULL;
}
/*
	CommandHandler handles the receipt of an SDMCommand message.  If the specified message and interface IDs are appropriate for
	one of the TaskManager's command messages, the command is issued.
	INPUTS:
		arg - The buffer containing the SDMCommand message.
	RETURNS:
		void * - Always NULL.
*/
void* CommandHandler(void* arg)
{
	char* buf = (char*)arg;
	SDMCommand msgCommand;

	// Unmarshal the message
	if (msgCommand.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMCommand message.\n");
		delete [] buf;
		return NULL;
	}
	MessageReceived(&msgCommand);

	debug_f(1,"Command request (interface %d, message %d)\n",msgCommand.command_id.getInterface(), msgCommand.command_id.getMessage());

	// Command to change the TM's mode
	if (msgCommand.command_id == CMD_CHANGE_MODE)
	{
		bool bDoHardReset = false;
		bool bDoSoftReset = false;
		unsigned char ucOldMode, ucModeCopy, ucNewMode;
		SDMComponent_ID idNewDm;

		// Get the TM's current mode value
		pthread_mutex_lock(&mode_mutex);
		ucModeCopy = g_ucMode;
		pthread_mutex_unlock(&mode_mutex);
		ucNewMode = GET_UCHAR(&msgCommand.data[0]);

		debug_f(2,"Command to change mode (TM current mode=%hhu, new mode=%hhu\n", ucModeCopy, ucNewMode);
		// If the current mode is not the same as the new change received
		if (ucModeCopy != ucNewMode)
		{
			// change to new mode
			ucOldMode = ucModeCopy;
			pthread_mutex_lock(&mode_mutex);
			g_ucMode = ucNewMode;
			pthread_mutex_unlock(&mode_mutex);

			if (ucNewMode == MODE_STATUS_HARD_RESET)
         {
            debug_f(1, "Performing a hard reset...\n");
				bDoHardReset = true;
         }
			else if (ucNewMode == MODE_STATUS_SOFT_RESET)
         {
			    debug_f(1, "Performing a soft reset...\n");
			    bDoSoftReset = true;
         }
			// Reset code for hard or soft grouped similarly
			// A soft reset should restart (kill) all of the tasks
			// running on each PM.
			// A hard reset needs to re-verify the DM and register
			// the usual xTEDS again.
			if (bDoHardReset || bDoSoftReset)
			{
			  if (bDoHardReset)
           {
			      // Reset dm_found, and re-verify the DM
			      pthread_mutex_lock(&dm_found_mutex);
			      dm_found = false;
			      pthread_mutex_unlock(&dm_found_mutex);
			      // Gets the new DM address
#ifdef PNP_BACKUP
			      VerifyNewDM(&msgCommand.data[1]);
			      idNewDm = DataManager;
			      debug_f(2,"New DM address is 0x%lx:%hd %ld\n",idNewDm.getAddress(), idNewDm.getPort(), idNewDm.getSensorID());
#endif


           }
#ifdef PNP_BACKUP
			  if (!isBackup)
           {
			      // Notify all PMs of the mode change
			      PublishStatusMessage(&msgCommand.data[1]);
           }
#else
			  PublishStatusMessage(&msgCommand.data[1]);
#endif

           if (bDoHardReset)
           {
			      VerifyDM();
               idNewDm = DataManager;
			      // The new DM address is acquired is responses to VerifyDM
			      debug_f(2,"New DM address is 0x%lx:%hd %ld\n",idNewDm.getAddress(), idNewDm.getPort(), idNewDm.getSensorID());

			      // Reregister the TM's xTEDS
//			      SDMxTEDS msgXteds;
//			      msgXteds.source = TaskManager;
//			      msgXteds.source.setSensorID(1);
//			      strncpy(msgXteds.xTEDS, STR_TASK_MANAGER_XTEDS, sizeof(msgXteds.xTEDS));
//			      msgXteds.Send();
//			      MessageSent(&msgXteds);
           }
           // Clear the task list
			  // Hold the list mutex as well to prevent the scheduler from restarting
			  // before the scheduler reset can be set and the task list from clearing
			  // This should be the only place that these two locks are held at the same
			  // time.
			  pthread_mutex_lock(&g_mutexSchedulerReset);
			  pthread_mutex_lock(&list_mutex);
			  g_bSchedulerReset = true;
			  taskList.ClearList();
			  pthread_mutex_unlock(&list_mutex);
			  pthread_mutex_unlock(&g_mutexSchedulerReset);

			  // Set all PM's to not having any running tasks
			  pmList.ClearAllRunningTasks();

			  // Re-Read the sdm.config file for any startup tasks
			  InitialStartUp();

			  // Reset the mode back to the mode before the reset
			  pthread_mutex_lock(&mode_mutex);
			  g_ucMode = ucOldMode;
			  pthread_mutex_unlock(&mode_mutex);

			  delete [] buf;
			  return NULL;
			}
			// If the mode change was not for a reset, publish here
#ifdef PNP_BACKUP
			if (!isBackup)
			{
			  PublishStatusMessage(&msgCommand.data[1]);
			}
#else
			PublishStatusMessage(&msgCommand.data[1]);
#endif
		}
	}
	// Command to enable message logging
	else if (msgCommand.command_id == CMD_ENABLE_LOGGING)
	{
		pthread_mutex_lock(&log_service_mutex);
		if (log_service.NeedsInit())
			log_service.SetLogFile("Task Manager Message Log\n","tmmessages.log");
		log_service.AddMessageType(&msgCommand);
		pthread_mutex_unlock(&log_service_mutex);
	}
	// Command to disable message logging
	else if (msgCommand.command_id == CMD_DISABLE_LOGGING)
	{
		pthread_mutex_lock(&log_service_mutex);
		log_service.RemoveMessageType(&msgCommand);
		pthread_mutex_unlock(&log_service_mutex);
	}
	// Command to start a task
	else if (msgCommand.command_id == CMD_START_TASK)
	{
		// Create a task request and post
		char buf[256];
		SDMPostTask msgTask;
		msgTask.priority = 1;
		unsigned int uiCurBufferOffset = 0;
		SDMTaskResources taskResources;
		//
		// Get the task name
		strncpy(msgTask.filename, msgCommand.data, sizeof(msgTask.filename));
		msgTask.filename[sizeof(msgTask.filename) - 1] = '\0';
		uiCurBufferOffset += XTEDS_MAX_TASK_NAME_SIZE;
		//
		// Get the arch type
		char cArchType = GET_CHAR(&msgCommand.data[uiCurBufferOffset]);
		switch( cArchType )
		  {
		  case ARCH_TYPE_INTEL:
		    taskResources.SetArch(SDM_INTEL);
		    break;
		  case ARCH_TYPE_MICROBLAZE:
		    taskResources.SetArch(SDM_MICROBLAZE);
		    break;
		  case ARCH_TYPE_SPARC:
			taskResources.SetArch(SDM_SPARC);
			break;
      default:
        break;
		  }
		uiCurBufferOffset += sizeof(char);
		//
		// Get the OS type
		char cOsType = GET_CHAR(&msgCommand.data[uiCurBufferOffset]);
		switch( cOsType )
		  {
		  case OS_TYPE_LINUX26:
		    taskResources.SetOs(SDM_LINUX26);
		    break;
		  case OS_TYPE_WIN32:
		    taskResources.SetOs(SDM_WIN32);
		    break;
		  case OS_TYPE_VXWORKS:
			taskResources.SetOs(SDM_VXWORKS);
			break;
      default:
        break;
		  }
		uiCurBufferOffset += sizeof(char);
		//
		// Get the mem type
		char cMemType = GET_CHAR(&msgCommand.data[uiCurBufferOffset]);
		switch( cMemType )
		  {
		  case MEM_TYPE_64:
		    taskResources.SetMem(SDM_MEM64);
		    break;
		  case MEM_TYPE_128:
		    taskResources.SetMem(SDM_MEM128);
		    break;
		  case MEM_TYPE_256:
		    taskResources.SetMem(SDM_MEM256);
		    break;
		  case MEM_TYPE_512:
		    taskResources.SetMem(SDM_MEM512);
		    break;
      default:
        break;
		  }
		uiCurBufferOffset += sizeof(char);
		msgTask.resources = taskResources.GetUShort();
		//
		// Get the mode
		char cMode = GET_CHAR(&msgCommand.data[uiCurBufferOffset]);
		switch( cMode )
		  {
		  case EXECUTION_MODE_NORMAL:
		    msgTask.mode = MODE_NORMAL;
		    break;
		  case EXECUTION_MODE_ALWAYS_RUNNING:
		    msgTask.mode = MODE_ALWAYS_RUNNING;
		    break;
      default:
        break;
		  }
		uiCurBufferOffset += sizeof(char);
		//
		// Get the Preferred Node Id
		char cPnode = GET_CHAR(&msgCommand.data[uiCurBufferOffset]);
		if ( cPnode > 0 ) // Only set a node ID if greater than 0, 0 implies the TM will choose a node
		{
			taskResources.SetPreferredPmNodeId(cPnode);
		}
		uiCurBufferOffset += sizeof(char);
		//
		// Get the task retrieval location
		char cRetrievalLocation = GET_CHAR(&msgCommand.data[uiCurBufferOffset]);
		// Retrieval location is the "version" to use
		msgTask.version = cRetrievalLocation;

		msgTask.Marshal(buf);
		PostTask(buf);
	}
	// Command to kill a task
	else if (msgCommand.command_id == CMD_KILL_TASK)
	{
		// Create a kill request and send
		SDMKill msgKill;
		msgKill.PID = GET_UINT(msgCommand.data);
		msgKill.killLevel = GET_UCHAR(&msgCommand.data[4]);
#ifdef PNP_BACKUP
		if (!isBackup)
		{
		  PerformKill(msgKill);
		}
#else
		PerformKill(msgKill);
#endif
	}
	delete[] buf;
	return NULL;
}
/*
	SerreqstHandler handles the receipt of an SDMSerreqst message.  If the specified message and interface IDs are appropriate for
	one of the TaskManager's service requests messages, the request is handled.
	INPUTS:
		arg - The buffer containing the SDMSerreqst message.
	RETURNS:
		void * - Always NULL.
*/
void* SerreqstHandler(void* arg)
{
	char* buf=(char*)arg;
	SDMSerreqst msgRequest;
	SDMData msgReply;

	// Unmarshal the message
	if (msgRequest.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMCommand message.\n");
		return NULL;
	}
	MessageReceived(&msgRequest);

	debug_f(1,"Service request received (interface %d, message %d)\n",msgRequest.command_id.getInterface(), msgRequest.command_id.getMessage());

	// Request to translate a task name to the SDM process identifier
	if (msgRequest.command_id == SER_NAME_TO_PID)
	{
		debug_f(2, "  Task name to PID request for task \"%s\".\n", msgRequest.data);
		msgReply.source = msgRequest.source;
		msgReply.msg_id = SER_NAME_TO_PID_REPLY;

		// Find the pid for the filename given
		pthread_mutex_lock(&list_mutex);
		unsigned int SDMTaskID = taskList.FindPID(msgRequest.data);
		pthread_mutex_unlock(&list_mutex);

		// Put the filename and the PID into the reply message
		strncpy(msgReply.msg, msgRequest.data, MAX_FILENAME_SIZE);
		PUT_INT(msgReply.msg + MAX_FILENAME_SIZE, SDMTaskID);

		// Send the message
		const int ReplyLength = msgRequest.length + sizeof(unsigned int);
		msgReply.length = ReplyLength;
		msgReply.Send(msgRequest.destination);

		debug_f(1, "  Name to PID reply sent to 0x%lx port: %i.id: %i\n", msgRequest.destination.getAddress(), msgRequest.destination.getPort(), SDMTaskID);
	}
	else if (msgRequest.command_id == SER_GET_TASK_LIST)
	  {
	    debug_f(2, "  Request to get the task list.\n");
	    msgReply.source = msgRequest.source;
	    msgReply.msg_id = SER_TASK_LIST_REPLY;

	    unsigned int uiReplyLength;
	    pthread_mutex_lock(&list_mutex);
	    uiReplyLength = taskList.FillTaskListBlob(msgReply.msg, sizeof(msgReply.msg));
	    pthread_mutex_unlock(&list_mutex);

	    msgReply.Send(msgRequest.destination, uiReplyLength);
	  }
	else if (msgRequest.command_id == SER_GET_RUNNING_TASK_LIST)
	  {
	    debug_f(2, "  Request to get the running task list.\n");
	    msgReply.source = msgRequest.source;
	    msgReply.msg_id = SER_RUNNING_TASK_LIST_REPLY;

	    unsigned int uiReplyLength;
	    pthread_mutex_lock(&list_mutex);
	    uiReplyLength = taskList.FillTaskListBlobRunningOnly(msgReply.msg, sizeof(msgReply.msg));
	    pthread_mutex_unlock(&list_mutex);

	    msgReply.Send(msgRequest.destination, uiReplyLength);
	  }
	else if (msgRequest.command_id == SER_GET_TASK_INFO)
	  {
	    debug_f(2, "  Request to get task info.\n");
	    msgReply.source = msgRequest.source;
	    msgReply.msg_id = SER_TASK_INFO_REPLY;

	    unsigned int ulRequestPid = GET_UINT(msgRequest.data);

	    unsigned int uiReplyLength;
	    pthread_mutex_lock(&list_mutex);
	    uiReplyLength = taskList.FillTaskInfoRequest(ulRequestPid, msgReply.msg, sizeof(msgReply.msg));
	    pthread_mutex_unlock(&list_mutex);

	    msgReply.Send(msgRequest.destination, uiReplyLength);
	  }

	return NULL;
}


void* KillHandler(void* arg)
{
	char* buf=(char*)arg;
	SDMKill kill;

	if (kill.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMKill message.\n");
		return NULL;
	}
	MessageReceived(&kill);
	PerformKill(kill);

	return NULL;
}

bool PerformKill(SDMKill& msgKill)
{
	debug_f(1, "Kill request for SDM pid %lu\n",msgKill.PID);

	pthread_mutex_lock(&list_mutex);
	const SDMComponent_ID PMComponentID = taskList.GetPMAddress(msgKill.PID);

	if (debug >= 3)
	{
		taskList.PrintList();
	}
	pthread_mutex_unlock(&list_mutex);

	msgKill.Send(PMComponentID);
	return true;
}

/*
	ReadyHandler handles the receipt of SDMReady messages from a ProcessManager.  A PM node must verify the existence of the
	TaskManager through the ready message.  The TaskManager responds with an SDMReady message containing the PM node's
	IP address and the IP address of the DataManager.
	INPUTS:
		arg - The HandlerArguments object with the SDMReady message.
	RETURNS:
		void * - Always NULL
*/
void* ReadyHandler(void* arg)
{
	HandlerArguments *hArgs = static_cast<HandlerArguments*>(arg);
	const char* buf = hArgs->getBuffer();
	unsigned long addr;
	SDMReady msgReady;
	SDMReady msgReadyRequest;
	//bool setNewDMAddress = false;

	// Unmarshal the message
	if (msgReadyRequest.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMReady message.\n");
		delete hArgs;
		return NULL;
	}
	MessageReceived(&msgReadyRequest);

	debug_f(3,"Ready query received\n");

	// If the SDMReady message is from the DataManager
	if (msgReadyRequest.destination.getPort() == PORT_DM)
	{
		delete hArgs;
		return NULL;
	}
	// If this is from the Task Manager's monitor process
	else if (msgReadyRequest.source.getPort() == PORT_TM_MONITOR)
	{
		// Send the reply message
		debug_f(3,"Received TM monitor heartbeat message, responding.\n");
		msgReady.Send(msgReadyRequest.source);
		MessageSent(&msgReady);
		delete hArgs;
		return NULL;
	}
	// Get the IP address of the sender
	addr = hArgs->getSenderHost();
	msgReady.destination.setPort(PORT_PM);

	// If the PM is on the same node as the TM, and the TM already knows its IP address, give the PM the known IP
	if(addr == inet_addr("127.0.0.1") && Address_TM != inet_addr("127.0.0.1"))
		msgReady.destination.setAddress(Address_TM);
	else
		msgReady.destination.setAddress(addr);
	// The DM's address, is given to the PM at the source component ID
	msgReady.source = DataManager;
	msgReady.Send(msgReady.destination);
	MessageSent(&msgReady);
	/*
	if (setNewDMAddress)
		VerifyDM();
   */
	delete hArgs;
	return NULL;
}
/*
	TaskFinishedHandler handles the receipt of SDMTaskFinished messages from a ProcessManager node.  A PM will send an SDMTaskFinished
	message once a task has finished execution, and the task should be removed from the TaskManager's task list.  The TM will also
	published the TaskFinished message as descirbed in the TM's xTEDS.
	INPUTS:
		arg - The buffer containing the SDMTaskFinished messaage.
	RETURNS:
		void * - Always NULL.
*/
void* TaskFinishedHandler(void* arg)
{
	char* buf=(char*)arg;
	char taskname[MAX_FILENAME_SIZE];
	int exitcode;
	SDMTaskFinished msgFinished;

	// Unmarshal the message
	if (msgFinished.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMTaskFinished message.\n");
		return NULL;
	}
	MessageReceived(&msgFinished);

	debug_f(1,"Task %s has finished, pid %d\n",msgFinished.filename, msgFinished.pid);

	// Decrement the number of running tasks for this PM
	if (!pmList.TaskFinished(msgFinished.source))
	{
		debug_f(0, "Error, Could not find the PM corresponding to a finished task.\n");
	}

	pthread_mutex_lock(&list_mutex);
	if (!taskList.TaskFinished(msgFinished.pid))
	  {
	    debug_f(0, "Error, Could not find the task in the task list.\n");
	  }
	pthread_mutex_unlock(&list_mutex);

	if (debug >= 3)
	{
	  pthread_mutex_lock(&list_mutex);
	  taskList.PrintList();
	  pthread_mutex_unlock(&list_mutex);
	}

	// Get the filename of the finished task
	strncpy(taskname, msgFinished.filename, MAX_FILENAME_SIZE);
	taskname[MAX_FILENAME_SIZE - 1] = '\0';
	exitcode = GET_INT(&msgFinished.result);
#ifdef PNP_BACKUP
	if (!isBackup)
	  {
	    // Publish the task finished notification message
	    PublishTaskFinishedMessage(taskname, exitcode);
	  }
#else
	PublishTaskFinishedMessage(taskname, exitcode, msgFinished.pid);
#endif
	return NULL;
}
/*
	PMRunningTaskHandler handles SDMTask messages received from ProcessManager nodes.  These messages are sent after the
	TaskManager has experienced a fault, and has died.  This function rebuilds the pmList so that tasks don't have to
	be reposted and the scheduler for the TM knows how many tasks are running on all registered PMs.
	INPUTS:
		arg - A pointer to a buffer containing the SDMTask message.
	RETURNS:
		void * - Always NULL.
*/
void* PMRunningTaskHandler(void* arg)
{
	char* buf = (char*)arg;
	SDMTask msgTask;

	// Unmarshal the message
	if (msgTask.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMTask message.\n");
		return NULL;
	}
	MessageReceived(&msgTask);

	debug_f(1,"SDMTask message received.\n");
	//
	// Make sure the TM pid value stays at a consistent value
	pthread_mutex_lock(&pid_mutex);
	if (msgTask.pid >= NextPID)
		NextPID = msgTask.pid + 1;
	pthread_mutex_unlock(&pid_mutex);
	//
	// Add this task to the task list
	Task task;
	task.SetTask(SCHEDULED, msgTask.priority, msgTask.pid, 0u /*resources*/, msgTask.filename, 0 /*interval*/, MODE_NORMAL, 0 /*version*/);
	pthread_mutex_lock(&list_mutex);
	taskList.AddTo(task);
	debug_f(4, "Posting task.\n");
	if (debug >= 4)
		taskList.PrintList();
	pthread_mutex_unlock(&list_mutex);


	// If a PM registered before receiving all of its running task messages,
	// simply add this task to that list, if this fails, assume the PM hasn't registered
	if (pmList.TaskHasStarted(msgTask.source))
	{
		// PM is already registered, finish
		return NULL;
	}
	// Search the pending PMs list to see if this task message corresponds to an already existing PM
	if (pending_pms.AlreadyRegistered(msgTask.source))
	{
		pending_pms.TaskHasStarted(msgTask.source);
	}
	else
	{
		// If the PM hasn't been found, it needs to be added to the list
		pending_pms.RegisterPM(msgTask.source, 0);
		pending_pms.TaskHasStarted(msgTask.source);
	}

	return NULL;
}
/*
	Scheduler schedules queued tasks in the system to ProcessManager nodes whose resource types match.  This scheduler routine tries
	to schedule tasks even among PM nodes.
	INPUTS:
		arg - Not used, exists to match function signature for thread routines.
	RETURNS:
		void * - Always NULL.

//TODO:  This algorithm needs to be updated to be able to schedule more robustly for heterogenous PM architectures.  Currently,
   taskList.FindPendingTask() returns the top pending task in the list, if PM resources for that task hasn't registered,
   it will race the rest of the list from being scheduled.
*/
void* Scheduler(void* arg)
{
	bool pending_tasks;
	unsigned int uiCurSeconds = 0;
	unsigned int uiCurUSeconds = 0;
	unsigned int uiLastSeconds = 0;
	const unsigned int PREFERRED_SCHEDULE_TIMEOUT = 60;	// In seconds
	const unsigned int WAIT_FOR_PM_TIMEOUT = 100000;	// In useconds
	while(1)
	{
      // search for active (i.e. available tasks)
      pthread_mutex_lock(&list_mutex);
      pending_tasks = taskList.AnyPending();
      pthread_mutex_unlock(&list_mutex);
      if(pending_tasks)
      {
         Task TaskData;
         pm_record PMData;
         bool bPmFound = false;
         //
         // Find a task to schedule
         pthread_mutex_lock(&list_mutex);
         int TaskIndex = taskList.FindPendingTask(TaskData /*output*/ );
         if (TaskIndex == -1)
         {
            pthread_mutex_unlock(&list_mutex);
            usleep(WAIT_FOR_PM_TIMEOUT);
            continue;
         }
         //
         // Make sure at least one PM is registered
         if (pmList.IsEmpty())
         {
            pthread_mutex_unlock(&list_mutex);
            usleep(WAIT_FOR_PM_TIMEOUT);
            continue;
         }
         //
         // Find a PM to schedule this task to
         if (TaskData.resources.IsPreferredPmIdSet())
         {
            // Find the PM with matching node id
            bPmFound = pmList.FindPMID(TaskData.resources, PMData);
            if (!bPmFound)
            {
               // If the PM is not yet available, check the timeout to make sure this task
               // eventually gets scheduled somewhere even if the PM never does register
               SDM_GetTime(&uiCurSeconds, &uiCurUSeconds);

               if (uiLastSeconds == 0)
                  uiLastSeconds = uiCurSeconds;
               else if(uiCurSeconds - uiLastSeconds > PREFERRED_SCHEDULE_TIMEOUT)
               {
                  // Remove the preferred id for all tasks in the task
                  // list with this current id, the pm node doesn't look
                  // like it's going to register
                  debug_f(1, "Preferred PM node not found, removing it from the task list...\n");
                  taskList.RemovePreferredPmId(TaskData.resources);
                  if (debug >= 3)
                    taskList.PrintList();
               }
               else
               {
                  debug_f(2, "Preferred PM not found for the top task, waiting for %ul more seconds...\n",
                     PREFERRED_SCHEDULE_TIMEOUT - (uiCurSeconds - uiLastSeconds));
                  if (debug >= 3)
                    taskList.PrintList();
               }
               pthread_mutex_unlock(&list_mutex);
               usleep(WAIT_FOR_PM_TIMEOUT);
               continue;
            }
         }
         else
         {
            // No preferred pm id --
            // Find some PM node to schedule taking into account
            // a relatively uniform node load (task count)
            for (int j = 0; j < MAX_JOBS; j++)
            {
               bPmFound = pmList.FindEligiblePM(j, TaskData.resources, PMData /*output*/ );
               if (bPmFound)
                  break;
            }
            if (!bPmFound)
            {
              debug_f(2, "No PM available to schedule tasks.\n");
               // PM not available, wait for one
               pthread_mutex_unlock(&list_mutex);
               usleep(WAIT_FOR_PM_TIMEOUT);
               continue;
            }
         }

         //
         // At this point, we have both a task and a pm to schedule
         //
         // Sleep to allow for task coordination
         if (TaskData.timeout != 0)
         {
	    pthread_mutex_unlock(&list_mutex);  // Don't hold this over a sleep
            sleep(TaskData.timeout);

            // Make sure a reset didn't occur while we were sleeping, if so, start over
	    pthread_mutex_lock(&g_mutexSchedulerReset);
	    bool bResetScheduler = g_bSchedulerReset;
	    if (g_bSchedulerReset)
	      g_bSchedulerReset = false; // Reset to false
	    pthread_mutex_unlock(&g_mutexSchedulerReset);

	    // If there has been a reset, don't continue
	    if (bResetScheduler)
	      continue;

	    // Otherwise, continue scheduling this task
	    pthread_mutex_lock(&list_mutex);
         }
	 //
         // Assign a PID
         pthread_mutex_lock(&pid_mutex);
         TaskData.pid = taskList[TaskIndex].pid = NextPID++;
         pthread_mutex_unlock(&pid_mutex);

#ifdef PNP_BACKUP
         if (!isBackup)
         {
            SendTask(PMData, TaskData);
         }
#else
	 SendTask(PMData, TaskData);
#endif
         //
         // A match, increment the task count
         pmList.TaskHasStarted(PMData.component_id);
         //
         // Save the PM address for the Task
         taskList[TaskIndex].state = SCHEDULED;
         taskList[TaskIndex].timeout = 0;
         taskList[TaskIndex].pmComponentID = PMData.component_id;
         //
         // Debug output
		 debug_f(1,"Scheduling task \"%s\"(pid %d) to Process Manager (NodeID %d) with\n   ",
				  TaskData.filename, TaskData.resources.GetPreferredPmId(), TaskData.pid);
         if (debug >= 1)
            printResources(PMData.resources);
         debug_f(1,"\n   %d running tasks\n\n",PMData.tasks+1);
         if (debug >= 3)
            taskList.PrintList();
         pthread_mutex_unlock(&list_mutex);
         if (debug >= 3)
            pmList.PrintList();

         uiLastSeconds = 0;
      }
      else
      {
         // No tasks to schedule, reset the preferred scheduling timeout
         uiLastSeconds = 0;
         sleep(1);
      }
   }

	return NULL;
}
/*
	The SendTask sends an appropriate task to an idle PM
	INPUT:
		pm_index - an index into the pmList structure
	RETURNS:
		bool - True if a task has been found to be scheduled, false otherwise.
*/
bool SendTask (const pm_record& PMData, const Task& task)
{
	SDMTask msgTask;

	// if a task was found marshal the task message
	msgTask.priority = task.priority;
	memset(msgTask.filename,'\0',MAX_FILENAME_SIZE);
	strncpy(msgTask.filename,task.filename,MAX_FILENAME_SIZE);
	msgTask.pid = task.pid;
	msgTask.version = task.taskVersion;

	// Send the message
	msgTask.Send(PMData.component_id);
	MessageSent(&msgTask);
	debug_f(2,"%s task sent\n",task.filename);

	PublishTaskStartedMessage(task.filename, task.pid);
	return true;
}

/*
	This thread runs for the life of the TM instance.  This thread is responsible for sending and receiving SDMHeartbeat messages to and
	from all registered PM nodes.  Also, if a heartbeat isn't responded to, the this thread will remove it from the registered PM
	list, making the assumption that the PM module has failed.

	INPUTS:
		arg - Not used.
	RETURNS:
		void * - Always NULL.
*/
void* PMHeartbeat (void* arg)
{
   sleep(5);
	int num_sent = 0;		                //counter for the number of messages sent
	int num_received = 0;		            //counter for the number of messages received

#ifndef __VXWORKS__  //VxWorks does not support poll
	struct pollfd pm_poll_fd;		         //poll struct
	pm_poll_fd.events = POLLIN | POLLPRI;
	pm_poll_fd.fd = pm_heartbeat_pipe[0];
#else
	struct fd_set fds;
	FD_SET(pm_heartbeat_pipe, &fds);
	timeval pmTimeout;
	pmTimeout.tv_sec = PM_HEARTBEAT_TIMEOUT;
#endif

	int poll_res = 0;
	SDMHeartbeat msgHeartbeat;	            //heartbeat message to send out
	SDMHeartbeat msgHeartbeatReceived;     //heartbeat message to receive
	char buf[BUFSIZE];		               //buffer for receiving message
	long length;			                  //Length of the heartbeat message being read

	msgHeartbeat.source = TaskManager;

	while (1)
	{
#ifdef PNP_BACKUP
      if (!isBackup)
      {
#endif
         // Send out heartbeat messages to all registered Process Managers
         num_sent = pmList.SendHeartbeatToAll(msgHeartbeat);

         debug_f(3, "Sent heartbeat to %d PMs.\n",num_sent);

         // Wait for responses
         num_received = 0;

         while (num_sent > num_received)
         {
#ifndef __VXWORKS__  //VxWorks doesn't support poll, use select instead
            if ((poll_res=poll(&pm_poll_fd,1,PM_HEARTBEAT_TIMEOUT)) < 0)
#else
			if((poll_res=select(pm_heartbeat_pipe + 1, &fds, NULL, NULL, &pmTimeout)) < 0)
#endif
            {
               perror ("PMHeartbeat: Poll error.\n");
               break;
            }
            else if (poll_res > 0)
            {
               // Read message length from the pipe
#ifndef __VXWORKS__
				read(pm_heartbeat_pipe[0], &length, sizeof(long));
#else
				read(pm_heartbeat_pipe, &length, sizeof(long));
#endif
               // Read message from pipe
               if (length > 0 && length < BUFSIZE)
               {
#ifndef __VXWORKS__	
					if (read(pm_heartbeat_pipe[0], buf, length) < 0)
#else
					if (read(pm_heartbeat_pipe, buf, length) < 0)			
#endif
					{
						continue;
					}
               }
               num_received++;
               if (msgHeartbeatReceived.Unmarshal(buf) < 0) // buf still gets unmarshaled
               {
                  printf("Invalid SDMHeartbeat message.\n");
               }
               else
               {
                  debug_f(3,"PM heartbeat received.\n");

                  // Find the PM node for which this heartbeat corresponds and reset its status
                  pmList.HeartbeatReceived(msgHeartbeatReceived.source);
               }
            }
            // If any PM nodes didn't respond within five seconds, break
            else
            {
               break;
            }
         }

         // Check for any PM nodes that haven't responded in a while
         pm_record PMNode;
         while (pmList.RemoveAnyFailed(PMNode))
         {
            debug_f(0,"PM node failed.\n");
            if (debug >= 3)
               pmList.PrintList();

            pthread_mutex_lock(&list_mutex);
            taskList.PMFailure(PMNode.component_id);
            if (debug >= 3)
               taskList.PrintList();
            pthread_mutex_unlock(&list_mutex);
   #ifdef BUILD_FOR_PNPSAT
            // Power-cycle the endpoint
            PowerCyclePmNode(PMNode.component_id);
   #endif
         }

         // Only send out heartbeats every five seconds or so
         sleep(5);
#ifdef PNP_BACKUP
      }
#endif
	}
	return NULL;
}

void RegInfoHandler(void* arg)
{
   char* pMessage = static_cast<char*>(arg);
   SDMRegInfo msgRegInfo;
   long lResult = msgRegInfo.Unmarshal(pMessage);
   if (lResult < 0)
   {
	  if (lResult != SDM_NO_FURTHER_DATA_PROVIDER)
		printf("Invalid SDMRegInfo message.\n");
      // Don't handle invalid messages or no further data provider messages
      return;
   }

#ifdef BUILD_FOR_PNPSAT
   if (msgRegInfo.id == REQREG_POWER_CONTROLLER_ID)
   {
      if (msgRegInfo.type == SDM_REGINFO_REGISTRATION)
      {
         pthread_mutex_lock(&g_mutexPowerControllerData);

         g_mmEndpointReset.setMsgDef(msgRegInfo.msg_def);
         g_midEndpointReset = msgRegInfo.msg_id;
         g_cidPowerController = msgRegInfo.source;
         g_bPowerControllerFound = true;

         pthread_mutex_unlock(&g_mutexPowerControllerData);
      }
      else if (msgRegInfo.type == SDM_REGINFO_CANCELLATION)
      {
         pthread_mutex_lock(&g_mutexPowerControllerData);

         g_bPowerControllerFound = false;

         pthread_mutex_unlock(&g_mutexPowerControllerData);
      }
   }
#endif // BUILD_FOR_PNPSAT
}


#ifdef BUILD_FOR_PNPSAT
void RequestRegPowerController()
{
  SDMReqReg msgRequest;

  msgRequest.destination = TaskManager;
  msgRequest.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
  msgRequest.id = REQREG_POWER_CONTROLLER_ID;
  strncpy(msgRequest.device, "PowerController", sizeof(msgRequest.device));
  strncpy(msgRequest.interface, "PowerStatusInterface", sizeof(msgRequest.interface));
  strncpy(msgRequest.item_name, "DeviceAsimReset", sizeof(msgRequest.item_name));

  msgRequest.Send();
}

/*
   Power cycle a PM node upon failure.
 */
void PowerCyclePmNode(const SDMComponent_ID& idPm)
{
  pthread_mutex_lock(&g_mutexPowerControllerData);

  if (g_bPowerControllerFound)
    {
      SDMCommand msgCommand;

      // Set the message id and the source of the command
      msgCommand.command_id = g_mmEndpointReset.getMsgID(COMMANDMSG);
      msgCommand.source = g_cidPowerController;

      // Set the sensor id of the pm node and the length of the message
      g_mmEndpointReset.setValue("SensorId", msgCommand, idPm.getSensorID());
      msgCommand.length = g_mmEndpointReset.getLength(COMMANDMSG);

      // Send the command
      msgCommand.Send();
    }
  else
    {
      debug_f(0, "%s -- Error, power controller has not been discovered.\n", __FUNCTION__);
    }

  pthread_mutex_unlock(&g_mutexPowerControllerData);
}
#endif // BUILD_FOR_PNPSAT

#ifdef PNP_BACKUP
void ForwardToBackup (char* buf, long length)
{
   list<SDMComponent_ID>::iterator it;
   /* send the buf to each of the backup TM's */
   for (it = Backup_TM_List.begin(); it != Backup_TM_List.end(); ++it)
   {
      in_addr in;
      in.s_addr = it->getAddress();
      char* ip = inet_ntoa(in);
      int port = (int)it->getPort();
      UDPsendto (ip, port, buf, length);
   }
}
#endif

/*
	Listener is the main message receiving thread for the TaskManager.  After a message is received, this routine spawns off a thread at
	the appropriate handler routine to handle the requests of the message.
	INPUTS:
		arg - Not used, exists to match the function signature for thread routines.
	RETURNS:
		void * - NULL
*/
void* Listener(void* arg)
{
	char buf[BUFSIZE];
	char result;
	bool m_dm_found;
	long length;
	pthread_t HandlerThread;
	pthread_attr_t attr;

#ifdef PNP_FAKE
	MessageManager* mm = (MessageManager*)arg;
#else
	MessageManager mm;
	if (!mm.Async_Init_Both(PORT_TM))
	  {
	    perror("Error initalizing message manager\n");
	  }
#endif

	SDMComHandle ComHandle;

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
	pthread_attr_setstacksize(&attr, THREAD_STACK_SIZE);

	while(1)
	{
#ifdef PNP_FAKE
		result = mm->BlockGetMessage(buf /* output */, length /* output */, ComHandle /* output */);
#else
		result = mm.BlockGetMessage(buf /* output */, length /* output */, ComHandle /* output */);
#endif
		pthread_mutex_lock(&perf_counter_mutex);
		total_recd++;
		prevsec_recd++;
		pthread_mutex_unlock(&perf_counter_mutex);

		pthread_mutex_lock(&dm_found_mutex);
		m_dm_found = dm_found;
		pthread_mutex_unlock(&dm_found_mutex);


		if(m_dm_found)
		{
		  //		   debug_f (1, "=== Received message: %c ===\n", buf[0]);
         switch(result)
         {
            case SDM_ACK:
               ackReceived = true;
               break;
            case SDM_Register:
               registerReceived = true;
               break;
            case SDM_ID:
               idReceived = true;
               break;
		       case SDM_RegPM:
  #ifdef PNP_BACKUP
		         ForwardToBackup(buf, length);
  #endif
		         RegPMHandler(buf);
		         break;

		       case SDM_ReqCode:
		         if(pthread_create(&HandlerThread,&attr,&ReqCodeHandler,memcpy(new char[length],buf,length)) != 0)
             {
                perror("Listener: Could not create ReqCodeHandler thread.\n");
             }
		         break;

		       case SDM_PostTask:
  #ifdef PNP_BACKUP
		         ForwardToBackup(buf, length);
  #endif
		         PostTaskHandler(buf);
		         break;

		       case SDM_RegInfo:
  #ifdef PNP_BACKUP
		         ForwardToBackup(buf, length);
  #endif
		         RegInfoHandler(buf);
		         break;

		       case SDM_Subreqst:
  #ifdef PNP_BACKUP
		         ForwardToBackup(buf, length);
  #endif
		         SubreqstHandler(buf);
		         break;

		       case SDM_Deletesub:
  #ifdef PNP_BACKUP
		         ForwardToBackup(buf, length);
  #endif
		         DeletesubHandler(buf);
		         break;

		       case SDM_Command:
  #ifdef PNP_BACKUP
		         ForwardToBackup(buf, length);
  #endif
		         if(pthread_create(&HandlerThread,&attr,&CommandHandler,memcpy(new char[length],buf,length)) != 0)
             {
                perror("Listener: Could not create CommandHandler thread.\n");
             }
		         break;

		       case SDM_Ready:
		         ReadyHandler(new HandlerArguments(buf, length, ComHandle.GetAddress()->sin_addr.s_addr, ntohs(ComHandle.GetAddress()->sin_port)));
		         break;

		       case SDM_TaskFinished:
  #ifdef PNP_BACKUP
		         ForwardToBackup(buf, length);
  #endif
		         TaskFinishedHandler(buf);
		         break;

		       case SDM_Task:
  #ifdef PNP_BACKUP
		         ForwardToBackup(buf, length);
  #endif
		         PMRunningTaskHandler(buf);
		         break;

		       case SDM_Serreqst:
		         SerreqstHandler(buf);
		         break;

		       case SDM_Kill:
		         KillHandler(buf);
		         break;
  #ifndef WIN32
		       case SDM_Heartbeat:
		         QueueHeartbeat(length, buf);
		         break;
  #endif


  #ifdef PNP_BACKUP
		       case SDM_DMLeader:
		         ReceiveLeader(buf);
		         break;

		       case SDM_Election:
		         exit(EXIT_FAILURE);
		         break;
  #endif

		       default:
		         debug_f(1,"Unexpected message received: %c\n", result);
		         break;
		     }
		}
		else
		{// Need to verify the DM
			if (result == SDM_Ready)
			{
				debug_f(3,"Ready message received\n");
				SDMReady in;
				in.Unmarshal(buf);
				if(in.destination.getPort() == PORT_DM)
				{
					DataManager.setAddress(in.destination.getAddress());
					debug_f(3,"DM address is 0x%lx:%hd %ld\n",DataManager.getAddress(), DataManager.getPort(), DataManager.getSensorID());
					// Address_TM = in.destination.getAddress();
					pthread_mutex_lock(&dm_found_mutex);
					dm_found = true;
					pthread_mutex_unlock(&dm_found_mutex);
				}
			}
		}
	}
	return NULL;
}

void QueueHeartbeat (long length, char buf[])
{
   SDMHeartbeat temp;
   temp.Unmarshal(buf);

#ifdef PNP_BACKUP
   if (Backup_TM_List.end() != find(Backup_TM_List.begin(), Backup_TM_List.end(), temp.source)) // found in the Backup TM List
   {
      debug_f (3, "Queuing heartbeat for main TM\n");
      /* Write the heartbeat message into the heartbeat pipe for the heartbeat thread */
      // First, write the length of the message
      if (write(tm_main_heartbeat_pipe[1], &length, sizeof(long)) < 0)
         printf("Could not sent heartbeat length to handler thread\n");
      // Write the actual message
      if (write(tm_main_heartbeat_pipe[1], buf, length) < 0)
         printf("Could not send heartbeat to handler thread\n");
   }
   else if (temp.source == mainTM)
   {
      debug_f (3, "Queuing heartbeat for backup TM\n");
      /* Write the heartbeat message into the heartbeat pipe for the heartbeat thread */
      // First, write the length of the message
      if (write(tm_back_heartbeat_pipe[1], &length, sizeof(long)) < 0)
         printf("Could not sent heartbeat length to handler thread\n");
      // Write the actual message
      if (write(tm_back_heartbeat_pipe[1], buf, length) < 0)
         printf("Could not send heartbeat to handler thread\n");
   }
   else
   {
#endif
      debug_f (3, "Queuing heartbeat for PM\n");
      /* Write the heartbeat message into the heartbeat pipe for the heartbeat thread */
      // First, write the length of the message
#ifndef __VXWORKS__
      if (write(pm_heartbeat_pipe[1], &length, sizeof(long)) < 0)
#else
	  if (write(pm_heartbeat_pipe, &length, sizeof(long)) < 0)
#endif
         printf("Could not sent heartbeat length to handler thread\n");
      // Write the actual message
#ifndef __VXWORKS__
      if (write(pm_heartbeat_pipe[1], buf, length) < 0)
#else
	  if (write(pm_heartbeat_pipe, buf, length) < 0)
#endif
         printf("Could not send heartbeat to handler thread\n");
#ifdef PNP_BACKUP
   }
#endif
}


/*
	The printResources routine outputs resource requirements is a human readable format
	INPUT:
		resources - bitwise or'd constant representing resource requirements
	RETURNS:
		void
*/
void printResources(const SDMTaskResources& resources)
{
	int os;		//contains the portion of resources pertaining to operating systems
	int mem;	//contains the portion of resources pertaining to memory requirements
	int arch;	//contains the portion of resources pertaining to architectures
	int pmid;	//contains the portion of resources pertaining to process manager id

	// mask of the various portions of resources
	os = resources.GetOs();
	mem = resources.GetMem();
	arch = resources.GetArch();
	pmid = resources.GetPreferredPmId();

	debug_f(3," resources: 0x%x pmid: 0x%x os: 0x%x mem: 0x%x arch: 0x%x\n",resources.GetUShort(),pmid,os,mem,arch);

	// print architecture requirements
	switch(arch)
	{
	case SDM_SPAU:
		printf("SPA-U");
		break;
	case SDM_INTEL:
		printf("Intel");
		break;
	case SDM_PPC_7404:
		printf("Power PC 7404");
		break;
	case SDM_PPC_755:
		printf("Power PC 755");
		break;
	case SDM_PPC_405:
		printf("Power PC 405");
		break;
	case SDM_MICROBLAZE:
		printf("Microblaze");
		break;
	case SDM_SPARC:
		printf("Sparc");
		break;
	default:
		printf("Unknown architecture");
		break;
	}

	printf (" machine, running ");

	// print os requirements
	switch(os)
	{
	case SDM_LINUX24:
		printf("Linux 2.4");
		break;
	case SDM_LINUX26:
		printf("Linux 2.6");
		break;
	case SDM_WIN32:
		printf("Win32");
		break;
	break;
	case SDM_VXWORKS:
		printf("VxWorks");
		break;
	default:
		printf("Unknown OS");
		break;
	}
	printf(" with at least ");
	// print memory requirements
	switch(mem)
	{
	case SDM_MEM32:
		printf("32 Mb RAM");
		break;
	case SDM_MEM64:
		printf("64 Mb RAM");
		break;
	case SDM_MEM128:
		printf("128 Mb RAM");
		break;
	case SDM_MEM256:
		printf("256 Mb RAM");
		break;
	case SDM_MEM512:
		printf("512 Mb RAM");
		break;
	case SDM_MEM1024:
		printf("1024 Mb RAM");
		break;
	default:
		printf("Unknown memory");
		break;
	}
	printf("\n");
}

/*
	The SendCode routine sends executable code to a PM
	INPUT:
		filename - the name of the file to be sent
	RETURNS:
		void
*/
void SendCode (char* buf)	// sends no file on failure
{	int fd;					//file descriptor to the code to be sent
	int length;				//length of code packet to send
	SDMError err;				//error message
	char file[MAX_FILENAME_SIZE];
	int max_code_size;
	unsigned short sequence = 0;
	unsigned short n_messages = 0;
	unsigned short seq_to_send = 0;
	SDMCode msgCode;
	SDMReqCode msgRequest;
	struct stat file_stats;
	if (msgRequest.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMReqCode message.\n");
		return;
	}
	MessageReceived(&msgRequest);

	debug_f(2,"PM has requested code for %s.\n",msgRequest.filename);
	memset(file,0,MAX_FILENAME_SIZE);
	memcpy(file,msgRequest.filename,strlen(msgRequest.filename)+1);
	max_code_size = sizeof(msgCode.code);
	//
	// Determine which file version is to be sent
	char strFullFilePath[256];
	switch (msgRequest.version)
	  {
	  case TASK_LOCATION_PRIMARY:
	    snprintf(strFullFilePath, sizeof(strFullFilePath), "%s/%s",
		     STR_TASK_LOCATION_PRIMARY, msgRequest.filename);
	    debug_f(2, "  Using primary location %s to open file.\n", strFullFilePath);
	    break;
	  case TASK_LOCATION_TEMPORARY:
	    snprintf(strFullFilePath, sizeof(strFullFilePath), "%s/%s",
		     STR_TASK_LOCATION_TEMPORARY, msgRequest.filename);
	    debug_f(2, "  Using temporary location %s to open file.\n", strFullFilePath);
	    break;
	  case TASK_LOCATION_BACKUP:
	    snprintf(strFullFilePath, sizeof(strFullFilePath), "%s/%s",
		     STR_TASK_LOCATION_BACKUP, msgRequest.filename);
	    debug_f(2, "  Using backup location %s to open file.\n", strFullFilePath);
	    break;
	  default:
	    strcpy(strFullFilePath, msgRequest.filename);
	    debug_f(2, "  Using default location to open file.\n");
	  }

#ifdef __VXWORKS__
	strcat(strFullFilePath, ".vxe");
#endif

	// open filename for reading
#ifdef WIN32
	if ((fd = open(strFullFilePath, O_RDONLY | _O_BINARY)) < 0)
#else
	  if ((fd = open(strFullFilePath, O_RDONLY)) < 0)
#endif
	{
		printf("Error opening file: %s for code transfer\n", strFullFilePath);
		err.error = SDM_ERROR_CODE_NOT_FOUND;
		strncpy(err.error_msg, msgRequest.filename, sizeof(err.error_msg));
		err.SendTo(msgRequest.source);
		MessageSent(&err);
	}
	else
	{
#ifdef WIN32
		pthread_mutex_lock(&code_transfer_mutex);
#endif
		/*Get file size*/
#ifdef __VXWORKS__
		if(stat(strFullFilePath, &file_stats) < 0)
		{
			printf("Error statting file: %s\n",strerror(errno));
		}
		int temp = (int)file_stats.st_size;
		n_messages = (unsigned short)(temp/max_code_size);		
		if ((temp/((double)max_code_size)) > ((double)n_messages))
		{
			n_messages++;
		}
#else
		if(fstat(fd, &file_stats) < 0)
		{
			printf("fstat() return an error: %s\n", strerror(errno));
		}
		n_messages = (unsigned short)(file_stats.st_size/max_code_size);		
		if ((file_stats.st_size/((double)max_code_size)) > ((double)n_messages))
			n_messages++;
#endif	
		msgCode.num_segments = n_messages;
		/*If the PM is rerequesting a specified sequence number*/
		if (msgRequest.seq_num > 0)
		{
			debug_f(2,"  (Rerequest for packet %d)\n", msgRequest.seq_num);
			seq_to_send = msgRequest.seq_num;
			/*Seek to the sequence number*/
			lseek(fd, (seq_to_send-1)*max_code_size, SEEK_SET);
			length = read(fd, &msgCode.code, max_code_size);

			if (length > 0)
				msgCode.code_length = length;
			msgCode.seq_num = seq_to_send;
			msgCode.num_segments = n_messages;
			strcpy(msgCode.filename, file);
			msgCode.SendTo(msgRequest.source);
			MessageSent(&msgCode);
			close(fd);
		}
		/*If this is a code request for the entire file*/
		else
		{
			lseek(fd, 0, SEEK_SET);
			length = read (fd, &msgCode.code, max_code_size);
			if(length > 0)
			{
				msgCode.code_length = length;
			}
			while (length > 0)
			{
				// send code packet
				msgCode.seq_num = ++sequence;
				msgCode.num_segments = n_messages;
				strcpy(msgCode.filename, file);
#ifdef WIN32
				Sleep(500);
#endif
				msgCode.SendTo(msgRequest.source);
				MessageSent(&msgCode);

				debug_f(2,"Sending code message for %s of code length %d with checksum %x.\n",file,length,msgCode.c_sum);
				
				// read next packet
				length = read (fd, &msgCode.code, max_code_size);
				if(length > 0)
				{
					msgCode.code_length = length;
				}
			}
			debug_f(2,"file sent.\n");
			// close file
			close(fd);
		}
#ifdef WIN32
		pthread_mutex_unlock(&code_transfer_mutex);
#endif
	}
}

/*
	The PostTask routine queues a task for execution
	INPUT:
		buf - the SDMPostTask message
	RETURNS:
		void
*/
void PostTask (char *buf)
{
	Task task;
	SDMPostTask msgPostTask;
	// unmarshal message
	if (msgPostTask.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMPostTask message.\n");
		return;
	}
	MessageReceived(&msgPostTask);

	// Fill the task info
	task.SetTask(PENDING, msgPostTask.priority, 0, msgPostTask.resources,
		     msgPostTask.filename, msgPostTask.sched_interval,
		     msgPostTask.mode, msgPostTask.version);

	pthread_mutex_lock(&list_mutex);
	taskList.AddTo(task);
	debug_f(4, "Posting task.\n");
	if (debug >= 4)
	{
		taskList.PrintList();
	}
	pthread_mutex_unlock(&list_mutex);

	if (debug >= 2)
	{
		debug_f(2,"%s task posted requiring a ",task.filename);
		printResources(task.resources);
		debug_f(2,". \n");
	}
#ifdef PNP_BACKUP
	if (!isBackup)
	{
	  PublishTaskQueuedMessage(task.filename);
	}
#else
	PublishTaskQueuedMessage(task.filename);
#endif
}
/*
	VerifyDM verifies the existence of the DataManager.  The DM is necessary for the TaskManager to carry out its needed operations.
	The DataManager's response to the SDMReady message is received in the Listener routine.
	INPUTS:
		None.
	RETURNS:
		void
*/
void VerifyDM(void)
{
	bool msg_rcvd = false;
	SDMReady msgReadyOut;
	msgReadyOut.destination.setPort(PORT_TM);
	msgReadyOut.destination.setAddress(TaskManager.getAddress());
	//msgReadyOut.destination.setAddress(DataManager.getAddress());
	printf("Searching for DM .");
	do
	{
		pthread_mutex_lock(&perf_counter_mutex);
		total_sent++;
		prevsec_sent++;
		pthread_mutex_unlock(&perf_counter_mutex);
		// Ready messages sent via broadcast to find the DM
		// TODO:  need to test broadcast under uclinux!
		//msgReadyOut.SendBCast(DataManager.getAddress(), PORT_DM);
		msgReadyOut.Send(DataManager);
		putchar('.');
		//fflush(NULL);
		usleep(500000);
		pthread_mutex_lock(&dm_found_mutex);
		msg_rcvd = dm_found;
		pthread_mutex_unlock(&dm_found_mutex);
	} while(!msg_rcvd);
	printf("DM found\n");
}

/*
	InitialStartUp parses through the sdm.config file found in the current directory to startup any tasks specified in that file.
	INPUTS:
		None.
	RETURNS:
		void
*/
void InitialStartUp(void)
{
	SDMPostTask msgTask;
	char buf[256];
	int fd = 0;
	int value;
	unsigned int i = 0;
#ifndef __VXWORKS__
	char file[65536];
#else
	char file[32768];
#endif
	int cont = 0;
	char filename[MAX_FILENAME_SIZE];
	int name = 0;
	unsigned int resource = 0;
	int start = 0;
	int end = 0;
	int tempi = 0;
	int timeout = 0;
	int mode = 0;
	int mem = 0;
	char memstring[8];

	// Open the SDM.config file
	fd = open(FILE_SDM_TASK_LIST, O_RDONLY);
	if(fd == -1)
	{
		perror("SDM task list was unable to be opened! ");
		printf("Could not open \"%s\"\n", FILE_SDM_TASK_LIST);
		return;
	}
#ifndef __VXWORKS__
	value = read(fd,file,65535);
#else
	value = read(fd,file,32767);
#endif
	close(fd);
  if(value < 0)
  {
    printf("Could read from file \"%s\"\n", FILE_SDM_TASK_LIST);
    return;
  }
	file[value] = '\0';
	
	bool TagClosed = false, inComment = false;;
	const unsigned int FILE_LENGTH = (int)strlen(file);
	for(i = 0; i < FILE_LENGTH; i++)
	{
		if(strncmp(&file[i],"<!--",4) == 0)
		{
			i+= 4;
			inComment = true;
			char* cp = strstr(&file[i],"-->");
			if ( cp == NULL )
			{
				printf("%s doesn't close the comment started at char pos %d\n",
					FILE_SDM_TASK_LIST,i);
				return;
			}
			i = (int)(cp-file)+3;
		}
		//if(strncmp(&file[i],"Device",6) == 0)
		//{
		//	// Don't do anything with devices
		//}
		if(strncmp(&file[i],"Application",11) == 0)
		{
			cont = 1;
			name = 0;
			resource = 0;
			timeout = 0;
			mode = 0;
			memset(filename,0,sizeof(filename));
			i+=11;
		}
		if(strncmp(&file[i],"pathOnSpacecraft",16) == 0)
		{
			name = 1;
			i+=16+1;
			while(file[i] != '"')
			{
				if(file[i] == '\0')
					return;
				i++;
			}
			i++;
			// Get the name of the executable
			start = i;
			while(file[i] != '"')
			{
				i++;
			}
			end = i;
			if(end - start > MAX_FILENAME_SIZE)
				memcpy(filename,&file[start],MAX_FILENAME_SIZE);
			else
				memcpy(filename,&file[start],(end-start));
			debug_f(3,"Start of filename is %d and end is %d with filename %s\n",start,end,filename);
		}
		if(strncmp(&file[i],"architecture",12) == 0)
		{
			i+=12+1;
			while(file[i] != '"')
			{
				if(file[i] == '\0')
					return;
				i++;
			}
			i++;
			if(strncmp(&file[i],"SPAU",4) == 0)
				resource |= SDM_SPAU;
			else if(strncmp(&file[i],"Intel",5) == 0)
				resource |= SDM_INTEL;
			else if(strncmp(&file[i],"PPC7404",7) == 0)
				resource |= SDM_PPC_7404;
			else if(strncmp(&file[i],"PPC755",6) == 0)
				resource |= SDM_PPC_755;
			else if(strncmp(&file[i],"PPC405",6) == 0)
				resource |= SDM_PPC_405;
			else if(strncmp(&file[i],"Microblaze",10) == 0)
				resource |= SDM_MICROBLAZE;
			else if(strncmp(&file[i],"Sparc",5) == 0)
				resource |= SDM_SPARC;
			cont |= 0x02;
		}
		if(strncmp(&file[i],"memoryMinimum",13) == 0)
		{
			i+=13+1;
			while(file[i] != '"')
			{
				if(file[i] == '\0')
					return;
				i++;
			}
			i++;
			tempi = i;
			while(file[i] != '"')
			{
				if(file[i] == '\0')
					return;
				i++;
			}
			memset(memstring,0,8);
			memcpy(memstring,&file[tempi],i-tempi);
			mem = atoi(memstring);
			if(mem <= 32)
				resource |= SDM_MEM32;
			else if(mem <= 64)
				resource |= SDM_MEM64;
			else if(mem <= 128)
				resource |= SDM_MEM128;
			else if(mem <= 256)
				resource |= SDM_MEM256;
			else if(mem <= 512)
				resource |= SDM_MEM512;
			else if(mem <= 1024)
				resource |= SDM_MEM1024;
			cont |= 0x04;
		}
		if(strncmp(&file[i],"operatingSystem",15) == 0)
		{
			i+=15+1;
			while(file[i] != '"')
			{
				if(file[i] == '\0')
					return;
				i++;
			}
			i++;
			if(strncmp(&file[i],"Win32",5) == 0)
				resource |= SDM_WIN32;
			else if(strncmp(&file[i],"Linux24",7) == 0)
				resource |= SDM_LINUX24;
			else if(strncmp(&file[i],"Linux26",7) == 0)
				resource |= SDM_LINUX26;
			else if(strncmp(&file[i],"VxWorks",7) == 0)
				resource |= SDM_VXWORKS;
			cont |= 0x08;
		}
		if (cont == 15 && name == 1)
		{
			if (file[i] == '>')
				TagClosed = true;
		}
		if (strncmp(&file[i], "preferredPMNodeID", 17) == 0)
		{
			i+=17+1;
			while (file[i] != '"')
			{
				if (file[i] == '\0')
					return;
				i++;
			}
			i++;
			char strNodeId[8];
			int Offset = 0;
			while (file[i + Offset] != '"')
			{
				strNodeId[Offset] = file[i + Offset];
				Offset++;

				// This should not happen
				if (Offset == sizeof(strNodeId) - 1)
					break;
			}
			strNodeId[Offset] = '\0';

			int ID = atoi(strNodeId);
			if (ID < 1 || ID > 255)
			{
				debug_f(0, "Invalid preferredPMNodeID value in %s.\n", FILE_SDM_TASK_LIST);
				continue;
			}
			resource |= PM_ID(atoi(strNodeId));
		}
		if (strncmp(&file[i], "scheduleTimeout", 15) == 0)
		{
			i+=15+1;
			while (file[i] != '"')
			{
				if (file[i] == '\0')
					return;
				i++;
			}
			i++;
			char strTimeout[8];
			int Offset = 0;
			while (file[i + Offset] != '"')
			{
				strTimeout[Offset] = file[i + Offset];
				Offset++;

				// This should not happen
				if (Offset == sizeof(strTimeout) - 1)
					break;
			}
			strTimeout[Offset] = '\0';
			timeout = atoi(strTimeout);
		}
		if (strncmp(&file[i], "executionMode", 13) == 0)
		  {
			i+=13+1;
		    while (file[i] != '"')
		      {
				if (file[i] == '\0')
				  {
					return;
				  }
				i++;
		      }

		    i++;
		    if (strncmp(&file[i], "alwaysRunning", 13) == 0)
		      {
			mode = MODE_ALWAYS_RUNNING;
		      }
		  }
		if(cont == 15 && name == 1 && TagClosed == true)
		{
			msgTask.resources = resource;
			msgTask.sched_interval = timeout;
			msgTask.mode = mode;
			strncpy(msgTask.filename, filename, MAX_FILENAME_SIZE);
			msgTask.Marshal(buf);
			PostTask(buf);
			cont = 0;
			name = 0;
			TagClosed = false;
		}
	}
	return;
}

/*
	MessageRecieved logs any messages received from the TaskManager (if logging is enabled).  This function should be called any
	time an SDM* message is received within the TaskManager.
	INPUTS:
		msg - The message to be logged.
	RETURNS:
		void
*/
void MessageReceived(SDMmessage *msg)
{
	pthread_mutex_lock(&log_service_mutex);
	if (!log_service.IsEmpty())
		log_service.MessageReceived(msg);
	pthread_mutex_unlock(&log_service_mutex);
}

/*
	MessageSend logs any message sent from the TaskManager (if logging is enabled).  This routine also increments the TaskManager's
	messaging performance counters.  This function should be called any time an SDM* message is sent within the TaskManager.
	INPUTS:
		msg - The message to be logged.
	RETURNS:
		void
*/
void MessageSent(SDMmessage *msg)
{
	/*Increment performance counters*/
	pthread_mutex_lock(&perf_counter_mutex);
	total_sent++;
	prevsec_sent++;
	pthread_mutex_unlock(&perf_counter_mutex);
	/*Log the message, if the logger is enabled*/
	pthread_mutex_lock(&log_service_mutex);
	if (!log_service.IsEmpty())
		log_service.MessageSent(msg);
	pthread_mutex_unlock(&log_service_mutex);
}

// --------------------------------------------------------------------
// ------------------FUNCTIONS PERTAINING TO BACKUP--------------------
// --------------------------------------------------------------------

#ifdef PNP_BACKUP

#ifdef PNP_FAKE
/*
 * sendIMA sends a message to the NetworkManager. This should only be called if the TaskManager is a backup and the main has gone down.
 */
void sendIMA (void)
{
   cout << "Sending IMA\n";

   // send message to NM
   SDMDMLeader ima;
   ima.source = TaskManager;
   ima.SendTo(NetworkManager);

   sleep (5); // wait for election to finish
}
#endif

#ifdef BUILD_FOR_PNPSAT
void RequestDMInfo (void)
{
   struct hostent *he;
   unsigned long addr;

   while ((he=gethostbyname("datamanager.spacewire")) == NULL)
   {
      sleep(1);
   }
   memcpy(&addr, he->h_addr, sizeof(addr));

   in_addr in;
   in.s_addr = addr;

   DataManager.setAddress(addr);
   DataManager.setPort(PORT_DM);
}

bool AmIBackup (void)
{
   cout << "Determining leader/backup status\n";

   SendIMA(SdmImaTm, debug);
   sleep(5);  //Wait 5 seconds while NM resolves election

   struct hostent *he;
   unsigned long addr;

   he=gethostbyname("taskmanager.spacewire");
   memcpy(&addr, he->h_addr, sizeof(addr));

   if (addr == TaskManager.getAddress())
   {
      return false;
   }

   mainTM.setAddress(addr);
   mainTM.setPort(PORT_TM);

   // alert Main TM that I am a backup

   return true;
}

#endif

#ifdef PNP_FAKE
void RequestDMInfo (MessageManager* mm)
{
   cout << "Requesting DM info from NM\n";
   char buf[BUFSIZE];
   char flag = '\0';
   // Request DM info from NM
   SDMDMLeader req;
   req.source.setAddress(Address_TM);
   req.source.setPort(PORT_TM);
   req.running_flag = 'd';

   req.SendTo(NetworkManager);

   while (flag != 'd')
   {
      mm->BlockGetMessage(buf);

      SDMDMLeader temp;
      temp.Unmarshal(buf);
      flag = temp.running_flag;

      ReceiveLeader(buf);
   }
}

void AmIBackup (MessageManager* mm)
{
   cout << "Determining leader/backup status\n";
   char buf[BUFSIZE];

   SDMDMLeader ima;

   ima.source = TaskManager;
   ima.SendTo(NetworkManager);

   mm->BlockGetMessage(buf);

   ReceiveLeader(buf);
}
#endif

void TakeOverLeadPosition (void)
{
   // alert DM
   SDMReady msg;
   msg.destination = TaskManager;
   msg.SendTo(DataManager);

   // alert all PM's
   SDMDMLeader pmMsg;
   pmMsg.source = TaskManager;
   pmMsg.running_flag = 't';

   pmList.SendToAll(pmMsg);

   pmList.PrintList();
   taskList.PrintList();
}

void VerifyNewDM(char *sender_buf)
{
	SDMComponent_ID tempDM;
	tempDM.Unmarshal(sender_buf, 0);
	tempDM.setPort(3504);
	bool msg_rcvd = false;
	SDMReady msgReadyOut;
	msgReadyOut.destination.setPort(PORT_TM);
	msgReadyOut.destination.setAddress(TaskManager.getAddress());
	printf("Searching for DM at: 0x%lx port: %u.", tempDM.getAddress(), tempDM.getPort());
	fflush(NULL);
	do
	{
		pthread_mutex_lock(&perf_counter_mutex);
		total_sent++;
		prevsec_sent++;
		pthread_mutex_unlock(&perf_counter_mutex);
		msgReadyOut.SendTo(tempDM);
		putchar('.');
		fflush(NULL);
		usleep(500000);
		pthread_mutex_lock(&dm_found_mutex);
		msg_rcvd = dm_found;
		pthread_mutex_unlock(&dm_found_mutex);
	} while(!msg_rcvd);
	printf("DM found\n");
	DataManager.setAddress(tempDM.getAddress());
}

void ReceiveLeader (char* buf)
{
   SDMDMLeader temp;
   temp.Unmarshal(buf);

   debug_f (1, "Running flag is %c\n", temp.running_flag);

   cout << "Running flag == " << temp.running_flag << endl;

   switch (temp.running_flag)
   {
      case '0':
         // I'm the leader now
         isBackup = false;
         debug_f(1, "I'm now the main TM\n");
         TakeOverLeadPosition();
         break;

      case '1':
         debug_f(1, "I've been assigned as backup\n");
         debug_f(1, "Alerting leader to my presence\n");
         mainTM = temp.source; // using destination to pass the mainTM's comp id
         temp.source = TaskManager;
         temp.running_flag = '2';
         temp.SendTo (mainTM);
         break;

      case '2':
         debug_f(1, "Adding 0x%lx as backup\n", temp.source.getAddress());
         Backup_TM_List.push_back(temp.source);
         break;

      case 'd':
         debug_f(1, "Received %lu from NM as DM's address\n", temp.source.getAddress());
         cout << "Received " << temp.source << " from NM as DM's address" << endl;
         DataManager.setAddress(temp.source.getAddress());
         DataManager.setPort(PORT_DM);
         break;

      default:
         break;
   }
}

/*
	This thread runs for the life of the TM instance.  This thread is responsible for sending and receiving SDMHeartbeat messages to and
	from all registered PM nodes.  Also, if a heartbeat isn't responded to, the this thread will remove it from the registered PM
	list, making the assumption that the PM module has failed.

	This thread runs differently if you are a backup TM. Backup's shouldn't be heartbeating the PM's, instead they should heartbeat the main
	TM.

	INPUTS:
		arg - Not used.
	RETURNS:
		void * - Always NULL.
*/

void* TMHeartbeat (void* arg)
{
  sleep(5);

  struct pollfd tm_back_poll_fd;		         //poll struct
  tm_back_poll_fd.events = POLLIN | POLLPRI;
  tm_back_poll_fd.fd = tm_back_heartbeat_pipe[0];

  struct pollfd tm_main_poll_fd;		         //poll struct
  tm_main_poll_fd.events = POLLIN | POLLPRI;
  tm_main_poll_fd.fd = tm_main_heartbeat_pipe[0];

  int poll_res = 0;
  SDMHeartbeat msgHeartbeat;	            //heartbeat message to send out
  SDMHeartbeat msgHeartbeatReceived;     //heartbeat message to receive
  char buf[BUFSIZE];		               //buffer for receiving message
  long length;			                  //Length of the heartbeat message being read

  msgHeartbeat.source = TaskManager;

  while (1)
    {
      if (isBackup)
	{
	  bool mainIsAlive = true;
	  SDMHeartbeat pulse;
	  pulse.source = TaskManager;

	  while (mainIsAlive)
	    {
	      cout << "Sending heartbeat to leader TM at " << mainTM << endl;
	      cout.flush();
	      // send heart beat
	      pulse.SendTo(mainTM);

	      // poll for response, with a 5 second timeout
	      poll_res = poll (&tm_back_poll_fd,1,5000);

	      if (poll_res < 0)
		{
		  perror ("Heartbeat: Poll error.\n");
		}
	      else if (poll_res == 0) // when poll returns a zero it means there was a time out
		{
		  printf ("Main task manager not responding, sending IMA message\n");
		  mainIsAlive = false;
		}
	      else // clear the pipe by reading the message
		{
		  // Read message length from the pipe
		  read(tm_back_heartbeat_pipe[0], &length, sizeof(long));

		  // Read message from pipe
		  if (length > 0 && length < BUFSIZE)
		    {
		      read(tm_back_heartbeat_pipe[0], buf, length);

		      SDMHeartbeat temp;
		      temp.Unmarshal(buf);
		    }
		}

	      if (mainIsAlive)
		{
		  // only send heart beats every 5 seconds
		  sleep(5);
		}
	    }


#ifdef PNP_FAKE
	  sendIMA();
#endif

#ifdef SEND_IMA
	  if (spacewire)
	    {
	      SendIMA(ImaTm, debug);
	    }
#endif
	}
      else
	{
	  while (1)
	    {
	      //respond to any heart beats we have received while sleeping
	      if ((poll_res=poll(&tm_main_poll_fd,1,1000)) < 0)
		{
		  perror ("PMHeartbeat: Poll error.\n");
		  break;
		}
	      else if (poll_res > 0)
		{
		  // Read message length from the pipe
		  read(tm_main_heartbeat_pipe[0], &length, sizeof(long));

		  // Read message from pipe
		  if (length > 0 && length < BUFSIZE)
		    {
		      read(tm_main_heartbeat_pipe[0], buf, length);

		      // send a reply

		      SDMHeartbeat temp;
		      temp.Unmarshal (buf);

		      SDMComponent_ID backup;
		      backup = temp.source;

		      temp.source = TaskManager;
		      temp.SendTo(backup);
		      cout << "Replied to heartbeat from " << backup << endl;
		    }
		}
	    }
	}
    }
  return NULL;
}

#endif // ifdef PNP_BACKUP
