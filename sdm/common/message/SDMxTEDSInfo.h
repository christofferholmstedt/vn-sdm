#ifndef __SDM_XTEDSINFO_H_
#define __SDM_XTEDSINFO_H_

#include "SDMmessage.h"

class SDMLIB_API SDMxTEDSInfo: public SDMmessage
{
public :
	SDMComponent_ID source;	//unique id of xTEDS provider
	char xTEDS[LARGE_MSG_BUFSIZE - 21];	//xTEDS registered with SDM system
	SDMxTEDSInfo();
	long Send();
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	long Recv(long port); SDM_DEPRECATED
	long Send(const SDMComponent_ID& destination);
	long MarshalEmpty(char* buf);
	long SendEmpty(const SDMComponent_ID& destination);
	int MsgToString(char *str_buf, int length) const;

private:
	bool emptyflag;		//A flag to be set when wanting to send an empty message
};

#endif
