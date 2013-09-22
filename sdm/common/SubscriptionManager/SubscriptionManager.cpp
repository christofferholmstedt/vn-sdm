#include "SubscriptionManager.h"
#include "../message/SDMData.h"
#include <string.h>
#include <stdio.h>

void delete_subptr(subscription*);
subscription* deep_subcopy(subscription*);

SubscriptionManager::SubscriptionManager():my_component_id(),sub_list(NULL),dat()
{};

SubscriptionManager::SubscriptionManager(const SubscriptionManager& a):my_component_id(a.my_component_id),sub_list(NULL),dat()
{
	sub_list = deep_subcopy(a.sub_list);
}

SubscriptionManager::~SubscriptionManager()
{
	delete_subptr(sub_list);
}

bool SubscriptionManager::AddSubscription(SDMSubreqst &subreqst)
{
	subscription* new_sub = NULL;
	//look for subscription
	for(subscription* cur=sub_list;cur!=NULL;cur=cur->next)
	{
		if(cur->msg_id == subreqst.msg_id)
		if(cur->component_id.getAddress() ==  subreqst.destination.getAddress())
		if(cur->component_id.getPort() == subreqst.destination.getPort())
		{
			return false; //duplicate subscription
		}
	}
	new_sub = new(subscription);
	new_sub->msg_id = subreqst.msg_id;
	new_sub->fault_id = subreqst.fault_id;
	new_sub->component_id = subreqst.destination;
	new_sub->isSerreqst = false;
	new_sub->next = sub_list;
	sub_list = new_sub;
	my_component_id = subreqst.source;
	return true;
}

bool SubscriptionManager::AddSubscription(SDMSerreqst &serreqst)
{
	subscription* new_sub = NULL;
	//look for subscription
	for(subscription* cur=sub_list;cur!=NULL;cur=cur->next)
	{
		if(cur->msg_id == serreqst.reply_id)
		if(cur->component_id.getAddress() ==  serreqst.destination.getAddress())
		if(cur->component_id.getPort() == serreqst.destination.getPort())
		{
			return false; //duplicate subscription
		}
	}
	new_sub = new(subscription);
	new_sub->msg_id = serreqst.reply_id;
	new_sub->fault_id = serreqst.fault_id;
	new_sub->component_id = serreqst.destination;
	new_sub->isSerreqst = true;
	new_sub->next = sub_list;
	sub_list = new_sub;
	my_component_id = serreqst.source;
	return true;
}

bool SubscriptionManager::RemoveSubscription(SDMDeletesub &deletesub)
{
	subscription* prev = NULL;
	//look for subscription
	for(subscription* cur=sub_list;cur!=NULL;cur=cur->next)
	{
		if(cur->msg_id == deletesub.msg_id)
		if(cur->component_id.getAddress() ==  deletesub.destination.getAddress())
		if(cur->component_id.getPort() == deletesub.destination.getPort())
		{
			if(prev == NULL)
				sub_list = cur->next;
			else
				prev->next = cur->next;
			delete cur;
			return true;
		}
		prev = cur;
	}
	return false;
}


int SubscriptionManager::SubscriptionCount(void)
{
    int count = 0;
    for(subscription* cur=sub_list;cur!=NULL;cur=cur->next)
	{
		count++;
	}
    return count;
}

bool SubscriptionManager::Publish(unsigned char interface_id,unsigned char message_id,char* data,long length)
{
	SDMMessage_ID id(interface_id, message_id);
	return Publish (id, data, length);

}

bool SubscriptionManager::Publish(SDMMessage_ID id, char* data, long length)
{
	bool published = false;
	int result;
	//form data message
	dat.source = my_component_id;
	dat.msg_id = id;
	memcpy(dat.msg,data,length);
	subscription *prev = NULL;
	//search for matching subscriptions
	for(subscription* cur=sub_list;cur!=NULL;prev=cur, cur=cur->next)
	{
		if((cur->msg_id == id) || (cur->fault_id == id))
		{
			result = dat.Send(cur->component_id,length);
			if(result != -1)
			{
				//If this is a service request (i.e. one-time message response), remove the item upon first publish
				if (cur->isSerreqst)
				{
					//if cur is the list head
					if (prev == NULL)
					{
						sub_list = cur->next;
						delete cur;
					}
					//if cur is in the middle or at the end of the list
					else
					{
						prev->next = cur->next;
						delete cur;
					}
				}
				published = true;
			}
		}
	}
	return published;
}

SubscriptionManager& SubscriptionManager::operator=(const SubscriptionManager& a)
{
	my_component_id = a.my_component_id;
	sub_list = deep_subcopy(a.sub_list);
	return *this;
}

bool SubscriptionManager::ClearAllSubscriptions(void)
{
	if (sub_list == NULL) return false;
	delete_subptr(sub_list);
	sub_list = NULL;
	return true;
}

SDMData *SubscriptionManager::GetLastPublished()
{
	return &dat;
}

void delete_subptr(subscription *p)
{
	if (p ==NULL) return;
	delete_subptr(p->next);
	delete(p);
}

subscription* deep_subcopy(subscription *p)
{
	subscription* q = NULL;
	if (p ==NULL) return NULL;
	q = new(subscription);
	q->msg_id = p->msg_id;
	q->fault_id = q->fault_id;
	//q->ip_addr = p->ip_addr;
	//q->port = p->port;
	q->isSerreqst = p->isSerreqst;
	q->component_id = p->component_id;
	q->next = deep_subcopy(p->next);
	return q;
}

