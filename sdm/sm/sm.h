#ifndef _SDM_SM_H_
#define _SDM_SM_H_

#include "sensor.h"
#include "../common/message/SDMmessage.h"
#include "../common/message/SDMReady.h"
#include "../common/message/SDMSubreqst.h"
#include "../common/message/SDMDeletesub.h"
#include "../common/message/SDMSerreqst.h"
#include "../common/message/SDMCommand.h"
#include "../common/message/SDMTat.h"
#include "../common/message/SDMError.h"
#include "../common/message/SDMCancelxTEDS.h"
#include "../common/message/SDMRegInfo.h"
#include "../common/message/SDMReqReg.h"
#include "../common/message/SDMConsume.h"
#include "../common/message/SDMCancel.h"
#include "../common/message/SDMxTEDS.h"
#include "../common/message/SDMAck.h"
#include "../common/message/SDMHello.h"
#include "../common/message/SDMRegister.h"
#include "../common/message/SDMID.h"
#include "../common/SubscriptionManager/SubscriptionManager.h"
#include "../common/MessageLogger/MessageLogger.h"
#include "../common/TCPcom.h"
#include "../common/Debug.h"
#include "../common/version.h"
#include "../common/Time/SDMTime.h"
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/poll.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#ifndef WIN32
#include <net/if.h>
#endif

#define TM_Mode_ID	1

//SM message ids
const unsigned long SENSOR_MANAGER_SID = 1;
const SDMMessage_ID CMD_ENABLE_LOGGING(3,16);
const SDMMessage_ID CMD_DISABLE_LOGGING(3,17);
const SDMMessage_ID SUB_PERFORMANCE_COUNTERS(2,13);


// Function prototypes
void VerifyDM(void);
void* UDPMonitor(void*);
void* TCPMonitor(void*);
double GetCurTime();
#ifdef WIN32
void SigIntHandler(int signum);
#else
void* SigHandler(void*);
#endif
void PublishPerformanceCounterMessage(void);
void MessageSent(SDMmessage *msg);
void MessageReceived(SDMmessage *msg);
int GetNodeAddress();

#endif

