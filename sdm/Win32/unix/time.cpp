#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <errno.h>

#include "WinSock2.h"
#include <sys/time.h>

#include "sdmLib.h"

SDMLIB_API int gettimeofday(struct timeval *tv, struct timezone *tz)
{
  /*Get time in seconds*/
  time_t cur_time;
  time(&cur_time);
  tv->tv_sec = (long)cur_time;
  /*Get milliseconds of current seconds (even though Linux does it in microseconds)*/
  SYSTEMTIME sys_time;
  GetSystemTime(&sys_time);
  tv->tv_usec = sys_time.wMilliseconds;
  return 0;
}

void AlrmHandler(int sig){}
void (*sigalrmHandler)(int) = AlrmHandler;

typedef struct {
	itimerval Value;
	int resolutionMs, pendingMode;
	MMRESULT TimerId;
} RealTimer;
RealTimer realTimer = { 0,0,0,0, 10, -1, 0 };

SDMLIB_API int getitimer( int which, struct itimerval* value )
{
	if ( value == NULL )
		return EINVAL;
	switch ( which )
	{
	case ITIMER_REAL:
		*value = realTimer.Value;
		break;
	case ITIMER_VIRTUAL:
		break;
	case ITIMER_PROF:
		break;
  default:
    break;
	}
	return 0;
}

void RealTimerHandler(UINT timerId, UINT msg, DWORD_PTR user, DWORD_PTR one, DWORD_PTR two)
{
	sigalrmHandler(SIGALRM);
	RealTimer& rt = realTimer;
	if ( rt.pendingMode == TIME_PERIODIC )
	{
		int intervalMs = rt.Value.it_interval.tv_sec*1000 + rt.Value.it_interval.tv_usec/1000;
		realTimer.TimerId = timeSetEvent( intervalMs, realTimer.resolutionMs, (LPTIMECALLBACK)RealTimerHandler, NULL, realTimer.pendingMode );
		rt.pendingMode = -1; // latch this one occurance
	}
}

SDMLIB_API int setitimer( int which, const struct itimerval* value, struct itimerval* old )
{
	int intervalMs, mode;
	switch ( which )
	{
	case ITIMER_REAL:
		if ( old != NULL )
			*old = realTimer.Value;

		realTimer.resolutionMs = value->it_value.tv_usec/1000;
		if ( value->it_interval.tv_usec/1000 < realTimer.resolutionMs )
			realTimer.resolutionMs = value->it_interval.tv_usec/1000;
		realTimer.resolutionMs %= 10;
		if ( realTimer.resolutionMs == 0 ) realTimer.resolutionMs = 10; // if no usec, default to system clock
		timeBeginPeriod(realTimer.resolutionMs);

		realTimer.Value = *value;

		realTimer.pendingMode = -1;
		if ( value->it_interval.tv_sec || value->it_interval.tv_usec )
		{
			mode = TIME_PERIODIC;
			realTimer.pendingMode = TIME_PERIODIC;
			intervalMs = value->it_interval.tv_sec*1000+value->it_interval.tv_usec/1000;
		}
		if ( value->it_value.tv_sec || value->it_value.tv_usec )
		{
			int periodMs = value->it_value.tv_sec*1000+value->it_value.tv_usec/1000;
			if ( periodMs == intervalMs )
				realTimer.pendingMode = -1; // leave everything else as PERIODIC
			else
			{
				intervalMs = periodMs;
				mode = TIME_ONESHOT;
			}
		}
		realTimer.TimerId = timeSetEvent( intervalMs, realTimer.resolutionMs, (LPTIMECALLBACK)RealTimerHandler, NULL, mode );
		break;
	case ITIMER_VIRTUAL:
	case ITIMER_PROF:
		printf("Currently unimplemented\n");
		errno = EINVAL;
		return -1;
	default:
		errno = EINVAL;
		return -1;
	}
	return 0;
}

SDMLIB_API void sigset( int sig, void (*handler)(int) )
{
	if ( sig == SIGALRM )
		sigalrmHandler = handler;
}


