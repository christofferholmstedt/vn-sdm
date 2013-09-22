#ifndef __SDM_XTEDS_DATA_MSG_H_
#define __SDM_XTEDS_DATA_MSG_H_

#include "xTEDSMessage.h"
#include "xTEDSVariable.h"
#include "SDMDataRates.h"
#include "MessageDef.h"
#include "xTEDSVariableList.h"
extern "C"
{
#include "xTEDSParser.h"
}

class xTEDSDataMsg:public xTEDSMessage
{
public:
	xTEDSDataMsg();
	virtual ~xTEDSDataMsg();

	MessageDef* RegInfo(void) const;
	virtual bool RegInfoMatch(const char* name, const xTEDSQualifierList&, const char* interface) const;
	virtual bool RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const;
	bool SetDataMsg(const data_msg* NewDataMsg, const xTEDSVariableList& VariablesList);

	SDMDataRates msg_arrival;
	float msg_rate;
	
	virtual void PrintDebug() const;
private:
	virtual bool MatchesQualifier(const xTEDSQualifierList&) const;
	void xTEDSInfo(char* InfoBufferOut, int BufferSize) const;
};

#endif
