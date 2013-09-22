#ifndef _SDM_XTEDS_WRAPPER_LIST_H_
#define _SDM_XTEDS_WRAPPER_LIST_H_

#include "MessageDef.h"
#include "xTEDSQualifierList.h"
#include "xTEDSWrapper.h"
#include "../message/SDMMessage_ID.h"

class SDMLIB_API xTEDSWrapperListNode
{
public:
	xTEDSWrapperListNode():Next(NULL),Data(NULL) {}
	~xTEDSWrapperListNode() {}
	xTEDSWrapperListNode(const xTEDSWrapperListNode&);
	xTEDSWrapperListNode& operator=(const xTEDSWrapperListNode&);
	
	xTEDSWrapperListNode* Next;
	xTEDSWrapper* Data;
};

class SDMLIB_API xTEDSWrapperList
{
public:
	xTEDSWrapperList();
	xTEDSWrapperList(const xTEDSWrapperList&);
	xTEDSWrapperList& operator= (const xTEDSWrapperList&);
	~xTEDSWrapperList();
	
	void AddItem(xTEDSWrapper* Item);
	MessageDef* RegInfo(const char* Name, const xTEDSQualifierList& Qualifiers, const char* Interface) const;
	MessageDef* RegexRegInfo(const char* Pattern, const xTEDSQualifierList& Qualifiers, const char* Interface) const;
	bool ContainsMessage(const SDMMessage_ID& RequestedId) const;
	SDMMessage_ID GetFaultID(const SDMMessage_ID& MessageID) const;
	SDMMessage_ID GetDataID(const SDMMessage_ID& MessageID) const;
	
	void PrintDebug() const;
private:
	xTEDSWrapperListNode* Head;
	void DeleteList();
};

#endif

