#ifndef _PM_H_
#define _PM_H_

#define TM_Mode_ID	1		//ID number used in RegInfo and ReqReg messages for TM's status message

extern void MessageSent(SDMmessage*);
extern void MessageReceived(SDMmessage*);
extern void SendRunningTasks(void);
extern void RegisterPM(void);
extern void DoReset(void);


void CancelReqRegSubs();
void ReqRegSubs();
void RegInfoHandler(const char* buf);
void DataHandler (const char *buf);
void HandleCodeMessage(const char* buf);
bool GetCode (const char* filename, long pid, int version, int fd_readcode);

#endif
