#ifndef __SDM_XTEDS_ORIENTATION_ITEM_H_
#define __SDM_XTEDS_ORIENTATION_ITEM_H_

extern "C"
{
#include "xTEDSParser.h"
}

class xTEDSOrientationItem
{
public:
	xTEDSOrientationItem();
	~xTEDSOrientationItem();
	xTEDSOrientationItem(const xTEDSOrientationItem&);
	xTEDSOrientationItem& operator=(const xTEDSOrientationItem&);
	
	void SetAxis(const char *);
	void SetAngle(const char *);
	void SetUnits(const char *);
	
	void SetOrientation(const orientation*);
	
	void VarInfoRequest(char* InfoBufferOut, size_t BufferLength) const;
private:
	char *m_strAxis;
	char *m_strAngle;
	char *m_strUnits;
};


#endif
