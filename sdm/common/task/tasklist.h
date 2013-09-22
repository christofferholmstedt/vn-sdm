// TaskList definition file
#ifndef __TASKLIST_H_
#define __TASKLIST_H_

#include "task.h"
#include "../sdmLib.h"

class SDMLIB_API TaskList
{
public:
	TaskList();
	void Init();
	bool AnyInactive();
	bool AnyPending();
	bool AddTo(const Task& t);
	bool RemoveFrom(unsigned int pid);
	bool RemoveFrom(char *filename);
	bool TaskFinished(unsigned int a_uiPid);
	bool IsFilePresent(char *filename);
	bool SetAddress(unsigned int pid, const SDMComponent_ID& PM);
	unsigned int SetState (unsigned int pid, char state);
	int FindPendingTask(Task& taskOut);
	bool FindPendingMatch (int resources, unsigned int newPID, Task& taskOut);
	unsigned int FindPID(const char* filename);
	SDMComponent_ID GetPMAddress(unsigned int pid);
	void ClearList();
	void PMFailure(const SDMComponent_ID& PMID);
	void RemovePreferredPmId(const SDMTaskResources& TaskResources);
	void PrintList();
	Task& operator[](int index);
private:
	Task tasks[NUMTASKS];
};

#endif
