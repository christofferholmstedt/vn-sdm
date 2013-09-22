#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "MemoryUtils.h"

SDMLIB_API 
char* SDM_strdup(const char* s)
{
	char* String = strdup(s);
	if (String == NULL)
	{
		SDMMemoryAllocError(__FUNCTION__);
	}
	return String;
}

SDMLIB_API 
char* SDM_strndup(const char* s, size_t n)
{
	char* String = strndup(s, n);

   if (String == NULL)
	{
		SDMMemoryAllocError(__FUNCTION__);
	}
	return String;
}

SDMLIB_API 
void* SDM_malloc(size_t size)
{
	void* Memory = malloc(size);
	if (Memory == NULL)
	{
		SDMMemoryAllocError(__FUNCTION__);
	}
	return Memory;
}

SDMLIB_API 
void SDMMemoryAllocError(const char* ErrorString)
{
	printf("Fatal Error - Could not allocate memory!\n  Error: %s\n", ErrorString);
	_exit(-1);
}

#ifdef __uClinux__
/* Petalinux for the ucLinux build doesn't have strndup */
char* strndup(const char* str, size_t n)
{
	size_t len = strlen(str);
	if ( len > n )
	{
		char* dup = (char*)malloc(n+1);
		strncpy(dup,str,n);
		dup[n] = 0;
		return dup;
	}
	else
		return strdup(str);
}
#endif

#ifdef __VXWORKS__
/* VxWorks doesn't have strndup */
char* strndup(const char* str, size_t n)
{
	size_t len = strlen(str);
	if ( len > n )
	{
		char* dup = (char*)malloc(n+1);
		strncpy(dup,str,n);
		dup[n] = 0;
		return dup;
	}
	else
		return strdup(str);
}
#endif



