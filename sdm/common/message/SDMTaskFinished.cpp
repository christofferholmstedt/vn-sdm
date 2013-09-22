#include <string.h>
#include <stdio.h>
#include "SDMTaskFinished.h"

SDMTaskFinished::SDMTaskFinished():source(),result(0), pid(0)
{
	MsgName = SDM_TaskFinished;
	filename[0] = '\0';
	total_length = 19;
}

long SDMTaskFinished::Send()
{
	return SendTM();
}

long SDMTaskFinished::Marshal(char* buf)
{
	int cur;
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	PUT_INT(&buf[cur], result);
	cur += sizeof(result);
	PUT_INT(&buf[cur], pid);
	cur += sizeof(pid);
	memcpy (&buf[cur], &filename, strlen(filename));
	cur += strlen(filename);
	buf[cur] = '\0';
	cur++;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMTaskFinished::Unmarshal(const char* buf)
{
	int cur;
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
	result = GET_INT(&buf[cur]);
	cur += sizeof (result);
	pid = GET_INT(&buf[cur]);
	cur += sizeof (pid);
	
	unsigned int uiCurLength = strlen(buf + cur);
	strncpy(filename, buf + cur, sizeof(filename));
	if (uiCurLength > sizeof(filename) - 1)
		filename[sizeof(filename) - 1] = '\0';
	cur += uiCurLength + 1;
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}
int SDMTaskFinished::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	if (length < 8096)
		return 0;
	source.IDToString(source_id,40);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMTaskFinished %ld:%ld %ld bytes, Source: %s PID: %d Filename: %s Result: %d", sec, subsec, msg_length,  source_id, pid, filename, result);
	return strlen(str_buf);
}
