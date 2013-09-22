#ifndef _SDM_PM_PROCESS_LIST_H_
#define _SDM_PM_PROCESS_LIST_H_

#include "PMProcess.h"
#include <vector>
#include <stdio.h>

//#define DEBUG_PM_PROCESS_LIST 1

using namespace std;

class PMProcessList
{
public:
	PMProcessList();

	int Add (const char* TaskName, unsigned int SdmPid, PROCESS_HANDLE OsPid = 0);
	bool Remove (unsigned int Index);
	size_t Size() { return (int)m_ProcessList.size(); }

	int GetIndexOfOsPid(PROCESS_HANDLE OsPid) const;
	int GetIndexOfSdmPid(unsigned int SdmPid) const;
	void UpdateOsPid(unsigned int SdmPid, PROCESS_HANDLE OsPid);
	void HeartbeatReceived(unsigned int SdmPid);
	void RemoveAll();
	PMProcess& operator [] (unsigned int index);
#ifdef DEBUG_PM_PROCESS_LIST
	void PrintList();
#endif
private:
	vector<PMProcess> m_ProcessList;
};

#endif
