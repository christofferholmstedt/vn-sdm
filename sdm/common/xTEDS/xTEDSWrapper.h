#ifndef _SDM_XTEDS_WRAPPER_H_
#define _SDM_XTEDS_WRAPPER_H_

#include <stdlib.h>
#include "MessageDef.h"
#include "xTEDSQualifierList.h"
#include "../message/SDMMessage_ID.h"

class SDMLIB_API xTEDSWrapper
{
public:
	enum WrapperType { WRAPPER_NOTIFICATION, WRAPPER_REQUEST, WRAPPER_COMMAND, WRAPPER_EMPTY };
	
	xTEDSWrapper();
	xTEDSWrapper(const xTEDSWrapper&);
	xTEDSWrapper& operator=(const xTEDSWrapper&);
	virtual ~xTEDSWrapper();
	
	virtual MessageDef* RegInfo(const char* ItemName) const = 0;
	virtual bool RegInfoMatch(const char* Name, const xTEDSQualifierList& Qualifiers, const char* Interface) const = 0;
	virtual bool RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const = 0;
	virtual bool ContainsMessage(const SDMMessage_ID& MessageID) const = 0;
	virtual SDMMessage_ID GetFaultMessageID() const = 0;
	void setInterfaceName(const char* Name);
	void setInterfaceID(int ID);
	WrapperType GetType() const { return Type; }
	virtual void PrintDebug() const;
protected:
	WrapperType Type;
	char* InterfaceName;
	int InterfaceID;
};

#endif

