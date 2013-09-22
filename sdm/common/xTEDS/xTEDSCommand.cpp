#include "xTEDSCommand.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSCommand::xTEDSCommand():m_CommandMessage(NULL),m_FaultMessage(NULL)
{
	Type = WRAPPER_COMMAND;
}

xTEDSCommand::~xTEDSCommand()
{
	if (m_CommandMessage != NULL)
		delete m_CommandMessage;
	if (m_FaultMessage != NULL)
		delete m_FaultMessage;
}

bool xTEDSCommand::SetCommand(const command* Command, const xTEDSVariableList& VariableList)
{
	if (Command == NULL || Command->command_message == NULL)
		return false;
	
	// Set the command attributes
	if (Command->interface_name != NULL) setInterfaceName (Command->interface_name);
	if (Command->interface_id != NULL) setInterfaceID (atoi(Command->interface_id));
	
	// Set the command message, required
	m_CommandMessage = new xTEDSCommandMsg();
	bool ReturnResult = m_CommandMessage->SetCommandMsg(Command->command_message, VariableList);
	if (ReturnResult == false)
 		return false;
	
	// Set the fault message, optional
	if (Command->fault_message != NULL)
	{
		m_FaultMessage = new xTEDSFaultMsg();
		ReturnResult = m_FaultMessage->SetFaultMsg(Command->fault_message, VariableList);
	}
	return ReturnResult;
}

MessageDef* xTEDSCommand::RegInfo(const char* ItemName) const
{
	char DefinitionsBuf[MSG_DEF_SIZE] = "";
	char xTEDSPortionBuf[MSG_DEF_SIZE] = "";
	char VarPortionBuf[MSG_DEF_SIZE] = "";

	if (m_CommandMessage == NULL) return NULL;
	
	MessageDef* pCmdMsgDef = m_CommandMessage->RegInfo();
	if (NULL == pCmdMsgDef)
	  return NULL;

	VariableDef* pCmdVarDef = m_CommandMessage->GetVariableXtedsDefinitions();

	if(m_FaultMessage!=NULL)	// If there exists a fault message
	{
		MessageDef* pFltMsgDef = m_FaultMessage->RegInfo();
		if (NULL == pFltMsgDef)
		  {
		    free (pCmdMsgDef);
		    free (pCmdVarDef);
		    return NULL;
		  }
		VariableDef* pFltVarDef = m_FaultMessage->GetVariableXtedsDefinitions();
		
		snprintf(DefinitionsBuf,sizeof(DefinitionsBuf),"<Command>\n\t%s\n\t%s\n</Command>",
			 pCmdMsgDef->GetDefinitions(),
			 pFltMsgDef->GetDefinitions());
		
		// Get the full variable xTEDS definitions, into VarPortionBuf
		VariableDef::ToStringConcatVariableDefsIgnoreDuplicates ( VarPortionBuf,
				   sizeof(VarPortionBuf), pCmdVarDef, pFltVarDef );

		snprintf(xTEDSPortionBuf,sizeof(xTEDSPortionBuf),"%s\n<Command>\n\t%s\n\t%s\n</Command>",
			 VarPortionBuf, pCmdMsgDef->GetxTEDSPortion(), pFltMsgDef->GetxTEDSPortion());
		
		delete pFltMsgDef;
		pFltMsgDef = NULL;

		delete pFltVarDef;
		pFltVarDef = NULL;
	}
	else				// If this is only a command message
	{
		snprintf(DefinitionsBuf,sizeof(DefinitionsBuf),"<Command>\n\t%s\n</Command>",
			 pCmdMsgDef->GetDefinitions());

		VariableDef::ToStringConcatVariableDefs(VarPortionBuf, sizeof(VarPortionBuf),
							pCmdVarDef, NULL);

		snprintf(xTEDSPortionBuf,sizeof(xTEDSPortionBuf),"%s\n<Command>\n\t%s\n</Command>",
			 VarPortionBuf, pCmdMsgDef->GetxTEDSPortion());
	}
	
	MessageDef* ReturnDef = new MessageDef();
	
	//
	// Set the message id to the id of the requested item
	ReturnDef->SetInterfaceMessageID(pCmdMsgDef->GetInterfaceMessageID());
	if (ItemName != NULL)
	{
		if (m_FaultMessage != NULL && m_FaultMessage->NameEquals(ItemName))
			ReturnDef->SetInterfaceMessageID(m_FaultMessage->GetID());
	}
	
	delete(pCmdMsgDef);
	if (NULL != pCmdVarDef)
	  delete pCmdVarDef;

	ReturnDef->SetDefinitions(DefinitionsBuf);
	ReturnDef->SetxTEDSPortion(xTEDSPortionBuf);
	return ReturnDef;
}

bool xTEDSCommand::RegInfoMatch(const char* Name, const xTEDSQualifierList& Qualifiers, const char* Interface) const
{
	if (m_CommandMessage != NULL && m_CommandMessage->RegInfoMatch(Name, Qualifiers, Interface))
		return true;
	else if (m_FaultMessage != NULL && m_FaultMessage->RegInfoMatch(Name, Qualifiers, Interface))
		return true;
	
	return false;
}

bool xTEDSCommand::RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const
{
	if (m_CommandMessage != NULL && m_CommandMessage->RegexMatch(Pattern, QualList, Interface))
		return true;
	else if (m_FaultMessage != NULL && m_FaultMessage->RegexMatch(Pattern, QualList, Interface))
		return true;
	
	return false;
}

bool xTEDSCommand::ContainsMessage(const SDMMessage_ID& MessageID) const
{
	if (m_CommandMessage != NULL && m_CommandMessage->GetID() == MessageID)
		return true;
	else if (m_FaultMessage != NULL && m_FaultMessage->GetID() == MessageID)
		return true;
	return false;
}

SDMMessage_ID xTEDSCommand::GetFaultMessageID() const
{
	if (m_FaultMessage != NULL)
		return m_FaultMessage->GetID();
	return SDMMessage_ID('\0', '\0');
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSCommand::PrintDebug() const
{
	xTEDSWrapper::PrintDebug();
	printf(" xTEDSCommand\n");
	
	if (m_CommandMessage!=NULL)
		m_CommandMessage->PrintDebug();
	
	if (m_FaultMessage!=NULL)
		m_FaultMessage->PrintDebug();
}
#endif
