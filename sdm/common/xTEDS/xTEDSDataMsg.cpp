#include "xTEDSDataMsg.h"
#include "MessageDef.h"
#include "../Exception/SDMBadIndexException.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSDataMsg::xTEDSDataMsg():msg_arrival(Event),msg_rate(0.0)
{
	m_ItemType = TYPE_DATAMSG;
}

xTEDSDataMsg::~xTEDSDataMsg()
{

}

bool xTEDSDataMsg::SetDataMsg(const data_msg* NewDataMsg, const xTEDSVariableList& VariablesList)
{
	if (NewDataMsg == NULL) return false;
	// Set the message attributes
	if (NewDataMsg->name != NULL) setName(NewDataMsg->name);
	if (NewDataMsg->id != NULL) setMessageID(atoi(NewDataMsg->id));
	if (NewDataMsg->interface_name != NULL) setInterfaceName(NewDataMsg->interface_name);
	if (NewDataMsg->interface_id != NULL) setInterfaceID(atoi(NewDataMsg->interface_id));
	if (NewDataMsg->msg_rate != NULL) msg_rate = atof(NewDataMsg->msg_rate);
	if (NewDataMsg->description != NULL) setDescription(NewDataMsg->description);
	
	if (NewDataMsg->msg_arrival != NULL)
	{
		if (strcmp(NewDataMsg->msg_arrival, "PERIODIC")==0)
			msg_arrival = Periodic;
		else
			msg_arrival = Event;
	}
	if (NewDataMsg->qualifiers != NULL)
	{
		for (qualifier_type* CurQual = NewDataMsg->qualifiers; CurQual != NULL; CurQual = CurQual->next)
			addQualifier (xTEDSQualifier(CurQual->name, CurQual->value, CurQual->units));
	}
	
	// Add variables
	for (var_ref* Cur = NewDataMsg->variables; Cur != NULL; Cur = Cur->next)
	{
		const xTEDSVariable* CurVar = VariablesList.Find(Cur->name, NewDataMsg->interface_name);
		
		if (CurVar == NULL)
		{
			printf("Error, could not find variable %s in interface %s being reference in data message %s.\n",Cur->name, NewDataMsg->interface_name, NewDataMsg->name);
			return false;	// Variable not found, error
		}
		
		// Otherwise, add to varibles list
		m_Variables.addItem(CurVar);
	}
	return true;
}

/*  Get a RegInfo request about this message */
MessageDef* xTEDSDataMsg::RegInfo(void) const
{
	char InfoBuf[MSG_DEF_SIZE];
	char xTEDSPortion[MSG_DEF_SIZE];
	int BufLength = 0;
	MessageDef* ReturnDef = new MessageDef();
	
	if (m_strItemName == NULL)
		return ReturnDef;
	
	xTEDSPortion[0] = InfoBuf[0] = '\0';

	snprintf(InfoBuf, sizeof(InfoBuf), "<DataMsg name=\"%s\" id=\"%d\" ", m_strItemName, m_ItemInterfaceMessageID.getInterfaceMessagePair());
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

/*  Create the xTEDS section corresponding to this Data message */
void xTEDSDataMsg::xTEDSInfo(char* InfoBufferOut, int BufferSize) const
{
	char xTEDSBuf[MSG_DEF_SIZE];
	const unsigned int xTEDSBufSize = sizeof(xTEDSBuf);
	int BufLength = 0;
	
	if (m_strItemName == NULL)
		return ;
	// Start with the empty string
	xTEDSBuf[0] = '\0';
	
	switch(msg_arrival)
	{
		case Event:
			snprintf(xTEDSBuf, xTEDSBufSize, "<DataMsg name=\"%s\" id=\"%d\" msgArrival=\"EVENT\"",m_strItemName,m_ItemInterfaceMessageID.getInterfaceMessagePair());
			break;
		case Periodic:
			if(msg_rate != 0.0f)
				snprintf(xTEDSBuf, xTEDSBufSize, "<DataMsg name=\"%s\" id=\"%d\" msgArrival=\"PERIODIC\" msgRate=\"%f\"", m_strItemName, m_ItemInterfaceMessageID.getInterfaceMessagePair(), msg_rate);
			else
				snprintf(xTEDSBuf, xTEDSBufSize, "<DataMsg name=\"%s\" id=\"%d\" msgArrival=\"PERIODIC\"",m_strItemName, m_ItemInterfaceMessageID.getInterfaceMessagePair());
			break;
		default:
			printf("Warning -- xTEDSDataMsg::xTEDSInfo - msg_arrival is invalid.\n");
	}
	// Add the description
	if(m_strItemDescription != NULL)
	{
		strncat(xTEDSBuf, " description=\"", xTEDSBufSize);
		strncat(xTEDSBuf, m_strItemDescription, xTEDSBufSize);
		strncat(xTEDSBuf, "\"", xTEDSBufSize);
	}
	// Close the tag
	strncat(xTEDSBuf, ">", xTEDSBufSize);
	// Add any qualifier elements
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
	// Close the CommandMsg
	strncat(xTEDSBuf, "\n\t</DataMsg>", xTEDSBufSize);
	
	strncat(InfoBufferOut, xTEDSBuf, BufferSize - 1);
}

bool xTEDSDataMsg::MatchesQualifier(const xTEDSQualifierList& QualList) const
{
	if(QualList.isEmpty())
		return true;
	
	char msg_rate_str[16], id_str[8];
	snprintf(msg_rate_str, sizeof(msg_rate_str), "%f", msg_rate);
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
			else if (CurQual.MatchesName("msgArrival"))
			{
				if (!CurQual.MatchesDescription((msg_arrival==Event?"EVENT":"PERIODIC")))
					return false;
			}
			else if (CurQual.MatchesName("msgRate"))
			{
				if (!CurQual.MatchesDescription(msg_rate_str))
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

bool xTEDSDataMsg::RegInfoMatch(const char* pname, const xTEDSQualifierList& qualifiers, const char* interface) const
{
	if (interface != NULL && strcmp(interface, m_strItemInterfaceName) != 0)
		return false;
	
	if (pname == NULL || strcmp(pname, m_strItemName) == 0)
	{
		if (MatchesQualifier(qualifiers))
			return true;
	}
	
	if (m_Variables.RegInfoMatch(pname, qualifiers, interface))
		return true;
	
	return false;
}

bool xTEDSDataMsg::RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const
{
	if (m_Variables.RegexMatch(Pattern, QualList, Interface))
		return true;
	
	return xTEDSItem::RegexMatch(Pattern, QualList, Interface);
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSDataMsg::PrintDebug() const
{
	char MsgArrivalStr[128];
	switch(msg_arrival)
	{
		case Event: 	
      strcpy(MsgArrivalStr, "Event"); 
      break;
		case Periodic: 	
      strcpy(MsgArrivalStr, "Periodic"); 
      break;
    default:
      break;
	}
	xTEDSMessage::PrintDebug();
	printf("   xTEDSDataMsg msg_arrival %s msg_rate %f\n\n", MsgArrivalStr, msg_rate);
	m_Variables.PrintDebug();
}
#endif



