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

#define BB_SETRATE	1
#define BB_VOLTREAD	2
#define BB_LCD		3

SDMComponent_ID sub_compid;
SDMMessage_ID sub_msgid;
SDMMessage_ID lcd_msgid;

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
	
	mm.Async_Init(4050);
	
	printf("\nSending ReqReg for breadboard data rate...\n");
	strcpy(reqreg_msg.device,"Bread Board");
	strcpy(reqreg_msg.interface,"1");
	strcpy(reqreg_msg.item_name,"Set_Data_Rate");
	reqreg_msg.id = BB_SETRATE;
	reqreg_msg.destination.setPort(4050);
	reqreg_msg.Send();
	
	printf("Sending ReqReg for breadboard voltage reading...\n");
	strcpy(reqreg_msg.item_name,"Voltage_Reading");
	reqreg_msg.id = BB_VOLTREAD;
	reqreg_msg.Send();
	
	printf("Sending ReqReg for breadboard LCD command...\n");
	strcpy(reqreg_msg.item_name,"Set_LCD");
	reqreg_msg.id = BB_LCD;
	reqreg_msg.Send();
	
	unsigned short data = 4;
	while (1)
	{
		type = mm.BlockGetMessage(buf);
		switch (type)
		{
			case SDM_RegInfo:
				if (reginfo_msg.Unmarshal(buf) != SDM_NO_FURTHER_DATA_PROVIDER)
				{
					if (reginfo_msg.id == BB_SETRATE)
					{
						cmd_msg.source = reginfo_msg.source;
						cmd_msg.command_id = reginfo_msg.msg_id;
						PUT_USHORT(cmd_msg.data,data);
						cmd_msg.length = 2;
						printf("Sending command message to set breadboard data rate to %hhd.\n",data);
						//cmd_msg.Send(reginfo_msg.source);
						cmd_msg.Send();
					}
					else if (reginfo_msg.id == BB_VOLTREAD)
					{
						cons_msg.source = reginfo_msg.source;
						sub_compid = reginfo_msg.source;
						cons_msg.destination.setPort(4050);
						cons_msg.msg_id = reginfo_msg.msg_id;
						sub_msgid = reginfo_msg.msg_id;
						printf("Sending consume for breadboard voltage reading...\n");
						cons_msg.Send();
					}
					else if (reginfo_msg.id == BB_LCD)
					{
						//Save the message ID number
						lcd_msgid = reginfo_msg.msg_id;
						printf("Saving lcd command message id...\n");
					}
				}
				break;
			case SDM_Data:
			{
				unsigned short voltage;
				data_msg.Unmarshal(buf);
				voltage = GET_USHORT(data_msg.msg+8);
				printf("Received voltage reading of %hhd\n",voltage);
				//Set the LCD to be the voltage reading
				SDMCommand cmd_msg;
				cmd_msg.command_id = lcd_msgid;
				cmd_msg.source = sub_compid;
				PUT_USHORT(cmd_msg.data,voltage);
				cmd_msg.length = 2;
				cmd_msg.Send();
				break;
			}
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
	cancel_msg.destination.setPort(4050);
	cancel_msg.Send();
	_exit(0);
}
