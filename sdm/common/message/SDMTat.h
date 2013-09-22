#ifndef __SDM_TAT_H
#define __SDM_TAT_H

#include "SDMmessage.h"

class SDMLIB_API SDMTat: public SDMmessage
{
public :
	SDMComponent_ID destination;	//unique id of device
					//total time given as seconds + useconds
	unsigned long seconds;		//time in seconds
	unsigned long useconds;		//time in useconds

	SDMTat();
	long Send();
	long Send(const SDMComponent_ID& destination);
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int length) const;
};

#endif
