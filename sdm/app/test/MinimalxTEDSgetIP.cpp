#include "../../common/message/SDMxTEDS.h"
#include "../../common/message/SDMData.h"
#include "../../common/message/SDMCancelxTEDS.h"
#include "../../common/message/SDMService.h"
#include "../../common/MessageManager/MessageManager.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <arpa/inet.h>

void RegisterxTEDS();
void CancelxTEDS();
void GetComponentID();

long my_port;
long my_sensorID;
long my_PID;
MessageManager mm;

int main(int argc,char** argv)
{
	SDMData dat;
	

	SDMInit(argc,argv);
	my_port = getPort();
	if (my_port < 0)
	{
		printf("Error requesting port.\n");
		return -1;
	}
	mm.Async_Init(my_port);
	RegisterxTEDS();
	GetComponentID();
	CancelxTEDS();
}

void RegisterxTEDS()
{
	SDMxTEDS  xteds;	// create an xTEDS registration message

	strcpy (xteds.xTEDS,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<xTEDS name=\"Minimal_xTEDS\" version=\"2.0\">\n\n\t<Application name=\"MinimalxTEDS\" kind=\"Software\"/>\n\n\t<Interface name=\"Min_Interface\" id=\"1\"/>\n\n</xTEDS>\n");	// set xTEDS

	xteds.source.setSensorID(1);		// set the id of this application
	xteds.source.setPort(my_port);
	printf("Registering producer xTEDS on port %ld\n",my_port);
	xteds.Send();				// register with the SDM
}

void GetComponentID()
{
	char buf[BUFSIZE];
	SDMService service;
	SDMData data;
	
	service.source = DataManager;
	service.source.setSensorID(1);  //DataManager sensor_id is always 1
	service.destination.setPort(my_port);
	service.command_id = 264;  //Could be queried for by using a SDMReqReg with item_name = ReturnSensorID
	service.length = 4;
	PUT_INT(service.data,PID);
	service.Send();

	mm.BlockGetMessage(buf);
	data.Unmarshal(buf);

	my_PID = GET_LONG(data.msg);
	my_sensorID = GET_LONG(&data.msg[4]);  //Could be gotten from the Messagemanipulator
	printf("My PID is %ld\n",my_PID);
	printf("My sensor_id is %ld\n",my_sensorID);
}

void CancelxTEDS()
{
	SDMCancelxTEDS cancel;
	printf("Canceling xTEDS\n");
	cancel.source.setSensorID(1);
	cancel.source.setPort(my_port);
	cancel.Send();
}
