#ifndef __SPA1_ASIM_H__
#define __SPA1_ASIM_H__

#include "../common/SubscriptionManager/SubscriptionManager.h"
#include "../common/sdmLib.h"
#include "../common/message_defs.h"
#include "../common/Time/SDMTime.h"
#include "../common/Debug.h"
#include "Spa1Queue.h"
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#ifndef WIN32
#include <linux/i2c.h> /* for I2C_SLAVE */
#endif
#ifndef I2C_SLAVE
#define I2C_SLAVE 0x0703   /* Change slave address       */
#endif


#define SPA1_HEADER_SIZE 3
#define MAX_PACKET_PAYLOAD 253
#define MAX_ASIM_MSG_SIZE	256
#define ASIM_READ_TIMEOUT 3
#define MAX_ASIM_FAILURES	3

enum RegistrationState { SENT_HELLO, RECVD_ACK, RECVD_REG, SENT_XTEDS, RECVD_ID };

/**
* @class Spa1Asim
*
* @brief Defines the Spa1Asim object for use by the SPA-1 Sensor Manager
*
* The Spa1Asim objects holds all information about a single SPA-1 ASIM that
* is registered with the SPA-1 Manager.  Utility functions are also included
* to write to/read from the ASIM.
*
* @author Bryan Hansen, Jacob Christensen
* @date 12/03/2009
*/
class Spa1Asim
{
   public:
      char* xTEDS; //Holds this ASIM's xTEDS in plain text format
      int xTEDSSize;

      ///Queue to send messages to the ASIM
      Spa1Queue sendToQueue;

      ///Queue used to recv messages from the ASIM
      Spa1Queue recvFromQueue;

      ///Manages subscriptions for this ASIM
      SubscriptionManager subscriptions;

      ///Pointer to next Spa1Asim in a list
      Spa1Asim* next;

      Spa1Asim(int busFd, unsigned char newAddress, int guid);
      int recvFromAsim(unsigned char* buf, size_t bufSize, bool blocking = false);
      int recvXtedsFromAsim();
      int sendToAsim(unsigned char* buf, size_t msgSize);
      bool doRegistration(void);


      //Getters/Setters for private members
      unsigned char getI2cAddress();
      void setI2CAddress(unsigned char newAddress);
      unsigned int getSensorIndex();
      void setSensorIndex(unsigned short newSensorIndex);
		unsigned int getSensorId();
      void setSensorId(unsigned long newSensorId);
		RegistrationState getRegState();
		void setRegState(RegistrationState newState);
		int getGuid();
		void incrementFailCount();
		int getFailCount();
		int getAsimName(char* outBuf);

   private:
      ///File descriptor used for reads/writes to i2c bus
      int i2cFd;

      /// Used to uniquely identify an ASIM during registration
      int guid;

      ///ASIMs address on I2C bus
      unsigned char i2cAddress;

      ///SPA-1 Manager sensor Index, also lower two bytes of SDM SensorID
      unsigned int sensorIndex;

		///SDM sensor id, received in SDMID msg after successful registration
      unsigned int sensorId;

		///Registration state of this ASIM
		RegistrationState regState;

		//Number of times a nack was received when attempting a read from the ASIM
		int failCount;
		
		///Private utility functions
      int readPacketHeader(unsigned char* buf, bool doBlocking = false);
      double getCurTime();
};

#endif
