#include <string.h>
#include <stdio.h>
#include "SDMxTEDSInfo.h"
#include "../UDPcom.h"

SDMxTEDSInfo::SDMxTEDSInfo():source(),emptyflag(false)
{
	MsgName = SDM_xTEDSInfo;
	xTEDS[0] = '\0';
	total_length = HEADER_SIZE;
}

long SDMxTEDSInfo::Send()
{
	return SendDM();
}

long SDMxTEDSInfo::Marshal(char* buf)
{
	int cur;
	if(emptyflag == true)
	{
		cur = MarshalEmpty(buf);
		return cur;
	}
	cur = HEADER_SIZE;
	long i= strlen(xTEDS);
	cur += source.Marshal(buf,cur);
	memcpy(buf+cur,xTEDS,i+1);
	cur += i + 1;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMxTEDSInfo::Unmarshal(const char* buf)
{
	int cur;
	cur = UnmarshalHeader(buf);
	if(cur==SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(msg_length == 0)
		return SDM_NO_FURTHER_XTEDS;
	if(total_length>msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	cur += source.Unmarshal(buf,cur);
	//
	// Get the xTEDS
	unsigned int uiCurLength = strlen(buf + cur);
	strncpy(xTEDS, buf + cur, sizeof(xTEDS));
	if (uiCurLength > sizeof(xTEDS) - 1)
		xTEDS[sizeof(xTEDS) - 1] = '\0';

#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return msg_length + HEADER_SIZE;
}

long SDMxTEDSInfo::Send(const SDMComponent_ID& destination)
{
	int result;
	emptyflag = false;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}

long SDMxTEDSInfo::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	return result;
}

long SDMxTEDSInfo::MarshalEmpty(char* buf)
{
	int cur;
	msg_length = 0;
	cur = MarshalHeader(buf);
	return cur;
}

long SDMxTEDSInfo::SendEmpty(const SDMComponent_ID& destination)
{
	int result;
	emptyflag = true;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}

int SDMxTEDSInfo::MsgToString(char *str_buf, int length) const
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
        "SDMxTEDSInfo %ld:%ld %ld bytes, Source: %s xTEDS: %s", sec, subsec, msg_length, source_id, xTEDS);
	return strlen(str_buf);
}
