#ifndef __SDM_XTEDS_LIBRARY_H_
#define __SDM_XTEDS_LIBRARY_H_

#include "../common/xTEDS/xTEDS.h"
#include "../common/semaphore/semaphore.h"
#include "../common/message/SDMComponent_ID.h"
#include "../common/Regex/Regex.h"

/******************************************************************************************************************************

	The xTEDSLibrary class is used by the DataManager to store a registered xTEDS for a device or application, and all
	needed information to handle the querying and subscribing to the device or application.  This class represents the
	data nodes for a linked list (xTEDSLibraryList).  When needed an xTEDSLibrary node is dynamically allocated.  If the
	node is no longer needed, it is set to not being available but is not deallocated.  The slot can be used for a future
	registration.  This class also provides access to the tree representing the registered xTEDS, which is constructed after
	the xTEDS is set.
	
******************************************************************************************************************************/


class xTEDSLibrary
{
public:
	xTEDSLibrary();
	xTEDSLibrary(const xTEDSLibrary&);

	virtual ~xTEDSLibrary();

	bool setxTEDS(char* new_xTEDS);
	void setAddress(const SDMComponent_ID& new_idAddr);
	void setSensorID(unsigned long new_sensorID);
	void setAvailable(bool new_available);
	void setTargetPort(unsigned short new_targetport);
	void setConnections(int new_connections);
	void setActive(bool new_active);
	void setPid(unsigned long new_pid);
	void setHub(int new_hub);
	void setSPANode(char* new_locationAddress);
	void setPosted(bool new_posted);
	void setComponentID(SDMComponent_ID new_id);
	void setSPAHub(char* new_spahub);
	void setMerged(bool new_merged);
	const char* getName(void);
	const char* getxTEDS(void);
	unsigned long getAddress(void);
	unsigned long getSensorID(void);
	bool getAvailable(void);
	unsigned short getTargetPort(void);
	int getConnections(void);
	bool getActive(void);
	unsigned long getPid(void);
	int getHub(void);
	char* getSPANode(void) { return m_strSPANode; }
	const char* getSPAHub(void);
	const char* getSPAPort(void);
	bool getPosted(void);
	const char* getComponentKey(void);
	bool getMerged(void);
	SDMComponent_ID getComponentID(void);
	RegexResult XtedsRegexSearchCapturesOnly(const RegularExpression& Pattern);

	xTEDSLibrary& operator=(const xTEDSLibrary&);

	Sem* inUse;			//Semaphore to provide mutual exclusion, all reading threads must lock before accessing
	xTEDS* xtedsTree;		//The tree structure storing the xTEDS information

private:
	bool available;			//Whether this xTEDSLibrary slot is being used
	int connections;		//The number of subscribed connections to the xTEDS (number of messages consumed)
	bool active;			//Whether the device or application is currently active
	unsigned long pid;		//The PID of the xTEDS
	int hub;			//The hub number of the device
	bool posted;			//Whether a task is posted to the TaskManager
	char* m_strSPANode;		//The SPA or USB address of a device
	char* fullxTED;			//The xTEDS of the device or application
	char* tempSPAHub;		//The SPAHub address
	SDMComponent_ID* id;		//The component identifier of the xTEDS
	bool merged;			//The status of whether the xTEDS has been merged
};

#endif
