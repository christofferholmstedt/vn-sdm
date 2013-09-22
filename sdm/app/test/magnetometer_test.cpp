#include "../../common/message/SDMmessage.h"
#include "../../common/message/SDMData.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/message/SDMConsume.h"
#include "../../common/MessageManager/MessageManager.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(int argc,char** argv)
{
	SDMInit(argc,argv);
	SDMReqReg request;
	SDMRegInfo info;
	SDMData data;
	SDMConsume consume;
	MessageManager mm;
	char buf[BUFSIZE];

	int result;
	int my_port = getPort();
	if (my_port < 0)
	{
		printf("Error getting port.\n");
		return -1;
	}
	mm.Async_Init(my_port);
	double timestamp;
	float Field_X;
	float Field_Y;
	float Field_Z;

	strncpy(request.item_name,"MagFieldData",81);
	strcpy(request.quallist,"<description=\"TFM100S Magnetometer Fields\"/>");
	request.destination.setPort(my_port);
	request.Send();
	result = info.Recv(my_port);
	while(result == SDM_NO_FURTHER_DATA_PROVIDER)
	{
		sleep(1);
		printf("Searching for Magnetometer...\n");
		request.Send();
		result = info.Recv(my_port);
	}
	consume.source = info.source;
	consume.msg_id = info.msg_id;
	consume.destination.setPort(my_port);
	while(result != SDM_NO_FURTHER_DATA_PROVIDER)
	{
		result = info.Recv(my_port);
	}
	printf("Magnetometer found, requesting field data\n");
	consume.Send();
	while(1)
	{
		if (mm.BlockGetMessage(buf) != SDM_Data)
			continue;
		result = data.Unmarshal(buf);
		if(result == SDM_INVALID_MESSAGE)
		{
			printf("Invalid Message recieved\n");
		}
		else
		{
			//get timestamp (DFP)
			memcpy(&timestamp,data.msg,8);
			//get Field_X (SFP)
			memcpy(&Field_X,data.msg+8,4);
			//get Field_Y (SFP)
			memcpy(&Field_Y,data.msg+12,4);
			//get Field_Z (SFP)
			memcpy(&Field_Z,data.msg+16,4);
			printf("time:%f\tX:%f\tY:%f\tZ:%f\n",timestamp,Field_X,Field_Y,Field_Z);
		}
	}
}
