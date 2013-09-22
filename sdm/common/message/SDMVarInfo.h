#ifndef __SDM_VAR_INFO_H_
#define __SDM_VAR_INFO_H_
#include "SDMmessage.h"
#include "SDMComponent_ID.h"
#include "SDMRegInfo.h"

class SDMLIB_API SDMVarInfo : public SDMmessage
{
public:
	SDMVarInfo();
	SDMComponent_ID source;				//The source corresponding to the reply
	unsigned short id;				//Identifier number of this request
	char interface[XTEDS_MAX_ITEM_NAME_SIZE];	//The name of the Interface the variable resides in
	char var_xTEDS[BUFSIZE-78];			//Returned variable information
	long Marshal(char *buf);
	long Unmarshal(const char *buf);
	long Send(const SDMComponent_ID& destination);
	long Recv(long port); SDM_DEPRECATED
	long MarshalEmpty(char* buf);
	long SendEmpty(const SDMComponent_ID& destination);
	int MsgToString(char *str_buf, int length) const;
	
private:
	bool emptyflag;	
};



#endif
