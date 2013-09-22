//a class to handle subscriptions and data publishing

#ifndef __SUBSCRIPTION_MANAGER_H_
#define __SUBSCRIPTION_MANAGER_H_

#include "../message/SDMmessage.h"
#include "../message/SDMSubreqst.h"
#include "../message/SDMSerreqst.h"
#include "../message/SDMDeletesub.h"
#include "../message/SDMData.h"
#include "../message/SDMComponent_ID.h"
#include "../message/SDMMessage_ID.h"

#include "../sdmLib.h"

typedef struct sub
{
SDMComponent_ID component_id;
SDMMessage_ID msg_id;
SDMMessage_ID fault_id;
bool isSerreqst;
struct sub* next;
sub():component_id(),msg_id(),fault_id(),isSerreqst(false),next(0) {}
sub(const sub& r);
sub& operator=(const sub& r);
} subscription;


class SDMLIB_API SubscriptionManager
{
public:
	SubscriptionManager();
	SubscriptionManager(const SubscriptionManager&);
	~SubscriptionManager();
	bool AddSubscription(SDMSubreqst &subreqst);
	bool AddSubscription(SDMSerreqst &serreqst);
	bool RemoveSubscription(SDMDeletesub &deletesub);
	int SubscriptionCount(void);
	bool ClearAllSubscriptions(void);
	bool Publish(unsigned char interface_id,unsigned char message_id,char* data,long length);
	bool Publish(SDMMessage_ID id, char* data, long length);
	SubscriptionManager& operator=(const SubscriptionManager&);
	SDMData* GetLastPublished(void);
private:
	SDMComponent_ID my_component_id;
	subscription* sub_list;
	SDMData dat;
};

#endif
