#include "xTEDSRequest.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include <unistd.h>
#endif

xTEDSRequest::xTEDSRequest():m_ReplyMessage(NULL),m_CommandMessage(NULL),m_FaultMessage(NULL)
{
	Type = WRAPPER_REQUEST;
}

xTEDSRequest::~xTEDSRequest()
{
	if (m_ReplyMessage != NULL)
		delete m_ReplyMessage;
	if (m_CommandMessage != NULL)
		delete m_CommandMessage;
	if (m_FaultMessage != NULL)
		delete m_FaultMessage;
}

bool xTEDSRequest::SetRequest(const request* Request, const xTEDSVariableList& VariablesList)
{
	if (Request == NULL || Request->command_message == NULL || Request->data_message == NULL)
		return false;
	
	if (Request->interface_name != NULL) setInterfaceName (Request->interface_name);
	if (Request->interface_id != NULL) setInterfaceID (atoi(Request->interface_id));
	
	// Set the command message, required
	m_CommandMessage = new xTEDSCommandMsg();
	bool ReturnResult = m_CommandMessage->SetCommandMsg(Request->command_message, VariablesList);
	if (ReturnResult == false)
		return false;
	
	// Set the reply message, required
	m_ReplyMessage = new xTEDSDataMsg();
	ReturnResult = m_ReplyMessage->SetDataMsg(Request->data_message, VariablesList);
	if (ReturnResult == false)
		return false;
	
	// Set the fault message, optional
	if (Request->fault_message != NULL)
	{
		m_FaultMessage = new xTEDSFaultMsg();
		ReturnResult = m_FaultMessage->SetFaultMsg(Request->fault_message, VariablesList);
	}
	return ReturnResult;
}

MessageDef* xTEDSRequest::RegInfo(const char* ItemName) const
{
	char DefinitionsBuf[MSG_DEF_SIZE] = "";
	char xTEDSPortionBuf[MSG_DEF_SIZE] = "";
	char VarPortionBuf[MSG_DEF_SIZE] = "";

	if (m_ReplyMessage == NULL || m_CommandMessage == NULL) return NULL;

	MessageDef* pReplyMsgDef;
	MessageDef* pCmdMsgDef;
	MessageDef* pFaultMsgDef;
	
	//produce data and command message portions
	pReplyMsgDef = m_ReplyMessage->RegInfo();
	if (NULL == pReplyMsgDef)
	  return NULL;

	VariableDef* pReplyVarDef = m_ReplyMessage->GetVariableXtedsDefinitions();

	pCmdMsgDef = m_CommandMessage->RegInfo();
	if (NULL == pCmdMsgDef)
	  {
	    free (pReplyMsgDef);
	    free (pReplyVarDef);
	    return NULL;
	  }
	VariableDef* pCmdVarDef = m_CommandMessage->GetVariableXtedsDefinitions();

	if(m_FaultMessage!=NULL)	// If there exists a fault message
	{
		pFaultMsgDef = m_FaultMessage->RegInfo();
		if (pFaultMsgDef == NULL)
		  {
		    free (pReplyMsgDef);
		    free (pReplyVarDef);
		    free (pCmdMsgDef);
		    free (pCmdVarDef);
		    return NULL;
		  }
		VariableDef* pFaultVarDef = m_FaultMessage->GetVariableXtedsDefinitions();

		snprintf(DefinitionsBuf, sizeof(DefinitionsBuf), "<Request>\n\t%s\n\t%s\n\t%s\n</Request>",
			 pCmdMsgDef->GetDefinitions(),
			 pReplyMsgDef->GetDefinitions(),
			 pFaultMsgDef->GetDefinitions());

		pCmdMsgDef->Join(pFaultMsgDef);
		VariableDef::ToStringConcatVariableDefsIgnoreDuplicates(VarPortionBuf,
			sizeof(VarPortionBuf), pCmdVarDef, pReplyVarDef);
		
		snprintf(xTEDSPortionBuf, sizeof(xTEDSPortionBuf),
			 "%s\n<Request>\n\t%s\n\t%s\n\t%s\n</Request>", VarPortionBuf,
			 pCmdMsgDef->GetxTEDSPortion(), pReplyMsgDef->GetxTEDSPortion(),
			 pFaultMsgDef->GetxTEDSPortion());
		
		delete pFaultMsgDef;
		pFaultMsgDef = NULL;

		delete pFaultVarDef;
		pFaultMsgDef = NULL;
	}
	else				// If this is only the command/data messages
	{
		snprintf(DefinitionsBuf, sizeof(DefinitionsBuf), "<Request>\n\t%s\n\t%s\n</Request>",
			 pCmdMsgDef->GetDefinitions(),
			 pReplyMsgDef->GetDefinitions());

		VariableDef::ToStringConcatVariableDefsIgnoreDuplicates(VarPortionBuf,
			sizeof(VarPortionBuf), pCmdVarDef, pReplyVarDef);

		snprintf(xTEDSPortionBuf, sizeof(xTEDSPortionBuf),
			 "%s\n<Request>\n\t%s\n\t%s\n</Request>", VarPortionBuf, 
			 pCmdMsgDef->GetxTEDSPortion(), pReplyMsgDef->GetxTEDSPortion());
	}
	MessageDef* ReturnMsgDef = new MessageDef();
	
	//
	// Set the message id to the id of the requested item
	ReturnMsgDef->SetInterfaceMessageID(pCmdMsgDef->GetInterfaceMessageID());
	if (ItemName != NULL)
	{
		if (m_ReplyMessage->NameEquals(ItemName))
			ReturnMsgDef->SetInterfaceMessageID(pReplyMsgDef->GetInterfaceMessageID());
		if (m_FaultMessage != NULL && m_FaultMessage->NameEquals(ItemName))
			ReturnMsgDef->SetInterfaceMessageID(m_FaultMessage->GetID());
	}
	
	delete pCmdMsgDef;
	delete pReplyMsgDef;
	if (NULL != pReplyVarDef)
	  delete pReplyVarDef;
	if (NULL != pCmdVarDef)
	  delete pCmdVarDef;

	ReturnMsgDef->SetDefinitions(DefinitionsBuf);
	ReturnMsgDef->SetxTEDSPortion(xTEDSPortionBuf);
	return ReturnMsgDef;
}

bool xTEDSRequest::RegInfoMatch(const char* Name, const xTEDSQualifierList& Qualifiers, const char* Interface) const
{
	if (m_ReplyMessage != NULL && m_ReplyMessage->RegInfoMatch(Name, Qualifiers, Interface))
		return true;
	else if (m_CommandMessage != NULL && m_CommandMessage->RegInfoMatch(Name, Qualifiers, Interface))
		return true;
	else if (m_FaultMessage != NULL && m_FaultMessage->RegInfoMatch(Name, Qualifiers, Interface))
		return true;
	
	return false;
}

bool xTEDSRequest::RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const
{
	if (m_ReplyMessage != NULL && m_ReplyMessage->RegexMatch(Pattern, QualList, Interface))
		return true;
	else if (m_CommandMessage != NULL && m_CommandMessage->RegexMatch(Pattern, QualList, Interface))
		return true;
	else if (m_FaultMessage != NULL && m_FaultMessage->RegexMatch(Pattern, QualList, Interface))
		return true;
	
	return false;
}

bool xTEDSRequest::ContainsMessage(const SDMMessage_ID& MessageID) const
{
	if (m_ReplyMessage != NULL && m_ReplyMessage->GetID() == MessageID)
		return true;
	else if (m_CommandMessage != NULL && m_CommandMessage->GetID() == MessageID)
		return true;
	else if (m_FaultMessage != NULL && m_FaultMessage->GetID() == MessageID)
		return true;
	return false;
}

SDMMessage_ID xTEDSRequest::GetFaultMessageID() const
{
	if (m_FaultMessage != NULL)
		return m_FaultMessage->GetID();
	return SDMMessage_ID('\0', '\0');
}

SDMMessage_ID xTEDSRequest::GetDataMessageID() const
{
	if (m_ReplyMessage != NULL)
		return m_ReplyMessage->GetID();
	return SDMMessage_ID('\0', '\0');
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSRequest::PrintDebug() const
{
	xTEDSWrapper::PrintDebug();
	printf(" xTEDSRequest\n");
	
	if (m_CommandMessage!=NULL)
		m_CommandMessage->PrintDebug();
	
	if (m_ReplyMessage!=NULL)
		m_ReplyMessage->PrintDebug();
	
	if (m_FaultMessage!=NULL)
		m_FaultMessage->PrintDebug();
}
#endif

