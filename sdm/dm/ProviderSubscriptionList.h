#ifndef _SDM_PROVIDER_SUBSCRIPTION_LIST_H_
#define _SDM_PROVIDER_SUBSCRIPTION_LIST_H_

#include "../common/message/SDMComponent_ID.h"
#include "../common/message/SDMMessage_ID.h"

#include "ProviderSubscription.h"

//#define DEBUG_SUB_LIST	1

/*
 *  Provider subscription list allows the DM to keep track of all applications subscribed
 *  to all device notifications.  If an application is reported to have failed from the PM
 *  the DM can cancel all of the subscriptions to the device notifications.  This is required
 *  to free up resources on ASIM who may not receive a cancellation.
 *
 */

class ProviderSubscriptionListNode
{
public:
	ProviderSubscriptionListNode() : Data(), pNext(NULL) {}
	ProviderSubscriptionListNode(const ProviderSubscriptionListNode&);
	ProviderSubscriptionListNode& operator=(const ProviderSubscriptionListNode&);
	ProviderSubscription Data;
	ProviderSubscriptionListNode* pNext;
};

class ProviderSubscriptionList
{
public:
	ProviderSubscriptionList();
	~ProviderSubscriptionList();
	ProviderSubscriptionList(const ProviderSubscriptionList&);
	ProviderSubscriptionList& operator=(const ProviderSubscriptionList&);

	void Add(const SDMComponent_ID& ProviderId, const SDMComponent_ID& SubscriberId, const SDMMessage_ID& MessageId);
	void Delete(const SDMComponent_ID& SubscriberId, const SDMMessage_ID& MessageId);
	void SubscriberFinish(const SDMComponent_ID& SubscriberId);
	void ProviderFinish(const SDMComponent_ID& ProviderId);
	void PrintList(const char* strFunction);
	void DeleteAll(const SDMComponent_ID& SubscriberId, bool bUseProviderId);
private:
	void Add(ProviderSubscriptionListNode* pNode);
	void DeleteList();
	ProviderSubscriptionListNode* m_pHead;
};

#endif
