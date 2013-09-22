#include "../../common/message/SDMData.h"
#include "../../common/message/SDMService.h"
#include "../../common/message/SDMConsume.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMCommand.h"
#include "../../common/MessageManipulator/MessageManipulator.h"
#include "../../common/MessageManager/MessageManager.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define DATA_PROVIDER		1

long my_port;
SDMComponent_ID data_provider;
SDMComponent_ID service_provider;
unsigned char service_msg = 0;
char msg_types[23] = "qruvtabcdilnomxyzABCDH";

MessageManipulator data_manipulator;

void RegInfoHandler(SDMRegInfo& info)
{
	SDMCommand command;
	SDMReqReg req_reg;
	char type;

	//Set the port we will be receiving on
	command.destination.setPort(my_port);
	//copy the sensor id into the consume message
	command.source=info.source;
	//copy the msg id into the consume message
	command.command_id=info.msg_id;
	if (info.id != DATA_PROVIDER)
		return;

	if (info.source.getPort() == PORT_TM)
	{
		printf("Send log command to TM? (y/n) ");
		type = getchar();
		getchar();
		if (type == 'n' || type == 'N')
			return;
	}
	else if (info.source.getPort() == PORT_DM)
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

	data_provider = info.source;
	data_manipulator.setMsgDef(info.msg_def);
	command.length = 1;
	for (int i = 0; i < 22; i++)
	{
		PUT_UCHAR(&command.data[0], msg_types[i]);
		usleep(100);
		printf("Enable logging command sent for message type %c.\n",msg_types[i]);
		command.Send();
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
