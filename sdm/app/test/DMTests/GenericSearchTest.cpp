#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <ctype.h>
#include "../../../common/message/SDMSearch.h"
#include "../../../common/message/SDMSearchReply.h"
#include "../../../common/MessageManager/MessageManager.h"


void SigHandler(int signum);
long myPort;

SDMSearch Request;

bool Menu();

int main (int argc, char ** argv)
{
	MessageManager mm;
	char buf[BUFSIZE];
	SDMSearchReply ReplyMsg;
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
	
	printf("-------------------SDMSearch Tester-------------------\n");
	
	bool MenuFinished = false;
	
	while (!MenuFinished)
		MenuFinished = Menu();
		
	printf("Sending request...\n");
	Request.destination.setPort(myPort);
	Request.Send();
	
	int count = 1;
	bool Finished = false;
	if (Request.reply > SDM_SEARCH_CURRENT)
	{
		printf("Press CTRL+C to quit.\n");
		sleep(1);
	}
	while (!Finished || Request.reply > SDM_SEARCH_CURRENT)
	{
		type = mm.BlockGetMessage(buf);
		switch (type)
		{
			case SDM_SearchReply:
			{
				long length = ReplyMsg.Unmarshal(buf);
				if (length == SDM_NO_FURTHER_DATA_PROVIDER)
					Finished = true;
				else
				{
					ReplyMsg.source.IDToString(InfoSource, sizeof(InfoSource));
					printf("(%d) SearchReply received (%s):\n",count++, InfoSource);
					
					printf("\t---Captured Text Portion:---\n");
					
					bool nullFound = false;
					for (unsigned int i = 0; i < sizeof(ReplyMsg.captured_matches); i++)
					{
						if (isprint(ReplyMsg.captured_matches[i]))
						{
							printf("%c", ReplyMsg.captured_matches[i]);
							nullFound = false;
						}
						else if (ReplyMsg.captured_matches[i] == '\0')
						{
							printf("0");
							if (nullFound)
							{
								printf("\n");
								break;
							}
							nullFound = true;
						}
						
					}
				}
				break;
			}
			default:
				printf("Unexpected message (%d).\n",type);
		}
	}
	printf("End of SDMSearch messages.\n");	
	printf("-------------------SDMSearch Tester Finished-------------------\n");
	return 0;	
}

bool Menu()
{
	unsigned char Item;
	printf("(1) Change \"reply\" type\n");
	printf("(2) Change \"id\"\n");
	printf("(3) Change \"reg_expr\"\n");
	printf("(4) Submit SDMSearch\n");
	//Get the selection
	printf("->");
	scanf("%hhu",&	Item);
	
	switch(Item)
	{
		case 1:		//Input for reply
		{
			int ReplyType;
			printf("\nReply Type:\n");
			printf("(1)\tSDM_SEARCH_CURRENT\n");
			printf("(2)\tSDM_SEARCH_CURRENT_AND_FUTURE\n");
			printf("(3)\tSDM_SEARCH_CANCEL\n");
			printf("->");
			scanf("%d",&ReplyType);
	
			switch (ReplyType)
			{
				case 1:
					Request.reply = SDM_SEARCH_CURRENT;
					break;
				case 2:
					Request.reply = SDM_SEARCH_CURRENT_AND_FUTURE;
					break;
				case 3:
					Request.reply = SDM_SEARCH_CANCEL;
					break;
				default:
					printf("Invalid choice, using SDM_SEARCH_CURRENT.\n");
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
		case 3:		//Input for reg_expr
		{
			printf("\nEnter the \"reg_expr\": ");
			scanf("%s", Request.reg_expr);
		}
		break;

		break;
		case 4:		//Finish the message building
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
