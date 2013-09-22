#ifndef __SDM_XTEDS_DRANGE_H_
#define __SDM_XTEDS_DRANGE_H_

#include "../message_defs.h"
#include "xTEDSOptionList.h"
extern "C"
{
#include "xTEDSParser.h"
}

class xTEDSDrange
{
public:
	xTEDSDrange();
	xTEDSDrange(const xTEDSDrange&);
	xTEDSDrange& operator=(const xTEDSDrange&);
	~xTEDSDrange();

	void setName(const char*);
	void setDescription(const char*);
	void setDRange(const drange* NewRange);
	
  void VarInfoRequest(char* InfoBufferOut, size_t BufferSize) const;
private:
	char* m_strName;
	char* m_strDescription;
	xTEDSOptionList m_xolOptions;
};

#endif
