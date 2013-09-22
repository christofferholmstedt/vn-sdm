#ifndef __SDM_REG_PM_H_
#define __SDM_REG_PM_H_

#include "SDMmessage.h"
#include "SDMComponent_ID.h"

//This is intended only for use by SDM core components

class SDMLIB_API SDMRegPM: public SDMmessage
{
public :
	SDMComponent_ID source;		//The PM registering with the TM
	unsigned short resources;	//an enumeration of the resources of a processor
	SDMRegPM();
	long Send();
	long Send(const SDMComponent_ID& destination);
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *buf, int length) const;
};

#endif
