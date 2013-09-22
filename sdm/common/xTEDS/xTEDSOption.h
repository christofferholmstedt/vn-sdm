#ifndef __SDM_XTEDS_OPTION_H_
#define __SDM_XTEDS_OPTION_H_

#include "../message_defs.h"
#include <cstring>
extern "C"
{
#include "xTEDSParser.h"
}

class xTEDSOption
{
public:
	xTEDSOption();
	xTEDSOption(const xTEDSOption&);

	~xTEDSOption();

	void setName(const char*);
	void setDescription(const char*);
	void setValue(const char*);
	void setAlarm(const char*);
	void setOption(const curveoption* Option);

  void VarInfoRequest(char* InfoBufferOut, size_t BufferSize) const;

	xTEDSOption& operator=(const xTEDSOption&);
private:
	char* m_strName;
	char* m_strDescription;
	char* m_strValue;
	char* m_strAlarm;
};

#endif
