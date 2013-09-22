#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "../../common/message/SDMKill.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/message/SDMCommand.h"
#include "../../common/message/SDMService.h"
#include "../../common/message/SDMConsume.h"
#include "../../common/message/SDMData.h"
#include "../../common/MessageManipulator/MessageManipulator.h"
#include "../../common/MessageManager/MessageManager.h"

#define TM_NAME_TO_PID		1
#define TM_TASK_STARTED_MESSAGE 2

long myPort;

int main (int argc, char** argv)
{
	SDMInit(argc, argv);
	MessageManipulator TMNameToPID;
	MessageManipulator TMTaskStartedMessage;
	
	SDMComponent_ID TaskManagerID;
	
	MessageManager mm;
	myPort = getPort();
	if (myPort == SDM_PM_NOT_AVAILABLE)
	{
		printf("PM not available.\n");
		return -1;
	}
	mm.Async_Init(myPort);
	
	const char* TaskName = "producer";
	
	// Send the ReqReg for TM's name to SDM pid service
	SDMReqReg ReqReg;
	strcpy(ReqReg.item_name, "NameToPID");
	ReqReg.reply = SDM_REQREG_CURRENT;
	ReqReg.destination.setPort(myPort);
	ReqReg.id = TM_NAME_TO_PID;
	ReqReg.Send();
	
	// Send the ReqReg for TM's task started notification
	strcpy(ReqReg.item_name, "TaskStarted");
	ReqReg.id = TM_TASK_STARTED_MESSAGE;
	ReqReg.Send();
	
	char MessageBuffer[BUFSIZE];
	while (1)
	{
		char MessageType = mm.BlockGetMessage(MessageBuffer);
		switch(MessageType)
		{
			case SDM_RegInfo:
			{
				SDMRegInfo InfoReply;
				if (InfoReply.Unmarshal(MessageBuffer) == SDM_NO_FURTHER_DATA_PROVIDER)
					break;
				if (InfoReply.id == TM_TASK_STARTED_MESSAGE)
				{
					// Set the Message Manipulator
					TMTaskStartedMessage.setMsgDef(InfoReply);
					TaskManagerID = InfoReply.source;
					
					// Consume the task started notification
					SDMConsume Consume;
					Consume.source = InfoReply.source;
					Consume.msg_id = InfoReply.msg_id;
					Consume.destination.setPort(myPort);
					Consume.Send();
				}
				else if (InfoReply.id == TM_NAME_TO_PID)
				{
					// Set the Message Manipulator
					TMNameToPID.setMsgDef(InfoReply);
					TaskManagerID = InfoReply.source;
				}
			}
			break;
			case SDM_Data:
			{
				SDMData Data;
				Data.Unmarshal(MessageBuffer);
				if (Data.msg_id == TMTaskStartedMessage.getMsgID(DATAMSG))
				{
					int Length;
					char* MessageTaskName = (char*)TMTaskStartedMessage.getArray("TaskName", Data, DATAMSG, Length);
					if (MessageTaskName == NULL)
						break;
					// See if the task we want to kill was just queued
					if (strcmp(MessageTaskName, TaskName)==0)
					{
						// Request the task's SDM pid
						SDMService Service;
						Service.source = TaskManagerID;
						Service.destination.setPort(myPort);
						Service.command_id = TMNameToPID.getMsgID(COMMANDMSG);
						TMNameToPID.setArray("TaskName", Service, TaskName, strlen(TaskName)+1);
						Service.length = TMNameToPID.getLength(COMMANDMSG);
						Service.Send();
					}
				}
				else if (Data.msg_id == TMNameToPID.getMsgID(DATAMSG))
				{
					// Kill the received PID
					unsigned int PID = TMNameToPID.getUINT32Value("SDMTaskPID", Data, DATAMSG);
					printf("Killing pid %u\n",PID);
					SDMKill Kill;
					Kill.PID = PID;
					sleep(1);
					Kill.Send();
				}
			}
			break;
		}
		
	}
	return 0;
}
