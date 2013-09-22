#ifndef __SDM_VAR_REQ_H_
#define __SDM_VAR_REQ_H_
#include "SDMmessage.h"
#include "SDMComponent_ID.h"
#include "SDMMessage_ID.h"

#define SDM_VARREQ_CURRENT 				0
#define SDM_VARREQ_CURRENT_AND_FUTURE			5
#define SDM_VARREQ_CANCEL				11

class SDMLIB_API SDMVarReq : public SDMmessage
{
public:
	SDMVarReq();
	SDMComponent_ID source;				//The id of the provider who's variables to request
	SDMComponent_ID destination;			//The id of the requester
	unsigned char reply;				//style of reply desired (see above)
	SDMMessage_ID msg_id;				//The interface containing the needed variables
	unsigned short id;				//Identifier number of this request
	char variable[XTEDS_MAX_ITEM_NAME_SIZE];	//The name of the variable
	long Marshal(char *buf);
	long Unmarshal(const char *buf);
	long Send();
	int MsgToString(char *str_buf, int length) const;
};

#endif
