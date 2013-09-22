#include <string.h>
#include <stdio.h>
#include "SDMTat.h"
#include "../UDPcom.h"

SDMTat::SDMTat():destination(),seconds(0),useconds(0)
{
	MsgName = SDM_Tat;
	total_length = 18;
}

long SDMTat::Send()
{
	return SendDM();
}

long SDMTat::Recv(long port)
{
	long result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	return result;
}

long SDMTat::Marshal(char* buf)
{
	int cur;
	cur = HEADER_SIZE;
	cur += destination.Marshal(buf,cur);
	PUT_ULONG (&buf[cur], seconds);
	cur += sizeof(seconds);
	PUT_ULONG (&buf[cur], useconds);
	cur += sizeof(useconds);
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMTat::Unmarshal(const char* buf)
{
	int cur;
	cur = UnmarshalHeader(buf);
	if(cur == SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(total_length!=msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	cur += destination.Unmarshal(buf,cur);
	seconds = GET_ULONG (&buf[cur]);
	cur += sizeof(seconds);
	useconds = GET_ULONG (&buf[cur]);
	cur += sizeof(useconds);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

long SDMTat::Send(const SDMComponent_ID& destination)
{
	int result;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}
int SDMTat::MsgToString(char *str_buf, int length) const
{
	char dest_id[40];

	if (length < 8096)
		return 0;
	destination.IDToString(dest_id, 40);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMTat %ld:%ld %ld bytes, Dest: %s Seconds: %ld USeconds: %ld", sec, subsec, msg_length, dest_id, seconds, useconds);
	return strlen(str_buf);
}
