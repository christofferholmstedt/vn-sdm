#include "Spa1Manager.h"

/**
* Main routine for the SPA-1 Manager
*
* Parses command line options and starts the signal handling, sdmLisener, and 
* i2cComm threads.
*
*/
int main(int argc, char** argv)
{
   MessageManager msgManager;
   pthread_attr_t threadAttr;
	int option = 0;

	DataManager.setAddress(inet_addr("127.0.0.1"));
	DataManager.setPort(PORT_DM);

	while(option != -1)
	{
		option = getopt(argc,argv,"g:d:v");
		switch (option)
		{
			case 'g':
				debug = atoi(optarg);
				break;
			case 'd':
				DataManager.setAddress(inet_addr(optarg));
				if (((long)DataManager.getAddress()) == -1)
				{
					printf("Error in DM address.  Format is -d[IP Addr in string notation]\n");
					return 0;
				}
				DataManager.setPort(PORT_DM);
				break;
			case 'v':
				printf("SDM Version: %s Repo Rev: %i\n", SDM_VERSION, REVISION_NUMBER);
            return 0;
			default:
				break;
		}
	}

#ifndef WIN32
	sigset_t sigSet;
	sigemptyset(&sigSet);
	sigaddset(&sigSet, SIGINT);
	pthread_sigmask(SIG_BLOCK, &sigSet, NULL);

	if(pthread_create(&sigHandler, NULL, &signalHandler, NULL) != 0)
	{
		printf("SPA-1 Manager: Could not start signal handler thread.\n");
	}
#else
	signal(SIGINT, signalHandler);
#endif

   msgManager.Async_Init(PORT_SPA1_MANAGER);

   if(sdmRegister(&msgManager) != 0)
   {
      printf("SPA-1 Manager: Error Registering with SDM.\n");
      return -1;
   }

   pthread_attr_init(&threadAttr);
   pthread_attr_setstacksize(&threadAttr, THREAD_STACK_SIZE);

   if (pthread_create(&sdmListenThread, &threadAttr, &sdmListener, &msgManager) < 0)
   {
      printf("SPA-1 Manager: Error creating SDM Listener thread\n");
   }

   if (pthread_create(&i2cThread, &threadAttr, &i2cComm, NULL) < 0)
   {
      printf("SPA-1 Manager: Error creating I2C Comm thread\n");
   }

	asimMonitor();

   pthread_join(sdmListenThread, NULL);
   pthread_join(i2cThread, NULL);

   return 0;
}

/**
* Function  used to register the SPA-1 Manager with the SDM
*
* @param msgManager A pointer to the Message Manager being used by the SPA-1 Manager
*
* @return An int indicating the outcome of the registration, 0 for success, -1 otherwise
*/
int sdmRegister(MessageManager* msgManager)
{
   SDMHello helloMsg;
   SDMAck ackMsg;
   SDMID idMsg;
   bool isRegistered = false;
   bool ackReceived = false;
   char buf[BUFSIZE];
   double timeout = 5.0;
   double endTime;

   helloMsg.type = 'C';
   helloMsg.source.setPort(PORT_SPA1_MANAGER);
   helloMsg.Send();
	debug_f(1, "Spa1Manager: Sending SDMHello Msg\n");

   endTime = getCurTime() + timeout;

   while (!isRegistered)
   {
      if (msgManager->IsReady())
      {
#ifdef WIN32
         switch (msgManager->GetMsg(buf))
#else
         switch (msgManager->GetMessage(buf))
#endif
         {
            case SDM_ACK:
               ackReceived = true;
               debug_f(1, "Spa1Manager: SDMAck received\n");
               break;
            case SDM_Register:
					debug_f(1, "Spa1Manager: SDMRegister Received\n");
               registerxTEDS();
               endTime = getCurTime() + timeout;
               break;
            case SDM_ID:
               isRegistered = true;
               debug_f(1, "Spa1Manager: SDMID received\n");
               break;
            default:
               break;
         }
      }
      else
      {
         if (!ackReceived && getCurTime() >= endTime)
         {
            helloMsg.Send();
            endTime = getCurTime() + timeout;
            debug_f(1, "Spa1Manager: Resending SDMHello Msg\n");
         }
         else if (ackReceived && !isRegistered && getCurTime() >= endTime)
         {
            registerxTEDS();
            endTime = getCurTime() + timeout;
         }
      }
      if(termination)
      {
         return -1;
      }
      usleep(10000);
   }
   debug_f(1, "Spa1Manager: Successully Registered with Data Manager\n");
   return 0;
}

/**
* Function used to register the SPA-1 Manager's xTEDS
*
*/
void registerxTEDS()
{
   SDMxTEDS xTEDSMsg;
   xTEDSMsg.source.setSensorID(1);
   xTEDSMsg.source.setPort(PORT_SPA1_MANAGER);
   strcpy(xTEDSMsg.xTEDS, spa1ManagerxTEDS);
   xTEDSMsg.Send();
	debug_f(1, "Spa1Manager: Sending xTEDS to Data Manager\n");
}

/**
* Thread that listens for incoming SDM messages and responds appropriately
*
* @param args A pointer the the SPA-1 Manager's Message Manager
*
*/
void* sdmListener(void* args)
{
   MessageManager* msgManager = (MessageManager*)args;
   char buf[BUFSIZE];

   while (!termination)
   {
      if (msgManager->IsReady())
      {
#ifdef WIN32
         switch (msgManager->GetMsg(buf))
#else
         switch (msgManager->GetMessage(buf))
#endif
         {
            case SDM_Serreqst:
					handleSerreqstMsg(buf);
               break;
            case SDM_Command:
					handleCommandMsg(buf);
               break;
            case SDM_Subreqst:
					handleSubreqstMsg(buf);
               break;
            case SDM_Deletesub:
					handleDeletesubMsg(buf);
               break;
            case SDM_Tat:
					// TODO:
               break;
            case SDM_Ready:
               break;
            case SDM_RegInfo:
               break;
            case SDM_Data:
               break;
            case SDM_ACK:
					handleAckMsg(buf);
               break;
            case SDM_Register:
					handleRegisterMsg(buf);
               break;
            case SDM_ID:
					handleIdMsg(buf);
               break;
            default:
               break;
         }
      }
      usleep(10000);
   }
   return NULL;
}

/**
* Handles all the I2C communication between the SPA-1 Manager and the
* SPA-1 ASIMs
*
* Opens the I2C file descriptor and starts the round robin communication.
* The round robin consists of three phases, writing to ASIMs, receiving from
* ASIMs, and searching for new ASIMs. The first two phase occur every iteration
* while searching for new ASIMs occurs only once every 256 iterations, essentially
* seaching for new ASIMs on the bus 4x per second.
*/
void* i2cComm(void* args)
{
   unsigned char highestKnownAddress = DEFAULT_ADDRESS; // no known addresses
   unsigned int endTime = 0;
   debug_f(2, "Spa1Manager: i2c Comm Thread started\n");
   busFd = open("/dev/i2c-0", O_RDWR);

   if (busFd == -1)
   {
      printf("Spa1Manager: Unable to open /dev/i2c-0, exiting...\n");
      termination = 1;
      cancelSdmRegistrations();
      return NULL;
   }

   // Start round robin
   debug_f(1, "Spa1Manager: Starting round robin\n");

   while (!termination)
   {
      asimTable.sendToAsims();  //Round robin write

		usleep(1000);  //Keep loop from running too much and give ASIMs a little time to respond

      asimTable.recvFromAsims();  //Round robin read

		if(getCurTime() > endTime)
		{
		   endTime = getCurTime() + 1;
		   highestKnownAddress = searchForNewAsims(highestKnownAddress);
			debug_f(3, "highestKnownAddress == %x\n", highestKnownAddress);
			if(debug > 3)
			{
				asimTable.printAsimData();
			}
		}      
   }

   return NULL;
}

/**
* Function which checks periodically checks each ASIM for any outgoing data
* or received status messages.
*
* Messages are checked at roughly 1
* @param args A pointer the the SPA-1 Manager's Message Manager
*
*/
void asimMonitor()
{
	while(!termination)
	{
		asimTable.checkMsgsFromAsim(); //Checks for msgs from ASIMs, publishes data msgs and inspects status msgs
		usleep(1000);
	}
}


/**
* Searches the address space for any unregistered ASIMs.  When a new ASIM is  
* found the registration process is initiated for that ASIM.
*
* @param highestKnownAddress The highest i2c address currently registered with the Spa1Manager
*
* @return An unsigned char of the updated highest known used i2c address
*/
unsigned char searchForNewAsims(unsigned char highestKnownAddress)
{
   debug_f(4, "Spa1Manager: Searching for new ASIMs\n");
   unsigned char buf[DEFAULT_BUFFER_SIZE];
   unsigned char highestAddressResponse = highestKnownAddress;

   int bytesRead = 0;
	pthread_t sdmRegThread;
	pthread_attr_t threadAttr;

	pthread_attr_init(&threadAttr);
	pthread_attr_setdetachstate(&threadAttr, PTHREAD_CREATE_DETACHED);

   unsigned char probeMsg[3];
   probeMsg[0] = 'Z';
   probeMsg[1] = 0;
   probeMsg[2] = 0;

   for (unsigned char address = DEFAULT_ADDRESS; (address <= highestKnownAddress) || (address < 0x80 && bytesRead != -1); ++address)
   {
      if (!asimTable.checkAddressUsed(address))
      {
         setSlaveAddress(address);
         write(busFd, probeMsg, 3);
			usleep(1000); //Give ASIM a little time to process message
         bytesRead = i2cRead(buf, SPA1_HEADER_SIZE + 4);

         debug_f(3, "bytesRead == %i\n", bytesRead);
			if(debug >= 4)
			{
				for(int i=0; i < bytesRead; i++)
				{
					debug_f(4, "buf[%i]: 0x%02x\n", i, buf[i]);		
				}
			}
         if (bytesRead != -1)
         {
            int guid = 0;
            memcpy(&guid, &buf[3], 4);

            debug_f(1, "Spa1Manager: Registering ASIM with GUID: %i at address 0x%x\n", guid, address);

            Spa1Asim* asim = new Spa1Asim(busFd, address, guid);
            bool success = asim->doRegistration();

            if (success)
            {
               debug_f(1, "Spa1Manager: Successful registration! Spawning thread to register with the DM\n");
               asimTable.addAsim(asim);
               debug_f(1, "Spa1Manager: Added ASIM to table, current count: %i\n", asimTable.getAsimCount());

               if (address > highestKnownAddress)
               {
                  highestAddressResponse = address;
               }

               if(pthread_create(&sdmRegThread, &threadAttr, &regAsimWithSdm, asim) < 0)  //Thread is created detached
               {
                  printf("Spa1Manager: Error spawning thread to register ASIM with DM\n");
               }
            }
            else
            {
               debug_f(1, "Spa1Manager: Failed registration for ASIM with GUID: %i\n", guid);
            }
         }
         else if (address < highestKnownAddress)
         {
            debug_f(2, "Spa1Manager: Detected hole in address space at address 0x%x\n", address);
         }
      }
   }

   return highestAddressResponse;
}


/**
* Attempts to read data off of the i2c bus.  
*
* If 0xff is read off of the bus, it is assumed that the ASIM is not yet ready to provide data
*
* @param buf The output buffer to read into
* @param size The size of the output buf
*
* @return An int containing the number of bytes read.  -1 signifying a timeout or error condition.
*/
int i2cRead(unsigned char* buf, size_t size)
{
   int bytesRead = 0;
   bool dataReady = false;
   double endTime = getCurTime() + I2C_READ_TIMEOUT;

   while (!dataReady)
   {
      bytesRead = read(busFd, buf, size);
		
		//0xff is placed onto the ASIMs output register to signify that it has no data ready
      if (bytesRead != -1 && buf[0] == 0xff && buf[1] == 0xff && buf[2] == 0xff)
      {
         dataReady = false;
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

   if (bytesRead == -1)
   {
      debug_f(3, "No response\n");
   }

   return bytesRead;
}

/**
* Sets the address of the I2C slave currently being read/written to  
*
* @param address The address to interact with on the I2C bus
*/
void setSlaveAddress(unsigned char address)
{
   debug_f(4, "Setting slave address to: %x\n", address);

#ifndef WIN32
   if (ioctl(busFd, I2C_SLAVE, address) < 0)
   {
		printf("Spa1Manager: Can't use ioctl to set i2c slave address\n");
   }
#endif
}

/**
* Thread used to register an individual ASIM with the SDM
*
* @param args A pointer to the Spa1Asim object to register
*
*/
void* regAsimWithSdm(void* args)
{
	Spa1Asim* asim = (Spa1Asim*)args;
	SDMHello helloMsg;
	double endTime = 0.0;
	int timeout = 5;
	char notificationBuf[5];

	helloMsg.source.setPort(PORT_SPA1_MANAGER);
	helloMsg.source.setSensorID(asim->getSensorIndex());
	helloMsg.Send();
	debug_f(1, "Spa1Manager: Sending SDMHello for ASIM with sensorIndex: %i\n", asim->getSensorIndex());
	asim->setRegState(SENT_HELLO);
	endTime = getCurTime() + timeout;

	while (asim->getRegState() == SENT_HELLO)
	{
		if(getCurTime() > endTime)
		{
			helloMsg.Send();
			debug_f(1, "Spa1Manager: Re-sending SDMHello for ASIM with sensorIndex: %i\n", asim->getSensorIndex());

			// reset the timeout after each timeout
			endTime = getCurTime() + timeout;
		}
		usleep(100000);
	}

	while (asim->getRegState() != RECVD_REG)
	{
		usleep(100000);
	}

	registerAsimXteds(asim);

	while (asim->getRegState() != RECVD_ID)
	{
		usleep(100000);
	}

	notificationBuf[0] = 0;  //0 = Registration
	PUT_UINT(&notificationBuf[1], asim->getSensorId());
	subscriptions.Publish(regChangeMsg, notificationBuf, 5); //Attempt to publish notification of an ASIM registration 
	
	debug_f(1, "Spa1Manager: ASIM %i successfully registered with the SDM\n",  asim->getSensorIndex());
	return NULL;
}

/**
* Used to handle an SDMAck message received by the SPA-1 Manager
*
* When an SDMAck message is received, this function sets the
* registration state of the corresponding Spa1Asim object to
* RECVD_ACK. This allows the ASIMs registration thread to proceed.
*
* @param buf The buffer containing the received SDMAck msg
*
*/
void handleAckMsg(char* buf)
{
	SDMAck ackMsg;
	Spa1Asim* asim;
	if(ackMsg.Unmarshal(buf) < 0)
	{
		printf("Spa1Manager: Bad SDMAck Msg received\n");
	}

	asim = asimTable.getAsimBySensorId(ackMsg.error);

	if(asim == NULL)
	{
		printf("Spa1Manager: No matching ASIM found for SDMAck with sensorIndex: %i\n", ackMsg.error);
		return;
	}
	debug_f(1, "Spa1Manager: SDMAck Received for ASIM %i\n",  asim->getSensorIndex());

	asim->setRegState(RECVD_ACK);
}

/**
* Used to handle an SDMRegister message received by the SPA-1 Manager
*
* When an SDMRegister message is received, this function sets the
* corresponding ASIMs registration state to RECVD_REG. This causes
* the ASIM's registration thread to continue and send the ASIM's xTEDS.
*
* @param buf The buffer containing the received SDMRegister msg
*
*/
void handleRegisterMsg(char* buf)
{
	SDMRegister registerMsg;
	Spa1Asim* asim;
	if(registerMsg.Unmarshal(buf) < 0)
	{
		printf("Spa1Manager: Bad SDMRegister Msg received\n");
	}

	asim = asimTable.getAsimBySensorIndex(registerMsg.sensorIndex);

	if(asim == NULL)
	{
		printf("Spa1Manager: No matching ASIM found for SDMRegister\n");
		return;
	}

	debug_f(1, "Spa1Manager: SDMRegister Received for ASIM %i\n",  asim->getSensorIndex());

	asim->setRegState(RECVD_REG);
}

/**
* Used to handle an SDMID message received by the SPA-1 Manager
*
* When an SDMID message is received, this function sets the
* corresponding ASIMs registration state to RECVD_ID. This causes
* the ASIM's registration thread to finish as the ASIM has now
* fully registered.
*
* @param buf The buffer containing the received SDMID msg
*
*/
void handleIdMsg(char* buf)
{
	SDMID idMsg;
	Spa1Asim* asim;
	if(idMsg.Unmarshal(buf) < 0)
	{
		printf("Bad SDMID Msg received\n");
	}

	asim = asimTable.getAsimBySensorId(idMsg.destination.getSensorID());

	if(asim == NULL)
	{
		printf("No matching ASIM found for SDMId\n");
		return;
	}

	debug_f(1, "Spa1Manager: SDMID Received for ASIM %i\n",  asim->getSensorIndex());

	asim->setRegState(RECVD_ID);
	asim->setSensorId(idMsg.destination.getSensorID());
}

/**
* Used to handle an SDMSerreqst message received by the SPA-1 Manager
*
* When an SDMSerreqst message is received, this function checks to see the
* intended destination. If it is for an ASIM, the command is passed along to 
* the corresponding ASIM.  If it is for the Spa1Manger, it is handled accordingly.
*
* @param buf The buffer containing the received SDMSerreqst msg
*
*/
void handleSerreqstMsg(char* buf)
{
	SDMSerreqst serReqstMsg;
	Spa1Asim* asim;
	unsigned char msgBuf[MAX_SPA1_MSG_SIZE];
	int msgSize;

	if (serReqstMsg.Unmarshal(buf) < 0)
	{
		printf("Spa1Manager: Invalid SDMSerreqst message\n");
		return;
	}

	if((serReqstMsg.source.getSensorID() & 0x0ff) != 1) //Destined for an ASIM
	{
		debug_f(1,"Spa1Manager: Service request received for ASIM %hu\n", serReqstMsg.source.getSensorID() & 0x00ff);

		asim = asimTable.getAsimBySensorId(serReqstMsg.source.getSensorID());
		if(asim != NULL)
		{
			msgSize = translator.translateToSpa1((unsigned char*)buf, msgBuf, MAX_SPA1_MSG_SIZE);
			if(asim->sendToQueue.putMsg(msgBuf, msgSize) == 0)
			{
				debug_f(1, "Spa1Manager: Added Service Request Msg destined for ASIM %hu to its queue\n", asim->getSensorIndex());
			}
			else
			{
				printf("Spa1Manager: Error adding request msg to ASIM queue\n");
			}
		}
		else
		{
			debug_f(1, "Spa1Manager: No matching ASIM (%hu) found for SDMSerreqst Msg\n", serReqstMsg.source.getSensorID() & 0x00ff);
		}
	}
	else	//Destined for Spa1Manager
	{
		if(serReqstMsg.command_id == getxTEDSMsg)
		{
			getAsimxTEDSReply(buf);
		}
		else if(serReqstMsg.command_id == getAsimDetailsMsg)
		{
			getAsimDetailsReply(buf);
		}
	}
}

/**
* Used to handle an a request made to the Spa1Manager for the xTEDS of a
* particular SPA-1 ASIM
*
* @param buf The buffer containing the received SDMSerreqst msg
*
*/
void getAsimxTEDSReply(char* buf)
{
	SDMSerreqst serReqstMsg;
	SDMData dataMsg;
	unsigned int sensorId;
	unsigned short xTEDSLen;
	Spa1Asim* asim;

	serReqstMsg.Unmarshal(buf);
	dataMsg.source = serReqstMsg.source;
	dataMsg.msg_id = serReqstMsg.reply_id;
	sensorId = GET_UINT(serReqstMsg.data);

	asim = asimTable.getAsimBySensorId(sensorId);
	
	if(asim != NULL)
	{
		xTEDSLen = (unsigned short)asim->xTEDSSize;
		PUT_USHORT(dataMsg.msg, xTEDSLen);
		memcpy(&dataMsg.msg[2], asim->xTEDS, xTEDSLen);
		dataMsg.length = xTEDSLen + sizeof(unsigned short);
		dataMsg.Send(serReqstMsg.destination);
	}
}

/**
* Used to handle an a request made to the Spa1Manager for details pertaining to
* a specific SPA-1 ASIM
*
* @param buf The buffer containing the received SDMSerreqst msg
*
*/
void getAsimDetailsReply(char* buf)
{
	SDMSerreqst serReqstMsg;
	SDMData dataMsg;
	unsigned int sensorId;
	Spa1Asim* asim;
	int cur = 0;
	char nameBuf[25];
	int nameSize;

	serReqstMsg.Unmarshal(buf);
	dataMsg.source = serReqstMsg.source;
	dataMsg.msg_id = serReqstMsg.reply_id;
	sensorId = GET_UINT(serReqstMsg.data);

	asim = asimTable.getAsimBySensorId(sensorId);
	
	if(asim != NULL)
	{
		PUT_UINT(&dataMsg.msg[cur], sensorId);
		cur += 4;
		dataMsg.msg[cur] = asim->getI2cAddress();
		cur += 1;
		PUT_UINT(&dataMsg.msg[cur], sensorId);
		cur += 4;
		nameSize = asim->getAsimName(nameBuf);
		memcpy(&dataMsg.msg[cur], nameBuf, nameSize);
		cur += nameSize;

		dataMsg.length = cur;
		dataMsg.Send(serReqstMsg.destination);
	}
}


/**
* Used to handle an SDMCommand message received by the SPA-1 Manager
*
* When an SDMCommand message is received, this function checks to see the
* intended destination. If it is for an ASIM, the command is passed along to 
* the corresponding ASIM.  If it is for the Spa1Manger, it is handled accordingly.
*
* @param buf The buffer containing the received SDMCommand msg
*
*/
void handleCommandMsg(char* buf)
{
	SDMCommand commandMsg;
	Spa1Asim* asim;
	unsigned char msgBuf[MAX_SPA1_MSG_SIZE];
	int msgSize;

	if (commandMsg.Unmarshal(buf) < 0)
	{
		printf("Spa1Manager: Invalid SDMCommand message\n");
		return;
	}

	if((commandMsg.source.getSensorID() & 0x0ff) != 1) //Destined for an ASIM
	{
		debug_f(1,"Spa1Manager: Command Msg received for ASIM %hu\n", commandMsg.source.getSensorID() & 0x00ff);

		asim = asimTable.getAsimBySensorId(commandMsg.source.getSensorID());
		if(asim != NULL)
		{
			msgSize = translator.translateToSpa1((unsigned char*)buf, msgBuf, MAX_SPA1_MSG_SIZE);
			if(asim->sendToQueue.putMsg(msgBuf, msgSize) == 0)
			{
				debug_f(1, "Spa1Manager: Added Command Msg destined for ASIM %hu to its queue\n", asim->getSensorIndex());
			}
			else
			{
				printf("Spa1Manager: Error adding command msg to ASIM queue\n");
			}
		}
		else
		{
			debug_f(1, "Spa1Manager: No matching ASIM (%hu) found for SDMCommand Msg\n", commandMsg.source.getSensorID() & 0x00ff);
		}
	}
	else	//Destined for Spa1Manager
	{
		if(commandMsg.command_id == resetBusMsg)
		{
			//TODO: Send reset messages to each ASIM?  
			//Perhaps close the i2c file descriptor and remove/re-insert the i2c kernel module?
			//We would have to basically suspend all operations of the SPA-1 Manager during this global reset
		}
	}
}


/**
* Used to handle an SDMSubreqst message received by the SPA-1 Manager
*
* When an SDMSubreqst message is received, this function checks to see the
* intended destination. If it is for an ASIM, the subscription is stored for the ASIM.
* If it is for the Spa1Manger, it is recoreded in the manager's subscription manager.
*
* @param buf The buffer containing the received SDMSubreqst msg
*
*/
void handleSubreqstMsg(char* buf)
{
	SDMSubreqst subReqstMsg;
	Spa1Asim* asim;
	unsigned char msgBuf[MAX_SPA1_MSG_SIZE];
	int msgSize;

	if (subReqstMsg.Unmarshal(buf) < 0)
	{
		printf("Spa1Manager: Invalid SDMSubreqst message\n");
		return;
	}

	if((subReqstMsg.source.getSensorID() & 0x0ff) != 1) //Destined for an ASIM
	{
		debug_f(1,"Spa1Manager: Subreqst Msg received for ASIM %hu\n", subReqstMsg.source.getSensorID() & 0x00ff);

		asim = asimTable.getAsimBySensorId(subReqstMsg.source.getSensorID());
		if(asim != NULL)
		{
			msgSize = translator.translateToSpa1((unsigned char*)buf, msgBuf, MAX_SPA1_MSG_SIZE);
			asim->subscriptions.AddSubscription(subReqstMsg);
			debug_f(1, "Spa1Manager: Subscription added for ASIM %hu msg(%i,%i)\n", subReqstMsg.source.getSensorID() & 0x00ff, subReqstMsg.msg_id.getInterface(), subReqstMsg.msg_id.getMessage());
			if(asim->sendToQueue.putMsg(msgBuf, msgSize) == 0)
			{
				debug_f(1, "Spa1Manager: Added data request msg destined for ASIM %hu to its queue\n", asim->getSensorIndex());
			}
			else
			{
				printf("Spa1Manager: Error adding data request msg to ASIM queue\n");
			}
		}
		else
		{
			debug_f(1, "Spa1Manager: No matching ASIM (%hu) found for SDMSubreqst Msg\n", subReqstMsg.source.getSensorID() & 0x00ff);
		}
	}
	else	//Destined for Spa1Manager
	{
		subscriptions.AddSubscription(subReqstMsg);
	}
}

/**
* Used to handle an SDMDeletesub message received by the SPA-1 Manager
*
* When an SDMDeletesub message is received, this function checks to see the
* intended destination. If it is for an ASIM, the subscription is removed for the ASIM.
* If it is for the Spa1Manger, it is removed from the manager's subscription manager.
*
* @param buf The buffer containing the received SDMDeletesub msg
*
*/
void handleDeletesubMsg(char* buf)
{
	SDMDeletesub delSubMsg;
	Spa1Asim* asim;

	if (delSubMsg.Unmarshal(buf) < 0)
	{
		printf("Spa1Manager: Invalid SDMSubreqst message\n");
		return;
	}

	if((delSubMsg.source.getSensorID() & 0x0ff) != 1) //Destined for an ASIM
	{
		debug_f(1,"Spa1Manager: Deletesub Msg received for ASIM %hu\n", delSubMsg.source.getSensorID() & 0x00ff);

		asim = asimTable.getAsimBySensorId(delSubMsg.source.getSensorID());
		if(asim != NULL)
		{
			asim->subscriptions.RemoveSubscription(delSubMsg);
			debug_f(1, "Spa1Manager: Subscription removed for ASIM %hu msg(%i,%i)\n", delSubMsg.source.getSensorID() & 0x00ff, delSubMsg.msg_id.getInterface(), delSubMsg.msg_id.getMessage());
		}
		else
		{
			debug_f(1, "Spa1Manager: No matching ASIM (%hu) found for SDMDeletesub Msg\n", delSubMsg.source.getSensorID() & 0x00ff);
		}
	}
	else	//Destined for Spa1Manager
	{
		subscriptions.RemoveSubscription(delSubMsg);
	}
}


/**
* Used for registering a SPA-1 ASIMs xTEDS with the SDM
*
* This function should only be called after an SDMRegister message
* is received for a specific ASIM. The xTEDS is sent and the Spa1Asim's
* registration state is updated to SENT_XTEDS.
*
* @param buf The buffer containing the received SDMID msg
*
*/
void registerAsimXteds(Spa1Asim* asim)
{
	SDMxTEDS xTEDSMsg;
	xTEDSMsg.source.setSensorID(asim->getSensorIndex());
   xTEDSMsg.source.setPort(PORT_SPA1_MANAGER);
	strcpy(xTEDSMsg.xTEDS, asim->xTEDS);
   xTEDSMsg.Send();
	debug_f(1, "Spa1Manager: SDMxTEDS sent for ASIM %i\n",  asim->getSensorIndex());
	asim->setRegState(SENT_XTEDS);
}

/**
* Used for canceling both the Spa1Manager's xTEDS with the SDM, as well as the
* xTEDS of all registered SPA-1 ASIMs.
*
*/
void cancelSdmRegistrations()
{
	SDMCancelxTEDS cancelxTEDSMsg;

	asimTable.cancelSdmRegistrations();

	cancelxTEDSMsg.source.setPort(PORT_SPA1_MANAGER);
	cancelxTEDSMsg.source.setSensorID(1);	//Cancel the Spa1Manager's xTEDS
	cancelxTEDSMsg.Send();
}

/**
* Linux signal handler to catch SIGINT and gracefully shut down the Spa1Manager and
* deregister itself and all ASIMs with the SDM.
*
*/
#ifndef WIN32
void* signalHandler(void* args)  //signal handler for linux
{
	sigset_t signal_set;
	int sig;
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGINT);

	while (!termination)
	{
		sigwait(&signal_set, &sig);
		switch(sig)
		{
			case SIGINT:
				printf("Spa1Manager: Shutting Down\n");
				termination = true;
				cancelSdmRegistrations();
				break;
		}
	}
	return NULL;
}
#endif


#ifdef WIN32
/**
* Windows signal handler to catch SIGINT and gracefully shut down the Spa1Manager and
* deregister itself and all ASIMs with the SDM.
*
* @param sig The signal received
*
*/
void signalHandler(int sig)
{
	switch (sig)
	{
		case SIGINT:
			printf("Spa1Manager: Shutting Down\n");
			termination = true;
			cancelSdmRegistrations();
			break;
		default:
			break;
	}
}
#endif

/**
* Utility function for retreiving the system time in seconds.
* Useful for simple polling timers.
*
* @return An int containing the current system clock value of seconds
*
*/
unsigned int getCurTime()
{
   unsigned int seconds;
   unsigned int uSeconds;
   SDM_GetTime(&seconds, &uSeconds);

   return seconds;
}
