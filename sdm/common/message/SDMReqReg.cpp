#include <string.h>
#include <stdio.h>
#include "SDMReqReg.h"

SDMReqReg::SDMReqReg():source(),destination(),reply(SDM_REQREG_CURRENT),id(0)
{
	MsgName = SDM_ReqReg;
	device[0] = interface[0] = item_name[0] = quallist[0] = '\0';
	total_length = 27;
}

long SDMReqReg::Send()
{
	return SendDM();
}

long SDMReqReg::Recv(long port)
{
	int result;
	result = RecvFrom(port);
	if (result <= 0)
		return SDM_MESSAGE_RECV_ERROR;
	return result;
}

long SDMReqReg::Marshal(char* buf)
{
	int cur;
	long device_length;
	long interface_length;
	long item_name_msg_length;
	long quallist_msg_length;

	device_length = (long)strlen(device);
	interface_length = (long)strlen(interface);
	item_name_msg_length = (long)strlen(item_name);
	quallist_msg_length = (long)strlen(quallist);
	cur = HEADER_SIZE;
	cur += source.Marshal(buf,cur);
	cur += destination.Marshal(buf,cur);
	PUT_UCHAR  (&buf[cur], reply);
	cur += sizeof(reply);
	PUT_USHORT (&buf[cur], id);
	cur += sizeof(id);
	memcpy(buf+cur,device,device_length);
	cur += device_length;
	buf[cur] = '\0';
	cur++;
	memcpy(buf+cur,interface,interface_length);
	cur += interface_length;
	buf[cur] = '\0';
	cur++;
	memcpy(buf+cur,item_name,item_name_msg_length);
	cur += item_name_msg_length;
	buf[cur] = '\0';
	cur++;
	memcpy(buf+cur,quallist,quallist_msg_length);
	cur += quallist_msg_length;
	buf[cur] = '\0';
	cur++;
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMReqReg::Unmarshal(const char* buf)
{
	int cur;
	unsigned int uiCurLength;

	//unmarshal header
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
	cur += destination.Unmarshal(buf,cur);
	reply = GET_UCHAR (&buf[cur]);
	cur += sizeof(reply);
	id = GET_USHORT (&buf[cur]);
	cur += sizeof(id);
	//
	// Get the device name
	uiCurLength = (unsigned int)strlen(buf+cur);
	strncpy(device, buf+cur, sizeof(device));
	if (uiCurLength > sizeof(device) - 1)
		device[sizeof(device) - 1] = '\0';
	cur += uiCurLength + 1;
	//
	// Get the interface name
	uiCurLength = (unsigned int)strlen(buf+cur);
	strncpy(interface, buf+cur, sizeof(interface));
	if (uiCurLength > sizeof(interface) - 1)
		interface[sizeof(interface) - 1] = '\0';
	cur += uiCurLength + 1;
	//
	// Get the item name
	uiCurLength = (unsigned int)strlen(buf+cur);
	strncpy(item_name, buf+cur, sizeof(item_name));
	if (uiCurLength > sizeof(item_name) - 1)
		item_name[sizeof(item_name) - 1] = '\0';
	cur += uiCurLength + 1;
	//
	// Get the qual list
	uiCurLength = (unsigned int)strlen(buf+cur);
	strncpy(quallist, buf+cur, sizeof(quallist));
	if (uiCurLength > sizeof(quallist) - 1)
		quallist[sizeof(quallist) - 1] = '\0';
	cur += uiCurLength + 1;
	
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}
int SDMReqReg::MsgToString(char *str_buf, int length) const
{
	char dest_id[40];
	char provider_id[40];

	if (length < 8096)
		return 0;
	destination.IDToString(dest_id, 40);
	source.IDToString(provider_id, 40);
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMReqReg %ld:%ld %ld bytes, Dest: %s Reply: %d ID: %d Provider: %s Device: %s Interface: %s ItemName: %s QualList: %s", sec, subsec, msg_length, dest_id, reply, id, provider_id, device, interface, item_name, quallist);
	return (int)strlen(str_buf);
}
