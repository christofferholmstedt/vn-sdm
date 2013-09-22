#ifndef _SDM_PROVIDER_SUBSCRIPTION_H_
#define _SDM_PROVIDER_SUBSCRIPTION_H_

#include "../common/message/SDMComponent_ID.h"
#include "../common/message/SDMMessage_ID.h"

class ProviderSubscription
{
public:
	ProviderSubscription();
	void Set(const SDMComponent_ID& idProvider, const SDMComponent_ID& idSubscriber, const SDMMessage_ID& idMessage);
	
	const SDMComponent_ID& GetSubscriber() const { return m_SubscriberId; }
	const SDMComponent_ID& GetProvider() const { return m_ProviderId; }
	const SDMMessage_ID& GetMessage() const { return m_MessageId; }
private:
	SDMComponent_ID m_ProviderId;
	SDMComponent_ID m_SubscriberId;
	SDMMessage_ID m_MessageId;
};

#endif
