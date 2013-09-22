//--------------------------------------------------------------------------------------
//---------------------------------WIN32 IMPLEMENTATION---------------------------------
//--------------------------------------------------------------------------------------
#include <pthread.h>
#include <sys/time.h>
#include <stdio.h>
#include "TimeKeeping.h"
#include "SDMTimeWin32.h"
#include "TimerList.h"
#include "LookupTable.h"

static LookupTable IDTable;
static pthread_mutex_t IDTableMutex = PTHREAD_MUTEX_INITIALIZER;
static TimerList Timers;
static pthread_mutex_t TimerMutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_t EventReceiver;
static pthread_mutex_t ThreadStartedMutex = PTHREAD_MUTEX_INITIALIZER;

struct DispatchArgs
{
	unsigned int TimeoutMs;
	int UpdateTableKey;
};
static bool ThreadStarted = false;

/*
 *  Initializes the timer service.  It prevents user program threads from being able to handle
 *  SIGALRM.  This problem is only applicable to the Linux and RTEMS builds.
 */

void SDM_TimeInit()
{
	InitializeTimeKeeping();
}

/*
 *  Gets the current system time and stores the current seconds in SecondsOut, and the current
 *  microseconds value in USecondsOut.
 *	Params:
 *		SecondsOut [OUTPUT] - Pointer location to store the current number of seconds
 *		USecondsOut [OUTPUT] - Pointer location to store the current number of micro seconds
 */
void SDM_GetTime(unsigned int *SecondsOut, unsigned int *USecondsOut)
{
	if (SecondsOut == NULL || USecondsOut == NULL) return;
	//Get and return the time from Windows
	LARGE_INTEGER count;
	QueryPerformanceCounter( &count );
	long long scaledCount = count.QuadPart - timeKeeping->tareCount;
	if ( timeKeeping->mode == 1 )
		scaledCount = (long long)(scaledCount*timeKeeping->ratio);
	unsigned long sec = (unsigned long)(scaledCount / timeKeeping->perfCountFreq);
	long long seconds = sec * timeKeeping->perfCountFreq;
	*SecondsOut = (unsigned int)(sec + timeKeeping->gpsEpochTareSeconds);
	*USecondsOut = (unsigned int)((scaledCount-seconds) * timeKeeping->uSecScale);
}

/*
*  Gets the current system time and returns it as a SecTime
*	Params:
*		SecTime [INPUT/OUTPUT] - Reference to a SecTime structure
*/
void SDM_GetTime( SecTime &secTime )
{
	//Get and return the time from Windows
	LARGE_INTEGER count;
	QueryPerformanceCounter( &count );
	long long scaledCount = count.QuadPart - timeKeeping->tareCount;
	if ( timeKeeping->mode == 1 )
		scaledCount = (long long)(scaledCount*timeKeeping->ratio);
	unsigned long sec = (unsigned long)(scaledCount / timeKeeping->perfCountFreq);
	long long seconds = sec * timeKeeping->perfCountFreq;
	secTime.SetSeconds( (unsigned int)(sec + timeKeeping->gpsEpochTareSeconds) );
	secTime.SetUSeconds( (unsigned int)((scaledCount-seconds) * timeKeeping->uSecScale) );
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
	UINT secondsAsMilliSeconds = (UINT)(Seconds * 1000 / timeKeeping->ratio);		//First add the Seconds
	//Convert microseconds to milliseconds, rounding up
	UINT ms = ((UINT)(USeconds/timeKeeping->ratio+999))/1000;
	
	Sleep(secondsAsMilliSeconds+ms);
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
int SDM_CreateTimer(unsigned int Seconds, unsigned int USeconds, void(*Callback)(int), bool Periodic)
{
	int UserID;
	pthread_t TimerThread;
	unsigned int CurSec, CurUSec;
	SDM_GetTime(&CurSec, &CurUSec);
	//Convert to milliseconds, if 0 < USeconds < 1000, default it to 1 ms
	if (USeconds > 0 && USeconds < 1000)
		USeconds = 1;
	else
		USeconds = static_cast<unsigned int>(USeconds / 1000.0);
	
	UINT TimeInMilliseconds = Seconds * 1000;	//First add the Seconds
	TimeInMilliseconds += USeconds;				//Now add the ms
	//
	// Add an empty value
	pthread_mutex_lock(&IDTableMutex);
	UserID = IDTable.AddValue(0);
	pthread_mutex_unlock(&IDTableMutex);
	//
	// Create a timer entry
	pthread_mutex_lock(&TimerMutex);
	Timers.AddTimer(Seconds, USeconds, CurSec, CurUSec, (void*)Callback, Periodic, UserID);
	pthread_mutex_unlock(&TimerMutex);
	//
	// Start the timer thread
	DispatchArgs *TimerThreadArgs = new DispatchArgs();
	TimerThreadArgs->UpdateTableKey = UserID;
	TimerThreadArgs->TimeoutMs = TimeInMilliseconds;
	pthread_create(&TimerThread, NULL, MessageDispatch, TimerThreadArgs);
	pthread_detach(TimerThread);
	return UserID;
}
/*
 *  Deletes the timer specified by TimerID.  This function has no effect if the timer specified does
 *  not exist.
 *
 */
void SDM_DeleteTimer(int TimerID)
{
	//
	// First, get the OS timer ID associated with the User timer ID
	pthread_t TimerThread;
	bool HaveThreadID = false;

	pthread_mutex_lock(&IDTableMutex);
	int OSTimerID = (int)IDTable.GetValueFromKey(TimerID);
	HaveThreadID = IDTable.GetThreadIDFromKey(TimerID, &TimerThread);
	pthread_mutex_unlock(&IDTableMutex);
	if (OSTimerID == 0)
	{
		printf("Could not identify the timer ID.\n");
		return;
	}
	//
	// Kill the timer with the OS
	if (!KillTimer(NULL, OSTimerID))
		printf("Could not stop the timer.\n");
	//
	// Remove the timer from the timers list
	pthread_mutex_lock(&TimerMutex);
	if (!Timers.RemoveTimer((int)TimerID))
		printf("Could not identify timer to remove.\n");
	pthread_mutex_unlock(&TimerMutex);
	//
	// Stop the timer thread
	if (HaveThreadID)
		pthread_cancel(TimerThread);
	else
		printf("Warning:  Could not stop timer thread for TimerID %d.\n",TimerID);
	//
	// Remove the IDTable entry for the timer
	pthread_mutex_lock(&IDTableMutex);
	IDTable.RemoveKeyGetValue(TimerID);
	pthread_mutex_unlock(&IDTableMutex);
}
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
	//
	// Get the current time
	unsigned int CurSec, CurUSec;
	SDM_GetTime(&CurSec, &CurUSec);
	//
	// Get current time remaining
	pthread_mutex_lock(&TimerMutex);
	int Result = Timers.GetTimeRemaining(TimerID, CurSec, CurUSec, SecondsOut, USecondsOut);
	pthread_mutex_unlock(&TimerMutex);
	return Result;
}
/*
 *  The timer event handler function.
 *
 */
void CALLBACK TimerFired(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime )
{
	//
	// Get the time that the timer fired
	unsigned int CurSec, CurUSec;
	SDM_GetTime(&CurSec, &CurUSec);
	//
	// Get the timer table entry
	pthread_mutex_lock(&IDTableMutex);
	int UserID = IDTable.GetKeyFromValue(idEvent);
	pthread_mutex_unlock(&IDTableMutex);
	if (UserID < 0)
	{
		printf("TimerFired:: Could not identify the timer.\n");
		return ;
	}
	//
	// Find out which timer was fired
	pthread_mutex_lock(&TimerMutex);
	void (*Callback)(int) = (void (*)(int))(Timers.GetCallback((int)UserID));
	bool IsPeriodic = Timers.IsPeriodic((int)UserID);
	//
	// Update timer time
	Timers.TimerFired(UserID, CurSec, CurUSec);
	pthread_mutex_unlock(&TimerMutex);
	//
	// If the timer is not periodic, remove it
	if (!IsPeriodic)
		SDM_DeleteTimer(UserID);
	//
	// Call the user's callback function
	if (Callback == NULL)
		return;
	(*Callback)(UserID);
}
/*
 *  Message dispatch thread for Win32 "signal" or event that a timer has expired.
 *
 */
void *MessageDispatch(void *ThreadArgs)
{
	DispatchArgs *Arguments = (DispatchArgs*)ThreadArgs;
	//
	// Create the timer
	UINT_PTR TimerID = SetTimer(NULL, NULL, Arguments->TimeoutMs, (TIMERPROC) TimerFired);
	//
	// Update the lookup table with the new entry
	pthread_t MyThreadID = pthread_self();
	pthread_mutex_lock(&IDTableMutex);
	IDTable.UpdateValue(Arguments->UpdateTableKey, (unsigned int)TimerID);
	IDTable.UpdateThreadIDFromKey(Arguments->UpdateTableKey, MyThreadID);
	pthread_mutex_unlock(&IDTableMutex);
	//
	// Free the arguments
	delete Arguments;

	MSG msg = { 0, 0, 0, 0 };
	while (1)
	{
		if (GetMessage(&msg, 0, 0, 0) )
		{
			if (msg.message == WM_TIMER)
			{
				DispatchMessage(&msg);
			}
		}
		Sleep(1);
	}
	return NULL;
}
