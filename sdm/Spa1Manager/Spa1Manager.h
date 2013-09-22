#ifndef __SPA1_MANAGER_H__
#define __SPA1_MANAGER_H__

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <getopt.h>
#include <signal.h>
#include <stdlib.h>
#include "Spa1ManagerxTEDS.h"
#include "Spa1Asim.h"
#include "Spa1AsimTable.h"
#include "Spa1Translator.h"
#include "Spa1Queue.h"
#include "../common/MessageManager/MessageManager.h"
#include "../common/message/SDMHello.h"
#include "../common/message/SDMID.h"
#include "../common/message/SDMAck.h"
#include "../common/message/SDMRegister.h"
#include "../common/message/SDMxTEDS.h"
#include "../common/message/SDMCancelxTEDS.h"
#include "../common/message/SDMSerreqst.h"
#include "../common/message/SDMData.h"
#include "../common/message/SDMCommand.h"
#include "../common/Time/SDMTime.h"
#include "../common/Debug.h"
#include "../common/version.h"
#include "../common/SubscriptionManager/SubscriptionManager.h"

#ifndef WIN32
#include <linux/i2c.h> /* for I2C_SLAVE */
#endif
#ifndef I2C_SLAVE
#define I2C_SLAVE 0x0703   /* Change slave address       */
#endif

///Defines
#define THREAD_STACK_SIZE 256000
#define MAX_SPA1_ASIMS  64
#define DEFAULT_ADDRESS 0x11
#define DEFAULT_BUFFER_SIZE 16
#define I2C_READ_TIMEOUT 3
#define MAX_SPA1_MSG_SIZE	256


///Function Prototypes
void* sdmListener(void* args);
void* i2cComm(void* args);
void* regAsimWithSdm(void* args);
#ifndef WIN32
void* signalHandler(void* args);
#else
void signalHandler(int sig);
#endif

void asimMonitor();
int sdmRegister(MessageManager* msgManager);
void registerxTEDS();
void registerAsimXteds(Spa1Asim* asim);
void cancelSdmRegistrations();
unsigned char searchForNewAsims(unsigned char);
int i2cRead(unsigned char* buf, size_t size);
void setSlaveAddress(unsigned char address);
unsigned int getCurTime();

void handleAckMsg(char* buf);
void handleRegisterMsg(char* buf);
void handleIdMsg(char* buf);
void handleSerreqstMsg(char* buf);
void handleCommandMsg(char* buf);
void sendCommandToAsim(Spa1Asim* asim, SDMCommand* commandMsg);
void handleSubreqstMsg(char* buf);
void handleDeletesubMsg(char* buf);
void getAsimxTEDSReply(char* buf);
void getAsimDetailsReply(char* buf);


///Globals
pthread_t sdmListenThread;
pthread_t i2cThread;
pthread_t sigHandler;
Spa1AsimTable asimTable;
Spa1Translator translator;
SubscriptionManager subscriptions;
int busFd;
int debug = 0;
bool termination = false;

SDMMessage_ID regChangeMsg(1,1);
SDMMessage_ID getxTEDSMsg(1,2);
SDMMessage_ID xTEDSReplyMsg(1,3);
SDMMessage_ID getAsimDetailsMsg(1,4);
SDMMessage_ID asimDetailsReplyMsg(1,5);
SDMMessage_ID resetBusMsg(2,1);

#endif
