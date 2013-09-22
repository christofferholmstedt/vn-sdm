#include <string.h>
#include <stdio.h>
#include "SDMReqCode.h"

SDMReqCode::SDMReqCode():source(), seq_num(0), version(0)
{
	MsgName = SDM_ReqCode;
	filename[0] = '\0';
	total_length = 17;
}

long SDMReqCode::Send()
{
	return SendTM();
}

long SDMReqCode::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	return result;
}

long SDMReqCode::Marshal(char* buf)
{
	int cur;
	int filename_length;
	cur = HEADER_SIZE;
	filename_length = (int)strlen(filename) + 1;
	cur += source.Marshal(buf,cur);
	PUT_USHORT(&buf[cur], seq_num);
	cur += sizeof(seq_num);
	PUT_INT(&buf[cur], version);
	cur += sizeof(version);
	memcpy (&buf[cur], &filename, filename_length);
	cur += filename_length;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMReqCode::Unmarshal(const char* buf)
{
	int cur;
	unsigned int filename_length;
	int source_size;
	cur = UnmarshalHeader(buf);
	if(cur == SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(total_length>msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	source_size = source.Unmarshal(buf, cur);
	filename_length = msg_length - source_size - sizeof(seq_num);
	cur += source_size;
	seq_num = GET_USHORT(&buf[cur]);
	cur += sizeof(seq_num);
	version = GET_INT(&buf[cur]);
	cur += sizeof(version);
	//
	// Get the filename
	filename_length = (unsigned int)strlen(buf + cur);
	strncpy(filename, buf + cur, sizeof(filename));
	if (filename_length > sizeof(filename) - 1)
		filename[sizeof(filename) - 1] = '\0';
	cur += filename_length + 1;

#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}
int SDMReqCode::MsgToString(char *str_buf, int length) const
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
        "SDMReqCode %ld:%ld %ld bytes, Source: %s Filename: %s seq_num: %hd version %d", sec, subsec, msg_length, source_id, filename, seq_num, version);
	return (int)strlen(str_buf);
}
