#include "Subscription.h"
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
extern "C"
{
#include "../common/MemoryUtils.h"
}

Subscription::Subscription():m_SubMessageID(),m_bInUse(false),m_iID(0),m_strItemName(NULL),m_strQualList(NULL),m_idSubscriber(),m_idSource(),m_strDevice(NULL),m_strInterface(NULL),m_bHasItems(false)
{
}

Subscription::Subscription(const Subscription& b):m_SubMessageID(),m_bInUse(false),m_iID(0),m_strItemName(NULL),m_strQualList(NULL),m_idSubscriber(),m_idSource(),m_strDevice(NULL),m_strInterface(NULL),m_bHasItems(false)
{
	if(m_strItemName!=NULL) free(m_strItemName);
	m_strItemName = SDM_strdup(b.m_strItemName);
	if(m_strQualList!=NULL) free(m_strQualList);
	m_strQualList = SDM_strdup(b.m_strQualList);
	if(m_strDevice!=NULL) free(m_strDevice);
	m_strDevice = SDM_strdup(b.m_strDevice);
	if(m_strInterface!=NULL) free(m_strInterface);
	m_strInterface = SDM_strdup(b.m_strInterface);
	m_idSubscriber = b.m_idSubscriber;
	m_bInUse = b.m_bInUse;
	m_iID = b.m_iID;
	m_bHasItems = b.m_bHasItems;
}

Subscription::~Subscription()
{
	if(m_strItemName!=NULL) free(m_strItemName);
	if(m_strQualList!=NULL) free(m_strQualList);
	if(m_strDevice!=NULL) free(m_strDevice);
	if(m_strInterface!=NULL) free(m_strInterface);
}

void Subscription::setAddress(char* new_IP)
{
	m_idSubscriber.setAddress(inet_addr(new_IP));
}

void Subscription::setPort(unsigned short new_port)
{
	m_idSubscriber.setPort(new_port);
}

void Subscription::setmID(int new_mID)
{
	m_SubMessageID = new_mID;
}

void Subscription::setInuse(bool new_inuse)
{
	m_bInUse = new_inuse;
}

void Subscription::setID(int new_ID)
{
	m_iID = new_ID;
}

void Subscription::setItemName(const char* new_itemname)
{
	if(m_strItemName!=NULL) free(m_strItemName);
	m_strItemName = SDM_strdup(new_itemname);
}

void Subscription::setQuallist(const char* new_quallist)
{
	if(m_strQualList!=NULL) free(m_strQualList);
	m_strQualList = SDM_strdup(new_quallist);
}

void Subscription::setItems(bool new_items)
{
	m_bHasItems = new_items;
}

void Subscription::setDestination(const SDMComponent_ID& new_destination)
{
	m_idSubscriber = new_destination;
}

void Subscription::setSource(const SDMComponent_ID& new_source)
{
	m_idSource = new_source;
}

void Subscription::setDevice(const char* new_device)
{
	if(m_strDevice!=NULL) free(m_strDevice);
	m_strDevice = SDM_strdup(new_device);
}

void Subscription::setInterface(const char* new_interface)
{
	if(m_strInterface!=NULL) free(m_strInterface);
	m_strInterface = SDM_strdup(new_interface);
}

char* Subscription::getAddress(void) const
{
	char* addr;
	struct in_addr inaddr;
	inaddr.s_addr = m_idSubscriber.getAddress();
	addr = inet_ntoa(inaddr);
	return addr;
}

unsigned short Subscription::getPort(void) const
{
	return m_idSubscriber.getPort();
}

int Subscription::getmID(void) const
{
	return m_SubMessageID.getInterfaceMessagePair();
}

/*
-- Now inline --

int Subscription::getID(void) const
{
	return m_iID;
}

SDMComponent_ID Subscription::getDestination(void) const
{
	return m_idSubscriber;
}

SDMComponent_ID Subscription::getSource(void) const
{
	return m_idSource;
}

const char* Subscription::getDevice(void) const
{
	return m_strDevice;
}

const char* Subscription::getInterface(void) const
{
	return m_strInterface;
}

const char* Subscription::getItemName(void) const
{
	return m_strItemName;
}

const char* Subscription::getQuallist(void) const
{
	return m_strQualList;
}

bool Subscription::getInuse(void) const
{
	return m_bInUse;
}

bool Subscription::getItems(void) const
{
	return m_bHasItems;
}
*/

Subscription& Subscription::operator=(const Subscription& b)
{
	if(m_strItemName!=NULL) free(m_strItemName);
	m_strItemName = SDM_strdup(b.m_strItemName);
	if(m_strQualList!=NULL) free(m_strQualList);
	m_strQualList = SDM_strdup(b.m_strQualList);
	m_bInUse = b.m_bInUse;
	m_iID = b.m_iID;
	m_bHasItems = b.m_bHasItems;
	if(m_strDevice!=NULL) free(m_strDevice);
	m_strDevice = SDM_strdup(b.m_strDevice);
	if(m_strInterface!=NULL) free(m_strInterface);
	m_strInterface = SDM_strdup(b.m_strInterface);
	m_idSubscriber = b.m_idSubscriber;
	return *this;
}
