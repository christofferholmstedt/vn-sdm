#ifndef __SDM_HEARTBEAT_H_
#define __SDM_HEARTBEAT_H_

#include "SDMmessage.h"

extern SDMLIB_API void SendHeartbeat();

class SDMLIB_API SDMHeartbeat: public SDMmessage
{
public:
	SDMComponent_ID source;			//The source of the heartbeat message
	SDMHeartbeat();
	long Marshal(char *buf);
	long Unmarshal(const char * buf);
	int MsgToString(char *str_buf, int length) const;
};
#endif
