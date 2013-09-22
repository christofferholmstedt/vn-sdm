#include "../../common/message/SDMmessage.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/UDPcom.h"
#include "../../common/message_defs.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

void nullrequest_test(void);
void badquallist_test(void);
void badreply(void);
void repeat_test(void);

int main(int argc, char** argv)
{
	SDMInit(argc,argv);
	nullrequest_test();
	badquallist_test();
	badreply();
	repeat_test();
}

//null request sends a SDMReqReg message with no itemname and no quallist
void nullrequest_test(void)
{
	SDMReqReg request;
	request.reply = SDM_REQREG_CURRENT;
	request.destination.setPort(0);
	request.id = 0;
	memset(request.item_name,'\0',81);
	memset(request.quallist,'\0',100);
	printf("Starting null request test\n");
	request.Send();
	printf("Test Finished\n");
	sleep(5);
}

//badquallist sends a SDMReqReg message with bad quallists
void badquallist_test(void)
{
	SDMReqReg request;
	request.reply = SDM_REQREG_CURRENT;
	request.destination.setPort(0);
	request.id = 0;
	memset(request.item_name,'\0',81);
	printf("Starting bad quallist test\n");
	strcpy(request.quallist,"HELLO WORLD!");
	request.Send();
	strcpy(request.quallist,"HELLO WORLD!/>");
	request.Send();
	strcpy(request.quallist,"<HELLO WORLD!/>");
	request.Send();
	strcpy(request.quallist,"</>");
	request.Send();
	for(int j=0;j<10;++j)
	{
		for(int i=0;i<100;++i)
			request.quallist[i] = rand() % 256;
		request.Send();
	}
	printf("Test Finished\n");
	sleep(5);
}

//badreply tried all the possible reply values
void badreply(void)
{
	SDMReqReg request;
	request.destination.setPort(4000);
	strcpy(request.item_name,"Deregistration");
	strcpy(request.quallist,"</>");
	printf("Starting bad reply test\n");
	for(int i=0;i<256;++i)
	{
		request.reply = i;
		request.id = i;
		request.Send();
	}
	printf("Test Finished\n");
	sleep(5);
}

//repeat test sends multiple copies of the same request thing to overflow a buffer
void repeat_test(void)
{
	SDMReqReg request;
	request.destination.setPort(4000);
	request.id = 1;
	request.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
	strcpy(request.item_name,"Deregistration");
	strcpy(request.quallist,"</>");
	printf("Starting repeat test\n");
	for(int i=0;i<50;++i)
		request.Send();
	printf("Test Finished\n");
	sleep(5);
}
