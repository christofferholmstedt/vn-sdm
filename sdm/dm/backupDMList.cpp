#include "backupDMList.h"

#include <stdlib.h>
#include <string.h>

DMBackupList::DMBackupList() : m_pHead(NULL), m_pLastAccess(NULL)
{}


DMBackupList::~DMBackupList()
{
	DeleteList();
}

bool DMBackupList::AddNode(const SDMComponent_ID& NewDmId)
{	
	DMBackupListNode* pNewNode = new DMBackupListNode;
  if (pNewNode == NULL)
  {
        return false;
  }

	pNewNode->m_idAddress = NewDmId;
	
	// If the list is empty, set the new node to the head
	if (m_pHead == NULL)
	{
		m_pHead = pNewNode;
	}
	// Otherwise, find the tail, then add
	else
	{
		DMBackupListNode* pCur = m_pHead;
		for (; pCur->m_pNext != NULL; pCur = pCur->m_pNext)
			;
		pCur->m_pNext = pNewNode;
	}
	
	// Set the last access pointer
	m_pLastAccess = pNewNode;
#ifdef DEBUG_DM_BACKUP_LIST
	PrintList();
#endif
}

void DMBackupList::DeleteList()
{
	DMBackupListNode* pTemp = NULL;
	for (DMBackupListNode* pCur = m_pHead; pCur != NULL; )
	{
		pTemp = pCur->m_pNext;
		delete pCur;
		pCur = pTemp;
	}
	m_pHead = NULL;
}

// Returns whether a node was added
bool DMBackupList::AddIfNew(const SDMComponent_ID& DmId)
{	
	if (ListContains(DmId))
		return false;
	else
	{
		AddNode(DmId);
		return true;
	}
}

// Returns whether the list contains the given Id
bool DMBackupList::ListContains(const SDMComponent_ID& Id)
{
	DMBackupListNode* pCur = Find(Id);
	
	// If pCur is not null, the list contains the node
	return (pCur != NULL);
}


void DMBackupList::SendMessageToAll(SDMmessage& Message)
{
	for (DMBackupListNode* pCur = m_pHead; pCur != NULL; pCur = pCur->m_pNext)
	{
		Message.SendTo(pCur->m_idAddress);
	}
}

// Returns whether the Id was found
bool DMBackupList::SendMessageTo(const SDMComponent_ID& Id, SDMmessage& Message)
{
	DMBackupListNode* pCur = Find(Id);
	
	if (pCur == NULL)
		return false;
	
	Message.SendTo(Id);
	return true;
}

DMBackupListNode* DMBackupList::Find(const SDMComponent_ID& Id)
{
	// For efficiency
	if (m_pLastAccess != NULL && m_pLastAccess->m_idAddress == Id)
		return m_pLastAccess;
	
	// Otherwise, do a linear search
	for (DMBackupListNode* pCur = m_pHead; pCur != NULL; pCur = pCur->m_pNext)
	{
		if (pCur->m_idAddress == Id)
		{
			m_pLastAccess = pCur;
			return pCur;
		}
	}
	return NULL;
}

#ifdef DEBUG_DM_BACKUP_LIST
void DMBackupList::PrintList()
{
	printf("***********************DM Backup List***********************\n");
	char strId[128];
	for (DMBackupListNode* pCur = m_pHead; pCur != NULL; pCur = pCur->m_pNext)
	{
		pCur->m_idAddress.IDToString(strId, sizeof(strId));
		printf("  %s\n", strId);
	}
	printf("************************************************************\n");
}
#endif



