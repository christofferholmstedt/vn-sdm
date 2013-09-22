//This is a wrapper class for the MessageLogger class.  The SDMMessageLogger is to be
//used in the SDMmessage class as a static member which logs all messages sent and
//received transparently as the message classes call Send() and Unmarshal().

#ifndef _SDM_MESSAGE_LOGGER_H_
#define _SDM_MESSAGE_LOGGER_H_
#include "MessageLogger.h"

class SDMmessage;

class SDMLIB_API SDMMessageLogger
{
public:
	SDMMessageLogger();
	bool MessageReceived(const SDMmessage &Message)
	   { return Logger.MessageReceived(&Message); }
	bool MessageSent(const SDMmessage &Message)
	   { return Logger.MessageSent(&Message); }
private:
	MessageLogger Logger;
};

#endif
