#ifndef _SDM_TM_H_
#define _SDM_TM_H_

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <arpa/inet.h>
#ifndef __VXWORKS__
#include <getopt.h>
#include <sys/poll.h>
#endif
#include <signal.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>


#ifndef WIN32
#include <net/if.h>
#endif

#include "tasklist.h"
#include "../common/UDPcom.h"
#include "../common/checksum/checksum.h"
#include "../common/message/SDMError.h"
#include "../common/message/SDMPostTask.h"
#include "../common/message/SDMxTEDS.h"
#include "../common/message/SDMSubreqst.h"
#include "../common/message/SDMDeletesub.h"
#include "../common/message/SDMCommand.h"
#include "../common/message/SDMReady.h"
#include "../common/message/SDMTask.h"
#include "../common/message/SDMCancelxTEDS.h"
#include "../common/message/SDMRegPM.h"
#include "../common/message/SDMCode.h"
#include "../common/message/SDMReqCode.h"
#include "../common/message/SDMTaskFinished.h"
#include "../common/message/SDMHeartbeat.h"
#include "../common/message/SDMKill.h"
#include "../common/message/SDMRegInfo.h"
#include "../common/message/SDMReqReg.h"
#include "../common/message/SDMDMLeader.h"
#include "../common/message/SDMHello.h"
#include "../common/message/SDMAck.h"
#include "../common/message/SDMRegister.h"
#include "../common/message/SDMID.h"

#include "../common/SubscriptionManager/SubscriptionManager.h"
#include "../common/MessageManager/MessageManager.h"
#include "../common/MessageLogger/MessageLogger.h"
#include "../common/MessageManipulator/MessageManipulator.h"
#include "../common/Debug.h"
#include "../common/version.h"
#include "../common/MemoryUtils.h"
#include "../common/Time/SDMTime.h"
#include "../dm/DMUtils.h"
#include "pm_record.h"
#include "pm_record_list.h"
#include "HandlerArguments.h"
#include "TmXtedsDefs.h"

#ifdef __uClinux__
# define BUILD_FOR_PNPSAT
#endif

#define MAX_JOBS 50

//
// Definitions for task load locations
//
#ifdef __uClinux__
# define STR_TASK_LOCATION_PRIMARY "/mnt/flash/bin"
# define STR_TASK_LOCATION_TEMPORARY    "/mnt/flash/bin_test"
# define STR_TASK_LOCATION_BACKUP  "/mnt/flash/bin_backup"
#else
# define STR_TASK_LOCATION_PRIMARY "."
# define STR_TASK_LOCATION_TEMPORARY    "."
# define STR_TASK_LOCATION_BACKUP  "."
#endif // ifdef __uClinux__

// Function prototypes
void printResources(const SDMTaskResources& resources);
bool SendTask (const pm_record& PMData, const Task& TaskData);
void SendCode (char* buf);
void PostTask (char *buf);
void VerifyDM(void);
void PublishStatusMessage(char *sender_buf);
void PublishTaskQueuedMessage(char* taskname);
void PublishTaskStartedMessage(char* taskname, unsigned int pid);
void PublishTaskFinishedMessage(char* taskname,int exitcode, unsigned int pid);
void PublishPerformanceCounterMessage(void);
void InitialStartUp(void);
void MessageReceived(SDMmessage *msg);
void MessageSent(SDMmessage *msg);
void* Listener(void*);
void* Scheduler(void*);
void* TMHeartbeat(void*);
void* PMHeartbeat(void*);
void* ReqCodeHandler(void* arg);
void* PostTaskHandler(void* arg);
void* SubreqstHandler(void* arg);
void* DeletesubHandler(void* arg);
void* CommandHandler(void* arg);
void* SerreqstHandler(void* arg);
void* ReadyHandler(void* arg);
void RegInfoHandler(void* arg);
void* TaskFinishedHandler(void* arg);
void* KillHandler(void* arg);
bool PerformKill(SDMKill& msgKill);
void* PMRunningTaskHandler(void* arg);
void QueueHeartbeat (long length, char buf[]);
void ReceiveLeader (char buf[]);
void TakeOverLeadPosition (void);
double GetCurTime();
#ifndef WIN32
void* SigHandler(void*);
#else
void SigHandler(int signum);
#endif

#ifdef PNP_FAKE
void sendIMA (void);
void RequestDMInfo(MessageManager*);
void AmIBackup(MessageManager*);
#endif

#ifdef PNP_BACKUP
void RequestDMInfo(void);
bool AmIBackup (void);
void VerifyNewDM(char *sender_buf);
#endif

#ifdef BUILD_FOR_PNPSAT
void RequestRegPowerController();
void PowerCyclePmNode(const SDMComponent_ID& idPm);
#endif // BUILD_FOR_PNPSAT

#endif  // _SDM_TM_H_
