#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <stdio.h>
#include "PMProcess.h"
#include "../common/Time/SDMTime.h"

// Static initialization
bool PMProcess::m_bTimerInitialized = false;

PMProcess::PMProcess()
	: m_strFilename(), m_ulLastHeartbeat(0), m_ulHeartbeatMissCount(0), m_uiSdmPid(0), m_OsPid(0), m_uiTotalFailCount(0), m_bFailedState(false)
#ifdef WIN32
	, m_bCode(false)
#endif
{}

PMProcess::PMProcess(const char* Name, unsigned int SdmPid, PROCESS_HANDLE OsPid)
	: m_strFilename(), m_ulLastHeartbeat(0), m_ulHeartbeatMissCount(0), m_uiSdmPid(SdmPid), m_OsPid(OsPid), m_uiTotalFailCount(0), m_bFailedState(false)
#ifdef WIN32
	, m_bCode(false)
#endif
{
	strncpy(m_strFilename, Name, sizeof(m_strFilename));
}

PMProcess::~PMProcess()
{}

bool PMProcess::Kill() const
{
#ifndef WIN32
	if (kill(m_OsPid, SIGKILL) == 0)
		return true;
	return false;
#else
	return TerminateProcess(m_OsPid, 0);
#endif
}

unsigned int PMProcess::GetCurTimeSeconds()
{
	unsigned int uiSeconds, uiUSeconds;
	if (!m_bTimerInitialized)
	{
		SDM_TimeInit();
		m_bTimerInitialized = true;
	}
	SDM_GetTime(&uiSeconds, &uiUSeconds);
	return uiSeconds;
}

void PMProcess::HeartbeatReceived()
{
	m_ulLastHeartbeat = GetCurTimeSeconds();
	m_ulHeartbeatMissCount = 0;
}

bool PMProcess::IsUnresponsive()
{
	// Don't try unless at least one heartbeat has been received
	if (m_ulLastHeartbeat == 0 && !m_bFailedState)
		return false;
	
	unsigned int uiCurSeconds = GetCurTimeSeconds();
	if (uiCurSeconds < m_ulLastHeartbeat)	// Sanity check
	{
		printf("Warning, current time is less than last received heartbeat.\n");
		return false;
	}
	
	if (uiCurSeconds - m_ulLastHeartbeat < TASK_HEARTBEAT_TIMEOUT)
		return false;
	else
	{
		// "Fake" a heartbeat, to allow another full interval for timeout
	  m_ulLastHeartbeat += TASK_HEARTBEAT_TIMEOUT;
		if (++m_ulHeartbeatMissCount >= TASK_TIMEOUT_ATTEMPTS)
			return true;
	}
	return false;
}

/*
NOW INLINE
bool PMProcess::IsNormalFinish() const
{
	return !m_bFailedState;
}
*/
void PMProcess::Failure()
{
	m_bFailedState = true;
	m_uiTotalFailCount++;
	m_ulLastHeartbeat = 0;
	m_ulHeartbeatMissCount = 0;
}

void PMProcess::Reset()
{
	m_OsPid = 0;
	m_bFailedState = false;
}





