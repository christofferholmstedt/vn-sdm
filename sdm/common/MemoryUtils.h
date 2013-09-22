#ifndef _SDM_MEMORY_UTILS_H_
#define _SDM_MEMORY_UTILS_H_

#include <string.h>
#include "sdmLib.h"

extern SDMLIB_API char* SDM_strdup(const char* s);
extern SDMLIB_API char* SDM_strndup(const char* s, size_t n);
extern SDMLIB_API void* SDM_malloc(size_t size);
extern SDMLIB_API void SDMMemoryAllocError(const char* ErrorString);
#ifdef __uClinux__
char* strndup(const char* str, size_t n);
#endif

#ifdef __VXWORKS__
char* strndup(const char* str, size_t n);
#endif

#endif
