#ifndef __SDM_XTEDS_COMMAND_H_
#define __SDM_XTEDS_COMMAND_H_

#include "xTEDSCommandMsg.h"
#include "xTEDSFaultMsg.h"
#include "xTEDSWrapper.h"
#include "xTEDSVariableList.h"

class xTEDSCommand:public xTEDSWrapper
{
public:
	xTEDSCommand();
	xTEDSCommand(const xTEDSCommand&);
	virtual ~xTEDSCommand();

	virtual MessageDef* RegInfo(const char* ItemName) const;
	virtual bool RegInfoMatch(const char* Name, const xTEDSQualifierList&, const char* Interface) const;
	virtual bool RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const;
	xTEDSCommand& operator=(const xTEDSCommand&);
	bool SetCommand(const command* Command, const xTEDSVariableList& VariableList);
	bool ContainsMessage(const SDMMessage_ID& MessageID) const;
	SDMMessage_ID GetFaultMessageID() const;
	virtual void PrintDebug() const;
private:
	xTEDSCommandMsg* m_CommandMessage;
	xTEDSFaultMsg* m_FaultMessage;
};

#endif
