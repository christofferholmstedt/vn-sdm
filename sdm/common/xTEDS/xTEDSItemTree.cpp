#include "xTEDSItemTree.h"
#include "xTEDSItem.h"
#include "MessageDef.h"
#include "xTEDSCommandMsg.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>


//Note an xTEDSItemTree owns its data items and so should delete them and make deep copies as needed.

xTEDSItemTree::xTEDSItemTree():m_Variables(),m_Commands(),m_Notifications(),m_Requests()
{
}

xTEDSItemTree::~xTEDSItemTree()
{
	// Variables is the only list the needs to be explicitly freed
	m_Variables.DeleteItems();
}

xTEDSItemTree& xTEDSItemTree::operator=(const xTEDSItemTree& Right)
{
	printf("xTEDSItemTree::operator=\n");
	return *this;
}

xTEDSItemTree::xTEDSItemTree(const xTEDSItemTree& Right):m_Variables(),m_Commands(),m_Notifications(),m_Requests()
{
	printf("xTEDSItemTree::Copy constructor\n");
}

MessageDef* xTEDSItemTree::ExactRegInfo(const char* name, const xTEDSQualifierList& qualifiers, const char* interface) const
{
	//TODO:  Remove the dynamic allocation and return by using copy constructor
	MessageDef* Result = NULL;

	Result = m_Commands.RegInfo(name, qualifiers, interface);

	if (Result != NULL)
		Result->Join(m_Notifications.RegInfo(name, qualifiers, interface));
	else
		Result = m_Notifications.RegInfo(name, qualifiers, interface);

	if (Result != NULL)
		Result->Join(m_Requests.RegInfo(name, qualifiers, interface));
	else
		Result = m_Requests.RegInfo(name, qualifiers, interface);

	return Result;
	//return RegInfo(root,name,qualifiers,interface);

}

MessageDef* xTEDSItemTree::AllRegInfo(const xTEDSQualifierList& qualifiers, const char* interface) const
{
	return ExactRegInfo(NULL, qualifiers, interface);
}

MessageDef* xTEDSItemTree::RegexRegInfo(const char* pattern, const xTEDSQualifierList& qualifiers, const char* interface) const
{
	MessageDef* Result = NULL;

	Result = m_Commands.RegexRegInfo(pattern, qualifiers, interface);

	if (Result != NULL)
		Result->Join(m_Notifications.RegexRegInfo(pattern, qualifiers, interface));
	else
		Result = m_Notifications.RegexRegInfo(pattern, qualifiers, interface);

	if (Result != NULL)
		Result->Join(m_Requests.RegexRegInfo(pattern, qualifiers, interface));
	else
		Result = m_Requests.RegexRegInfo(pattern, qualifiers, interface);

	return Result;
}

void xTEDSItemTree::AddVariable(const variable* pNewVariable)
{
	xTEDSVariable* NewVariable = new xTEDSVariable();
	NewVariable->SetVariable(pNewVariable);

	m_Variables.addItem(NewVariable);
}

bool xTEDSItemTree::AddCommand(const command* Command)
{
	if (Command == NULL)
		return false;

	xTEDSCommand* NewCommand = new xTEDSCommand();
	if (!NewCommand->SetCommand(Command, m_Variables))
	{
		delete NewCommand;
		return false;
	}

	m_Commands.AddItem(NewCommand);
	return true;
}

bool xTEDSItemTree::AddNotification(const notification* Notification)
{
	if (Notification == NULL)
		return false;

	xTEDSNotification* NewNotification = new xTEDSNotification();
	if (!NewNotification->SetNotification(Notification, m_Variables))
	{
		delete NewNotification;
		return false;
	}

	m_Notifications.AddItem(NewNotification);
	return true;
}

bool xTEDSItemTree::AddRequest(const request* Request)
{
	if (Request == NULL)
		return false;

	xTEDSRequest* NewRequest = new xTEDSRequest();
	if (!NewRequest->SetRequest(Request, m_Variables))
	{
		delete NewRequest;
		return false;
	}

	m_Requests.AddItem(NewRequest);
	return true;
}

VariableDef* xTEDSItemTree::VarInfoRequest(const char* VarName, const SDMMessage_ID& Interface) const
{
	return m_Variables.VarInfoRequest(VarName, Interface);
}

SDMMessage_ID xTEDSItemTree::GetNotificationFaultID(const SDMMessage_ID& DataMessageID) const
{
	return m_Notifications.GetFaultID(DataMessageID);
}

SDMMessage_ID xTEDSItemTree::GetCommandFaultID(const SDMMessage_ID& CommandMessageID) const
{
	return m_Commands.GetFaultID(CommandMessageID);
}

SDMMessage_ID xTEDSItemTree::GetServiceFaultID(const SDMMessage_ID& CommandMessageID) const
{
	return m_Requests.GetFaultID(CommandMessageID);
}

SDMMessage_ID xTEDSItemTree::GetServiceDataID(const SDMMessage_ID& CommandMessageID) const
{
	return m_Requests.GetDataID(CommandMessageID);
}

bool xTEDSItemTree::IsServiceIdValid(const SDMMessage_ID& RequestedId) const
{
	if (GetServiceDataID (RequestedId) == SDMMessage_ID('\0', '\0'))
		return false;
	return true;
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSItemTree::PrintDebug()
{
	m_Variables.PrintDebug();
	printf("\n");
	m_Notifications.PrintDebug();
	printf("\n");
	m_Commands.PrintDebug();
	printf("\n");
	m_Requests.PrintDebug();
	printf("\n");
}
#endif



