#include "SDMCancelxTEDS.h"
#include <stdio.h>
#include <string.h>

SDMCancelxTEDS::SDMCancelxTEDS():source(), fullCancel(0)
{
	MsgName = SDM_CancelxTEDS;
	total_length = 11;
}

long SDMCancelxTEDS::Send()
{
   msg_length = 11;
	return SendDM();
}

long SDMCancelxTEDS::Marshal(char* buf)
{
	int cur;
	cur = HEADER_SIZE;
	MarshalHeader(buf);
	cur += source.Marshal(buf,cur);
	memcpy(&buf[cur], &fullCancel, 1);
	cur += 1;
	msg_length=cur-HEADER_SIZE;

	return cur;
}

long SDMCancelxTEDS::Unmarshal(const char* buf)
{
	int cur;
	cur = UnmarshalHeader(buf);
	if(cur==SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(msg_length == 10)  //If original style SDMCancelxTEDS
	{
	   cur += source.Unmarshal(buf,cur);
	   fullCancel = 0;
	}
	else
	{
      if(total_length!=msg_length)
      {
         printf("total length: %i msg_legnth: %i\n", total_length, msg_length);
         return SDM_INVALID_MESSAGE;
      }
      cur+= source.Unmarshal(buf,cur);
      fullCancel = buf[cur];
      cur += 1;
	}
#ifdef BUILD_WITH_MESSAGE_LOGGING
   Logger.MessageReceived(*this);
#endif

	return cur;
}

int SDMCancelxTEDS::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	if (length < 8096)
		return 0;
	source.IDToString(source_id, 40);
#ifdef WIN32 // cleanup - remove duplicate code for maintainability
	sprintf(str_buf,
#else
	snprintf(str_buf, length,
#endif
        "SDMCancelxTEDS %ld:%ld %ld bytes, Source: %s", sec, subsec, msg_length, source_id);
	return (int)strlen(str_buf);
}
