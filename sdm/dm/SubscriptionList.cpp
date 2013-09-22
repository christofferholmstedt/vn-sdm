#include "SubscriptionList.h"
#include "Subscription.h"
#include "../common/Debug.h"
#include <stdlib.h>
#include <string.h>
extern "C"
{
#include "../common/MemoryUtils.h"
}

/*
	copyList copies the subscription list pointed to by "list".
	INPUTS:
		list - The list to copy
		tail - (output parameter) A pointer to the tail which is assigned to be the tail of the copied list
	RETUNS:
		SubscriptionListNode* - A pointer to the newly copied list
*/
struct SubscriptionListNode* copyList(struct SubscriptionListNode* list,struct SubscriptionListNode** tail)
{
	struct SubscriptionListNode* p;
	struct SubscriptionListNode* head;
	head = (struct SubscriptionListNode*)SDM_malloc(sizeof(struct SubscriptionListNode));
	p = head;
	for(struct SubscriptionListNode* cur=list;cur!=NULL;cur=cur->next)
	{
		p->data = cur->data;
		if(cur->next!=NULL)
		{
			p->next = (struct SubscriptionListNode*)SDM_malloc(sizeof(struct SubscriptionListNode));
		}
		else
		{
			p->next = NULL;
			*tail = p;
		}
		p = p->next;
	}
	return head;
}

/*
	deleteList traverses through the subscription list and frees all of the items associated with each entry.  This function
	is called from the destructor and from the assignment operator.
	INPUTS:
		p - The head of the list to delete
	RETURNS:
		void
*/
void deleteList(struct SubscriptionListNode* p)
{
	if(p==NULL) return;
	deleteList(p->next);
	if(p->data!=NULL)
		delete(p->data);
	free(p);
}

/*
	Default Constructor, initializes the head and tail pointers to null.
*/
SubscriptionList::SubscriptionList():head(NULL),tail(NULL)
{}

/*
	Copy Constructor, copies the subscription list of the copying object.
*/
SubscriptionList::SubscriptionList(const SubscriptionList& b):head(NULL),tail(NULL)
{
	head = copyList(b.head,&tail);
}

/*
	~SubscriptionList (destructor) removes all subscriptions (heap allocated) in the list.
*/
SubscriptionList::~SubscriptionList()
{
	deleteList(head);
}

/*
	addSubscription adds a new subscription node to the linked list of subscriptions adding the parameter data as the Subscription
	node.
	INPUTS:
		data - The Subscription object added to the list, the pointer is added directly and not copied.
	RETURNS:
		void
*/
void SubscriptionList::addSubscription(Subscription* data)
{
	struct SubscriptionListNode* p = (struct SubscriptionListNode*)SDM_malloc(sizeof(struct SubscriptionListNode));
	p->data = data;
	p->next = NULL;
	if(tail == NULL)
	{
		head = p;
		tail = p;
	}
	else
	{
		tail->next = p;
		tail = p;
	}
}

/*
	addSubscription adds a new reply subscription to the list of subscriptions.  This overload adds a subscription to a DataManager
	notification (in its xTEDS).  The linked list is first checked to make sure a duplicate subscription will not be added by 
	checking against the input parameters.  If the subscription is not in the list, a new item is (malloc) added to the linked 
	list.  Debug information for this function can be output on level 4.
	INPUTS:
		ip - The IP address of the subscribing process
		port - The port of the subscribing process
		mID - The message and interface identifier for the message being subscribed to
		debug - The debug level of the DataManager
	RETURNS:
		SubscriptionListNode* - The position in the linked list of the added SubscriptionListNode
*/
SubscriptionListNode* SubscriptionList::addSubscription(const SDMComponent_ID& SubscriberId, int mID, int debug)
{
	SubscriptionListNode* result = NULL;
	SubscriptionListNode* node;
	int count = 0;

	node = head;
	while(node!=NULL)	//Check to see if subscription is a duplicate
	{
		if(node->data->getInuse() == true)	//Check to see if in use
		{
			if (node->data->getDestination() == SubscriberId)
			{
				if(node->data->getmID() == mID)	//Check to see if message id matches
				{
					if(node->data->getItems() == false)
					{
						debug_f(4, "Multiple subscription trying to be entered\n");
						return result;	//No need to enter subscription because it is a duplicate
					}
				}
			}
		}
		node = node->next;
	}
	node = head;
	while(node!=NULL)
	{
		if(node->data->getInuse()==false)
			break;
		node = node->next;
	}
	if(node==NULL)
	{
		addSubscription(new Subscription());
		node = tail;
	}
	node->data->setDestination(SubscriberId);
	node->data->setmID(mID);	//Copy msg id into subscription
	node->data->setInuse(true);	//Set in use to 1
	node->data->setItems(false);	//Set Items to false to indicate there are no Items from ReqReg because this is a DM subscription
	debug_f(4, "Subscription is on ip: 0x%lx port: %d to message ID: 0x%x\n",SubscriberId.getAddress(),SubscriberId.getPort(),mID);
	result = node;
	node = head;
	if (debug >= 4)		//only print if subscription and debug level great enough
	{
		while(node!=NULL) //Print current subscriptions
		{
			if(node->data->getInuse() == true)	
			{
				char SubscriberText[64];
				node->data->getDestination().IDToString(SubscriberText, sizeof(SubscriberText));
				printf("Subscription %d: %s messageID: 0x%x\n",count+1,SubscriberText,node->data->getmID());
				count++;
			}
			node = node->next;
		}
	}
	return result;
}

/*
	addOrRemoveSubscription adds or removes a SDMReqReg or SDMSearch subscription to the subscription list depending on the
	value of "reply".  If the subscription is to be added, the appropriate Search or ReqReg subscription is added according
	to all of the reply information.  If the subscription is to be removed, the appropriate Search or ReqReg subscription is
	removed based on all of the source application information.
	INPUTS:
		reply - The subscription operation, can be one of SDM_REQREG_CURRENT_AND_FUTURE, SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS,
			SDM_REQREG_CANCEL, SDM_SEARCH_CURRENT_AND_FUTURE, SDM_SEARCH_CANCEL
		ip - The IP address of the subscriber
		port - The port of the subscriber
		source - The component identifier of the interested device or application to which the subscription is intended
		device - The device name of the device or application to which the subscription is intended (ReqReg only)
 		interface - The interface of the device or application to which the subscription is intended (ReqReg only)
		itemname - The itemname (ReqReg) or search query (Search) the subscriber is interested in
		quallist - The qualifier list of the device or application to which the subscription is intended (ReqReg only)
		ID - The identifier number for this subscription stream
		mID - The type of subscription, can be one of SEARCH_REPLY, REQ_REG_FUTURE, or ReqRegCancellation
		debug - The debug level of the DataManager
	RETURNS:
		bool - true on successful addition/removal, false otherwise
		
*/
bool SubscriptionList::addOrRemoveSubscription(int reply, const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* device, const char* interface, const char* itemname, const char* quallist, int ID, int mID, int debug)
{
	bool result = false;
	static int error = 0;
	bool cancelsingle = false;

	switch(reply) //Check the reply value
	{
		case SUB_CURRENT_AND_FUTURE:
		case SUB_CURRENT_FUTURE_AND_CANCELLATIONS:
			if(mID == SEARCH_REPLY)
				result = addSearchSubscription(SubscriberId, source, itemname, ID, error, debug);
			else if(mID == VAR_REQ_REPLY)
				result = addVarReqSubscription(SubscriberId, source, interface, itemname, ID, error, debug);
			else
				result = addReqRegSubscription(reply, SubscriberId, source, device, interface, itemname, quallist, ID, error, debug);
			break;
		case SUB_CANCEL:
			if(source.isEmpty() == true)
			{
				if(itemname == NULL || strlen(itemname) == 0)  //Check to see if the item_name matches
				{
					if(quallist == NULL || strlen(quallist) == 0)  //Check to see if the qual_list matches
					{
						if(device == NULL || strlen(device)==0)	//Check to see if device name matches
						{
							if(interface == NULL || strlen(interface)==0)	//Check to see if interface name matches
							{
								if(mID == SEARCH_REPLY)
									result = removeSearchSubscription(SubscriberId, debug);
								else if(mID == VAR_REQ_REPLY)
									result = removeVarReqSubscription(SubscriberId, debug);
								else
									result = removeReqRegSubscription(reply, SubscriberId, debug);
							}
							else
								cancelsingle = true;
						}
						else
							cancelsingle = true;
					}
					else
						cancelsingle = true;
				}
				else
					cancelsingle = true;
			}
			else
				cancelsingle = true;
			if(cancelsingle == true)
			{
				if(mID == SEARCH_REPLY)
					result = removeSearchSubscription(SubscriberId, source, itemname, debug);
				else if(mID == VAR_REQ_REPLY)
					result = removeVarReqSubscription(SubscriberId, source, interface, itemname, debug);
				else
					result = removeReqRegSubscription(reply, SubscriberId, source, device, interface, itemname, quallist, debug);
			}
			break;
		default:
			error++;
			printf("Unable to handle subscriptions request because the reply type of %d was invalid Error Count: %d\n",reply,error);
			result = true;
			break;
	}
	return result;
}

/*
	addReqRegSubscription adds a ReqReg subscription to the subscription list.  This function first checks for a duplicate subscription, if
	this is the case the subscription won't be added (returns true).  If the subscription has not been previously added, it is added to
	the subscription list (returns true).  If the "reply" is set to either SDM_REQREG_CURRENT_AND_FUTURE or SDM_SEARCH_CURRENT_AND_FUTURE
	one subscription is entered.  If the "reply" type is set to SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS, two subscriptions are entered
	one corresponding to future added subscriptions, and one corresponding to future cancellations.
	INPUTS:
		reply - The subscription operation, can be one of SDM_REQREG_CURRENT_AND_FUTURE, SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS,
			SDM_REQREG_CANCEL, SDM_SEARCH_CURRENT_AND_FUTURE, SDM_SEARCH_CANCEL
		ip - The IP address of the subscriber
		port - The port of the subscriber
		source - The component identifier of the interested device or application to which the subscription is intended
		device - The device name of the device or application to which the subscription is intended (ReqReg only)
 		interface - The interface of the device or application to which the subscription is intended (ReqReg only)
		itemname - The itemname (ReqReg) or search query (Search) the subscriber is interested in
		quallist - The qualifier list of the device or application to which the subscription is intended (ReqReg only)
		ID - The identifier number for this subscription stream
		error - (output reference parameter) incremented if a duplicate subscription exists
		debug - The debug level of the DataManager
	RETURNS:
		bool - Always true
		error - (reference parameter) incremented if a duplicate subscription exists
*/
bool SubscriptionList::addReqRegSubscription(int reply, const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* device, const char* interface, const char* itemname, const char* quallist, int ID, int& error, int debug)
{
	int cont = 0, val1 = 0, val2 = 0, tempreply = 0,j;
	SubscriptionListNode* node;
	bool nosub = false;

	if(reply == SUB_CURRENT_AND_FUTURE)
	{
		cont = 1;	//Set a variable for the number of subscriptions to be entered
		val1 = REQ_REG_FUTURE;
	}
	else
	{
		cont = 2;	//Set a variable for the number of subscriptions to be entered
		val1 = REQ_REG_FUTURE;
		val2 = REQ_REG_CANCELLATION;
	}
	for(j = 0; j < cont; j++)
	{
		node = head;
		nosub = false;
		while(node!=NULL)	//Check to see if subscription is a duplicate
		{
			if(node->data->getInuse() == true)	//Check to see if in use
			{
				if (node->data->getDestination() == SubscriberId)
				{
					if(node->data->getmID() == val1 || node->data->getmID() == val2)	//Check to see if message id matches
					{
						if(node->data->getSource()==source)
						{
							if(node->data->getItems() == true)	//Check to see if message the are items in use
							{
								if(strcmp(node->data->getItemName(),itemname) == 0)  //Check to see if the item_name matches
								{
									if(strcmp(node->data->getQuallist(),quallist) == 0)  //Check to see if the qual_list matches
									{
										if(strcmp(node->data->getDevice(),device)==0)	//Check to see if device name matches
										{
											if(strcmp(node->data->getInterface(),interface)==0)	//Check to see if interface name matches
											{
												if(j == 0 && node->data->getmID() == val1)
												{
													nosub = true;
												if(reply == SUB_CURRENT_AND_FUTURE)
													{
														error++;
														debug_f(2, "Multiple subscription trying to be entered Error Count: %d\n",error);
														return true;	//No need to enter subscription because it is a duplicate
													}
												}
												else if(j == 1 && node->data->getmID() == val2)
												{
													error++;
													debug_f(2, "Multiple subscription trying to be entered Error Count: %d\n",error);
													return true;	//No need to enter subscription because it is a duplicate
												}
											}
										}
									}
								}
							}
						}
					}
				}
			}
			node = node->next;
		}
		if(nosub == false)
		{
			node = head;
			while(node!=NULL)	//Find an array location in the subscription list that is not in use
			{
				if(node->data->getInuse() == false)
					break;
				node = node->next;
			}
			if(node==NULL)
			{
				addSubscription(new Subscription());
				node = tail;
			}
			//Enter the subscription
			node->data->setItemName(itemname);
			node->data->setQuallist(quallist);
			node->data->setDestination(SubscriberId);
			node->data->setSource(source);
			node->data->setDevice(device);
			node->data->setInterface(interface);
			//Set the subscription message id
			if(reply == SUB_CURRENT_AND_FUTURE)
				tempreply = REQ_REG_FUTURE;
			if(reply == SUB_CURRENT_FUTURE_AND_CANCELLATIONS && j == 0)
				tempreply = REQ_REG_FUTURE;
			if(reply == SUB_CURRENT_FUTURE_AND_CANCELLATIONS && j == 1)
				tempreply = REQ_REG_CANCELLATION;
			node->data->setmID(tempreply); //Copy the message id into subscription
			node->data->setInuse(true);	//Set subscription in use
			node->data->setItems(true);	//Set subscription items
			node->data->setID(ID);
		}
	}
	return true;
}

/*
	removeReqRegSubscription removes all subscriptions corresponding to the input "port" and "ip".  This function always returns
 	false to notify the ReqReg function in the DM that it can finish whether or not a subscription was cancelled.
 	INPUTS:
 		reply - The subscription operation, this could be SDM_REQREG_CANCEL or SDM_SEARCH_CANCEL
 		ip - The IP address of the subscriber to cancel
 		port - The port of the subscriber to cancel
 		debug - The debug level of the DataManager
 	RETURNS:
 		bool - Always false
*/
bool SubscriptionList::removeReqRegSubscription(int reply, const SDMComponent_ID& SubscriberId, int debug)
{
	int cont = 0, tempreply = 0,j;
	SubscriptionListNode* node;

	if(reply == SUB_CANCEL)
		cont = 2;	//Set the number of subscriptions to cancel
	for(j = 0; j < cont; j++)
	{
		node = head;
		if(reply == SUB_CANCEL && j == 0)
			tempreply = REQ_REG_FUTURE;	//Set the message id
		if(reply == SUB_CANCEL && j == 1)
			tempreply = REQ_REG_CANCELLATION;	//Set the message id
		while(node!=NULL)
		{
			if(node->data->getInuse() == true)	//Check to see if subscription in use
			{
                SDMComponent_ID tempId = node->data->getDestination();
				if (tempId.getAddress() == SubscriberId.getAddress() && tempId.getPort() == SubscriberId.getPort())
				{
					if(node->data->getmID() == tempreply)	//Check to see if message ID match
					{
						if(node->data->getItems() == true)	//Check to see it item is set
						{
							node->data->setPort(0);	//Set port to 0
							node->data->setmID(0);	//Set message id to 0
							node->data->setInuse(false);	//Set in use to 0
							node->data->setItems(false);	//Set items to 0
							node->data->setID(0);
							debug_f(4, "Canceled subscription\n");
						}
						else
							debug_f(4, "Unable to cancel subscription because there is no items\n");
					}
					else
						debug_f(4, "Unable to cancel subscription because message ID does not match current subscriptions\n");
				}
				else
					debug_f(4, "Unable to cancel subscription because address does not match current subscription\n");
			}
			node = node->next;
		}
	}
	return false;
}

/*
	removeReqRegSubscription removes a SDMReqReg subscription according to the paramemter information of the subscription.  This function
	removes at max a matching pair of subscriptions. This function always returns false to notify the ReqReg function in the DM that it 
	can finish whether or not a subscription was cancelled.
	INPUTS:
		reply - The subscription operation, can be one of SDM_REQREG_CURRENT_AND_FUTURE, SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS,
			SDM_REQREG_CANCEL, SDM_SEARCH_CURRENT_AND_FUTURE, SDM_SEARCH_CANCEL
		ip - The IP address of the subscriber
		port - The port of the subscriber
		source - The component identifier of the interested device or application to which the subscription is intended
		device - The device name of the device or application to which the subscription is intended (ReqReg only)
 		interface - The interface of the device or application to which the subscription is intended (ReqReg only)
		itemname - The itemname (ReqReg) or search query (Search) the subscriber is interested in
		quallist - The qualifier list of the device or application to which the subscription is intended (ReqReg only)
		debug - The debug level of the DataManager
	RETURNS:
		bool - Always false
	
*/
bool SubscriptionList::removeReqRegSubscription(int reply, const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* device, const char* interface, const char* itemname, const char* quallist, int debug)
{
	int cont = 0, tempreply = 0,j;
	SubscriptionListNode* node;

	if (device==NULL || interface==NULL || itemname==NULL || quallist==NULL)
		return false;
	if(reply == SUB_CANCEL)
		cont = 2;	//Set the number of subscriptions to cancel
	for(j = 0; j < cont; j++)
	{
		node = head;
		if(reply == SUB_CANCEL && j == 0)
			tempreply = REQ_REG_FUTURE;	//Set the message id
		if(reply == SUB_CANCEL && j == 1)
			tempreply = REQ_REG_CANCELLATION;	//Set the message id
		while(node!=NULL)
		{
			if(node->data->getInuse() == true)	//Check to see if subscription in use
			{
				if (node->data->getDestination() == SubscriberId)
				{
					if(node->data->getmID() == tempreply)	//Check to see if message ID match
					{
						if(node->data->getItems() == true)	//Check to see it item is set
						{
							if(node->data->getSource()==source)
							{
								if(strcmp(node->data->getItemName(),itemname) == 0)  //Check to see if the item_name matches
								{
									if(strcmp(node->data->getQuallist(),quallist) == 0)  //Check to see if the qual_list matches
									{
										if(strcmp(node->data->getDevice(),device)==0)	//Check to see if device name matches
										{
											if(strcmp(node->data->getInterface(),interface)==0)	//Check to see if interface name matches
											{
												node->data->setPort(0);	//Set port to 0
												node->data->setmID(0);	//Set message id to 0
												node->data->setInuse(false);	//Set in use to 0
												node->data->setItems(false);	//Set items to 0
												node->data->setID(0);
												debug_f(4, "Canceled subscription\n");
												if(reply == SUB_CANCEL && j == 1)
													return false;	//If subscriptions canceled this function is done
												if(reply < SUB_CANCEL)
													return false;	//If subscription is canceled this function is done
											}
											else
												debug_f(4, "Unable to cancel subscription because there is no interface\n");
										}
										else
											debug_f(4, "Unable to cancel subscription because there is no device\n");
									}
									else
										debug_f(4, "Unable to cancel subscription because there is no quallist\n");
								}
								else
									debug_f(4,"Unable to cancel subscription because there is no item_name\n");
							}
							else
								debug_f(4, "Unable to sources do not match\n");
						}
						else
							debug_f(4, "Unable to cancel subscription because there is no items\n");
					}
					else
						debug_f(4, "Unable to cancel subscription because message ID does not match current subscriptions\n");
				}
				else
					debug_f(4, "Unable to cancel subscription because address does not match current subscription\n");
			}
			node = node->next;
		}
	}
	return false;
}

/*
	addSearchSubscription adds a subscription for SDMSearch requests according to the input information.  This function first checks
	to be sure that the current request is not a duplicate subscription.
	INPUTS:
		ip - The IP address of the subscriber
		port - The port of the subscriber
		source - The component identifier of the interested device or application to which the subscription is intended
		itemname - The itemname (ReqReg) or search query (Search) the subscriber is interested in
		ID - The identifier number for this subscription stream
		error - (output reference parameter) incremented if a duplicate subscription exists
		debug - The debug level of the DataManager
	RETURNS:
		bool - Always true
*/
bool SubscriptionList::addSearchSubscription(const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* itemname, int ID, int& error, int debug)
{
	SubscriptionListNode* node;
		
	node = head;
	while(node!=NULL)	//Check to see if subscription is a duplicate
	{
		if(node->data->getInuse() == true)	//Check to see if in use
		{
			if(node->data->getDestination() == SubscriberId)
			{
				if(node->data->getSource()==source)
				{
					if(node->data->getItems() == true)	//Check to see if message the are items in use
					{
						if(strcmp(node->data->getItemName(),itemname) == 0)  //Check to see if the item_name matches
						{
							if(node->data->getmID() == SEARCH_REPLY)
							{
								error++;
								debug_f(2, "Multiple subscription trying to be entered Error Count: %d\n",error);
								return true;	//No need to enter subscription because it is a duplicate
							}
						}
					}
				}
			}
		}
		node = node->next;
	}
	node = head;
	while(node!=NULL)	//Find an array location in the subscription list that is not in use
	{
		if(node->data->getInuse() == false)
			break;
		node = node->next;
	}
	if(node==NULL)
	{
		addSubscription(new Subscription());
		node = tail;
	}
	//Enter the subscription
	node->data->setItemName(itemname);
	node->data->setDestination(SubscriberId);
	node->data->setSource(source);
	node->data->setmID(SEARCH_REPLY); //Copy the message id into subscription
	node->data->setInuse(true);	//Set subscription in use
	node->data->setItems(true);	//Set subscription items
	node->data->setID(ID);
	return true;
}

/*
	removeSearchSubscription removes a subscription from an SDMSearch query.
	INPUTS:
		ip - The IP address of the subscriber
		port - The port of the subscriber
		debug - The debug level of the DataManager
	RETURNS:
		bool - Always false
*/
bool SubscriptionList::removeSearchSubscription(const SDMComponent_ID& SubscriberId, int debug)
{
	SubscriptionListNode* node;
	
	node = head;
	while(node!=NULL)
	{
		if(node->data->getInuse() == true)	//Check to see if subscription in use
		{
			if (node->data->getDestination() == SubscriberId)
			{
				if(node->data->getmID() == SEARCH_REPLY)	//Check to see if message ID match
				{
					if(node->data->getItems() == true)	//Check to see it item is set
					{
						node->data->setPort(0);	//Set port to 0
						node->data->setmID(0);	//Set message id to 0
						node->data->setInuse(false);	//Set in use to 0
						node->data->setItems(false);	//Set items to 0
						node->data->setID(0);
						debug_f(4, "Canceled subscription\n");
					}
					else
						debug_f(4, "Unable to cancel subscription because there is no items\n");
				}
				else
					debug_f(4, "Unable to cancel subscription because message ID does not match current subscriptions\n");
			}
			else
				debug_f(4, "Unable to cancel subscription because address does not match current subscription\n");
		}
		node = node->next;
	}
	return false;
}

/*
	removeSearchSubscription removes a subscription from an SDMSearch query.
	INPUTS:
		ip - The IP address of the subscriber
		port - The port of the subscriber
		source - The component identifier of the interested sensor or application
		itemname - The search query issued
		debug - The debug level of the DataManager
	RETURNS:
		bool - Always false
*/
bool SubscriptionList::removeSearchSubscription(const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* itemname, int debug)
{
	SubscriptionListNode* node;

	if (itemname==NULL)
		return false;
	
	node = head;
	while(node!=NULL)
	{
		if(node->data->getInuse() == true)	//Check to see if subscription in use
		{
			if (node->data->getDestination() == SubscriberId)
			{
				if(node->data->getmID() == SEARCH_REPLY)	//Check to see if message ID match
				{
					if(node->data->getSource()==source)
					{
						if(strcmp(node->data->getItemName(),itemname) == 0)  //Check to see if the item_name matches
						{
							node->data->setPort(0);	//Set port to 0
							node->data->setmID(0);	//Set message id to 0
							node->data->setInuse(false);	//Set in use to 0
							node->data->setItems(false);	//Set items to 0
							node->data->setID(0);
							debug_f(4, "Canceled subscription\n");
							return false;
						}
						else
							debug_f(4, "Unable to cancel subscription because there is no item_name\n");
					}
					else
						debug_f(4, "Unable to sources do not match\n");
				}
				else
					debug_f(4, "Unable to cancel subscription because message ID does not match current subscriptions\n");
			}
			else
				debug_f(4, "Unable to cancel subscription because address does not match current subscription\n");
		}
		node = node->next;
	}
	return false;
}

/*
	addVarReqSubscription adds a subscription for SDMSearch requests according to the input information.  This function first checks
	to be sure that the current request is not a duplicate subscription.
	INPUTS:
		ip - The IP address of the subscriber
		port - The port of the subscriber
		source - The component identifier of the interested device or application to which the subscription is intended
		interface - The string version of the message id interface pair
		itemname - The variable name
		ID - The identifier number for this subscription stream
		error - (output reference parameter) incremented if a duplicate subscription exists
		debug - The debug level of the DataManager
	RETURNS:
		bool - Always true
*/
bool SubscriptionList::addVarReqSubscription(const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* interface, const char* itemname, int ID, int& error, int debug)
{
	SubscriptionListNode* node;
		
	node = head;
	while(node!=NULL)	//Check to see if subscription is a duplicate
	{
		if(node->data->getInuse() == true)	//Check to see if in use
		{
			if (node->data->getDestination() == SubscriberId)
			{
				if(node->data->getSource()==source)
				{
					if(node->data->getItems() == true)	//Check to see if message the are items in use
					{
						if(strcmp(node->data->getItemName(),itemname) == 0)  //Check to see if the item_name matches
						{
							if(strcmp(node->data->getInterface(),interface)==0)	//Check to see if interface name matches
							{
								if(node->data->getmID() == VAR_REQ_REPLY)
								{
									error++;
									debug_f(2, "Multiple subscription trying to be entered Error Count: %d\n",error);
									return true;	//No need to enter subscription because it is a duplicate
								}
							}
						}
					}
				}
			}
		}
		node = node->next;
	}
	node = head;
	while(node!=NULL)	//Find an array location in the subscription list that is not in use
	{
		if(node->data->getInuse() == false)
			break;
		node = node->next;
	}
	if(node==NULL)
	{
		addSubscription(new Subscription());
		node = tail;
	}
	//Enter the subscription
	node->data->setItemName(itemname);
	node->data->setDestination(SubscriberId);
	node->data->setSource(source);
	node->data->setmID(VAR_REQ_REPLY); //Copy the message id into subscription
	node->data->setInuse(true);	//Set subscription in use
	node->data->setItems(true);	//Set subscription items
	node->data->setID(ID);
	node->data->setInterface(interface);
	return true;
}

/*
	removeVarReqSubscription removes a subscription from an SDMSearch query.
	INPUTS:
		ip - The IP address of the subscriber
		port - The port of the subscriber
		debug - The debug level of the DataManager
	RETURNS:
		bool - Always false
*/
bool SubscriptionList::removeVarReqSubscription(const SDMComponent_ID& SubscriberId, int debug)
{
	SubscriptionListNode* node;
	
	node = head;
	while(node!=NULL)
	{
		if(node->data->getInuse() == true)	//Check to see if subscription in use
		{
			if (node->data->getDestination() == SubscriberId)
			{
				if(node->data->getmID() == VAR_REQ_REPLY)	//Check to see if message ID match
				{
					if(node->data->getItems() == true)	//Check to see it item is set
					{
						node->data->setPort(0);	//Set port to 0
						node->data->setmID(0);	//Set message id to 0
						node->data->setInuse(false);	//Set in use to 0
						node->data->setItems(false);	//Set items to 0
						node->data->setID(0);
						debug_f(4, "Canceled subscription\n");
					}
					else
						debug_f(4, "Unable to cancel subscription because there is no items\n");
				}
				else
					debug_f(4, "Unable to cancel subscription because message ID does not match current subscriptions\n");
			}
			else
				debug_f(4, "Unable to cancel subscription because address does not match current subscription\n");
		}
		node = node->next;
	}
	return false;
}

/*
	removeVarReqSubscription removes a subscription from an SDMSearch query.
	INPUTS:
		ip - The IP address of the subscriber
		port - The port of the subscriber
		source - The component identifier of the interested sensor or application
		interface - The string version of the message id interface pair
		itemname - The variable name
		debug - The debug level of the DataManager
	RETURNS:
		bool - Always false
*/
bool SubscriptionList::removeVarReqSubscription(const SDMComponent_ID& SubscriberId, const SDMComponent_ID& source, const char* interface, const char* itemname, int debug)
{
	SubscriptionListNode* node;

	if (itemname==NULL)
		return false;
	
	node = head;
	while(node!=NULL)
	{
		if(node->data->getInuse() == true)	//Check to see if subscription in use
		{
			if (node->data->getDestination() == SubscriberId)
			{
				if(node->data->getmID() == VAR_REQ_REPLY)	//Check to see if message ID match
				{
					if(node->data->getSource()==source)
					{
						if(strcmp(node->data->getItemName(),itemname) == 0)  //Check to see if the item_name matches
						{
							node->data->setPort(0);	//Set port to 0
							node->data->setmID(0);	//Set message id to 0
							node->data->setInuse(false);	//Set in use to 0
							node->data->setItems(false);	//Set items to 0
							node->data->setID(0);
							debug_f(4, "Canceled subscription\n");
							return false;
						}
						else
							debug_f(4, "Unable to cancel subscription because there is no item_name\n");
					}
					else
						debug_f(4, "Unable to sources do not match\n");
				}
				else
					debug_f(4, "Unable to cancel subscription because message ID does not match current subscriptions\n");
			}
			else
				debug_f(4, "Unable to cancel subscription because address does not match current subscription\n");
		}
		node = node->next;
	}
	return false;
}

/*
	operator= (Assignment operator) deletes the current instance's subscription list and copies the subscription list of the
	right operand.
	INPUTS:
		b - The right operand
	RETURNS:
		SubscriptionList& - Reference to "this"
*/
SubscriptionList& SubscriptionList::operator=(const SubscriptionList& b)
{
	deleteList(head);
	head = copyList(b.head,&tail);
	return *this;
}

