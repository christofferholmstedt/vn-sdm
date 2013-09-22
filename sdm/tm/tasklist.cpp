// TaskList implementation file

#include "tasklist.h"
#include "../common/Exception/SDMBadIndexException.h"
#include "../common/message/SDMTaskError.h"
#include <string.h>
#include <unistd.h>
#include <stdio.h>

TaskList::TaskList()
{	Init();
}

void TaskList::Init()
{
	for (int n=0; n<NUMTASKS; n++)
	{	tasks[n].InitTask();
	}
}

bool TaskList::AnyInactive()
{
	for (int n=0; n<NUMTASKS; n++)
		if (tasks[n].state == INACTIVE)
			return true;
	return false;
}

bool TaskList::AnyPending()
{
	for (int n=0; n<NUMTASKS; n++)
		if (tasks[n].state == PENDING)
			return true;
	return false;
}

bool TaskList::AddTo(const Task& t)
{
	int n;
	if (!AnyInactive()) return false;
	else
	{
		for (n=0; n<NUMTASKS && tasks[n].state != INACTIVE; n++) ;
		if (n >= NUMTASKS) return false;
		else tasks[n] = t;
	}
	return true;
}

bool TaskList::RemoveFrom(unsigned int p)	// remove task by pid
{
	int n;
	for (n=0; n<NUMTASKS && tasks[n].pid != p; n++) ;
	if (n >= NUMTASKS) return false;
	else tasks[n].Delete();
	return true;
}

bool TaskList::RemoveFrom(char *filename)
{
	int n;
	if (filename == NULL)
		return false;
	for (n=0; n<NUMTASKS; n++)
	{
		if (tasks[n].filename != NULL)
			if (!strcmp(tasks[n].filename, filename))
				break;
	}
	if (n >= NUMTASKS)
		return false;
	else
		tasks[n].Delete();
	return true;
}

/*
  Perform whatever cleanup is needed when a PM reports that a task is finished.
  Take the following actions depending on the task's mode:
    MODE_NORMAL -- The task is finished, remove it from the list.
    MODE_ALWAYS_RUNNING -- The task probably faulted, reschedule it.
 */
bool TaskList::TaskFinished(unsigned int a_uiPid)
{
  int n = 0;
  bool bFound = false;
  bool bResult = false;

  // Find the finished task
  for (n = 0; n < NUMTASKS; n++)
    {
      if (tasks[n].pid == a_uiPid)
	{
	  bFound = true;
	  break;
	}
    }

  // If the task wasn't found, return error
  if (false == bFound)
    {
      return false;
    }

  // Otherwise, n is the index of the task
  switch(tasks[n].taskMode)
    {
    case MODE_NORMAL:
      // Remove the task from the list
      bResult = RemoveFrom(a_uiPid);
      break;
    case MODE_ALWAYS_RUNNING:
      // Set the task to be rescheduled, remove its pid
      tasks[n].state = PENDING;
      tasks[n].pid = 0;
      bResult = true;
      break;
    default:
      printf("%s -- Invalid mode option.\n", __FUNCTION__);
      break;
    }

  return bResult;
}

void TaskList::ClearList()
{
	for (int n = 0; n < NUMTASKS; n++)
	{
		tasks[n].Delete();
	}
}

bool TaskList::IsFilePresent(char *f)
{
	int n;
	for (n=0; n<NUMTASKS; n++)
		if (tasks[n].filename != NULL)
			if (!strcmp(f, tasks[n].filename))
				return true;
	return false;
}

unsigned int TaskList::SetState (unsigned int p, char state)			// set state by pid
{
	int n;
	for (n=0; n<NUMTASKS; n++)
		if (tasks[n].pid == p)
		{	tasks[n].state = state;
			if (state == FINISHED)
				tasks[n].pid = PID_INVALID;
			return tasks[n].pid;
		}
	return 0;
}

/*bool MatchResources (int pmResources, int taskResources)		// verify pmResources <= taskResources
{
	if ((taskResources & PMIDMASK) != 0)
		if ((pmResources & PMIDMASK) != (taskResources & PMIDMASK))
			return false;
	
	if ((pmResources & ARCHMASK) == (taskResources & ARCHMASK))
		if ((pmResources & MEMMASK) >= (taskResources & MEMMASK))
			if ((pmResources & OSMASK) == (taskResources & OSMASK))
				return true;
	return false;
}*/

// Find a pending task in the list
int TaskList::FindPendingTask(Task& taskOut)
{
	for (int n = 0; n < NUMTASKS; n++)
	{
		if (tasks[n].state == PENDING)
		{
			taskOut = tasks[n];
			return n;
		}
	}
	return -1;
}

// Only match PENDING tasks (tasks that have not been scheduled)
bool TaskList::FindPendingMatch (int resources, unsigned int newPID, Task& taskOut)
{
	int n, lastpos;
	bool success = false;
	taskOut.InitTask();
	lastpos=0;
	for (n=0; n<NUMTASKS && !success; n++)
	{	if (tasks[n].state == PENDING)
			if (SDMTaskResources::MatchResources (resources, tasks[n].resources))
				if (tasks[n].priority >= taskOut.priority)
				{
					tasks[n].pid = newPID;
					taskOut = tasks[n];
					success = true;
					lastpos = n;
				}
	}
	return success;
}

bool TaskList::SetAddress(unsigned int p, const SDMComponent_ID& PM)
{
	int n;
	bool found = false;
	for (n=0; n<NUMTASKS && !found; n++)
	{
		if (tasks[n].pid == p)
		{
			tasks[n].SetPM(PM);
			return true;
		}
	}
	return false;
}

void TaskList::RemovePreferredPmId(const SDMTaskResources& TaskResources)
{
	for (int n = 0; n < NUMTASKS; n++)
	{
		if (tasks[n].state != INACTIVE && tasks[n].resources.GetPreferredPmId() == TaskResources.GetPreferredPmId())
			tasks[n].resources.SetPreferredPmNodeId(0);
	}
}

unsigned int TaskList::FindPID(const char* filename)
{
	if (filename == NULL)
		return PID_INVALID;
	for (int n = 0; n < NUMTASKS; n++)
	{
		if (tasks[n].state == SCHEDULED && tasks[n].filename != NULL && strcmp(tasks[n].filename, filename)==0)
		{
			return tasks[n].pid;
		}
	}
	return PID_INVALID;
}

// This PM has failed, set all tasks to PENDING and cancel their xTEDS
void TaskList::PMFailure(const SDMComponent_ID& PMID)
{
  SDMTaskError msgError;
  msgError.source = PMID;
  for (int n = 0; n < NUMTASKS; n++)
    {
      if (tasks[n].GetPM() == PMID)
	{
	  msgError.source.setSensorID(tasks[n].pid);
	  msgError.pid = tasks[n].pid;
	  msgError.Send();

	  tasks[n].state = PENDING;
	}
    }
}

void TaskList::PrintList()
{
	printf("\n***Task List is:\n");
	for (int n = 0; n < NUMTASKS; n++)
	{
		if (tasks[n].state != INACTIVE)
		{
			char StateStr[16];
			switch(tasks[n].state)
			{
				case INACTIVE:
					strncpy(StateStr, "INACTIVE", sizeof(StateStr)); break;
				case ACTIVE:
					strncpy(StateStr, "ACTIVE", sizeof(StateStr)); break;
				case ASSIGNED:
					strncpy(StateStr, "ASSIGNED", sizeof(StateStr)); break;
				case SCHEDULED:
					strncpy(StateStr, "SCHEDULED", sizeof(StateStr)); break;
				case PENDING:
					strncpy(StateStr, "PENDING", sizeof(StateStr)); break;
				case FINISHED:
					strncpy(StateStr, "FINISHED", sizeof(StateStr)); break;
			}
			printf("  Index %d: name: %s pid: %d state: %s priority: %hhd resources: %hd timeout: %d mode: %d version: %d\n",n,tasks[n].filename, tasks[n].pid, StateStr, tasks[n].priority, tasks[n].resources.GetUShort(), tasks[n].timeout, tasks[n].taskMode, tasks[n].taskVersion);
		}
	}
	printf ("***\n\n");
}

SDMComponent_ID TaskList::GetPMAddress(unsigned int pid)
{
	for (int n = 0; n < NUMTASKS; n++)
	{
		if (tasks[n].pid == pid)
		{
			return tasks[n].GetPM();
		}
	}
	return SDMComponent_ID();
}

 Task& TaskList::operator[] (int index)
{
	if (index < 0 || index >= NUMTASKS)
		throw SDMBadIndexException(__FUNCTION__);
	
	if (tasks[index].state == INACTIVE)
		throw SDMBadIndexException(__FUNCTION__);
	
	return tasks[index];
}

unsigned int TaskList::FillTaskListBlob(char* pBuffer, unsigned int uiBufferSize)
{
  return FillTaskListBlob(pBuffer, uiBufferSize, TASKS_ALL);
}

unsigned int TaskList::FillTaskListBlobRunningOnly (char* pBuffer, unsigned int uiBufferSize)
{
  return FillTaskListBlob(pBuffer, uiBufferSize, TASKS_RUNNING);
}

/*
 *  Fill a "blob" buffer of the tasks specified in eTaskSet.  The blob consists of
 *  each task's SDM pid and their task name stored sequentially in pBuffer.  Each
 *  entry is null terminated by the task name, and the last entry is double
 *  null terminated.
 */
unsigned int TaskList::FillTaskListBlob(char* pBuffer, unsigned int uiBufferSize, TaskSet eTaskSet)
{
  unsigned int uiCurOffset = sizeof(unsigned short);
  unsigned int uiBytesRemaining = uiBufferSize - 2; // Include double null term
  unsigned short usNumTasks = 0;
  char strFormatString[512];

  for (int n = 0; n < NUMTASKS; n++)
    {
      if (tasks[n].state == INACTIVE)
	continue;

      switch(eTaskSet)
	{
	case TASKS_RUNNING:
	  // TODO:  "Scheduled" really means "running" this should be changed
	  if (SCHEDULED != tasks[n].state)
	    break;

	  // else fall through
	case TASKS_ALL:
	  {
	    snprintf(strFormatString, sizeof(strFormatString), "%-8u%s\n", tasks[n].pid, tasks[n].filename);
	    unsigned int uiCurEntryLength = strlen(strFormatString);

	    if (uiCurOffset + uiCurEntryLength < uiBytesRemaining)
	      {
		strcpy(&pBuffer[uiCurOffset], strFormatString);
		
		uiCurOffset += uiCurEntryLength;
		uiBytesRemaining -= uiCurEntryLength;
		usNumTasks++;
	      }
	  }
	  break;
	default:
	  printf("%s -- Invalid TaskSet.\n", __FUNCTION__);
	  return 0;
	}
    }
  PUT_USHORT(&pBuffer[0], usNumTasks);

  pBuffer[uiCurOffset++] = '\0';

  return uiCurOffset;
}

unsigned int TaskList::FillTaskInfoRequest(unsigned int uiPid, char* pBuffer, unsigned int uiBufferSize)
{
  // Find the task
  int iTaskIndex = 0;
  for ( ; iTaskIndex < NUMTASKS; iTaskIndex++)
    {
      if (tasks[iTaskIndex].state == INACTIVE)
	{
	  continue;
	}
      else if (tasks[iTaskIndex].pid == uiPid)
	{
	  // Found
	  break;
	}
    }
  if (iTaskIndex >= NUMTASKS)
    {
      // Not found
      return 0;
    }

  //
  // Put the task name
  unsigned int uiCurBufferOffset = 0;
  strcpy(pBuffer + uiCurBufferOffset, tasks[iTaskIndex].filename);
  uiCurBufferOffset += XTEDS_MAX_TASK_NAME_SIZE;
  //
  // Put the architecture type, in xTEDS enum form
  switch( tasks[iTaskIndex].resources.GetArch() )
    {
    case SDM_INTEL:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], ARCH_TYPE_INTEL );
      break;
    case SDM_MICROBLAZE:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], ARCH_TYPE_MICROBLAZE );
      break;
    default:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], 0 );
    }
  uiCurBufferOffset += sizeof(char);
  //
  // Put the OS type
  switch( tasks[iTaskIndex].resources.GetOs() )
    {
    case SDM_LINUX26:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], OS_TYPE_LINUX26 );
      break;
    case SDM_WIN32:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], OS_TYPE_WIN32 );
      break;
    default:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], 0 );
    }
  uiCurBufferOffset += sizeof(char);
  // 
  // Put the memory type
  switch( tasks[iTaskIndex].resources.GetMem() )
    {
    case SDM_MEM64:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], MEM_TYPE_64 );
      break;
    case SDM_MEM128:      
      PUT_CHAR( &pBuffer[uiCurBufferOffset], MEM_TYPE_128 );     
      break;
    case SDM_MEM256:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], MEM_TYPE_256 );
      break;
    case SDM_MEM512:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], MEM_TYPE_512 );
      break;
    default:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], 0 );
    }
  uiCurBufferOffset += sizeof(char);
  //
  // Put the PM id
  PUT_UCHAR( &pBuffer[uiCurBufferOffset], tasks[iTaskIndex].resources.GetPreferredPmIdNum() );
  uiCurBufferOffset += sizeof(char);
  //
  // Put the task state
  switch( tasks[iTaskIndex].state )
    {
    case SCHEDULED:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], TASK_STATE_SCHEDULED );
      break;
    case PENDING:
      // Queued
      PUT_CHAR( &pBuffer[uiCurBufferOffset], TASK_STATE_QUEUED );
      break;
    case FINISHED:
      // Stopped
      PUT_CHAR( &pBuffer[uiCurBufferOffset], TASK_STATE_STOPPED );
      break;
    case RUNNING:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], TASK_STATE_RUNNING );
      break;
    default:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], 0 );
    }
  uiCurBufferOffset += sizeof(char);
  //
  // Put the task mode
  switch( tasks[iTaskIndex].taskMode )
    {
    case MODE_NORMAL:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], EXECUTION_MODE_NORMAL );
      break;
    case MODE_ALWAYS_RUNNING:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], EXECUTION_MODE_ALWAYS_RUNNING );
      break;
    default:
      PUT_CHAR( &pBuffer[uiCurBufferOffset], 0 );
    }
  uiCurBufferOffset += sizeof(char);
  
  return uiCurBufferOffset;
}
