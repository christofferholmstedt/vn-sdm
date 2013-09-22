#ifndef __MESSAGE_LOGGER_H_
#define __MESSAGE_LOGGER_H_

#ifndef BUILD_WITH_MESSAGE_LOGGING
#  include "../message/SDMCommand.h"
#  include "../message/SDMmessage.h"
#endif
#include "../message/SDMComponent_ID.h"


#ifdef BUILD_WITH_MESSAGE_LOGGING
class SDMCommand;
class SDMmessage;
#endif

struct LogID
{
	SDMComponent_ID component;
	unsigned char msg_type;
	LogID* next;
	LogID():component(),msg_type(0)
	{ }
};

class SDMLIB_API MessageLogger
{
public:
	MessageLogger();
	~MessageLogger();
	bool AddMessageType(const SDMCommand *msg);	//Adds message types for logging
	bool RemoveMessageType(const SDMCommand *msg);//Removes message types for logging
	bool MessageReceived(const SDMmessage *msg);	//Called when messsage is received
	bool MessageSent(const SDMmessage *msg);	//Called when message is sent
	bool Contains(char msg_type);		//Determines whether a type is being logged
	bool Contains(char msg_type, SDMComponent_ID id);
	bool Contains(char msg_type, SDMComponent_ID id1, SDMComponent_ID id2);
	void SetLogFile(const char *header, const char *filename);
	bool IsEmpty();				//Returns whether message types are being logged
	bool NeedsInit();			//Used to determine if log file needs to be set
	void LogAllMessageTypes();		//Tell the service to log everything
private:
	bool WriteLogMessage(char *prefix, char *msg_buf);
	void GetCompIDs(const SDMmessage *msg, char *buf, int &num_ids);

	int numTypes;			//A counter of the number of types being logged
	int fd;				//File descriptor of the log file
	bool init_done;			//Flag to determine whether log file needs to be set
	LogID* LogIdListHead;
};


#endif
