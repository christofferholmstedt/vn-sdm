#include "../../../common/message/SDMxTEDS.h"
#include "../../../common/message/SDMCancelxTEDS.h"
#include "../../../common/message/SDMmessage.h"
#include "../../../common/message/SDMSerreqst.h"
#include "../../../common/message/SDMData.h"
#include "../../../common/MessageManager/MessageManager.h"
#include "../../../common/message/SDMHello.h"
#include "../../../common/message/SDMID.h"
#include "../../../common/message/SDMRegister.h"
#include "../../../common/Time/SDMTime.h"
#include <string.h>
#include <stdio.h>

void PerformRequest(char*);
void Register(MessageManager*);
double GetCurTime();
void CancelxTEDS();

long my_port;
bool done = false;
int requestCount = 0;

//xTEDS data
const char* XML_HEADER = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
const char* XTEDS_SECTION = "\n<xTEDS version=\"2.0\" name=\"converter_xTEDS\">";
const char* APP_SECTION = "\n\t<Application name=\"converter\" kind=\"Software\"/>";
const char* INTERFACE = "\n\t<Interface name=\"Converter_Interface\" id=\"1\">";
const char* VAR_DATA_1 = "\n\t\t<Variable name=\"data\" format=\"FLOAT32\"";
const char* VAR_DATA_2 = " kind=\"Float_Data\"/>";
const char* VAR_CONVERTEE_1 = "\n\t\t<Variable name=\"convertee\" format=\"UINT16\"";
const char* VAR_CONVERTEE_2 = " kind=\"Int_Data\"/>";
const char* REQUEST = "\n\n\t\t<Request>";
const char* CMD_CONVERT_1 = "\n\t\t\t<CommandMsg name=\"convert\" id=\"1\">";
const char* CMD_CONVERT_2 = "\n\t\t\t\t<VariableRef name=\"convertee\"/>";
const char* CMD_CONVERT_3 = "\n\t\t\t</CommandMsg>";
const char* MSG_RESULTS_1 = "\n\t\t\t<DataReplyMsg name=\"results\" id=\"2\"";
const char* MSG_RESULTS_2 = " msgArrival=\"EVENT\">\n\t\t\t\t";
const char* MSG_RESULTS_3 = "<VariableRef name=\"data\"/>\n\t\t\t</DataReplyMsg>";
const char* REQUEST_END = "\n\t\t</Request>";
const char* INTERFACE_END = "\n\t</Interface>";
const char* XTEDS_END = "\n</xTEDS>";

int main(int argc,char** argv)
{
	SDMInit(argc,argv);
	my_port = getPort();
	if(my_port == SDM_PM_NOT_AVAILABLE)
	{
		printf("No PM is available to get port from!\n");
		printf("Using port 5003\n");
		my_port = 5003;
	}

	MessageManager mm;
	mm.Async_Init(my_port);
	Register(&mm);
	
	char buf[BUFSIZE];
	// now wait for and handle 15 service request messages
	printf("Waiting for service request.\n");
	while(!done)
	{		
		if(mm.IsReady())
		{
			switch(mm.GetMessage(buf))
			{
				case SDM_Serreqst:
					printf("Request Received\n");
					requestCount++;
					PerformRequest(buf);
					break;
				default:
					break;			
			}	
		}	
		if(requestCount >= 15)
		{
			done = true;
		}
		usleep(1000);
	}
	printf("Converter is shutting itself down\n");
	CancelxTEDS();
	return 0;
}

void Register(MessageManager* mm)
{
	bool helloReceived = false;
	bool registerReceived = false;
	bool idReceived = false;
	bool registering = true;
	
	char buf[BUFSIZE];
	
//	create an xTEDS registration message
	 SDMxTEDS  xteds;

	// SDMCancelxTEDS cancel;

	 // set xTEDS
	 strcat (xteds.xTEDS,XML_HEADER);
	 strcat (xteds.xTEDS,XTEDS_SECTION);
	 strcat (xteds.xTEDS,APP_SECTION);
	 strcat (xteds.xTEDS,INTERFACE);
	 strcat (xteds.xTEDS,VAR_DATA_1);
	 strcat (xteds.xTEDS,VAR_DATA_2);
	 strcat (xteds.xTEDS,VAR_CONVERTEE_1);
	 strcat (xteds.xTEDS,VAR_CONVERTEE_2);
	 strcat (xteds.xTEDS,REQUEST);
	 strcat (xteds.xTEDS,CMD_CONVERT_1);
	 strcat (xteds.xTEDS,CMD_CONVERT_2);
	 strcat (xteds.xTEDS,CMD_CONVERT_3);
	 strcat (xteds.xTEDS,MSG_RESULTS_1);
	 strcat (xteds.xTEDS,MSG_RESULTS_2);
	 strcat (xteds.xTEDS,MSG_RESULTS_3);
	 strcat (xteds.xTEDS,REQUEST_END);
	 strcat (xteds.xTEDS,INTERFACE_END);
	 strcat (xteds.xTEDS,XTEDS_END);

	 // set the id of this application
	 xteds.source.setSensorID(1);
	 //cancel.source.setSensorID(xteds.source.getSensorID());
	 //cancel.source.setPort(my_port);
	 xteds.source.setPort(my_port);
	 printf("Registering converter xTEDS on port %ld\n",my_port);
	 // register with the SDM
	 
	 SDMHello hello;
	 hello.source.setPort(my_port);
	 hello.type = 'A';
	 double endTime = 0;
	 while(registering)
	 {
		if(mm->IsReady())   //Listen for messages
		{
			switch(mm->GetMessage(buf))
			{
				case SDM_ACK:
					printf("SDMAck received acknowledging Hello\n");
					helloReceived = true;
					endTime = 0;
					break;
				case SDM_Register:
					printf("SDMRegister received\n");
					registerReceived = true;
					endTime = 0;
					break;
				case SDM_ID:
					printf("SDMID recieved, registration complete\n");
					idReceived = true;
					registering = false;
					break;
				default:
					break;
			}			
		}
		else
		{
			if(GetCurTime() > endTime)  //Check for timeouts
			{
				if(!helloReceived)  //Send Hello Msg
				{
					printf("Sending SDMHello\n");
					hello.Send();
					endTime = GetCurTime() + 5.0;
				}
				else if(registerReceived && !idReceived)  //Register xTEDS
				{
					xteds.Send();
					endTime = GetCurTime() + 10.0;
				}				
			}
		}
		usleep(1000);
	 }
}


void PerformRequest(char* buf)
{
	unsigned short int_data;
	float float_data;
	SDMSerreqst request;
	SDMData dat;
	
	request.Unmarshal(buf);
	// copy integer parameter into variable int_strain
	int_data = GET_SHORT(request.data);
	//  convert to float between 0 and 1
	float_data = int_data/(float)0xffff;
	printf("Converted %d to %f\n",int_data,float_data);
	dat.source = request.source;
	// fill in other fields
	dat.msg_id = request.reply_id;
	// convert float_data to raw data bytes
	PUT_FLOAT(dat.msg, float_data);
	printf("Sending reply.\n");
	// return to requester
	dat.Send (request.destination,4);
}

double GetCurTime()
{
	struct timespec tv;
	int tv_usec;
	clock_gettime(CLOCK_REALTIME, &tv);
	tv_usec = tv.tv_nsec/1000;
	return tv.tv_sec + ((double)tv_usec/1000000.0);
}

void CancelxTEDS()
{
	SDMCancelxTEDS cancel;
	printf("Canceling xTEDS\n");
	cancel.source.setSensorID(1);
	cancel.source.setPort(my_port);
	cancel.Send();
}
