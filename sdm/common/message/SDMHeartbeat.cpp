#include "SDMHeartbeat.h"
#include "../Time/SDMTime.h"
#include <string.h>
#include <stdio.h>


/*
 *  Send a heartbeat message to the local Process Manager.  The PM knows who the application
 *  is by way of application PID in the sensor ID field of the message.  Therefore, this
 *  can't be called until SDMInit() has been.
 */
SDMLIB_API void SendHeartbeat()
{
	const unsigned int MIN_SEND_INTERVAL = 20;	// Minimum time to wait before re-sending, in seconds
	unsigned int uiCurSeconds = 0, uiTemp = 0;
	static unsigned int uiLastSendTime = 0;
	SDM_GetTime(&uiCurSeconds, &uiTemp);

	// If the previous heartbeat was sent within the minimum interval, don't send
	if (uiCurSeconds - uiLastSendTime < MIN_SEND_INTERVAL && uiLastSendTime != 0)
		return;

	SDMHeartbeat msgHeartbeat;
	SDMComponent_ID PmId;
	
	msgHeartbeat.source.setSensorID(PID);
	PmId.setAddress(ADDR_LOCAL_HOST);
	PmId.setPort(PORT_PM);
	msgHeartbeat.SendTo(PmId);

	uiLastSendTime = uiCurSeconds;
}

SDMHeartbeat::SDMHeartbeat():source()
{
	MsgName = SDM_Heartbeat;
	total_length = 10;
}

long SDMHeartbeat::Marshal(char *buf)
{
	int cur = HEADER_SIZE;
	cur += source.Marshal(buf, cur);
	msg_length = cur-HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMHeartbeat::Unmarshal(const char * buf)
{
	int cur = UnmarshalHeader(buf);
	if (cur==SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if (total_length != msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	cur += source.Unmarshal(buf, cur);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

int SDMHeartbeat::MsgToString(char * str_buf, int length) const
{
	char source_id[40];

	if (length < 8096)
		return 0;
	source.IDToString(source_id, 40);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMHeartbeat %ld:%ld %ld bytes, Source: %s", sec, subsec, msg_length, source_id);
	return (int)strlen(str_buf);
}
