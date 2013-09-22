#include "PendingTask.h"
#include <string.h>


PendingTask::PendingTask() : m_strName(), m_ulSdmPid(0)
{
	m_strName[0] = '\0';
}

PendingTask::PendingTask(const PendingTask& right) : m_strName(), m_ulSdmPid(0)
{
	this->m_ulSdmPid = right.m_ulSdmPid;
	strncpy(this->m_strName, right.m_strName, sizeof(m_strName));
	this->m_strName[MAX_FILENAME_SIZE-1] = '\0';
}

PendingTask& PendingTask::operator=(const PendingTask& right)
{
	this->m_ulSdmPid = right.m_ulSdmPid;
	strncpy(this->m_strName, right.m_strName, sizeof(m_strName));
	this->m_strName[MAX_FILENAME_SIZE-1] = '\0';
	return *this;
}

PendingTask::PendingTask(const char* strTaskName, unsigned long ulSdmPid)
	: m_strName(), m_ulSdmPid(0)
{
	strncpy(m_strName, strTaskName, sizeof(m_strName));
	m_strName[MAX_FILENAME_SIZE-1] = '\0';
	m_ulSdmPid = ulSdmPid;
}
