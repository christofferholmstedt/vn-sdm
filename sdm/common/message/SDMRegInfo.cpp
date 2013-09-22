#include <string.h>
#include <stdio.h>
#include "SDMRegInfo.h"
#include "../UDPcom.h"

SDMRegInfo::SDMRegInfo():id(0),type(0),source(),msg_id(0,0),emptyflag(false)
{
	MsgName = SDM_RegInfo;
	msg_def[0] = '\0';
	xTEDS_section[0] = '\0';
	total_length = 16;
}

long SDMRegInfo::Send(const SDMComponent_ID& destination)
{
	int result;
	emptyflag = false;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}

long SDMRegInfo::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	if (result == 1)
		return SDM_NO_FURTHER_DATA_PROVIDER;
	return result;
}

long SDMRegInfo::Marshal(char* buf)
{
	int cur;
	if(emptyflag == true)
	{
		cur = MarshalEmpty(buf);
		return cur;
	}
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	cur += msg_id.Marshal(buf, cur);
	PUT_USHORT (&buf[cur], id);
	cur += sizeof(id);
	PUT_UCHAR  (&buf[cur], type);
	cur += sizeof(type);
	strcpy(buf+cur, msg_def);
	cur += (int)strlen(msg_def) + 1;		//Add the string length plus the null terminator
	strcpy(buf+cur, xTEDS_section);
	cur += (int)strlen(xTEDS_section) + 1;	//Add the string length plus the null terminator
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMRegInfo::Unmarshal(const char* buf)
{
	int cur;
	cur = UnmarshalHeader(buf);
	if(cur==SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(msg_length == 0)
		return SDM_NO_FURTHER_DATA_PROVIDER;
	if(total_length>msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	cur += source.Unmarshal(buf,cur);
	cur += msg_id.Unmarshal(buf, cur);
	id = GET_USHORT (&buf[cur]);
	cur += sizeof(id);
	type = GET_UCHAR (&buf[cur]);
	cur += sizeof(type);
	strcpy(msg_def, buf+cur);
	cur += (int)strlen(msg_def) + 1;		//Add strlen plus null terminator
	strcpy(xTEDS_section, buf+cur);
	cur += (int)strlen(xTEDS_section) + 1;	//Add strlen plus null terminator
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

long SDMRegInfo::MarshalEmpty(char* buf)
{
	int cur;
	msg_length = 0;
	cur = MarshalHeader(buf);
	return cur;
}

long SDMRegInfo::SendEmpty(const SDMComponent_ID& destination)
{
	int result;
	emptyflag = true;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}

int SDMRegInfo::MsgToString(char *str_buf, int length) const
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
        "SDMRegInfo %ld:%ld %ld bytes, Source: %s %s ID: %d Type: %d MsgDef: %s", sec, subsec, msg_length, source_id, message_id, id, type, msg_def);
	return (int)strlen(str_buf);
}
