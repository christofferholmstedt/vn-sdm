#ifndef _SDM_PM_RECORD_LIST_H_
#define _SDM_PM_RECORD_LIST_H_

#include <pthread.h>
#include "pm_record.h"
#include "../common/message/SDMComponent_ID.h"
#include "../common/message/SDMHeartbeat.h"
#include "../common/task/SDMTaskResources.h"

#define HEARTBEAT_INACTIVE	-1
#define MAX_PM 8

// This class used to hold records for Process Managers used with the Task Manager.  All
// PMs are generally identified with the TM by the PM component identifier.  This
// class is thread-safe.

class PMRecordList
{
public:
	PMRecordList();
	// List related functions
	bool RegisterPM(const SDMComponent_ID& PMAddress, const SDMTaskResources& Resources);
	bool AlreadyRegistered(const SDMComponent_ID& PMAddress, const SDMTaskResources& Resources = 0);
	void ClearAllRunningTasks();
	bool TaskFinished(const SDMComponent_ID& PMAddress);
	bool TaskHasStarted(const SDMComponent_ID& PMAddress);
	bool RemovePM();
	bool FindPMID(const SDMTaskResources& TaskResources, pm_record& PmDataOut);
	bool FindEligiblePM(int NumTasks, const SDMTaskResources& TaskResources, pm_record& PmDataOut);
	void SetTasks(const SDMComponent_ID& PMAddress, int NumTasks);
	int GetTasks(const SDMComponent_ID& PMAddress);
   void SendToAll(SDMmessage& message);

	bool IsEmpty();

	// Heartbeat related functions
	int SendHeartbeatToAll(SDMHeartbeat& HearbeatMessage);
	void HeartbeatReceived(const SDMComponent_ID& PMAddress);
	bool RemoveAnyFailed(pm_record &PMOut);

	void PrintList();
private:
	pm_record pmList[MAX_PM];
	unsigned int schedulerInfoIndex;
	int HeartbeatStatus[MAX_PM];
	pthread_mutex_t DataMutex;
};


#endif
