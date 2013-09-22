//header for functions to do checksums for SDM messages

#include "../sdmLib.h"

#ifdef  __cplusplus
extern "C" {
#endif

extern SDMLIB_API int checksum(char* msg,int len);
extern SDMLIB_API int checksum_valid(char* msg,int len);

#ifdef  __cplusplus
}
#endif
