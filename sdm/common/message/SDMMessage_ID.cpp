#include <string.h>
#include <stdio.h>
#include "SDMMessage_ID.h"
#include "../marshall.h"

SDMMessage_ID::SDMMessage_ID() : _interface(0), _message(0)
{
}

SDMMessage_ID::SDMMessage_ID(unsigned char interface_id, unsigned char msg_id) : _interface(interface_id), _message(msg_id)
{
}

SDMMessage_ID::SDMMessage_ID(int interface_id, int msg_id) : _interface(0), _message(0)
{
	setInterface(interface_id);
	setMessage(msg_id);
}

void SDMMessage_ID::setInterface(int interface_num)
{
	//Mask off all but lowest byte
	unsigned char c_value = static_cast<unsigned char> (interface_num&0xFF);
	setInterface(c_value);
}

void SDMMessage_ID::setMessage(int msg_num)
{
	//Mask off all but lowest byte
	unsigned char c_value = static_cast<unsigned char> (msg_num&0xFF);
	setMessage(c_value);
}

short SDMMessage_ID::getInterfaceMessagePair() const
{
	return (short)(_message + (_interface << 8));
}
bool SDMMessage_ID::operator== (const SDMMessage_ID &other) const
{
	if (this->_message == other._message)
		if (this->_interface == other._interface)
			return true;
	return false;
}
bool SDMMessage_ID::operator== (const short &other) const
{
	if (_interface == (other >> 8))
		if (_message == (other&0x00FF))
			return true;
	return false;
}
SDMMessage_ID& SDMMessage_ID::operator= (const SDMMessage_ID &other)
{
	_interface = other._interface;
	_message = other._message;
	return *this;
}
SDMMessage_ID& SDMMessage_ID::operator= (const int value)
{
	_interface = (0x0000ff00&value) >> 8;
	_message = (0x000000ff&value);
	return *this;
}

int SDMMessage_ID::Marshal(char *buf, int start)
{
	int cur = 0;
	PUT_UCHAR(&buf[start], _interface);
	PUT_UCHAR(&buf[start+1], _message);
	cur +=2;
	return cur;
}

int SDMMessage_ID::Unmarshal(const char *buf, int start)
{
	int cur = 0;
	_interface = GET_UCHAR(&buf[start]);
	_message = GET_UCHAR(&buf[start+1]);
	cur +=2;
	return cur;
}

int SDMMessage_ID::IDToString(char *buf, int length) const
{
	if (length < 30)
		return 0;
#ifdef WIN32
	sprintf(buf, "Interface: %d Message: %d", getInterface(), getMessage());
#else
	snprintf(buf, length,"Interface: %d Message: %d", getInterface(), getMessage());
#endif
	return (int)strlen(buf);
}
