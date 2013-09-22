#ifndef __SDM_REGISTER_H_
#define __SDM_REGISTER_H_

#include "SDMmessage.h"


class SDMLIB_API SDMRegister : public SDMmessage
{
public:
   short sensorIndex;

	SDMRegister();
	long Marshal(char *buf);
	long Unmarshal(const char *buf);
	int MsgToString(char *str_buf, int length) const;
private:
};

#endif
