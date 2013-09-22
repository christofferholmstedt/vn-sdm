#include <string.h>
#include <stdio.h>
#include "SDMReady.h"
#include "../UDPcom.h"

SDMReady::SDMReady():destination(), source()
{
	MsgName = SDM_Ready;
	total_length = 20;
}

long SDMReady::Send()
{
	if (destination.getPort() == PORT_PM)
		return SendTM();
	return SendDM();
}

long SDMReady::Send(const SDMComponent_ID& destination)
{
	return SendTo(destination);
}

long SDMReady::Sendtcp(const SDMComponent_ID& destination)
{
	return SendTCP(destination.getAddress(),destination.getPort());
}

//addr must be in network byte order
long SDMReady::SendBCast(long addr, unsigned short dest_port)
{
	return SendBroadcast(addr,dest_port);
}

long SDMReady::Marshal(char* buf)
{
	int cur = HEADER_SIZE;
	cur += source.Marshal(buf, cur);
	cur += destination.Marshal(buf,cur);
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMReady::Unmarshal(const char* buf)
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
	cur += source.Unmarshal(buf, cur);
	cur += destination.Unmarshal(buf,cur);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return HEADER_SIZE+msg_length;
}
int SDMReady::MsgToString(char *str_buf, int length) const
{
	char dest_id[40];
	char source_id[40];

	if (length < 8096)
		return 0;
	destination.IDToString(dest_id, 40);
	source.IDToString(source_id, 40);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMReady %ld:%ld %ld bytes, Source: %s Dest: %s", sec, subsec, msg_length, source_id, dest_id);
	return (int)strlen(str_buf);
}
