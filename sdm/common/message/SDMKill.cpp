#include <string.h>
#include <stdio.h>
#include "SDMKill.h"
#include "../UDPcom.h"

SDMKill::SDMKill():PID(0), killLevel(0)
{
	MsgName = SDM_Kill;
	total_length = 5;
}

long SDMKill::Send(const SDMComponent_ID& destination)
{
	return SendTo(destination);
}

long SDMKill::Send()
{
	return SendTo(TaskManager);
}

long SDMKill::Marshal(char* buf)
{
	int cur = HEADER_SIZE;
	PUT_ULONG(&buf[cur],PID);
	cur += sizeof(PID);
	PUT_UCHAR(&buf[cur], killLevel);
	cur += sizeof(killLevel);
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMKill::Unmarshal(const char* buf)
{
	int cur;
	cur = UnmarshalHeader(buf);
	if(cur == SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(msg_length == 4)
	{
      PID = GET_ULONG(&buf[cur]);
      cur += sizeof(PID);
      killLevel = 0;
	}
	else
	{
      if(total_length!=msg_length)
      {
         return SDM_INVALID_MESSAGE;
      }
      PID = GET_ULONG(&buf[cur]);
      cur += sizeof(PID);
      killLevel = GET_UCHAR(&buf[cur]);
      cur += sizeof(killLevel);
	}
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return HEADER_SIZE+msg_length;
}
int SDMKill::MsgToString(char *str_buf, int length) const
{
	if (length < 8096)
		return 0;
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMKill %ld:%ld %ld bytes, PID: %ld",sec,subsec,msg_length,PID);
	return (int)strlen(str_buf);
}
