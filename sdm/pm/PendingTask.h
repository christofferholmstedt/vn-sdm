#ifndef __SDM_PENDING_TASK_H_
#define __SDM_PENDING_TASK_H_

#include "../common/message_defs.h"

class PendingTask
{
public:
	PendingTask();
	PendingTask(const char* strFilename, unsigned long ulSdmPid);
	PendingTask(const PendingTask& right);
	PendingTask& operator= (const PendingTask& right);

	char* GetName() { return m_strName; }
	unsigned long GetPid() const { return m_ulSdmPid; }
private:
	char m_strName[MAX_FILENAME_SIZE];
	unsigned long m_ulSdmPid;
};

#endif

