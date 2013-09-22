#include <unistd.h>
#include <stdio.h>
#include "ErrorUtils.h"

void ErrorUtils::MemoryAllocError(const char* ErrorString)
{
	printf("Fatal Error - Could not allocate memory!\n  Error: %s\n",ErrorString);
	_exit(-1);
}

void ErrorUtils::MemoryAllocError()
{
	MemoryAllocError("");
}

