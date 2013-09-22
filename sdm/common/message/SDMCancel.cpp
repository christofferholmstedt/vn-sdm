#include "SDMCancel.h"
#include <string.h>
#include <stdio.h>

SDMCancel::SDMCancel():source(),destination(),msg_id(0,0)
{
	MsgName = SDM_Cancel;
	total_length = 22;
}

long SDMCancel::Send()
{
	return SendDM();
}

long SDMCancel::Marshal(char* buf)
{
	int cur;
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	cur += destination.Marshal(buf,cur);
	cur += msg_id.Marshal(buf, cur);
	msg_length = cur-HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMCancel::Unmarshal(const char* buf)
{
	int cur;
	cur = UnmarshalHeader(buf);
	if(cur==SDM_INVALID_MESSAGE)
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
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}
/*
 *  MsgToString() puts the message into str_buf into human readable form, returning the number of characters copied.
 */
int SDMCancel::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	char dest_id[40];
	char message_id[30];

	if (length < 8096)
		return 0;
	source.IDToString(source_id, 40);
	destination.IDToString(dest_id, 40);
	msg_id.IDToString(message_id, 30);
#ifdef WIN32 // cleanup - remove duplicate code for maintainability
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMCancel %ld:%ld %ld bytes, Source: %s Dest: %s %s", sec, subsec, msg_length, source_id, dest_id, message_id);
	return (int)strlen(str_buf);
}
