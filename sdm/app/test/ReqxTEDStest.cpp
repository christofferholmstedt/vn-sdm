#include "../../common/message/SDMmessage.h"
#include "../../common/message/SDMReqxTEDS.h"
#include "../../common/message/SDMxTEDSInfo.h"
#include "../../common/MessageManager/MessageManager.h"
#include "../../common/UDPcom.h"

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void ReplyTest(void);
void ReplyOnPortTest(void);
void BadNameTest(void);
void DMPortTest(void);

int main(int argc, char** argv)
{

	SDMInit(argc,argv);
	BadNameTest();
	DMPortTest();
	ReplyOnPortTest();
}

void ReplyOnPortTest(void)
{
	SDMReqxTEDS request;
	SDMxTEDSInfo info;
	char buf[BUFSIZE];
	long port = 4000;
	MessageManager mm;
	long length;
	
	mm.Async_Init(port);

	request.select = 2;
	request.source.setSensorID(1);
	strcpy(request.device_name,"DataManager");
	request.destination.setPort(port);
	printf("Starting reply on port test\n");
	request.Send();
	if (mm.BlockGetMessage(buf, length) == SDM_xTEDSInfo)
	{
		info.Unmarshal(buf);
		printf("Command Byte:%c id:%lu datalength:%ld",buf[0],info.source.getSensorID(),length);
		printf("\n%s\n",info.xTEDS);
		fflush(NULL);
	}

	sleep(1);

	request.select = 3;
	request.Send();
	if (mm.BlockGetMessage(buf,length) == SDM_xTEDSInfo)
	{
		info.Unmarshal(buf);
		printf("Command Byte:%c id:%lu datalength:%ld",buf[0],info.source.getSensorID(),length);
		printf("\n%s\n",info.xTEDS);
		fflush(NULL);
	}

	printf("Reply on port test done\n");
	fflush(NULL);
	sleep(5);
}

void BadNameTest(void)
{
	char msg[100];
	memset(msg,0,100);
	msg[0] = SDM_ReqxTEDS;
	msg[5] = 1;
	printf("Starting Bad Name Test\n");
	struct in_addr inaddr;
	inaddr.s_addr = DataManager.getAddress();
	UDPsendto(inet_ntoa(inaddr),PORT_DM,msg,100);
	printf("Bad Name Test done\n");
	fflush(NULL);
	sleep(5);
}

void DMPortTest(void)
{
	SDMReqxTEDS request;

	request.select = 2;
	request.source.setSensorID(1);
	strcpy(request.device_name,"DataManager");
	request.destination.setPort(PORT_DM);
	printf("Starting DM port test\n");
	request.Send();
	request.select = 3;
	request.Send();
	printf("DM port test done\n");
	fflush(NULL);
	sleep(5);
}
