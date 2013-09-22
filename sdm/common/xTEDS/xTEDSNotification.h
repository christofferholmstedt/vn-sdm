#ifndef __SDM_XTEDS_NOTIFICATION_H_
#define __SDM_XTEDS_NOTIFICATION_H_

#include "xTEDSItem.h"
#include "xTEDSDataMsg.h"
#include "xTEDSFaultMsg.h"
#include "xTEDSWrapper.h"
#include "xTEDSVariableList.h"

class xTEDSNotification:public xTEDSWrapper
{
public:
	xTEDSNotification();
	xTEDSNotification(const xTEDSNotification&);
	virtual ~xTEDSNotification();

	virtual MessageDef* RegInfo(const char* ItemName) const;
	virtual bool RegInfoMatch(const char* Name, const xTEDSQualifierList& , const char* Interface) const;
	virtual bool RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const;
	bool SetNotification(const notification* Notification, const xTEDSVariableList& VariablesList);
	bool ContainsMessage(const SDMMessage_ID& MessageID) const;
	SDMMessage_ID GetFaultMessageID() const;
	
	xTEDSNotification& operator=(const xTEDSNotification&);
	virtual void PrintDebug() const;
private:
	xTEDSDataMsg* m_DataMessage;
	xTEDSFaultMsg* m_FaultMessage;
};

#endif
