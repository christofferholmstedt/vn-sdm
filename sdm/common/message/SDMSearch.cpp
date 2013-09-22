#include <string.h>
#include <stdio.h>
#include "SDMSearch.h"

SDMSearch::SDMSearch():source(),destination(),reply(SDM_SEARCH_CURRENT),id(0)
{
	MsgName = SDM_Search;
	reg_expr[0] = '\0';
	total_length = 24;
}

long SDMSearch::Send()
{
	return SendDM();
}

long SDMSearch::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	return result;
}

long SDMSearch::Marshal(char* buf)
{
	int cur;
	long reg_expr_msg_length;

	reg_expr_msg_length = (long)strlen(reg_expr);
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	cur += destination.Marshal(buf,cur);
	PUT_UCHAR  (&buf[cur], reply);
	cur += sizeof(reply);
	PUT_USHORT (&buf[cur], id);
	cur += sizeof(id);
	memcpy(buf+cur,reg_expr,reg_expr_msg_length);
	cur += reg_expr_msg_length;
	buf[cur] = '\0';
	cur++;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMSearch::Unmarshal(const char* buf)
{
	int cur;
	unsigned int reg_expr_msg_length;

	//unmarshal header
	cur = UnmarshalHeader(buf);
	if(cur == SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(total_length>msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	cur += source.Unmarshal(buf,cur);
	cur += destination.Unmarshal(buf,cur);
	reply = GET_UCHAR (&buf[cur]);
	cur += sizeof(reply);
	id = GET_USHORT (&buf[cur]);
	cur += sizeof(id);
	//
	// Get the regular expression
	reg_expr_msg_length = (unsigned int)strlen(buf+cur);
	strncpy(reg_expr, buf + cur, sizeof(reg_expr));
	if (reg_expr_msg_length > sizeof(reg_expr) - 1)
		reg_expr[sizeof(reg_expr) - 1] = '\0';
	cur += reg_expr_msg_length+1;
	
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

int SDMSearch::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	char destination_id[40];

	if (length < 8096)
		return 0;
	source.IDToString(source_id, 40);
	destination.IDToString(destination_id, 40);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
    "SDMSearch %ld:%ld %ld bytes, Source: %s Destination: %s Reply: %d ID: %d RegExpr: %s", sec, subsec, msg_length, source_id, destination_id, reply, id, reg_expr);
	return (int)strlen(str_buf);
}
