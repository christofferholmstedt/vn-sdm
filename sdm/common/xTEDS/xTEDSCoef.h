#ifndef __SDM_XTEDS_COEF_H_
#define __SDM_XTEDS_COEF_H_

#include "../message_defs.h"
extern "C"
{
#include "xTEDSParser.h"
}
#include <cstring>

class xTEDSCoef
{
public:
	xTEDSCoef();
	xTEDSCoef(const xTEDSCoef&);
	xTEDSCoef& operator=(const xTEDSCoef&);
	~xTEDSCoef();

	void setCoef(const coef* NewCoef);
	void setDescription(const char*);
	void setValue(const char*);
	void setExponent(const char*);

  void VarInfoRequest(char* InfoBufferOut, size_t BufferSize) const;
private:
	char* m_strDescription;
	char* m_strValue;
	char* m_strExponent;
};

#endif
