#include <stdio.h>
#include <string.h>
#include "SDMRegister.h"

SDMRegister::SDMRegister()
{
	MsgName = SDM_Register;
	total_length = 2;
	sensorIndex = -1;
}

long SDMRegister::Marshal(char *buf)
{
	int cur = HEADER_SIZE;
	PUT_SHORT(&buf[cur], sensorIndex);
	cur += sizeof(short);
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMRegister::Unmarshal(const char*buf)
{
	int cur = UnmarshalHeader(buf);
	if(cur == SDM_INVALID_MESSAGE || total_length != msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	sensorIndex = GET_SHORT(&buf[cur]);
	cur += sizeof(short);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

int SDMRegister::MsgToString(char *str_buf, int length) const
{
	if (length < 8096)
		return 0;
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMRegister %ld:%ld %ld bytes", sec, subsec, msg_length);
	return (int)strlen(str_buf);
}
