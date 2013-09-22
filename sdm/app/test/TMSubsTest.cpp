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
#include "../../common/message/SDMCommand.h"
#include "../../common/MessageManager/MessageManager.h"

#define TMSUB_STATUS		1
#define TMSUB_TASKQUEUED 	2
#define TMSUB_TASKSTARTED	3
#define TMSUB_TASKFINISHED	4
#define TMSER_NAMETOPID		5
#define TMDAT_NAMETOPID		8
#define TMCMD_KILLTASK		6
#define TMCMD_STARTTASK		7
#define TMSER_TASKLIST          10
#define TMSER_TASKLISTREPLY     11
#define TMSER_RUNNINGTASKLIST   9
#define TMSER_RUNNINGTASKLISTREPLY 12
#define TMSER_TASKINFO   13
#define TMSER_TASKINFOREPLY 14

using namespace std;

SDMMessage_ID status_id;
SDMMessage_ID queued_id;
SDMMessage_ID started_id;
SDMMessage_ID finished_id;
SDMMessage_ID nametopid_id;
SDMMessage_ID nametopidreply_id;
SDMMessage_ID starttask_id;
SDMMessage_ID killtask_id;
SDMMessage_ID tasklist_id;
SDMMessage_ID tasklistreply_id;
SDMMessage_ID runningtasklist_id;
SDMMessage_ID runningtasklistreply_id;
SDMMessage_ID taskinfo_id;
SDMMessage_ID taskinforeply_id;

const int my_port = 4999;
bool providers_found = false;
vector<long> sensor_ids;
vector<SDMComponent_ID> comp_ids;
SDMComponent_ID TMID;
int signals_recd;
bool convert_name_ready = false;
const char* START_TASKNAME = "messagecountconsumer";
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
		case TMSUB_STATUS:
			printf("Task manager's Status subscription found, subscribing...\n");
			status_id = reg.msg_id;
			TMID = reg.source;
			consume.Send();
			providers_found = true;
			break;
		case TMSUB_TASKQUEUED:
			printf("Task manager's TaskQueued subscription found, subscribing...\n");
			queued_id = reg.msg_id;
			TMID = reg.source;
			consume.Send();
			providers_found = true;
			break;
		case TMSUB_TASKSTARTED:
			printf("Task manager's TaskStarted subscription found, subscribing...\n");
			started_id = reg.msg_id;
			TMID = reg.source;
			consume.Send();
			providers_found = true;
			break;
		case TMSUB_TASKFINISHED:
			printf("Task manager's TaskFinished subscription found, subscribing...\n");
			finished_id = reg.msg_id;
			TMID = reg.source;
			consume.Send();
			providers_found = true;
			break;
		case TMSER_NAMETOPID:
			printf("Task manager's NameToPID subscription found, subscribing...\n");
			nametopid_id = reg.msg_id;
			TMID = reg.source;
			providers_found = true;
			break;
		case TMDAT_NAMETOPID:
			nametopidreply_id = reg.msg_id;
			break;
		case TMCMD_STARTTASK:
			printf("Task manager's StartTask subscription found, subscribing...\n");
			starttask_id = reg.msg_id;
			break;
		case TMCMD_KILLTASK:
			printf("Task manager's KillTask subscription found, subscribing...\n");
			killtask_id = reg.msg_id;
			break;
	case TMSER_TASKLIST:
	  printf("Found task list request.\n");
	  tasklist_id = reg.msg_id;
	  break;
	case TMSER_TASKLISTREPLY:
	  tasklistreply_id = reg.msg_id;
	  break;
	case TMSER_RUNNINGTASKLISTREPLY:
	  runningtasklistreply_id = reg.msg_id;
	  break;
	case TMSER_RUNNINGTASKLIST:
	  printf("Found running task list request.\n");
	  runningtasklist_id = reg.msg_id;
	  break;
	case TMSER_TASKINFO:
	  printf("Found task info request.\n");
	  taskinfo_id = reg.msg_id;
	  break;
	case TMSER_TASKINFOREPLY:
	  taskinforeply_id = reg.msg_id;
	  break;
		default:
			printf("Received unexpected Reg Info type.\n");
	}
}

void SendRegReqs()
{
	SDMReqReg request;
	request.destination.setPort(my_port);
	strcpy(request.interface, "TM_Interface");
	
	printf("Sending request for the Status subscription.\n");
	request.id = TMSUB_STATUS;
	strcpy(request.item_name, "Status");
	request.Send();
	
	printf("Sending request for the TaskQueued subscription.\n");
	request.id = TMSUB_TASKQUEUED;
	strcpy(request.item_name, "TaskQueued");
	request.Send();
	
	printf("Sending request for the TaskStarted subscription.\n");
 	request.id = TMSUB_TASKSTARTED;
	strcpy(request.item_name, "TaskStarted");
	request.Send();
	
	printf("Sending request for TaskFinshed subscription.\n\n");
	strcpy(request.item_name, "TaskFinished");
	request.id = TMSUB_TASKFINISHED;
	request.Send();
	
	printf("Sending request for Task name to PID service.\n\n");
	strcpy(request.item_name, "NameToPID");
	request.id = TMSER_NAMETOPID;
	request.Send();
	
	strcpy(request.item_name, "TaskPID");
	request.id = TMDAT_NAMETOPID;
	request.Send();
	
	printf("Sending request for start task command.\n\n");
	strcpy(request.item_name, "StartTask");
	request.id = TMCMD_STARTTASK;
	request.Send();
	
	printf("Sending request for kill task command.\n\n");
	strcpy(request.item_name, "KillTask");
	request.id = TMCMD_KILLTASK;
	request.Send();

	printf("Sending request for task list command.\n\n");
	strcpy(request.item_name, "GetTaskList");
	request.id = TMSER_TASKLIST;
	request.Send();

	printf("Sending request for running task list command.\n\n");
	strcpy(request.item_name, "GetRunningTaskList");
	request.id = TMSER_RUNNINGTASKLIST;
	request.Send();

	printf("Sending request for running task list command.\n\n");
	strcpy(request.item_name, "RunningTaskListReply");
	request.id = TMSER_RUNNINGTASKLISTREPLY;
	request.Send();

	printf("Sending request for running task list command.\n\n");
	strcpy(request.item_name, "TaskListReply");
	request.id = TMSER_TASKLISTREPLY;
	request.Send();
	
	printf("Sending request for getting task info.\n\n");
	strcpy(request.item_name, "GetTaskInfo");
	request.id = TMSER_TASKINFO;
	request.Send();

	strcpy(request.item_name, "TaskInfoReply");
	request.id = TMSER_TASKINFOREPLY;
	request.Send();
}

void DataHandler(SDMData data)
{
	unsigned char mode;
	int exit_status;
	char task_name[MAX_FILENAME_SIZE];
	SDMService request;
	bool PidRequest = false;
	printf("Data message received.\n");
	if (data.msg_id == status_id)
	{
		mode = GET_UCHAR(data.msg);
		printf("Status message received mode is %hd.\n", mode);
	}
	else if (data.msg_id == queued_id)
	{
		strncpy(task_name, data.msg, MAX_FILENAME_SIZE);
		printf("TaskQueued message received for task \"%s\".\n", task_name);
		//PidRequest = true;
		SDMService msgService;
		msgService.command_id = tasklist_id;
		msgService.source = TMID;
		msgService.destination.setPort(my_port);
		msgService.Send();
		printf("Sending task list request...\n");
	}
	else if (data.msg_id == started_id)
	{
		strncpy(task_name, data.msg, MAX_FILENAME_SIZE);
		unsigned int uiPid = GET_UINT(data.msg + MAX_FILENAME_SIZE);
		printf("TaskStarted message received for task \"%s\", pid %u\n", task_name, uiPid);
		if (strcmp(task_name, START_TASKNAME) == 0)
			PidRequest = true;
		SDMService msgService;
		msgService.command_id = runningtasklist_id;
		msgService.source = TMID;
		msgService.destination.setPort(my_port);
		msgService.Send();
		printf("Sending task list request...\n");

		printf("Sending task info request...\n");
		msgService.command_id = taskinfo_id;
		PUT_UINT(msgService.data, uiPid);
		msgService.length = sizeof(unsigned int);
		msgService.Send();
	}
	else if (data.msg_id == finished_id)
	{
		strncpy(task_name, data.msg, MAX_FILENAME_SIZE);
		unsigned int uiPid = GET_UINT(data.msg+MAX_FILENAME_SIZE);
		exit_status = GET_INT(data.msg+MAX_FILENAME_SIZE + sizeof(unsigned int));
		printf("TaskFinished message received for task \"%s\", pid %u, and returned %d.\n", task_name, uiPid, exit_status);
		
		//PidRequest = true;
	}
	else if (data.msg_id == nametopidreply_id)
	{
		int PID = GET_INT(data.msg + MAX_FILENAME_SIZE);
		printf("Received PID number %d for task %s.\n",PID, data.msg);
		
		printf("Killing task %s\n",data.msg);
		SDMCommand cmdMsg;
		cmdMsg.command_id = killtask_id;
		PUT_INT(cmdMsg.data, PID);
		cmdMsg.length = 4;
		cmdMsg.SendTo(data.source);
	}
	else if (data.msg_id == tasklistreply_id || data.msg_id == runningtasklistreply_id)
	  {
	    if (data.msg_id == tasklistreply_id)
	      printf("--- Task list is:\n");
	    else
	      printf("--- Running task list is:\n");
	    printf("%s\n",data.msg);
	    /*   unsigned int uiCurPid;
	    char strTaskName[512];
	    unsigned int uiCurOffset = 0;
	    bool bDoubleNullFound = false;

	    unsigned short usNumTasks = GET_USHORT(&data.msg[uiCurOffset]);
	    uiCurOffset += sizeof (unsigned short);

	    printf (" -- %hu items --\n", usNumTasks);
	    //while (!bDoubleNullFound)
	    for (unsigned short i = 0; i < usNumTasks; i++)
	      {
		uiCurPid = GET_UINT(&data.msg[uiCurOffset]);
		uiCurOffset += sizeof(uiCurPid);
		
		strcpy(strTaskName, &data.msg[uiCurOffset]);
		uiCurOffset += strlen(strTaskName) + 1;
		
		printf ("   Task \"%s\" pid %u\n", strTaskName, uiCurPid);
		}*/
	    printf(" ---- \n");
	  }
	else if (data.msg_id == taskinforeply_id)
	  {
	    char strTaskName[MAX_FILENAME_SIZE];
	    unsigned int uiCurBufferOffset = 0;
	    strcpy(strTaskName, data.msg);
	    uiCurBufferOffset += MAX_FILENAME_SIZE;

	    char cArchType = GET_CHAR( &data.msg[uiCurBufferOffset] );
	    uiCurBufferOffset += sizeof(char);

	    char cOsType = GET_CHAR(& data.msg[uiCurBufferOffset] );
	    uiCurBufferOffset += sizeof(char);
	   
	    char cMemType = GET_CHAR( &data.msg[uiCurBufferOffset] );
	    uiCurBufferOffset += sizeof(char);

	    unsigned char ucPmId = GET_UCHAR( &data.msg[uiCurBufferOffset] );
	    uiCurBufferOffset += sizeof(char);

	    char cTaskState = GET_CHAR( &data.msg[uiCurBufferOffset] );
	    uiCurBufferOffset += sizeof(char);

	    char cExecutionMode = GET_CHAR( &data.msg[uiCurBufferOffset] );
	    uiCurBufferOffset += sizeof(char);

	    printf("Task info reply received for %s-\n", strTaskName);
	    printf("  Arch: %hhd Os: %hhd Mem: %hhd\n", cArchType, cOsType, cMemType);
	    printf("  PmId: %hhd State: %hhd Mode: %hhd\n", ucPmId, cTaskState, cExecutionMode);
	  }
	if (PidRequest)
	{
		request.source = TMID;
		request.destination.setPort(my_port);
		request.command_id = nametopid_id;
		strcpy(request.data, data.msg);
		request.length = strlen(data.msg);
		request.Send();
	}
}

void SigHandler(int sig_num)
{
	SDMCancel cancel;
	cancel.source = comp_ids[0];
	cancel.destination.setPort(my_port);
	if (sig_num == SIGINT)
	{
		printf("Canceling subscriptions...");
		cancel.msg_id = status_id;
		cancel.Send();
		cancel.msg_id = queued_id;
		cancel.Send();
		cancel.msg_id = started_id;
		cancel.Send();
		cancel.msg_id = finished_id;
		cancel.Send();
		printf("Done.\n");
	}
	exit(EXIT_SUCCESS);
}
int main (int argc, char ** argv)
{
	char buf[BUFSIZE];
	long length;
	SDMRegInfo info;
	SDMData data;
	SDMInit(argc, argv);
	int Count = 0;
	MessageManager mm;
	mm.Async_Init(my_port);
	signal(SIGINT, SigHandler);
	
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
			sleep(1);
			/*	if (Count++ == 10)
			{
				printf("  Starting task %s...\n", START_TASKNAME);
				SDMCommand request;
				request.source = TMID;
				request.command_id = starttask_id;
				request.destination.setPort(my_port);
				const unsigned short ZERO = 0;
				PUT_USHORT(request.data, ZERO);
				PUT_INT(request.data + 2, 0);
				const unsigned int FILENAME_OFFSET = 6;
				strcpy(request.data + FILENAME_OFFSET, START_TASKNAME);
				request.length = 27;
				request.Send();
				Count = 0;
				}*/
		}
	}
	
	
	return 0;
}
