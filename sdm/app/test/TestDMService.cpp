#include "../../common/message/SDMxTEDS.h"
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
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void RegisterxTEDS();
void CancelxTEDS();
void* Publisher(void *);
void* Listener(void *);

long my_port;

int main(int argc,char** argv)
{
	SDMService service;
	SDMConsume con;
	MessageManager mm;
	char buf[BUFSIZE];
	char name[128];
	char ip[17];
	long port;
	SDMComponent_ID id;

	int pid = 0;
	SDMData dat;

	SDMInit(argc,argv);
	my_port = getPort();
	if (my_port < 0)
	{
		printf("Error getting port.\n");
		return -1;
	}
	mm.Async_Init(my_port);
	
	RegisterxTEDS();
	usleep(100);
	service.source.setSensorID(1);
	service.command_id = 264;
	service.destination.setPort(my_port);
	service.length = 4;
	pid = atoi(argv[3]);
	memcpy(service.data,&pid,4);
	service.Send();
	
	if (mm.BlockGetMessage(buf) != SDM_Data)
	{
		printf("Error, unknown message received.\n");
		return -1;
	}
	dat.Unmarshal(buf);
	
	pid = GET_LONG(dat.msg);
	printf("My SensorID is %d\n",pid);
	service.command_id = 262;
	memcpy(service.data,&pid,4);
	service.Send();
	
	if (mm.BlockGetMessage(buf) != SDM_Data)
	{
		printf("Error, unknown message received.\n");
		return -1;
	}
	dat.Unmarshal(buf);
	
	memset(name,0,128);
	strncpy(name,dat.msg,127);
	printf("My name is %s\n",name);
	service.command_id = 268;
	service.Send();
	
	if (mm.BlockGetMessage(buf) != SDM_Data)
	{
		printf("Error, unknown message received.\n");
		return -1;
	}
	dat.Unmarshal(buf);
	
	port = GET_LONG(dat.msg);
	strcpy(ip,&dat.msg[4]);
	printf("My port is %ld and my ip is %s\n",port,ip);
	service.command_id = 267;
	service.Send();
	service.command_id = 270;
	id.setSensorID(pid);
	id.setPort(port);
	id.setAddress(inet_addr(ip));
	id.Unmarshal(service.data,0);
	service.Send();
	
	if (mm.BlockGetMessage(buf) != SDM_Data)
	{
		printf("Error, unknown message received.\n");
		return -1;
	}
	dat.Unmarshal(buf);
	
	printf("My componentKey is %s\n",dat.msg);
	CancelxTEDS();
}

void RegisterxTEDS()
{
	SDMxTEDS  xteds;	// create an xTEDS registration message

	strcpy (xteds.xTEDS,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<xTEDS version=\"2.0\" name=\"Producer_xTEDS\">\n\t<Application name=\"producer\" kind=\"data\" componentKey=\"ProducerKey\"/>\n\t<Interface name=\"Producer_Interface\" id=\"1\">\n\t<Variable name=\"data\" format=\"UINT16\" kind=\"data\" qualifier=\"Single Value\"/>\n\t<Notification>\n\t\t<DataMsg name=\"all\" id=\"1\" msgArrival=\"PERIODIC\" msgRate=\"1\">\n\t\t\t<VariableRef name=\"data\"/>\n\t\t</DataMsg>\n\t</Notification>\n\t</Interface>\n</xTEDS>\n");	// set xTEDS

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
