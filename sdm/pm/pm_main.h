#ifndef _SDM_PM_H_
#define _SDM_PM_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#ifndef __VXWORKS__
#include <sys/poll.h>
#include <getopt.h>
#endif
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <list>
#include <pthread.h>
#include <fcntl.h>

#ifdef WIN32
#include <windows.h>
#include <process.h>
#endif

#include "../common/message/SDMReady.h"
#include "../common/message/SDMTask.h"
#include "../common/message/SDMRegPM.h"
#include "../common/message/SDMCancelxTEDS.h"
#include "../common/message/SDMxTEDS.h"
#include "../common/message/SDMCode.h"
#include "../common/message/SDMReqCode.h"
#include "../common/message/SDMError.h"
#include "../common/message/SDMTaskFinished.h"
#include "../common/message/SDMSubreqst.h"
#include "../common/message/SDMCommand.h"
#include "../common/message/SDMReqReg.h"
#include "../common/message/SDMRegInfo.h"
#include "../common/message/SDMConsume.h"
#include "../common/message/SDMCancel.h"
#include "../common/message/SDMHeartbeat.h"
#include "../common/message/SDMTaskError.h"
#include "../common/message/SDMKill.h"
#include "../common/message/SDMDMLeader.h"
#include "../common/message/SDMHello.h"
#include "../common/message/SDMAck.h"
#include "../common/message/SDMRegister.h"
#include "../common/message/SDMID.h"
#include "../common/Debug.h"
#include "../common/UDPcom.h"
#include "../common/checksum/checksum.h"
#include "../common/SubscriptionManager/SubscriptionManager.h"
#include "../common/MessageLogger/MessageLogger.h"
#include "PMProcessList.h"
#include "../common/task/SDMTaskResources.h"

/*Windows uses closesocket instead of close for socket descriptors*/
#ifdef WIN32
#ifdef close
#undef close
#endif
#define close closesocket
#endif

#define MAX_TASK_FAILURES	5	// The number of times a task will be restarted if heartbeats timeout
//system returns this value if a file is not found
#define FILE_NOT_FOUND	32512
#define PORT_MSG_LENGTH 5
#define TM_Mode_ID	1		//ID number used in RegInfo and ReqReg messages for TM's status message

// Message IDs
const SDMMessage_ID NOTI_PERF_COUNTERS(2,13);
const SDMMessage_ID CMD_ENABLE_LOGGING(3,16);
const SDMMessage_ID CMD_DISABLE_LOGGING(3,17);

// Function prototypes
int VerifyTM(void);
void* Listener(void* args);
void RegisterPM(void);
void TaskLauncher(char* filename,long pid);
PROCESS_HANDLE LaunchTask (char *strTaskFilename, long lSdmPid);
void* SigHandler(void* args);
#ifdef WIN32
void* SigChldThreadFunc(void* args);
#endif
void SigChldHandler(int sig);
void SigIntHandler(int sig);
void SigTermHandler(int sig);
void SigAlrmHandler(int sig);
void SigIntHandler(int sig_num);
void CommandHandler(char *buf);
void SubreqstHandler(char *buf);
void DeletesubHandler(char *buf);
void KillHandler(char *buf);
void HeartbeatHandler(char *buf);
void* TaskHandler(void* args);
void PublishPerformanceCounterMessage(void);
void DoReset();
void RegisterXteds();
void SendRunningTasks(void);
void MessageSent(SDMmessage *msg);
void MessageReceived(SDMmessage* msg);
bool IsFileAvailable(const char* Filename);
void ErrorHandler(const char* buf);
void* TaskHeartbeatMonitor(void* args);
int SetCloseFileOnExec(int fd);
void RemoveCodeReceiver(const char* strFilename);
void DMLeaderHandler(char*);
double GetCurTime();

/*Structure that represents all information needed to initiate a code transfer*/
struct code_recv
{
	int fd_code;
#ifdef BUILD_FOR_IDS
	unsigned short ids_handle;
#endif
	char filename[MAX_FILENAME_SIZE];
};


#endif
