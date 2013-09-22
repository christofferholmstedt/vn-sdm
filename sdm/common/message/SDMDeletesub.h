#ifndef __SDM_DELETESUB_H_
#define __SDM_DELETESUB_H_

#include "SDMmessage.h"
#include "SDMMessage_ID.h"

class SDMLIB_API SDMDeletesub: public SDMmessage
{
public :
	SDMComponent_ID source;		//data provider
	SDMComponent_ID destination;	//data consumer
	SDMMessage_ID msg_id;
	SDMDeletesub();
	long Recv(long port); SDM_DEPRECATED
	long Send();
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int length) const;
};

#endif
