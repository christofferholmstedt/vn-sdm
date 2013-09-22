#include "../../common/message/SDMSearch.h"
#include "../../common/message/SDMSearchReply.h"
#include "../../common/MessageManager/MessageManager.h"
#include "../../common/message/SDMData.h"
#include "../../common/message/SDMConsume.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <signal.h>

#define ORIENTATION_SEARCH_ID	1

long my_port = 4020;
int sigint_count = 0;

void SigHandler(int signum);
int main(int argc,char** argv)
{
	SDMSearch s;
	SDMSearchReply reply;
	SDMData dat;
	SDMConsume con;
	int result = 0;
	char buf[BUFSIZE];
	long length;
	MessageManager mm;
	int cur = 0;
	int count = 0;
	char c;
	unsigned long SID;
		
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
	s.reply = SDM_SEARCH_CURRENT_AND_FUTURE;
	
	printf("\nSending SDMSearch for Device orientation\n");
	memset(s.reg_expr,0,512);
	strcpy(s.reg_expr,".*?<Orientation.*?axis=\"(.*?)\".*");
	s.id = ORIENTATION_SEARCH_ID;
	s.Send();
	
	con.destination = s.destination;
	con.source.setPort(PORT_DM);
	con.source.setAddress(DataManager.getAddress());
	con.source.setSensorID(1);
	con.msg_id = 0x103;
	con.Send();
	
	con.msg_id = 0x104;
	con.Send();
	while(1)
	{
		if (mm.IsReady())
		{
			c = mm.GetMessage(buf,length);
			cur = 0;
			switch(c)
			{
				case SDM_SearchReply:
					result = reply.Unmarshal(buf);
					if(result == SDM_NO_FURTHER_DATA_PROVIDER)
						continue;
					printf("\n");
					if (reply.id == ORIENTATION_SEARCH_ID)
						printf("Reply for orientation search:\n");
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
					break;
				case SDM_Data:
					result = dat.Unmarshal(buf);
					if(dat.length > 4)
					{
						memcpy(&SID,&dat.msg[1],4);
						printf("xTEDS change of type %d on SID %ld\n",dat.msg[0],SID);
					}
					else
					{
						memcpy(&SID,&dat.msg[0],4);
						printf("xTEDS modificaton of SID %ld\n",SID);
					}
					break;
				default:
					printf("Unexpected message of type %c \n",c);
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
	printf("Sending search subscription cancellation for interface searches only.\n");
	search.reply = SDM_SEARCH_CANCEL;
	search.destination.setPort(my_port);
	strcpy(search.reg_expr,".*?<Orientation.*?axis=\"(.*?)\".*");
	search.Send();
	sigint_count++;
	exit(0);
}

