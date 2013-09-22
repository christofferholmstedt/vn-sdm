#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../../../common/message/SDMReqReg.h"
#include "../../../common/message/SDMRegInfo.h"
#include "../../../common/MessageManager/MessageManager.h"


void SigHandler(int signum);
long myPort;

SDMReqReg Request;

bool Menu();

int main (int argc, char ** argv)
{
	MessageManager mm;
	char buf[BUFSIZE];
	SDMRegInfo reginfo_msg;
	unsigned char type;
	char InfoSource[40];
	char MessageID[40];
	SDMInit(argc, argv);
	signal(SIGINT,SigHandler);
	
	myPort = getPort();
	if (myPort == SDM_PM_NOT_AVAILABLE)
	{
		myPort = 4059;
	}
	mm.Async_Init(myPort);
	
	printf("-------------------SDMReqReg Tester-------------------\n");
	
	bool MenuFinished = false;
	
	while (!MenuFinished)
		MenuFinished = Menu();
		
	printf("Sending request...\n");
	Request.destination.setPort(myPort);
	Request.Send();
	
	int count = 1;
	bool Finished = false;
	if (Request.reply > SDM_REQREG_CURRENT)
	{
		printf("Press CTRL+C to quit.\n");
		sleep(1);
	}
	while (!Finished || Request.reply > SDM_REQREG_CURRENT)
	{
		type = mm.BlockGetMessage(buf);
		switch (type)
		{
			case SDM_RegInfo:
			{
				long length = reginfo_msg.Unmarshal(buf);
				if (length == SDM_NO_FURTHER_DATA_PROVIDER)
					Finished = true;
				else
				{
					reginfo_msg.source.IDToString(InfoSource, sizeof(InfoSource));
					reginfo_msg.msg_id.IDToString(MessageID, sizeof(MessageID));
					if (reginfo_msg.type == SDM_REGINFO_REGISTRATION)
						printf("(%d) RegInfo received (%s) registration (%s):\n",count++, InfoSource, MessageID);
					else if (reginfo_msg.type == SDM_REGINFO_CANCELLATION)
						printf("(%d) RegInfo received (%s) cancellation (%s):\n",count++, InfoSource, MessageID);
					else
						printf("(%d) RegInfo received (%s) unknown (%s):\n",count++, InfoSource, MessageID);
					printf("\t---Message Def Portion---\n");
					printf("%s\n\n",reginfo_msg.msg_def);
					printf("\t---xTEDS Portion---\n");
					printf("%s\n\n",reginfo_msg.xTEDS_section);
				}
				break;
			}
			default:
				printf("Unexpected message (%d).\n",type);
		}
	}
	printf("End of SDMRegInfo messages.\n");	
	printf("-------------------SDMReqReg Tester Finished-------------------\n");
	return 0;	
}

bool Menu()
{
	unsigned char Item;
	printf("(1) Change \"reply\" type\n");
	printf("(2) Change \"id\"\n");
	printf("(3) Change \"device\"\n");
	printf("(4) Change \"interface\"\n");
	printf("(5) Change \"item_name\"\n");
	printf("(6) Change \"quallist\"\n");
	printf("(7) Submit SDMReqReg\n");
	//Get the selection
	printf("->");
	scanf("%hhu",&	Item);
	
	switch(Item)
	{
		case 1:		//Input for reply
		{
			int ReplyType;
			printf("\nReply Type:\n");
			printf("(1)\tSDM_REQREG_CURRENT\n");
			printf("(2)\tSDM_REQREG_CURRENT_AND_FUTURE\n");
			printf("(3)\tSDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS\n");
			printf("->");
			scanf("%d",&ReplyType);
	
			switch (ReplyType)
			{
				case 1:
					Request.reply = SDM_REQREG_CURRENT;
					break;
				case 2:
					Request.reply = SDM_REQREG_CURRENT_AND_FUTURE;
					break;
				case 3:
					Request.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
					break;
				default:
					printf("Invalid choice, using SDM_REQREG_CURRENT.\n");
					break;
			}
		}
		break;
		case 2:		//Input for id
		{
			short Rid;
			printf("\nEnter the \"id\": ");
			scanf("%hd",&Rid);
			Request.id = Rid;
		}
		break;
		case 3:		//Input for device
		{
			printf("\nEnter the \"device\": ");
			scanf("%s", Request.device);
		}
		break;
		case 4:		//Input for interface
		{
			printf("\nEnter the \"interface\": ");
			scanf("%s", Request.interface);
		}
		break;
		case 5:		//Input for item_name
		{
			printf("\nEnter the \"item_name\": ");
			scanf("%s", Request.item_name);
		}
		break;
		case 6:		//Input for quallist
		{
			printf("\nEnter the \"quallist\": ");
			scanf("%s", Request.quallist);
		}
		break;
		case 7:		//Finish the message building
		{
			return true;
		}
		break;
		default:
		break;
	}
	//User did not finish
	return false;
}

void SigHandler(int signum)
{

	_exit(0);
}
