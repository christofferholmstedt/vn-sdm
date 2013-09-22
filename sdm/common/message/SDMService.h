#ifndef __SDM_SERVICE_H_
#define __SDM_SERVICE_H_

#include "SDMmessage.h"
#include "SDMMessage_ID.h"

class SDMLIB_API SDMService: public SDMmessage
{
public :
	SDMComponent_ID source;		//the service provider
	SDMComponent_ID destination;	//the subscriber
	SDMMessage_ID command_id;	//unique id of command portion of service
	short length;			//number of bytes in the data portion
	short seq_num;			//a sequence number for sync purposes
	char data[BUFSIZE-35];		//data to be passed to service provider
	SDMService();
	long Send();
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int length) const;
};

#endif
