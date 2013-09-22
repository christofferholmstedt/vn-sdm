#include "xTEDSItem.h"

#include <string.h>
#include <stdlib.h>
#include "../Regex/Regex.h"

xTEDSItem::xTEDSItem():m_strItemName(NULL),m_strItemDescription(NULL),m_ItemQualifiers(NULL),m_ItemType(TYPE_NONE),m_strItemInterfaceName(NULL),m_ItemInterfaceMessageID()
{
}

xTEDSItem::xTEDSItem(const xTEDSItem& b):m_strItemName(NULL),m_strItemDescription(NULL),m_ItemQualifiers(b.m_ItemQualifiers),m_ItemType(b.m_ItemType),m_strItemInterfaceName(NULL),m_ItemInterfaceMessageID(b.m_ItemInterfaceMessageID)
{
	if(m_strItemName!=NULL) free(m_strItemName);
	m_strItemName = strdup(b.m_strItemName);
	if(m_strItemDescription!=NULL) free(m_strItemDescription);
	m_strItemDescription = strdup(b.m_strItemDescription);
	if(m_strItemInterfaceName!=NULL) free(m_strItemInterfaceName);
	m_strItemInterfaceName = strdup(b.m_strItemInterfaceName);
}

xTEDSItem::~xTEDSItem()
{
	if(m_strItemName!=NULL) free(m_strItemName);
	if(m_strItemDescription!=NULL) free(m_strItemDescription);
	if(m_strItemInterfaceName!=NULL) free(m_strItemInterfaceName);
	if(m_ItemQualifiers!=NULL) delete(m_ItemQualifiers);
}

void xTEDSItem::setName(char* new_name)
{
	if (new_name == NULL) return;
	if(m_strItemName!=NULL) free(m_strItemName);
	m_strItemName = strdup(new_name);
}

void xTEDSItem::setDescription(char* new_description)
{
	if (new_description == NULL) return;
	if(m_strItemDescription!=NULL) free(m_strItemDescription);
	m_strItemDescription = strdup(new_description);
}

void xTEDSItem::setInterfaceName(char* new_interfacename)
{
	if (new_interfacename == NULL) return;
	if(m_strItemInterfaceName!=NULL) free(m_strItemInterfaceName);
	m_strItemInterfaceName = strdup(new_interfacename);
}

void xTEDSItem::setInterfaceID(int id)
{
	if (id > 0 && id < 255)
		m_ItemInterfaceMessageID.setInterface(static_cast<unsigned char>(id));
}

xTEDSItem& xTEDSItem::operator=(const xTEDSItem& b)
{
	if(m_strItemName!=NULL) free(m_strItemName);
	m_strItemName = strdup(b.m_strItemName);
	if(m_strItemDescription!=NULL) free(m_strItemDescription);
	m_strItemDescription = strdup(b.m_strItemDescription);
	if(m_strItemInterfaceName!=NULL) free(m_strItemInterfaceName);
	m_strItemInterfaceName = strdup(b.m_strItemInterfaceName);
	m_ItemType = b.m_ItemType;
	m_ItemInterfaceMessageID = b.m_ItemInterfaceMessageID;
	m_ItemQualifiers = b.m_ItemQualifiers;
	return *this;
}

void xTEDSItem::addQualifier(const xTEDSQualifier &NewQualifier)
{
	if (m_ItemQualifiers == NULL)
		m_ItemQualifiers = new xTEDSQualifierList();
	m_ItemQualifiers->addQualifier(NewQualifier);
}

bool xTEDSItem::NameEquals(const char* CompareName) const
{
	if (strcmp(m_strItemName, CompareName) == 0)
		return true;
	return false;
}

bool xTEDSItem::RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const
{
	if (DoesRegexMatch(m_strItemName, Pattern))
		return true;
	return false;
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSItem::PrintDebug() const
{
	char IDStr[128];
	char ItemTypeStr[128];
	
	switch(m_ItemType)
	{
		case TYPE_VARIABLE:	
      strcpy(ItemTypeStr, "TYPE_VARIABLE"); 
      break;
		case TYPE_DATAMSG:  	
      strcpy(ItemTypeStr, "TYPE_DATAMSG"); 
      break;
		case TYPE_COMMANDMSG:	
      strcpy(ItemTypeStr, "TYPE_COMMANDMSG"); 
      break;
		case TYPE_FAULTMSG:  	
      strcpy(ItemTypeStr, "TYPE_FAULTMSG"); 
      break;
		case TYPE_DATAREPLYMSG: 
      strcpy(ItemTypeStr, "TYPE_DATAREPLYMSG"); 
      break;
		case TYPE_NONE:  	
      strcpy(ItemTypeStr, "TYPE_NONE"); 
      break;
    default:
      break;
	}
	m_ItemInterfaceMessageID.IDToString(IDStr, sizeof(IDStr));
	printf("xTEDSItem name %s description %s interface %s type %s ID %s\n",m_strItemName, m_strItemDescription, m_strItemInterfaceName, ItemTypeStr, IDStr);
}
#endif
