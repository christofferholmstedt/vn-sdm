#include <stdio.h>
#include <string.h>
#include "SDMRegPM.h"
#include "../UDPcom.h"

SDMRegPM::SDMRegPM():source(),resources(0)
{
	MsgName = SDM_RegPM;
	total_length = 12;
}

long SDMRegPM::Send()
{
	return SendTM();
}

long SDMRegPM::Send(const SDMComponent_ID& destination)
{
	return SendTo(destination);
}

long SDMRegPM::Marshal(char* buf)
{
	int cur;
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	PUT_USHORT (&buf[cur], resources);
	cur += sizeof(resources);
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMRegPM::Unmarshal(const char* buf)
{
	int cur;
	cur = UnmarshalHeader(buf);
	if(cur == SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(total_length!=msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	cur += source.Unmarshal(buf,cur);
	resources = GET_USHORT (&buf[cur]);
	cur += sizeof(resources);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}
int SDMRegPM::MsgToString(char *str_buf, int length) const
{
	char src_id[40];

	if (length < 8096)
		return 0;
	source.IDToString(src_id,40);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMRegPM %ld:%ld %ld bytes, Resources: %hu Source: %s", sec, subsec, msg_length, resources, src_id);
	return (int)strlen(str_buf);
}

