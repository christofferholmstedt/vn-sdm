#ifndef _SDM_TIME_LINUX_H_
#define _SDM_TIME_LINUX_H_

#include "SecTime.h"

void *TimerHandler(void *args);
void SDM_TimeInit();
void SDM_GetTime(unsigned int *SecondsOut, unsigned int *USecondsOut);
void SDM_GetTime(SecTime &secTime);
void SDM_Sleep(unsigned int Seconds, unsigned int USeconds);
int SDM_CreateTimer(unsigned int Seconds, unsigned int USeconds, void(*Callback)(int), bool Periodic);
void SDM_DeleteTimer(int TimerID);
int SDM_ReadTimer(int TimerID, unsigned int *SecondsOut, unsigned int *USecondsOut);
#ifdef __VXWORKS__
void usleep(int microseconds);
#endif

#endif
