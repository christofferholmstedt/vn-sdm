#ifndef __SDM_XTEDS_FAULT_MSG_H_
#define __SDM_XTEDS_FAULT_MSG_H_

#include "xTEDSMessage.h"
#include "xTEDSVariable.h"
#include "xTEDSVariableList.h"
#include "MessageDef.h"

class xTEDSFaultMsg:public xTEDSMessage
{
public:
	xTEDSFaultMsg();
	virtual ~xTEDSFaultMsg();

	MessageDef* RegInfo(void) const;
	virtual bool RegInfoMatch(const char* name, const xTEDSQualifierList&, const char* interface) const;
	virtual bool RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const;
	bool SetFaultMsg(const fault_msg* FaultMsg, const xTEDSVariableList& VariablesList);

	virtual void PrintDebug() const;
private:
	virtual bool MatchesQualifier(const xTEDSQualifierList&) const;
	void xTEDSInfo(char* InfoBufferOut, int BufferSize) const;
};

#endif
