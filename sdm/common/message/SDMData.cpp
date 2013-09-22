#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include "SDMData.h"
#include "../UDPcom.h"

SDMData::SDMData():source(),msg_id(0,0),length(0),seq_num(0),pid(PID)
{
	MsgName = SDM_Data;
	msg[0] = '\0';
	total_length = 18;
}

long SDMData::Send(const SDMComponent_ID& destination,long data_length)
{
	long result;
	length = data_length;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}

long SDMData::Send(const SDMComponent_ID& destination)
{
	long result;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}

long SDMData::Recv(long port,long length)
{
	char buf[BUFSIZE];
	long result;
	if(bound == IP_SOCK_INVALID)
	{
		bound = UDPpassive(port);
	}	
  if (bound > 0)
  {
    result = UDPserv_recv(bound,buf,BUFSIZE);
    if (result > 0)
    {
	    return Unmarshal(buf,length);
    }
  }
  return SDM_MESSAGE_RECV_ERROR;
}

long SDMData::Marshal(char* buf,long data_length)
{
	int cur;
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	cur += msg_id.Marshal(buf, cur);
	PUT_LONG(&buf[cur],pid);
	cur += sizeof(pid);
	PUT_SHORT(&buf[cur],seq_num);
	cur += sizeof(seq_num);
	memcpy(buf+cur,msg,data_length);
	cur += data_length;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMData::Unmarshal(const char* buf,long length)
{
	return Unmarshal(buf);
}

long SDMData::Marshal(char* buf)
{
	return Marshal(buf,length);
}

long SDMData::Unmarshal(const char* buf)
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
	pid = GET_LONG (&buf[cur]);
	cur += sizeof(pid);
	seq_num = GET_SHORT(&buf[cur]);
	cur += sizeof(seq_num);
	memcpy(msg,buf+cur,msg_length - cur + HEADER_SIZE);
	length = msg_length - cur + HEADER_SIZE;
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return msg_length + HEADER_SIZE;
}

/*short SDMData::getInt(long start_byte) const
{
	return GET_INT (&msg[start_byte]);
}

long SDMData::getLong(long start_byte) const
{
	return GET_LONG (&msg[start_byte]);
}

signed char SDMData::getChar(long start_byte) const
{
	return GET_CHAR (&msg[start_byte]);
}

unsigned char SDMData::getByte(long start_byte) const
{
	return GET_UCHAR (&msg[start_byte]);
}

float SDMData::getFloat(long start_byte) const
{
	return GET_FLOAT (&msg[start_byte]);
}

double SDMData::getDouble(long start_byte) const
{
	return GET_DOUBLE (&msg[start_byte]);
}

char* SDMData::getString(long start_byte) const
{
	return strndup(msg+start_byte,BUFSIZE-HEADER_SIZE-start_byte);
}

void SDMData::setSocket(int sock)
{
	bound = sock;
}*/

int SDMData::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	char data_section[511];
	char message_id[30];
	int i, j;

	if (length < 8096)
		return 0;
	for (i = 0, j = 0; j < this->length && i < 510; i+=2, j++)
	{
		sprintf(&data_section[i], "%.2x", msg[j]);
	}
	data_section[i] = '\0';

	msg_id.IDToString(message_id, 30);
	source.IDToString(source_id, 40);
#ifdef WIN32
	sprintf(str_buf,"SDMData %ld:%ld %d bytes, Source: %s %s pid: %ld seq_num: %d [DATA SECTION: %s ] DataLength: %d", sec, subsec, msg_length, source_id, message_id, pid, seq_num, data_section, this->length);
#else
	snprintf(str_buf,length,"SDMData %ld:%ld %d bytes, Source: %s %s pid: %ld seq_num: %d [DATA SECTION: %s ] DataLength: %d", sec, subsec, msg_length, source_id, message_id, pid, seq_num, data_section, this->length);
#endif
	return strlen(str_buf);
}
