// TaskList definition file
#ifndef __TASKLIST_H_
#define __TASKLIST_H_

#include "task.h"
#include "TmXtedsDefs.h"

class TaskList
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
	unsigned int FillTaskListBlob (char* pBuffer, unsigned int uiBufferSize);
	unsigned int FillTaskListBlobRunningOnly (char* pBuffer, unsigned int uiBufferSize);
	unsigned int FillTaskInfoRequest(unsigned int uiPid, char* pBuffer, unsigned int uiBufferSize);
	void PrintList();
	Task& operator[](int index);
private:
	enum TaskSet { TASKS_ALL, TASKS_RUNNING };
	unsigned int FillTaskListBlob (char* pBuffer, unsigned int uiBufferSize, TaskSet eTaskSet);
	Task tasks[NUMTASKS];
};

#endif
