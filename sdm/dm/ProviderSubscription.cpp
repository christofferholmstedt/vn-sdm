#include "ProviderSubscription.h"

ProviderSubscription::ProviderSubscription() : m_ProviderId(), m_SubscriberId(), m_MessageId()
{
}

void ProviderSubscription::Set(const SDMComponent_ID& idProvider, const SDMComponent_ID& idSubscriber, const SDMMessage_ID& idMessage)
{
	m_ProviderId = idProvider;
	m_SubscriberId = idSubscriber;
	m_MessageId = idMessage;
}
