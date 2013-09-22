#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "../../../common/Time/SDMTime.h"

const unsigned int TimeValsSec[] = { 1, 8, 7, 3 };
const unsigned int TimeValsUSec [] = { 0, 20000, 86994, 238821};
unsigned int TimeValIndex = 0;
pthread_mutex_t TimeValMutex = PTHREAD_MUTEX_INITIALIZER;

void *ThreadTimer(void *args);

void CallBack (int Timer)
{
	printf("Callback called by timer %d\n",Timer);
}

int main (int argc, char ** argv)
{
	printf("-------------------------SDM Time Test Started-------------------------\n");
	printf("SDM_GetTime()  ");
	unsigned int Sec, USec;
	SDM_GetTime(&Sec, &USec);
	printf("sec=%u, usec=%u passed.\n",Sec,USec);
	printf("SDM_GetTime(BadInput)  ");
	SDM_GetTime(NULL, NULL);
	printf("passed.\n");
	
	SDM_TimeInit();
	
	printf("\n\n");
	printf("SDMSleep(1, 500)  ");  fflush(NULL);
	SDM_Sleep(1, 500);
	printf("passed.\n");
	
	pthread_t t1, t2, t3, t4;
	pthread_create(&t1, NULL, ThreadTimer, NULL);
	pthread_create(&t2, NULL, ThreadTimer, NULL);
	pthread_create(&t3, NULL, ThreadTimer, NULL);
	pthread_create(&t4, NULL, ThreadTimer, NULL);
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	
	printf("-------------------------SDM Time Test Finished-------------------------\n");
	
	return 0;
}

void *ThreadTimer(void *arg)
{
	unsigned int Sec, USec, Index, t1, t2;
	pthread_mutex_lock(&TimeValMutex);
	Index = TimeValIndex++;
	Sec = TimeValsSec[Index];
	USec = TimeValsUSec[Index++];
	pthread_mutex_unlock(&TimeValMutex);
	int TimerID;
	printf("%u - SDM_CreateTimer(%u seconds, %u useconds)\n",Index, Sec, USec);
	if ((TimerID=SDM_CreateTimer(Sec, USec, &CallBack, true)) < 0)
		printf("failed.\n");
	
	bool Finished = false;
	int count = 0;
	while (!Finished)
	{
		SDM_Sleep(1, 0);
		count++;
		SDM_ReadTimer(TimerID, &t1, &t2);
		printf("%u - Current Timer remaining is %u, %u\n",TimerID,t1,t2);
		if (count == 10)
		{
			printf("%u - Deleting Timer.\n",Index);
			SDM_DeleteTimer(TimerID);
			printf("%u - Creating Timer.\n",Index);
			if ((TimerID=SDM_CreateTimer(Sec, USec, &CallBack, true)) < 0)
				printf("failed.\n");
		}
		if (count == 20)
			Finished = true;
	}
	printf("%u done.\n",Index);
	return NULL;
}
