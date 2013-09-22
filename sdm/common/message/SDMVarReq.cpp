#include <string.h>
#include <stdio.h>
#include "SDMVarReq.h"

SDMVarReq::SDMVarReq():source(), destination(), reply(SDM_VARREQ_CURRENT), msg_id(), id(0)
{
	MsgName = SDM_VarReq;
	total_length = 25;
	variable[0] = '\0';
}

long SDMVarReq::Send()
{
	return SendDM();
}

long SDMVarReq::Marshal(char *buf)
{
	int cur = HEADER_SIZE;	
	cur += source.Marshal(buf, cur);
	cur += destination.Marshal(buf, cur);
	PUT_UCHAR(&buf[cur], reply);
	cur += sizeof(reply);
	cur += msg_id.Marshal(buf, cur);
	PUT_USHORT(buf+cur, id);
	cur += sizeof(id);
	strcpy(buf+cur, variable);		//Copy the variable string field
	cur += strlen(variable) + 1;		//Cur is now the strlen plus null terminator
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMVarReq::Unmarshal(const char *buf)
{
	int cur = UnmarshalHeader(buf);
	if (cur == SDM_INVALID_MESSAGE || total_length > msg_length)
		return SDM_INVALID_MESSAGE;
	cur += source.Unmarshal(buf, cur);
	cur += destination.Unmarshal(buf, cur);
	reply = GET_UCHAR (&buf[cur]);
	cur += sizeof(reply);
	cur += msg_id.Unmarshal(buf, cur);
	id = GET_USHORT(buf+cur);
	cur += sizeof(id);
	strcpy(variable, buf+cur);
	cur += strlen(variable) + 1;
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

int SDMVarReq::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	char dest_id[40];
	char message_id[40];

	if (length < 8096)
		return 0;
	source.IDToString(source_id, 40);
	destination.IDToString(dest_id, 40);
	msg_id.IDToString(message_id, 30);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMVarReq %ld:%ld %ld bytes, Source: %s Dest: %s MsgID: %s id: %hu variable: %s", sec, subsec, msg_length, source_id, dest_id, message_id, id, variable);
	return strlen(str_buf);
}
