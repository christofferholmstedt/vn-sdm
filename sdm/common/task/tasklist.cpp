// TaskList implementation file

#include "tasklist.h"
#include "../Exception/SDMBadIndexException.h"
#include "../message/SDMTaskError.h"
#include <string.h>
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
			printf("  Index %d: name: %s pid: %d state: %s priority: %hhd resources: %hd timeout: %d mode: %d\n",n,tasks[n].filename, tasks[n].pid, StateStr, tasks[n].priority, tasks[n].resources.GetUShort(), tasks[n].timeout, tasks[n].taskMode);
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
	if (index < 0 || index > NUMTASKS)
		throw SDMBadIndexException(__FUNCTION__);
	
	if (tasks[index].state == INACTIVE)
		throw SDMBadIndexException(__FUNCTION__);
	
	return tasks[index];
}

