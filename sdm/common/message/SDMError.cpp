#include <stdio.h>
#include <string.h>
#include "SDMError.h"
#include "../UDPcom.h"
#include "SDMmessage.h"

SDMError::SDMError():source(),error(0),msg_id(0,0),error_msg()
{
	MsgName = SDM_Error;
	total_length = 13;
	error_msg[0] = '\0';
}

long SDMError::Send()
{
	return SendDM();
}

long SDMError::Send(const SDMComponent_ID& destination)
{
	return SendTo(destination);
}

long SDMError::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	return result;
}

long SDMError::Marshal(char* buf)
{
	int cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	cur += msg_id.Marshal(buf, cur);
	PUT_UCHAR (&buf[cur], error);
	cur += sizeof(error);
	
	unsigned int uiCurLength = (unsigned int)strlen(error_msg);
	strncpy(buf + cur, error_msg, uiCurLength + 1);
	cur += uiCurLength + 1;
	
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return HEADER_SIZE+msg_length;
}

long SDMError::Unmarshal(const char* buf)
{
	int cur;
	cur = UnmarshalHeader(buf);
	if(cur==SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(total_length>msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	cur += source.Unmarshal(buf,cur);
	cur += msg_id.Unmarshal(buf, cur);
	error = GET_UCHAR (&buf[cur]);
	cur += sizeof(error);
	
	unsigned int uiMsgLength = (unsigned int)strlen(buf + cur);
	strncpy(error_msg, buf + cur, sizeof(error_msg));
	if (uiMsgLength > sizeof(error_msg) - 1)
		error_msg[sizeof(error_msg) - 1] = '\0';
	
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return HEADER_SIZE+msg_length;
}
int SDMError::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	char message_id[30];

	if (length < 8096)
		return 0;
	source.IDToString(source_id, 40);
	msg_id.IDToString(message_id, 30);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMError %ld:%ld %ld bytes, Source: %s %s Error: %d", sec, subsec, msg_length, source_id, message_id, error);
	return (int)strlen(str_buf);
}
