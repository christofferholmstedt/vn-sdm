#ifndef _SDM_ERROR_H_
#include "sdmLib.h"

// A central location for functions dealing with SDM related errors.

class SDMLIB_API  ErrorUtils
{
public:
	static void MemoryAllocError(const char* ErrorString);
	static void MemoryAllocError();
};

#endif
