#ifndef __SDM_XTEDS_COMMAND_MSG_H_
#define __SDM_XTEDS_COMMAND_MSG_H_

#include "xTEDSMessage.h"
#include "xTEDSVariable.h"
#include "MessageDef.h"
#include "xTEDSVariableList.h"


class xTEDSCommandMsg:public xTEDSMessage
{
public:
	xTEDSCommandMsg();
	virtual ~xTEDSCommandMsg();

	MessageDef* RegInfo(void) const;
	bool RegInfoMatch(const char* name, const xTEDSQualifierList& , const char* interface) const;
	virtual bool RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const;
	bool SetCommandMsg(const command_message* Command, const xTEDSVariableList& VariableList);

	virtual void PrintDebug() const;
private:
	bool MatchesQualifier(const xTEDSQualifierList&) const;
	void xTEDSInfo(char* InfoBufferOut, int BufferSize) const;
};

#endif
