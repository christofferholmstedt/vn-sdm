#ifndef __SDM_CANCEL_XTEDS_H_
#define __SDM_CANCEL_XTEDS_H_

#include "SDMmessage.h"

class SDMLIB_API SDMCancelxTEDS: public SDMmessage
{
public :
	SDMComponent_ID source;		//the xTEDS provider
	unsigned char fullCancel;  //0 to deactivate an xTEDS, 1 to completey remove it
	SDMCancelxTEDS();
	long Send();
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int length) const;
};

#endif
