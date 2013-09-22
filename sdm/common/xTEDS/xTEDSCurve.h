#ifndef __SDM_XTEDS_CURVE_H_
#define __SDM_XTEDS_CURVE_H_

#include "../message_defs.h"
extern "C"
{
#include "xTEDSParser.h"
}
#include "xTEDSCoefList.h"

class xTEDSCurve
{
public:
	xTEDSCurve();
	xTEDSCurve(const xTEDSCurve&);

	~xTEDSCurve();

	void setCurve(const curve* NewCurve);
	void setName(const char*);
	void setDescription(const char*);
	
  void VarInfoRequest(char* InfoBufferOut, size_t BufferSize) const;
private:
	xTEDSCurve& operator=(const xTEDSCurve&);
	char* m_strName;
	char* m_strDescription;
	xTEDSCoefList m_xclCoefs;
};

#endif
