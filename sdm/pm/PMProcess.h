#ifndef _SDM_PM_PROCESS_H_
#define _SDM_PM_PROCESS_H_

#include "../common/message_defs.h"
#include "../common/version.h"

#ifdef WIN32
#  include <windows.h>
#  define PROCESS_HANDLE HANDLE
#else
#  define PROCESS_HANDLE int
#endif

#define TASK_HEARTBEAT_TIMEOUT		10	// In seconds
#define TASK_TIMEOUT_ATTEMPTS		6	// Number of retries

class PMProcess
{
public:
	PMProcess();
	PMProcess(const char* Name, unsigned int SdmPid, PROCESS_HANDLE OsPid);
	~PMProcess();
	
	unsigned int GetSdmPid() const { return m_uiSdmPid; }
	PROCESS_HANDLE GetOsPid() const { return m_OsPid; }
	const char* GetName() const { return m_strFilename; }
	unsigned int GetFailCount() const { return m_uiTotalFailCount; }
	void SetOsPid(PROCESS_HANDLE OsPid) { m_OsPid = OsPid; }
	bool Kill() const;
	bool IsNormalFinish() const { return !m_bFailedState; }
	bool IsUnresponsive();
	bool IsFailed() const { return m_bFailedState; }
	void Failure();
	void Reset();
	void HeartbeatReceived();

#ifdef WIN32
	void SetCode(bool NewCode) { m_bCode = NewCode; }
	bool GetCode() const { return m_bCode; }
#endif
private:
	char m_strFilename[MAX_FILENAME_SIZE];		// Process name
	unsigned long m_ulLastHeartbeat;		// Seconds of last heartbeat, in EPOC time
	unsigned long m_ulHeartbeatMissCount;		// Number of heartbeats missed
	unsigned int m_uiSdmPid;			// SDM PID for this process
	PROCESS_HANDLE m_OsPid;				// Operating System PID for this process
	unsigned int m_uiTotalFailCount;		// Number of times this process has failed
	bool m_bFailedState;				// Indicates whether this process is in a fail state
#ifdef WIN32
	bool m_bCode;
#endif
	static unsigned int GetCurTimeSeconds();
	static bool m_bTimerInitialized;
};

#endif
