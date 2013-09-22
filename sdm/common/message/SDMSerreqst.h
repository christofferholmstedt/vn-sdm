#ifndef __SDM_SERREQST_H_
#define __SDM_SERREQST_H_

#include "SDMmessage.h"
#include "SDMMessage_ID.h"

class SDMLIB_API SDMSerreqst: public SDMmessage
{
public :
	SDMComponent_ID source;		//the service provider
	SDMComponent_ID destination;	//the subscriber
	SDMMessage_ID command_id;	//unique id of command portion of service
	SDMMessage_ID reply_id;		//unique id of expected data reply message
	SDMMessage_ID fault_id;		//unique id of possible fault message, may be 0 for no fault
	short length;			//length of data portion
	short seq_num;			//a sequence number for sync purposes
	char data[BUFSIZE-39];		//raw data to be processed
	SDMSerreqst();
	long Send(const SDMComponent_ID& destination);
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int length) const;
};

#endif
