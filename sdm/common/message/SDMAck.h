#ifndef __SDM_ACK_H_
#define __SDM_ACK_H_
#include "SDMmessage.h"
#include "SDMComponent_ID.h"
#include "../SDMComHandle.h"

//This class is intended for use by only SDM core components

class SDMLIB_API SDMAck : public SDMmessage
{
public:
	short error;		//Error code if any
	SDMAck();
	long Send();
	long Send(const SDMComHandle& Handle);
	long Marshal(char *buf);
	long Unmarshal(const char *buf);
	int MsgToString(char *buf, int length) const;
};

#endif
