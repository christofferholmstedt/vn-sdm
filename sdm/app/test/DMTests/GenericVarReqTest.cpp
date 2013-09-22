#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../../../common/message/SDMVarReq.h"
#include "../../../common/message/SDMVarInfo.h"
#include "../../../common/MessageManager/MessageManager.h"


void SigHandler(int signum);
long myPort;

SDMVarReq Request;

bool Menu();

int main (int argc, char ** argv)
{
	MessageManager mm;
	char buf[BUFSIZE];
	SDMVarInfo varinfo_msg;
	unsigned char type;
	SDMInit(argc, argv);
	signal(SIGINT,SigHandler);
	char InfoSource[40];
	
	myPort = getPort();
	if (myPort == SDM_PM_NOT_AVAILABLE)
	{
		myPort = 4059;
	}
	mm.Async_Init(myPort);
	
	printf("-------------------SDMVarReq Tester-------------------\n");
	
	bool MenuFinished = false;
	
	while (!MenuFinished)
		MenuFinished = Menu();
		
	printf("Sending request...\n");
	Request.destination.setPort(myPort);
	Request.Send();
	
	int count = 1;
	bool Finished = false;
	if (Request.reply > SDM_VARREQ_CURRENT)
	{
		printf("Press CTRL+C to quit.\n");
		sleep(1);
	}
	while (!Finished || Request.reply > SDM_VARREQ_CURRENT)
	{
		type = mm.BlockGetMessage(buf);
		switch (type)
		{
			case SDM_VarInfo:
			{
				long length = varinfo_msg.Unmarshal(buf);
				if (length == SDM_NO_FURTHER_DATA_PROVIDER)
					Finished = true;
				else
				{
					varinfo_msg.source.IDToString(InfoSource, sizeof(InfoSource));
					printf("(%d) VarInfo received (%s):\n",count++, InfoSource);
					printf("\t---xTEDS Portion---\n");
					printf("%s\n\n",varinfo_msg.var_xTEDS);
				}
				break;
			}
			default:
				printf("Unexpected message (%d).\n",type);
		}
	}
	printf("End of SDMVarInfo messages.\n");	
	printf("-------------------SDMVarReq Tester Finished-------------------\n");
	return 0;	
}

bool Menu()
{
	unsigned char Item;
	printf("(1) Change \"reply\"\n");
	printf("(2) Change \"msg_id\"\n");
	printf("(3) Change \"id\"\n");
	printf("(4) Change \"variable\"\n");
	printf("(5) Submit SDMVarReq\n");
	//Get the selection
	printf("->");
	scanf("%hhu",&	Item);
	
	switch(Item)
	{
		case 1:		//Input for reply
		{
			int ReplyType;
			printf("\nReply Type:\n");
			printf("(1)\tSDM_VARREQ_CURRENT\n");
			printf("(2)\tSDM_VARREQ_CURRENT_AND_FUTURE\n");
			printf("(3)\tSDM_VARREQ_CANCEL\n");
			printf("->");
			scanf("%d",&ReplyType);
	
			switch (ReplyType)
			{
				case 1:
					Request.reply = SDM_VARREQ_CURRENT;
					break;
				case 2:
					Request.reply = SDM_VARREQ_CURRENT_AND_FUTURE;
					break;
				case 3:
					Request.reply = SDM_VARREQ_CANCEL;
					break;
				default:
					printf("Invalid choice, using SDM_VARREQ_CURRENT.\n");
					break;
			}
		}
		break;
		case 2:		//Input for msg_id
		{
			SDMMessage_ID MessageID;
			unsigned char ID;
			printf("\nEnter the \"msg_id\" interface id: ");
			scanf("%hhu",&ID);
			MessageID.setInterface(ID);
			
			Request.msg_id = MessageID;
		}
		break;
		case 3:		//Input for device
		{
			printf("\nEnter the \"id\": ");
			scanf("%hd", &Request.id);
		}
		break;
		case 4:		//Input for interface
		{
			printf("\nEnter the \"variable\": ");
			scanf("%s", Request.variable);
		}
		break;
		case 5:		//Finish the message building
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
