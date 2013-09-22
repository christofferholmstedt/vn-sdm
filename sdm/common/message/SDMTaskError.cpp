#include <string.h>
#include <stdio.h>
#include "SDMTaskError.h"

SDMTaskError::SDMTaskError():source(),status(0), pid(0)
{
	MsgName = SDM_TaskError;
	filename[0] = '\0';
	total_length = 19;
}

long SDMTaskError::Send()
{
	return SendDM();
}

long SDMTaskError::Marshal(char* buf)
{
	int cur;
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	PUT_INT(&buf[cur], status);
	cur += sizeof(status);
	PUT_UINT(&buf[cur], pid);
	cur += sizeof(pid);
	memcpy (&buf[cur], &filename, strlen(filename));
	cur += strlen(filename);
	buf[cur] = '\0';
	cur++;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMTaskError::Unmarshal(const char* buf)
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
	status = GET_INT(&buf[cur]);
	cur += sizeof (status);
	pid = GET_UINT(&buf[cur]);
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
int SDMTaskError::MsgToString(char *str_buf, int length) const
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
        "SDMTaskError %ld:%ld %ld bytes, Source: %s PID: %u Filename: %s Result: %d", sec, subsec, msg_length,  source_id, pid, filename, status);
	return strlen(str_buf);
}
