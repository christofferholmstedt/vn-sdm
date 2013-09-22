#ifndef __SDM_ELECTION_H_
#define __SDM_ELECTION_H_

#include "SDMmessage.h"

//This class is intended for use by only SDM core components

class SDMLIB_API SDMElection : public SDMmessage
{
public:
	SDMElection();
	~SDMElection();
	long Marshal(char *buf);
	long Unmarshal(const char *buf);
	int MsgToString(char *str_buf, int length) const;
	long Send();
private:
};

#endif
