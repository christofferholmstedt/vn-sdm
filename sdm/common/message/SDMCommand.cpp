#include <string.h>
#include <stdio.h>
#include "SDMCommand.h"

SDMCommand::SDMCommand():fault_id(0,0)
{
	MsgName = SDM_Command;
	total_length = 24;
}

long SDMCommand::Send()
{
	return SendDM();
}

long SDMCommand::Send(const SDMComponent_ID& destination)
{
	return SendTo(destination);
}

long SDMCommand::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	return result;
}

long SDMCommand::Marshal(char* buf)
{
	int cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	cur += destination.Marshal(buf,cur);
	cur += command_id.Marshal(buf, cur);
	cur += fault_id.Marshal(buf, cur);
	memcpy(buf+cur,&data,length);
	cur+=length;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMCommand::Unmarshal(const char* buf)
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
	cur += destination.Unmarshal(buf,cur);
	cur += command_id.Unmarshal(buf, cur);
	cur += fault_id.Unmarshal(buf, cur);
	length = msg_length - cur + HEADER_SIZE;
	memcpy(&data,buf+cur,length);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return msg_length+HEADER_SIZE;
}
int SDMCommand::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	char destination_id[40];
	char data_section[511];
	char cmd_id[30];
	char flt_id[30];
	int i, j;
	if (length < 8096)
		return 0;
	for (i = 0, j = 0; j < this->length && i < 510; i+=2, j++)
	{
		sprintf(&data_section[i], "%.2x", data[j]);
	}
	data_section[i] = '\0';

	source.IDToString(source_id, 40);
	destination.IDToString(destination_id, 40);
	command_id.IDToString(cmd_id, 30);
	fault_id.IDToString(flt_id, 30);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMCommand %ld:%ld %ld bytes, Source: %s Destination: %s CommandID: %s FaultID: %s [DATA SECTION: %s ]", sec, subsec, msg_length, source_id, destination_id, cmd_id, flt_id, data_section);
	return (int)strlen(str_buf);
}
