#ifndef _SDM_BAD_INDEX_EXCEPTION_H_
#define _SDM_BAD_INDEX_EXCEPTION_H_

#include "SDMException.h"
#include "../sdmLib.h"

class SDMLIB_API SDMBadIndexException : public SDMException
{
public:
	SDMBadIndexException(const char* strMessage);
	virtual ~SDMBadIndexException();
	virtual const char* Message() const;
};

#endif
