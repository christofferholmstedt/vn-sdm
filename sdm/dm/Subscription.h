/******************************************************************************************************************************

	The Subscription class holds the necessary information needed to create a subscription entry for the SubscriptionList
	class.  These subscription entries are used by the DataManager for various device and application subscriptions.
	Including subscription to the DataManager's notification messages, subscriptions to SDMReqReg queries with future and
	cancellation reply types, and subscriptions to SDMSearch queries with future reply types.

******************************************************************************************************************************/
#ifndef __SDM_SUBSCRIPTION_H_
#define __SDM_SUBSCRIPTION_H_

#include "../common/message/SDMComponent_ID.h"
#include "../common/message/SDMMessage_ID.h"

class Subscription
{
public:
	Subscription();
	Subscription(const Subscription&);

	virtual ~Subscription();

	void setAddress(char* new_IP);
	void setPort(unsigned short new_port);
	void setmID(int new_mID); SDM_DEPRECATED
	void setmID(const SDMMessage_ID& NewMid);
	void setInuse(bool new_inuse);
	void setID(int new_ID);
	void setItemName(const char* new_itemname);
	void setQuallist(const char* new_quallist);
	void setItems(bool new_items);
	void setDestination(const SDMComponent_ID& new_destination);
	void setSource(const SDMComponent_ID& new_source);
	void setDevice(const char* new_device);
	void setInterface(const char* new_interface);
	char* getAddress(void) const;
	unsigned short getPort(void) const;
	int getmID(void) const;
	bool getInuse(void) const { return m_bInUse; }
	const char* getItemName(void) const { return m_strItemName; }
	const char* getQuallist(void) const { return m_strQualList; }
	bool getItems(void) const { return m_bHasItems; }
	int getID(void) const { return m_iID; }
	SDMComponent_ID getDestination(void) const { return m_idSubscriber; }
	SDMComponent_ID getSource(void) const { return m_idSource; }
	const char* getDevice(void) const { return m_strDevice; }
	const char* getInterface(void) const { return m_strInterface; }

	Subscription& operator=(const Subscription&);
private:
	SDMMessage_ID m_SubMessageID;	//The message ID to which this entry is subscribed
	bool m_bInUse;			//Whether the subscription entry is in use
	int m_iID;			//The ID number associated with this subscription stream
	char* m_strItemName;		//The item_name field for the subscription
	char* m_strQualList;		//The qual_list field for the subscription
	SDMComponent_ID m_idSubscriber;	//The destination component identifier for subscription replies
	SDMComponent_ID m_idSource;	//The source component identifier of the interested device
	char* m_strDevice;		//The defice field for the subscription
	char* m_strInterface;		//The interface field for the subscription
	bool m_bHasItems;		//Whether this list is associated with subscription items
};

#endif
