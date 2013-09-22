#include "../../common/message/SDMData.h"
#include "../../common/message/SDMService.h"
#include "../../common/message/SDMConsume.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMCancel.h"
#include "../../common/MessageManipulator/MessageManipulator.h"
#include "../../common/MessageManager/MessageManager.h"
#include "../../common/marshall.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

#define DATA_PROVIDER		1

long my_port;
SDMConsume consume_msgs[4];
SDMComponent_ID service_provider;
static int providerIndex = -1;

MessageManipulator data_manipulator;

void DataHandler(SDMData& dat,long length)
{
	unsigned int total_recd = 0;
	unsigned int lastsec_recd = 0;
	unsigned int total_sent = 0;
	unsigned int lastsec_sent = 0;

	total_recd = GET_UINT(&dat.msg[0]);
	lastsec_recd = GET_UINT(&dat.msg[4]);
	total_sent = GET_UINT(&dat.msg[8]);
	lastsec_sent = GET_UINT(&dat.msg[12]);


	if(dat.source.getPort() == PORT_DM)
	{
	 	printf("DM ::  Total messages recd = %u, Messages last second recd= %u, Total messages sent = %u, Messages last second sent = %u\n", total_recd, lastsec_recd, total_sent, lastsec_sent);
	}
	else if (dat.source.getPort() == PORT_TM)
        {
	  	printf("TM ::  Total messages recd = %u, Messages last second recd= %u, Total messages sent = %u, Messages last second sent = %u\n", total_recd, lastsec_recd, total_sent, lastsec_sent);
        } 
	else if (dat.source.getPort() == PORT_PM)
	{
	  	printf("PM ::  Total messages recd = %u, Messages last second recd= %u, Total messages sent = %u, Messages last second sent = %u\n", total_recd, lastsec_recd, total_sent, lastsec_sent);
	}
	else if (dat.source.getPort() == PORT_SM)
	{
		printf("SM ::  Total messages recd = %u, Messages last second recd= %u, Total messages sent = %u, Messages last second sent = %u\n", total_recd, lastsec_recd, total_sent, lastsec_sent);
	}
	else
		printf("Unknown sender. %ld:%hd\n", dat.source.getAddress(), dat.source.getPort());
}

void RegInfoHandler(SDMRegInfo& info)
{
	providerIndex++;
	//Set the port we will be receiving on
	consume_msgs[providerIndex].destination.setPort(my_port);
	//copy the sensor id into the consume message
	consume_msgs[providerIndex].source = info.source;
	//copy the msg id into the consume message
	consume_msgs[providerIndex].msg_id = info.msg_id;

	if (info.source == DataManager)
	  printf("RegInfo for DataManager received.");
	else if (info.source == TaskManager)
	  printf("RegInfo for TaskManager received.");
	//else if (info.source == SensorManager)
	//  printf("RegInfo for SensorManager received.");
	
	printf("Message id is %ud interface id is %ud \n",info.msg_id.getMessage(),info.msg_id.getInterface());
	fflush(NULL);
	switch(info.id)
	{
	case DATA_PROVIDER:
		if (info.type != 1)
		{
			data_manipulator.setMsgDef(info.msg_def);
			printf("New Data provider found");
			printf("\n\n%s\n",info.msg_def);
			//Send the consume message
			consume_msgs[providerIndex].Send();
		}
		break;

	}

}

void SigHandler(int signum)
{
	if (signum == SIGINT)
	{
		SDMCancel cancel_msg;
		cancel_msg.destination.setPort(my_port);
		printf("Cancelling subscriptions...");
		for (int i = 0; i <= providerIndex; i++)
		{
			cancel_msg.source = consume_msgs[i].source;
			cancel_msg.msg_id = consume_msgs[i].msg_id;
			cancel_msg.Send();
		}
		printf("Done.\n");
		_exit(0);
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
	mm.Async_Init(my_port);
	signal(SIGINT, SigHandler);

	printf("%s listening on port %ld\n",argv[0],my_port);

	while(1)
	{
		if (mm.IsReady())
		{
			switch(mm.GetMessage(buf,length))
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
			if(consume_msgs[0].source.getSensorID() == 0)
			{
				//request info on integer data providers
				//Set variable name
				strcpy(req_reg.item_name,"Total_Messages_Recd");
				//Set the quallist can be empty
				strcpy(req_reg.quallist,"< format=\"UINT32\"/>");
				req_reg.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
				req_reg.destination.setPort(my_port);
				req_reg.id = DATA_PROVIDER;
				req_reg.Send();
				printf("Searching for new data provider\n");
				sleep(2);
			}
			usleep(1000);
		}
	}
}
