#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/MessageManager/MessageManager.h"

#define LOGMSGID 1

int main(int argc, char* argv[])
{
	SDMInit(argc,argv);
	long my_port = getPort();
	MessageManager mm;
	bool cont = true;
	long result;
	char buf[BUFSIZE];
	long length = BUFSIZE;

	mm.Async_Init(my_port);
	sleep(1);
//_Test #1:_

       SDMReqReg   request;
       SDMRegInfo  info;
    // Let's find out where the DM is running.
    strcpy(request.device, "DataManager");
    //strcpy(request.interface, "Message_Log");
    //strcpy(request.item_name, "Enable_Logging");
    strcpy(request.quallist, "");
    request.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
    request.destination.setPort(my_port);
    request.id = LOGMSGID;
    request.Send();
	
    	printf("\n\n\nTest 1\n");
	while(cont)
	{
		if (mm.IsReady())
		{
			mm.GetMessage(buf,length);
			result = info.Unmarshal(buf);
			if(result == SDM_NO_FURTHER_DATA_PROVIDER)
				cont = false;
			if(cont == true)
			{
				memset(buf,0,BUFSIZE);
				if(info.MsgToString(buf,BUFSIZE) > 0)
					printf("recv'd: %s\n",buf);
			}			
		}	
	}

//_Test #2: _
	cont = true;
    // Let's find out where the DM is running.
    strcpy(request.device, "DataManager");
    //strcpy(request.interface, "Message_Log");
    strcpy(request.item_name, "Enable_Logging");
    strcpy(request.quallist, "");
    request.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
    request.destination.setPort(my_port);
    request.id = LOGMSGID;
    request.Send();

	printf("\n\n\nTest 2\n");
	while(cont)
	{
		if (mm.IsReady())
		{
			mm.GetMessage(buf,length);
			result = info.Unmarshal(buf);
			if(result == SDM_NO_FURTHER_DATA_PROVIDER)
				cont = false;
			if(cont == true)
			{
				memset(buf,0,BUFSIZE);
				if(info.MsgToString(buf,BUFSIZE) > 0)
					printf("recv'd: %s\n",buf);
			}			
		}	
	}
//_Test #3: _
	cont = true;
    // Let's find out where the DM is running.
    strcpy(request.device, "DataManager");
    strcpy(request.interface, "Message_Log");
    strcpy(request.item_name, "Enable_Logging");
    strcpy(request.quallist, "");
    request.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
    request.destination.setPort(my_port);
    request.id = LOGMSGID;
    request.Send();

	printf("\n\n\nTest 3\n");
	while(cont)
	{
		if (mm.IsReady())
		{
			mm.GetMessage(buf,length);
			result = info.Unmarshal(buf);
			if(result == SDM_NO_FURTHER_DATA_PROVIDER)
				cont = false;
			if(cont == true)
			{
				memset(buf,0,BUFSIZE);
				if(info.MsgToString(buf,BUFSIZE) > 0)
					printf("recv'd: %s\n",buf);
			}			
		}	
	}

//_Test #4: _
	cont = true;
    // Let's find out where the DM is running.
    strcpy(request.device, "DataManager");
    strcpy(request.interface, "Message_Log");
    //strcpy(request.item_name, "Enable_Logging");
	memset(request.item_name,0,33);
    strcpy(request.quallist, "");
    request.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
    request.destination.setPort(my_port);
    request.id = LOGMSGID;
    request.Send();

	printf("\n\n\nTest 4\n");
	while(cont)
	{
		if (mm.IsReady())
		{
			mm.GetMessage(buf,length);
			result = info.Unmarshal(buf);
			if(result == SDM_NO_FURTHER_DATA_PROVIDER)
				cont = false;
			if(cont == true)
			{
				memset(buf,0,BUFSIZE);
				if(info.MsgToString(buf,BUFSIZE) > 0)
					printf("recv'd: %s\n",buf);
			}			
		}	
	}

	request.reply = SDM_REQREG_CANCEL;
	request.Send();

	SDMReqReg reqreg;
	reqreg.reply = SDM_REQREG_CANCEL;
	reqreg.destination = request.destination;
	reqreg.Send();
}
