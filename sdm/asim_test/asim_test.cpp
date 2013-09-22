#include "../common/asim/ASIM.h"
#include "../common/message_defs.h"

#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>

ASIM sensor;

void menu();
void init();
void reset();
void selftest();
void data();
void stream();
void poweron();
void powerdown();
void version();
void asim_command();
void xteds();
void cancel();
void timeattone();

void* Listener(void*);

int main(int argc,char** argv)
{
	pthread_t listener_thread;
	printf("ASIM Tester 0.1\n");
	
	if (argc == 3)
	{
		printf(" Opening %s",argv[1]);
		if (strcmp(argv[2], "debug") == 0)
		{
			sensor.SetDebug(4);
			printf(" in DEBUG mode.\n");
		}
		else
			printf("\n");
		if (!sensor.Open(argv[1]))
		{
			printf(" Error: Could not open device %s\n",argv[1]);
			_exit(0);
		}
	}	
	else if (argc == 2)
	{
		if (!sensor.Open(argv[1]))
		{
			printf(" Error: Could not open device %s\n",argv[1]);
			_exit(0);
		}
		printf(" Opening %s\n",argv[1]);
	}
	else
	{
		printf("Usage: %s device [debug]\n",argv[0]);
		_exit(0);
	}
	printf(" ASIM USB path: %s\n\n",sensor.USBLocation());
	pthread_create(&listener_thread,NULL,&Listener,NULL);
	usleep(50000);
	init();
	usleep(50000);
	version();
	
	while(1)
		menu();
	pthread_join(listener_thread,NULL);
}

void* Listener(void*)
{
	char buf[BUFSIZE];
	unsigned short length;
	int i;

	while(1)
	{
		switch(sensor.Read(length,(unsigned char*)buf,sizeof(buf)))
		{
		case ASIM_STATUS:
			if (buf[0]&0x80) //first bit is set for an error
			{
				printf("ASIM status ERROR: 0x%hhx\n",buf[0]);
				if(buf[0]&0x40) //illegal command bit
				{
					printf("Illegal or unrecognized command\n");
				}
				if(buf[0]&0x20) //self test failure bit
				{
					printf("Self Test failed\n");
				}
			}
			else
			{
				printf("ASIM status OK: 0x%hhx\n",buf[0]);
			}
			if(buf[0]&0x10) //mode bit
			{
				printf("ASIM mode: operational\n");
			}
			else
			{
				printf("ASIM mode: idle\n");
			}
			break;
		case ASIM_XTEDS:
			printf("\nASIM xTEDS:\n");
			for(i=0;i<length;++i)
			{
				if(isprint(buf[i])||isspace(buf[i]))
					printf("%c",buf[i]);
				else
					printf("\nERROR: contains non-prinatble character %x\n",buf[i]);
			}
			printf("\n");
			break;
		case ASIM_DATA:
			printf("\nASIM data message (%hu bytes): (%hhd, %hhd)\n",length,buf[0],buf[1]);
			for(i=0;i<length-2;++i)
			{
				printf("%hhx ",buf[2+i]);
			}
			printf("\n");
			break;
		case ASIM_VERSION:
			printf("\nASIM version %hhd\n",buf[0]);
			break;
		case ASIM_ERROR:
			printf("\nASIM read error\n");
			break;
		default:
			printf("\nUnexpected ASIM message\n");
		}
	}
}

void menu(void)
{
	int command;

	printf("1) Initialize\n");
	printf("2) Reset\n");
	printf("3) Self Test\n");
	printf("4) Data request\n");
	printf("5) Stream request\n");
	printf("6) Power On\n");
	printf("7) Power Down\n");
	printf("8) Version request\n");
	printf("9) Command\n");
	printf("10) xTEDS request\n");
	printf("11) Time at Tone\n");
	printf("12) Cancel stream\n");
	printf("13) Quit\n");
	printf("command: ");
	if(scanf("%d",&command)==0)
	{
		getchar();
	}
	switch(command)
	{
	case 1:
		init();
		break;
	case 2:
		reset();
		break;
	case 3:
		selftest();
		break;
	case 4:
		data();
		break;
	case 5:
		stream();
		break;
	case 6:
		poweron();
		break;
	case 7:
		powerdown();
		break;
	case 8:
		version();
		break;
	case 9:
		asim_command();
		break;
	case 10:
		xteds();
		break;
	case 11:
		timeattone();
		break;
	case 12:
		cancel();
		break;
	case 13:
		_exit(0);
	default:
		printf("Bad Command\n");
	}	
}

void init()
{
	printf("Initializing\n");
	if (!sensor.Initialize())
		printf("Error sending initialize message\n");
}

void reset()
{
	printf("Reseting\n");
	if (!sensor.Reset())
		printf("Error sending reset message\n");
}

void selftest()
{
	printf("Self Testing\n");
	if (!sensor.SelfTest())
		printf("Error sending self test message\n");
}

void data()
{
	unsigned char msg_id;
	unsigned char interface_id;
	printf("Message id: ");
	scanf("%hhd",&msg_id);
	printf("Interface id: ");
	scanf("%hhd",&interface_id);
	printf("Requesting Data message id %hhd in interface %hhd\n",msg_id,interface_id);
	if (sensor.ReqData(interface_id,msg_id))
		printf("Error sending data request message\n");
}

void stream()
{
	unsigned char msg_id;
	unsigned char interface_id;
	unsigned long count;
	printf("Message id: ");
	scanf("%hhd",&msg_id);
	printf("Interface id: ");
	scanf("%hhd",&interface_id);
	printf("Message count: ");
	scanf("%ld",&count);
	printf("Requesting Data message id %hhd in interface %hhd, %ld times\n",msg_id,interface_id,count);
	if (!sensor.ReqStream(interface_id,msg_id,count))
		printf("Error sending stream request message\n");
}

void poweron()
{
	printf("Power On\n");
	if (!sensor.PowerOn())
		printf("Error sending power on message\n");
}

void powerdown()
{
	printf("Power Down\n");
	if (!sensor.PowerDown())
		printf("Error sending power down message\n");
}

void version()
{
	printf("Version request\n");
	if (!sensor.ReqVersion())
		printf("Error sending version request message\n");
}

void asim_command()
{
	printf("Command\n");
	
	unsigned char msg_id;
	unsigned char interface_id;
	unsigned short length;
	unsigned char buf[64];
	printf("Interface id: ");
	scanf("%hhu",&interface_id);
	printf("Message id: ");
	scanf("%hhu",&msg_id);
	printf("Command length: ");
	scanf("%hu",&length);
	if (length > 59)
	{
		printf("Invalid length.\n");
		return;
	}
	for (unsigned short i = 0; i < length; i++)
	{
		printf("Byte %hu: ",i);
		scanf("%hhu",buf+i);
	}
	if (!sensor.Command(interface_id, msg_id, length, buf))
		printf("Error sending command message\n");
}

void xteds()
{
	printf("xTEDS request\n");
	sensor.ReqxTEDS();
}

void timeattone()
{
	printf("Time at Tone\n");
	long sec, usec;
	
	printf("Seconds: ");
	scanf("%ld",&sec);
	printf("USeconds: ");
	scanf("%ld",&usec);
	printf("Time at tone: seconds %ld useconds %ld\n",sec,usec);
 	if (!sensor.TimeAtTone(sec,usec))
		printf("Error sending time at tone message\n");
}

void cancel()
{
	unsigned char msg_id;
	unsigned char interface_id;
	printf("Message id: ");
	scanf("%hhd",&msg_id);
	printf("Interface id: ");
	scanf("%hhd",&interface_id);
	printf("Cancel message id %hhd in interface %hhd\n",msg_id, interface_id);
	if (!sensor.Cancel(interface_id,msg_id))
		printf("Error sending cancel message\n");
}
