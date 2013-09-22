#ifndef _PM_IDS_H_
#define _PM_IDS_H_

#define TM_Mode_ID	1		//ID number used in RegInfo and ReqReg messages for TM's status message

void HandleCodeMessage(const char* buf);
void ReqRegSubs(void);
void TaskHandler(const char* buf);
void RegInfoHandler(const char* buf);
void DataHandler (const char *buf);
void CancelReqRegSubs();
bool GetCode (const char* filename, long pid, int version, int fd_readcode);

#endif
