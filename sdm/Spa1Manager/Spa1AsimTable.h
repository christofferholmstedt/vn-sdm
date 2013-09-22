#ifndef __SPA1_ASIM_TABLE_H__
#define __SPA1_ASIM_TABLE_H__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include "Spa1Asim.h"
#include "Spa1Translator.h"
#include "../common/Debug.h"
#include "../common/message/SDMCancelxTEDS.h"
#include "../common/message/SDMData.h"

/**
* @class Spa1AsimTable
*
* @brief Defines the Spa1AsimTable object for use by the SPA-1 Manager
*
* @author Bryan Hansen
* @date 01/13/2010
*/
class Spa1AsimTable
{
public:
	Spa1AsimTable();
	bool checkAddressUsed(unsigned char address);
	void addAsim(Spa1Asim* asim);
	void removeAsim(unsigned char address);
	unsigned char getNextAddress();
	Spa1Asim* getAsimBySensorId(unsigned long sensorId);
	Spa1Asim* getAsimByGuid(int guid);
	Spa1Asim* getAsimBySensorIndex(unsigned short sensorIndex);
	void sendToAsims();
	void recvFromAsims();
	void checkMsgsFromAsim();
	void cancelSdmRegistrations();
	int getAsimCount();
	void printAsimData();
	void printLinkedList();

private:
	///Next sensor index to assign when a ASIM is discovered
	unsigned short nextSensorIndex;

	///Pointer to the head of the table (linked list)
	Spa1Asim* head;

	//Pointer to the tail of the table (linked list)
	Spa1Asim* tail;

	///An array used to specify used and available addresses in the I2C bus
	bool addressSpace[128];

	///The number of ASIMs currently registered
	int asimCount;

	///Mutex which must be held when accessing the Spa1AsimTable
	pthread_mutex_t asimTableMutex;
};

#endif
