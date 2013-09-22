//--------------------------------------------------------------------------------------
//---------------------------------LINUX IMPLEMENTATION---------------------------------
//--------------------------------------------------------------------------------------
#include <sys/time.h>
#include <unistd.h>
#include <signal.h>
#include <pthread.h>
#include <stdio.h>
#include "TimerList.h"
#include "SDMTimeLinux.h"
#include "TimeKeeping.h"

#ifdef __VXWORKS__
#include <vxWorks.h>
#include <time.h>
#include <timers.h >
#endif

#define DEBUG_TIMER	1

static TimerList Timers;
static pthread_mutex_t TimerMutex = PTHREAD_MUTEX_INITIALIZER;
static bool HandlerThreadStarted = false;
static pthread_mutex_t HandlerStartedMutex = PTHREAD_MUTEX_INITIALIZER;

/*
 *  Initializes the timer service.  It prevents user program threads from being able to handle
 *  SIGALRM.  This problem is only applicable to the Linux and RTEMS builds.
 *
 *
*/
void SDM_TimeInit()
{
	//Set the global thread mask to ignore SIGALRM
	sigset_t SignalMask;
	sigemptyset(&SignalMask);
	sigaddset(&SignalMask, SIGALRM);
	if ((pthread_sigmask(SIG_BLOCK, &SignalMask, NULL)) != 0)
		perror("SDM_TimeInit::pthread_sigmask(): ");
}
/*
 *  Gets the current system time and stores the current seconds in SecondsOut, and the current
 *  microseconds value in USecondsOut.
 *	Params:
 *		SecondsOut [OUTPUT] - Pointer location to store the current number of seconds
 *		USecondsOut [OUTPUT] - Pointer location to store the current number of micro seconds
 */

/* If this is Linux or uClinux with a FSWIL time source */
#if !defined(__uClinux__) || defined(BUILD_FSWIL_TIMESYNC_TIME_SOURCE)
void SDM_GetTime(unsigned int *SecondsOut, unsigned int *USecondsOut)
{
	if (SecondsOut == NULL || USecondsOut == NULL) return;
	if (false == IsTimeInitialized())
	  {
	    InitializeTimeKeeping();
	  }

#ifdef __VXWORKS__  //VxWorks has nanosecond precision
	struct timespec tv;
	int tv_usec;
	clock_gettime(CLOCK_REALTIME, &tv);
	tv_usec = tv.tv_nsec/1000;
	long long scaledCount = tv.tv_sec*1000000LL - timeKeeping->tareCount + tv_usec;

	if ( timeKeeping->mode == 1 )
	{
		  scaledCount = (long long)(scaledCount*timeKeeping->ratio);
	}
	unsigned long sec = (unsigned long)(scaledCount / timeKeeping->perfCountFreq);
	long long seconds = sec * timeKeeping->perfCountFreq;
	*SecondsOut = (unsigned int)(sec + timeKeeping->gpsEpochTareSeconds);
	*USecondsOut = (unsigned int)((scaledCount-seconds) * timeKeeping->uSecScale);
#else  
	struct timeval tv;
	gettimeofday(&tv, NULL);
	long long scaledCount = tv.tv_sec*1000000LL - timeKeeping->tareCount + tv.tv_usec;
	if ( timeKeeping->mode == 1 )
	{
	  scaledCount = (long long)(scaledCount*timeKeeping->ratio);
	}
	unsigned long sec = (unsigned long)(scaledCount / timeKeeping->perfCountFreq);
	long long seconds = sec * timeKeeping->perfCountFreq;
	*SecondsOut = (unsigned int)(sec + timeKeeping->gpsEpochTareSeconds);
	*USecondsOut = (unsigned int)((scaledCount-seconds) * timeKeeping->uSecScale);
#endif
}
#else /* Otherwise, build for uClinux with a low-level TAT message */

struct sysclock {
  unsigned long CLOCK_VER;
  unsigned long CLOCK_STAT;
  unsigned long CLOCK_CTRL;
  unsigned long TIME_SEC;
  unsigned long TIME_SUBSEC;
  unsigned long TAT_SEC;
  unsigned long TAT_SUBSEC;
  unsigned long RES_SUBSEC;
} __attribute__((packed));

#warning "Unmaintainable definition"
#define CONFIG_XILINX_SYSCLOCK_PNP_0_BASEADDR 0x81610000

void SDM_GetTime(unsigned int *SecondsOut, unsigned int *USecondsOut)
{
	if (SecondsOut == NULL || USecondsOut == NULL) return;
	struct timeval tv;
	volatile struct sysclock *ssysclk = (struct sysclock*)(CONFIG_XILINX_SYSCLOCK_PNP_0_BASEADDR);

	unsigned long sec1;
	unsigned long sec2;
	unsigned long subs;

	sec1 = ssysclk->TIME_SEC;

	if (sec1 != 0) {
	  subs = ssysclk->TIME_SUBSEC;
	  sec2 = ssysclk->TIME_SEC;
	  
	  /*
	   * Detect rollover. We have one second
	   * to win the race.
	   */
	  if (sec1 != sec2) {
	    sec1 = ssysclk->TIME_SEC;
	    subs = ssysclk->TIME_SUBSEC;
	  }

	  *SecondsOut = sec1;
	  *USecondsOut = subs;
	}
	else {
	  /*
	   * Clock not running?
	   */
	  gettimeofday(&tv, NULL);
	  
	  *SecondsOut = tv.tv_sec;
	  *USecondsOut = tv.tv_usec;
	}
}
#endif

/*
*  Gets the current system time and returns it as a SecTime
*	Params:
*		SecTime [INPUT/OUTPUT] - Reference to a SecTime structure
*/
void SDM_GetTime( SecTime &secTime )
{
  unsigned int uiSec;
  unsigned int uiUsec;

  SDM_GetTime(&uiSec, &uiUsec);
  secTime.SetSeconds(uiSec);
  secTime.SetUSeconds(uiUsec);
}

/*
 *  Sleep for the time specified in Seconds and USeconds.
 *	Params:
 *		Seconds - The number of seconds to sleep
 *		USeconds - The number of microseconds to sleep
 *
 */
void SDM_Sleep(unsigned int Seconds, unsigned int USeconds)
{
#ifndef __uClinux__
  unsigned int secs = (unsigned int)(Seconds / timeKeeping->ratio);
  unsigned int usecs = (unsigned int)(USeconds / timeKeeping->ratio);

  sleep(secs);
  usleep(usecs);
#else
  sleep(Seconds);
  usleep(USeconds);
#endif
}
/*
 *  Create a timer to expire at the specified number of Seconds and USeconds.  This function returns
 *  an ID number for the timer to distinguish between multiple timers, and to perform other timer
 *  related operations on the ID.  Optionally, the function specified by Callback will be called
 *  when the timer expires.
 *	Params:
 *		Seconds - The number of seconds until the timer is to expire
 *		USeconds - The number of microseconds until the timer is to expire
 *		Callback - The function to call when the timer expires (can be NULL).
 *		Periodic - Whether the timer should auto-restart upon expiration.
 *	Returns:
 *		int - An identifier number for the timer.
 */
#ifndef __VXWORKS__ //For all version except VxWorks
int SDM_CreateTimer(unsigned int Seconds, unsigned int USeconds, void(*Callback)(int), bool Periodic)
{
	//Start the signal handling thread
	pthread_mutex_lock(&HandlerStartedMutex);
	// If the handler needs to be started
	if (!HandlerThreadStarted)
	{
		//Set the global thread mask to ignore SIGALRM
		sigset_t SignalMask;
		sigemptyset(&SignalMask);
		sigaddset(&SignalMask, SIGALRM);
		if ((pthread_sigmask(SIG_BLOCK, &SignalMask, NULL)) != 0)
		{
			perror("SDM_CreateTimer::pthread_sigmask(): ");
			pthread_mutex_unlock(&HandlerStartedMutex);
			return -1;
		}
		//Start the HandlerThread
		pthread_t HandlerThread;
		if (pthread_create (&HandlerThread, NULL, TimerHandler, NULL) != 0)
		{
			perror("SDM_CreateTimer::pthread_create(): ");
			pthread_mutex_unlock(&HandlerStartedMutex);
			return -1;
		}
		pthread_detach(HandlerThread);
		//Now the thread has started, update the HandlerThreadStarted
		HandlerThreadStarted = true;
	}
	pthread_mutex_unlock(&HandlerStartedMutex);
	
	//Get the current time
	unsigned int CurSec, CurUSec;
	SDM_GetTime(&CurSec, &CurUSec);
	//Add the timer to the list
	pthread_mutex_lock(&TimerMutex);
	
	int TimerNum = Timers.AddTimer(Seconds, USeconds, CurSec, CurUSec, (void*)Callback, Periodic);
	bool TimerListEmpty = Timers.IsEmpty();
	//See if there is already a timer running

	itimerval TimeVal;
	getitimer(ITIMER_REAL, &TimeVal);
	
	if (TimerListEmpty || (TimeVal.it_value.tv_sec == 0 && TimeVal.it_value.tv_usec == 0))
	{
		Timers.SetRunningTimer(TimerNum);
		//Start a new timer
		TimeVal.it_value.tv_sec = Seconds;
		TimeVal.it_value.tv_usec = USeconds;

		setitimer(ITIMER_REAL, &TimeVal, NULL);

	}
	//If the current running timer won't expire before this one needs to, reset it to this timer
	else if (static_cast<unsigned int>(TimeVal.it_value.tv_sec) > Seconds || (static_cast<unsigned int>(TimeVal.it_value.tv_sec) == Seconds && static_cast<unsigned int>(TimeVal.it_value.tv_usec) > USeconds))
	{
		Timers.SetRunningTimer(TimerNum);
		TimeVal.it_value.tv_sec = Seconds;
		TimeVal.it_value.tv_usec = USeconds;

		setitimer(ITIMER_REAL, &TimeVal, NULL);
	}
	pthread_mutex_unlock(&TimerMutex);
	return TimerNum;
}


/*
 *  Deletes the timer specified by TimerID.  This function has no effect if the timer specified does
 *  not exist.
 *
 */
void SDM_DeleteTimer(int TimerID)
{
	//Get the current time
	unsigned int CurSec, CurUSec, t1, t2;
	SDM_GetTime(&CurSec, &CurUSec);
	
	pthread_mutex_lock(&TimerMutex);
	int TempID = Timers.GetRunningTimer();
	Timers.RemoveTimer(TimerID);
	pthread_mutex_unlock(&TimerMutex);
	//If the deleted timer is the one currently running, cancel the timer
	if (TempID == TimerID)
	{
		itimerval TimeVal;
		TimeVal.it_value.tv_sec = 0;
		TimeVal.it_value.tv_usec = 0;

		setitimer(ITIMER_REAL, &TimeVal, NULL);

		//Start the new timer
		pthread_mutex_lock(&TimerMutex);
		TempID = Timers.GetSmallestTimerInterval(CurSec, CurUSec, &t1, &t2);
		pthread_mutex_unlock(&TimerMutex);
		//If no more timers
		if (TempID < 0)
			return ;
		//Otherwise, set this timer
		TimeVal.it_value.tv_sec = t1;
		TimeVal.it_value.tv_usec = t2;
		Timers.SetRunningTimer(TempID);

		setitimer(ITIMER_REAL, &TimeVal, NULL);
	}	
}

#else  //VxWorks version - uses POSIX Timers 
int SDM_CreateTimer(unsigned int Seconds, unsigned int USeconds, void(*Callback)(int), bool Periodic)
{
	//Start the signal handling thread
	pthread_mutex_lock(&HandlerStartedMutex);
	// If the handler needs to be started
	if (!HandlerThreadStarted)
	{
		//Set the global thread mask to ignore SIGALRM
		sigset_t SignalMask;
		sigemptyset(&SignalMask);
		sigaddset(&SignalMask, SIGALRM);
		if ((pthread_sigmask(SIG_BLOCK, &SignalMask, NULL)) != 0)
		{
			perror("SDM_CreateTimer::pthread_sigmask(): ");
			pthread_mutex_unlock(&HandlerStartedMutex);
			return -1;
		}
		//Start the HandlerThread
		pthread_t HandlerThread;
		if (pthread_create (&HandlerThread, NULL, TimerHandler, NULL) != 0)
		{
			perror("SDM_CreateTimer::pthread_create(): ");
			pthread_mutex_unlock(&HandlerStartedMutex);
			return -1;
		}
		pthread_detach(HandlerThread);
		//Now the thread has started, update the HandlerThreadStarted
		HandlerThreadStarted = true;
	}
	pthread_mutex_unlock(&HandlerStartedMutex);
	
	//Get the current time
	unsigned int CurSec, CurUSec;
	SDM_GetTime(&CurSec, &CurUSec);
	//Add the timer to the list
	pthread_mutex_lock(&TimerMutex);
	
	int TimerNum = Timers.AddTimer(Seconds, USeconds, CurSec, CurUSec, (void*)Callback, Periodic);
	bool TimerListEmpty = Timers.IsEmpty();
	//See if there is already a timer running

	itimerspec TimeVal;
	timer_gettime(CLOCK_REALTIME, &TimeVal);
	
	if (TimerListEmpty || (TimeVal.it_value.tv_sec == 0 && TimeVal.it_value.tv_nsec == 0))
	{
		Timers.SetRunningTimer(TimerNum);
		//Start a new timer
		TimeVal.it_value.tv_sec = Seconds;
		TimeVal.it_value.tv_nsec = USeconds*1000;

		timer_settime(CLOCK_REALTIME, 0, &TimeVal, NULL);
	}
	//If the current running timer won't expire before this one needs to, reset it to this timer
	else if (static_cast<unsigned int>(TimeVal.it_value.tv_sec) > Seconds || (static_cast<unsigned int>(TimeVal.it_value.tv_sec) == Seconds && static_cast<unsigned int>(TimeVal.it_value.tv_nsec) > USeconds*1000))
	{
		Timers.SetRunningTimer(TimerNum);
		TimeVal.it_value.tv_sec = Seconds;
		TimeVal.it_value.tv_nsec = USeconds * 1000;

		timer_settime(CLOCK_REALTIME, 0, &TimeVal, NULL);
	}
	pthread_mutex_unlock(&TimerMutex);
	return TimerNum;
}

/*
 *  Deletes the timer specified by TimerID.  This function has no effect if the timer specified does
 *  not exist.
 *
 */
void SDM_DeleteTimer(int TimerID)
{
	//Get the current time
	unsigned int CurSec, CurUSec, t1, t2;
	SDM_GetTime(&CurSec, &CurUSec);
	
	pthread_mutex_lock(&TimerMutex);
	int TempID = Timers.GetRunningTimer();
	Timers.RemoveTimer(TimerID);
	pthread_mutex_unlock(&TimerMutex);
	//If the deleted timer is the one currently running, cancel the timer
	if (TempID == TimerID)
	{
		itimerspec TimeVal;
		TimeVal.it_value.tv_sec = 0;
		TimeVal.it_value.tv_nsec = 0;

		timer_settime(CLOCK_REALTIME, 0, &TimeVal, NULL);

		//Start the new timer
		pthread_mutex_lock(&TimerMutex);
		TempID = Timers.GetSmallestTimerInterval(CurSec, CurUSec, &t1, &t2);
		pthread_mutex_unlock(&TimerMutex);
		//If no more timers
		if (TempID < 0)
			return ;
		//Otherwise, set this timer
		TimeVal.it_value.tv_sec = t1;
		TimeVal.it_value.tv_nsec = t2*1000;
		Timers.SetRunningTimer(TempID);

		timer_settime(CLOCK_REALTIME, 0, &TimeVal, NULL);
	}	
}
#endif


/*
 *  Reads the current value for the TimerID specified.  The time returned in the output
 *  parameters is the time remaining until the timer expires.
 *	Params:
 *		TimerID - Identifier number of the timer
 *		SecondsOut [OUTPUT] - Pointer to the location where to store the seconds remaining
 *		USecondsOut [OUTPUT] - Pointer to the location where to store the micro seconds remaining
 *	Returns:
 *		int - 0 on success, or -1 if some error occurred
 *
 */
int SDM_ReadTimer(int TimerID, unsigned int *SecondsOut, unsigned int *USecondsOut)
{
	unsigned int CurSec, CurUSec;
	SDM_GetTime(&CurSec, &CurUSec);
	//
	// Get the time remaining on the timer specified
	pthread_mutex_lock(&TimerMutex);
	int Result = Timers.GetTimeRemaining(TimerID, CurSec, CurUSec, SecondsOut, USecondsOut);
	pthread_mutex_unlock(&TimerMutex);
	
	return Result;
}

/*
 *  Signal handler (for SIGALRM only).  Because this thread must lock a mutex, it should be the only thread
 *  to ever handle SIGALRM.
 */
void* TimerHandler(void *ignored)
{
	sigset_t SignalMask;
	sigemptyset(&SignalMask);
	sigaddset(&SignalMask, SIGALRM);
	int SigNum;
	while (1)
	{
		if (sigwait(&SignalMask, &SigNum) != 0)
		{
			perror ("TimerHandler::sigwait(): ");
			return NULL;
		}
		if (SigNum != SIGALRM) continue;
		//Get the current time
		unsigned int CurSec, CurUSec;
		SDM_GetTime(&CurSec, &CurUSec);
		//Find out which timer expired
		pthread_mutex_lock(&TimerMutex);
		int TimerID = Timers.WhichExpired(CurSec, CurUSec);
		if (TimerID < 0)
		{
			printf("Error (SDMTime::TimerHandler):  Could not identify the expired timer.\n");
			pthread_mutex_unlock(&TimerMutex);
			continue;
		}
		//Keep processing until all finished timers are done
		bool TimerSet = false;
		while (TimerID > 0)
		{
			//Remove the timer if it is finished
			if (!Timers.IsPeriodic(TimerID))
				Timers.RemoveTimer(TimerID);
			//Restart with the minimum timer
			unsigned int NewSec, NewUSec;
			int NewTimerID = Timers.GetSmallestTimerInterval(CurSec, CurUSec, &NewSec, &NewUSec);
			
#ifndef __VXWORKS__
			itimerval TimerVal;
			//See if a timer is currently running
			if (!TimerSet)
			{
				//If no timer is running, start this one, we can be sure that the first
				//entry returned from WhichExpired() is the smallest first
				TimerVal.it_value.tv_sec = NewSec;
				TimerVal.it_value.tv_usec = NewUSec;
				TimerVal.it_interval.tv_sec = 0;
				TimerVal.it_interval.tv_usec = 0;
				//Set the timer
				Timers.SetRunningTimer(NewTimerID);
				TimerSet = true;

				setitimer(ITIMER_REAL, &TimerVal, NULL);
			}
#else
			itimerspec TimerVal;
			//See if a timer is currently running
			if (!TimerSet)
			{
				//If no timer is running, start this one, we can be sure that the first
				//entry returned from WhichExpired() is the smallest first
				TimerVal.it_value.tv_sec = NewSec;
				TimerVal.it_value.tv_nsec = NewUSec*1000;
				TimerVal.it_interval.tv_sec = 0;
				TimerVal.it_interval.tv_nsec = 0;
				//Set the timer
				Timers.SetRunningTimer(NewTimerID);
				TimerSet = true;
			
				timer_settime(CLOCK_REALTIME, 0, &TimerVal, NULL);
			}
#endif
			
			//Call the user's callback function
			void (*Callback)(int) = (void (*)(int))(Timers.GetCallback(TimerID));
			if (Callback == NULL)
			{
				TimerID = Timers.WhichExpired(CurSec, CurUSec);
				continue;
			}
			(*Callback)(TimerID);
			//Get the next timer
			TimerID = Timers.WhichExpired(CurSec, CurUSec);
		}
		pthread_mutex_unlock(&TimerMutex);
	}
	return NULL;
}

#ifdef __VXWORKS__
void usleep(int uSecs)
{
	int nanoSecs = uSecs * 1000;
	struct timespec time;
	time.tv_sec = 0;
	time.tv_nsec = nanoSecs;	
	nanosleep(&time, NULL);
}
#endif
