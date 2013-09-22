#include "MessageDef.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

MessageDef::MessageDef():mMessageInterfaceID(),def(NULL),xTEDSPortion(NULL),next(NULL)
{}

MessageDef::MessageDef(const MessageDef& b):mMessageInterfaceID(b.mMessageInterfaceID),def(b.def),xTEDSPortion(b.xTEDSPortion),next(b.next)
{}

MessageDef::~MessageDef()
{
	if(def != NULL)
	{
		free(def);
	}
	if(xTEDSPortion != NULL)
	{
		free(xTEDSPortion);
	}
	if(next != NULL)
	{
		delete next;
	}
}

MessageDef& MessageDef::operator=(const MessageDef& b)
{
	def = b.def;
	xTEDSPortion = b.xTEDSPortion;
	next = b.next;
	return *this;
}

void MessageDef::operator += (MessageDef* Right)
{
	Join(Right);
}

void MessageDef::Join(MessageDef* b)
{
	//join the two lists
	MessageDef* cur;
	if(b == NULL)
		return;
	if(next == NULL)
	{
		next = b;
		return;
	}
	for(cur = next;cur->next!=NULL;cur=cur->next);
	cur->next = b;
}

void MessageDef::SetInterfaceMessageID(const SDMMessage_ID& NewID)
{
	mMessageInterfaceID = NewID;
}

void MessageDef::SetDefinitions(const char* NewDef)
{
	if (NewDef == NULL) return;
	if (def != NULL) free (def);
	def = strdup(NewDef);
}

void MessageDef::SetxTEDSPortion(const char* NewxTEDS)
{
	if (NewxTEDS == NULL) return;
	if (xTEDSPortion != NULL) free(xTEDSPortion);
	xTEDSPortion = strdup(NewxTEDS);
}

void MessageDef::Print()
{
	printf("msg_def: %s message: %s\n",def,xTEDSPortion);
	if(next!=NULL)
		next->Print();
}
