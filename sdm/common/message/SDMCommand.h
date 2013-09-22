#ifndef __SDM_COMMAND_H
#define __SDM_COMMAND_H

#include "SDMService.h"

class SDMLIB_API SDMCommand:public SDMService
{
public:
	SDMMessage_ID fault_id;		//unique id of possible fault message, may be 0 for no fault
	SDMCommand();
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	long Send();
	long Send(const SDMComponent_ID& destination);
	long Recv(long port); SDM_DEPRECATED
	int MsgToString(char *str_buf, int length) const;
};

#endif
