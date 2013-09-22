#ifndef __SDM_XTEDS_MESSAGE_H_
#define __SDM_XTEDS_MESSAGE_H_

#include "xTEDSItem.h"
#include "xTEDSVariableList.h"
#include "xTEDSVariable.h"

class xTEDSMessage:public xTEDSItem
{
public:
	xTEDSMessage();
	xTEDSMessage(const xTEDSMessage&);
	virtual ~xTEDSMessage();

	xTEDSMessage& operator=(const xTEDSMessage&);

	bool addVariable(xTEDSVariable* );

	int getMessageID() const;
	void setMessageID(int NewID);
	virtual VariableDef* GetVariableXtedsDefinitions() const;
	virtual void PrintDebug() const;
protected:
	xTEDSVariableList m_Variables;
};

#endif
