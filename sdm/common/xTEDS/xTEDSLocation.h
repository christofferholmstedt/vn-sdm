#ifndef __SDM_XTEDS_LOCATION_H_
#define __SDM_XTEDS_LOCATION_H_

extern "C"
{
#include "xTEDSParser.h"
}

class xTEDSLocation
{
public:
	xTEDSLocation();
	~xTEDSLocation();
	xTEDSLocation(const xTEDSLocation&);
	xTEDSLocation& operator=(const xTEDSLocation&);
	
	void setX(const char *xStr);
	void setY(const char *yStr);
	void setZ(const char *zStr);
	void setUnits(const char *unitsStr);
	
	void setLocation(const char *x, const char *y, const char *z, const char *units);
	void setLocation(const location *loc);
	
  void VarInfoRequest(char* InfoBufferOut, size_t BufferSize);
private:
	char *m_strX;
	char *m_strY;
	char *m_strZ;
	char *m_strUnits;
};

#endif
