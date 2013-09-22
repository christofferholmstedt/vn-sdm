#ifndef __SDM_CANCEL_H_
#define __SDM_CANCEL_H_

#include "SDMmessage.h"
#include "SDMMessage_ID.h"

class SDMLIB_API SDMCancel: public SDMmessage
{
public :
	SDMComponent_ID source;		//the data source
	SDMComponent_ID destination;	//the subscriber
	SDMMessage_ID msg_id;		//unique id of message to cancel
	SDMCancel();
	long Send();
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *buf, int length) const;
};

#endif
