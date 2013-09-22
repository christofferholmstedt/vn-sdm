#ifndef __SDM_XTEDS_ITEM_TREE_H_
#define __SDM_XTEDS_ITEM_TREE_H_


#include "xTEDSItem.h"
#include "xTEDSQualifierList.h"
#include "xTEDSVariableList.h"
#include "xTEDSWrapper.h"
#include "xTEDSWrapperList.h"
#include "xTEDSVariable.h"
#include "xTEDSCommand.h"
#include "xTEDSRequest.h"
#include "xTEDSNotification.h"
#include "../sdmLib.h"

class SDMLIB_API xTEDSItemTree
{
public:
	xTEDSItemTree();
	xTEDSItemTree(const xTEDSItemTree&);		//Not defined - shouldn't be used
	xTEDSItemTree& operator=(const xTEDSItemTree&); //Not defined - shouldn't be used
	
	~xTEDSItemTree();
	MessageDef* ExactRegInfo(const char* Name, const xTEDSQualifierList& qualifier, const char* Interface) const;
	MessageDef* AllRegInfo(const xTEDSQualifierList& qualifier, const char* Interface) const;
	MessageDef* RegexRegInfo(const char* Pattern, const xTEDSQualifierList& qualifier, const char* Interface) const;
	
	void AddVariable(const variable* NewVariable);
	bool AddCommand(const command* Command);
	bool AddNotification(const notification* Notification);
	bool AddRequest(const request* Request);
	
	bool IsCommandIdValid(const SDMMessage_ID& RequestedId) const { return m_Commands.ContainsMessage(RequestedId); }
	bool IsServiceIdValid(const SDMMessage_ID& RequestedId) const;
	
	SDMMessage_ID GetNotificationFaultID(const SDMMessage_ID& DataMessageID) const;
	SDMMessage_ID GetCommandFaultID(const SDMMessage_ID& CommandMessageID) const;
	SDMMessage_ID GetServiceFaultID(const SDMMessage_ID& CommandMessageID) const;
	SDMMessage_ID GetServiceDataID(const SDMMessage_ID& CommandMessageID) const;
	VariableDef* VarInfoRequest(const char* VarName, const SDMMessage_ID& Interface) const;
	
	void PrintDebug();
private:
	xTEDSVariableList m_Variables;
	xTEDSWrapperList m_Commands;
	xTEDSWrapperList m_Notifications;
	xTEDSWrapperList m_Requests;
};

#endif
