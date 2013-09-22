#ifndef __unistd_h_
#define __unistd_h_

#include "stdlib.h"
#include <unix/fcntl.h>
#include "sdmLib.h"

//#define main AppMain

typedef unsigned short ushort;
typedef unsigned int uint;
typedef unsigned long ulong;

typedef unsigned short u_int16_t;
typedef unsigned int u_int32_t;

typedef int key_t;
typedef int pid_t;
typedef int uid_t;

// Missing defines for open
#ifndef S_IRUSR
#define S_IRUSR 0400
#define S_IWUSR 0200
#define S_IXUSR 0100
#endif
#ifndef S_IRGRP
#define S_IRGRP 0040
#define S_IWGRP 0020
#define S_IXGRP 0010
#endif
#ifndef S_IROTH
#define S_IROTH 0004
#define S_IWOTH 0002
#define S_IXOTH 0001
#endif

#define chmod wChmod
#define close wClose
#define read wRead
#define write wWrite
#define lseek wLseek
#define snprintf _snprintf

extern SDMLIB_API int fcntl(int fd, uint flags);
extern SDMLIB_API int fcntl(int fd, uint op, uint flags);
extern SDMLIB_API int open(const char* filepath, unsigned int flags);

#ifdef  __cplusplus
extern "C" {
#endif

extern SDMLIB_API void chdir(const char* newDirectory);
extern SDMLIB_API int chmod(const char* filename, int mode);
extern SDMLIB_API int close(int fd);
extern SDMLIB_API pid_t fork(void);
extern SDMLIB_API int ioctl(int fd, uint op, ...);
extern SDMLIB_API int pipe(int fd[2]);
extern SDMLIB_API int read(int fd, void* buffer, int len);
extern SDMLIB_API void sleep(uint seconds);
extern SDMLIB_API char* strerror_r(int errornum, char* buf, size_t len);
extern SDMLIB_API char* strndup(const char* str, size_t len);
extern SDMLIB_API void usleep( uint microseconds );
extern SDMLIB_API int write(int fd, const void* buffer, int len);
extern SDMLIB_API int lseek(int fd, long offset, int origin);

#ifdef __cplusplus
}
#endif

#endif // __unistd_h_
