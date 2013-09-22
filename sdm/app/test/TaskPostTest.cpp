#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "../../common/message/SDMCommand.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/MessageManager/MessageManager.h"
#include "../../common/MessageManipulator/MessageManipulator.h"
#include "../../common/task/taskdefs.h"
#include "../../tm/tm.h"


void RequestTmMessages();
void RegInfoHandler(void*);
int StartTaskMenu();

enum ReqRegIds { ID_START_TASK };

long g_lPort = 0;

//
// TM Data
SDMComponent_ID g_cidTaskManager;
//   StartTask data
SDMMessage_ID g_midStartTask;
MessageManipulator g_mmStartTask;
bool g_bStartTaskFound = false;


int main (int argc, char** argv)
{
  char msgBuf[BUFSIZE];
  MessageManager mm;

  SDMInit(argc, argv);

  if ((g_lPort = getPort()) == SDM_PM_NOT_AVAILABLE)
    {
      g_lPort = 7354; //Arbitrary
    }

  mm.Async_Init(g_lPort);

  printf("Finding TM messages.\n");
  RequestTmMessages();

  char cMessageType;
  while (false == g_bStartTaskFound)
    {
      if (mm.IsReady())
	{
	  cMessageType = mm.GetMessage(msgBuf);
	  switch(cMessageType)
	    {
	    case SDM_RegInfo:
	      RegInfoHandler(msgBuf);
	      break;
	    default:
	      printf("Unexpected message 0x%hhx (%c)\n", cMessageType, cMessageType);
	      break;
	    }
	}
      else
	{
	  sleep (1);
	}
    }

  while (0 != StartTaskMenu())
    ;

  return 0;
}

int StartTaskMenu()
{
  char strTaskName[128];
  printf ("Enter the name of the task to start (exit to exit): ");
  scanf ("%s", strTaskName);

  if (0 == strcmp(strTaskName, "exit"))
    return 0;
  
  char cAnswer;
  unsigned short usResources = SDM_INTEL | SDM_LINUX26 | SDM_MEM128 | PM_ID(3);
  int iMode = 1;
  char cArchType, cOsType, cMemType, cExecutionMode, cLoadLocation;

  
  printf ("Enter the Architecture type.\n");
  printf ("1)  ARCH_TYPE_INTEL\n");
  printf ("2)  ARCH_TYPE_MICROBLAZE\n");
  printf ("  : ");
  scanf ("%hhd", &cAnswer);
  switch (cAnswer)
    {
    case 1:
      cArchType = ARCH_TYPE_INTEL;
      break;     
    case 2:
      cArchType = ARCH_TYPE_MICROBLAZE;
      break;
    }
  
  printf("Enter the Operating system type.\n");
  printf("1)  OS_TYPE_LINUX26\n");
  printf("2)  OS_TYPE_WIN32\n");
  printf("  : ");
  scanf ("%hhd", &cAnswer);
  switch (cAnswer)
    {
    case 1:
      cOsType = OS_TYPE_LINUX26;
      break;
    case 2:
      cOsType = OS_TYPE_WIN32;
      break;
    }

  printf("Enter the memory type.\n");
  printf("1) MEM_TYPE_64\n");
  printf("2) MEM_TYPE_128\n");
  printf("3) MEM_TYPE_256\n");
  printf("4) MEM_TYPE_512\n");
  usResources |= SDM_MEM128;
  printf("  : ");
  scanf ("%hhd", &cAnswer);
  switch (cAnswer)
    {
    case 1:
      cMemType = MEM_TYPE_64;
      break;
    case 2:
      cMemType = MEM_TYPE_128;
      break;
    case 3:
      cMemType = MEM_TYPE_256;
      break;
    case 4:
      cMemType = MEM_TYPE_512;
      break;
    }

  printf("Enter the execution mode.\n");
  printf("1) EXECUTION_MODE_NORMAL\n");
  printf("2) EXECUTION_MODE_ALWAYS_RUNNING\n");
  printf("  : ");
  scanf ("%hhd", &cAnswer);
  switch (cAnswer)
    {
    case 1:
      cExecutionMode = EXECUTION_MODE_NORMAL;
      break;
    case 2:
      cExecutionMode = EXECUTION_MODE_ALWAYS_RUNNING;
      break;
    }

  printf("Enter the task load location.\n");
  printf("1) TASK_LOCATION_PRIMARY\n");
  printf("2) TASK_LOCATION_TEMPORARY\n");
  printf("3) TASK_LOCATION_BACKUP\n");
  printf("  : ");
  scanf("%hhd", &cAnswer);
  switch (cAnswer)
    {
    case 1:
      cLoadLocation = TASK_LOCATION_PRIMARY;
      break;
    case 2:
      cLoadLocation = TASK_LOCATION_TEMPORARY;
      break;
    case 3:
      cLoadLocation = TASK_LOCATION_BACKUP;
      break;
    }
  
  unsigned int uiBufferOffset = 0;
  // Put together the message
  SDMCommand msgCommand;
  msgCommand.source = g_cidTaskManager;
  msgCommand.command_id = g_midStartTask;
  msgCommand.length = g_mmStartTask.getLength(COMMANDMSG);
  strcpy(msgCommand.data, strTaskName);
  uiBufferOffset += XTEDS_MAX_TASK_NAME_SIZE;

  PUT_CHAR( &msgCommand.data[uiBufferOffset], cArchType);
  uiBufferOffset += sizeof(char);

  PUT_CHAR( &msgCommand.data[uiBufferOffset], cOsType);
  uiBufferOffset += sizeof(char);

  PUT_CHAR( &msgCommand.data[uiBufferOffset], cMemType);
  uiBufferOffset += sizeof(char);

  PUT_CHAR( &msgCommand.data[uiBufferOffset], cExecutionMode);
  uiBufferOffset += sizeof(char);

  PUT_CHAR( &msgCommand.data[uiBufferOffset], cLoadLocation);
  uiBufferOffset += sizeof(char);

  msgCommand.Send();
  return -1;
}

void RegInfoHandler(void* pMessageBuffer)
{
  char* pMessage = static_cast<char*>(pMessageBuffer);
  SDMRegInfo msgInfo;
 
  long lResult = 0;
  if ((lResult = msgInfo.Unmarshal(pMessage)) == SDM_NO_FURTHER_DATA_PROVIDER)
    {
      return;
    }
  else if (lResult < 0)
    {
      printf("Invalid SDMRegInfo message.\n");
      return;
    }

  if (msgInfo.id == ID_START_TASK)
    {
      if (msgInfo.type == SDM_REGINFO_REGISTRATION)
	{
	  g_mmStartTask.setMsgDef(msgInfo.msg_def);
	  g_midStartTask = msgInfo.msg_id;
	  g_cidTaskManager = msgInfo.source;
	  g_bStartTaskFound = true;
	}
      else if (msgInfo.type == SDM_REGINFO_CANCELLATION)
	{
	  g_bStartTaskFound = false;
	}
    }
}

void RequestTmMessages()
{
  SDMReqReg msgRequest;
  msgRequest.destination.setPort(g_lPort);
  strncpy(msgRequest.device, "TaskManager", sizeof(msgRequest.device));
  strncpy(msgRequest.item_name, "StartTask", sizeof(msgRequest.item_name));
  msgRequest.id = ID_START_TASK;
  msgRequest.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;

  msgRequest.Send();
}
