#include <stdio.h>
#include <string.h>
#include "SDMAck.h"

SDMAck::SDMAck() : error(0)
{
	MsgName = SDM_ACK;
	total_length = 2;
}

long SDMAck::Send()
{
	return SendDM();
}

long SDMAck::Send(const SDMComHandle& Handle)
{
	if (Handle.IsValidHandle())
		return SendReplyTo(Handle.GetSock(), Handle.GetAddress(), Handle.IsTcp());
	return -1;
}

long SDMAck::Marshal(char *buf)
{
	int cur = HEADER_SIZE;
	PUT_SHORT(buf+cur,error);
	cur += sizeof(error);
	msg_length = cur-HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMAck::Unmarshal(const char * buf)
{
	int cur = UnmarshalHeader(buf);
	if (cur == SDM_INVALID_MESSAGE || total_length != msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	error = GET_SHORT(buf+cur);
	cur += sizeof(error);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

int SDMAck::MsgToString(char *buf, int length) const
{
	if (length < 8096)
		return 0;
#ifdef WIN32 // cleanup - remove duplicate code for maintainability
	sprintf(buf,
#else
 	snprintf(buf,length,
#endif
	        "SDMAck %ld:%ld %ld bytes, error: %hd", sec, subsec, msg_length, error);
return (int)strlen(buf);
}
