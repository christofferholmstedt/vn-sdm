#ifndef __SDM_HELLO_H_
#define __SDM_HELLO_H_
#include "SDMmessage.h"



class SDMLIB_API SDMHello : public SDMmessage
{
public:
	SDMComponent_ID source;
	char type;		//Component Type.  'D'=Device, 'A'=Application

	SDMHello();
	long Send();
	long Marshal(char *buf);
	long Unmarshal(const char *buf);
	int MsgToString(char *buf, int length) const;
};

#endif
