#include "PMProcessList.h"
#include <stdio.h>

PMProcessList::PMProcessList()
	: m_ProcessList()
{}

/*
 *  Add a process to the list.  If the new process is a restart of a failed process, the PID
 *  will already exist in this list, the fail count will be greater than zero.  In this case
 *  don't actually add another item in the list, but update the OsPid.
 *  Returns:
 *	int - The index of the added element.
 */
int PMProcessList::Add(const char* TaskName, unsigned int SdmPid, PROCESS_HANDLE OsPid)
{
	int iIndex = GetIndexOfSdmPid(SdmPid);
	// If the process didn't previously exist
	if (iIndex == -1)
	{
		PMProcess NewProc(TaskName, SdmPid, OsPid);
		m_ProcessList.push_back(NewProc);
		iIndex = m_ProcessList.size() - 1;
	}
	else if (iIndex != -1 && m_ProcessList[iIndex].GetSdmPid() == SdmPid)
	{
		// Sanity check
		if (m_ProcessList[iIndex].GetFailCount() == 0)
			printf("Warning: PMProcessList::Add()- inconsistent state, failure count shouldn't be zero.\n");
		
		m_ProcessList[iIndex].SetOsPid(OsPid);
	}
#ifdef DEBUG_PM_PROCESS_LIST
	PrintList();
#endif
	return iIndex;
}

bool PMProcessList::Remove(unsigned int Index)
{
	if (Index > m_ProcessList.size())
		return false;
	
	m_ProcessList.erase(m_ProcessList.begin() + Index, m_ProcessList.begin() + Index + 1);
#ifdef DEBUG_PM_PROCESS_LIST
	PrintList();
#endif
	return true;
}

int PMProcessList::GetIndexOfOsPid(PROCESS_HANDLE OsPid) const
{
	for (unsigned int i = 0; i < m_ProcessList.size(); i++)
	{
		if (m_ProcessList[i].GetOsPid() == OsPid)
			return i;
	}
	return -1;
}

int PMProcessList::GetIndexOfSdmPid(unsigned int SdmPid) const
{
	for (unsigned int i = 0; i < m_ProcessList.size(); i++)
	{
		if (m_ProcessList[i].GetSdmPid() == SdmPid)
			return i;
	}
	return -1;
}

void PMProcessList::UpdateOsPid(unsigned int SdmPid, PROCESS_HANDLE OsPid)
{
	int iIndex = GetIndexOfSdmPid(SdmPid);
	if (iIndex == -1)
	{
		printf("PMProcessList::HeartbeatReceived: Invalid SdmPid (%u)\n", SdmPid);
		return;
	}
	m_ProcessList[iIndex].SetOsPid(OsPid);
	
#ifdef DEBUG_PM_PROCESS_LIST
	PrintList();
#endif
}

void PMProcessList::HeartbeatReceived(unsigned int SdmPid)
{
	int Index = GetIndexOfSdmPid(SdmPid);
	if (Index == -1)
	{
		printf("PMProcessList::HeartbeatReceived: Invalid SdmPid (%u)\n", SdmPid);
		return;
	}
	
	m_ProcessList[Index].HeartbeatReceived();
}

PMProcess& PMProcessList::operator[] (unsigned int index)
{
	return m_ProcessList[index];
}

void PMProcessList::RemoveAll()
{
	m_ProcessList.clear();
}

#ifdef DEBUG_PM_PROCESS_LIST
void PMProcessList::PrintList()
{
	printf("*********************Process List (%u items)*********************\n", m_ProcessList.size());
	for (unsigned int i = 0; i < m_ProcessList.size(); i++)
	{
		printf("Index %u:  Name = \"%s\" SdmPid = %u OsPid = %d\n", i, m_ProcessList[i].GetName(), m_ProcessList[i].GetSdmPid(), m_ProcessList[i].GetOsPid());
	}
	printf("*****************************************************************\n");
}
#endif

