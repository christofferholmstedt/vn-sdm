#ifndef __SDM_XTEDS_ITEM_H_
#define __SDM_XTEDS_ITEM_H_

#include "MessageDef.h"
#include "xTEDSQualifierList.h"
#include "../message/SDMMessage_ID.h"

class xTEDSItem
{
public:
	enum itemType {TYPE_VARIABLE, TYPE_DATAMSG, TYPE_COMMANDMSG, TYPE_FAULTMSG, TYPE_DATAREPLYMSG, TYPE_NONE};

	xTEDSItem();
	xTEDSItem(const xTEDSItem&);

	virtual ~xTEDSItem();

	virtual MessageDef* RegInfo() const = 0;
	virtual bool RegInfoMatch(const char* name, const xTEDSQualifierList&, const char* interface) const = 0;
	virtual bool RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const;
	void setName(char*);
	void setDescription(char*);
	void setInterfaceName(char*);
	void setInterfaceID(int id);
	void addQualifier(const xTEDSQualifier &NewQualifier);
	const char* getName(void) const { return m_strItemName; }
	const char* getDescription(void) const { return m_strItemDescription; }
	const char* getInterfaceName(void) const { return m_strItemInterfaceName; }
	int getInterfaceID() const { return m_ItemInterfaceMessageID.getInterface(); }
	itemType Type() const { return m_ItemType; }
	SDMMessage_ID GetID() const { return m_ItemInterfaceMessageID; }
	bool NameEquals(const char* CompareName) const;
	xTEDSItem& operator=(const xTEDSItem&);
	virtual void PrintDebug() const;
protected:
	char* m_strItemName;
	char* m_strItemDescription;
	xTEDSQualifierList* m_ItemQualifiers;
	virtual bool MatchesQualifier(const xTEDSQualifierList&) const = 0;
	itemType m_ItemType;
	char* m_strItemInterfaceName;
	SDMMessage_ID m_ItemInterfaceMessageID;

};

#endif
