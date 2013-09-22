#include "../../common/message/SDMxTEDS.h"
#include "../../common/message/SDMCancelxTEDS.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

long myPort = 0;

int main(int argc, char* argv[])
{
	char xteds[3*BUFSIZE];
	int fd = 0;
	SDMxTEDS xTEDS;
	SDMCancelxTEDS can;
	int value = 0;
	char cont = 0;
	char add[100];
	int result = 0;

	SDMInit(argc,argv);
	myPort = getPort();
	if(argc <= 4)
	{
		printf("./xTEDSPoster TM-ip DM-ip pid xTEDSfileName\n");
		return 0;
	}
	memset(xteds,0,3*BUFSIZE);
	fd = open(argv[4],O_RDONLY);
	if(fd == -1)
	{
		perror("File was unable to be opened! \n");
		return -1;
	}
	value = read(fd,xteds,3*BUFSIZE);
	xTEDS.source.setAddress(DataManager.getAddress());
	xTEDS.source.setPort(myPort);
	xTEDS.source.setSensorID(1);
	strncpy(xTEDS.xTEDS,xteds,value);
	printf("Would you like to include a usb address? (y or n): ");
	cont = getchar();
	if(cont == 'y')
	{
		printf("SPA Node path (x.x): ");
		fflush(NULL);
		scanf("%s",add);
		strcpy(xTEDS.SPA_node,add);
		printf("SPA Node path entered is %s\n",add);
	}
	result = xTEDS.Send();
	if(result < 0)
	{
		switch(result)
		{
			case -1:
				printf("Error: Send Error\n");
				return 0;
				break;
			case -2:
				printf("Error: Recv Error\n");
				return 0;
				break;
			case -3:
				printf("Error: Invalid Message\n");
				return 0;
				break;
			case -9:
				printf("Error: Unable to Register\n");
				return 0;
				break;
			case -10:
				printf("Error: Invalid xTEDS\n");
				return 0;
				break;
			default:
				printf("Error: Unknown error code %d\n",result);
				return 0;
				break;
		}
	}	
	sleep(5);
	can.source = xTEDS.source;
	result = 0;
	result = can.Send();
	if(result < 0)
	{
		switch(result)
		{
			case -1:
				printf("Error: Send Error\n");
				return 0;
				break;
			case -2:
				printf("Error: Recv Error\n");
				return 0;
				break;
			case -3:
				printf("Error: Invalid Message\n");
				return 0;
				break;
			case -11:
				printf("Error: Unknown xTEDS\n");
				return 0;
				break;
			case -14:
				printf("Error: Invalid Cancel\n");
				return 0;
				break;
			default:
				printf("Error: Unknown error code %d\n",result);
				return 0;
				break;
		}
	}
	return 0;
}
