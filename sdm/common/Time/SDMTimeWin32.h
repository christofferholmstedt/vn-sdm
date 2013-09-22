#ifndef _SDM_TIME_WIN32_H_
#define _SDM_TIME_WIN32_H_
#include <windows.h>
#ifdef interface
# undef interface
#endif
#include "../sdmLib.h"
#include "SecTime.h"

extern SDMLIB_API void SDM_TimeInit();
extern SDMLIB_API void CALLBACK TimerFired(HWND hwnd, UINT uMsg, UINT idEvent, DWORD dwTime );
extern SDMLIB_API void SDM_GetTime(unsigned int *SecondsOut, unsigned int *USecondsOut);
extern SDMLIB_API void SDM_GetTime(SecTime &secTime);
extern SDMLIB_API void SDM_Sleep(unsigned int Seconds, unsigned int USeconds);
extern SDMLIB_API int SDM_CreateTimer(unsigned int Seconds, unsigned int USeconds, void(*Callback)(int), bool Periodic);
extern SDMLIB_API void SDM_DeleteTimer(int TimerID);
extern SDMLIB_API int SDM_ReadTimer(int TimerID, unsigned int *SecondsOut, unsigned int *USecondsOut);

extern SDMLIB_API void *MessageDispatch(void *args);


#endif
