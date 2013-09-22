#ifndef __SDM_REGINFO_H_
#define __SDM_REGINFO_H_

#define SDM_REGINFO_REGISTRATION	0
#define SDM_REGINFO_CANCELLATION	1

#include "SDMmessage.h"
#include "SDMMessage_ID.h"

class SDMLIB_API SDMRegInfo: public SDMmessage
{
public :
	unsigned short id;			//the id of the SDMReqReg resulting in this SDMRegInfo
	unsigned char type;			//switch indicating if message is the result of a regestration or cancellation
	SDMComponent_ID source;			//unique id of xTEDS provider
	SDMMessage_ID msg_id;			//unique id of data message
	char msg_def[MSG_DEF_SIZE];		//annotated summary of data message
	char xTEDS_section[MSG_DEF_SIZE];	//section of the full data message definition in the xTEDS
	SDMRegInfo();
	long Send(const SDMComponent_ID& destination);
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	long MarshalEmpty(char* buf);
	long SendEmpty(const SDMComponent_ID& destination);
	int MsgToString(char *str_buf, int length) const;

private:
	bool emptyflag;			//This flag is set for sending and empty SDMRegInfo message
};

#endif
