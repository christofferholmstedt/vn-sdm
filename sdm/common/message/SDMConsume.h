#ifndef __SDM_CONSUME_H_
#define __SDM_CONSUME_H_

#include "SDMmessage.h"
#include "SDMMessage_ID.h"

class SDMLIB_API SDMConsume: public SDMmessage
{
public :

	SDMComponent_ID source;		//the data provider
	SDMComponent_ID destination;	//the subscriber
	SDMMessage_ID msg_id;		//unique id of desired data message as defined in the xTEDS of provider
	SDMConsume();
	long Send();
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int length) const;
};

#endif
