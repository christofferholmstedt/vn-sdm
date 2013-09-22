#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "SDMxTEDS.h"
#include "../UDPcom.h"

SDMxTEDS::SDMxTEDS():source(),active(1),pid(PID)
{
	MsgName = SDM_xTEDS;
	SPA_node[0] = '\0';
	xTEDS[0] = '\0';
	total_length = 17;
}

long SDMxTEDS::Send()
{
	return SendDM();
}

long SDMxTEDS::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	return result;
}

long SDMxTEDS::Marshal(char* buf)
{
	int cur;
	unsigned int i,j;

	cur = HEADER_SIZE;

	cur += source.Marshal(buf,cur);
	PUT_CHAR(&buf[cur],active);
	cur += sizeof(active);
	PUT_LONG(&buf[cur], pid);
	cur += sizeof(pid);
	
	//Start at byte two, the first byte could be zero if this is a segmented xTEDS
	for(i=2; i<sizeof(xTEDS); i++)
  {
		if(xTEDS[i] == '\0')
    {
			break;	//find null terminator
    }
  }
  if (i >= sizeof(xTEDS) - 1)
  {
    i = sizeof(xTEDS) - 2;
  }
	memcpy(buf+cur,xTEDS,i+1);
	cur += i+1;
	for(j=0; j<sizeof(SPA_node); j++)
  {
		if(SPA_node[j] == '\0')
    {
			break;	//find null terminator
    }
  }
  if (j < sizeof(SPA_node) - 1)
  {
        j++;
  }
	memcpy(buf+cur,SPA_node,j);
	cur += j;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMxTEDS::Unmarshal(const char* buf)
{
	int cur;
	unsigned int xteds_length,usb_length;
	cur = UnmarshalHeader(buf);
	if(cur==SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(total_length>msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	cur += source.Unmarshal(buf,cur);
	active = GET_CHAR (&buf[cur]);
	cur += sizeof(active);
	pid = GET_LONG (&buf[cur]);
	cur += sizeof(pid);
	//
	// Determine whether this is a segmented xTEDS, or an empty xTEDS
	bool IsSegmented = false;
	if (buf[cur] <= MAX_XTEDS_SEQUENCE_VALUE && buf[cur+1] <= MAX_XTEDS_SEQUENCE_VALUE+1 && buf[cur+2] > MAX_XTEDS_SEQUENCE_VALUE)
		IsSegmented = true;
	//
	// Pull out the xTEDS
	if (IsSegmented)	//If segmented, ignore the possible null in first two bytes
		xteds_length = strlen(buf+cur+2) + 2;
	else			//Otherwise, look at the first two bytes
		xteds_length = strlen(buf+cur);
	//
	// Check to make sure the xTEDS in the message doesn't go beyond the size of the buffer
	if (xteds_length >= sizeof(xTEDS)-1)
	{
		//If so, copy all that we can, and terminate the string
		strncpy(xTEDS, buf+cur, sizeof(xTEDS));
		xTEDS[sizeof(xTEDS)-1] = '\0';
	}
	else	//Otherwise, copy out the string as usual
		memcpy(xTEDS,buf+cur,xteds_length+1);
	//
	// Pull out the USB path
	cur += xteds_length+1;
	usb_length = strlen(buf+cur);
	//
	// Check to make sure the USB path in the message doesn't go beyond the size of the buffer
	if (usb_length >= sizeof(SPA_node)-1)
	{
		//If it does, copy all we can and terminate the string
		strncpy(SPA_node, buf+cur, sizeof(SPA_node));
		SPA_node[sizeof(SPA_node)-1] = '\0';
	}
	else	//Otherwise, copy out the string as usual
		memcpy(SPA_node,buf+cur,usb_length+1);
	cur += usb_length+1;
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

long SDMxTEDS::getPID(void)
{
	return pid;
}

void SDMxTEDS::setPID(void)
{
	pid = PID;
}

int SDMxTEDS::MsgToString(char *str_buf, int length) const
{
	char source_id[40];

	if (length < 3*BUFSIZE)
		return 0;
	source.IDToString(source_id, 40);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,3*BUFSIZE-1,
#endif
        "SDMxTEDS %ld:%ld %ld bytes, Source: %s PID: %ld Active: %d xTEDS: %s SPANode: %s", sec, subsec, msg_length, source_id, pid, active, xTEDS, SPA_node);
	return strlen(str_buf);
}
