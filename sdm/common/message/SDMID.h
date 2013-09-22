#ifndef __SDM_ID_H_
#define __SDM_ID_H_

#include "SDMmessage.h"


class SDMLIB_API SDMID: public SDMmessage
{
public:
	SDMComponent_ID destination;			//The destination of the ID msg

	SDMID();
	long Marshal(char *buf);
	long Unmarshal(const char * buf);
	int MsgToString(char *str_buf, int length) const;
};
#endif
