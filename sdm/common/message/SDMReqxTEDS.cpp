#include <string.h>
#include <stdio.h>
#include "SDMReqxTEDS.h"

SDMReqxTEDS::SDMReqxTEDS():select(-1),destination(),source()
{
	MsgName = SDM_ReqxTEDS;
	device_name[0] = '\0';
	total_length = 12;
}

long SDMReqxTEDS::Send()
{
	return SendDM();
}

long SDMReqxTEDS::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	return result;
}

long SDMReqxTEDS::Marshal(char* buf)
{
	int cur;
	cur = HEADER_SIZE;
	cur += destination.Marshal(buf,cur);
	PUT_CHAR(&buf[cur],select);
	cur += sizeof(select);
	switch(select)
	{
	case 0:
	case 2:	//use sensor_id
		cur += source.Marshal(buf,cur);
		break;
	case 1: //use device_name
	case 3:
		msg_length = (short)strlen(device_name);
		memcpy(buf+cur,device_name,msg_length);
		cur += msg_length;
		buf[cur] = '\0';
		cur++;
		break;
	default:
		return SDM_INVALID_SELECT;
	}
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);			//re-marshal header with correct length
	return msg_length + HEADER_SIZE;
}

long SDMReqxTEDS::Unmarshal(const char* buf)
{
	int cur;
	long device_name_msg_length;

	cur = UnmarshalHeader(buf);
	if(cur==SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(total_length>msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	cur += destination.Unmarshal(buf,cur);
	select = GET_CHAR (&buf[cur]);
	cur += sizeof(select);
	switch(select)
	{
	case 0:
	case 2:
		cur += source.Unmarshal(buf,cur);
		return cur;
	case 1:
	case 3:
		device_name_msg_length = (long)strlen(buf+cur);
		memset(device_name,0,sizeof(device_name));
		memcpy(&device_name,buf+cur,device_name_msg_length);
		cur += device_name_msg_length + 1;
		return cur;
  default:
    break;
	};
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return SDM_INVALID_SELECT;
}
int SDMReqxTEDS::MsgToString(char *str_buf, int length) const
{
	char source_id[40];
	char dest_id[40];

	if (length < 8096)
		return 0;
	source.IDToString(source_id, 40);
	destination.IDToString(dest_id, 40);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMReqxTEDS %ld:%ld %ld bytes, Select: %d", sec, subsec, msg_length, select);
	switch(select)
	{
	case 0:
	case 2:	//use sensor_id
		strcat(str_buf," Source: ");
		strcat(str_buf, source_id);
		break;
	case 1: //use device_name
	case 3:
		strcat(str_buf," DeviceName: ");
		strcat(str_buf, device_name);
		break;
  default:
    break;
	}
	return (int)strlen(str_buf);
}
