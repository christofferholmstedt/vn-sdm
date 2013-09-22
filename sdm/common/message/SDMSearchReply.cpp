#include <string.h>
#include <stdio.h>
#include "SDMSearchReply.h"
#include "../UDPcom.h"

SDMSearchReply::SDMSearchReply():source(),id(0),emptyflag(false)
{
	MsgName = SDM_SearchReply;
	captured_matches[0] = '\0';
	total_length = 13;
}

long SDMSearchReply::Send(const SDMComponent_ID& destination)
{
	int result;
	emptyflag = false;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}

long SDMSearchReply::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	if (result == 1)
		return SDM_NO_FURTHER_DATA_PROVIDER;
	return result;
}

long SDMSearchReply::Marshal(char* buf)
{
	int cur;
	int bufmarker;
	if(emptyflag == true)
	{
		cur = MarshalEmpty(buf);
		return cur;
	}
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	PUT_USHORT (&buf[cur], id);
	cur += sizeof(id);
	bufmarker = 0;
	while(captured_matches[bufmarker] != 0)
	{
		memcpy(buf+cur,captured_matches+bufmarker,strlen(captured_matches+bufmarker));
		cur += (int)strlen(captured_matches+bufmarker);
		buf[cur] = 0;
		cur++;
		bufmarker += (int)strlen(captured_matches+bufmarker);
		bufmarker++;
	}
	buf[cur] = 0;
	cur++;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMSearchReply::Unmarshal(const char* buf)
{
	int cur;
	int bufmarker;
	long captured_matches_msg_length;
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
	id = GET_USHORT (&buf[cur]);
	cur += sizeof(id);
	bufmarker = 0;
	while (buf[cur] != 0)
	{
		captured_matches_msg_length = (long)strlen(buf + cur) + 1;
		memcpy(&captured_matches[bufmarker], buf + cur, captured_matches_msg_length);
		cur += captured_matches_msg_length;
		bufmarker += captured_matches_msg_length;
	}
	captured_matches[bufmarker++] = '\0';
	cur++;
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

long SDMSearchReply::MarshalEmpty(char* buf)
{
	int cur;
	msg_length = 0;
	cur = MarshalHeader(buf);
	return cur;
}

long SDMSearchReply::SendEmpty(const SDMComponent_ID& destination)
{
	int result;
	emptyflag = true;
	result = SendTo(destination);
	if (result <= 0)
		return SDM_MESSAGE_SEND_ERROR;
	return result;
}

int SDMSearchReply::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	char MatchBuf[sizeof(captured_matches)];

	if (length < 8096)
		return 0;
	source.IDToString(source_id, 40);
	
	bool NullFound = false;
	for (unsigned int i = 0; i < sizeof(MatchBuf) - 1; i++)
	{
		if (captured_matches[i] == '\0')
		{
			MatchBuf[i] = '0';
			if (NullFound)
			{
				MatchBuf[++i] = '\0';
				break;
			}
			else
				NullFound = true;
		}
		else
		{
			NullFound = false;
			MatchBuf[i] = captured_matches[i];
		}
	}
	
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMSearchReply %ld:%ld %ld bytes, Source: %s ID: %d captured_matches: \"%s\"", sec, subsec, msg_length, source_id, id, MatchBuf);
	return (int)strlen(str_buf);
}
