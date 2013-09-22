#ifndef __SDM_REQREG_H_
#define __SDM_REQREG_H_

#include "SDMmessage.h"

#define SDM_REQREG_CURRENT 				0
#define SDM_REQREG_CURRENT_AND_FUTURE			5
#define SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS	7
#define SDM_REQREG_CANCEL				11

#define QUALLIST_MAX_SIZE		1024

class SDMLIB_API SDMReqReg: public SDMmessage
{
public :
	SDMComponent_ID source;		//optional componentID of the xTEDS provider to search
	SDMComponent_ID destination;	//the subscriber
	unsigned char reply;		//value indicating the style of reply desired see #defines above
	unsigned short id;		//id of this request
	char device[XTEDS_MAX_ITEM_NAME_SIZE];		//optional name of the device or application to search
	char interface[XTEDS_MAX_ITEM_NAME_SIZE];	//optional name of the interface to search
	char item_name[XTEDS_MAX_ITEM_NAME_SIZE];	//optional buffer containing item name to look for
	char quallist[QUALLIST_MAX_SIZE];	//optional buffer containing qualifications for item
	SDMReqReg();
	long Send();
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *buf, int length) const;
};

#endif
