#include <stdio.h>
#include <string.h>
#include "SDMHello.h"

SDMHello::SDMHello() : type('D')
{
	MsgName = SDM_Hello;
	total_length = 11;
}

long SDMHello::Send()
{
	return SendDM();
}

long SDMHello::Marshal(char* buf)
{
	int cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	PUT_CHAR(&buf[cur], type);
	cur += sizeof(char);
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMHello::Unmarshal(const char* buf)
{
	int cur = UnmarshalHeader(buf);
	if(cur == SDM_INVALID_MESSAGE || total_length != msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	cur += source.Unmarshal(buf,cur);
	type = GET_CHAR(&buf[cur]);
	cur += sizeof(char);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

int SDMHello::MsgToString(char* buf, int length) const
{
	if (length < 8096)
		return 0;
#ifdef WIN32
	sprintf(buf,
#else
 	snprintf(buf,length,
#endif
        "SDMHello %ld:%ld %ld bytes, error: %c", sec, subsec, msg_length, type);
	return (int)strlen(buf);
}
