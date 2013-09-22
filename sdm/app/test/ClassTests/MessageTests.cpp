#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "../../../common/message/SDMData.h"
#include "../../../common/MessageManager/MessageManager.h"


const unsigned int MYPORT = 7453;
const unsigned int MYPORT2 = 9745;

void* Sender(void*);
void* Forwarder(void*);
bool DataCheck(const SDMData& Message);

int main (int argc, char** argv)
{
	pthread_t SenderThread, ForwarderThread;
	
	if (0 != pthread_create(&SenderThread, NULL, Sender, NULL))
	{
		printf("Could not create sender thread.\n");
		return -1;
	}
	
	if (0 != pthread_create(&ForwarderThread, NULL, Forwarder, NULL))
	{
		printf("Could not create forwarder thread.\n");
		return -1;
	}
	
	pthread_join(SenderThread, NULL);
	pthread_join(ForwarderThread, NULL);
	
	return 0;
}

void* Sender(void* ignored)
{
	MessageManager mm;
	SDMData dat;
	for (int i = 0; i < 256; i++)
		dat.msg[i] = 0x45;
	dat.length = 256;
	mm.Async_Init(MYPORT);
	char buf[BUFSIZE];
	
	SDMComponent_ID Receiver;
	Receiver.setAddress(inet_addr("127.0.0.1"));
	Receiver.setPort(MYPORT2);
	
	while(1)
	{
		if (mm.IsReady())
		{
			if (mm.GetMessage(buf) == SDM_Data)
			{
				SDMData received;
				received.Unmarshal(buf);
				
				printf("(Sender)  Received SDMData with timestamp %ld, %ld.\n",received.GetSecondsStamp(), received.GetSubSecondsStamp());
				fflush(NULL);
				if (!DataCheck(received))
				{
					printf("(Sender)  ERROR message doesn't match!\n");
				}
			}
			else
				printf("(Sender)  Unknown message received.\n");
			
		}
		// Send the message
		printf("(Sender)  Sending message...\n");
		dat.SendTo(Receiver);
		
		sleep(1);
	}
	
	return NULL;
}

void* Forwarder(void* ignored)
{
	MessageManager mm;
	SDMData dat;
	mm.Async_Init(MYPORT2);
	char buf[BUFSIZE];
	
	SDMComponent_ID Receiver;
	Receiver.setAddress(inet_addr("127.0.0.1"));
	Receiver.setPort(MYPORT);
	
	while(1)
	{
		if (mm.IsReady())
		{
			if (mm.GetMessage(buf) == SDM_Data)
			{
				SDMData received;
				long Length = received.Unmarshal(buf);
				
				printf("(Forwarder)  Received SDMData with timestamp %ld, %ld length is %ld.\n",received.GetSecondsStamp(), received.GetSubSecondsStamp(), Length);
				
				
				Length = received.Forward(Receiver);
				printf("(Forwarder)  Forwarding message length is %ld.\n", Length);
				fflush(NULL);
			}
			else
				printf("(Forwarder)  Unknown message received.\n");
		}
		sleep(1);
	}
	return NULL;
}

bool DataCheck(const SDMData& Message)
{
	for (int i = 0; i < 256; i++)
	{
		if (Message.msg[i] != 0x45)
			return false;
	}
	return true;
}



