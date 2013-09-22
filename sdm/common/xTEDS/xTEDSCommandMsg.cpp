#include "xTEDSCommandMsg.h"
#include "MessageDef.h"
#include "../Exception/SDMBadIndexException.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSCommandMsg::xTEDSCommandMsg()
{
	m_ItemType = TYPE_COMMANDMSG;
}

xTEDSCommandMsg::~xTEDSCommandMsg()
{

}

bool xTEDSCommandMsg::SetCommandMsg(const command_message* CommandMsg, const xTEDSVariableList& VariablesList)
{
	if (CommandMsg == NULL) return false;
	
	// Set all of the attributes of the message
	if (CommandMsg->name != NULL) setName(CommandMsg->name);
	if (CommandMsg->id != NULL) setMessageID(atoi(CommandMsg->id));
	if (CommandMsg->interface_name != NULL) setInterfaceName(CommandMsg->interface_name);
	if (CommandMsg->interface_id != NULL) setInterfaceID(atoi(CommandMsg->interface_id));
	if (CommandMsg->description != NULL) setDescription(CommandMsg->description);
	
	if (CommandMsg->qualifiers != NULL)
	{
		for (qualifier_type* CurQual = CommandMsg->qualifiers; CurQual != NULL; CurQual = CurQual->next)
			addQualifier (xTEDSQualifier(CurQual->name, CurQual->value, CurQual->units));
	}
	
	// Set the variables
	for (var_ref* Cur = CommandMsg->variables; Cur != NULL; Cur = Cur->next)
	{
		const xTEDSVariable* CurVar = VariablesList.Find(Cur->name, CommandMsg->interface_name);
		
		if (CurVar == NULL)
		{
			printf("Error, could not find variable %s in interface %s being reference in command message %s.\n",Cur->name, CommandMsg->interface_name, CommandMsg->name);
			return false;	// Variable not found, error
		}
		
		// Otherwise, add to varibles list
		m_Variables.addItem(CurVar);
	}
	return true;
}

MessageDef* xTEDSCommandMsg::RegInfo(void) const
{
	char InfoBuf[MSG_DEF_SIZE];
	char xTEDSPortion[MSG_DEF_SIZE];
	int BufLength = 0;
	MessageDef* ReturnDef = new MessageDef();
	
	xTEDSPortion[0] = InfoBuf[0] = '\0';
	
	snprintf(InfoBuf, sizeof(InfoBuf), "<CommandMsg name=\"%s\" id=\"%d\" ", m_strItemName, m_ItemInterfaceMessageID.getInterfaceMessagePair());
	if (!m_Variables.IsEmpty())
	{	
		BufLength = strlen(InfoBuf);
		m_Variables.VarReqReg(InfoBuf + BufLength, sizeof(InfoBuf) - BufLength);
	}	
	BufLength = strlen(InfoBuf);
	strncat(InfoBuf, "/>", sizeof(InfoBuf) - BufLength);
	
	ReturnDef->SetInterfaceMessageID(m_ItemInterfaceMessageID);
	ReturnDef->SetDefinitions(InfoBuf);
	
	// Add xTEDS section
	xTEDSInfo(xTEDSPortion, sizeof(xTEDSPortion));
	ReturnDef->SetxTEDSPortion(xTEDSPortion);
	
	return ReturnDef;
}

void xTEDSCommandMsg::xTEDSInfo(char* InfoBufferOut, int BufferSize) const
{
	char xTEDSBuf[MSG_DEF_SIZE];
	const unsigned int xTEDSBufSize = sizeof(xTEDSBuf);
	int BufLength = 0;
	
	if (m_strItemName == NULL)
		return ;
	
	snprintf(xTEDSBuf, xTEDSBufSize, "<CommandMsg name=\"%s\" id=\"%d\"",m_strItemName,m_ItemInterfaceMessageID.getInterfaceMessagePair());
	// Get the description
	if(m_strItemDescription != NULL)
	{
		strncat(xTEDSBuf, " description=\"", xTEDSBufSize);
		strncat(xTEDSBuf, m_strItemDescription, xTEDSBufSize);
		strncat(xTEDSBuf, "\"", xTEDSBufSize);
	}
	// Close the tag
	strncat(xTEDSBuf,">", xTEDSBufSize);
	// Add any qualifiers
	if(m_ItemQualifiers!=NULL)
	{
		BufLength = strlen(xTEDSBuf);
		strncat(xTEDSBuf, "\n\t\t", sizeof(xTEDSBuf) - BufLength);
		
		BufLength += 3;
		m_ItemQualifiers->QualifierInfoRequest(xTEDSBuf + BufLength, sizeof(xTEDSBuf) - BufLength);
	}
	
	// Add the variables
	if (!m_Variables.IsEmpty())
	{
		BufLength = strlen(xTEDSBuf);
		strncat(xTEDSBuf, "\n\t\t", sizeof(xTEDSBuf) - BufLength);
		
		BufLength += 3;
		m_Variables.VarRef(xTEDSBuf + BufLength, sizeof(xTEDSBuf) - BufLength);
	}
	
	// Close the CommandMsg
	strncat(xTEDSBuf, "\n\t</CommandMsg>", xTEDSBufSize);
	
	strncat(InfoBufferOut, xTEDSBuf, BufferSize - 1);
}

bool xTEDSCommandMsg::MatchesQualifier(const xTEDSQualifierList& QualList) const
{
	if(QualList.isEmpty())
		return true;
	
	char id_str[8];
	snprintf(id_str, sizeof(id_str), "%d", m_ItemInterfaceMessageID.getMessage());
	
	//check entire qualifier list
	for (int i = 0; i < QualList.Size(); i++)
	{
		try
		{
			const xTEDSQualifier& CurQual = QualList[i];
			if (CurQual.MatchesName("name"))
			{
				if (!CurQual.MatchesDescription(m_strItemName))
					return false;
			}
			else if (CurQual.MatchesName("description"))
			{
				if (!CurQual.MatchesDescription(m_strItemDescription))
					return false;
			}
			else if (CurQual.MatchesName("id"))
			{
				if (!CurQual.MatchesDescription(id_str))
					return false;
			}
			else
				return false;
		}
		catch (SDMBadIndexException& ex)
		{
			printf("Error %s\n", ex.Message());
			return false;
		}
	}
	return true;
}

bool xTEDSCommandMsg::RegInfoMatch(const char* pname, const xTEDSQualifierList& qualifiers, const char* interface) const
{
	if (interface != NULL && strcmp(interface, m_strItemInterfaceName) != 0)
		return false;
	
	if (pname == NULL || strcmp(pname, m_strItemName)==0)
	{
		if (MatchesQualifier(qualifiers))
		{
			return true;
		}
	}
	
	if (m_Variables.RegInfoMatch(pname, qualifiers, interface))
		return true;
	
	return false;
}

bool xTEDSCommandMsg::RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const
{
	if (m_Variables.RegexMatch(Pattern, QualList, Interface))
		return true;
	
	return xTEDSItem::RegexMatch(Pattern, QualList, Interface);
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSCommandMsg::PrintDebug() const
{
	xTEDSMessage::PrintDebug();
	printf("   xTEDSCommandMsg\n\n");
	m_Variables.PrintDebug();
}
#endif

