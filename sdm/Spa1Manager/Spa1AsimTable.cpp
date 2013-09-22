#include "Spa1AsimTable.h"

extern int debug;

/**
* Default constructor for the Spa1AsimTable object
*
*/
Spa1AsimTable::Spa1AsimTable() : head(NULL), tail(NULL), nextSensorIndex(2), asimCount(0)
{
   memset (addressSpace, 0, 128);
   memset (addressSpace, 1, 16);  //First 16 addresses are reserved by the I2C standard or by us for future use
	pthread_mutex_init(&asimTableMutex, NULL);
}

/**
* Checks to see if an I2C address is currently in use
*
* @param address The I2C address to check for availability
*
* @return A bool True meaning the address is used, false means it is available
*/
bool Spa1AsimTable::checkAddressUsed(unsigned char address)
{
   return addressSpace[address];
}

/**
* Adds a Spa1Asim to the table
*
* @param asim A pointer to the new ASIM to add to the table
*/
void Spa1AsimTable::addAsim(Spa1Asim* asim)
{
	pthread_mutex_lock(&asimTableMutex);
   addressSpace[asim->getI2cAddress()] = 1;
	asim->setSensorIndex(nextSensorIndex);

	nextSensorIndex++;

   if (head == NULL)
   {
      head = asim;
      tail = head;
   }
   else
   {
      tail->next = asim;
      tail = tail->next;
   }
	asimCount++;
	pthread_mutex_unlock(&asimTableMutex);
}


/**
* Removes a Spa1Asim from the table
*
* @param address The I2C address of the ASIM to remove
*/
void Spa1AsimTable::removeAsim(unsigned char address)
{
   Spa1Asim* toRemove;
   Spa1Asim* cur;

   addressSpace[address] = 0;

	//No mutexes here as this is only called when the mutex is already held for the table
   if (head != NULL)
   {
      if (head->getI2cAddress() == address)
      {
         toRemove = head;
         head = head->next;
         delete toRemove;
			asimCount--;
         return;
      }

      for (cur = head; cur->next != tail; cur = cur->next)
      {
         if (cur->next->getI2cAddress() == address)
         {
            toRemove = cur->next;
            cur->next = cur->next->next;
            delete toRemove;
				asimCount--;
            return;
         }
      }

      if (tail->getI2cAddress() == address)
      {
         toRemove = tail;
         tail = cur;
         cur->next = NULL;
         delete toRemove;
			asimCount--;
      }
   }
}

/**
* Gets a Spa1Asim from the table by its Sensor Id
*
* @param sensorId The 4 byte SDM sensorId as assigned by the DataManager
*
* @return A Spa1Asim* which points to the requested Spa1Asim object
*/
Spa1Asim* Spa1AsimTable::getAsimBySensorId(unsigned long sensorId)
{
	unsigned short sensorIndex = sensorId & 0x00ff;  //Chop off top two bytes used by the SDM
	return getAsimBySensorIndex(sensorIndex);
}

/**
* Gets a Spa1Asim from the table by its Sensor Index
*
* @param sensorId The 2 byte sensor index as assigned by the Spa1Manager
*
* @return A Spa1Asim* which points to the requested Spa1Asim object
*/
Spa1Asim* Spa1AsimTable::getAsimBySensorIndex(unsigned short sensorIndex)
{
	Spa1Asim* cur;

	pthread_mutex_lock(&asimTableMutex);
	for (cur = head; cur != NULL; cur = cur->next)
	{
		if(cur->getSensorIndex() == sensorIndex)
		{
			pthread_mutex_unlock(&asimTableMutex);
			return cur;
		}
	}
	pthread_mutex_unlock(&asimTableMutex);

	return NULL;
}

/**
* Gets a Spa1Asim from the table by the GUID it used to gain I2C arbitration
*
* @param guid The 4 byte buid used to gain arbitration on the I2C bus
*
* @return A Spa1Asim* which points to the requested Spa1Asim object
*/
Spa1Asim* Spa1AsimTable::getAsimByGuid(int guid)
{
	Spa1Asim* cur;

	pthread_mutex_lock(&asimTableMutex);
	for (cur = head; cur != NULL; cur = cur->next)
	{
		if(cur->getGuid() == guid)
		{
			pthread_mutex_unlock(&asimTableMutex);
			return cur;
		}
	}
	pthread_mutex_unlock(&asimTableMutex);

	return NULL;
}

/**
* Function to write data out to the ASIMs during the round robin phase
*
* Sending data to ASIMs in this round robin fashion should prevent any ASIMs
* from being ignored or prioritized
*/
void Spa1AsimTable::sendToAsims()
{
	unsigned char buf[MAX_ASIM_MSG_SIZE];
	int msgSize;

	pthread_mutex_lock(&asimTableMutex);
	for(Spa1Asim* cur = head; cur != NULL; cur = cur->next)
	{
		if(cur->sendToQueue.getNumMsgs() > 0)
		{
			msgSize = cur->sendToQueue.getMsg(buf, MAX_ASIM_MSG_SIZE); //Retreive msg from queue
			if(msgSize > 0)
			{
				cur->sendToAsim(buf, msgSize);
				debug_f(2, "Spa1Manager: Sent %i byte msg to ASIM %i\n", msgSize, cur->getSensorIndex());
			}
			else
			{
				printf("Spa1Queue: Error retreiving msg from queue to send to ASIM\n");
			}
		}
	}
	pthread_mutex_unlock(&asimTableMutex);
}

/**
* Function to read data from the ASIMs during the round robin phase
*
* Reading data from ASIMs in this round robin fashion should prevent any ASIMs
* from being ignored or prioritized
*/
void Spa1AsimTable::recvFromAsims()
{
	unsigned char buf[MAX_ASIM_MSG_SIZE];
	int msgSize;
	SDMCancelxTEDS cancelxTEDSMsg;

	pthread_mutex_lock(&asimTableMutex);
	for(Spa1Asim* cur = head; cur != NULL; cur = cur->next)
	{
		msgSize = cur->recvFromAsim(buf, MAX_ASIM_MSG_SIZE);

		if(msgSize > 0) //Msg Received
		{
			cur->recvFromQueue.putMsg(buf, msgSize);  //Add msg to ASIM's queue
			debug_f(2, "Spa1Manager: Received Msg from ASIM %i and added it to it's outgoing queue\n", cur->getSensorIndex());
		}
		else if(msgSize == -1)  //ASIM did not respond
		{
			cur->incrementFailCount();
			debug_f(2, "Spa1Manager: ASIM %i unresponsive, fail count: %i\n", cur->getSensorIndex(), cur->getFailCount());
			if(cur->getFailCount() > MAX_ASIM_FAILURES)
			{
				cancelxTEDSMsg.source.setPort(PORT_SPA1_MANAGER);
				cancelxTEDSMsg.source.setSensorID(cur->getSensorIndex());
				cancelxTEDSMsg.Send();
				debug_f(2, "Spa1Manager: Canceling xTEDS and removing ASIM %i from ASIM table\n", cur->getSensorIndex());
				removeAsim(cur->getI2cAddress());
			}
		}
	}
	pthread_mutex_unlock(&asimTableMutex);
}

/**
* Function called periodically to check the ASIMs to see if they have any
* data or status messages queued up in their output buffer that need to be
* handled.
*
* If a data message is pulled from an ASIMs queue, the message is published.  If
* there are no subscribers for the given message then a cancel data message is sent
* to the ASIM so that it will stop producing that data.
* Status messages are examined and if an error bit is set a message is currently printed
* to the screen. 
*/
void Spa1AsimTable::checkMsgsFromAsim()
{
	unsigned char buf[MAX_ASIM_MSG_SIZE];
	Spa1Translator translator;
	short msgSize;

	pthread_mutex_lock(&asimTableMutex);
	for(Spa1Asim* cur = head; cur != NULL; cur = cur->next)
	{
		if(cur->recvFromQueue.getNumMsgs() > 0) //Msgs to be looked at or sent out
		{
			debug_f(2, "Spa1Manager: %i msgs in ASIM %i's outgoing queue\n", cur->recvFromQueue.getNumMsgs(), cur->getSensorIndex());
			cur->recvFromQueue.getMsg(buf, MAX_ASIM_MSG_SIZE);
			memcpy(&msgSize, &buf[1], 2);
			msgSize = SDM_ntohs(msgSize);
			switch(buf[0])
			{
				case 'D':
					if(cur->subscriptions.Publish(buf[3], buf[4], (char*)&buf[5], msgSize))
					{
						debug_f(2, "Spa1Manager: Published data from ASIM %i for msg (%i,%i)\n", cur->getSensorIndex(), buf[3], buf[4]);
					}
					else
					{
						debug_f(2, "Spa1Manager: Received data from ASIM %i for msg (%i,%i), but no subscribers\n", cur->getSensorIndex(), buf[3], buf[4]);
						msgSize = translator.packageCancelData(buf[3], buf[4], buf, MAX_ASIM_MSG_SIZE);
						cur->sendToAsim(buf, msgSize);  //Send cancel data msg to ASIM
					}
					break;
				case 'S':
					debug_f(2, "Spa1Manager: Received Status from ASIM %i: 0x%02x\n", cur->getSensorIndex(), buf[3]);

					if(buf[3] & 0x80)  //Error bit(s) set  //TODO: Are there any actions which should be taken if one of these errors is reported?
					{
						if(buf[3] & 0x40)
						{
							debug_f(1, "Spa1Manager: ASIM %i reported an illegal opcode error\n", cur->getSensorIndex());
						}
						if(buf[3] & 0x20)
						{
							debug_f(1, "Spa1Manager: ASIM %i reported an unknown interface id and/or msg id\n", cur->getSensorIndex());
						}
						if(buf[3] & 0x10)
						{
							debug_f(1, "Spa1Manager: ASIM %i reported a self-test failure\n", cur->getSensorIndex());
						}
					}
					else if(buf[3] != 0)  //Operational status bits set
					{
						//TBD
					}
					break;
				default:
					break;
			}
		}
	}
	pthread_mutex_unlock(&asimTableMutex);
}

/**
* Cancels the SDM registrations for all registered SPA-1 ASIMs
*
*/
void Spa1AsimTable::cancelSdmRegistrations()
{
	SDMCancelxTEDS cancelxTEDSMsg;
	cancelxTEDSMsg.source.setPort(PORT_SPA1_MANAGER);

	for(Spa1Asim* cur = head; cur != NULL; cur = cur->next)
	{
		cancelxTEDSMsg.source.setSensorID(cur->getSensorIndex());
		cancelxTEDSMsg.Send();
		debug_f(2, "Spa1Manager: Canceling xTEDS for ASIM %i\n", cur->getSensorIndex());
	}
}

/**
* Utility function to print out the asim table along with details about each asim
*
*/
void Spa1AsimTable::printAsimData()
{
	printf("\n*********ASIM Table - size: %i************\n", asimCount);
	for(Spa1Asim* cur = head; cur != NULL; cur = cur->next)
	{
		printf("\tASIM %i - RegState: %i, I2C Addr: 0x%x, GUID: %i, FailCount: %i\n", cur->getSensorIndex(), cur->getRegState(), cur->getI2cAddress(), cur->getGuid(), cur->getFailCount());
	}
	printf("********************************************\n\n");
}

/**
* Returns the number of currently registered SPA-1 ASIMs
*
* @return An int containing the number of registered SPA-1 ASIMs
*/
int Spa1AsimTable::getAsimCount()
{
	return asimCount;
}
