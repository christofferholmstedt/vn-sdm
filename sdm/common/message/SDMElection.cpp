#include <stdio.h>
#include <string.h>
#include "SDMElection.h"

SDMElection::SDMElection()
{
	MsgName = SDM_Election;
	total_length = 0;
}
SDMElection::~SDMElection()
{
}
long SDMElection::Marshal(char *buf)
{
	int cur = HEADER_SIZE;

	MarshalHeader(buf);
	return cur;
}

long SDMElection::Unmarshal(const char*buf)
{
	int cur = 0;
	cur = UnmarshalHeader(buf);
	if (cur == SDM_INVALID_MESSAGE)
		return SDM_INVALID_MESSAGE;
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

//SDMElection messages send via Broadcast
long SDMElection::Send()
{
	return SendBroadcast();
}

int SDMElection::MsgToString(char *str_buf, int length) const
{
	if (length < 8096)
		return 0;
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMElection %ld:%ld %ld bytes", sec, subsec, msg_length);
	return (int)strlen(str_buf);
}
