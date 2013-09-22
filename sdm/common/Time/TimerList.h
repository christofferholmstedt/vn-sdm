#ifndef _SDM_TIMER_LIST_H_
#define _SDM_TIMER_LIST_H_
#include "SecTime.h"

#define MAX_NUM_TIMERS 5
#define MAX_USEC_VALUE	1000000
#define TIMER_INACTIVE 0
#define TIMER_NOT_FOUND	-1

struct TimerListItem
{
	SecTime TimerVal;
	SecTime StartTime;
	int TimerID;
	bool Periodic;
	void *Callback;
	TimerListItem():TimerVal(),StartTime(),TimerID(0),Periodic(false),Callback(NULL)
	{ }
};

class SDMLIB_API TimerList
{
public:
	TimerList();
	int AddTimer(unsigned int Seconds, unsigned int USeconds, unsigned int CurSeconds, unsigned int CurUSeconds, void *Callback, bool Periodic);
	int AddTimer(unsigned int Seconds, unsigned int USeconds, unsigned int CurSeconds, unsigned int CurUSeconds, void *Callback, bool Periodic, unsigned int AssignedID);
	int WhichExpired(unsigned int CurSeconds, unsigned int CurUSeconds);
	bool RemoveTimer(int TimerID);
	void *GetCallback(int TimerID);
	bool IsPeriodic(int TimerID);
	void TimerFired(int TimerID, unsigned int Seconds, unsigned int USeconds);
	int GetSmallestTimerInterval(unsigned int CurSeconds, unsigned int CurUSeconds, unsigned int *TimerSecOut, unsigned int *TimerUSecOut);
	int GetTimeRemaining(int TimerID, unsigned int CurSeconds, unsigned int CurUSeconds, unsigned int *TimerSecOut, unsigned int *TimerUSecOut);
	bool IsEmpty();
	void SetRunningTimer(int TimerID);
	int GetRunningTimer() { return CurRunningTimer; }
private:
	int GetIndexOfID(int ID);
	int CurID;
	int CurRunningTimer;
	TimerListItem Timers[MAX_NUM_TIMERS];
};

#endif
