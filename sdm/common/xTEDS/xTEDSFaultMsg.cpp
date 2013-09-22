#include "xTEDSFaultMsg.h"
#include "MessageDef.h"
#include "../Exception/SDMBadIndexException.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSFaultMsg::xTEDSFaultMsg()
{
	m_ItemType = TYPE_FAULTMSG;
}

xTEDSFaultMsg::~xTEDSFaultMsg()
{

}

bool xTEDSFaultMsg::SetFaultMsg(const fault_msg* FaultMsg, const xTEDSVariableList& VariablesList)
{
	if (FaultMsg == NULL) return false;
	
	if (FaultMsg->id != NULL) setMessageID(atoi(FaultMsg->id));
	if (FaultMsg->name != NULL) setName(FaultMsg->name);
	if (FaultMsg->description != NULL) setDescription(FaultMsg->description);
	if (FaultMsg->interface_name != NULL) setInterfaceName(FaultMsg->interface_name);
	if (FaultMsg->interface_id != NULL) setInterfaceID(atoi(FaultMsg->interface_id));
	if (FaultMsg->qualifiers != NULL)
	{
		for (qualifier_type* CurQual = FaultMsg->qualifiers; CurQual != NULL; CurQual = CurQual->next)
			addQualifier (xTEDSQualifier(CurQual->name, CurQual->value, CurQual->units));
	}
	
	// Add variables
	for (var_ref* Cur = FaultMsg->variables; Cur != NULL; Cur = Cur->next)
	{
		const xTEDSVariable* CurVar = VariablesList.Find(Cur->name, FaultMsg->interface_name);
		
		if (CurVar == NULL)
		{
			printf("Error, could not find variable %s in interface %s being reference in fault message %s.\n",Cur->name, FaultMsg->interface_name, FaultMsg->name);
			return false;	// Variable not found, error
		}
		
		// Otherwise, add to varibles list
		m_Variables.addItem(CurVar);
	}
	return true;
}

MessageDef* xTEDSFaultMsg::RegInfo(void) const
{
	char InfoBuf[MSG_DEF_SIZE];
	char xTEDSPortion[MSG_DEF_SIZE];
	int BufLength = 0;
	MessageDef* ReturnDef = new MessageDef();

	xTEDSPortion[0] = InfoBuf[0] = '\0';

	snprintf(InfoBuf, sizeof(InfoBuf), "<FaultMsg name=\"%s\" id=\"%d\" ", m_strItemName, m_ItemInterfaceMessageID.getInterfaceMessagePair());
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

/*  Create the xTEDS section corresponding to this fault message */
void xTEDSFaultMsg::xTEDSInfo(char* InfoBufferOut, int BufferSize) const
{
	char xTEDSBuf[MSG_DEF_SIZE];
	const unsigned int xTEDSBufSize = sizeof(xTEDSBuf);
	int BufLength = 0;
	
	if (m_strItemName == NULL)
		return ;
	
	snprintf(xTEDSBuf, xTEDSBufSize, "<FaultMsg name=\"%s\" id=\"%d\"",m_strItemName,m_ItemInterfaceMessageID.getInterfaceMessagePair());
	// Add the description
	if(m_strItemDescription != NULL)
	{
		strncat(xTEDSBuf, " description=\"", xTEDSBufSize);
		strncat(xTEDSBuf, m_strItemDescription, xTEDSBufSize);
		strncat(xTEDSBuf, "\"", xTEDSBufSize);
	}
	// Close the tag
	strncat(xTEDSBuf, ">", xTEDSBufSize);
	// Add any qualifiers
	if(m_ItemQualifiers!=NULL)
	{
		BufLength = strlen(xTEDSBuf);
		strncat(xTEDSBuf, "\n\t\t", sizeof(xTEDSBuf) - BufLength);
		
		BufLength += 3;
		m_ItemQualifiers->QualifierInfoRequest(xTEDSBuf + BufLength, sizeof(xTEDSBuf) - BufLength);
	}
	// Add any variables
	if (!m_Variables.IsEmpty())
	{
		BufLength = strlen(xTEDSBuf);
		strncat(xTEDSBuf, "\n\t\t", sizeof(xTEDSBuf) - BufLength);
		
		BufLength += 3;
		m_Variables.VarRef(xTEDSBuf + BufLength, sizeof(xTEDSBuf) - BufLength);
	}
	// Close the FaultMsg
	strncat(xTEDSBuf, "\n\t</FaultMsg>", xTEDSBufSize);
	
	strncat(InfoBufferOut, xTEDSBuf, BufferSize - 1);
}

bool xTEDSFaultMsg::MatchesQualifier(const xTEDSQualifierList& QualList) const
{
	if(QualList.isEmpty())
		return true;
	
	char id_str[8];
	snprintf(id_str, sizeof(id_str), "%d",getMessageID());
	
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

bool xTEDSFaultMsg::RegInfoMatch(const char* pname, const xTEDSQualifierList& qualifiers, const char* interface) const
{
	if (pname == NULL || strcmp(pname, m_strItemName)==0)
	{
		if (interface == NULL || strcmp(interface, m_strItemInterfaceName)==0)
		{
			if (MatchesQualifier(qualifiers))
				return true;
		}
	}
	
	if (m_Variables.RegInfoMatch(pname, qualifiers, interface))
		return true;
	
	return false;
}

bool xTEDSFaultMsg::RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const
{
	if (m_Variables.RegexMatch(Pattern, QualList, Interface))
		return true;
	
	return xTEDSItem::RegexMatch(Pattern, QualList, Interface);
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSFaultMsg::PrintDebug() const
{
	xTEDSMessage::PrintDebug();
	printf("   xTEDSFaultMsg\n\n");
	m_Variables.PrintDebug();
}
#endif



