#include "pm_record_list.h"
#include "task.h"
#include <stdio.h>

PMRecordList::PMRecordList(): schedulerInfoIndex(0), DataMutex()
{
	pthread_mutex_init(&DataMutex, NULL);
	for (unsigned int i = 0; i < MAX_PM; i++)
		HeartbeatStatus[i] = 0;
}

// Determine whether a PM with the same address is already in the list
bool PMRecordList::AlreadyRegistered(const SDMComponent_ID& PMAddress, const SDMTaskResources& Resources)
{
	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (pmList[i].in_use)
		{
			if (pmList[i].component_id.getAddress() == PMAddress.getAddress())
			{
				pthread_mutex_unlock(&DataMutex);
				return true;
			}
			if (Resources.IsPreferredPmIdSet())
			{
				if (pmList[i].resources.GetPreferredPmId() == Resources.GetPreferredPmId())
					printf("Warning:  Multiple PM's registered with same PM node ID.\n");
			}
		}
	}
	pthread_mutex_unlock(&DataMutex);
	return false;
}

bool PMRecordList::RegisterPM(const SDMComponent_ID& PMAddress, const SDMTaskResources& Resources)
{
	// Find an unused PM entry
	unsigned int i;

	pthread_mutex_lock(&DataMutex);
	for (i = 0; i < MAX_PM; i++)
	{
		if (!pmList[i].in_use)
			break;
	}
	if (i == MAX_PM)
	{
		pthread_mutex_unlock(&DataMutex);
		return false;	// No more entries available
	}

	pmList[i].in_use = true;
	pmList[i].tasks = 0;
	pmList[i].resources = Resources;
	pmList[i].component_id = PMAddress;
	// Pms always have PORT_PM
	pmList[i].component_id.setPort(PORT_PM);

	pthread_mutex_unlock(&DataMutex);
	return true;
}

// Clears all running tasks for each PM, useful for when TM resets
void PMRecordList::ClearAllRunningTasks()
{
	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		// No need to check for in_use, setting all to zero will have no negative effect
		pmList[i].tasks = 0;
	}
	pthread_mutex_unlock(&DataMutex);
}

// Decrement the number of running tasks for the given PM
bool PMRecordList::TaskFinished(const SDMComponent_ID& PMAddress)
{
	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (pmList[i].in_use && pmList[i].component_id.getAddress() == PMAddress.getAddress())
		{
			pmList[i].tasks--;
			pthread_mutex_unlock(&DataMutex);
			return true;
		}
	}
	pthread_mutex_unlock(&DataMutex);
	return false;
}

bool PMRecordList::TaskHasStarted(const SDMComponent_ID& PMAddress)
{
	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (pmList[i].in_use && pmList[i].component_id.getAddress() == PMAddress.getAddress())
		{
			pmList[i].tasks++;
			pthread_mutex_unlock(&DataMutex);
			return true;
		}
	}
	pthread_mutex_unlock(&DataMutex);
	return false;
}

bool PMRecordList::FindPMID(const SDMTaskResources& TaskResources, pm_record& PmDataOut)
{
	if (!TaskResources.IsPreferredPmIdSet())
		return false;

	// Otherwise, find the PM with the matching id
	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (TaskResources.GetPreferredPmId() == pmList[i].resources.GetPreferredPmId())
		{
			PmDataOut = pmList[i];
			pthread_mutex_unlock(&DataMutex);
			return true;
		}
	}
	pthread_mutex_unlock(&DataMutex);

	// The preferred PM has not registered
	return false;
}

// Find an eligible PM for scheduling and return it in PmDataOut.  A PM is only eligible if its
// number of running tasks is no greater than NumTasks.  Keep the scheduler index as a member
// variable to prevent looking at the same PM if the resources don't allow a schedule match.
bool PMRecordList::FindEligiblePM(int NumTasks, const SDMTaskResources& TaskResources, pm_record& PmDataOut)
{
	ushort taskResources = TaskResources.GetIgnorePmId();
	ushort taskArchOs = taskResources&(ARCHMASK|OSMASK);
	pthread_mutex_lock(&DataMutex);
	for (; schedulerInfoIndex < MAX_PM; schedulerInfoIndex++)
	{
		ushort pmResources = pmList[schedulerInfoIndex].resources.GetIgnorePmId();
		if (pmList[schedulerInfoIndex].in_use && pmList[schedulerInfoIndex].tasks <= NumTasks &&
		   (pmResources&(ARCHMASK|OSMASK)) == taskArchOs && (pmResources&MEMMASK) >= (taskResources&MEMMASK) )
		{
			PmDataOut = pmList[schedulerInfoIndex];
			schedulerInfoIndex++;
			pthread_mutex_unlock(&DataMutex);
			return true;
		}
	}
	if (schedulerInfoIndex >= MAX_PM)
		schedulerInfoIndex = 0;

	pthread_mutex_unlock(&DataMutex);
	return false;
}

int PMRecordList::SendHeartbeatToAll(SDMHeartbeat& HeartbeatMessage)
{
	int numSent = 0;

	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (pmList[i].in_use)
		{
			HeartbeatMessage.SendTo(pmList[i].component_id);
			HeartbeatStatus[i]++;
			numSent++;
		}
		else
		{
			HeartbeatStatus[i] = HEARTBEAT_INACTIVE;
		}
	}
	pthread_mutex_unlock(&DataMutex);
	return numSent;
}

void PMRecordList::SendToAll(SDMmessage& message)
{
	pthread_mutex_lock(&DataMutex);

	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (pmList[i].in_use)
		{
			message.SendTo(pmList[i].component_id);
		}
	}

	pthread_mutex_unlock(&DataMutex);
}

void PMRecordList::HeartbeatReceived(const SDMComponent_ID& PMAddress)
{
	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (pmList[i].in_use && pmList[i].component_id.getAddress() == PMAddress.getAddress())
			HeartbeatStatus[i] = 0;
	}
	pthread_mutex_unlock(&DataMutex);
}

bool PMRecordList::RemoveAnyFailed(pm_record &PMNodeOut)
{
	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (pmList[i].in_use && HeartbeatStatus[i] >= 2)
		{
			// This node has failed
			PMNodeOut = pmList[i];
			pmList[i].in_use = false;
			pmList[i].tasks = 0;
			pmList[i].resources = 0;
			pthread_mutex_unlock(&DataMutex);
			return true;
		}
	}
	pthread_mutex_unlock(&DataMutex);
	return false;
}

int PMRecordList::GetTasks(const SDMComponent_ID& PMAddress)
{
	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (pmList[i].in_use && pmList[i].component_id.getAddress() == PMAddress.getAddress())
		{
			int iCurTasks = pmList[i].tasks;
			pthread_mutex_unlock(&DataMutex);
			return iCurTasks;
		}
	}
	pthread_mutex_unlock(&DataMutex);
	return 0;
}

bool PMRecordList::IsEmpty()
{
	bool bAnyFound = false;
	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (pmList[i].in_use)
		{
			bAnyFound = true;
			break;
		}
	}
	pthread_mutex_unlock(&DataMutex);

	return !bAnyFound;
}

void PMRecordList::SetTasks(const SDMComponent_ID& PMAddress, int NumTasks)
{
	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (pmList[i].in_use && pmList[i].component_id.getAddress() == PMAddress.getAddress())
			pmList[i].tasks = NumTasks;
	}
	pthread_mutex_unlock(&DataMutex);
}

void PMRecordList::PrintList()
{
	printf("***PMRecordList is\n");

	pthread_mutex_lock(&DataMutex);
	for (unsigned int i = 0; i < MAX_PM; i++)
	{
		if (pmList[i].in_use)
		{
			char ID[128];
			pmList[i].component_id.IDToString(ID, sizeof(ID));
			printf("  Index %u: %s tasks: %hd resources: %hu\n",i,ID,pmList[i].tasks,pmList[i].resources.GetUShort());
		}
	}
	pthread_mutex_unlock(&DataMutex);
	printf("***\n\n");
}

