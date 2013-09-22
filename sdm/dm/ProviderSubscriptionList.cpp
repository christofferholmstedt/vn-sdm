#include <stdio.h>
#include "../common/message/SDMDeletesub.h"
#include "../common/message/SDMCancel.h"
#include "ProviderSubscriptionList.h"

ProviderSubscriptionList::ProviderSubscriptionList() : m_pHead(NULL)
{
}

ProviderSubscriptionList::~ProviderSubscriptionList()
{
	DeleteList();
}

//
// Delete the entire list
void ProviderSubscriptionList::DeleteList()
{
	ProviderSubscriptionListNode* pTemp;
	for (ProviderSubscriptionListNode* pCur = m_pHead; pCur != NULL; )
	{
		pTemp = pCur->pNext;
		delete pCur;
		pCur = pTemp;
	}
	m_pHead = NULL;
#ifdef DEBUG_SUB_LIST
	PrintList(__FUNCTION__);
#endif
}

//
// Add the indicated subscription
void ProviderSubscriptionList::Add(const SDMComponent_ID& ProviderId, const SDMComponent_ID& SubscriberId, const SDMMessage_ID& MessageId)
{
	ProviderSubscriptionListNode* NewNode = new ProviderSubscriptionListNode();
	
	NewNode->Data.Set(ProviderId, SubscriberId, MessageId);
	
	Add(NewNode);
}

//
// Add to the end of the list
void ProviderSubscriptionList::Add(ProviderSubscriptionListNode* pNode)
{
	if (m_pHead == NULL)
		m_pHead = pNode;
	else
	{
		ProviderSubscriptionListNode* pCur = m_pHead;
		for (; pCur->pNext != NULL; pCur = pCur->pNext)
			;
		pCur->pNext = pNode;
	}
#ifdef DEBUG_SUB_LIST
	PrintList(__FUNCTION__);
#endif
}

//
// For the finished subscriber, cancel all subscriptions and delete the subscriber
// from the list.
void ProviderSubscriptionList::SubscriberFinish(const SDMComponent_ID& SubscriberId)
{
	SDMDeletesub msgDelete;
	SDMComponent_ID temp;

	for (ProviderSubscriptionListNode* pCur = m_pHead; pCur != NULL; pCur = pCur->pNext)
	{
	    temp = pCur->Data.GetSubscriber();
	    //printf("Sub Add: 0x%lx Port: %li SID: %li\nComp Add: 0x%lx Port: %li SID: %li\n",
            //SubscriberId.getAddress(), SubscriberId.getPort(), SubscriberId.getSensorID(),
            //temp.getAddress(), temp.getPort(), temp.getSensorID());
		if (SubscriberId.getAddress() == temp.getAddress() && SubscriberId.getPort() == temp.getPort())
		{
			msgDelete.source = pCur->Data.GetProvider();
			msgDelete.destination = pCur->Data.GetSubscriber();
			msgDelete.msg_id = pCur->Data.GetMessage();
#ifdef DEBUG_SUB_LIST
			{
				char strProvider[128];
				char strSubscriber[128];
				char strMessage[128];
				msgDelete.source.IDToString(strProvider, sizeof(strProvider));
				msgDelete.destination.IDToString(strSubscriber, sizeof(strSubscriber));
				msgDelete.msg_id.IDToString(strMessage, sizeof(strMessage));
				
				printf("Provider SubList SDMDeletesub sent:\n  provider %s subscriber %s message %s\n",
				       strProvider, strSubscriber, strMessage);
			}
#endif
			msgDelete.Send();
			//printf("Sending Deletsub Msg\n");
		}
	}
	
	DeleteAll(SubscriberId, false /*Delete subscriber id*/);
}

void ProviderSubscriptionList::ProviderFinish(const SDMComponent_ID& ProviderId)
{
	DeleteAll(ProviderId, true /*Delete provider id*/);
}

//
// Delete the entry with the specified subscriber and message
void ProviderSubscriptionList::Delete(const SDMComponent_ID& SubscriberId, const SDMMessage_ID& MessageId)
{
	ProviderSubscriptionListNode* pCur = m_pHead, *pPrev = NULL, *pTemp = NULL;

	while (pCur != NULL)
	{
		if (pCur->Data.GetSubscriber() == SubscriberId && pCur->Data.GetMessage() == MessageId)
		{
			if (pPrev == NULL)
			{
				// We are deleting the head
				pTemp = pCur->pNext;
				delete m_pHead;
				pCur = m_pHead = pTemp;
			}
			else
			{
				// Otherwise, we are at a middle element
				pTemp = pCur->pNext;
				delete pCur;
				pCur = pPrev->pNext = pTemp;
			}
		}
		else
		{
			pPrev = pCur;
			pCur = pCur->pNext;
		}
	}
#ifdef DEBUG_SUB_LIST
	PrintList(__FUNCTION__);
#endif
}

//
// Delete all entries with the given SubscriberId
void ProviderSubscriptionList::DeleteAll(const SDMComponent_ID& compId, bool bUseProviderId)
{
	ProviderSubscriptionListNode* pCur = m_pHead, *pPrev = NULL, *pTemp = NULL;
    SDMComponent_ID subscriber, temp2;
    SDMCancel cancelMsg;
	while (pCur != NULL)
	{
	    subscriber = pCur->Data.GetSubscriber();
	    temp2 = pCur->Data.GetProvider();

//	    printf("SubAdd: 0x%lx Port: %li ID: %li\nProvAdd: 0x%lx Port: %li SID: %li\nComp to Add: 0x%lx Port: %li ID: %li\n",
//            subscriber.getAddress(), subscriber.getPort(), subscriber.getSensorID(),
//            temp2.getAddress(), temp2.getPort(), temp2.getSensorID(),
//            compId.getAddress(), compId.getPort(), compId.getSensorID());
		if ((bUseProviderId && pCur->Data.GetProvider() == compId)
			|| (!bUseProviderId && subscriber.getAddress() == compId.getAddress() && subscriber.getPort() == compId.getPort()))
		{
		    // Perform a delete
		    //printf("Deleteing Subscription....\n");
			if (pPrev == NULL)
			{
				// We are deleting the head
				pTemp = pCur->pNext;
				delete m_pHead;
				pCur = m_pHead = pTemp;
			}
			else
			{ 
				// Otherwise, we are at a middle element
				pTemp = pCur->pNext;
				delete pCur;
				pCur = pPrev->pNext = pTemp;
			}
		}
		else
		{
			pPrev = pCur;
			pCur = pCur->pNext;
		}
	}
#ifdef DEBUG_SUB_LIST
	PrintList(__FUNCTION__);
#endif
}

void ProviderSubscriptionList::PrintList(const char* strFunction)
{
	printf("*******************Provider Subscription List*******************\n");
	printf("Called function %s()\n", strFunction);
	char strProvider[128];
	char strSubscriber[128];
	char strMessage[128];
	for (ProviderSubscriptionListNode* pCur = m_pHead; pCur != NULL; pCur = pCur->pNext)
	{
		pCur->Data.GetSubscriber().IDToString(strSubscriber, sizeof(strSubscriber));
		pCur->Data.GetProvider().IDToString(strProvider, sizeof(strProvider));
		pCur->Data.GetMessage().IDToString(strMessage, sizeof(strMessage));
		printf("  entry:  provider %s subscriber %s message %s\n", strProvider, strSubscriber, strMessage);
	}
	printf("****************************************************************\n");
}



