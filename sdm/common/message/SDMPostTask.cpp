#include <string.h>
#include <stdio.h>
#include "SDMPostTask.h"

SDMPostTask::SDMPostTask():resources(0),priority(0),sched_interval(0),mode(0),version(0)
{
	filename[0] = '\0';
	MsgName = SDM_PostTask;
	total_length = 16;
}

long SDMPostTask::Send()
{
	return SendTM();
}

long SDMPostTask::Marshal(char* buf)
{
	int cur = HEADER_SIZE;
	PUT_USHORT (&buf[cur], resources);
	cur += sizeof(resources);
	PUT_CHAR  (&buf[cur], priority);
	cur += sizeof(priority);
	PUT_INT (&buf[cur], sched_interval);
	cur += sizeof(sched_interval);
	PUT_INT (&buf[cur], mode);
	cur += sizeof(mode);
	PUT_INT (&buf[cur], version);
	cur += sizeof(version);
	msg_length = (short)strlen(filename);
	memcpy(buf+cur,&filename,msg_length);
	cur += msg_length;
	buf[cur] = '\0';//null termination
	cur++;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return msg_length + HEADER_SIZE ;
}

long SDMPostTask::Unmarshal(const char* buf)
{
	int cur;
	cur = UnmarshalHeader(buf);
	if(cur==SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(total_length>msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	resources = GET_USHORT(&buf[cur]);
	cur += sizeof(resources);
	priority = GET_CHAR (&buf[cur]);
	cur += sizeof(priority);
	sched_interval = GET_INT(&buf[cur]);
	cur += sizeof(sched_interval);
	mode = GET_INT(&buf[cur]);
	cur += sizeof(mode);
	version = GET_INT(&buf[cur]);
	cur += sizeof(version);
	//
	// Get the filename
	unsigned int uiCurLength = (unsigned int)strlen(buf + cur);
	strncpy(filename, buf + cur, sizeof(filename));
	if (uiCurLength > sizeof(filename) - 1)
		filename[sizeof(filename) - 1] = '\0';
	
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return msg_length+HEADER_SIZE;
}
int SDMPostTask::MsgToString(char *str_buf, int length) const
{
	if (length < 8096)
		return 0;
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMPostTask %ld:%ld %ld bytes, Resources: %hu Priority: %d Filename: %s SchedInterval: %d Mode: %d Version: %d", sec, subsec, msg_length, resources, priority, filename, sched_interval, mode, version);
	return (int)strlen(str_buf);
}
