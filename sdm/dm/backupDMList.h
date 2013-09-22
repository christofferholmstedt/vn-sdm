/******************************************************************************************************************************

	The backupDMList class is used to keep track of all registered backup DataManagers.  Backup DataManagers receive
	all copies of SDMxTEDS and SDMCancelxTEDS messages.  This class helps facilitate sending those messages out.
	This list is built when SDMReady messages arrive from the backup DMs as heartbeat messages.

******************************************************************************************************************************/
#ifndef __SDM_BACKUP_DM_LIST_H_
#define __SDM_BACKUP_DM_LIST_H_

#include <stdio.h>
#include "../common/message/SDMComponent_ID.h"
#include "../common/message/SDMmessage.h"

#define DEBUG_DM_BACKUP_LIST	1

class DMBackupListNode
{
public:
	DMBackupListNode() : m_idAddress(), m_pNext(NULL) {}
	DMBackupListNode(const DMBackupListNode&);
	DMBackupListNode& operator=(const DMBackupListNode&);
	SDMComponent_ID m_idAddress;
	class DMBackupListNode* m_pNext;
};

class DMBackupList
{
public:
	DMBackupList();
	DMBackupList(const DMBackupList&);
	DMBackupList& operator=(const DMBackupList&);
	~DMBackupList();

	bool AddNode(const SDMComponent_ID& NewDmId);
	bool AddIfNew(const SDMComponent_ID& DmId);
	void SendMessageToAll(SDMmessage& Message);
	bool SendMessageTo(const SDMComponent_ID& DmId, SDMmessage& Message);
    void PrintList();

private:
	DMBackupListNode* m_pHead;
	DMBackupListNode* m_pLastAccess;

	void DeleteList();
	bool ListContains(const SDMComponent_ID& Id);
	DMBackupListNode* Find(const SDMComponent_ID& Id);
};

#endif
