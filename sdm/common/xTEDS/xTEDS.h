#ifndef __XTEDS_H_
#define __XTEDS_H_

#include "xTEDSItemTree.h"
#include "xTEDSItem.h"
#include "MessageDef.h"
#include "VariableDef.h"

#include "../sdmLib.h"

class SDMLIB_API xTEDS
{
public:
	xTEDS();
	~xTEDS();
	xTEDS(const xTEDS&);
	xTEDS& operator=(const xTEDS&);
	
	bool Parse(char* xteds_text);
	
	MessageDef* RegInfo(const char* Name, const char* Qualifier, const char* Device, const char* Interface);
	MessageDef* AllRegInfo(const char* Qualifier, const char* Device, const char* Interface);
	MessageDef* RegexRegInfo(const char* Pattern, const char* Qualifier, const char* Device, const char* Interface);
	VariableDef* getVarInfo(const char* strVariableName, const SDMMessage_ID& idInterface) const;
	
	SDMMessage_ID getServiceDataMsgID(const SDMMessage_ID& CommandID) const;
	SDMMessage_ID getServiceFaultMsgID(const SDMMessage_ID& CommandID) const;
	SDMMessage_ID getCommandFaultMsgID(const SDMMessage_ID& CommandID) const;
	SDMMessage_ID getNotificationFaultMsgID(const SDMMessage_ID& DataID) const;
	bool isCommandIdValid(const SDMMessage_ID& RequestedId) const;
	bool isServiceIdValid(const SDMMessage_ID& RequestedId) const;
	
	const char* getDeviceName(void) const { return m_strDeviceName; }
	const char* getComponentKey(void) const { return m_strComponentKey; }
	const char* getSPAUHub(void) const { return m_strSPAUHub; }
	const char* getSPAUPort(void) const { return m_strSPAUPort; }
private:
	xTEDSItemTree m_TreeRoot;
	char* m_strDeviceName;
	char* m_strComponentKey;
	char* m_strSPAUHub;
	char* m_strSPAUPort;
};

#endif
