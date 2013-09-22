#ifndef __SDM_DM_H_
#define __SDM_DM_H_

#include "../common/UDPcom.h"
#include "../common/TCPcom.h"
#include "../common/message_defs.h"
#include "../common/version.h"
#include "../common/message/SDMSubreqst.h"
#include "../common/message/SDMDeletesub.h"
#include "../common/message/SDMConsume.h"
#include "../common/message/SDMReqReg.h"
#include "../common/message/SDMRegInfo.h"
#include "../common/message/SDMCancel.h"
#include "../common/message/SDMService.h"
#include "../common/message/SDMSerreqst.h"
#include "../common/message/SDMCommand.h"
#include "../common/message/SDMReqxTEDS.h"
#include "../common/message/SDMxTEDSInfo.h"
#include "../common/message/SDMmessage.h"
#include "../common/message/SDMCancelxTEDS.h"
#include "../common/message/SDMxTEDS.h"
#include "../common/message/SDMTat.h"
#include "../common/message/SDMPostTask.h"
#include "../common/message/SDMData.h"
#include "../common/message/SDMReady.h"
#include "../common/message/SDMSearch.h"
#include "../common/message/SDMSearchReply.h"
#include "../common/message/SDMElection.h"
#include "../common/message/SDMDMLeader.h"
#include "../common/message/SDMAck.h"
#include "../common/message/SDMVarReq.h"
#include "../common/message/SDMTaskError.h"
#include "../common/message/SDMVarInfo.h"
#include "../common/message/SDMHeartbeat.h"
#include "../common/message/SDMHello.h"
#include "../common/message/SDMRegister.h"
#include "../common/message/SDMID.h"
#include "../common/MessageLogger/MessageLogger.h"
#include "../common/MessageManager/MessageManager.h"
#include "../common/Debug.h"
#include "../common/Exception/SDMRegexException.h"
#include "../common/SDMRegQueue.h"
#include "../common/SDMCancelQueue.h"
#include "Parse.h"
#include "xTEDSLibraryList.h"
#include "xTEDSParameters.h"
#include "SubscriptionList.h"
#include "backupDMList.h"
#include "xTEDSSegmentBuilder.h"
#include "DMUtils.h"
#include "ProviderSubscriptionList.h"
//
//Data Manager xTEDS message identifiers
//
const SDMMessage_ID INVALID_MESSAGE_ID(0, 0);
//DM Notification messages
const SDMMessage_ID NOTI_REGISTRATION(1, 1);
const SDMMessage_ID NOTI_DEREGISTRATION(1, 2);
const SDMMessage_ID NOTI_XTEDS_MODIFICATION(1, 3);
const SDMMessage_ID NOTI_REGISTRATION_CHANGE(1, 4);
const SDMMessage_ID NOTI_PERFORMANCE_COUNTERS(2, 13);

//Data reply messages
const SDMMessage_ID RPLY_CONVERTED_DEVICE_NAME(1, 5);
const SDMMessage_ID RPLY_CONVERTED_SPANODE(1, 7);
const SDMMessage_ID RPLY_CONVERTED_IP(1, 10);
const SDMMessage_ID RPLY_RETURN_COMP_KEY(1, 15);
const SDMMessage_ID RPLY_ERRORS(2, 19);

//Command requests
const SDMMessage_ID CMD_ENABLE_LOGGING(3, 16);
const SDMMessage_ID CMD_DISABLE_LOGGING(3, 17);

//Service requests
const SDMMessage_ID SER_SEND_SENSOR_ID(1, 6);
const SDMMessage_ID SER_SEND_PID(1, 8);
const SDMMessage_ID SER_SID_TO_SPANODE(1, 11);
const SDMMessage_ID SER_SID_TO_IP(1, 12);
const SDMMessage_ID SER_COMPID_TO_COMPKEY(1, 14);
const SDMMessage_ID SER_GET_ERRORS(2, 18);

//xTEDS modification types
#define MOD_NOT_APPLICABLE		0x0
#define REGISTRATION_MODIFICATION 	0x1
#define DEREGISTRATION_MODIFICATION 	0x2
#define UPDATE_MODIFICATION		0x3

//xTEDS Hub types
#define APPLICATION			0x0
#define DEVICE				0x1
#define ROBOHUB				0x2

//
//Data Manager Function Prototypes
//
void* RegistrationHandler(void* args);
void* CancelRegHandler(void* args);
double GetCurTime();
void TaskError(char *buf, int size, const SDMComponent_ID& RequesterId);
void Consume(char *buf, int size, const SDMComponent_ID& RequesterId);
void Cancel(char *buf, int size, const SDMComponent_ID& RequesterId);
void Command(char *buf, int size, const SDMComponent_ID& SenderId);
void Service(char *buf, int size, const SDMComponent_ID& RequesterId);
void Serreqst(const char* buf, int size, const SDMComponent_ID& RequesterId);
void ReqReg(char *buf, int size, const int xTEDref, const SDMComponent_ID& RequesterId, int xTEDSAction);
void Search(char *buf, int size, const SDMComponent_ID& RequesterId, int xTEDref);
int SendAckMessage(short sAckStatus, bool bUseComponentId, const SDMComponent_ID& idDest, const SDMComHandle& AppHandle, bool bForceSend = false);
void* xTEDS(void* arg);//char *buf, int size, char *ipaddr
void* CancelxTEDS(void* arg);//char *buf, int size, char *ipaddr);
void ReqxTEDS(char *buf, int size, const SDMComponent_ID& RequesterId);
void Subscribe( const SDMComponent_ID& RequesterId, const SDMMessage_ID& mID);
void CancelSubscription(const SDMComponent_ID& RequesterId, int mID);
void PublishxTEDSModificationSubscription(unsigned long SensorID, int MessageID, int ModificationAction, int xTEDSRef);
void PublishNotification(unsigned long SensorID, SDMMessage_ID MessageID, int ModificationAction = MOD_NOT_APPLICABLE);
void Publish(SubscriptionListNode* node, unsigned long sID, int mID, int xTEDref);
void Ready(char *buf, int size, const SDMComponent_ID& RequesterId);
void ServicePublish(const SDMComponent_ID& RequesterId, unsigned int sID, const SDMMessage_ID& DataReplyId, int seq_num);
void TAT(char *buf, int size, const SDMComponent_ID& RequesterId);
void PipeInit();
void* ChildFunctionCallProcess(void*);
void* UdpListenerProcess(void*);
void* TcpListenerProcess(void*);
void PrintxTEDS();
xTEDSLibraryListNode* AlreadyRegistered(char* sensor, const char* buf, unsigned short port, SDMComponent_ID& idAddr, int type, int& spot);
xTEDSLibraryListNode* StoreInfo(char* sensor, int& spot, const SDMComponent_ID& idAddr, const char* buf, int type);
void PostTask(xTEDSLibraryListNode* node);
void MessageSent(SDMmessage *msg);
void MessageReceived(SDMmessage *msg);
xTEDSLibraryListNode* MatchSID(long sID);
void* UpdatexTEDS(void* arg);
void* SendxTEDS(void* arg);
void MergexTEDS(xTEDSLibraryListNode* flag, bool update, SDMxTEDS& ted, int xTEDref);
bool MergexTEDS(xTEDSLibraryListNode* flag, bool update, SDMxTEDS& ted, int xTEDref, int Hubvalue);
void VarReq(char* buf, int size, const SDMComponent_ID& RequesterId, int xTEDref);
bool IAmElected();
#ifndef WIN32
void* SigHandler(void*);
#else
void SigHandler(int);
#endif //WIN32


#ifdef PNP_BACKUP
void NMElection(MessageManager* mm);
bool AmIPrimary(MessageManager* mm);
void* Heartbeat(void*);
void QueueHeartbeat (char buf[], long length);
void NonElected(MessageManager* mm);
int RunBackupListener(void);
void BackupModifyReqRegSubscription(const char* msgBuf);
void BackupModifySearchSubscription(const char* msgBuf);
void BackupModifyVarReqSubscription(const char* msgBuf);
void BackupConsume(const char* msgBuf);
void BackupTaskError(const char* msgBuf);
#ifdef PNP_FAKE
void DMSendIMA();
#endif      //PNP_FAKE
#endif      //PNP_BACKUP



#define xsize 25

#endif	//->#ifndef __SDM_DM_H_
