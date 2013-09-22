#ifndef __SDMMESSAGE_ID_H_
#define __SDMMESSAGE_ID_H_

#include "../sdmLib.h"

class SDMLIB_API SDMMessage_ID
{
public:
	SDMMessage_ID();
	SDMMessage_ID(unsigned char interface_id, unsigned char msg_id);
	SDMMessage_ID(int interface_id, int msg_id);
	void setInterface(unsigned char interface_num) { _interface = interface_num; }	//Sets the interface id number for this Message_ID
	void setMessage(unsigned char msg_num) { _message = msg_num; }			//Sets the message id number for this Message_ID
	void setInterface(int interface_num);
	void setMessage(int msg_num);
	unsigned char getInterface() const { return _interface; }	//Gets the interface id number for this Message_ID
	unsigned char getMessage() const { return _message; };		//Gets the message id number for this Message_ID
	short getInterfaceMessagePair() const;
	bool operator== (const SDMMessage_ID &other) const;
	bool operator== (const short &other) const;
	SDMMessage_ID& operator= (const SDMMessage_ID &other);
	SDMMessage_ID& operator= (const int value);
	int Marshal(char *buf, int start);
	int Unmarshal(const char *buf, int start);
	int IDToString(char *buf, int length) const;
private:
	unsigned char _interface;
	unsigned char _message;
};

#endif
