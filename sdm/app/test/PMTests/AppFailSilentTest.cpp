#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../../common/MessageManager/MessageManager.h"
#include "../../../common/message/SDMReqReg.h"
#include "../../../common/message/SDMRegInfo.h"
#include "../../../common/message/SDMCommand.h"

long lMyPort;

void FindTMServices();
void DeleteTasks();
void CopyTasks();
void RegInfoHandler(const SDMRegInfo&); 

const int ID_START_TASK = 1;

SDMMessage_ID idStartTask;
SDMComponent_ID idTaskManager;

bool bFinish = false;

int main (int argc, char** argv)
{
	SDMInit(argc, argv);
	
	lMyPort = getPort();
	if (lMyPort == SDM_PM_NOT_AVAILABLE)
		lMyPort = 5432;
	
	MessageManager mm;
	mm.Async_Init(lMyPort);
	
	CopyTasks();
	FindTMServices();
	
	char buf[BUFSIZE];
	SDMRegInfo msgRegInfo;
	while (!bFinish)
	{
		if (mm.IsReady())
		{
			switch(mm.GetMessage(buf))
			{
				case SDM_RegInfo:
				{
					if (msgRegInfo.Unmarshal(buf) != SDM_NO_FURTHER_DATA_PROVIDER)
					{
						RegInfoHandler(msgRegInfo);
					}
					break;
				}
			}
		}
		else
			sleep(1);
	}
	
	return 0;
}

void RegInfoHandler(const SDMRegInfo& msgInfo)
{
	if (msgInfo.id == ID_START_TASK)
	{
		idStartTask = msgInfo.msg_id;
		idTaskManager = msgInfo.source;
		
		SDMCommand msgCommand;
		msgCommand.command_id = idStartTask;
		msgCommand.source = idTaskManager;
		strcpy(msgCommand.data + 2, "AppFailSilentTestConsumer");
		msgCommand.length = 28;
		
		printf("Starting AppFailSilentTestConsumer\n");
		msgCommand.Send();
		
		strcpy(msgCommand.data + 2, "AppFailSilentTestProducer");
		
		printf("Starting AppFailSilentTestProducer\n");
		msgCommand.Send();
		
		bFinish = true;
	}
	
	
}

void FindTMServices()
{
	SDMReqReg msgRequest;
	
	strcpy(msgRequest.device, "TaskManager");
	strcpy(msgRequest.item_name, "StartTask");
	msgRequest.id = ID_START_TASK;
	msgRequest.destination.setPort(lMyPort);
	msgRequest.Send();
}

void CopyTasks()
{
	system("cp AppFailSilentTestConsumer ../../../tm/.");
	system("cp AppFailSilentTestProducer ../../../tm/.");
}

void DeleteTasks()
{
	system("rm -f ../../../tm/AppFailSilentTestConsumer");
	system("rm -f ../../../tm/AppFailSilentTestProducer");
}

