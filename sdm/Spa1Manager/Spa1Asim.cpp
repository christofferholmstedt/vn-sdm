#include "Spa1Asim.h"

extern int debug;

/**
* Constructor that creates a Spa1ASIM object
*/
Spa1Asim::Spa1Asim(int busFd, unsigned char newAddress, int guid) : i2cFd(busFd), i2cAddress(newAddress), guid(guid), xTEDSSize(0), failCount(0), next(NULL)
{
   // do nothing
}

/**
* Utility function for receiving messages from the ASIM.
*
* @param buf The output buffer the message will be written into
* @param bufSize The size of the output buffer
*
* @return An int containing the number of bytes actually read, -1 indicates
*           an error condition has occured.
*/
int Spa1Asim::recvFromAsim(unsigned char* buf, size_t bufSize, bool blocking)
{

#ifndef WIN32
   if (ioctl(i2cFd, I2C_SLAVE, i2cAddress) < 0)
   {
      printf("SPA-1 Manager: Error setting i2c address in recv\n");
   }
#endif

   short length = 0;
   int bytesRead = 0;

   bytesRead = readPacketHeader(buf, blocking);

   if (bytesRead == 0)
   {
      return 0;
   }

   if (bytesRead == -1)
   {
      return bytesRead;
   }

   memcpy(&length, &buf[1], 2);

   if ((unsigned short)(length + SPA1_HEADER_SIZE) > bufSize || length > MAX_PACKET_PAYLOAD)
   {
      return -1;
   }

   bytesRead += read(i2cFd, &buf[3], length);

   return bytesRead;
}

/**
* Utility function for receiving messages from the ASIM in a blocking manner.
*
* @param buf The output buffer the message will be written into
* @param bufSize The size of the output buffer
*
* @return An int containing the number of bytes actually read, -1 indicates
*           an error condition has occured.
*/
int Spa1Asim::recvXtedsFromAsim()
{
#ifndef WIN32
   if (ioctl(i2cFd, I2C_SLAVE, i2cAddress) < 0)
   {
      printf("SPA-1 Manager: Error setting i2c address in recv\n");
   }
#endif

   short length = 0;
   int bytesRead = 0;
   unsigned char headerBuf[3];
   
	usleep(1000);
   readPacketHeader(headerBuf, true);

   memcpy(&length, &headerBuf[1], 2);

	debug_f(4, "Read xTEDS Header: 0x%02x w/ length: %i\n", headerBuf[0], length);

   xTEDS = new char[length + 1];
   memset(xTEDS, 0, length + 1);

	usleep(1000);

   if (length <= MAX_PACKET_PAYLOAD)
   {
      bytesRead = read(i2cFd, &xTEDS[3], length);
   }
   else
   {
      // loop and reassemble packets
      int index = 0;
      int numberPackets = length / MAX_PACKET_PAYLOAD;
      int lastPacketLength = length % MAX_PACKET_PAYLOAD;

      // read the rest of the first packet
      bytesRead = read(i2cFd, &xTEDS[index], MAX_PACKET_PAYLOAD);
		debug_f(4, "Read %i bytes of xTEDS\n", bytesRead);
      index += MAX_PACKET_PAYLOAD;

      // read all the other packets
      for (int packet = 1; packet < numberPackets; ++packet)
      {
			usleep(1000);
         readPacketHeader(headerBuf, true);
			debug_f(4, "Read xTEDS Header: 0x%02x 0x%02x 0x%02x\n", headerBuf[0], headerBuf[1], headerBuf[2]);
			usleep(1000);
         bytesRead += read (i2cFd, &xTEDS[index], MAX_PACKET_PAYLOAD);
			debug_f(4, "Read %i bytes of xTEDS\n", bytesRead);
         index += MAX_PACKET_PAYLOAD;
      }

      // read the last packet
      if (lastPacketLength > 0)
      {
			usleep(1000);
         readPacketHeader(headerBuf, true);
			debug_f(4, "Read xTEDS Header: 0x%02x 0x%02x 0x%02x\n", headerBuf[0], headerBuf[1], headerBuf[2]);
			usleep(1000);
         bytesRead += read (i2cFd, &xTEDS[index], lastPacketLength);
			debug_f(4, "Read %i bytes of xTEDS\n", bytesRead);
      }

   }

   return bytesRead;
}

/**
* Utility function for reading just the header from an ASIM msg
*
* @param buf The buffer to read the header into
* @param doBlocking Whether this function should continue attempting to read until
*				data becomes available.
*
* @return An int containing the number of bytes actually read, -1 indicates
*           an unresponsive ASIM.  0 indicates that the ASIM responded, but did
*				not have any data available for reading.  If doBlocking is true, -1 
*				can also signify a timeout.
*/
int Spa1Asim::readPacketHeader(unsigned char* buf, bool doBlocking)
{
   int bytesRead = 0;

   if (!doBlocking)
   {
      bytesRead = read(i2cFd, buf, SPA1_HEADER_SIZE);

      if (bytesRead == -1)
      {
         return bytesRead;
      }

      if (buf[0] == 0xff && buf[1] == 0xff && buf[2] == 0xff)
      {
         bytesRead = 0;
      }
   }
   else
   {
      bool dataReady = false;
      double endTime = getCurTime() + ASIM_READ_TIMEOUT;

      while (!dataReady)
      {
         bytesRead = read(i2cFd, buf, SPA1_HEADER_SIZE);

         if (bytesRead == -1)
         {
            break;
         }

         if (buf[0] == 0xff && buf[1] == 0xff && buf[2] == 0xff)
         {
            dataReady = false;
				usleep(1000);
         }
         else
         {
            dataReady = true;
         }

         if (getCurTime() > endTime)
         {
            bytesRead = -1;
            break;
         }
      }
   }

   return bytesRead;
}




/**
* Utility function for sending messages to the ASIM.
*
* @param buf The buffer containing the message to be sent
* @param msgSize The size of the message to send in bytes
*
* @return An int containing the number of bytes actually written, -1 indicates
*           an error condition has occured.
*/
int Spa1Asim::sendToAsim(unsigned char* buf, size_t msgSize)
{
#ifndef WIN32
   if (ioctl(i2cFd, I2C_SLAVE, i2cAddress) < 0)
   {
      printf("SPA-1 Manager: Error setting i2c address in send\n");
   }
#endif

   return write(i2cFd, buf, msgSize);
}

/**
* Returns the current i2c address of the ASIM
*
* @return An unsigned char containing the I2C address
*/
unsigned char Spa1Asim::getI2cAddress()
{
   return i2cAddress;
}

/**
* Sets the 1-byte I2C address of the ASIM
*
* @param newAddress The address to set
*/
void Spa1Asim::setI2CAddress(unsigned char newAddress)
{
   i2cAddress = newAddress;
}

/**
* Returns the current sensor index of the ASIM
*
* @return An unsigned int containing the ASIM's sensor index
*/
unsigned int Spa1Asim::getSensorIndex()
{
   return sensorIndex;
}

/**
* Sets the sensor indexd of this ASIM
*
* @param newSensorId The sensor Index to set
*/
void Spa1Asim::setSensorIndex(unsigned short newSensorIndex)
{
   sensorIndex = newSensorIndex;
}

/**
* Returns the current sensorId of the ASIM
*
* @return An unsigned int containing the ASIM's sensor id
*/
unsigned int Spa1Asim::getSensorId()
{
   return sensorId;
}

/**
* Sets the sensor id of this ASIM
*
* @param newSensorId The sensor Id to set
*/
void Spa1Asim::setSensorId(unsigned long newSensorId)
{
   sensorId = newSensorId;
}

/**
* Returns the current registration state
*
* @return A RegistrationState enum indicating this ASIM current registration state
*/
RegistrationState Spa1Asim::getRegState()
{
	return regState;
}

/**
* Sets the registration state of the ASIM
*
* @param newState The registration state to set
*/
void Spa1Asim::setRegState(RegistrationState newState)
{
	regState = newState;
}

/**
* Performs the registration of the ASIM with the SM
*/
bool Spa1Asim::doRegistration(void)
{
   unsigned char outBuf[16];
   unsigned char inBuf[BUFSIZE];

   memset(outBuf, 0, 16);
   outBuf[0] = 'I';
   outBuf[1] = 0;
   outBuf[2] = 0;

   this->sendToAsim(outBuf, 3);           // Send I
	debug_f(4, "Sent (I) msg\n");
	usleep(1000);
   int bytesRead = this->recvFromAsim(inBuf, BUFSIZE, true);    // Get S blocking!
   //printf ("After I bytesRead == %i\n", bytesRead);
	debug_f(4, "Received (S)\n");
	if(debug >= 4)
	{
		for(int i = 0; i < bytesRead; i++)
		{
			debug_f(4, "buf[%i]: 0x%02x\n", i, inBuf[i]);
		}
	}

   //printf("Got S: %x\n", inBuf[3]);
   if (bytesRead == -1)
   {
      return false;
   }

   // See the page about the status message at:
   // https://gonzales.cs.usu.edu/drupal/node/47
   if ((inBuf[3] & 0xe0) != 0)
   {
      return false;
   }

   outBuf[0] = 'U';
   this->sendToAsim(outBuf, 3);           // Send U
	debug_f(4, "Sent (U) msg\n");
	usleep(1000);
   this->recvFromAsim(inBuf, BUFSIZE, true);    // Get K
	debug_f(4, "Received (K)\n");
	if(debug >= 4)
	{
		for(int i = 0; i < 4; i++)
		{
			debug_f(4, "buf[%i]: 0x%02x\n", i, inBuf[i]);
		}
	}
   //printf("Got K: %x\n", inBuf[3]);
   // there is no invalid version and it means nothing at this point

   outBuf[0] = 'X';
   this->sendToAsim(outBuf, 3);           // Send X
	debug_f(4, "Sent (X) msg\n");
	usleep(1000);
   xTEDSSize = this->recvXtedsFromAsim();
	debug_f(4, "Received (J) size: %i\n", xTEDSSize);

   if (debug >= 4)
   {
      printf ("Got xTEDS: ");
      for (int i = 0; i < xTEDSSize; ++i)
      {
         printf("%c", xTEDS[i]);
      }
      printf ("\n");
   }

   return true;
}

/**
* Increments the number of failures associated with this ASIM
*
*/
void Spa1Asim::incrementFailCount()
{
	failCount++;
}

/**
* Returns the current number of failures for this ASIM
*
* @return An int containing the current failure count
*/
int Spa1Asim::getFailCount()
{
	return failCount;
}


/**
* Private utility function used to return the system time
*
* @return A double containing the current system time (seconds + partial seconds)
*/
double Spa1Asim::getCurTime()
{
   unsigned int seconds;
   unsigned int uSeconds;
   double curTime;
   SDM_GetTime(&seconds, &uSeconds);
   curTime = seconds + ((double)uSeconds/1000000.0);
   return curTime;
}


/**
* Returns the guid used by this ASIM for arbitration
*
* @return An int containing guid used by the ASIM
*/
int Spa1Asim::getGuid()
{
   return guid;
}


/**
* Returns the name (null terminated) of the ASIM as pulled from its xTEDS
*
* @param outBuf An output buffer which will have the ASIMs name place into
*				it.  This buffer should be at least 25 bytes long.
*
* @return An int containing length of the null terminated ASIM name
*/
int Spa1Asim::getAsimName(char* outBuf)
{
	char* temp;
	int nameSize;
	if(xTEDS != NULL)
	{
		temp = strstr(xTEDS, "Device name=\"");

		for(nameSize = 0; nameSize < 24; nameSize++)
		{
			if(temp[nameSize + 13] == '"')
			{
				memcpy(outBuf, &temp[13], nameSize);
				outBuf[nameSize] = '\0';  //null terminate
				break;
			}
		}

		if(nameSize == 24)
		{
			memcpy(outBuf, &temp[13], nameSize);
			outBuf[nameSize] = '\0';  //null terminate
		}

		return nameSize + 1;  //return size of name + 1 for null terminator
	}
	else
	{
		return 0;  //No name available as xTEDS not yet registered
	}
}

