#include "xTEDSNotification.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSNotification::xTEDSNotification():m_DataMessage(NULL),m_FaultMessage(NULL)
{
	Type = WRAPPER_NOTIFICATION;
}

xTEDSNotification::~xTEDSNotification()
{
	if (m_DataMessage != NULL)
		delete m_DataMessage;
	if (m_FaultMessage != NULL)
		delete m_FaultMessage;
}

bool xTEDSNotification::SetNotification(const notification* Notification, const xTEDSVariableList& VariablesList)
{
	if (Notification == NULL || Notification->data_message == NULL)
		return false;
	
	if (Notification->interface_name != NULL) setInterfaceName (Notification->interface_name);
	if (Notification->interface_id != NULL) setInterfaceID (atoi(Notification->interface_id));
	
	// Set the data message, required
	m_DataMessage = new xTEDSDataMsg();
	bool ReturnResult = m_DataMessage->SetDataMsg(Notification->data_message, VariablesList);
	if (ReturnResult == false)
		return false;
	
	// Set the fault message, optional
	if (Notification->fault_message != NULL)
	{
		m_FaultMessage = new xTEDSFaultMsg();
		ReturnResult = m_FaultMessage->SetFaultMsg(Notification->fault_message, VariablesList);
	}
	return ReturnResult;
}

MessageDef* xTEDSNotification::RegInfo(const char* ItemName) const
{
	char DefinitionsBuf[MSG_DEF_SIZE] = "";
	char xTEDSPortionBuf[MSG_DEF_SIZE] = "";
	char VarPortionBuf[MSG_DEF_SIZE] = "";

	if (m_DataMessage == NULL) return NULL;
	
	MessageDef* pDataMsgDef = m_DataMessage->RegInfo();
	if (NULL == pDataMsgDef)
	  return NULL;

	VariableDef* pDataVarDef = m_DataMessage->GetVariableXtedsDefinitions();

	if(m_FaultMessage!=NULL)	// If there exists a fault message
	{
		MessageDef* pFaultMsgDef = m_FaultMessage->RegInfo();
		if (NULL == pFaultMsgDef)
		  {
		    free (pDataMsgDef);
		    free (pDataVarDef);
		    return NULL;
		  }
	      
		VariableDef* pFaultVarDef = m_FaultMessage->GetVariableXtedsDefinitions();
		
		snprintf(DefinitionsBuf, sizeof(DefinitionsBuf), "<Notification>\n\t%s\n\t%s\n</Notification>",
			 pDataMsgDef->GetDefinitions(),
			 pFaultMsgDef->GetDefinitions());

		VariableDef::ToStringConcatVariableDefsIgnoreDuplicates(VarPortionBuf,
			   sizeof(VarPortionBuf), pDataVarDef, pFaultVarDef);

		snprintf(xTEDSPortionBuf,sizeof(xTEDSPortionBuf),
			 "%s\n<Notification>\n\t%s\n\t%s\n</Notification>",
			 VarPortionBuf,
			 pDataMsgDef->GetxTEDSPortion(),
			 pFaultMsgDef->GetxTEDSPortion());
		
		delete pFaultMsgDef;
		pFaultMsgDef = NULL;

		delete pFaultVarDef;
		pFaultVarDef = NULL;
	}
	else				// If this is only the data message
	{
		snprintf(DefinitionsBuf,sizeof(DefinitionsBuf),"<Notification>\n\t%s\n</Notification>",
			 pDataMsgDef->GetDefinitions());

		VariableDef::ToStringConcatVariableDefs(VarPortionBuf, sizeof(VarPortionBuf),
							pDataVarDef, NULL);

		snprintf(xTEDSPortionBuf,sizeof(xTEDSPortionBuf),
			 "%s\n<Notification>\n\t%s\n</Notification>",
			 VarPortionBuf, pDataMsgDef->GetxTEDSPortion());
	}
	
	MessageDef* ReturnDef = new MessageDef();
	
	//
	// Set the message id to the id of the requested item
	ReturnDef->SetInterfaceMessageID(pDataMsgDef->GetInterfaceMessageID());
	if (ItemName != NULL)
	{
		if (m_FaultMessage != NULL && m_FaultMessage->NameEquals(ItemName))
			ReturnDef->SetInterfaceMessageID(m_FaultMessage->GetID());
	}
	
	delete pDataMsgDef;

	if (NULL != pDataVarDef)
	  delete pDataVarDef;
	
	ReturnDef->SetDefinitions(DefinitionsBuf);
	ReturnDef->SetxTEDSPortion(xTEDSPortionBuf);

	return ReturnDef;
}

bool xTEDSNotification::RegInfoMatch(const char* Name, const xTEDSQualifierList& Qualifiers, const char* Interface) const
{
	if (m_DataMessage != NULL && m_DataMessage->RegInfoMatch(Name, Qualifiers, Interface))
		return true;
	else if (m_FaultMessage != NULL && m_FaultMessage->RegInfoMatch(Name, Qualifiers, Interface))
		return true;
	
	return false;
}

bool xTEDSNotification::RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const
{
	if (m_DataMessage != NULL && m_DataMessage->RegexMatch(Pattern, QualList, Interface))
		return true;
	else if (m_FaultMessage != NULL && m_FaultMessage->RegexMatch(Pattern, QualList, Interface))
		return true;
	
	return false;
}

bool xTEDSNotification::ContainsMessage(const SDMMessage_ID& MessageID) const
{
	if (m_DataMessage != NULL && m_DataMessage->GetID() == MessageID)
		return true;
	else if (m_FaultMessage != NULL && m_FaultMessage->GetID() == MessageID)
		return true;
	return false;
}

SDMMessage_ID xTEDSNotification::GetFaultMessageID() const
{
	if (m_FaultMessage != NULL)
		return m_FaultMessage->GetID();
	return SDMMessage_ID('\0', '\0');
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSNotification::PrintDebug() const
{
	xTEDSWrapper::PrintDebug();
	printf(" xTEDSNotification\n");
	
	if (m_DataMessage!=NULL)
		m_DataMessage->PrintDebug();
	
	if (m_FaultMessage!=NULL)
		m_FaultMessage->PrintDebug();
}
#endif


