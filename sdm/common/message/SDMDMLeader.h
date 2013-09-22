#ifndef __SDM_DM_LEADER_H_
#define __SDM_DM_LEADER_H_

#include "SDMmessage.h"
#include "SDMComponent_ID.h"

//This class is intended for use by only SDM core components

class SDMLIB_API SDMDMLeader : public SDMmessage
{
public:
	SDMComponent_ID source;		//The DM who sent the message
	char running_flag;		//This flag specifies that this DM is already running and overrides any smaller addresses
	SDMDMLeader();
	~SDMDMLeader();
	long Marshal(char *buf);
	long Unmarshal(const char *buf);
	long Send();
	int MsgToString(char *str_buf, int length) const;
private:
};

#endif
