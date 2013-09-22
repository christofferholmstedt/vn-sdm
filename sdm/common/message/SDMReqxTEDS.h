#ifndef __SDM_REQXTEDS_H_
#define __SDM_REQXTEDS_H_

#include "SDMmessage.h"

class SDMLIB_API SDMReqxTEDS: public SDMmessage
{
public :
	char select;			//indicates whether sensor id or device name is used
	SDMComponent_ID destination;	//the subscriber who wants the xTEDS
	SDMComponent_ID source;		//unique id of xTEDS provider
	char device_name[XTEDS_MAX_ITEM_NAME_SIZE];	//device name of xTEDS provider
	SDMReqxTEDS();
	long Send();
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int length) const;
};

#endif
