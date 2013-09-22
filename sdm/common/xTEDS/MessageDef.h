#ifndef __SDM_MESSAGE_DEF_H
#define __SDM_MESSAGE_DEF_H
#include "../sdmLib.h"

#include "../message_defs.h"
#include "../message/SDMMessage_ID.h"

class SDMLIB_API MessageDef
{
public:
	MessageDef();
	MessageDef(const MessageDef&);
	~MessageDef();

	MessageDef& operator=(const MessageDef&);

	void operator += (MessageDef* Right);

	void Print();
	void Join(MessageDef*);
	void SetInterfaceMessageID(const SDMMessage_ID& );
	SDMMessage_ID GetInterfaceMessageID() const { return mMessageInterfaceID; }
	void SetDefinitions(const char* NewDefinitions);
	void SetxTEDSPortion(const char* NewxTEDS);
	char* GetxTEDSPortion() const { return xTEDSPortion; }
	char* GetDefinitions() const { return def; }
private:
	SDMMessage_ID mMessageInterfaceID;
	char* def;
	char* xTEDSPortion;
public:	//TODO
	MessageDef* next;

};


#endif
