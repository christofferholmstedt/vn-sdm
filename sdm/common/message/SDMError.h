#ifndef __SDM_ERROR_H
#define __SDM_ERROR_H

#include "SDMmessage.h"
#include "SDMMessage_ID.h"

class SDMLIB_API SDMError: public SDMmessage
{
public :
	SDMComponent_ID source;		//source of error
	unsigned char error;		//an error code
	SDMMessage_ID msg_id;		//message id producing the error
	char error_msg[256];
	SDMError();
	long Send();
	long Send(const SDMComponent_ID& destination);
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int length) const;
};

#endif
