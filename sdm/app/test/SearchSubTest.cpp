#include "../../common/message/SDMSearch.h"
#include "../../common/message/SDMSearchReply.h"
#include "../../common/MessageManager/MessageManager.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#define INTERFACE_SEARCH_ID	1
#define DEVICE_SEARCH_ID	2
#define APPLICATION_SEARCH_ID	3

long my_port = 4020;
int sigint_count = 0;

void SigHandler(int signum);
int main(int argc,char** argv)
{
	SDMSearch s;
	SDMSearchReply reply;
	int result = 0;
	char buf[BUFSIZE];
	long length;
	MessageManager mm;
	int cur = 0;
	int count = 0;
	
	signal(SIGINT,SigHandler);
	SDMInit(argc,argv);
	my_port = getPort();
	if(my_port == SDM_PM_NOT_AVAILABLE)
	{
		printf("Unable to get a port from the Process Manager!\n");
		exit(0);
	}
	mm.Async_Init(my_port);
	sleep(1);
	s.destination.setPort(my_port);
	s.destination.setAddress(DataManager.getAddress());  //This application must be run on the same node as the DM
	s.id = INTERFACE_SEARCH_ID;
	s.reply = SDM_SEARCH_CURRENT_AND_FUTURE;
	
	strcpy(s.reg_expr,".*?<Interface name=\"(.*?)\".*?>.*?<Interface name=\"(.*?)\".*?>(.*?<Interface name=\"(.*?)\".*?>.*?)*|.*?<Interface name=\"(.*?)\".*?>.*?<Interface name=\"(.*?)\".*?>.*?|.*?<Interface name=\"(.*?)\".*?>.*?");
	
	s.Send();
	
	printf("\nSending SDMSearch for registered Devices\n");
	memset(s.reg_expr,0,512);
	strcpy(s.reg_expr,".*?<Device.*?name=\"(.*?)\".*");
	s.id = DEVICE_SEARCH_ID;
	s.Send();
	
	printf("Sending SDMSearch for registered Applications\n");
	memset(s.reg_expr,0,512);
	strcpy(s.reg_expr,".*?<Application.*?name=\"(.*?)\".*");
	s.id = APPLICATION_SEARCH_ID;
	s.Send();
	while(1)
	{
		if (mm.IsReady())
		{
			mm.GetMessage(buf,length);
			cur = 0;
			result = reply.Unmarshal(buf);
			if(result == SDM_NO_FURTHER_DATA_PROVIDER)
				continue;
			printf("\n");
			if (reply.id == INTERFACE_SEARCH_ID)
				printf("Reply for interface search:\n");
			else if (reply.id == DEVICE_SEARCH_ID)
				printf("Reply for device search:\n");
			else if (reply.id == APPLICATION_SEARCH_ID)
				printf("Reply for application search:\n");
			if(count != 0)
				printf("\n");
			printf("Match(es) from %lu:%lu:%d\n",reply.source.getSensorID(),reply.source.getAddress(),reply.source.getPort());
			count++;
			while(reply.captured_matches[cur]!=0)
			{
				if(strlen(reply.captured_matches+cur)<32)
					printf("Match is %s\n",reply.captured_matches+cur);
				else
					printf("Match length of %d exceeds name length restriction of 32\n",strlen(reply.captured_matches+cur));
				cur += strlen(reply.captured_matches+cur)+1;
			}
			
		}
		else
		{
			printf(".");
			sleep(1);
			fflush(NULL);
		}
	}
}
void SigHandler(int signum)
{
	SDMSearch search;
	if (sigint_count == 0)
	{
		printf("Sending search subscription cancellation for interface searches only.\n");
		search.reply = SDM_SEARCH_CANCEL;
		search.destination.setPort(my_port);
		strcpy(search.reg_expr,".*?<Interface name=\"(.*?)\".*?>.*?<Interface name=\"(.*?)\".*?>(.*?<Interface name=\"(.*?)\".*?>.*?)*|.*?<Interface name=\"(.*?)\".*?>.*?<Interface name=\"(.*?)\".*?>.*?|.*?<Interface name=\"(.*?)\".*?>.*?");
		search.Send();
		sigint_count++;
	}
	else if (sigint_count == 1)
	{
		printf("Sending search subscription cancellations.\n");
		search.reply = SDM_SEARCH_CANCEL;
		search.destination.setPort(my_port);
		search.Send();
		sigint_count++;
	}
	else
		exit(0);
}

