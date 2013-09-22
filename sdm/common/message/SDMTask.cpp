#include <string.h>
#include <stdio.h>
#include "SDMTask.h"
#include "../UDPcom.h"

SDMTask::SDMTask():source(),priority(0),pid(0),version(0)
{
	MsgName = SDM_Task;
	filename[0] = '\0';
	total_length = 10;
}

long SDMTask::Send(const SDMComponent_ID& destination)
{
	return SendTo(destination);
}

long SDMTask::Marshal(char* buf)
{
	int cur;
	long filename_msg_length;

	filename_msg_length = (long)strlen(filename);
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	PUT_CHAR(&buf[cur],priority);
	cur += sizeof(priority);
	PUT_LONG(&buf[cur],pid);
	cur += sizeof(pid);
	PUT_INT(&buf[cur], version);
	cur += sizeof(version);
	memcpy(buf+cur,&filename,filename_msg_length);
	cur += filename_msg_length;
	buf[cur]=0;
	cur++;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMTask::Unmarshal(const char* buf)
{
	int cur;
	unsigned int uiCurLength;
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
	priority = GET_CHAR (&buf[cur]);
	cur += sizeof(priority);
	pid = GET_LONG (&buf[cur]);
	cur += sizeof(pid);
	version = GET_INT(&buf[cur]);
	cur += sizeof(version);
	//
	// Get the filename
	uiCurLength = (unsigned int)strlen(buf+cur);
	strncpy(filename, buf + cur, sizeof(filename));
	if (uiCurLength > sizeof(filename) - 1)
		filename[sizeof(filename) - 1] = '\0';
	
	cur += uiCurLength + 1;
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}
int SDMTask::MsgToString(char *str_buf, int length) const
{
	if (length < 8096)
		return 0;
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMTask %ld:%ld %ld bytes, Priority: %hhd PID: %ld Version: %d Filename: %s", sec, subsec, msg_length, priority, pid, version, filename);
	return (int)strlen(str_buf);
}
