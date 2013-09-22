#ifndef _SDM_XTEDS_SUBSCRIPTION_LIST_H_
#define _SDM_XTEDS_SUBSCRIPTION_LIST_H_

#include "../message/SDMMessage_ID.h"
#include "../message/SDMComponent_ID.h"

class xTEDSSubscriptionListNode
{
public:
	xTEDSSubscriptionListNode() : pSub(NULL), pNext(NULL) {}
	xTEDSSubscription* pSub;
	xTEDSSubscriptionListNode* pNext;
};

class xTEDSSubscriptionList
{
public:
	void Add(const SDMComponent_ID& idSubscriber, const SDMMessage_ID& idMessage);
	void Remove(const SDMComponent_ID& idSubscriber, const SDMMessage_ID& idMessage);
private:
	bool Contains(const SDMComponent_ID& idSubscriber, const SDMMessage_ID& idMessage);
};


#endif

