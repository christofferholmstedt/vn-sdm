#include "../../common/message/SDMxTEDS.h"
#include "../../common/message/SDMSubreqst.h"
#include "../../common/message/SDMDeletesub.h"
#include "../../common/message/SDMCancelxTEDS.h"
#include "../../common/message/SDMService.h"
#include "../../common/message/SDMData.h"
#include "../../common/message/SDMConsume.h"
#include "../../common/MessageManager/MessageManager.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void RegisterxTEDS();
void CancelxTEDS();

long my_port;

int main(int argc,char** argv)
{
	SDMService service;
	SDMConsume con;
	char buf[BUFSIZE];
	long length;
	MessageManager mm;
	bool one = false;

	int pid = 0;
	int sid = 0;
	SDMData dat;

	SDMInit(argc,argv);
	my_port = getPort();
	mm.Async_Init(my_port);
	RegisterxTEDS();
	sleep(1);
	service.source.setSensorID(1);
	service.command_id = 264;
	service.destination.setPort(my_port);
	service.length = 4;
	pid = atoi(argv[3]);
	memcpy(service.data,&pid,4);
	service.Send();
	while(1)
	{
		if (mm.IsReady())
		{
			mm.GetMessage(buf,length);
			dat.Unmarshal(buf,4);
			switch(dat.msg_id.getInterfaceMessagePair())
			{
				case 257:
					memset(&pid,0,4);
					memcpy(&pid,dat.msg,4);
					if(one == false)
					{
						printf("Registered SensorID's are %d",pid);
						fflush(NULL);
						one = true;
					}
					else
					{
						printf(", %d",pid);
						fflush(NULL);
						if(pid == sid)
						{
							printf("\n");
							CancelxTEDS();
							return 0;
						}
					}
					break;
				case 265:
					memcpy(&sid,&dat.msg[0],4);
					printf("My SensorID is %d\n",sid);
					con.source.setSensorID(1);
					con.msg_id = 257;
					con.destination.setPort(my_port);
					con.Send();
					break;
				default:
					printf("Unexpected data message\n");
					break;
			}
		}	
	}
}

void RegisterxTEDS()
{
	SDMxTEDS  xteds;	// create an xTEDS registration message

	strcpy (xteds.xTEDS,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<xTEDS version=\"2.0\" name=\"Producer_xTEDS\">\n\t<Application name=\"producer\" kind=\"data\"/>\n\t<Interface name=\"Producer_Interface\" id=\"1\">\n\t<Variable name=\"data\" format=\"UINT16\" kind=\"data\" qualifier=\"Single Value\"/>\n\t<Notification>\n\t\t<DataMsg name=\"all\" id=\"1\" msgArrival=\"PERIODIC\" msgRate=\"1\">\n\t\t\t<VariableRef name=\"data\"/>\n\t\t</DataMsg>\n\t</Notification>\n\t</Interface>\n</xTEDS>\n");	// set xTEDS

	xteds.source.setSensorID(1);		// set the id of this application
	xteds.source.setPort(my_port);
	printf("Registering producer xTEDS on port %ld\n",my_port);
	xteds.Send();				// register with the SDM
}

void CancelxTEDS()
{
	SDMCancelxTEDS cancel;
	printf("Canceling xTEDS\n");
	cancel.source.setSensorID(1);
	cancel.source.setPort(my_port);
	cancel.Send();
}
