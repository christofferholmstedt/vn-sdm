#ifndef __SDM_KILL_H_
#define __SDM_KILL_H_

#include "SDMmessage.h"

class SDMLIB_API SDMKill: public SDMmessage
{
public :
	unsigned long PID;		//The pid of the process to kill
	unsigned char killLevel;  //0 to restart process if data is requested, 1 to completely kill task
	SDMKill();
	long Send();
	long Send(const SDMComponent_ID& destination);
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int lenght) const;
};

#endif
