#ifndef _SDM_REGEX_EXCEPTION_
#define _SDM_REGEX_EXCEPTION_

#include "SDMException.h"
#include "../sdmLib.h"

class SDMLIB_API SDMRegexException : public SDMException
{
public:
	SDMRegexException(const char* ExceptionMessage);
	virtual ~SDMRegexException();
	
	virtual const char* Message() const;
};

#endif

