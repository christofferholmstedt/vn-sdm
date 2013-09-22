//*********************************************************************
//Sensor Manager Module of the SDM
//
//This source is compilable on both a Linux and a Win32 architecture.  Throughout, there are
//compile switches as #ifdef ... #endif which conditionally add or remove functionality.
//The most notable changes for compilation is the removal of a separate signal handling thread
//under Win32, because Windows has far fewer options for process signals than Linux.
//*********************************************************************

#include "sm.h"
#include "SensorMonitor.h"


unsigned int MAX_SENSORS=15;
//Sensor* sensor;
SensorMonitor sensor;

SubscriptionManager sm_subscriptions;
pthread_mutex_t subscription_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t perf_counter_mutex = PTHREAD_MUTEX_INITIALIZER;	//a mutex for performance counter access
pthread_mutex_t dm_found_mutex = PTHREAD_MUTEX_INITIALIZER;		//a mutex to cooperate the verifyDM procedure
pthread_mutex_t log_service_mutex = PTHREAD_MUTEX_INITIALIZER;		//a mutex for the message logger service
// Locked before any sensor write, this is another concurrency bug in the ASIM driver
// using a mutex for all requests prevents messages from stepping on each others' toes
// in the driver
pthread_mutex_t sensor_write_mutex = PTHREAD_MUTEX_INITIALIZER;
unsigned long Address_SM = inet_addr("127.0.0.1");
unsigned int total_recd = 0;		//message counter for total received for life of sm
unsigned int prevsec_recd = 0;		//message counter for total received previous second
unsigned int total_sent = 0;		//message counter for total sent for life of sm
unsigned int prevsec_sent = 0;		//message counter for total sent previous second
bool dm_found = false;
int debug;
bool prompt;
MessageLogger log_service;
short tm_mode_msg_id = 0;
unsigned char tm_mode;
SDMComponent_ID tm_mode_source;

bool ackReceived = false;
bool registerReceived = false;
bool idReceived = false;

char * sm_xTEDS = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<xTEDS version=\"2.0\" xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"Sensor_Manager_xTEDS\">\n\t<Application kind=\"Software\" name=\"SensorManager\"/>\n\t<Interface name=\"Msg_Count\" id=\"2\">\n\t\t<Variable name=\"Total_Messages_Recd\" kind=\"Total\" format=\"UINT32\"/>\n\t\t<Variable name=\"Messages_Last_Second_Recd\" kind=\"Total\" format=\"UINT32\"/>\n\t\t<Variable name=\"Total_Messages_Sent\" kind=\"Total\" format=\"UINT32\"/>\n\t\t<Variable name=\"Messages_Last_Second_Sent\" kind=\"Total\" format=\"UINT32\"/>\n\n\t\t<Notification>\n\t\t\t<DataMsg name=\"Message_Count\" id=\"13\" msgArrival=\"PERIODIC\">\n\t\t\t\t<VariableRef name=\"Total_Messages_Recd\"/>\n\t\t\t\t<VariableRef name=\"Messages_Last_Second_Recd\"/>\n\t\t\t\t<VariableRef name=\"Total_Messages_Sent\"/>\n\t\t\t\t<VariableRef name=\"Messages_Last_Second_Sent\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t</Interface>\n\t<Interface name=\"Message_Log\" id=\"3\">\n\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"Msg_Type\"/>\n\t\t<Variable format=\"UINT32\" kind=\"IP_long\" name=\"Address\"/>\n\t\t<Variable format=\"UINT16\" kind=\"Port_of_Device\" name=\"Port\"/>\n\t\t<Variable format=\"UINT32\" kind=\"ID\" name=\"Sensor_ID\"/>\n\t\t<Command>\n\t\t\t<CommandMsg name=\"Enable_Logging\" id=\"16\">\n\t\t\t\t<VariableRef name=\"Msg_Type\"/>\n\t\t\t\t<VariableRef name=\"Address\"/>\n\t\t\t\t<VariableRef name=\"Port\"/>\n\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n\t\t\t</CommandMsg>\n\t\t</Command>\n\t\t<Command>\n\t\t\t<CommandMsg name=\"Disable_Logging\" id=\"17\">\n\t\t\t\t<VariableRef name=\"Msg_Type\"/>\n\t\t\t\t<VariableRef name=\"Address\"/>\n\t\t\t\t<VariableRef name=\"Port\"/>\n\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n\t\t\t</CommandMsg>\n\t\t</Command>\n\t</Interface>\n</xTEDS>";

int main(int argc, char** argv)
{
	int result;
	SDM_TimeInit();
	static struct option long_options[] = {
		{"dm",1,0,'d'},
		{"help",0,0,'h'},
		{"max_sensors",1,0,'n'},
		{"debug",1,0,'g'},
		{"prompt",0,0,'p'},
		{0,0,0,0}
	};
	int option_index;
	int option;
	pthread_t UDP_thread;
	pthread_t TCP_thread;
	pthread_t SigHandler_thread;
	bool DM_set = false;
	prompt = false;
	SDMxTEDS xteds;
#ifndef WIN32
	sigset_t signal_set;
#endif
	SDMReqReg reqreg_msg;

	//parse command line options
	while(1)
	{
		option = getopt_long(argc,argv,"g:hn:d:p", long_options, &option_index);
		if(option==-1)
			break; //no more options
		switch(option)
		{
			case 'h':
				printf("Usage: sm [options]\n");
				printf("Options:\n");
				printf("--dm=<addr> -d<addr>\t\t\tSet IP address of Data Manager\n\t\t\t\t\t<addr> should be given in dot number notation\n");
				printf("--help -h\t\t\t\tDisplay this information\n");
				printf("--max_sensors=<number> -n<number>\tSet maximum <number> of ASIMs for this Sensor Manager\n");
				printf("--debug=<level> -g<level>\t\tSet level of debug messages\n\t\t\t\t\t0=none, 1=moderate, 2=verbose\n");
				printf("--prompt -p\t\t\t\tPrompt for each sensor before monitoring\n");
				return 0;
			case 'd':
				DataManager.setAddress(inet_addr(optarg));
				if (((long)DataManager.getAddress()) == -1)
				{
					printf("Error in DM address.  Be sure to use --dm= instead of -dm=\n");
					return 0;
				}
				DataManager.setPort(PORT_DM);
				DM_set = true;
				break;
			case 'n':
				MAX_SENSORS = atoi(optarg);
				break;
			case 'g':
				debug = atoi(optarg);
				break;
			case 'p':
				prompt = true;
				break;
			case '?':
				break;
		}
	}
	// Get the address of this SensorManager node
	if (GetNodeAddress() == -1)
		printf("Unable to get the SM's IP address, using localhost instead.\n");

	// If the DataManager address wasn't specified on the command line, assume localhost
	if(!DM_set)
	{
		DataManager.setAddress(inet_addr("127.0.0.1"));
		DataManager.setPort(PORT_DM);
	}
	debug_f(2,"Finding DM at address 0x%lx\n",DataManager.getAddress());
	printf("SM %s (%d sensors)\n",SDM_VERSION,MAX_SENSORS);
	switch(debug)
	{
		case 1:
		printf("SM in debug 1 (moderate).\n");
		break;
		case 2:
		printf("SM in debug 2 (verbose).\n");
		break;
		case 3:
		printf("SM in debug 3 (verbose w/msg echo).\n");
		break;
	}

	//All subsequent threads block the SIGINT and SIGALRM signals so they aren't interrupted after calling pthread_mutex_lock()
	//this avoids a deadlock situation by dedicating a single thread for signal handling.
#ifdef WIN32
	signal(SIGINT,SigIntHandler);
#else
	sigemptyset(&signal_set);
	sigaddset(&signal_set, SIGALRM);
	sigaddset(&signal_set, SIGINT);
	pthread_sigmask(SIG_BLOCK, &signal_set, NULL);
#endif

	//Start listener threads, then verify DM
	result = pthread_create(&UDP_thread,NULL,&UDPMonitor,NULL);
	if(result < 0)
	{
		perror("Could not start UDP Listener");
	}
	result = pthread_create(&TCP_thread,NULL,&TCPMonitor,NULL);
	if(result < 0)
	{
		perror("Could not start TCP Listener");
	}
	/*No signal handling thread for Win32*/
#ifndef WIN32
	result = pthread_create(&SigHandler_thread,NULL,&SigHandler,NULL);
	if(result < 0)
	{
		perror("Could not start Sig Handler thread.");
	}
#endif
	printf("Listening for UDP messages on port %d\n",PORT_SM);
	printf("Listening for TCP message on port %d\n",PORT_SM);
	fflush(NULL);
	VerifyDM();


   SDMHello hello;
   hello.source.setPort(PORT_SM);
   hello.type = 'C';
   double endTime = 0;
   double timeOut = 5.0;
   while(!ackReceived)
   {
      if(GetCurTime() > endTime)
      {
         debug_f(1, "Sending Hello\n");
         hello.Send();
         endTime = GetCurTime() + timeOut;
      }
      usleep(10000);
   }
   while(!registerReceived)
   {
      usleep(10000);
   }
   debug_f(1, "Registering xTEDS\n");

   // Send the SensorManager's xTEDS
	xteds.source.setSensorID(1);
	xteds.source.setPort(PORT_SM);
	strcpy(xteds.xTEDS, sm_xTEDS);
	xteds.Send();
	MessageSent(&xteds);

   while (!idReceived)
   {
      usleep(10000);
   }
   debug_f(1, "SDMID received\n");

	//Send ReqReg for TM's Mode notification
	reqreg_msg.destination.setPort(PORT_SM);
	reqreg_msg.reply = SDM_REQREG_CURRENT_AND_FUTURE;
	reqreg_msg.id = TM_Mode_ID;
	strcpy(reqreg_msg.device, "TaskManager");
	strcpy(reqreg_msg.interface,"TM_Interface");
	strcpy(reqreg_msg.item_name,"Status");
	reqreg_msg.Send();

	//initialize sensor array
	if (!sensor.InitializeSensors(MAX_SENSORS, prompt, debug))
	{
		printf("Error initializing sensors.\n");
		return 0;
	}

	pthread_join(UDP_thread,NULL);
	pthread_join(TCP_thread,NULL);
}


double GetCurTime()
{
   unsigned int seconds;
   unsigned int uSeconds;
   double curTime;
   SDM_GetTime(&seconds, &uSeconds);
   curTime = seconds + ((double)uSeconds/1000000.0);
   return curTime;
}



#ifdef WIN32
/*	SigIntHandler for Win32 handles only SIGINT.  Upon a SIGINT, the SensorManager cancels its xTEDS and the xTEDS of any connected
	devices, then the process exits.
	INPUTS:
		signum - The signal number returned by the system.
	RETURNS:
		void
*/
void SigIntHandler(int signum)
{
	SDMCancelxTEDS cancel;
	SDMCancel cancel_msg;
	unsigned int i;
	int sig;
#ifndef WIN32
	sigset_t signal_set;
#endif
	cancel.source.setPort(PORT_SM);
	if (signum == SIGINT)
	{
		printf("\nShutting down\n");
		pthread_mutex_lock(&dm_found_mutex);
		if (dm_found)
		{
			// Cancel each sensor
			for(i=0;i<MAX_SENSORS;++i)
			{
				cancel.source.setSensorID(i+SM_OFFSET);
				cancel.Send();
				MessageSent(&cancel);
			}
			// Cancel the SensorManager
			cancel.source.setSensorID(1);
			cancel.Send();
			MessageSent(&cancel);
		}
		pthread_mutex_unlock(&dm_found_mutex);
		// Cancel the subscription to the TM mode message
		cancel_msg.source = tm_mode_source;
		cancel_msg.destination.setPort(PORT_SM);
		cancel_msg.msg_id = tm_mode_msg_id;
		cancel_msg.Send();
		MessageSent(&cancel_msg);
		exit(EXIT_SUCCESS);
	}
}
#else
/*
	Signal handler for the Linux implementation handles both SIGINT and SIGALRM.  SIGINT will cause the SensorManager to cancel its xTEDS
	and the xTEDS of any connected devices, then exit the process.  SIGALRM will publish the performance counter message and reset the
	second-count performance counters back to zero.  This signal handler is a signal handling thread which prevents deadlock because
	the SIGALRM section locks a mutex.
	INPUTS:
		arg - Not used, only there to match the function signature of thread routines.
	RETURNS:
		void * - Always NULL.
*/
void* SigHandler(void* arg)
{
	SDMCancelxTEDS cancel;
	SDMCancel cancel_msg;
	unsigned int i;
	int sig;
	sigset_t signal_set;
	cancel.source.setPort(PORT_SM);
	while (1)
	{
		sigfillset(&signal_set);
		sigwait(&signal_set, &sig);

		switch(sig)
		{
		case SIGINT:
			// Cancel all xTEDS and shutdown
			printf("\nShutting down\n");
			pthread_mutex_lock(&dm_found_mutex);
			if (dm_found)
			{
				// Cancel each sensor
				for(i=0;i<MAX_SENSORS;++i)
				{
					cancel.source.setSensorID(i+SM_OFFSET);
					cancel.Send();
					MessageSent(&cancel);
				}
				// Cancel the SensorManager
				cancel.source.setSensorID(1);
				cancel.Send();
				MessageSent(&cancel);
			}
			pthread_mutex_unlock(&dm_found_mutex);
//			delete [] sensor;
			// Cancel the subscription to the TM mode message
			cancel_msg.source = tm_mode_source;
			cancel_msg.destination.setPort(PORT_SM);
			cancel_msg.msg_id = tm_mode_msg_id;
			cancel_msg.Send();
			MessageSent(&cancel_msg);
			exit(EXIT_SUCCESS);
			break;
		case SIGALRM:
			// Publish performance counters and reset to zero
			PublishPerformanceCounterMessage();
			pthread_mutex_lock(&perf_counter_mutex);
			prevsec_recd = 0;
			prevsec_sent = 0;
			pthread_mutex_unlock(&perf_counter_mutex);
		}
	}
}
#endif



void* AckHandler(void* arg)
{
   SDMAck ackMsg;
   char* buf = (char*)arg;
   if (ackMsg.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMAck message.\n");
		delete [] buf;
		return NULL;
	}
   // Log message
	MessageReceived(&ackMsg);

	if(!ackReceived)
	{
	   debug_f(1, "Ack received for the SM\n");
      ackReceived = true;
      return NULL;
   }

   debug_f(1, "Ack recevied for sensor index: %i\n", ackMsg.error);
   if(ackMsg.error >= 0)
   {
      sensor.SensorAcked(ackMsg.error);
   }

   return NULL;
}


void* RegisterHandler(void* arg)
{
   SDMRegister registerMsg;
   char* buf = (char*)arg;
   if (registerMsg.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMRegister message.\n");
		delete [] buf;
		return NULL;
	}
   // Log message
	MessageReceived(&registerMsg);

   if(!registerReceived)
	{
	   debug_f(1, "Register msg received for the SM\n");
      registerReceived = true;
      return NULL;
   }

   debug_f(1, "Register msg recevied for sensor index: %hi\n", registerMsg.sensorIndex);
   if(registerMsg.sensorIndex >= 0)
   {
      sensor.SendxTEDS(registerMsg.sensorIndex);
   }

   return NULL;
}

void* IDHandler(void* arg)
{
   SDMID idMsg;
   char* buf = (char*)arg;
   if (idMsg.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMID message.\n");
		delete [] buf;
		return NULL;
	}
   // Log message
	MessageReceived(&idMsg);

   if(!idReceived)
	{
	   debug_f(1, "ID msg received for the SM\n");
      idReceived = true;
      return NULL;
   }

   debug_f(1, "ID msg recevied for sensor index: %i\n", (int)((idMsg.destination.getSensorID()&0x00FF) - SM_OFFSET));
   if(idMsg.destination.getSensorID() != 0)
   {
      unsigned long sensorIndex = (idMsg.destination.getSensorID()&0x00FF) - SM_OFFSET;
      sensor.SensorRegConfirmed(sensorIndex);
   }

   return NULL;
}


/*
	ServiceHandler handles the receipt of SDMService messages.  These messages are forwareded to the appropriate ASIM based on the SensorID
	number of the source component identifier in the message.
	INPUTS:
		arg - The buffer containing the SDMService message.
	RETURNS:
		void * - Always NULL
*/
void* ServiceHandler(void* arg)
{
	SDMSerreqst service_request;
	char* buf = (char*)arg;
	if (service_request.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMService message.\n");
		delete [] buf;
		return NULL;
	}
	// Log message
	MessageReceived(&service_request);

	// Request sensor identifier of the sensor on which to perform the service
	const unsigned long request_sid = (service_request.source.getSensorID()&0x00FF);
	debug_f(1,"Service request for sensor id %lu => asim%lu\n",service_request.source.getSensorID(),request_sid-SM_OFFSET);

	// Determine which sensor should get this message
	// If the request is within a valid range
	if (request_sid-SM_OFFSET < MAX_SENSORS)
		sensor[request_sid-SM_OFFSET].Service(service_request);
	else
		printf("Error: Service request for sensor; sensor id out of range (%lu)\n",request_sid);
	delete [] buf;
	return NULL;
}
/*
	CommandHandler handles the receipt of SDMCommand messages.  These messages are forwarded to the appropriate ASIM based on the SensorID
	number of the source component identifier in the message.  If the SensorID applies to the SensorManager, then the appropriate command
	is performed based on the command messages defined in the SM's xTEDS.
	INPUTS:
		arg - The buffer containing the SDMCommand message.
	RETURNS:
		void * - Always NULL.
*/
void* CommandHandler(void* arg)
{
	SDMCommand command;
	char* buf = (char*)arg;
	// Unmarshal message
	if (command.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMCommand message.\n");
		delete [] buf;
		return NULL;
	}
	// Log message
	MessageReceived(&command);
	// Request sensor identifier of the sensor on which to perform the command
	const unsigned long request_sid = (command.source.getSensorID()&0x00FF);
	debug_f(1,"Command for sensor id %lu => asim%lu\n",command.source.getSensorID(),request_sid-SM_OFFSET);

	// Determine which sensor should get this message
	// Command for the SensorManager (Enable message logging)
	if (request_sid == SENSOR_MANAGER_SID && command.command_id == CMD_ENABLE_LOGGING)
	{
		pthread_mutex_lock(&log_service_mutex);
		if (log_service.NeedsInit())
			log_service.SetLogFile("Sensor Manager Message Log\n","smmessages.log");
		log_service.AddMessageType(&command);
		pthread_mutex_unlock(&log_service_mutex);
	}
	// Command for the SensorManager (Disable message logging)
	else if (request_sid == SENSOR_MANAGER_SID && command.command_id == CMD_DISABLE_LOGGING)
	{
		pthread_mutex_lock(&log_service_mutex);
		log_service.RemoveMessageType(&command);
		pthread_mutex_unlock(&log_service_mutex);
	}
	// Commmand for an ASIM, if within valid range
	else if (request_sid != SENSOR_MANAGER_SID && request_sid-SM_OFFSET < MAX_SENSORS)
	{
		pthread_mutex_lock(&sensor_write_mutex);
		usleep(1500);
		sensor[request_sid-SM_OFFSET].Command(command);
		pthread_mutex_unlock(&sensor_write_mutex);
	}
	else
	{
		printf("Error: command reqeust for sensor; no matching command or sensor id out of range (%lu).\n",request_sid);
	}
	delete [] buf;
	return NULL;
}
/*
	SubscriptionHandler handles the receipt of SDMSubreqst messages.  If the message is for an ASIM, it is forwarded appropriately based on the
	SensorID in the source component identifier of the message.  If the message if for the SensorManager, the requester is added to the SM's
	subscription list based on the messages defined in the SM's xTEDS.
	INPUTS:
		arg - The buffer containing the SDMSubreqst message.
	RETURNS:
		void * - Always NULL.
*/
void* SubscriptionHandler(void* arg)
{
	SDMSubreqst request;
	char* buf = (char*)arg;
	// Unmarshal message
	if (request.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMSubreqst message.\n");
		delete [] buf;
		return NULL;
	}
	// Log message
	MessageReceived(&request);
	// Request sensor identifier of the sensor on which to perform the subscription request
	const unsigned long request_sid = (request.source.getSensorID()&0x00FF);
	debug_f(1,"Subscription Request for sensor id %ld => asim%lu\n",request.source.getSensorID(),request_sid-SM_OFFSET);

	// Determine which sensor should get this message
	// Performance counter subscription request for the SensorManager
	if (request_sid == SENSOR_MANAGER_SID && request.msg_id == SUB_PERFORMANCE_COUNTERS)
	{
#ifndef WIN32
		fflush(NULL);
		pthread_mutex_lock(&subscription_mutex);
		sm_subscriptions.AddSubscription(request);
		pthread_mutex_unlock(&subscription_mutex);
		itimerval interval;
		getitimer(ITIMER_REAL, &interval);
		if (interval.it_interval.tv_sec == 0 && interval.it_value.tv_sec == 0)
		{
			//Time interval for the publish interval of the performance counter
			timeval pubInterval;
			pubInterval.tv_sec = 1;
			pubInterval.tv_usec = 0;

			itimerval timerInterval;
			timerInterval.it_interval = pubInterval;
			timerInterval.it_value = pubInterval;

			//Set the performance counter timer
			setitimer(ITIMER_REAL, &timerInterval, NULL);
		}
#endif
	}
	// Subscription request for an ASIM, if within valid range
	else if (request_sid != 1 && request_sid-SM_OFFSET < MAX_SENSORS)
	{
		pthread_mutex_lock(&sensor_write_mutex);
		usleep(1500);
		sensor[request_sid-SM_OFFSET].Subscribe(request);
		pthread_mutex_unlock(&sensor_write_mutex);
	}
	else
	{
		printf("Error: subscription request for sensor; no matching subscription or sensor id out of range (%lu).\n",request_sid);
	}
	delete [] buf;
	return NULL;
}
/*
	DeleteSubscriptionHandler handles the receipt of SDMDeletesub messages.  If the request is for an ASIM, it is forwarded appropriately based
	on the SensorID component identifier.  If the request is for the SensorManager, the subscription is removed from the SM's subscription list
	based on the message definitions in its xTEDS.
	INPUTS:
		arg - The buffer containing the SDMDeletesub message.
	RETURNS:
		void * - Always NULL.
*/
void* DeleteSubscriptionHandler(void* arg)
{
	SDMDeletesub cancel;
	char* buf = (char*)arg;
	// Unmarshal message
	if (cancel.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMDeletesub message.\n");
		delete [] buf;
		return NULL;
	}
	// Log message
	MessageReceived(&cancel);

	// Get the sensor identifier of the sensor on which to perform the delete subscription request
	const unsigned long request_sid = (cancel.source.getSensorID()&0x00FF);
	debug_f(1,"Cancel Request for sensor id %lu => asim%lu\n",cancel.source.getSensorID(),request_sid-SM_OFFSET);

	// Determine which sensor should get this message
	// If this is a request for the SensorManager
	if (request_sid == SENSOR_MANAGER_SID && cancel.msg_id == SUB_PERFORMANCE_COUNTERS)
	{
		pthread_mutex_lock(&subscription_mutex);
		sm_subscriptions.RemoveSubscription(cancel);
		pthread_mutex_unlock(&subscription_mutex);
	}
	// Request for ASIM, check to be sure that the request is within a valid range
	else if (request_sid != SENSOR_MANAGER_SID && request_sid-SM_OFFSET < MAX_SENSORS)
	{
		pthread_mutex_lock(&sensor_write_mutex);
		usleep(1500);
		sensor[request_sid-SM_OFFSET].CancelSubscription(cancel);
		pthread_mutex_unlock(&sensor_write_mutex);
	}
	// Error
	else
	{
		printf("Error: delete subscription request; no matching subscription or sensor id out of range (%lu).\n",request_sid);
	}
	delete [] buf;
	return NULL;
}
/*
	TatHandler handles the receipt of SDMTat messages and forwards the message down to ASIMs.  If the SensorID field is zero, the message is
	forwarded to all ASIMs, otherwise the message is sent to the ASIM specified.
	INPUTS:
		arg - The buffer containing the SDMTat message.
	RETURNS:
		void * - Always NULL.
*/
void* TatHandler(void* arg)
{
	SDMTat tat;
	char* buf = (char*)arg;
	// Unmarshal message
	if (tat.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMTat message.\n");
		delete [] buf;
		return NULL;
	}
	// Log message
	MessageReceived(&tat);

	// Request sensor identifier of the sensor on which to perform the tat
	const unsigned long request_sid = (tat.destination.getSensorID()&0x00FF);

	if(tat.destination.getSensorID() == 0) //send to all sensors
	{
		debug_f(1,"Time at Tone Request for all sensors\n");

		for(unsigned int i=0;i<MAX_SENSORS;++i)
		{
			pthread_mutex_lock(&sensor_write_mutex);
			usleep(1500);
			sensor[i].TimeAtTone(tat.seconds,tat.useconds);
			pthread_mutex_unlock(&sensor_write_mutex);
		}
	}
	else
	{
		debug_f(1,"Time at Tone Request for sensor id %lu => asim%lu\n",tat.destination.getSensorID(),request_sid-SM_OFFSET);

		//determine which sensor should get this message
		// Make sure request is within valid range
		if (request_sid-SM_OFFSET < MAX_SENSORS)
		{
			pthread_mutex_lock(&sensor_write_mutex);
			usleep(1500);
			sensor[request_sid-SM_OFFSET].TimeAtTone(tat.seconds,tat.useconds);
			pthread_mutex_unlock(&sensor_write_mutex);
		}
		else
			printf("Error: time-at-tone request; sensor id out of range (%lu).\n",request_sid);
	}
	delete [] buf;
	return NULL;
}
/*
	ReadyHandler handles the receipt of SDMReady message from the DataManager.  This routine handles the replies from the VerifyDM routine which
	verifies the existence of the DataManager.  This routine is also used to get the IP address of the DM.
	INPUTS:
		arg - The buffer containing the SDMReady message.
	RETURNS:
		void * - Always NULL.
*/
void* ReadyHandler(void* arg)
{
	SDMReady ready;
	char* buf = (char*)arg;
	bool m_dm_found = false;
	pthread_mutex_lock(&dm_found_mutex);
	m_dm_found = dm_found;
	pthread_mutex_unlock(&dm_found_mutex);

	// Unmarshal the message
	if (ready.Unmarshal(buf) < 0)
	{
		printf("Received invalid ready message.\n");
		delete [] buf;
		return NULL;
	}
	else
		MessageReceived(&ready);	// Log message

	// If this is a heartbeat request, respond
	if ((ready.source.getPort() == PORT_SM_MONITOR) && (ready.source.getAddress() == inet_addr("127.0.0.1")) && (ready.source.getSensorID() == 0))
	{
		debug_f(3,"Heartbeat message received.\n");
		ready.SendTo(ready.source);
		MessageSent(&ready);
		delete [] buf;
		return NULL;
	}
	// If the DataManager has not yet been found, this is a response from it
	if (!m_dm_found)
	{
		if (ready.destination.getPort() == PORT_DM  && ready.source.getPort() == PORT_SM)
		{
			DataManager = ready.destination;
			// Set DM found flag to true
			pthread_mutex_lock(&dm_found_mutex);
			dm_found = true;
			pthread_mutex_unlock(&dm_found_mutex);
		}
	}
	delete [] buf;
	return NULL;
}
/*
	RegInfoHandler handles the receipt of SDMRegInfo message to the SensorManager.  The SM issues an SDMReqReg for the TaskManager's mode
	message.  The mode message will be used to reset the SM if the DataManager fails.
	INPUTS:
		arg - The buffer containing the SDMRegInfo message.
	RETURNS:
		void * - Always NULL.
*/
void* RegInfoHandler(void* arg)
{
	char* buf = (char*) arg;
	SDMRegInfo reginfo_msg;
	SDMConsume consume_msg;
	long result;

	// Unmarshal the message
	if ((result = reginfo_msg.Unmarshal(buf)) < 0)
	{
		if (result == SDM_NO_FURTHER_DATA_PROVIDER)
		{
			delete [] buf;
			return NULL;
		}
		else
		{
			printf("Invalid SDMRegInfo message (%ld).\n",result);
			delete [] buf;
			return NULL;
		}
	}
	else
		MessageReceived(&reginfo_msg);
	// If the SDMRegInfo message is about the TaskManager's mode notification
	if (reginfo_msg.id == TM_Mode_ID)
	{
		// Subscribe to this message
		consume_msg.source = reginfo_msg.source;
		consume_msg.destination.setPort(PORT_SM);
		consume_msg.msg_id = reginfo_msg.msg_id;
		tm_mode_msg_id = reginfo_msg.msg_id.getInterfaceMessagePair();
		tm_mode_source = reginfo_msg.source;
		consume_msg.Send();
		MessageSent(&consume_msg);
	}

	delete [] buf;
	return NULL;
}
/*
	DataHandler handles the receipt of SDMData message to the SensorManager.  The SM subscribes to the TaskManager's mode change message which
	informs the SM of a DataManager failure.  If the SDMData message is from the TaskManager, the SensorManager acquires the new DM address and
	reregisters its xTEDS along with the xTEDS of all of its connected sensors.
	INPUTS:
		arg - The buffer containing the SDMData message.
	RETURNS:
		void * - Always NULL.
*/
void* DataHandler(void* arg)
{
	char* buf = (char*) arg;
	SDMData data_msg;
	SDMComponent_ID new_dm_address;
	unsigned char old_mode;

	// Unmarshal the message
	if (data_msg.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMData message.\n");
		delete [] buf;
		return NULL;
	}

	// If this is a TaskManager mode change message
	if (data_msg.msg_id == tm_mode_msg_id && data_msg.source == tm_mode_source)
	{
		old_mode = tm_mode;
		tm_mode = data_msg.msg[0];

		debug_f(1,"TM Mode Change %d.\n",tm_mode);
		if (tm_mode == MODE_SOFT_RESET || tm_mode == MODE_HARD_RESET)
		{
			new_dm_address.Unmarshal(&data_msg.msg[1], 0);

			DataManager = new_dm_address;
			debug_f(1,"New DM address is 0x%lx:%hd %ld\n",new_dm_address.getAddress(), new_dm_address.getPort(), new_dm_address.getSensorID());

			// Clear the SM's subscription list, it is no longer applicable
			pthread_mutex_lock(&subscription_mutex);
			sm_subscriptions.ClearAllSubscriptions();
			pthread_mutex_unlock(&subscription_mutex);


			// Verify the Data Manager
			VerifyDM();

			// Resend the SM's xTEDS
			SDMxTEDS xteds;
			strcpy(xteds.xTEDS, sm_xTEDS);
			xteds.source.setPort(PORT_SM);
			xteds.source.setAddress(Address_SM);
			xteds.source.setSensorID(1);
			xteds.Send();
			MessageSent(&xteds);

			// Re-register all sensors
			for (unsigned int i = 0; i < MAX_SENSORS; i++)
			{
				// Reregister the xTEDS to the DM, of all registered sensors
				sensor[i].ReRegister();
			}
		}
		tm_mode = old_mode;
	}

	delete [] buf;
	return NULL;
}
/*
	PublishPerformanceCounterMessage publishes the SensorManager's performance counters to all registered subscribers.
	INPUTS:
		None.
	RETURNS:
		void
*/
void PublishPerformanceCounterMessage(void)
{
	char msg[16];	// Buffer for performance counters message
	// Fill the buffer with current values of the performance counters
	pthread_mutex_lock(&perf_counter_mutex);
	PUT_UINT(&msg[0], total_recd);
	PUT_UINT(&msg[4], prevsec_recd);
	PUT_UINT(&msg[8], total_sent);
	PUT_UINT(&msg[12], prevsec_recd);
	pthread_mutex_unlock(&perf_counter_mutex);

	pthread_mutex_lock(&subscription_mutex);
	// Publish the notification
	if (sm_subscriptions.Publish(SUB_PERFORMANCE_COUNTERS, msg, 16))
	{
		// Log message
		MessageSent(sm_subscriptions.GetLastPublished());
		debug_f(3,"Performance counter notification sent.\n");
	}
	else
	{
		debug_f(3,"No performance counter subscribers.\n");
	}
	pthread_mutex_unlock(&subscription_mutex);
}

/*
	UDPMonitor listens for messages (which should be from the Data Manager) regarding subscriptions and cancellations for ASIMs and SensorManager
	streams and services
	INPUTS:
		args - Not used, only there to match function signature for thread routines.
	RETURNS:
		void * - Always NULL
*/
void* UDPMonitor(void* args)
{
	int result;
	char buf[BUFSIZE];
	char msg_id;
	int sock;

	pthread_t HandlerThread;
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	sock = UDPpassive(PORT_SM);
	if (sock == IP_SOCK_INVALID)
	{
		printf("UDPMonitor::Could not open port %d.\n",PORT_SM);
		return NULL;
	}
	while(1)
	{
		if(UDPserv_recv(sock, buf, sizeof(buf)) < 0)
      {
         perror("UDPMonitor: UDPserv_recv error");
         UDPclose(sock);
			return NULL;
      }
		msg_id = buf[0];
		pthread_mutex_lock(&perf_counter_mutex);
		total_recd++;
		prevsec_recd++;
		pthread_mutex_unlock(&perf_counter_mutex);
		switch(msg_id)
		{
		case SDM_Serreqst:
			result = pthread_create(&HandlerThread,&attr,&ServiceHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Service Request Handler");
			}
			break;
		case SDM_Command:
			result = pthread_create(&HandlerThread,&attr,&CommandHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Command Handler");
			}
			break;
		case SDM_Subreqst:
			result = pthread_create(&HandlerThread,&attr,&SubscriptionHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Subscription Request Handler");
			}
			break;
		case SDM_Deletesub:
			result = pthread_create(&HandlerThread,&attr,&DeleteSubscriptionHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Cancel Request Handler");
			}
			break;
		case SDM_Tat:
			result = pthread_create(&HandlerThread,&attr,&TatHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Time At Tone Handler");
			}
			break;
		case SDM_Ready:
			result = pthread_create(&HandlerThread,&attr,&ReadyHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if (result < 0)
			{
				perror("Could not start Ready Handler");
			}
			break;
		case SDM_RegInfo:
			result = pthread_create(&HandlerThread,&attr,&RegInfoHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if (result < 0)
			{
				perror("Could not start RegInfo Handler");
			}
			break;
		case SDM_Data:
			result = pthread_create(&HandlerThread,&attr,&DataHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if (result < 0)
			{
				perror("Could not start Data Handler");
			}
			break;
		case SDM_Error:		//there are currently no error messages handled
			break;
      case SDM_ACK:
         result = pthread_create(&HandlerThread,&attr,&AckHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Ack Handler");
			}
         break;
      case SDM_Register:
         result = pthread_create(&HandlerThread,&attr,&RegisterHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Register Handler");
			}
         break;
      case SDM_ID:
         result = pthread_create(&HandlerThread,&attr,&IDHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start ID Handler");
			}
         break;
		default:
			printf("Unexpected Message: %c\n", msg_id);
			SDMAck ackMsg;
			ackMsg.Unmarshal(buf);
			printf("Ack message error code: %i\n", ackMsg.error);

			break;
		}
	}
	UDPclose(sock);
	return NULL;
}

/*
	TCPMonitor listens for TCP Connections used for more robust command delivery.
	INPUTS:
		args - Not used, only there to match function signature for thread routines.
	RETURNS:
		void * - Always NULL
*/
void* TCPMonitor(void* args)
{
	int result;
	char buf[BUFSIZE];
	struct sockaddr_in sin;
	int listen_sock;
	int sock;
  int count;
	short length;
	int status;

	pthread_t HandlerThread;
	pthread_attr_t attr;

	memset (&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = INADDR_ANY;
	sin.sin_port = htons (static_cast<u_int16_t>(PORT_SM));
	listen_sock = TCPpassive(PORT_SM, MAX_TCP_CONNECTIONS);
	if (listen_sock == IP_SOCK_INVALID) {
		return NULL;
	}

	pthread_attr_init(&attr);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	while(1)
	{
		sock = TCPserv_accept(listen_sock);
    if (sock < 0) // cleanup issue 31
    {
        printf("Error: TCPMonitor could not accept socket connection.\n");
        return NULL;
    }
		status = TCPrecv(sock,buf,BUFSIZE);	//get message
    if (status < 0)
    {
        printf("Error: TCPMonitor: recv error\n");
        return NULL;
    }
    count = status;
		while(count < HEADER_SIZE)
    {
			status = TCPrecv(sock,&buf[status],BUFSIZE-status);
      if (status < 0)
      {
          printf("Error: TCPMonitor: recv error\n");
          return NULL;
      }
      count += status;
    }
		length = GET_SHORT(&buf[9]);
		while(length > status - HEADER_SIZE)
    {
			status = TCPrecv(sock,&buf[status],BUFSIZE-status);
      if (status < 0) // cleanup issue 32
      {
        return NULL;
      }
      count += status;
    }
		if(length != status - HEADER_SIZE)
			printf("Error: More bytes recv'd than expected!\n");

		pthread_mutex_lock(&perf_counter_mutex);
		total_recd++;
		prevsec_recd++;
		pthread_mutex_unlock(&perf_counter_mutex);

		switch(buf[0])
		{
		case SDM_Serreqst:
			result = pthread_create(&HandlerThread,&attr,&ServiceHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Service Request Handler");
			}
			break;
		case SDM_Command:
			result = pthread_create(&HandlerThread,&attr,&CommandHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Command Handler");
			}
			break;
		case SDM_Subreqst:
			result = pthread_create(&HandlerThread,&attr,&SubscriptionHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Subscription Request Handler");
			}
			break;
		case SDM_Deletesub:
			result = pthread_create(&HandlerThread,&attr,&DeleteSubscriptionHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Cancel Request Handler");
			}
			break;
		case SDM_Tat:
			result = pthread_create(&HandlerThread,&attr,&TatHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Time At Tone Handler");
			}
			break;
		case SDM_Ready:
			result = pthread_create(&HandlerThread,&attr,&ReadyHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if (result < 0)
			{
				perror("Could not start Ready Handler");
			}
			break;
		case SDM_RegInfo:
			result = pthread_create(&HandlerThread,&attr,&RegInfoHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if (result < 0)
			{
				perror("Could not start RegInfo Handler");
			}
			break;
		case SDM_Data:
			result = pthread_create(&HandlerThread,&attr,&DataHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if (result < 0)
			{
				perror("Could not start Data Handler");
			}
			break;
		case SDM_Error:		//there are currently no error messages handled
			break;
      case SDM_ACK:
         result = pthread_create(&HandlerThread,&attr,&AckHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Ack Handler");
			}
         break;
      case SDM_Register:
         result = pthread_create(&HandlerThread,&attr,&RegisterHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start Register Handler");
			}
         break;
      case SDM_ID:
         result = pthread_create(&HandlerThread,&attr,&IDHandler,memcpy(new char[BUFSIZE],buf,BUFSIZE));
			if(result < 0)
			{
				perror("Could not start ID Handler");
			}
         break;
		}
		TCPclose(sock);
	}
	return NULL;
}
/*
	VerifyDM is used to verify the existence of the DataManager when the SM is started.  The existence of the DM is necessary for any SDM
	component to operate.
	INPUTS:
		None.
	RETURNS:
		void
*/
void VerifyDM(void)
{
	bool msg_rcvd = false;
	SDMReady msg;
	SDMReady msg_in;
	msg.destination.setPort(PORT_SM);
	msg.destination.setAddress(Address_SM);
	msg.source.setPort(PORT_SM);
	printf("Searching for DM ..");
	fflush(NULL);
	do {
		pthread_mutex_lock(&perf_counter_mutex);
		total_sent++;
		prevsec_sent++;
		pthread_mutex_unlock(&perf_counter_mutex);
		msg.SendBCast(DataManager.getAddress(), PORT_DM);
		putchar('.');
		fflush(NULL);
		usleep(250000);
		pthread_mutex_lock(&dm_found_mutex);
		msg_rcvd = dm_found;
		pthread_mutex_unlock(&dm_found_mutex);
	} while (!msg_rcvd);
	printf("DM found\n");
}
/*
	GetNodeAddress sets the IP address of the SensorManager in the global variable Address_SM.
	Returns: int - Zero on success, -1 on failure.
*/
#ifdef WIN32
int GetNodeAddress()
{
	hostent * localHost;
	char * IPAddr;
	char hostname[64];

	if (gethostname(hostname,sizeof(hostname)) < 0)
		return -1;
	if ((localHost = gethostbyname(hostname)) == NULL)
		return -1;
	IPAddr = inet_ntoa(*(struct in_addr *)localHost->h_addr_list[0]);
	Address_SM = inet_addr(IPAddr);
	debug_f(3,"Sensor Manager address is 0x%x\n",Address_SM);
	return 0;
}
#else
int GetNodeAddress()
{
	struct ifreq ifr;
	struct sockaddr_in *sin = (struct sockaddr_in *)&ifr.ifr_addr;
	int sockfd;

	bzero(&ifr, sizeof(ifr));

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Error GetNodeAddres(), socket(): ");
		return(-1);
	}

	strcpy(ifr.ifr_name, "eth0");
	sin->sin_family = AF_INET;

	if(ioctl(sockfd, SIOCGIFADDR, &ifr) == 0)
	{
		Address_SM = inet_addr(inet_ntoa(sin->sin_addr));
		debug_f(3,"SM Address is %ld\n",Address_SM);
	}
	else
		return -1;
	return 0;
}
#endif
/*
	MessageSent is called whenever an SDM* message is sent within the SensorManager.  This function increments the performance counters and
	logs the message if the message logger is set.
	INPUTS:
		msg - A pointer to the SDM* message sent.
	RETURNS:
		void
*/
void MessageSent(SDMmessage *msg)
{
	pthread_mutex_lock(&perf_counter_mutex);
	total_sent++;
	prevsec_sent++;
	pthread_mutex_unlock(&perf_counter_mutex);
	pthread_mutex_lock(&log_service_mutex);
	if (!log_service.IsEmpty())
		log_service.MessageSent(msg);
	pthread_mutex_unlock(&log_service_mutex);
}
/*
	MessageReceived is called whenever an SDM* message is received within the SensorManager.  This function logs the message if the log
	service is set.
	INPUTS:
		msg - A pointer to the SDM* message received.
	RETURNS:
		void
*/
void MessageReceived(SDMmessage *msg)
{
	pthread_mutex_lock(&log_service_mutex);
	if (!log_service.IsEmpty())
		log_service.MessageReceived(msg);
	pthread_mutex_unlock(&log_service_mutex);
}
