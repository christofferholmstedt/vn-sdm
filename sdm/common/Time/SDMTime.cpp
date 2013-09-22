




//--------------------------------------------------------------------------------------
//---------------------------------RTEMS IMPLEMENTATION---------------------------------
//--------------------------------------------------------------------------------------
#elif defined (RTEMS_BUILD)
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
#ifdef WIN32
	//Get and return the time from Windows
	time_t CurSeconds;
	time(&CurSeconds);
	*SecondsOut = static_cast<long>(SecondsOut);
	
	SYSTEMTIME SysTime;
	GetSystemTime(&SysTime);
	*USecondsOut = static_cast<long>(SysTime.wMilliseconds);
#elif defined (RTEMS_BUILD)
	//Get and return the time from RTEMS
#else
	//Get and return the time from Linux
	struct timeval CurrTime;
	gettimeofday(&CurrTime, NULL);
	*SecondsOut = static_cast<long>(CurrTime.tv_sec);
	*USecondsOut = static_cast<long>(CurrTime.tv_usec);
#endif
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
	sleep(Seconds);
	usleep(USeconds);
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

}
/*
 *  Deletes the timer specified by TimerID.  This function has no effect if the timer specified does
 *  not exist.
 *
 */
void SDM_DeleteTimer(int TimerID)
{

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
int SDM_ReadTimer(int TimerID, unsigned int *SecondsOut, unsigned int *USecondsOut);
{

}




#endif
