#include "xTEDSMessage.h"
#include "xTEDSItem.h"
#include "xTEDSVariableList.h"

#include <stdlib.h>

xTEDSMessage::xTEDSMessage():m_Variables()
{
}

xTEDSMessage::~xTEDSMessage()
{
}

bool xTEDSMessage::addVariable(xTEDSVariable* pVar)
{
	if (pVar == NULL) return false;
	m_Variables.addItem(pVar);
	return true;
}

int xTEDSMessage::getMessageID() const
{
	return m_ItemInterfaceMessageID.getMessage();
}

void xTEDSMessage::setMessageID(int NewID)
{
	if (NewID > 0 && NewID < 256)
		m_ItemInterfaceMessageID.setMessage(static_cast<unsigned char>(NewID));
}

VariableDef* xTEDSMessage::GetVariableXtedsDefinitions() const
{
  SDMMessage_ID defaultMessageId(0,0);

  // Request VarInfo for all of the variables
  return m_Variables.VarInfoRequest("", defaultMessageId, xTEDSVariableList::MATCH_ALL); 
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSMessage::PrintDebug() const
{
	printf("   ");
	xTEDSItem::PrintDebug();
}
#endif

