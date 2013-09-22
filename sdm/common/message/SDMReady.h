#ifndef __SDM_READY_H_
#define __SDM_READY_H_

#include "SDMmessage.h"

//This class is intended for use by only SDM core components

class SDMLIB_API SDMReady: public SDMmessage
{
public :
	SDMComponent_ID destination;		//The originator of the Ready message for sensor_id and port, and the address of node being sent to
	SDMComponent_ID source;		//The address of the sender, for heartbeat messages
	SDMReady();
	long Send();
	long Send(const SDMComponent_ID& destination);
	long Sendtcp(const SDMComponent_ID& destination);
	long SendBCast(long addr, unsigned short dest_port);
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int lenght) const;
};

#endif
