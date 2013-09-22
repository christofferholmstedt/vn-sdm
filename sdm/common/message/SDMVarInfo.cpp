#include <string.h>
#include <stdio.h>
#include "SDMVarInfo.h"

SDMVarInfo::SDMVarInfo():source(),id(0),emptyflag(false)
{
	MsgName = SDM_VarInfo;
	total_length = 14;
	interface[0] = '\0';
	var_xTEDS[0] = '\0';
}

long SDMVarInfo::Marshal(char *buf)
{
	int cur = HEADER_SIZE;
	if(emptyflag == true)
	{
		cur = MarshalEmpty(buf);
		return cur;
	}
	cur += source.Marshal(buf, cur);
	PUT_USHORT(buf+cur, id);
	cur += sizeof(id);
	strcpy(buf+cur, interface);	//Copy the interface string field
	cur += strlen(interface) + 1;	//Cur pointer is the size of the string plus null terminator
	strcpy(buf+cur, var_xTEDS);	//Copy the variable string field
	cur += strlen(var_xTEDS) + 1;	//Cur pointer is the size of the string plus null terminator
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMVarInfo::Unmarshal(const char *buf)
{
	int cur = UnmarshalHeader(buf);
	if (cur == SDM_INVALID_MESSAGE)
		return SDM_INVALID_MESSAGE;
	if (msg_length == 0)
		return SDM_NO_FURTHER_DATA_PROVIDER;
	if (total_length > msg_length)
		return SDM_INVALID_MESSAGE;
	cur += source.Unmarshal(buf, cur);
	id = GET_USHORT(buf+cur);
	cur += sizeof(id);
	strcpy(interface, buf+cur);
	cur += strlen(interface) + 1;
	strcpy(var_xTEDS, buf+cur);
	cur += strlen(var_xTEDS) + 1;
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

long SDMVarInfo::MarshalEmpty(char* buf)
{
	int cur;
	msg_length = 0;
	cur = MarshalHeader(buf);
	return cur;
}

long SDMVarInfo::Send(const SDMComponent_ID& destination)
{
	int result;
	emptyflag = false;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}

long SDMVarInfo::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	if (result == 1)
		return SDM_NO_FURTHER_DATA_PROVIDER;
	return result;
}

long SDMVarInfo::SendEmpty(const SDMComponent_ID& destination)
{
	int result;
	emptyflag = true;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}

int SDMVarInfo::MsgToString(char *str_buf, int length) const
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
        "SDMVarInfo %ld:%ld %ld bytes, Source: %s id: %hu interface: %s var_xTEDS: %s", sec, subsec, msg_length, source_id, id, interface, var_xTEDS);
	return strlen(str_buf);
}
