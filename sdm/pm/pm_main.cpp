//*********************************************************************
//Process Manager Module of the SDM
//
//This source is compilable on both a Linux and a Win32 architecture.  Throughout, there are
//compile switches as #ifdef ... #endif which conditionally add or remove code based on the build.
//The way by which Windows and Linux handle forking/execing processes and signal handling is
//very different, becuase of this there are different versions of a couple of function for each.
//*********************************************************************
#include "pm_main.h"
#include "pmxTEDS.h"
#include "PendingTask.h"
#include <errno.h>
#include "../common/Time/SDMTime.h"
#include "../common/semaphore/semaphore.h"

#ifndef WIN32
#  include <net/if.h>
#  include <netdb.h>
#endif

#ifdef __VXWORKS__
#include <rtpLib.h>
#include <taskLib.h>
#include <hostLib.h>
#include <pipeDrv.h>
#include <usrFsLib.h>
#endif

#ifdef BUILD_FOR_IDS
#  include "pm_ids.h"
#else
#  include "pm.h"
#endif

using namespace std;

int debug = 0;
bool spacewire = false;
bool merged = false;
char* workingDirectory = "./Logs";

unsigned int total_recd = 0;		// message counter for total received for life of pm
unsigned int prevsec_recd = 0;		// message counter for total received previous second
unsigned int total_sent = 0;		// message counter for total sent for life of pm
unsigned int prevsec_sent = 0;		// message counter for total sent previous second
pthread_mutex_t perfCounterMutex = PTHREAD_MUTEX_INITIALIZER;

SDMMessage_ID tm_mode_msg_id;
unsigned char tm_mode = 0;
SDMComponent_ID tm_mode_source;
SubscriptionManager subscriptions;
pthread_mutex_t subscriptionsMutex = PTHREAD_MUTEX_INITIALIZER;

unsigned long Address_PM = inet_addr("127.0.0.1");
bool bgTMDetected = false;		// Bool determining whether the TM has already been found

vector<PendingTask> taskQueue;
pthread_mutex_t taskQueueMutex = PTHREAD_MUTEX_INITIALIZER;

vector<code_recv> codeReceivers;	// Vector of all tasks currently doing a code transfer
pthread_mutex_t codeReceiversMutex = PTHREAD_MUTEX_INITIALIZER;

PMProcessList runningTaskList;
pthread_mutex_t taskListMutex = PTHREAD_MUTEX_INITIALIZER;

MessageLogger log_service;		// Message Logger utility

const unsigned int THREAD_STACK_SIZE = 256000;

int g_iPMListenSock = IP_SOCK_INVALID;

bool ackReceived = false;
bool registerReceived = false;
bool idReceived = false;

#ifdef __uClinux__
SDMTaskResources g_TaskResources(SDM_LINUX26 | SDM_MICROBLAZE | SDM_MEM128);
#elif WIN32
SDMTaskResources g_TaskResources(SDM_WIN32 | SDM_INTEL | SDM_MEM1024);
#else
SDMTaskResources g_TaskResources(SDM_LINUX26 | SDM_INTEL | SDM_MEM128);
#endif
Sem g_semLaunchTask(1);

int main(int argc,char** argv)
{
	char* LOCAL_ADDR = "127.0.0.1";
	SDMxTEDS pm_xteds;
	SDM_TimeInit();

	bool TM_set = false;
	//parse command line options
	while(1)
	{
#ifndef __VXWORKS__
		static struct option long_options[] = {
			{"dm",1,0,'d'},
			{"tm",1,0,'t'},
			{"help",0,0,'h'},
			{"debug",1,0,'g'},
			{"spacewire",1,0,'s'},
			{"nodeid",1,0,'n'},
			{"merged",1,0,'m'},
			{"workingDirectory",1,0,'w'},
			{0,0,0,0} };
		int option_index;
		int option = getopt_long(argc,argv,"g:s:hn:d:t:n:mw:", long_options, &option_index);
#else
		int option = getopt(argc,argv,"g:s:hn:d:t:n:mw:");
#endif
		
		if(option==-1)
			break; //no more options
		switch(option)
		{
			case 'd':
				//DM address no longer needed, it is acquired by the TM
				break;
			case 'g':
				debug = atoi(optarg);
				break;
			case 'h':
				printf("Usage: pm [options]\n");
				printf("Options:\n");
				//printf("--dm=<addr> -d<addr>\t\t\tSet IP address of Data Manager\n\t\t\t\t\t<addr> should be given in dot number notation\n");
				printf("--debug=<level> -g<level>\t\tSet level of debug messages\n\t\t\t\t\t0=none, 1=moderate, 2=verbose\n");
				printf("--tm=<addr> -t<addr>\t\t\tSet IP address of Task Manager\n\t\t\t\t\t<addr> should be given in dot number notation\n");
				printf("--help -h\t\t\t\tDisplay this information\n");
				printf("--merged -m\t\t\tMerge the output of all child processes with pm's output. Default is to log them\n");
				printf("--nodeid=<id> -n<id>\t\t\tSet this node's id for preferred PM scheduling from the TM.\n");
				printf("--spacewire=<bool> -s<bool>\t\tEnable or disable SpaceWire mode\n");
				printf("--workingDirectory=<path> -w<path>\t\tLogging directory. Defaults to ./'Logs'\n");
				return 0;
			case 'm':
			  merged = true;
			  break;
			case 'n':
			{
				int iNodeId = atoi(optarg);
				if (iNodeId < 1 || iNodeId > 255)
				{
					debug_f(0, "Invalid nodeid specified on command-line of %d\n", iNodeId);
					break;
				}
				g_TaskResources.SetPreferredPmNodeId(static_cast<unsigned short>(iNodeId));
				break;
			}
			case 's':
			  spacewire = !!atoi(optarg);
			  break;
			case 't':
			  // If spacewire mode is enabled, this setting will have no effect
				if(strcmp(optarg,"local")==0)
				{
					TaskManager.setAddress(inet_addr(LOCAL_ADDR));
					TaskManager.setPort(PORT_TM);
				}
				else
				{
					TaskManager.setAddress(inet_addr(optarg));
					TaskManager.setPort(PORT_TM);
				}
				TM_set = true;
				break;
			case 'w':
			  workingDirectory = strdup(optarg);
			  break;
			case '?':
				break;
		}
	}
	
	if ( spacewire )
		debug_f(1, "Running in SpaceWire mode\n");

	if(!TM_set && !spacewire)
	{
		TaskManager.setAddress(inet_addr(LOCAL_ADDR));
		TaskManager.setPort(PORT_TM);
	}
	else if(spacewire)
	  {
#ifndef __VXWORKS__		
		unsigned long addr;
		struct hostent *he;	    
	    while ((he=gethostbyname("taskmanager.spacewire")) == NULL) {
	      debug_f(1, "gethostname failed for taskmanager.spacewire. Retrying in 5 secs\n");
	      sleep(5);
	    }
	    memcpy(&addr, he->h_addr, sizeof(addr));
#else
		int addr;
		while ((addr = hostGetByName("taskmanager.spacewire")) == ERROR)
		{
			debug_f(1, "gethostname failed for taskmanager.spacewire. Retrying in 5 secs\n");
			sleep(5);
		}
#endif

	    TaskManager.setAddress(addr);
	    TaskManager.setPort(PORT_TM);
	    TM_set = true;
	  }

	//output version information (including debug message style)
	printf ("PM (Process Manager) %s\n",SDM_VERSION);
	switch(debug)
	{
		case 1:
		printf("PM in debug 1 (moderate).\n");
		break;
		case 2:
		printf("PM in debug 2 (verbose).\n");
		break;
		case 3:
		printf("PM in debug 3 (verbose w/message echo).\n");
		break;
	}
	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);
	pthread_attr_setstacksize(&threadAttr, THREAD_STACK_SIZE);
	pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);
#ifndef WIN32
	//All subsequent threads block the below signals so they aren't interrupted after calling pthread_mutex_lock()
	//this avoids a deadlock situation by dedicating a single thread for signal handling.

	sigset_t signal_set;
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGALRM);
	sigaddset(&signal_set, SIGINT);
	//sigaddset(&signal_set, SIGSEGV);
	sigaddset(&signal_set, SIGCHLD);
	pthread_sigmask(SIG_BLOCK, &signal_set, NULL);

	pthread_t SigHandlerThread;
	if (0 != pthread_create(&SigHandlerThread, &threadAttr, &SigHandler, NULL))
	{
		printf("Error spawning signal handler thread.\n");
		return -1;
	}
#else	//WIN32 case
	// Start a separate thread for SigChldHandling
	pthread_t SigHandlerThread;
	if (0 != pthread_create(&SigHandlerThread, &threadAttr, &SigChldThreadFunc, NULL))
	{
		printf("Error spawning SigChld thread.\n");
		return -1;
	}
	signal(SIGINT, *SigIntHandler);
	sigset(SIGALRM, SigAlrmHandler);
#endif
	pthread_t HeartbeatMonitorThread;
	if (0 != pthread_create(&HeartbeatMonitorThread, &threadAttr, &TaskHeartbeatMonitor, NULL))
	{
		printf("Error spawning heartbeat handler thread.\n");
		return -1;
	}

	if (VerifyTM() == -1)
		return -1;

   pthread_attr_t ListenThreadAttr;
	pthread_attr_init(&ListenThreadAttr);
	pthread_attr_setstacksize(&ListenThreadAttr, THREAD_STACK_SIZE);
   pthread_t ListenerThread;
   if (0 != pthread_create(&ListenerThread, &ListenThreadAttr, &Listener, NULL))
	{
		perror("Could not create Listen thread.\n");
		return -1;
	}

   SDMHello hello;
   hello.source.setPort(PORT_PM);
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


	pm_xteds.source.setSensorID(1);
	pm_xteds.source.setPort(PORT_PM);
	strcpy(pm_xteds.xTEDS, xTEDS);
	MessageSent(&pm_xteds);
	pm_xteds.Send();

   while (!idReceived)
   {
      usleep(10000);
   }
   debug_f(1, "SDMID received\n");

	RegisterPM();

   pthread_join(ListenerThread, NULL);

	return 0;
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


//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//					START SIGNAL HANDLING FUNCTIONS
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifdef WIN32
void* SigChldThreadFunc(void* args)
{
	while (1)
	{
		SigChldHandler(SIGCHLD);
		usleep(10000);
	}
}
#endif
#ifndef WIN32
void* SigHandler(void* args)
{
	sigset_t signal_set;
	sigset_t pending_set;
	int sig;
  int sig_pending;
	
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGINT);
	sigaddset(&signal_set, SIGALRM);
	sigaddset(&signal_set, SIGSEGV);
	sigaddset(&signal_set, SIGCHLD);

	while (1)
	{
		sig_pending = sigpending(&pending_set);

		if (sig_pending == 0 && (sigismember(&pending_set, SIGINT) || 
      sigismember(&pending_set, SIGALRM) || sigismember(&pending_set, SIGSEGV) || 
      sigismember(&pending_set, SIGCHLD)))
    {
			sigwait(&signal_set, &sig);

			switch (sig)
			{
			case SIGINT:
				SigIntHandler(SIGINT);
				break;
			case SIGALRM:
				SigAlrmHandler(SIGALRM);
				break;
			case SIGSEGV:
				SigIntHandler(SIGSEGV);
				break;
			case SIGCHLD:
				SigChldHandler(SIGCHLD);
				break;
			}
		}
		else
		{
			// Periodically "fake" a SIGCHLD because multiple SIGCHLDs simultaneously may
			// overwrite a previous one
			SigChldHandler(SIGCHLD);
			usleep(500000);
		}
	}
	return NULL;
}
#endif
/*
	Signal handler routine that handles SIGCHLD, which is raise any time a forked child process has exited.  The PM will keep a list of
	running tasks and remove the PID of the finished task, and sent an SDMTaskFinished message to the TM.  If the TM's mode changes to
	the mode signifying a DM failure, the SDMTaskFinished message is not sent, and this function just collects the return value of the
	child process.
	INPUTS:
		int sig -- The signal number (SIGCHLD)
	RETURNS:
		void -- nothing
*/
void SigChldHandler(int sig)
{
	//
	// See if there are any queued tasks to be started
	pthread_mutex_lock(&taskQueueMutex);
	size_t uiTaskQueueSize = taskQueue.size();
	pthread_mutex_unlock(&taskQueueMutex);
	if (uiTaskQueueSize > 0)
	{
		debug_f(3, "taskQueue contains %d items.\n", uiTaskQueueSize);
		pthread_mutex_lock(&taskQueueMutex);
		PendingTask launchTask = taskQueue[0];
		taskQueue.erase(taskQueue.begin(), taskQueue.begin() + 1);
		pthread_mutex_unlock(&taskQueueMutex);
		LaunchTask(launchTask.GetName(), launchTask.GetPid());
	}
	//
	// See if any finished tasks need to be retrieved
	int iStatus = 0;
	PROCESS_HANDLE iPid = 0;
	SDMTaskFinished msgFinished;
	SDMCancelxTEDS msgCancel;
#ifdef WIN32
	bool bFoundFinished = false;
	unsigned long ulStatus = 0;
	for (unsigned int i = 0; i < runningTaskList.Size(); i++)
	{
		iPid = runningTaskList[i].GetOsPid();
		GetExitCodeProcess(iPid,&ulStatus);
		if (ulStatus == STILL_ACTIVE)
			continue;
		else
		{
			bFoundFinished = true;
			break;
		}
	}
	// If no finished processes were found, return
	if (!bFoundFinished)
		return;
	iStatus = static_cast<int>(ulStatus);
#else
	// See what child process has finished execution
	iPid = waitpid(-1, &iStatus, WNOHANG);
	debug_f(4, "iPid is %d\n", iPid);
	if (iPid == 0 || iPid == -1)
		return;
#endif
	debug_f(3,"Finished pid is %p\n", iPid);

	// Find the finished process in the runningTaskList list and removed it, also send an SDMTaskFinished message to the TM*/
	pthread_mutex_lock(&taskListMutex);
	int TaskIndex = runningTaskList.GetIndexOfOsPid(iPid);
	if (TaskIndex == -1)
	{
		printf("Could not find a running task with pid %p\n", iPid);
		pthread_mutex_unlock(&taskListMutex);
		return;
	}
	// If this was not a normal finish (i.e. the task was unresponsive and killed), restart the task
	if (runningTaskList[TaskIndex].IsNormalFinish() == false)
	{
		// Reset the fail state
		runningTaskList[TaskIndex].Reset();

		SDMTask msgTask;
		// Restart the task, reusing the same SDM PID
		msgTask.pid = runningTaskList[TaskIndex].GetSdmPid();
		strncpy(msgTask.filename, runningTaskList[TaskIndex].GetName(), sizeof(msgTask.filename));
		SDMComponent_ID PmId;
		PmId.setAddress(Address_PM);
		PmId.setPort(PORT_PM);
		msgTask.Send(PmId);

		pthread_mutex_unlock(&taskListMutex);
		return;
	}
	// Otherwise, normal finish, inform the TM and DM
	debug_f(1,"Finished %s task with return code %d.\n", runningTaskList[TaskIndex].GetName(), iStatus);
	if (tm_mode != MODE_HARD_RESET || tm_mode != MODE_SOFT_RESET)
	{
	   printf("Informing TM and DM of termination...\n");
		// Inform the TM of the finished task
		strncpy(msgFinished.filename, runningTaskList[TaskIndex].GetName(), MAX_FILENAME_SIZE);
		msgFinished.result = iStatus;
		msgFinished.pid = runningTaskList[TaskIndex].GetSdmPid();
		msgFinished.source.setAddress(Address_PM);
		msgFinished.source.setPort(PORT_PM);
		msgFinished.Send();	//Send the return code to the TM
		MessageSent(&msgFinished);

		// Ensure that the xTEDS for this task is cancelled
		msgCancel.source.setPort(PORT_PM);
		msgCancel.source.setAddress(Address_PM);
		msgCancel.source.setSensorID(runningTaskList[TaskIndex].GetSdmPid());
		msgCancel.Send();
		MessageSent(&msgCancel);
	}
	runningTaskList.Remove(TaskIndex);
	pthread_mutex_unlock(&taskListMutex);
}

/*
	The signal_handler routine is used to respond to a Ctrl-C
	INPUTS:
		signal - the signal that the routine caught
*/
void SigIntHandler(int signal)
{
	SDMCancelxTEDS cancel;
	SDMCancel cancel_msg;
	// Shutdown the ProcessManager
	if (signal == SIGINT)
	{
		// Cancel the ProcessManager from the DataManager
		cancel.source.setPort(PORT_PM);
		cancel.source.setAddress(Address_PM);
		cancel.Send();
		MessageSent(&cancel);

		// For each task, terminate their execution and cancel their xTEDS (if registered)
		pthread_mutex_lock(&taskListMutex);
		for (unsigned int i = 0; i < runningTaskList.Size(); i++)
		{
			// Terminate the process
			runningTaskList[i].Kill();

			// Cancel this process's xTEDS
			cancel.source.setSensorID(runningTaskList[i].GetSdmPid());
			cancel.Send();
			MessageSent(&cancel);
			debug_f(3,"Sending SDMCancelxTEDS for SDM pid %d\n", runningTaskList[i].GetSdmPid());
		}
		pthread_mutex_unlock(&taskListMutex);

		// Cancel the subscription to the TaskManager's mode message
		CancelReqRegSubs();
		// Terminate process
		exit(EXIT_SUCCESS);
	}
	if (signal == SIGSEGV)
	{
		cancel.source.setPort(PORT_PM);
		cancel.source.setAddress(Address_PM);
		cancel.Send(); //inform DM of the segmentation fault
		MessageSent(&cancel);
		printf("SIGSEGV\n");
		return; //continue normal operation
	}
}

void SigAlrmHandler(int sig)
{
	if (sig == SIGALRM)
	{
		PublishPerformanceCounterMessage();
		pthread_mutex_lock(&perfCounterMutex);
		prevsec_recd = prevsec_sent = 0;
		pthread_mutex_unlock(&perfCounterMutex);
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//					END SIGNAL HANDLING FUNCTIONS
//
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void* TaskHeartbeatMonitor(void* args)
{
	//SDMCancelxTEDS msgCancel;

	while (1)
	{
		pthread_mutex_lock(&taskListMutex);
		for (unsigned int i = 0; i < runningTaskList.Size(); i++)
		{
			if (runningTaskList[i].IsUnresponsive() && !runningTaskList[i].IsFailed())
			{
				debug_f(0, "\"%s\" (SdmPid=%u, OsPid=%p) is unresponsive; restarting...\n", runningTaskList[i].GetName(), runningTaskList[i].GetSdmPid(), runningTaskList[i].GetOsPid());

				// Kill the task
				runningTaskList[i].Kill();

				if (runningTaskList[i].GetFailCount() >= MAX_TASK_FAILURES)
				{
					debug_f(0, "Warning:  Task \"%s\" is faulty and won't be restarted.\n", runningTaskList[i].GetName());
					runningTaskList.Remove(i);
					continue;
					//TODO:  Send SDMTaskFinished??
				}
				// Send SDMTaskFinished to DM.  This tells the DM to cancel it without
				// Cancel the task and restart it
				SDMTaskError msgError;
				msgError.source.setAddress(Address_PM);
				msgError.source.setPort(PORT_PM);
				msgError.source.setSensorID(runningTaskList[i].GetSdmPid());
				msgError.pid = runningTaskList[i].GetSdmPid();
				msgError.Send();

				// The task list entry is kept, but a reset will allow it to start over
				// its heartbeat status and set its failure state
				runningTaskList[i].Failure();

				// Note:  This task will be restarted when it is wait()ed on by the
				// SIGCHLD handler.
			}
		}
		pthread_mutex_unlock(&taskListMutex);
		sleep(2);
	}
	return NULL;
}

/*
	PublishPerformanceCounterMessage sends out the current values on the message performance counters to all subscribers of the message.
	INPUTS:
		None.
	RETURNS:
		None.
*/
void PublishPerformanceCounterMessage()
{
	char msg[16];

	pthread_mutex_lock(&perfCounterMutex);
	PUT_UINT(&msg[0], total_recd);
	PUT_UINT(&msg[4], prevsec_recd);
	PUT_UINT(&msg[8], total_sent);
	PUT_UINT(&msg[12], prevsec_sent);
	pthread_mutex_unlock(&perfCounterMutex);

	pthread_mutex_lock(&subscriptionsMutex);
	if (subscriptions.Publish(NOTI_PERF_COUNTERS, msg, 16))
	{
		MessageSent(subscriptions.GetLastPublished());
		debug_f(3,"Publishing Message_Count\n");
	}
	pthread_mutex_unlock(&subscriptionsMutex);
}
/*
	VerifyTM finds and verifies that there is a TaskManager running.  If there is a TM running,
	the TM will return the DataManager's address in the SDMReady message.  If there is not a
	TM running, the PM will just spin in this loop until it gets a response.
	INPUTS:
		None.
	RETURN VALUE:
		None.
*/
int VerifyTM(void)
{
	SDMReady msgReady;
	char buf[BUFSIZE];
	int sock = UDPpassive(PORT_PM);
	if (sock == IP_SOCK_INVALID)
	{
		printf("%s() could not bind port.\n", __FUNCTION__);
		return -1;
	}

	msgReady.destination.setPort(PORT_PM);
	msgReady.destination.setAddress(TaskManager.getAddress());
	printf("Searching for TM .");
	//fflush(NULL);
	do {
		total_sent++;
		prevsec_sent++;
		msgReady.Send();
		putchar('.');
		//fflush(NULL);
	} while (! UDPavail(sock, 250));

	UDPrecv (sock, buf, BUFSIZE);

	total_recd++;
	prevsec_recd++;
	msgReady.Unmarshal(buf);
	// Get the actual IP address of this PM node
	Address_PM = msgReady.destination.getAddress();
	// Get the DM address
	DataManager = msgReady.source;
	UDPclose (sock);
	printf("TM found\n");
	debug_f(3,"Setting DM address to 0x%lx\n", DataManager.getAddress());
	return 0;
}

/*
	RegisterPM registers this PM node with the TaskManager according to its resource type.
	INPUTS:
		None.
	RETURN VALUE:
		None.
*/
void RegisterPM(void)
{
	SDMRegPM msgReg;
	msgReg.resources = g_TaskResources.GetUShort();
	msgReg.source.setAddress(Address_PM);
	msgReg.source.setPort(PORT_PM);
	msgReg.Send();
	MessageSent(&msgReg);
}

/*
 *	Start a task.  Setup the command-line arguments for the task and start it.  Information
 *	about the task is kept in the running task list.
 *	INPUTS:
 *		strTaskFilename - the file to be executed
 *		lSdmPid - SDM assigned process id
 *	RETURN VALUE:
 *		the return value is the process id of the executing task
*/
PROCESS_HANDLE LaunchTask (char *strTaskFilename, long lSdmPid)
{
	PROCESS_HANDLE AppPid; 		// pid of the launched application
	struct in_addr addrDm;		// Structure for DataManager's address
	struct in_addr addrTm;		// Structure for TaskManager's address
	char strDmAddress[16];		// Char array of DataManager's address in number-dot notation
	char strTmAddress[16];		// Char array of TaskManager's address in number-dot notation
	char strPid[8];				// String version of the lSdmPid

	// Set the TM and DM addresses in number-dot notation to pass as command line args to the task being launched
	addrTm.s_addr = TaskManager.getAddress();
	addrDm.s_addr = DataManager.getAddress();
	strncpy(strTmAddress, inet_ntoa(addrTm), sizeof(strTmAddress));
	strncpy(strDmAddress, inet_ntoa(addrDm), sizeof(strDmAddress));
	sprintf(strPid, "%ld", lSdmPid);		// SDM process identifier in string format

	debug_f(2,"Launching %s task\n", strTaskFilename);
	//
	// Assure that the file exists
	if (!IsFileAvailable(strTaskFilename))
	{
		printf("Fatal error (LaunchTask):  File does not exist for %s\n", strTaskFilename);
		return 0;
	}
	//
	// Add the new task to the runningTaskList list
	// Must be added before the task is started
	pthread_mutex_lock(&taskListMutex);
	int iTaskIndex = runningTaskList.Add(strTaskFilename, lSdmPid);
	pthread_mutex_unlock(&taskListMutex);
	
#ifdef WIN32
	//
	// ******************  WINDOWS  ******************
	//
	// Perform win32 specific fork/exec like operations
	PROCESS_INFORMATION proc_info;		// Structure for process information needed by CreateProcess

	STARTUPINFO start_info;			// Structure for process startup info needed by CreateProcess
	memset(&start_info,0,sizeof(STARTUPINFO));
	//
	// Setup the task arguments to be passed to the exec function
	char strCommand[256];
	snprintf(strCommand, sizeof(strCommand), "%s %s %s %s", strTaskFilename, strTmAddress, strDmAddress, strPid);

	HANDLE log;

	CreateDirectory(workingDirectory,NULL);
	if ( !merged )
	{
		char name[256];
		name[0] = '\0';
		strcat_s(name,sizeof(name),"Logs\\");
		char* cp = strstr(strTaskFilename,".exe");
		if ( cp == NULL )
			strcat_s(name,sizeof(name),strTaskFilename);
		else
			strncat_s(name,sizeof(name),strTaskFilename,cp-strTaskFilename);
		strcat_s(name,sizeof(name),".log");
		//sprintf_s(name,sizeof(name),"Logs\\%s.log",strTaskFilename);
		SECURITY_ATTRIBUTES security;
		security.nLength = sizeof(security);
		security.bInheritHandle = TRUE;
		security.lpSecurityDescriptor = NULL;
		log = CreateFile(name,GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,&security,
			CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_NO_BUFFERING|FILE_FLAG_WRITE_THROUGH,NULL);
		start_info.dwFlags = STARTF_USESTDHANDLES;
		start_info.hStdOutput = log;
	}
	if (CreateProcess(strTaskFilename, strCommand, NULL, NULL, TRUE, 0, NULL, workingDirectory, &start_info, &proc_info))
	{
		debug_f(3,"Process successfully created.\n");
		// Get the process handle
		AppPid = proc_info.hProcess;
		// Update the PID
		pthread_mutex_lock(&taskListMutex);
		runningTaskList.UpdateOsPid(lSdmPid, AppPid);
		pthread_mutex_unlock(&taskListMutex);
	}
	else
	{
		printf("Error starting task %s! (%d)\n", strTaskFilename, GetLastError());

		pthread_mutex_lock(&taskListMutex);
		runningTaskList.Remove(iTaskIndex);
		pthread_mutex_unlock(&taskListMutex);

		return NULL;
	}
	CloseHandle(log);
#elif defined(__VXWORKS__)
	//
	// ******************  VXWORKS  ******************
	//

	// Setup the task arguments to be passed to the exec function
	char strProgName[MAX_FILENAME_SIZE+10];
	strcpy(strProgName, "/ram0/");
	strcat(strTaskFilename, ".vxe");
	strcat(strProgName, strTaskFilename);

	const char* taskArgs[5];
	const char* envVars[2];
	char libPath[100];
	strcpy(libPath, "LD_LIBRARY_PATH=");
	strcpy(&libPath[16], getenv("LD_LIBRARY_PATH"));
	taskArgs[0] = strProgName;
	taskArgs[1] = strTmAddress;
	taskArgs[2] = strDmAddress;
	taskArgs[3] = strPid;
	taskArgs[4] = NULL;
	
	envVars[0] = libPath;
	envVars[1] = NULL;
	
	g_semLaunchTask.Wait();	
	AppPid = rtpSpawn(taskArgs[0], taskArgs, envVars, 100, 0x20000, 0, VX_FP_TASK);	
	
	if (AppPid < 0)
	{
		printf("Error spawning child rtp: %s\n", taskArgs[0]);

		pthread_mutex_lock(&taskListMutex);
		runningTaskList.Remove(iTaskIndex);
		pthread_mutex_unlock(&taskListMutex);

		g_semLaunchTask.Signal();
		return -1;
	}
	
	// Update the PID
	g_semLaunchTask.Signal();
	pthread_mutex_lock(&taskListMutex);
	runningTaskList.UpdateOsPid(lSdmPid, AppPid);
	pthread_mutex_unlock(&taskListMutex);
#else
	//
	// ******************  LINUX  ******************
	//

	// Setup the task arguments to be passed to the exec function
	char * taskArgs[5];
	taskArgs[0] = strTaskFilename;
	taskArgs[1] = strTmAddress;
	taskArgs[2] = strDmAddress;
	taskArgs[3] = strPid;
	taskArgs[4] = NULL;
	//
	// Add the "./" for Linux to start the task
	char strProgName[MAX_FILENAME_SIZE+2];	//Task name prepended with "./" for exec
	sprintf (strProgName, "./%s", strTaskFilename);
	//
	// Fork a child
	g_semLaunchTask.Wait();
	AppPid = fork();
	if (AppPid < 0)
	{
		printf("Error forking child process..\n");

		pthread_mutex_lock(&taskListMutex);
		runningTaskList.Remove(iTaskIndex);
		pthread_mutex_unlock(&taskListMutex);

		g_semLaunchTask.Signal();
		return -1;
	}
	else if (AppPid == 0)	// Child process
	{
#define EXEC_RETRIES (5)

	  for(int iExecTry=0; iExecTry < EXEC_RETRIES; iExecTry++)
	    {
	      if (execvp(strProgName, taskArgs) < 0)
		{
		  perror("Error on exec:");
		  sleep(5);
		}
	    }

		// Absolutely must exit if exec fails
		_exit(0);
	}
	else			// Parent process
	{
		// Update the PID
		g_semLaunchTask.Signal();
		pthread_mutex_lock(&taskListMutex);
		runningTaskList.UpdateOsPid(lSdmPid, AppPid);
		pthread_mutex_unlock(&taskListMutex);
	}
#endif
	return AppPid;
}

/*
	Set the flags on "fd" to auto-close the file on an exec.  This prevents any tasks from holding
	onto the PM's files if the PM fails and needs to restart.
 */
int SetCloseFileOnExec(int fd)
{
	return fcntl(fd, F_SETFD, FD_CLOEXEC);
}
/*
	Find an available port to give to an application.
 */
long FindAvailablePort()
{
	static int CurPort = PORT_APP_START;
	int iSock;
	while((iSock = UDPpassive(CurPort)) == IP_SOCK_INVALID)
	{
		CurPort++;
		if (CurPort >= 65534)
			CurPort = PORT_APP_START;
	}

	UDPclose(iSock);
	long lReturnPort = CurPort++;
	return lReturnPort;
}

void* Listener(void* args)
{
	char buf[BUFSIZE];
	int result;
	SDMTask task;
	char port_msg[PORT_MSG_LENGTH];
	long cur_port = PORT_APP_START;
	port_msg[0] = SDM_ReqPort;
	g_iPMListenSock = UDPpassive(PORT_PM);

	if (g_iPMListenSock == IP_SOCK_INVALID)
	{
		printf("Could not bind PORT_PM\n");
		return NULL;
	}
	if (SetCloseFileOnExec(g_iPMListenSock) == -1)
	{
		printf("Error changing file flags for the listen port.\n");
		return NULL;
	}

	printf("Waiting for tasks...\n");

	ReqRegSubs();

	pthread_attr_t taskThreadAttr;
	pthread_attr_init(&taskThreadAttr);
	pthread_attr_setdetachstate(&taskThreadAttr, PTHREAD_CREATE_DETACHED);
	pthread_attr_setstacksize(&taskThreadAttr, THREAD_STACK_SIZE);
	pthread_t taskThread;

	while(1)
	{
		result = UDPserv_recv(g_iPMListenSock,buf,BUFSIZE);
		pthread_mutex_lock(&perfCounterMutex);
		total_recd++;
		prevsec_recd++;
		pthread_mutex_unlock(&perfCounterMutex);

		if (result > 0)
		{
			switch(buf[0])
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
				case SDM_Task:
					// Start a separate thread if code transfer is needed
					if (0 != pthread_create(&taskThread, &taskThreadAttr, &TaskHandler, memcpy(new char[result], buf, result)))
					{
						perror("Error spawning TaskHandler thread.\n");
					}
					break;
				case SDM_Kill:
					KillHandler(buf);
					break;
				case SDM_ReqPort:
					cur_port = FindAvailablePort();
					PUT_LONG(port_msg+1, cur_port);
					UDPserv_reply(g_iPMListenSock, port_msg, PORT_MSG_LENGTH);
					break;
				case SDM_Code:
					HandleCodeMessage(buf);
					break;
				case SDM_Subreqst:
					SubreqstHandler(buf);
					break;
				case SDM_Deletesub:
					DeletesubHandler(buf);
					break;
				case SDM_Command:
					CommandHandler(buf);
					break;
				case SDM_RegInfo:
					RegInfoHandler(buf);
					break;
				case SDM_Data:
					DataHandler(buf);
					break;
				case SDM_Heartbeat:
					HeartbeatHandler(buf);
					break;
				case SDM_Error:
					ErrorHandler(buf);
					break;
				case SDM_DMLeader:
				    DMLeaderHandler(buf);
				    break;
				default:
					debug_f(0,"Unexpected Message Type:%c\n",buf[0]);
					break;
			}
		}
	}
	return NULL;
}
/*
	DoReset basically sets the ProcessManager's state to the start state, before any tasks were started.
	This happens when the DataManager fails and a new DM is elected.  All applications need to have the
	DM address updated, so they are killed and restarted if needed.
	INPUTS:
		None.
	RETURN VALUE:
		None.
*/
void DoReset()
{
        // Treat this cancellation as a task error message.
        // This prevents the task from being posted as "inactive", which
        // would cause it to get reposted as other tasks start up and
        // perform requests
	SDMCancelxTEDS msgCancelxTEDS;
	SDMTaskError msgTaskError;

	// Kill all running tasks
	pthread_mutex_lock(&taskListMutex);
	for (unsigned int i = 0; i < runningTaskList.Size(); i++)
	{
	   // For now, this is a hard reset, meaning all running tasks are killed
		debug_f(3,"Killing %s (%p)\n", runningTaskList[i].GetName(), runningTaskList[i].GetOsPid());
		runningTaskList[i].Kill();

		msgTaskError.source.setPort(PORT_PM);
		msgTaskError.source.setAddress(Address_PM);
		msgTaskError.source.setSensorID(runningTaskList[i].GetSdmPid());
		msgTaskError.pid = runningTaskList[i].GetSdmPid();
		msgTaskError.Send();
	}

	runningTaskList.RemoveAll();
	pthread_mutex_unlock(&taskListMutex);

	// Clear the PM's subscription list
	pthread_mutex_lock(&subscriptionsMutex);
	subscriptions.ClearAllSubscriptions();
	pthread_mutex_unlock(&subscriptionsMutex);
}

void RegisterXteds()
{
  // Re-register the PM with the DM
  debug_f(3,"Reregistering the PM's xTEDS\n");
  SDMxTEDS msgxTEDS;
  msgxTEDS.source.setSensorID(1);
  msgxTEDS.source.setAddress(Address_PM);
  msgxTEDS.source.setPort(PORT_PM);
  strcpy(msgxTEDS.xTEDS, xTEDS);
  msgxTEDS.Send();
  MessageSent(&msgxTEDS);
}

void ErrorHandler(const char* buf)
{
	SDMError msgError;
	long lMsgSize;
	if ((lMsgSize=msgError.Unmarshal(buf)) < 0)
	{
		printf("Invalid SDMError message received.\n");
		return;
	}
	MessageReceived(&msgError);

	debug_f(1, "Error message received.\n");

	unsigned int i = 0;
	pthread_mutex_lock(&codeReceiversMutex);
	size_t uiSize = codeReceivers.size();
	for (i = 0; i < uiSize; i++)
	{
		if (!strcmp(codeReceivers[i].filename, msgError.error_msg))
		{
			if (write(codeReceivers[i].fd_code, buf, lMsgSize) < 0)
			{
				printf("Error writing error message to code consumer\n");
			}
			else
				break;
		}
	}
	if (i == uiSize)
		printf("Recieved error message that didn't match any code consumer\n");
	pthread_mutex_unlock(&codeReceiversMutex);
}

/*
 *  Handle a SDMTask message from the Task Manager.  If the executable for the task doesn't exist, a code
 *  transfer will be performed.
 *
 */
void* TaskHandler(void* args)
{
	char* msgBuf = (char*) args;
	SDMTask msgTask;
	if (msgTask.Unmarshal(msgBuf) < 0)
	{
		printf("Invalid SDMTask message.\n");
		delete [] msgBuf;
		return NULL;
	}
#ifdef WIN32
	char* cp = strstr(msgTask.filename,".exe");
	if ( cp == NULL )
	{
		strcat_s(msgTask.filename,sizeof(msgTask.filename),".exe");
	}
#endif
	MessageReceived(&msgTask);

	// Check to see if code file exists
	if (!IsFileAvailable(msgTask.filename))
	{
#ifndef __VXWORKS__
		int iaCodeFd[2];	// Pipe descriptors for transfering code
		//
		// Setup pipes and perform a code transfer
		if (pipe(iaCodeFd) != 0)
		{
			perror("Error calling pipe(): ");
			delete [] msgBuf;
			return NULL;
		}
#else
		int iaCodeFd[2];
		char pipeName[MAX_FILENAME_SIZE];
		strcpy(pipeName, "/pipe/");
		strcat(pipeName, msgTask.filename);
		if(pipeDevCreate(pipeName, 5, BUFSIZE) != 0)
		{
			printf("ERROR creating pipe for code transfer: %i %s\n", errno, strerror( errno ));
		}
		iaCodeFd[0] = open(pipeName, O_RDONLY);
		iaCodeFd[1] = open(pipeName, O_WRONLY);
#endif
		//
		// Add a record for this code receiver thread
		code_recv receiverRecord;
		strncpy(receiverRecord.filename, msgTask.filename, sizeof(receiverRecord.filename));
		receiverRecord.filename[sizeof(receiverRecord.filename)-1] = '\0';
#ifndef __VXWORKS__
		receiverRecord.fd_code = iaCodeFd[1]; 		// Write end
#else
		receiverRecord.fd_code = iaCodeFd[1]; 		// Write end
#endif

		pthread_mutex_lock(&codeReceiversMutex);
		codeReceivers.push_back(receiverRecord);
		pthread_mutex_unlock(&codeReceiversMutex);
		//
		// Request the code
		debug_f(0, "Sending request for code of %s, version %d, pid %lu\n",
			msgTask.filename, msgTask.version, msgTask.pid);
#ifndef __VXWORKS__
		bool bSuccess = GetCode(msgTask.filename, msgTask.pid, msgTask.version, iaCodeFd[0] /*Read end*/);
		close(iaCodeFd[0]);
#else
		bool bSuccess = GetCode(msgTask.filename, msgTask.pid, msgTask.version, iaCodeFd[0]  /*Read end*/);
		close(iaCodeFd[0]);
		close(iaCodeFd[1]);
		pipeDevDelete(pipeName, 1);
#endif
		
		if (bSuccess)	// If code transfer was a success
		{
			// Close the other end of the code transfer pipes
			debug_f(2, "Code received for %s, queueing task...\n", msgTask.filename);
		}
		else		// If code transfer failed
		{
			debug_f(0,"Could not retrieve %s from the SDM file system.\n", msgTask.filename);

			// Inform the TM of the failure to begin
			SDMTaskFinished msgFinished;
			strncpy(msgFinished.filename, msgTask.filename, MAX_FILENAME_SIZE);
			msgFinished.result = -1;
			msgFinished.pid = msgTask.pid;
			msgFinished.source.setAddress(Address_PM);
			msgFinished.source.setPort(PORT_PM);
			msgFinished.Send();
			MessageSent(&msgFinished);

			delete [] msgBuf;
			return NULL;
		}
	}
	//
	// Add the task to the task queue to be started
	// This fixes a uClinux problem where the thread that forks a process must
	// be the thread that performs a wait()/waitpid() (the signal handler thread)
	PendingTask newTask(msgTask.filename, msgTask.pid);
	pthread_mutex_lock(&taskQueueMutex);
	taskQueue.push_back(newTask);
	pthread_mutex_unlock(&taskQueueMutex);

	delete [] msgBuf;
	return NULL;
}

void KillHandler(char *buf)
{
	SDMKill msgKill;
	if (msgKill.Unmarshal(buf) == SDM_INVALID_MESSAGE)
	{
		printf("Invalid kill message.\n");
		return;
	}
	MessageReceived(&msgKill);
	debug_f(1, "Received kill command for pid %ld\n", msgKill.PID);

	// Find and kill the task
	pthread_mutex_lock(&taskListMutex);
	int TaskIndex = runningTaskList.GetIndexOfSdmPid(msgKill.PID);
	if (TaskIndex == -1)
	{
		printf("Could not find the task to kill\n");
		pthread_mutex_unlock(&taskListMutex);
		return;
	}

   runningTaskList[TaskIndex].Kill();

	if(msgKill.killLevel == 1)
	{
		debug_f(1, "Permanantly Killing Task with pid: %ld\n", msgKill.PID);
		SDMTaskFinished msgFinished;
		strncpy(msgFinished.filename, runningTaskList[TaskIndex].GetName(), MAX_FILENAME_SIZE);
		msgFinished.result = 0;
		msgFinished.pid = runningTaskList[TaskIndex].GetSdmPid();
		msgFinished.source.setAddress(Address_PM);
		msgFinished.source.setPort(PORT_PM);
		msgFinished.Send();	//Send the return code to the TM
		MessageSent(&msgFinished);

      SDMCancelxTEDS msgCancel;
      msgCancel.source.setPort(PORT_PM);
		msgCancel.source.setAddress(Address_PM);
		msgCancel.source.setSensorID(runningTaskList[TaskIndex].GetSdmPid());
		msgCancel.fullCancel = 1;
		msgCancel.Send();

      runningTaskList.Remove(TaskIndex); //This should keep a task from being reposted
	}

	pthread_mutex_unlock(&taskListMutex);
}
/*	CommandHandler handles the reception of SDMCommand messages and performs the requested command, if it is applicable.
	INPUTS:
		buf - The buffer containing the SDMCommand message.
	RETURNS:
		None.
*/
void CommandHandler(char *buf)
{
	SDMCommand msgCommand;
	if (msgCommand.Unmarshal(buf) < 0)
	{
		printf("Invalid command message.\n");
		return;
	}
	MessageReceived(&msgCommand);

	// Enable message logging command
	if (msgCommand.command_id == CMD_ENABLE_LOGGING)
	{
		if (log_service.NeedsInit())
			log_service.SetLogFile("Process Manager Message Log\n", "pmmessages.log");
		log_service.AddMessageType(&msgCommand);
	}
	// Disable message logging command
	else if (msgCommand.command_id == CMD_DISABLE_LOGGING)
	{
		log_service.RemoveMessageType(&msgCommand);
	}
}
/*
	SubreqstHandler handles the reception of SDMSubreqst messages and adds the subscriber to the subscription list.
	INPUTS:
		buf - The buffer containing the SDMSubreqst message.
	RETURNS:
		None.
*/
void SubreqstHandler(char *buf)
{
	SDMSubreqst msgRequest;
	if (msgRequest.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMSubreqst message.\n");
		return;
	}
	MessageReceived(&msgRequest);
	debug_f(1,"Subscription request.\n");

	// Add the subscription to the PM's sub list
	pthread_mutex_lock(&subscriptionsMutex);
	subscriptions.AddSubscription(msgRequest);
	pthread_mutex_unlock(&subscriptionsMutex);

	// If request is for performance counters, start system timer
	if (msgRequest.msg_id == NOTI_PERF_COUNTERS)
	{
#ifndef __VXWORKS__
		itimerval interval;
		getitimer(ITIMER_REAL, &interval);
		if (interval.it_value.tv_sec == 0 && interval.it_interval.tv_sec == 0)
		{
			//Time interval for the performance counter publish
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

}
/*
	DetelesubHandler deletes a subscription from the ProcessManager's subscription list.
	INPUT:
		buf - The buffer containing the SDMDeletesub message.
	RETURNS:
		None.
*/
void DeletesubHandler(char *buf)
{
	SDMDeletesub msgDelete;
	if (msgDelete.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMDeletesub message.\n");
		return;
	}
	MessageReceived(&msgDelete);
	debug_f(1,"Delete subscription request.\n");

	// Remove the subscription
	pthread_mutex_lock(&subscriptionsMutex);
	subscriptions.RemoveSubscription(msgDelete);
	pthread_mutex_unlock(&subscriptionsMutex);
}
/*
	HeartbeatHandler handles the reception of SDMHeartbeat messages from the TaskManager and responds
	to them with an SDMHeartbeat message.  This mechanism is used to detect ProcessManager failure.
	INPUTS:
		buf - The buffer containing the SDMHeartbeat message
	RETURNS:
		void
*/
void HeartbeatHandler (char * buf)
{
	SDMHeartbeat msgHeartBeat;
	if (msgHeartBeat.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMHeartbeat message.\n");
		return;
	}
	MessageReceived(&msgHeartBeat);

	if (msgHeartBeat.source.getPort() == PORT_TM)
	{
		debug_f(3,"Heartbeat message received (TM).\n");
		// Reply back to the TM
		msgHeartBeat.source.setAddress(Address_PM);
		msgHeartBeat.source.setPort(PORT_PM);
		msgHeartBeat.SendTo(TaskManager);
		MessageSent(&msgHeartBeat);
	}
	else if (msgHeartBeat.source.getPort() == PORT_PM_MONITOR)
	{
		debug_f(3,"Heartbeat message received (PM monitor).\n");
		SDMComponent_ID monitorId (msgHeartBeat.source);
		// Reply back to the monitor process
		msgHeartBeat.source.setAddress(Address_PM);
		msgHeartBeat.source.setPort(PORT_PM);
		msgHeartBeat.SendTo(monitorId);
		MessageSent(&msgHeartBeat);
	}
	else
	{
		debug_f(3,"Heartbeat message received (PID %lu).\n", msgHeartBeat.source.getSensorID());
		// Make note of the heartbeat
		pthread_mutex_lock(&taskListMutex);
		runningTaskList.HeartbeatReceived(msgHeartBeat.source.getSensorID());
		pthread_mutex_unlock(&taskListMutex);
	}
}

void DMLeaderHandler(char* buf)
{
    SDMDMLeader temp;
    temp.Unmarshal(buf);
    if(temp.running_flag == 't')
    {
        TaskManager = temp.source;
        printf("New TM Address Received: 0x%lx\n", TaskManager.getAddress());
    }
}

/*
	SendRunningTasks sends to the TaskManager, all running tasks on this PM node.  This routine is called when the TM
	has experienced a fault and has died.  Each PM will then call this routine which allows the TM to rebuild its
	list of running tasks running in the SDM.
	INPUTS:
		None.
	RETURNS:
		void
*/
void SendRunningTasks(void)
{
	SDMTask msgTask;

	// The source of this message is this ProcessManager
	msgTask.source.setAddress(Address_PM);
	msgTask.source.setPort(PORT_PM);

	// Send to the TaskManager, all running tasks on this PM node
	pthread_mutex_lock(&taskListMutex);
	for (unsigned int i = 0; i < runningTaskList.Size(); i++)
	{
		strncpy(msgTask.filename, runningTaskList[i].GetName(), MAX_FILENAME_SIZE);
		msgTask.filename[MAX_FILENAME_SIZE-1] = '\0';
		msgTask.pid = runningTaskList[i].GetSdmPid();
		msgTask.Send(TaskManager);
		MessageSent(&msgTask);
	}
	pthread_mutex_unlock(&taskListMutex);
}

void MessageReceived(SDMmessage* msg)
{
	if (!log_service.IsEmpty())
		log_service.MessageReceived(msg);
}

void MessageSent(SDMmessage *msg)
{
	// Increment performance counters
	pthread_mutex_lock(&perfCounterMutex);
	total_sent++;
	prevsec_sent++;
	pthread_mutex_unlock(&perfCounterMutex);

	// Log the message, if the logger is enabled
	if (!log_service.IsEmpty())
		log_service.MessageSent(msg);
}

/*
 *  Determine if a file exists in the current running directory.  Used to determine whether a task needs to be
 *  added to the pending task list if the IDS is not available.
 */
bool IsFileAvailable(const char* Filename)
{
	if (Filename == NULL) return false;
#ifndef __VXWORKS__
	struct stat file_stats;

	if (stat(Filename, &file_stats) < 0)
	{
		if (errno == ENOENT)
		{
			return false;
		}
	}
	if (file_stats.st_size > 0)
		return true;
	return false;
#else
	char fullFilename[MAX_FILENAME_SIZE];
	strcpy(fullFilename, "/ram0/");
	strcat(fullFilename, Filename);
	strcat(fullFilename, ".vxe");
	if(access(fullFilename, F_OK) == 0)
	{
		return true;
	}
	else
	{
		return false;
	}	
#endif
}

void RemoveCodeReceiver(const char* strFilename)
{
	pthread_mutex_lock(&codeReceiversMutex);
	const size_t RECEIVER_LIST_SIZE = codeReceivers.size();
	for (unsigned int uiIndex = 0; uiIndex < RECEIVER_LIST_SIZE; uiIndex++)
	{
		if (strcmp (codeReceivers[uiIndex].filename, strFilename) == 0)
		{
			debug_f(3, "Removing code receiving entry for task %s.\n", strFilename);
			close(codeReceivers[uiIndex].fd_code);
			codeReceivers.erase(codeReceivers.begin() + uiIndex, codeReceivers.begin() + uiIndex + 1);
			break;
			//fall through
		}
	}
	pthread_mutex_unlock(&codeReceiversMutex);
}

