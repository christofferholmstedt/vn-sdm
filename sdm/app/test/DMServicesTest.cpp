#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <vector>
#include <signal.h>

#include "../../common/message/SDMRegInfo.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMConsume.h"
#include "../../common/message/SDMCancel.h"
#include "../../common/message/SDMData.h"
#include "../../common/message/SDMCommand.h"
#include "../../common/message/SDMService.h"
#include "../../common/message/SDMSerreqst.h"
#include "../../common/message/SDMMessage_ID.h"
#include "../../common/MessageManager/MessageManager.h"

#define DMSUB_REGISTRATION 	1
#define DMSUB_DEREGISTRATION 	2
#define DMSUB_REGCHANGE		3
#define DMCOM_CONVERTEDNAME	4
#define DMSER_SPANODE		5

using namespace std;

SDMMessage_ID registration_id;
SDMMessage_ID deregistration_id;
SDMMessage_ID regchange_id;
SDMMessage_ID send_sid;
SDMMessage_ID spanode;
SDMMessage_ID converted_spanode(1, 7);
SDMMessage_ID converted_name(1,5);
SDMMessage_ID converted_ip(1, 10);
SDMMessage_ID sensor_toip(1, 12);
SDMMessage_ID pid_tosid(1, 8);
SDMMessage_ID pid_tosidreply(1, 9);
SDMService sensor_id_msg;

const int my_port = 4999;
bool providers_found = false;
vector<long> sensor_ids;
vector<SDMComponent_ID> comp_ids;
int signals_recd;
bool convert_name_ready = false;
//Tests whether the given argument is contiained within sensor_ids
bool sensor_ids_contains(long num)
{
	for (unsigned int i = 0; i < sensor_ids.size(); i++)
	{
		if (sensor_ids[i] == num)
			return true;
	}
	return false;
}
bool comp_ids_contains(SDMComponent_ID id)
{
	for (unsigned int i = 0; i < comp_ids.size(); i++)
	{
		if (comp_ids[i] == id)
			return true;
	}
	return false;
}


void RegInfoHandler(SDMRegInfo reg)
{
	SDMConsume consume;
	consume.destination.setPort(my_port);
	consume.source = reg.source;
	consume.msg_id = reg.msg_id;
	
	switch(reg.id)
	{
		case DMSUB_REGISTRATION:
			if (reg.source.getSensorID() == 1)
			{
				printf("Data manager's Registration subscription found, subscribing...\n");
				registration_id = reg.msg_id;
				if (!comp_ids_contains(reg.source))
					comp_ids.push_back(reg.source);
				consume.Send();
				providers_found = true;
			}
			break;
		case DMSUB_DEREGISTRATION:
			if (reg.source.getSensorID() == 1)
			{
				printf("Data manager's Deregistration subscription found, subscribing...\n");
				deregistration_id = reg.msg_id;
				if (!comp_ids_contains(reg.source))
					comp_ids.push_back(reg.source);
				consume.Send();
				providers_found = true;
			}
			break;
		case DMSUB_REGCHANGE:
			if (reg.source.getSensorID() == 1)
			{
				printf("Data manager's Registration Change subscription found, subscribing...\n");
				regchange_id = reg.msg_id;
				if (!comp_ids_contains(reg.source))
					comp_ids.push_back(reg.source);
				consume.Send();
				providers_found = true;
			}
			break;
		case DMCOM_CONVERTEDNAME:
			if (reg.source.getSensorID() == 1)
			{
				printf("Found DM convert name service.\n");
				if (reg.msg_id.getMessage() == 5)
				{
					send_sid = reg.msg_id;
					sensor_id_msg.source = reg.source;
					sensor_id_msg.command_id = reg.msg_id;
					sensor_id_msg.command_id.setMessage(6);
					sensor_id_msg.length = 4;
					sensor_id_msg.destination.setPort(my_port);
					convert_name_ready = true;
				}
				else if (reg.msg_id.getMessage() == 5)
				{
					converted_name = reg.msg_id;
				}
			}
			break;
		case DMSER_SPANODE:
			printf("Found service for SPANode.\n");
			spanode = reg.msg_id;
			break;
		default:
			printf("Received unexpected Reg Info type.\n");
	}
}

void SendRegReqs()
{
	SDMReqReg request;
	request.destination.setPort(my_port);
	strcpy(request.interface, "DM_Interface");
	
	printf("Sending request for the Registration subscription.\n");
	request.id = DMSUB_REGISTRATION;
	strcpy(request.item_name, "Registration");
	request.Send();
	
	printf("Sending request for the Deregistration subscription.\n");
	request.id = DMSUB_DEREGISTRATION;
	strcpy(request.item_name, "Deregistration");
	request.Send();
	
	printf("Sending request for the RegisterChange subscription.\n");
	request.id = DMSUB_REGCHANGE;
	strcpy(request.item_name, "RegisterChange");
	request.Send();
	
	printf("Sending request for ConvertedDeviceName command.\n\n");
	strcpy(request.item_name, "ConvertedDeviceName");
	request.id = DMCOM_CONVERTEDNAME;
	request.Send();
	
	printf("Sending request for SensorIDtoSPANode service.\n\n");
	strcpy(request.item_name, "SensorIDtoSPANode");
	request.id = DMSER_SPANODE;
	request.Send();
}

void DataHandler(SDMData data)
{
	unsigned long sensor_id;
	unsigned long address;
	unsigned short port;
	unsigned char type;
	char device_name[81];
	
	if (data.msg_id == registration_id)
	{
		sensor_id = GET_INT(data.msg);
		printf("Registration data message received.  Sensor id registered is %ld.\n", sensor_id);
		if (!sensor_ids_contains(sensor_id))
			sensor_ids.push_back(sensor_id);
		printf("  getting SPANode.\n");
		
		SDMService ser;
		ser.source = data.source;
		ser.command_id = spanode;
		PUT_UINT(ser.data, sensor_id);
		ser.length = 4;
		ser.destination.setPort(my_port);
		ser.Send();
	}
	else if (data.msg_id == converted_spanode)
	{
		sensor_id = GET_UINT(data.msg);
		
		printf("  SpaNode for sensor id %u is \"%s\"\n", sensor_id, data.msg + 4);
	}
	else if (data.msg_id == deregistration_id)
	{
		sensor_id = GET_INT(data.msg);
		printf("Deregistration data message received.  Sensor id deregistered is %ld.\n", sensor_id);
		if (!sensor_ids_contains(sensor_id))
			sensor_ids.push_back(sensor_id);
	}
	else if (data.msg_id == regchange_id)
	{
		type = GET_UCHAR(data.msg);
		sensor_id = GET_INT(data.msg+1);
		if (type == 1)
			printf("Change registration data message received.  Sensor id %ld registered.\n", sensor_id);
		else if (type == 2)
			printf("Change registration data message received.  Sensor id %ld deregistered.\n", sensor_id);
		if (!sensor_ids_contains(sensor_id))
			sensor_ids.push_back(sensor_id);
	}
	else if (data.msg_id == converted_name)
	{
		sensor_id = GET_UINT(data.msg);
		memcpy(device_name, data.msg+4, 81);
		printf("The converted name for sensor id %ld is %s.\n", sensor_id, device_name);
	}
	else if (data.msg_id == converted_ip)
	{
		sensor_id = GET_UINT(data.msg);
		address = GET_UINT(data.msg+4);
		port = GET_USHORT(data.msg+8);
		printf("The ip address for sensor id %ld is %lu:%hd.\n",sensor_id,address,port);
	}
	else if (data.msg_id == pid_tosidreply)
	{
		sensor_id = GET_UINT(data.msg + 4);
		printf("PID TO SENSOR ID RETURNED %ld\n", sensor_id);
	}
	
	static int count = 0;
	if ( count == 0 )
	{
		SDMService ser;
		ser.source = data.source;
		ser.command_id = pid_tosid;
		unsigned int mypid = 123;
		PUT_UINT(ser.data, mypid);
		ser.length = 4;
		ser.destination.setPort(my_port);
		ser.Send();
	}
	if (count ++ == 3)
		count = 0;
}

void SigHandler(int sig_num)
{
	SDMCancel cancel;
	cancel.destination.setPort(my_port);
	if (sig_num == SIGINT)
	{
		signals_recd++;
		if (signals_recd == 1)		//Cancel the subscriptions, and prepare to send commands
		{
			printf("\n\nCanceling subscriptions...");
			for (unsigned int i = 0; i < comp_ids.size(); i++)
			{
				cancel.source = comp_ids[i];
				cancel.msg_id = registration_id;
				cancel.Send();
				cancel.msg_id = deregistration_id;
				cancel.Send();
				cancel.msg_id = regchange_id;
				cancel.Send();
			}
			printf("Done.\n");
			if (!convert_name_ready)
			{
				printf("No RegInfo received for the convert name message.\n");
				return;
			}
			printf("\n");
			for (unsigned int i = 0; i < sensor_ids.size(); i++)
			{
				printf("Requesting to convert sensor id %ld to device name...\n", sensor_ids[i]);
				PUT_UINT(&sensor_id_msg.data, sensor_ids[i]);
				sensor_id_msg.Send();
			}
			sensor_id_msg.command_id = sensor_toip;
			printf("\n");
			for (unsigned int i = 0; i < sensor_ids.size(); i++)
			{
				printf("Requesting to convert sensor id %ld to ip...\n", sensor_ids[i]);
				PUT_UINT(&sensor_id_msg.data, sensor_ids[i]);
				sensor_id_msg.Send();
			}
			printf("\n");
			
		}
		else
			exit(EXIT_SUCCESS);
	}
}
int main (int argc, char ** argv)
{
	char buf[BUFSIZE];
	long length;
	SDMRegInfo info;
	SDMData data;
	SDMInit(argc, argv);
	
	MessageManager mm;
	mm.Async_Init(my_port);
	signal(SIGINT, SigHandler);
	
	printf("This program tests the Data Manager's \"Registration\", \"Deregistration\", and \"Register Change\" subscriptions.  It also tests the services \"SendSensorID/ConvertedDeviceName\" and \"SensorIDtoIP/ConvertedIP\".  After testing for registration/deregistrations, type CTRL+C to convert all received sensor IDs to their device names and ip addresses.\n\n");
	sleep(3);
	while (1)
	{
		if (mm.IsReady())
		{
			switch(mm.GetMessage(buf, length))
			{
				case SDM_RegInfo:
					if (info.Unmarshal(buf) != SDM_NO_FURTHER_DATA_PROVIDER)
					{
						RegInfoHandler(info);
					}
					break;
				case SDM_Data:
					data.Unmarshal(buf);
					DataHandler(data);
					break;
				
			}
			
		}
		else if (!providers_found)
		{
			SendRegReqs();
			sleep(1);
		}
		else
		{
			usleep(5000);
		}
	}
	
	
	return 0;
}
