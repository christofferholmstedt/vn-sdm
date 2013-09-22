#ifndef _SDM_EXCEPTION_H_
#define _SDM_EXCEPTION_H_

#include "../sdmLib.h"
#include <string.h>

class SDMLIB_API SDMException
{
public:
	SDMException();
	SDMException(const char* ExceptionMessage);
	virtual ~SDMException();
	
	virtual const char* Message() const;
private:
	char m_strMessage[256];
};


#endif
