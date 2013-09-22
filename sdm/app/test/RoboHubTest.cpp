#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMCommand.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/MessageManager/MessageManager.h"
#include "../../common/message/SDMData.h"
#include "../../common/message/SDMConsume.h"
#include "../../common/message/SDMCancel.h"

#define RH_STATUS	1
#define RH_TEMPREADING	2

SDMComponent_ID sub_compid;
SDMMessage_ID sub_msgid;
SDMMessage_ID StatusID;
SDMMessage_ID TempReadingID;
const int myPort = 4058;
void SigHandler(int signum);

int main (int argc, char ** argv)
{
	MessageManager mm;
	SDMReqReg reqreg_msg;
	char buf[BUFSIZE];
	SDMRegInfo reginfo_msg;
	SDMCommand cmd_msg;
	SDMData data_msg;
	SDMConsume cons_msg;
	unsigned char type;
	SDMInit(argc, argv);
	signal(SIGINT,SigHandler);
	
	mm.Async_Init(myPort);
	
	printf("\nSending ReqReg for robohub status message...\n");
	strcpy(reqreg_msg.device,"RoboHub_8_Port");
	strcpy(reqreg_msg.item_name,"GetHubStatus");
	reqreg_msg.id = RH_STATUS;
	reqreg_msg.destination.setPort(myPort);
	reqreg_msg.Send();
	
	printf("Sending ReqReg for robohub temperature reading...\n");
	strcpy(reqreg_msg.item_name,"DeviceTemp");
	reqreg_msg.id = RH_TEMPREADING;
	reqreg_msg.Send();
	
	while (1)
	{
		type = mm.BlockGetMessage(buf);
		switch (type)
		{
			case SDM_RegInfo:
				if (reginfo_msg.Unmarshal(buf) != SDM_NO_FURTHER_DATA_PROVIDER)
				{
					//Robohub status message reginfo
					if (reginfo_msg.id == RH_STATUS)
					{
						cmd_msg.source = reginfo_msg.source;
						cmd_msg.command_id = reginfo_msg.msg_id;
						cmd_msg.length = 0;
						printf("Sending command message to get RoboHub status.\n");
						cmd_msg.Send(reginfo_msg.source);
					}
					//Robohub temperature reading message
					else if (reginfo_msg.id == RH_TEMPREADING)
					{
						cons_msg.source = reginfo_msg.source;
						sub_compid = reginfo_msg.source;
						cons_msg.destination.setPort(myPort);
						TempReadingID = cons_msg.msg_id = reginfo_msg.msg_id;
						sub_msgid = reginfo_msg.msg_id;
						printf("Sending consume for robohub temperature reading...\n");
						cons_msg.Send();
					}
				}
				break;
			case SDM_Data:
				if (data_msg.Unmarshal(buf) < 0)
				{
					printf("Invalid data message received.\n");
					continue;
				}
				//If this is the temperature reading response
				if (data_msg.msg_id == TempReadingID)
				{
					//pull out the temperature measurement
					short TempVal = GET_SHORT(data_msg.msg+8);
					printf("Temperature reading received: %hd\n",TempVal);
				}
				//This is the status command reply
				else
				{
					//pull out the port enumeration
					unsigned char PortEnum = data_msg.msg[8];
					printf("Received port enumeration: %hhu\n",PortEnum);
				}
				break;
			default:
				printf("Unexpected message (%d).\n",type);
		}
	}
	
	
}

void SigHandler(int signum)
{
	SDMCancel cancel_msg;
	cancel_msg.source = sub_compid;
	cancel_msg.msg_id = sub_msgid;
	cancel_msg.destination.setPort(myPort);
	cancel_msg.Send();
	_exit(0);
}
