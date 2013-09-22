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

long Port = 4058;
pthread_mutex_t PortMutex = PTHREAD_MUTEX_INITIALIZER;
//const char *InputFilename = "LargexTEDSSmaller.xml";
const int MAX_READ_SIZE = 7500;
void *xTEDSSender(void *InputFilename);

int main (int argc, char ** argv)
{
	if (argc < 4)
	{
		printf("Usage: %s TM-ADDR DM-ADDR PID\n",argv[0]);
		return 0;
	}
	SDMInit(argc, argv);
	pthread_t t1, t2, t3;
	
	pthread_create(&t1, NULL, xTEDSSender, strdup("Battery.xml"));
	pthread_create(&t2, NULL, xTEDSSender, strdup("LargexTEDSSmaller.xml"));
	pthread_create(&t3, NULL, xTEDSSender, strdup("SolarArray.xml"));
	
	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	
	return 0;
}

void *xTEDSSender(void *Arg)
{
	char *InputFilename = (char*)Arg;
	MessageManager mm;
	pthread_mutex_lock(&PortMutex);
	long myPort = Port++;
	pthread_mutex_unlock(&PortMutex);
	
	mm.Async_Init(myPort);
	int FileFD;
	printf("Reading %s...",InputFilename);
	if ((FileFD = open(InputFilename, O_RDONLY)) < 0)
	{
		perror("Error opening input file\n");
		return 0;
	}
	//
	// Read in the entire file
	char FileBuf[65535];
	int FileLength = read(FileFD, FileBuf, sizeof(FileBuf));
	if (FileLength < 0)
	{
		perror("Error reading file.\n");
		return 0;
	}
	printf("File Read.\n");
	//
	// Figure out how many segments to send
	int NumSegments = static_cast<int>((FileLength % MAX_READ_SIZE) == 0 ? FileLength/static_cast<double>(MAX_READ_SIZE) : FileLength/static_cast<double>(MAX_READ_SIZE)+1);
	SDMxTEDS xTEDSMessage;
	xTEDSMessage.source.setPort(myPort);
	xTEDSMessage.source.setSensorID(1);
	for (int i = 0; i < NumSegments; i++)
	{
		//Set the segment numbers in the xTEDS message
		xTEDSMessage.xTEDS[0] = static_cast<unsigned char>(i);
		xTEDSMessage.xTEDS[1] = static_cast<unsigned char>(NumSegments);
		
		//Read in a portion of the xTEDS message
		memset(xTEDSMessage.xTEDS+2, 0, sizeof(xTEDSMessage.xTEDS)-2);
		strncpy(xTEDSMessage.xTEDS+2, FileBuf + i*MAX_READ_SIZE, MAX_READ_SIZE);
		printf("%ld - Sending segment %hhd of %hhd\n",myPort, xTEDSMessage.xTEDS[0], xTEDSMessage.xTEDS[1]);
		xTEDSMessage.Send();
		printf("%ld - Sent.\n",myPort);
		//
		//Wait for an ACK
		bool ACKRecd = false;
		char MessageBuf[BUFSIZE];
		while (!ACKRecd)
		{
			usleep(1000);
			if (mm.GetMessage(MessageBuf) == SDM_ACK)
			{
				printf("%ld - ACK\n", myPort);
				ACKRecd = true;
			}
			else
				printf(".");
			fflush(NULL);
		}
	}
	
	printf("%ld - xTEDS sent.\n",myPort);
	free (Arg);
	usleep(200000);
	//Send a cancel message
	SDMCancelxTEDS cancel;
	cancel.source.setPort(myPort);
	cancel.source.setSensorID(1);
	cancel.Send();

  close(FileFD);
	
	return NULL;
}
