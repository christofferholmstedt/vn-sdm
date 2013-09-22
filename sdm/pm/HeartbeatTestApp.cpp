#include "../common/message/SDMHeartbeat.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char** argv)
{
	SDMInit(argc, argv);
	
	printf("Heartbeat test app running (%d).\n", getpid());
	
	SendHeartbeat();
	
	while (1)
	{
		sleep(1);
	}
	return 0;
}
