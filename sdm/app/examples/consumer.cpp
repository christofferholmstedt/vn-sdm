#include "../../common/message/SDMData.h"
#include "../../common/message/SDMService.h"
#include "../../common/message/SDMConsume.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMHeartbeat.h"
#include "../../common/MessageManipulator/MessageManipulator.h"
#include "../../common/MessageManager/MessageManager.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define DATA_PROVIDER		1
#define SERVICE_PROVIDER	2

long my_port;
SDMComponent_ID data_provider;
SDMComponent_ID service_provider;
SDMMessage_ID data_msg(0,0);
SDMMessage_ID service_msg(0,0);

MessageManipulator data_manipulator;
MessageManipulator service_manipulator;

void DataHandler(SDMData& dat,long length)
{
	SDMService request;
	short int_value;
	float float_value;
	static float geo_average = 0;

	if((dat.source == data_provider)&&(dat.msg_id == data_msg))
	{
		//marshal appropriate service message
		//copy source componentID into service request
		request.source=service_provider;
		request.destination.setPort(my_port);
		//copy msg id into service request
		request.command_id=service_msg;
		//set the length we are sending
		request.length = sizeof(short);
		//copy integer data into service request
		if(service_provider.getSensorID()==0)
		{
			printf("No converter is available\n");
			return;
		}
		int_value = data_manipulator.getUINT16Value("data",dat,DATAMSG);
		service_manipulator.setValue("convertee",request,int_value);
		//send request
		request.Send();
	}
	else if((dat.source == service_provider))
	{
		float_value = service_manipulator.getFLOAT32Value("data",dat,DATAMSG);
		geo_average /=2;
		geo_average += float_value;
		//extract and display results
		printf("Running Average -- %f\n",geo_average);
	}
}

void RegInfoHandler(SDMRegInfo& info)
{
	SDMConsume consume;
	SDMReqReg req_reg;

	//Set the port we will be receiving on
	consume.destination.setPort(my_port);
	//copy the sensor id into the consume message
	consume.source=info.source;
	//copy the msg id into the consume message
	consume.msg_id=info.msg_id;

	switch(info.id)
	{
	case DATA_PROVIDER:
		if(info.type == 1)
		{
			data_provider.setSensorID(0);
			printf("Data provider failed . . . ");
			printf("Searching for new provider\n");
			//request info on integer data providers,
			//the DM will repost software tasks that
			// could satisfiy our requirments

			//Set variable name
			strcpy(req_reg.item_name,"data");
			//Set the quallist can be empty
			strcpy(req_reg.quallist,"< format=\"UINT16\"/>");
			req_reg.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
			req_reg.destination.setPort(my_port);
			req_reg.id = DATA_PROVIDER;
			req_reg.Send();
		}
		else
		{
			if(data_provider.getSensorID() == 0)
			{
			data_provider = info.source;
			data_msg = info.msg_id;
			data_manipulator.setMsgDef(info.msg_def);
			printf("New Data provider found");
			printf("\n\n%s\n",info.msg_def);
			//Send the consume message
			consume.Send();
			}
			else
			{
			printf("Data provider found");
			printf(" - not used\n\n%s\n",info.msg_def);
			}
		}
		break;
	case SERVICE_PROVIDER:
		if(info.type == SDM_REGINFO_CANCELLATION)
		{
			service_provider.setSensorID(0);
			printf("Service provider failed . . . ");
			printf("Searching for new provider\n");
			//request info on service providers,
			//the DM will repost software tasks
			//that could satisfiy our requirments

			//Set var name to convert which we already know
			strcpy(req_reg.item_name,"convert");
			//We will not be using wildcards
			req_reg.quallist[0] = '\0';
			req_reg.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
			req_reg.destination.setPort(my_port);
			req_reg.id = SERVICE_PROVIDER;
			req_reg.Send();
		}
		else
		{
			if(service_provider.getSensorID() == 0)
			{
			service_provider = info.source;
			service_msg = info.msg_id;
			service_manipulator.setMsgDef(info.msg_def);
			printf("New Service provider found");
			printf("\n\n%s\n",info.msg_def);
			}
			else
			{
			printf("Service provider found - ");
			printf("not used\n\n%s\n",info.msg_def);
			}
		}
		break;
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

	//initialize consumer
	SDMInit(argc,argv);
	my_port = getPort();
	if(my_port == SDM_PM_NOT_AVAILABLE)
	{
		printf("No PM is available to get port from!\n");
		return 0;
	}
	mm.Async_Init(my_port);

	printf("Consumer listening on port %ld\n",my_port);

	while(1)
	{
		if (mm.IsReady())
		{
			SendHeartbeat();
#ifdef WIN32
			switch(mm.GetMsg(buf,length))
#else
			switch(mm.GetMessage(buf,length))
#endif
			{
			case SDM_Data:
				dat.Unmarshal(buf,length);
				DataHandler(dat,length);
				break;
			case SDM_RegInfo:
				if(info.Unmarshal(buf)!=SDM_NO_FURTHER_DATA_PROVIDER)
				{
					RegInfoHandler(info);
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
				strcpy(req_reg.item_name,"data");
				//Set the quallist can be empty
				strcpy(req_reg.quallist,"< format=\"UINT16\"/>");
				req_reg.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
				req_reg.destination.setPort(my_port);
				req_reg.id = DATA_PROVIDER;
				req_reg.Send();
				printf("Searching for new data provider\n");
				sleep(2);
			}
			if(service_provider.getSensorID() == 0)
			{
				//request info on service providers
				//Set var name to convert which we already know
				strcpy(req_reg.item_name,"convert");
				//We will not be using wildcards
				req_reg.quallist[0] = '\0';
				req_reg.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
				req_reg.destination.setPort(my_port);
				req_reg.id = SERVICE_PROVIDER;
				req_reg.Send();
				printf("Searching for new service provider\n");
				sleep(2);
			}
			usleep(1000);
		}
	}
}
