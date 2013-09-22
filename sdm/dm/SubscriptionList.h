/******************************************************************************************************************************

	The SubscriptionList class is a linked list of SubscriptionListNode items which are used to add and remove various 
	subscriptions specific to the DataManager module of the SDM.  Namely, this list holds subscription information for 
	DataManager notification subscriptions, SDMReqReg query subscriptions (when SDM_REQREG_CURRENT_AND_FUTURE and
	SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS search types are used), and SDMSearch query subscriptions (when the
	SDM_SEARCH_CURRENT_AND_FUTURE search type is used.
	
******************************************************************************************************************************/
#ifndef __SDM_SUBSCRIPTION_LIST_H_
#define __SDM_SUBSCRIPTION_LIST_H_

//The SubscriptionList does not 'own' its items, it is just a way for items to reference other items in the tree

#include "Subscription.h"
#include "../common/message/SDMComponent_ID.h"
#include <stdio.h>


#define REQ_REG_FUTURE 0x401
#define REQ_REG_CANCELLATION 0x402
#define VAR_REQ_REPLY 0x403
#define SEARCH_REPLY 0x404

#define SUB_CURRENT_AND_FUTURE			5	// Corresponds to SDM_REQREG_* macros with same value for list request
#define SUB_CURRENT_FUTURE_AND_CANCELLATIONS	7	// Corresponds to SDM_REQREG_* macros with same value for list request
#define SUB_CANCEL				11	// Corresponds to SDM_REQREG_* macros with same value for list request

/* Linked list node */
struct SubscriptionListNode
{
	Subscription* data;
	struct SubscriptionListNode* next;
};

class SubscriptionList
{
public:
	SubscriptionList();
	SubscriptionList(const SubscriptionList&);
	~SubscriptionList();
	void addSubscription(Subscription*);
	SubscriptionListNode* addSubscription(const SDMComponent_ID& SubscriberId, int mID, int debug);
	bool addOrRemoveSubscription(int reply, const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* device, const char* interface, const char* itemname, const char* quallist, int ID, int mID, int debug);
	bool addReqRegSubscription(int reply, const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* device, const char* interface, const char* itemname, const char* quallist, int ID, int& error, int debug);
	bool removeReqRegSubscription(int reply, const SDMComponent_ID& SubscriberId, int debug);
	bool removeReqRegSubscription(int reply, const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* device, const char* interface, const char* itemname, const char* quallist, int debug);
	bool addSearchSubscription(const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* itemname, int ID, int& error, int debug);
	bool removeSearchSubscription(const SDMComponent_ID& SubscriberId, int debug);
	bool removeSearchSubscription(const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* itemname, int debug);
	bool addVarReqSubscription(const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* interface, const char* itemname, int ID, int& error, int debug);
	bool removeVarReqSubscription(const SDMComponent_ID& SubscriberId, int debug);
	bool removeVarReqSubscription(const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* interface, const char* itemname, int debug);
	SubscriptionList& operator=(const SubscriptionList&);
	struct SubscriptionListNode* head;
	struct SubscriptionListNode* tail;
};

#endif
