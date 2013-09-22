// TimeKeepingWin32.cpp : Sets up the shared memory for use by timeKeeping methods.
//

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdio.h>

#include "TimeKeeping.h"

struct SDMLIB_API TimeKeepingRec* timeKeeping;
SDMLIB_API struct SDMLIB_API TimeKeepingRec* GetTimeKeeping(){ return timeKeeping; }

static short deltaMonthDays[] = {0,1,-1,0,0,1,1,2,3,3,4,4,5 };
static unsigned int GpsSeconds()
{
	// Leap seconds is set to 14, which was last updated on 31 Dec, 2005.  As of this date, Nov 15, 2007, the next 
	// update is unannounced.
	unsigned int seconds;
	unsigned int leapSeconds = 14;
	SYSTEMTIME systemTime;
	GetSystemTime( &systemTime );
	short yearNow = systemTime.wYear;
	short dYear = systemTime.wYear - 1980;
	short dMonth = systemTime.wMonth - 1; // January
	short dDay = systemTime.wDay - 6;
	short feb29=0;
	int thisYearLeaps;
	for( short year = 1980; year<= yearNow; year++ )
		if ( !(year%4) && ( (year%100) || !(year%400) ) )
		{
			thisYearLeaps = true;
			feb29++;
		}
		else
			thisYearLeaps = false;
	if ( thisYearLeaps && dMonth < 2 ) feb29--;
	unsigned int days = dYear*365 + dMonth*30 + deltaMonthDays[dMonth] + dDay + feb29;
	seconds = days*86400 + (systemTime.wHour*60 + systemTime.wMinute)*60 + systemTime.wSecond + leapSeconds;

	return seconds;
}

SDMLIB_API void InitializeTimeKeeping()
{
#define BUF_SIZE 256
	TCHAR szName[]=TEXT("TimeKeeping");

	HANDLE hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,   // read/write access
		FALSE,                 // do not inherit the name
		szName);               // name of mapping object 

	bool created = false;

	if (hMapFile == NULL) 
	{
//		printf("Couldn't OpenFileMapping; trying to CreateFileMapping\n");

		hMapFile = CreateFileMapping(
			INVALID_HANDLE_VALUE,    // use paging file
			NULL,                    // default security 
			PAGE_READWRITE,          // read/write access
			0,                       // max. object size 
			BUF_SIZE,                // buffer size  
			szName);                 // name of mapping object

		if (hMapFile == NULL || hMapFile == INVALID_HANDLE_VALUE) 
		{ 
			printf("Could not create file mapping object (%d).\n", 
				GetLastError());
			return;
		}
		created = true;
	} 

	timeKeeping = (struct SDMLIB_API TimeKeepingRec*) MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,                   
		0,                   
		BUF_SIZE );           

	if (timeKeeping == NULL) 
	{ 
		printf("Could not map view of file (%d)\n", 
			GetLastError()); 
		return;
	}

	if ( created )
	{
		timeKeeping->tareCount = 0;
		timeKeeping->mode=0; // 0=unsynced 1=unscaled, free running; 2=time scaled, free running;
				     // 3 = unscaled, paused, 4 = scaled, paused
		timeKeeping->gpsEpochTareSeconds=0;
		timeKeeping->ratio=1.0;
		timeKeeping->uSecScale=1.0;
		timeKeeping->nSecScale=1.0;
		timeKeeping->perfCountFreq=1000000000;
	
		LARGE_INTEGER perfCountFreq;
		QueryPerformanceFrequency( &perfCountFreq );
		timeKeeping->perfCountFreq = perfCountFreq.QuadPart;
		timeKeeping->uSecScale = 1000000.0 / (double)timeKeeping->perfCountFreq;
		// For future use, just to show that QueryPerformanceCounter resolves down to <1 ns
		timeKeeping->nSecScale = 1000000000.0 / (double)timeKeeping->perfCountFreq;
		LARGE_INTEGER count;
		QueryPerformanceCounter( &count );
		timeKeeping->tareCount = count.QuadPart;
		timeKeeping->gpsEpochTareSeconds = GpsSeconds();
	}
}
