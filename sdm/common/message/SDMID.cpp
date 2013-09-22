#include <string.h>
#include <stdio.h>
#include "SDMID.h"


SDMID::SDMID():destination()
{
	MsgName = SDM_ID;
	total_length = 10;
}

long SDMID::Marshal(char *buf)
{
	int cur = HEADER_SIZE;
	cur += destination.Marshal(buf, cur);
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMID::Unmarshal(const char * buf)
{
	int cur = UnmarshalHeader(buf);
	if (cur==SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if (total_length != msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	cur += destination.Unmarshal(buf, cur);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

int SDMID::MsgToString(char * str_buf, int length) const
{
	char destination_id[40];

	if (length < 8096)
		return 0;
	destination.IDToString(destination_id, 40);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMID %ld:%ld %ld bytes, Source: %s", sec, subsec, msg_length, destination_id);
	return (int)strlen(str_buf);
}
