#ifndef __time_h
#define __time_h

#include "sdmLib.h"

extern SDMLIB_API int gettimeofday(struct timeval *tv, struct timezone *tz);

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

struct itimerval {
	struct timeval it_interval;
	struct timeval it_value;
	};

#define ITIMER_REAL 0
#define ITIMER_VIRTUAL 1
#define ITIMER_PROF 2

#define SIGALRM 14

extern SDMLIB_API void sigset( int sig, void (*handler)(int) );
extern SDMLIB_API int setitimer( int which, const struct itimerval* newInterval, struct itimerval* old );
extern SDMLIB_API int getitimer( int which, struct itimerval* old );

#endif
