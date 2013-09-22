#include "../../common/message/SDMmessage.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/UDPcom.h"
#include "../../common/message_defs.h"
#include "../../common/MessageManager/MessageManager.h"
#include "../../common/message/SDMRegInfo.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

int sigcount = 0;
long my_port = 4030;

void SigHandler(int signum);
int main(int argc, char** argv)
{
	SDMInit(argc,argv);
	MessageManager mm;
	mm.Async_Init(my_port);
	signal(SIGINT,SigHandler);
	SDMReqReg request;
	SDMRegInfo info;
	char buf[BUFSIZE];
	long length;
	request.destination.setPort(my_port);
	request.id = 1;
	request.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
	printf("Sending ReqReg for Message_Count.\n");
	strcpy(request.item_name,"Message_Count");
	strcpy(request.quallist,"</>");
	request.Send();
	printf("Sending ReqReg for Enable_Logging.\n");
	strcpy(request.item_name,"Enable_Logging");
	request.Send();
	printf("Sending ReqReg for faults.\n");
	strcpy(request.item_name,"faultdata");
	request.Send();
	
	while(1)
	{
		if (mm.IsReady())
		{
			mm.GetMessage(buf,length);
			if (info.Unmarshal(buf) > 0)
			{
				printf("RegInfo received\n%s\n\n",info.msg_def);
			}
		}
		else
		{
			printf(".");
			sleep(1);
		}
	}
	
	
	request.reply = SDM_REQREG_CANCEL;
	request.Send();
	return 1;
}
void SigHandler(int signum)
{
	SDMReqReg req;
	req.reply = SDM_REQREG_CANCEL;
	req.destination.setPort(my_port);
	if (sigcount == 0)
	{
		printf("Cancelling ReqReg subscription for Message_Count.\n");
		strcpy(req.item_name,"Message_Count");
		strcpy(req.quallist,"</>");
		req.Send();
		sigcount++;
	}
	else if (sigcount == 1)
	{
		printf("Cancelling all ReqReg subscriptions.\n");
		req.Send();
		sigcount++;
	}
	else
		exit(0);
}
