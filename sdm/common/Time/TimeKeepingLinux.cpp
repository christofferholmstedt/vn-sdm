// TimeKeepingLinux.cpp : Sets up the shared memory for use by timeKeeping methods.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#ifndef __VXWORKS__
#include <sys/ipc.h>
#include <sys/shm.h>
#else
#include <sys/mman.h>
#include <unistd.h>
#include <fcntl.h>
#endif
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <string.h>

#include "TimeKeeping.h"

struct SDMLIB_API TimeKeepingRec* timeKeeping;
SDMLIB_API struct SDMLIB_API TimeKeepingRec* GetTimeKeeping(){ return timeKeeping; }

static bool g_bTimeInitialized = false;
bool IsTimeInitialized() { return g_bTimeInitialized; }

static unsigned int GpsSeconds()
{
	// Leap seconds is set to 14, which was last updated on 31 Dec, 2005.  As of this date, Nov 15, 2007, the next 
	// update is unannounced.
	unsigned int seconds;
	unsigned int leapSeconds = 14;

	struct tm gpsEpoch;
	memset(&gpsEpoch,0,sizeof(gpsEpoch));
	gpsEpoch.tm_year = 80;
	gpsEpoch.tm_mday = 6;
	time_t gpsTime = mktime(&gpsEpoch);
	time_t now;
	time(&now);
	seconds = now - gpsTime + leapSeconds;

	return seconds;
}

SDMLIB_API void InitializeTimeKeeping()
{
#define SHM_KEY 0x43258902
#define SHM_SIZE 256  

  void* pAddr;
  bool  bInitialize = false;
  int   shmid;


#ifndef __VXWORKS__  
  key_t key = (key_t)SHM_KEY;

  if((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT | IPC_EXCL)) == -1)
    {
      if((shmid = shmget(key, SHM_SIZE, 0644 | IPC_CREAT)) == -1)
	{
	  perror("shmget");
	  return;
	}

      bInitialize = false;
    }
  else
    {
      bInitialize = true;
    }
  
  if((pAddr=shmat(shmid, (void*)0, 0)) == (void*)-1)
    {
      perror("shmat");
      return;
    }
#else
	if((shmid = shm_open("/timeKeepingShm", O_CREAT | O_RDWR , S_IRUSR | S_IWUSR)) < 0)
	{
		if((shmid = shm_open("/timeKeepingShm", O_RDWR, S_IRUSR | S_IWUSR)) < 0)
		{
			printf("Error creating shared memory for time keeping\n");
			return;
		}
		bInitialize = false;
	}
	else
	{
		bInitialize = true;
	}
	
	//set object size

	if (ftruncate(shmid, 0x40) == -1)
	{
		printf("Error setting shm size\n");
		return;
	}
	pAddr = mmap(0, 0x40, PROT_READ | PROT_WRITE, MAP_SHARED, shmid, 0);
	if (pAddr == (void*)MAP_FAILED)
	{
		printf("Error mapping shm\n");
		return;
	}	
	close(shmid);
#endif
  timeKeeping = (struct SDMLIB_API TimeKeepingRec*)pAddr;

  if(bInitialize)
    {
        timeKeeping->tareCount = 0;
        timeKeeping->mode=0; // 0=unsynced 1=unscaled, free running; 2=time scaled, free running;
        // 3 = unscaled, paused, 4 = scaled, paused
        timeKeeping->gpsEpochTareSeconds=0;
        timeKeeping->ratio=1.0;
        timeKeeping->uSecScale=1.0;
        timeKeeping->nSecScale=1.0;
        timeKeeping->perfCountFreq=1000000000;

#ifdef __VXWORKS__
        struct timespec tv;
        clock_gettime(CLOCK_REALTIME, &tv);
        timeKeeping->tareCount = tv.tv_sec * 1000000LL + tv.tv_nsec/1000;
#else
        struct timeval tv;
        gettimeofday(&tv, NULL);
        timeKeeping->tareCount = tv.tv_sec * 1000000LL + tv.tv_usec;
#endif
        timeKeeping->perfCountFreq = 1000000;
        timeKeeping->uSecScale = 1.0;
        timeKeeping->nSecScale = 1000.0;

        timeKeeping->gpsEpochTareSeconds = GpsSeconds();
    }
  g_bTimeInitialized = true;
}
