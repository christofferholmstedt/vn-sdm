#include <stdio.h>
#include <string.h>
#include "SDMDMLeader.h"

SDMDMLeader::SDMDMLeader(): source(),running_flag(0)
{
	MsgName = SDM_DMLeader;
	total_length = 11;
}
SDMDMLeader::~SDMDMLeader()
{
}

long SDMDMLeader::Marshal(char *buf)
{
	int cur = HEADER_SIZE;
	cur += source.Marshal(buf, cur);
	PUT_CHAR(&buf[cur], running_flag);
	cur++;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMDMLeader::Unmarshal(const char *buf)
{
	int cur = 0;
	cur = UnmarshalHeader(buf);
	if (cur == SDM_INVALID_MESSAGE)
		return SDM_INVALID_MESSAGE;
	if (total_length != msg_length)
		return SDM_INVALID_MESSAGE;
	cur += source.Unmarshal(buf,cur);
	running_flag = GET_CHAR(&buf[cur]);
	cur++;
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

//SDMDMLeader messages are sent via Broadcast
long SDMDMLeader::Send()
{
	return SendBroadcast();
}
int SDMDMLeader::MsgToString(char *str_buf, int length) const
{
	char source_id[40];

	if (length < 8096)
		return 0;
	source.IDToString(source_id, 40);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMDMLeader %ld:%ld %ld bytes, Source: %s running_flag: %c", sec, subsec, msg_length, source_id, running_flag);
	return (int)strlen(str_buf);
}
