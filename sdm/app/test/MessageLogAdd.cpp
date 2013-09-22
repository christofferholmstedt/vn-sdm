#include "../../common/message/SDMData.h"
#include "../../common/message/SDMService.h"
#include "../../common/message/SDMConsume.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMCommand.h"
#include "../../common/message/SDMComponent_ID.h"
#include "../../common/MessageManipulator/MessageManipulator.h"
#include "../../common/MessageManager/MessageManager.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


#define DATA_PROVIDER		1

long my_port;
SDMComponent_ID data_provider;
SDMComponent_ID service_provider;
unsigned char service_msg = 0;

MessageManipulator data_manipulator;

void RegInfoHandler(SDMRegInfo& info)
{
	SDMCommand command;
	SDMReqReg req_reg;
	char type;
	SDMComponent_ID comp_id;
	char ip_address[16];
	int sensor_id;
	int port;

	//Set the port we will be receiving on
	command.destination.setPort(my_port);
	//copy the sensor id into the consume message
	command.source=info.source;
	//copy the msg id into the consume message
	command.command_id=info.msg_id;
	
	if (info.id != DATA_PROVIDER)
		return;

	if (info.source.getAddress() == TaskManager.getAddress() && info.source.getPort() == TaskManager.getPort())
	{
		printf("Send log command to TM? (y/n) ");
		type = getchar();
		getchar();
		if (type == 'n' || type == 'N')
			return;
	}
	else if (info.source.getAddress() == DataManager.getAddress() && info.source.getPort() == DataManager.getPort())
	{
		printf("Send log command to DM? (y/n) ");
		type = getchar();
		getchar();
		if (type == 'n' || type == 'N')
			return;
	}
	else if (info.source.getPort() == PORT_SM)
	{
		printf("Send log command to SM? (y/n) ");
		type = getchar();
		getchar();
		if (type == 'n' || type == 'N')
			return;
	}
	else if (info.source.getPort() == PORT_PM)
	{
		printf("Send log command to PM? (y/n) ");
		type = getchar();
		getchar();
		if (type == 'n' || type == 'N')
			return;
	}
	
	printf("Log for a specific component id? (y/n) ");
	type = getchar();
	getchar();
	if (type == 'y' || type == 'Y')
	{
		printf("Enter the IP address (number-dot notation): ");
		scanf("%s", ip_address);
		getchar();
		printf("Enter the port: ");
		scanf("%d", &port);
		getchar();
		printf("Enter the sensor id: ");
		scanf("%d", &sensor_id);
		getchar();
		if (!strcmp(ip_address,"0"))
			comp_id.setAddress(0);
		else
			comp_id.setAddress(inet_addr(ip_address));
		comp_id.setPort(port);
		comp_id.setSensorID(sensor_id);
	}
	else
	{
		comp_id.setAddress(0);
		comp_id.setPort(0);
		comp_id.setSensorID(0);
	}

	data_provider = info.source;
	data_manipulator.setMsgDef(info.msg_def);
	command.length = 12;
	printf("\n\n%s\n",info.msg_def);
	printf("\nEnter the character representation of the message types to log.\n");
	printf("Example: typing \"tu[ENTER]\" will add both SDMData and SDMSubreqst messages.\n");
	printf("--> ");
	while ((type = getchar()) != '\n')
	{
		switch (type)
		{
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
			case 'g':
			case 'h':
			case 'i':
			case 'j':
			case 'k':
			case 'l':
			case 'm':
			case 'n':
			case 'o':
			case 'p':
			case 'q':
			case 'r':
			case 's':
			case 't':
			case 'u':
			case 'v':
			case 'w':
			case 'x':
			case 'y':
			case 'z':
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
			case 'G':
			case 'H':
			case 'I':
			case 'J':
				PUT_UCHAR(&command.data[0], type);
				comp_id.Marshal(command.data, 1);
				command.Send();
				printf("     Command message sent for message type '%c'.\n",type);
				break;
			case '0':		//Log everything
				PUT_UCHAR(&command.data[0], '\0');
				comp_id.Marshal(command.data, 1);
				command.Send();
				printf("     Command message sent to log all messages.\n");
				break;
		}
		usleep(2000);
	}
}

int main(int argc,char** argv)
{
	MessageManager mm;
	SDMData dat;
	SDMRegInfo info;
	SDMReqReg req_reg;
	char buf[BUFSIZE];
	long length;
	bool infosDone = false;
	int numRecd = 0;

	//initialize consumer
	SDMInit(argc,argv);
	my_port = getPort();
	mm.Async_Init(my_port);

	printf("Consumer listening on port %ld\n",my_port);

	while(!infosDone)
	{
		if (mm.IsReady())
		{
			switch(mm.GetMessage(buf,length))
			{
			case SDM_RegInfo:
				if(info.Unmarshal(buf)!=SDM_NO_FURTHER_DATA_PROVIDER)
				{
					numRecd++;
					RegInfoHandler(info);
				}
				else
				{
					if (numRecd == 0)
					{
						printf("No log messages found.\n");
						fflush(NULL);
					}
					infosDone = true;
				}
				break;
			default:
				printf("Unexpected message\n");
			}
		}
		else
		{	//check for data and service providers
			if(data_provider.getSensorID() == 0)
			{
				//request info on integer data providers
				//Set variable name
				strcpy(req_reg.item_name,"Enable_Logging");
				//Set the quallist can be empty
				strcpy(req_reg.quallist,"< >");
				req_reg.reply = SDM_REQREG_CURRENT_AND_FUTURE;
				req_reg.destination.setPort(my_port);
				req_reg.id = DATA_PROVIDER;
				req_reg.Send();
				printf("Searching for log command...\n");
				sleep(2);
			}
			usleep(1000);
		}
	}
}
