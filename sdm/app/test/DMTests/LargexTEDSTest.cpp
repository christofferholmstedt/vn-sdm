#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>

#include "../../../common/message/SDMxTEDS.h"
#include "../../../common/message/SDMCancelxTEDS.h"
#include "../../../common/message/SDMComponent_ID.h"
#include "../../../common/MessageManager/MessageManager.h"
#include "xTEDSPoster.h"

const char* strFilename = "LargexTEDSSmallest.xml";

int main (int argc, char ** argv)
{
	if (argc < 4)
	{
		printf("Usage: %s TM-ADDR DM-ADDR PID\n",argv[0]);
		return 0;
	}
	SDMInit(argc, argv);
	
	printf("BUFSIZE=%d\n", BUFSIZE);
	printf("LARGE_MSG_BUFSIZE=%d\n", LARGE_MSG_BUFSIZE);

	xTEDSPoster::PostxTEDS( strFilename );

	printf("xTEDS message sent.\n");
	return 0;
}
