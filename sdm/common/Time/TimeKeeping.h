#ifndef TimeKeeping_h
#define TimeKeeping_h

#include "../sdmLib.h"
// Time keeping values
struct SDMLIB_API TimeKeepingRec
{
	int mode; // 0=unscaled, free running; 1=time scaled, free running; 2 = unscaled, paused, 3 = scaled, paused
	unsigned long gpsEpochTareSeconds;
	double ratio, uSecScale, nSecScale;
	long long tareCount, perfCountFreq;
};
extern struct SDMLIB_API TimeKeepingRec* timeKeeping;

extern SDMLIB_API void InitializeTimeKeeping();
extern SDMLIB_API struct SDMLIB_API TimeKeepingRec* GetTimeKeeping();

//
// Defined only for Linux
extern bool IsTimeInitialized();

#endif
