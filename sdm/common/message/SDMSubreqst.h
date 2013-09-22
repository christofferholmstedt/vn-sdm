#ifndef __SDM_SUBREQST_H_
#define __SDM_SUBREQST_H_

#include "SDMmessage.h"
#include "SDMMessage_ID.h"

class SDMLIB_API SDMSubreqst: public SDMmessage
{
public :
	SDMComponent_ID source;		//the data source
	SDMComponent_ID destination;	//the subscriber
	SDMMessage_ID msg_id;		//the message id of the message wanted
	SDMMessage_ID fault_id;		//unique id of possible fault message, may be 0 for no fault
	SDMSubreqst();
	long Send();
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int length) const;
};

#endif
