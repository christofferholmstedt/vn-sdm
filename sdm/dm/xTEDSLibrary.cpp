#include "xTEDSLibrary.h"

#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <regex.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../common/Exception/SDMRegexException.h"
#include "../common/ErrorUtils.h"
extern "C"
{
#include "../common/MemoryUtils.h"
}

xTEDSLibrary::xTEDSLibrary():inUse(NULL),xtedsTree(NULL),available(false),connections(0),active(false),pid(0),hub(0),posted(false),m_strSPANode(NULL),fullxTED(NULL),tempSPAHub(NULL),id(NULL),merged(false)
{
	id = new SDMComponent_ID();
	if (id == NULL)
		ErrorUtils::MemoryAllocError(__FUNCTION__);
	
	id->setSensorID(0);
	id->setPort(0);
	id->setAddress(0);
	connections = 0;
	pid = 0;
	available = true;
	active = false;
	hub = 0;
	posted = false;
	inUse = new Sem(1);
	merged = false;
}

xTEDSLibrary::xTEDSLibrary(const xTEDSLibrary& b):inUse(NULL),xtedsTree(NULL),available(false),connections(0),active(false),pid(0),hub(0),posted(false),m_strSPANode(NULL),fullxTED(NULL),tempSPAHub(NULL),id(NULL),merged(false)
{
	if(fullxTED!=NULL) free(fullxTED);
	fullxTED = SDM_strdup(b.fullxTED);
	if(m_strSPANode!=NULL) free(m_strSPANode);
	m_strSPANode = SDM_strdup(b.m_strSPANode);
	if(xtedsTree!=NULL) delete(xtedsTree);
	xtedsTree = b.xtedsTree;
	if(id!=NULL) delete(id);	
	id = b.id;
	if(tempSPAHub!=NULL) free(tempSPAHub);
	tempSPAHub = b.tempSPAHub;
	connections = b.connections;
	pid = b.pid;
	available = b.available;
	active = b.active;
	hub = b.hub;
	posted = b.posted;
	merged = b.merged;
}
/****
	Destructor - Frees all dynamically allocated members.
****/
xTEDSLibrary::~xTEDSLibrary()
{
	if(xtedsTree!=NULL) delete(xtedsTree);
	if(fullxTED!=NULL) free(fullxTED);
	if(m_strSPANode!=NULL) free(m_strSPANode);
	if(id!=NULL) delete(id);
	if(tempSPAHub!=NULL) free(tempSPAHub);
	delete(inUse);
}
/****
	setxTEDS sets the xTEDS for this xTEDSLibrary.  This function will also free any previosly set xTEDS and the associated
	xtedsTree member.  A new xtedsTree is built after parsing the xTEDS.
	Params:
		new_xTEDS - The xTEDS to be set.
	Returns:
		bool - True if the xTEDS was successfully parsed, false otherwise.
****/
bool xTEDSLibrary::setxTEDS(char* new_xTEDS)
{
	if(fullxTED!=NULL) free(fullxTED);
	int length = strlen(new_xTEDS);
	fullxTED = SDM_strndup(new_xTEDS,length);
	if(xtedsTree!=NULL) delete(xtedsTree);
	xtedsTree = new xTEDS();
	if (xtedsTree == NULL)
		ErrorUtils::MemoryAllocError(__FUNCTION__);
	
	bool bParseResult = xtedsTree->Parse(new_xTEDS);
	if (false == bParseResult)
	{
		delete xtedsTree;
		xtedsTree = NULL;
	}
	return bParseResult;
}
/****
	setAddress sets the IP address member of the "id" SDMComponent_ID member.
	Params:
		new_ip - The character string IP address to set.
****/
void xTEDSLibrary::setAddress(const SDMComponent_ID& new_idAddr)
{
	id->setAddress(new_idAddr.getAddress());
}
/****
	setSensorID sets the sensorID member of the "id" SDMComponent_ID member.
****/
void xTEDSLibrary::setSensorID(unsigned long new_sensorID)
{
	id->setSensorID(new_sensorID);
}
/****
	setAvailable sets the "available" member, indicating whether this xTEDSLibrary node is being used.
	Params:
		new_available - The value to set, true if the xTEDSLibrary node is being used, false otherwise.
****/
void xTEDSLibrary::setAvailable(bool new_available)
{
	available = new_available;
}
/****
	setTargetPort sets the port member of the "id" SDMComponent_ID member.
	Params:
		new_targetport - The port value to set.
****/
void xTEDSLibrary::setTargetPort(unsigned short new_targetport)
{
	id->setPort(new_targetport);
}
/****
	setConnections sets the number of connections to the xTEDS.  This represents the number of consumed
	data messages to the device or application.
	Params:
		new_connections - The new number of connections to the xTEDS.
****/
void xTEDSLibrary::setConnections(int new_connections)
{
	connections = new_connections;
}
/****
	setActive sets whether the xTEDS of the application should be active in the SDM system.  This is mainly 
	applicable to applications, the xTEDS is still registered but is not active for registrations until
	it is set to active again.
	Params:
		new_active - The value to indicate whether active
****/
void xTEDSLibrary::setActive(bool new_active)
{
	active = new_active;
}
/****
	setPid sets the application PID number.  This is the SDM process identifier number.
	Params:
		new_pid - The identifier number to set for this xTEDS.
****/
void xTEDSLibrary::setPid(unsigned long new_pid)
{
	pid = new_pid;
}
/****
	setHub sets the hub number to which the device is connected.  This is only applicable to devices, and
	not applications.
	Params:
		new_hub - The new hub number value.
****/
void xTEDSLibrary::setHub(int new_hub)
{
	hub = new_hub;
}
/****
	setSPANode sets the USB path of the connected device.  This is only applicable to devices,
	and not applications.
	Params:
		new_locationAddress - The new USB path of the device.
****/
void xTEDSLibrary::setSPANode(char* new_locationAddress)
{
	if(m_strSPANode!=NULL) free(m_strSPANode);
	m_strSPANode = SDM_strdup(new_locationAddress);
}
/****
	setSPAHub sets the SPAHub address of the connected device.  This is only applicable to devices,
	and not applications.
	Params:
		new_spahub - The new SPAHub address to set.
****/
void xTEDSLibrary::setSPAHub(char* new_spahub)
{
	if(tempSPAHub!=NULL) free(tempSPAHub);
	tempSPAHub = SDM_strdup(new_spahub);
}
/****
	setPosted sets whether the application has been posted to the TaskManager.  This is applicable
	only to applications and not devices.
	Params:
		new_posted - Whether the application has been posted.
****/
void xTEDSLibrary::setPosted(bool new_posted)
{
	posted = new_posted;
}
/****
	setMerged set whether the xTEDS has been merged with information from the sdm.config file.
	Params:
		new_merged - Whether the xTEDS has been merged
****/
void xTEDSLibrary::setMerged(bool new_merged)
{
	merged = new_merged;
}
/****
	getName returns the name of the device from the associated xTEDS tree.
	Returns:
		char * - The name of the device, or NULL if not set.
****/
const char* xTEDSLibrary::getName(void)
{
	if (xtedsTree != NULL)
		return xtedsTree->getDeviceName();
	return NULL;
}
/****
	getxTEDS returns the xTEDS of the connected device or application.
	Returns:
		char * - The xTEDS of the device, or NULL if the xTEDS hasn't been set.
****/
const char* xTEDSLibrary::getxTEDS(void)
{
	return fullxTED;
}
/****
	getAddress returns the IP address, in number-dot-notation, of the connected device or application.
	Returns:
		char * - The IP address of the device or application.
****/
unsigned long xTEDSLibrary::getAddress(void)
{
	return id->getAddress();
}
/****
	getSensorID returns the sensor identifier number of the device or application.
	Returns:
		unsigned long - The sensor identifier number of the device or application.
****/
unsigned long xTEDSLibrary::getSensorID(void)
{
	return id->getSensorID();
}
/****
	getAvailable returns whether the xTEDSLibrary slot is being used.
	Returns:
		bool - True if the xTEDSLibrary slot is in use, false otherwise.
****/
bool xTEDSLibrary::getAvailable(void)
{
	return available;
}
/****
	getTargetPort returns the port of the device or application.
	Returns:
		long - The port number of the device or application.
****/
unsigned short xTEDSLibrary::getTargetPort(void)
{
	return id->getPort();
}
/****
	getConnections returns the number of connections to this xTEDSLibrary (number of consumed messages).
	Returns:
		int - the number of connections to the xTEDSLibrary.
****/
int xTEDSLibrary::getConnections(void)
{
	return connections;
}
/****
	getActive returns whether or not the this xTEDS is active.
	Returns:
		bool - Wether the xTEDS is active
****/
bool xTEDSLibrary::getActive(void)
{
	return active;
}
/****
	getPid returns the SDM process identifier number of the application.
	Returns:
		unsigned long - The SDM process identifier number of the application.
****/
unsigned long xTEDSLibrary::getPid(void)
{
	return pid;
}
/****
	getHub returns the hub number of the connected device.
	Returns:
		int - The hub number of the connected device.
****/
int xTEDSLibrary::getHub(void)
{
	return hub;
}

/****
	getLocationAddress returns the USB path of the connected device.
	Returns:
		char * - The USB path of the connected device, or NULL if not set.
****/
/*NOW INLINE
char* xTEDSLibrary::getLocationAddress(void)
{
	return m_strSPANode;
}*/

/****
	getSPAHub returns the SPA hub of the connected device.
	Returns:
		char * - The SPA hub of the connected device, or NULL if not set.
****/
const char* xTEDSLibrary::getSPAHub(void)
{
	if(xtedsTree!=NULL)
		return xtedsTree->getSPAUHub();
	else
		return tempSPAHub;
}
/****
	getSPAPort returns the SPA port of the connected device.
	Returns:
		char * - The SPA port of the connected device, or NULL if not set.
****/
const char* xTEDSLibrary::getSPAPort(void)
{
	if(xtedsTree!=NULL)
		return xtedsTree->getSPAUPort();
	else
		return NULL;
}
/****
	getPosted returns whether the application has been posted to the TaskManager.
	Returns:
		bool - True if the application has been posted to the TaskManager, false otherwise.
****/
bool xTEDSLibrary::getPosted(void)
{
	return posted;
}
/****
	setComponentID sets the component identifier for the application or device.
	Params:
		new_id - The component identifier to set.
****/
void xTEDSLibrary::setComponentID(SDMComponent_ID new_id)
{
	id->setAddress(new_id.getAddress());
	id->setSensorID(new_id.getSensorID());
	id->setPort(new_id.getPort());
}
/****
	getComponentID returns the SDMComponent_ID of the device or application.
	Returns:
		SDMComponent_ID - The component identifier of the device or application
****/
SDMComponent_ID xTEDSLibrary::getComponentID(void)
{
	SDMComponent_ID temp;
	temp.setAddress(id->getAddress());
	temp.setSensorID(id->getSensorID());
	temp.setPort(id->getPort());
	return temp;
}
/****
	getComponentKey returns the component key of the device or application from the xTEDS tree.
	Returns:
		char * - The component key of the device or application, or NULL if the xTEDS is not available.
****/
const char* xTEDSLibrary::getComponentKey(void)
{
	if (xtedsTree != NULL)
		return xtedsTree->getComponentKey();
	return NULL;
}
/****
	getMerged returns whether the xTEDS has been merged with info from the sdm.config file
	Returns:
		bool - True if the xTEDS has been merged, false otherwise
****/
bool xTEDSLibrary::getMerged(void)
{
	return merged;
}
/****
	operator= performs a shallow copy of the xTEDSLibrary object (the xtedsTree object is not deep-copied).
****/
xTEDSLibrary& xTEDSLibrary::operator=(const xTEDSLibrary& b)
{
	if(fullxTED!=NULL) free(fullxTED);
	fullxTED = SDM_strdup(b.fullxTED);
	if(m_strSPANode!=NULL) free(m_strSPANode);
	m_strSPANode = SDM_strdup(b.m_strSPANode);
	if(xtedsTree!=NULL) delete(xtedsTree);
	xtedsTree = b.xtedsTree;
	if(id!=NULL) delete(id);
	id = b.id;
	if(tempSPAHub!=NULL) free(tempSPAHub);
	tempSPAHub = b.tempSPAHub;
	connections = b.connections;
	pid = b.pid;
	available = b.available;
	active = b.active;
	hub = b.hub;
	posted = b.posted;
	return *this;
}
/*
	Perform a regular expression search of the xTEDS based on Pattern.
 */
RegexResult xTEDSLibrary::XtedsRegexSearchCapturesOnly(const RegularExpression& Pattern)
{
	return RegexSearchCapturesOnly(fullxTED, Pattern);
}
