#ifndef __SDM_XTEDS_REQUEST_H_
#define __SDM_XTEDS_REQUEST_H_

#include "xTEDSItem.h"
#include "xTEDSDataMsg.h"
#include "xTEDSCommandMsg.h"
#include "xTEDSFaultMsg.h"
#include "xTEDSWrapper.h"
#include "xTEDSVariableList.h"

class xTEDSRequest:public xTEDSWrapper
{
public:
	xTEDSRequest();
	xTEDSRequest(const xTEDSRequest&);
	virtual ~xTEDSRequest();

	virtual MessageDef* RegInfo(const char* ItemName) const;
	virtual bool RegInfoMatch(const char* Name, const xTEDSQualifierList&, const char* Interface) const;
	virtual bool RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const;
	bool SetRequest(const request* Request, const xTEDSVariableList& VariablesList);
	bool ContainsMessage(const SDMMessage_ID& MessageID) const;
	SDMMessage_ID GetFaultMessageID() const;
	SDMMessage_ID GetDataMessageID() const;
	xTEDSRequest& operator=(const xTEDSRequest&);
	virtual void PrintDebug() const;
private:
	xTEDSDataMsg* m_ReplyMessage;
	xTEDSCommandMsg* m_CommandMessage;
	xTEDSFaultMsg* m_FaultMessage;
};

#endif
