#include <unistd.h>
#include <stdlib.h>
#include "TimerList.h"

#include <stdio.h>

TimerList::TimerList():CurID(1),CurRunningTimer(-1)
{
}
/*
 *
 *
 */
int TimerList::AddTimer(unsigned int Seconds, unsigned int USeconds, unsigned int CurSeconds, unsigned int CurUSeconds, void *Callback, bool Periodic, unsigned int AssignedID)
{
	//Find an inactive timer entry
	int i = 0;
	for (i = 0; i < MAX_NUM_TIMERS; i++)
		if (Timers[i].TimerID == 0)
			break;
	//If no entries, return error
	if (i == MAX_NUM_TIMERS) return -1;
	//i is the index of an available timer entry
	Timers[i].TimerVal.SetSeconds(Seconds);
	Timers[i].TimerVal.SetUSeconds(USeconds);
	Timers[i].StartTime.SetSeconds(CurSeconds);
	Timers[i].StartTime.SetUSeconds(CurUSeconds);
	Timers[i].Callback = Callback;
	Timers[i].TimerID = AssignedID;
	Timers[i].Periodic = Periodic;
	return Timers[i].TimerID;
}
/*
 *
 *
 */
int TimerList::AddTimer(unsigned int Seconds, unsigned int USeconds, unsigned int CurSeconds, unsigned int CurUSeconds, void *Callback, bool Periodic)
{
	//Find an inactive timer entry
	int i = 0;
	for (i = 0; i < MAX_NUM_TIMERS; i++)
		if (Timers[i].TimerID == 0)
			break;
	//If no entries, return error
	if (i == MAX_NUM_TIMERS) return -1;
	//i is the index of an available timer entry
	Timers[i].TimerVal.SetSeconds(Seconds);
	Timers[i].TimerVal.SetUSeconds(USeconds);
	Timers[i].StartTime.SetSeconds(CurSeconds);
	Timers[i].StartTime.SetUSeconds(CurUSeconds);
	Timers[i].Callback = Callback;
	Timers[i].TimerID = CurID++;
	Timers[i].Periodic = Periodic;
	return Timers[i].TimerID;
}
/*
 *  Return the timer id of the timer that most recently expired
 *
 */
int TimerList::WhichExpired(unsigned int CurSeconds, unsigned int CurUSeconds)
{
	//We have the current time, find the timer entry whose difference in time is the smallest
	SecTime CurTime(CurSeconds, CurUSeconds);
	SecTime SmallestTime(0x7FFFFFFF, 0x7FFFFFFF);
	int CurIndex = -1;
	int i = 0;
	//Find the entry with the minimal time difference
	for (i = 0; i < MAX_NUM_TIMERS; i++)
	{
		if (Timers[i].TimerID == TIMER_INACTIVE) continue;
		//See if this timer's start time plus its timer value is less than the current time
		SecTime TimerExpireTime = Timers[i].TimerVal + Timers[i].StartTime;
		if (TimerExpireTime < CurTime)
		{
			if (TimerExpireTime < SmallestTime)
			{
				SmallestTime = TimerExpireTime;
				CurIndex = i;
			}
		}
	}
	//If we could not find a timer
	if (CurIndex == -1) return -1;
	//Otherwise, i is the timer found
	//Save the new current time for the timer
	Timers[CurIndex].StartTime = CurTime;
	return Timers[CurIndex].TimerID;
}
/*
 *  Remove a timer from the list.
 *
 */
bool TimerList::RemoveTimer(int TimerID)
{
	//Find the timer
	int TimerIndex = 0;
	if ((TimerIndex = GetIndexOfID(TimerID)) == TIMER_NOT_FOUND)
		return false;
	//Delete item, set the entry as inactive
	Timers[TimerIndex].TimerVal.Clear();
	Timers[TimerIndex].Callback = NULL;
	Timers[TimerIndex].TimerID = 0;	//Inactive flag
	return true;
}
/*
 *  Get the callback pointer for the TimerID.
 *
 */
void* TimerList::GetCallback(int TimerID)
{
	//Find the timer
	int TimerIndex = 0;
	if ((TimerIndex = GetIndexOfID(TimerID)) == TIMER_NOT_FOUND)
		return NULL;
	return Timers[TimerIndex].Callback;
}
/*
 *  Get whether the timer is periodic.
 *
 */
bool TimerList::IsPeriodic(int TimerID)
{
	//Find the timer
	int TimerIndex = 0;
	if ((TimerIndex = GetIndexOfID(TimerID)) == TIMER_NOT_FOUND)
		return false;
	return Timers[TimerIndex].Periodic;
}
/*
 *  The the smallest interval to the next timer expiration, returns the ID of that timer.
 *
 */
int TimerList::GetSmallestTimerInterval(unsigned int CurSeconds, unsigned int CurUSeconds, unsigned int *TimerSecOut, unsigned int *TimerUSecOut)
{
		if (TimerSecOut == NULL || TimerUSecOut == NULL) return -1;
	//We have the current time, find the timer entry whose difference in time is the smallest
	const SecTime CurTime(CurSeconds, CurUSeconds);
	const SecTime TimeZero(0,0);
	SecTime SmallestTime(0x7FFFFFFF, 0x7FFFFFFF);
	SecTime CurLowPriTime(-1000000, -1000000);
	int CurIndex = -1;
	int i = 0;
	//Find the entry with the minimal time difference
	for (i = 0; i < MAX_NUM_TIMERS; i++)
	{
		if (Timers[i].TimerID == TIMER_INACTIVE) continue;
		//Find the timer whose start time plus its timer time is the smallest
		SecTime TimerExpireTime = Timers[i].TimerVal + Timers[i].StartTime;
		if (TimerExpireTime - CurTime < TimeZero)
			continue;
		else
		{
			if (TimerExpireTime - CurTime < SmallestTime)
			{
				SmallestTime = TimerExpireTime - CurTime;
				CurIndex = i;
			}
		}
	}

	//If we could not find a timer
	if (CurIndex == -1)
	{
			*TimerSecOut = *TimerUSecOut = 0;
			return -1;
	}

	*TimerSecOut = (unsigned int)abs(SmallestTime.GetSeconds());
	*TimerUSecOut = (unsigned int)abs(SmallestTime.GetUSeconds());

	if (CurIndex >= 0 && CurIndex < MAX_NUM_TIMERS)
  {
		return Timers[CurIndex].TimerID;
  }

	return -1;	
}
/*
 *  Get the time remaining on a timer.
 *
 */
int TimerList::GetTimeRemaining(int TimerID, unsigned int CurSeconds, unsigned int CurUSeconds, unsigned int *TimerSecOut, unsigned int *TimerUSecOut)
{
	if (TimerSecOut == NULL || TimerUSecOut == NULL) return -1;
	//Find the timer
	int TimerIndex = 0;
	if ((TimerIndex = GetIndexOfID(TimerID)) == TIMER_NOT_FOUND)
		return -1;

	SecTime TimeRemaining(CurSeconds, CurUSeconds);
	TimeRemaining = Timers[TimerIndex].TimerVal - (TimeRemaining - Timers[TimerIndex].StartTime);
	*TimerSecOut = TimeRemaining.GetSeconds();
	*TimerUSecOut = TimeRemaining.GetUSeconds();
	return 0;
}
/*
 *  Reset a timer's start time.
 *
 */
void TimerList::TimerFired(int TimerID, unsigned int Seconds, unsigned int USeconds)
{
	//Find the timer
	int TimerIndex = 0;
	if ((TimerIndex = GetIndexOfID(TimerID)) == TIMER_NOT_FOUND)
		return;

	SecTime NewTime(Seconds, USeconds);
	Timers[TimerIndex].StartTime = NewTime;
}
/*
 *  Get the index of a TimerID.
 *
 */
int TimerList::GetIndexOfID(int ID)
{
	for (int i = 0; i < MAX_NUM_TIMERS; i++)
		if (Timers[i].TimerID == ID)
			return i;
	return -1;
}
/*
 *  Get whether the list is empty.
 *
 */
bool TimerList::IsEmpty()
{
	for (int i = 0; i < MAX_NUM_TIMERS; i++)
	{
		if (Timers[i].TimerID != TIMER_INACTIVE)
			return false;
	}
	return true;
}
/*
 *  Set the current running timer
 *
 */
void TimerList::SetRunningTimer(int TimerID)
{
	if (TimerID >=0 && TimerID < CurID)
		CurRunningTimer = TimerID;
}
