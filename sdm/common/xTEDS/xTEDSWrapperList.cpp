#include "xTEDSWrapperList.h"
#include "MessageDef.h"
#include "xTEDSRequest.h"

xTEDSWrapperList::xTEDSWrapperList():Head(NULL)
{
}

xTEDSWrapperList::~xTEDSWrapperList()
{
	DeleteList();
}

void xTEDSWrapperList::DeleteList()
{
	for (xTEDSWrapperListNode* Cur = Head; Cur!= NULL; )
	{
		xTEDSWrapperListNode* Temp = Cur->Next;
		delete Cur->Data;
		delete Cur;
		Cur = Temp;
	}
	Head = NULL;
}

void xTEDSWrapperList::AddItem(xTEDSWrapper* Item)
{
	xTEDSWrapperListNode* NewNode = new xTEDSWrapperListNode();
	NewNode->Data = Item;
	
	if (Head == NULL)
		Head = NewNode;
	else
	{
		xTEDSWrapperListNode* Cur;
		for (Cur = Head; Cur->Next != NULL; Cur = Cur->Next)
			;
		Cur->Next = NewNode;
	}
}

MessageDef* xTEDSWrapperList::RegInfo(const char* Name, const xTEDSQualifierList& Qualifiers, const char* Interface) const
{
	MessageDef* Def = NULL;
	for (xTEDSWrapperListNode* Cur = Head; Cur != NULL; Cur = Cur->Next)
	{
		if (Cur->Data != NULL && Cur->Data->RegInfoMatch(Name, Qualifiers, Interface))
		{
			if (Def == NULL)
				Def = Cur->Data->RegInfo(Name);
			else
				Def->Join(Cur->Data->RegInfo(Name));
		}
	}
	return Def;
}

MessageDef* xTEDSWrapperList::RegexRegInfo(const char* Pattern, const xTEDSQualifierList& Qualifiers, const char* Interface) const
{
	MessageDef* Def = NULL;
	for (xTEDSWrapperListNode* Cur = Head; Cur != NULL; Cur = Cur->Next)
	{
		if (Cur->Data != NULL && Cur->Data->RegexMatch(Pattern, Qualifiers, Interface))
		{
			if (Def == NULL)
				Def = Cur->Data->RegInfo(NULL);
			else
				Def->Join(Cur->Data->RegInfo(NULL));
		}
	}
	return Def;
}

SDMMessage_ID xTEDSWrapperList::GetFaultID(const SDMMessage_ID& MessageID) const
{
	for (xTEDSWrapperListNode* Cur = Head; Cur != NULL; Cur = Cur->Next)
	{
		if (Cur->Data != NULL && Cur->Data->ContainsMessage(MessageID))
		{
			// There should only be one instance of this message id, so stop searching
			return Cur->Data->GetFaultMessageID();
		}
	}
	return SDMMessage_ID('\0', '\0');
}

SDMMessage_ID xTEDSWrapperList::GetDataID(const SDMMessage_ID& MessageID) const
{
	for (xTEDSWrapperListNode* Cur = Head; Cur != NULL; Cur = Cur->Next)
	{
		if (Cur->Data != NULL && Cur->Data->GetType() == xTEDSWrapper::WRAPPER_REQUEST)
		{
			xTEDSRequest* RequestData = static_cast<xTEDSRequest*>(Cur->Data);
			
			if (RequestData->ContainsMessage(MessageID))
				return RequestData->GetDataMessageID();
		}
	}
	return SDMMessage_ID('\0', '\0');
}

bool xTEDSWrapperList::ContainsMessage(const SDMMessage_ID& RequestedId) const
{
	for (xTEDSWrapperListNode* Cur = Head; Cur != NULL; Cur = Cur->Next)
	{
		if (Cur->Data != NULL && Cur->Data->ContainsMessage(RequestedId))
			return true;
	}
	return false;
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSWrapperList::PrintDebug() const
{
	for (xTEDSWrapperListNode* Cur = Head; Cur != NULL; Cur = Cur->Next)
	{
		if (Cur->Data != NULL)
			Cur->Data->PrintDebug();
	}
}
#endif
