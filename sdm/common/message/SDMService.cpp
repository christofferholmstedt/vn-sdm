#include <string.h>
#include <stdio.h>
#include "SDMService.h"

SDMService::SDMService():source(),destination(),command_id(0,0),length(0),seq_num(0)
{
	MsgName = SDM_Service;
	data[0] = '\0';
	total_length = 24;
}

long SDMService::Send()
{
	return SendDM();
}

long SDMService::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	return result;
}

long SDMService::Marshal(char* buf)
{
	int cur;
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	cur += destination.Marshal(buf,cur);
	cur += command_id.Marshal(buf, cur);
	PUT_SHORT(&buf[cur],seq_num);
	cur += sizeof(seq_num);
	memcpy(buf+cur,&data,length);
	cur += length;
	msg_length = cur-HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMService::Unmarshal(const char* buf)
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
	seq_num = GET_SHORT(&buf[cur]);
	cur += sizeof(seq_num);
	length = msg_length + HEADER_SIZE - cur;
	memcpy(&data,buf+cur,length);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return msg_length+HEADER_SIZE;
}
int SDMService::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	char dest_id[40];
	char data_section[511];
	char cmd_id[30];
	int i, j;

	if (length < 8096)
		return 0;
	for (i = 0, j = 0; j < this->length && i < 510; i+=2, j++)
	{
		sprintf(&data_section[i], "%.2x", data[j]);
	}
	data_section[i] = '\0';

	source.IDToString(source_id, 40);
	destination.IDToString(dest_id, 40);
	command_id.IDToString(cmd_id, 30);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMService %ld:%ld %ld bytes, Source: %s Dest: %s CommandID: %s seq_num: %d [DATA SECTION: %s ]", sec, subsec, msg_length, source_id, dest_id, cmd_id, seq_num, data_section);
	return (int)strlen(str_buf);
}
