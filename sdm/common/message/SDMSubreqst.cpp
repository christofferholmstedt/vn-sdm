#include <string.h>
#include <stdio.h>
#include "SDMSubreqst.h"

SDMSubreqst::SDMSubreqst():source(),destination(),msg_id(0,0),fault_id(0,0)
{
	MsgName = SDM_Subreqst;
	total_length = 24;
}

long SDMSubreqst::Send()
{
	int result;
	result = SendTo(source);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}

long SDMSubreqst::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	return result;
}

long SDMSubreqst::Marshal(char* buf)
{
	int cur;
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	cur += destination.Marshal(buf,cur);
	cur += msg_id.Marshal(buf, cur);
	cur += fault_id.Marshal(buf, cur);
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMSubreqst::Unmarshal(const char* buf)
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
	cur += source.Unmarshal(buf,cur);
	cur += destination.Unmarshal(buf,cur);
	cur += msg_id.Unmarshal(buf, cur);
	cur += fault_id.Unmarshal(buf, cur);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}
int SDMSubreqst::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	char dest_id[40];
	char message_id[30];
	char flt_id[30];

	if (length < 8096)
		return 0;
	source.IDToString(source_id, 40);
	destination.IDToString(dest_id, 40);
	msg_id.IDToString(message_id, 30);
	fault_id.IDToString(flt_id, 30);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMSubreqst %ld:%ld %ld bytes, Source: %s Dest: %s msg_id: %s FaultID: %s", sec, subsec, msg_length, source_id, dest_id, message_id, flt_id);
	return (int)strlen(str_buf);
}
