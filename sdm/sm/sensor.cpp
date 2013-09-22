#include "sensor.h"
#include "../common/message_defs.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/time.h>
#include "../common/message/SDMxTEDS.h"
#include "../common/message/SDMCancelxTEDS.h"
#include "../common/message/SDMTat.h"
#include "../common/message/SDMHello.h"
#include "SensorMonitor.h"

#define MAX_TRIES	30

Sensor::Sensor():
  device(ASIM()),
  sensor_id(),
  device_xTEDS(NULL),
  subscriptions(SubscriptionManager()),
  sensor_mutex(),
  connected(false),
  m_Ready(false),
  debug_level(0),
  m_USBMonitorThread(),
  m_Monitor(NULL)
{
  device_name[0] = '\0';
  pthread_mutex_init(&sensor_mutex, NULL);
  sensor_id.setPort(PORT_SM);
}

Sensor::Sensor(long id):
  device(ASIM()),
  sensor_id(),
  device_xTEDS(NULL),
  subscriptions(SubscriptionManager()),
  sensor_mutex(),
  connected(false),
  m_Ready(false),
  debug_level(0),
  m_USBMonitorThread(),
  m_Monitor(NULL)
{
  device_name[0] = '\0';
  pthread_mutex_init(&sensor_mutex, NULL);
  sensor_id.setPort(PORT_SM);
  Open(id);
}

// It doesn't really make sense to copy or assign a Sensor object.  Therefore 
// Copy Constructor and operator= functions are declared, but not defined; 
// creating a linker error if the developer tries to use them.

// Sensor::Sensor(const Sensor& a):
//   subscriptions(a.subscriptions),
//   device(a.device),
//   sensor_id(a.sensor_id),
//   device_xTEDS(a.device_xTEDS),
//   mutex(a.mutex),
//   connected(a.connected),
//   debug_level(a.debug_level)
// {
// }
//
// Sensor& Sensor::operator=(const Sensor& a)
// {
//   subscriptions = a.subscriptions;
//   device = a.device;
//   sensor_id = a.sensor_id;
//   mutex = a.mutex;	//this is a pointer but the copy should point to the 
//                         //same mutex
//   connected = a.connected;
//   return *this;
// }

Sensor::~Sensor()
{
  pthread_mutex_destroy(&sensor_mutex);
}

void Sensor::SetDebug(int new_debug_level)
{
  debug_level = new_debug_level;
  device.SetDebug(new_debug_level);
}

/** Open sensor for use

   Open sets the sensor's SensorID number and saves the path name of the sensor.
   This function is called from the SensorManager.

   INPUTS:
   @param id - The sensor ID number to be assigned for this sensor.

   RETURNS:
   @return bool - True on success, false otherwise.
 */
bool Sensor::Open(long id)
{
  //set sensor id
  sensor_id.setSensorID(id+SM_OFFSET);
  //build device_name string
#ifdef WIN32
  sprintf(device_name,"\\\\.\\ASIM-0%ld",id+1);
#else
  sprintf(device_name,"/dev/asim%ld",id);
#endif
  return true;
}

/** Monitor the USB channel

  USBMonitor is a thread function that monitors the USB channel through which 
  the SensorManager and the sensor device communicate. If a device is not 
  available, this function tries to open a handle.  If a device is connected, 
  this function attempts to read data from it.  If a device is connected and 
  then loses connection, this function will cancel the device from the 
  DataManager.

  INPUTS:
  @param arg - The Sensor object representing the sensor connected.

  RETURNS:
  @return void * - Always NULL.
*/
void* Sensor::USBMonitor(void* arg)
{
  USBMonitorThreadArgs* ThreadArgs = (USBMonitorThreadArgs*)arg;
  Sensor* sensor = ThreadArgs->SensorInstance;
  SensorMonitor* monitor = ThreadArgs->MonitorInstance;
  int ID = ThreadArgs->SensorID;
  delete ThreadArgs;

  unsigned short length;
  unsigned char buf[BUFSIZE];
  //open ASIM device

  // Set the thread's cancel state and type
  if ( 	0 != pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL) ||
	0 != pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL) )
  {
    printf("Could not set the thread's cancel state/type in USBMonitor.\n");
    return NULL;
  }

  if(sensor->debug_level>=2)
    printf("Monitoring %s\n",sensor->device_name);

  while(1)
  {
    fflush(NULL);
    pthread_testcancel();
    if(sensor->connected)
    {
      /*Verify that this sensor is still connected*/
      sensor->connected = sensor->device.VerifyConnection();
      /*If the sensor is still connected, attempt to read from it*/
      if(sensor->connected)
      {
	if(sensor->debug_level>=3)
	  printf("starting read on %s\n",sensor->device_name);

	sensor->Read(length, buf, sizeof(buf));
      }
      /*If the device has lost connected, cancel it*/
      else
      {
	if(sensor->debug_level>=0)
	{
	  printf("%s disconnected\n",sensor->device_name);
	  fflush(NULL);
	}
	sensor->Cancel();
	sensor->m_Ready = false;
	sensor->device.Close();
      }
    }
    /*If the sensor is not connected, attempt to open a handle to it.*/
    else
    {
      /*If the sensor exists, register it*/
      if(sensor->device.Open(sensor->device_name))
      {
	if(sensor->debug_level>=0)
	{
	  printf("%s connected\n",sensor->device_name);
	  fflush(NULL);
	}
	sensor->connected = true;
	monitor->SensorRegistering(ID);
	if(sensor->Register(ID))
	{
	  printf("%s registered\n",sensor->device_name);
	  monitor->SensorRegistered(ID);
	  sensor->m_Ready = true;
	  fflush(NULL);
	}
	else
	{
	  printf("%s failed to register\n",sensor->device_name);
	  fflush(NULL);
	  sensor->m_Ready = false;
	  sensor->device.Close();
	  sensor->connected = false;
	}

      }
      /*Otherwise, close the handle*/
      else
      {
	if(sensor->debug_level>=6)
	{
	  printf("No device connected at %s\n",sensor->device_name);
	  fflush(NULL);
	}
	sensor->device.Close();
	sleep(1);
      }
    }
  }
  return NULL;
}

/** Start the USB listener thread.

  StartUSBMonitor starts the USB listener thread for sensor communications,
  by spawning off a new thread.
  INPUTS:
  @param id - The SensorID number of the sensor device.

  RETURNS:
  @return  pthread_t* - A pointer to the pthread started.
*/
pthread_t* Sensor::StartUSBMonitor(long id, SensorMonitor* Monitor)
{
  //static pthread_t USBMonitor_thread;
  m_Monitor = Monitor;

  int result;
  Open(id);
  result = pthread_create(&m_USBMonitorThread,NULL,&USBMonitor, 
			  new USBMonitorThreadArgs(this, Monitor, id));
  if(result < 0)
  {
    perror("Could not start ASIM monitor");
  }
  return &m_USBMonitorThread;
}

/** Remove a sensor from registration and listening.

  Kill the listener thread, and removes the subscription for the sensor.

  INPUTS:
  @param Disconnected - is the sensor currently disconnected.
*/
void Sensor::CancelSensor(bool Disconnected)
{
  if (Disconnected)
    printf("%s disconnected\n", device_name);
  // Kill the listener thread
  if (0 != pthread_cancel(m_USBMonitorThread))
  {
    printf("Could not cancel USBMonitor thread.\n");
  }
  // Cancel xTEDS and subscriptions
  Cancel();
}

/** Check if sensor still connected
 *
 * RETURNS:
 * @return true if connected, otherwise false
 *
 * NOTES:
 * Alternative to device.VerifyConnection().  Trying device.VerifyConnection()
 * while another thread is block on a read for the device resets the ASIM.
 */
bool Sensor::CheckConnection()
{
  // This is sort of an ugly hack... Trying device.VerifyConnection() while 
  // another thread is block on a read for the device resets the ASIM.  This 
  // method will check to see if the handle still exists in /dev.  This is used
  // to verify that an ASIM hasn't disconnected and if it has, the calling 
  // thread can cancel it.  The device driver doesn't cancel
  // an ASIM if it is connected, but the handle disappears in /dev.

  char Command[64];
  snprintf(Command, sizeof(Command), "ls %s > /dev/null", device_name);
  if (0 != system(Command))
    return false;

  return true;
}

/** TimeAtTone sends a TAT message down to the attached ASIM.
 *
 * INPUTS:
 * @param seconds - The seconds value for the time.
 * @param useconds - The microseconds value for the time.
 *
 * RETURNS:
 * @return void
*/
void Sensor::TimeAtTone(unsigned long seconds,unsigned long useconds)
{
  if(!m_Ready)
    return;

  if(debug_level>=1)
    printf("%s : Time At Tone %lu sec %lu usec\n",device_name,seconds,useconds);

  pthread_mutex_lock(&sensor_mutex);
  if (!device.TimeAtTone(seconds,useconds))
    printf("%s : Error sending time at tone message.\n", device_name);
  pthread_mutex_unlock(&sensor_mutex);
}

/** Read data from connected ASIM.
 *
 *  Read attempts to read data from the connected ASIM.  If the message is data,
 *  it is published to all interested subscribers, otherwise
 *  the message received is printed to the screen (if debug is high enough).
 *
 * INPUTS:
 * @param buf    [output] - The buffer in which to store the message.
 * @param length [output] - The number of bytes stored in buf.
 *
 * RETURNS:
 * @return char - The type of ASIM message received.
 */
char Sensor::Read(unsigned short& length, unsigned char* buf, int bufsize)
{
  char msg_type;
  int error_code;
  char error_str[80];
  int i;

  if(!connected)
    return ASIM_ERROR;

  memset(buf, 0, bufsize);	//Clear out the message buffer
  msg_type = device.Read(length,buf,bufsize);
  error_code = errno;

  switch(msg_type)
  {
  case ASIM_STATUS:
    if (buf[0]&0x80) //first bit is set for an error
    {
      if(debug_level>=0)
      {
	printf("ASIM %s status ERROR: %hhd\n",device_name,buf[0]);
      }
      if(debug_level>=2)
      {
	if(buf[0]&0x40) //illegal command bit
	{
	  printf("\tIllegal or unrecognized command\n");
	}
	if(buf[0]&0x20) //self test failure bit
	{
	  printf("\tSelf Test failed\n");
	}
      }
    }
    else
    {
      if(debug_level>=1)
      {
	printf("ASIM %s status OK: %hhd\n",device_name,buf[0]);
      }
    }
    if(debug_level>=2)
    {
      if(buf[0]&0x10) //mode bit
      {
	printf("\tASIM mode: operational\n");
      }
      else
      {
	printf("\tASIM mode: idle\n");
      }
    }
    break;

  case ASIM_XTEDS:
    if(debug_level>=1)
    {
      printf("%s xTEDS (%d)\n",device_name,length);
      fflush(NULL);
      if(debug_level>=2)
      {
	for(i=0;i<length;++i)
	{
	  if(isprint(buf[i])||isspace(buf[i]))
	  {
	    printf("%c",buf[i]);
	  }
	  else
	  {
	    printf("\nERROR %s xTEDS contains invalid character 0x%x\n",
		   device_name,buf[i]);
	  }
	}
      }
    }
    break;

  case ASIM_XTEDS_ID_PAIR:
    if(debug_level>=1)
    {
      printf("%s xTEDS_PID (%d)\n",device_name,length);
      fflush(NULL);
      if(debug_level>=2)
      {
	printf(" (ID=0x");
	for(i = 0; i < (length > 4 ? 4 : length);++i)
	  printf("%x",buf[i]);
	printf(")\n");
	for( ;i<length;++i)
	{
	  if(isprint(buf[i])||isspace(buf[i]))
	  {
	    printf("%c",buf[i]);
	  }
	  else
	  {
	    printf("\nWARNING: %s xTEDS contains invalid character 0x%x\n",
		   device_name,buf[i]);
	  }
	}
      }
    }
    break;

  case ASIM_DATA:
    if(debug_level>=2)
    {
      printf("%s produced message %hhd\n",device_name,buf[0]);
    }
    pthread_mutex_lock(&sensor_mutex);
    if(!subscriptions.Publish(buf[0],buf[1],(char*)(buf+2),length-2))
    {
      if(debug_level>=1)
      {
	printf("\t%s:%hhd had no subscribers\n",device_name,buf[0]);
	printf("\tCanceling %s:%hhd\n",device_name,buf[0]);
      }
      device.Cancel(buf[0], buf[1]);
    }
    else
    {
      MessageSent(subscriptions.GetLastPublished());
    }
    pthread_mutex_unlock(&sensor_mutex);
    break;

  case ASIM_TIME_AT_TONE:
  {
    // A modification for Fronterhouse.  The ASI protocol doesn't define an 
    // ASIM producing a Time-At-Tone, however, the GPS SPA-U ASIM will.  This 
    // will send it to the SM, which will in turn send it to all ASIMs connected
    // to the SM.

    SDMTat TATMsg;
    char SendBuffer[BUFSIZE];

    TATMsg.destination.setSensorID(0);	// Send to all ASIMs
    TATMsg.seconds = GET_UINT(buf);
    TATMsg.useconds = GET_UINT(buf+4);

    int TATLength = TATMsg.Marshal(SendBuffer);
    if (TATLength < 0)
    {
      printf("Error marshalling TAT message.\n");
      return ASIM_ERROR;
    }

    // Send to the SensorManager listen thread
    if (UDPsendto("127.0.0.1", PORT_SM, SendBuffer, TATLength) < 0)
    {
      printf("Error sending TAT message.\n");
      return ASIM_ERROR;
    }
  }
  break;

  case ASIM_VERSION:
    if(debug_level>=1)
      printf("%s running ASIM version %hhd\n",device_name,buf[0]);
    break;

  case ASIM_ERROR:
    if(debug_level>=0)	//display errors
    {
      printf("%s read error: %s\n",device_name,strerror_r(error_code,error_str,80));
    }
    break;

  case ASIM_TIMEOUT:
    if(debug_level>=3)	//only display timeout errors on debug 3
    {
      printf("%s read timeout: %s\n",
	     device_name,strerror_r(error_code,error_str,80));
    }
    break;

#ifdef WIN32
  case NULL:	/*Default return for no message available in Win32*/
    usleep(10000);		/*Give time for a message to be produced*/
    break;
#endif
  default:
    if(debug_level>=0)
      printf("%s produced an undefined message 0x%x\n",device_name,msg_type);
    break;
  }
  return msg_type;
}

/** Register initializes the sensor, requests its xTEDS, and registers the 
 *  sensor with the SDM.
 *
 * INPUTS:
 *  None.
 * RETURNS:
 * @return bool - True on success, false on failure.
 */
bool Sensor::Register(int sensorIndex)
{
  SDMxTEDS xTEDS;
  unsigned short length;
  char buf[BUFSIZE];
  bool isValid = false;
  char* end_xTEDS;	//pointer to the </xteds> tag
  char status;
  int register_tries;
  int sleep_time;

  //
  // Initialize
  //
  if(debug_level>=2)
    printf("Initializing %s\n",device_name);

  device.Initialize();
  status = Read(length,(unsigned char*)buf, sizeof(buf));
  if(status == ASIM_ERROR)
    return false;

  //
  // Version Request
  //
  if(debug_level>=2)
    printf("Requesting ASIM version for %s\n",device_name);
  device.ReqVersion();
  status = Read(length,(unsigned char*)buf, sizeof(buf));
  if(status == ASIM_ERROR)
    return false;

  //
  // xTEDS Request
  //
  if(debug_level>=2)
    printf("Requesting xTEDS for %s\n",device_name);
  device.ReqxTEDS();
  register_tries = 1;
  sleep_time = 0;

  while(!isValid)
  {
    status = Read(length,(unsigned char*)buf, sizeof(buf));
    if(status==ASIM_ERROR)
      return false;

    if(status!=ASIM_XTEDS && status!=ASIM_XTEDS_ID_PAIR)
    {
      //Occassionally on the first attempt, a version request may have just 
      // been read, so don't output the below error message if not really an 
      // error on the first attempt
      if(debug_level>=0 && register_tries != 1)
      {
	printf("ERROR: reading xTEDS for %s failed, retrying - status is %hhx\n",
	       device_name,status);
      }

      if(register_tries > MAX_TRIES)
      {
	printf("ERROR: bad device %s\n",device_name);
	return false;
      }
      sleep_time += register_tries;	//increase the wait between tries
      register_tries++;
      sleep(sleep_time);
      if (debug_level >= 2)
      {
	printf("Re-requesting xTEDS for %s\n",device_name);
      }
      device.ReqxTEDS();		//re-request xTEDS
    }
    else
    {
      //look for </xTEDS> to insure that the entire xTEDS was read
      end_xTEDS = NULL;
      end_xTEDS = strstr(buf+4,"</xTEDS>"); //Add four because if a PID is 
                                            // present, it could contain 0x00 
                                            // (null-term)
      if(end_xTEDS!=NULL)
	isValid = true;
      else
      {
	if(debug_level>=0)
	{
	  printf("ERROR: read invalid xTEDS for %s\n",device_name);
	  if(debug_level>=2)
	  {
	    printf("Requesting xTEDS for %s\n",device_name);
	  }
	}

	if(register_tries > MAX_TRIES)
	{
	  printf("ERROR: bad device %s\n",device_name);
	  return false;
	}

	sleep_time += register_tries;	//increase the wait between tries
	register_tries++;
	sleep(sleep_time);
	device.ReqxTEDS();		//re-request xTEDS
      }
    }
  }

  //Free the old xTEDS, if this is a re-reg
  if (device_xTEDS != NULL)
  {
    delete [] device_xTEDS;
    device_xTEDS = NULL;
  }


//TODO:  What is this whole ID pair thing?
  //If this was an xTEDS reply with a corresponding unique ID
  if (status == ASIM_XTEDS_ID_PAIR)
  {
    device_xTEDS = new char[length+1-4];   	//Allocate xTEDS buffer, without 
                                                // ID number
    strncpy(device_xTEDS, buf+4, length-4);	//Copy the xTEDS, without the ID 
                                                // number
    device_xTEDS[length] = '\0';		//End string
    //xTEDS.pid = GET_INT(buf);			//Copy out the PID identifier of 
                                                // this ASIM
    //memcpy(xTEDS.xTEDS, buf+4, length - 4);	//Copy the xTEDS into the 
                                                //SDMxTEDS message, without the ID
  }
  //This is just a plain old xTEDS reply
  else
  {
    device_xTEDS = new char[length+1];		//Allocate the xTEDS buffer
    strncpy(device_xTEDS,buf, length);		//Copy the xTEDs
    device_xTEDS[length] = '\0';		//End string
  }

  SDMHello helloMsg;
  helloMsg.type = 'D';
  helloMsg.source.setPort(PORT_SM);
  helloMsg.source.setSensorID(sensorIndex);
  helloMsg.Send();
  unsigned int sendTime = 0;
  if(m_Monitor != NULL)
  {
    sendTime = m_Monitor->SetHelloSendTime(sensorIndex);
  }


  if(debug_level >= 0)
  {
    printf("SDMHello msg sent for sensor at index: %i at time: %i\n", sensorIndex, sendTime);
  }

  if(debug_level>=2)
  {
    printf("USB path of %s:%s\n",device_name,xTEDS.SPA_node);
  }

  return true;
}

/** ReRegister the ASIM.
 * ReRegister re-registers an ASIM with the SDM by resending its xTEDS.  A 
 * device is reregistered when the DataManager fails and a new DM has been 
 * elected.
 *
 * INPUTS:
 *  None.
 * RETURNS:
 *  @return void
 */
void Sensor::ReRegister()
{
  //Reregister the xTEDS of the current device
  SDMxTEDS xteds_msg;
  if (m_Ready)
  {
    strcpy(xteds_msg.SPA_node, device.USBLocation());
    xteds_msg.source = sensor_id;
    strcpy(xteds_msg.xTEDS, device_xTEDS);
    xteds_msg.Send();
    MessageSent(&xteds_msg);
  }
  //Cancel all subscriptions, which are no longer applicable
  pthread_mutex_lock(&sensor_mutex);
  subscriptions.ClearAllSubscriptions();
  pthread_mutex_unlock(&sensor_mutex);
}

/** Service sends a service request message down to an ASIM.
 *
 * INPUTS:
 * @param request - The SDMSerreqst message whose data will be sent.
 * RETURNS:
 * @return void
 */
void Sensor::Service(SDMSerreqst& request)
{
  if(!m_Ready)
    return;

  if(debug_level>=1)
    printf("%s recieved service request.\n",device_name);

  pthread_mutex_lock(&sensor_mutex);
  subscriptions.AddSubscription(request);
  device.Command(request.command_id.getInterface(),
		 request.command_id.getMessage(),
		 request.length,
		 (unsigned char*)request.data);
  pthread_mutex_unlock(&sensor_mutex);
}

/** Command sends a command message down to an ASIM.
 *
 * INPUTS:
 * @param command - The SDMCommand message whose data will be sent.
 * RETURNS:
 * @return void
 */
void Sensor::Command(SDMCommand& command)
{
  if(!m_Ready)
    return;

  if(debug_level>=1)
    printf("%s recieved command for interface id: %d command id: %d\n", 
	   device_name, 
	   command.command_id.getInterface(), 
	   command.command_id.getMessage());

  pthread_mutex_lock(&sensor_mutex);
  device.Command(command.command_id.getInterface(),
		 command.command_id.getMessage(),
		 command.length,(unsigned char*)command.data);
  pthread_mutex_unlock(&sensor_mutex);
}

/** Cancel an ASIM from the SDM system.
 * 
 * Cancel cancels an ASIM from the SDM system by sending an SDMCancelxTEDS 
 * message to the DataManager.
 *
 * INPUTS:
 *  None.
 * RETURNS:
 *  @return void
 */
void Sensor::Cancel()
{
  if(debug_level>=2)
    printf("Canceling xTEDS for %s\n",device_name);

  SDMCancelxTEDS cancel;
  cancel.source = sensor_id;
  cancel.Send();
  MessageSent(&cancel);

  pthread_mutex_lock(&sensor_mutex);
  connected = false;
  subscriptions.ClearAllSubscriptions();
  pthread_mutex_unlock(&sensor_mutex);
}

/** Subscribe sends a subscription request (for a data stream) down to the ASIM.
 *
 * INPUTS:
 * @param request - The SDMSubreqst message whose data is sent.
 *
 * RETURNS:
 * @return void
 */
void Sensor::Subscribe(SDMSubreqst& request)
{
  if(!m_Ready)
    return;

  if(debug_level>=1)
    printf("%s recieved subscription request.\n",device_name);

  pthread_mutex_lock(&sensor_mutex);
  subscriptions.AddSubscription(request);
  device.ReqData(request.msg_id.getInterface(),
		 request.msg_id.getMessage(),
		 request.destination.getAddress(),
		 request.destination.getPort());
  pthread_mutex_unlock(&sensor_mutex);
}

/** CancelSubscription sends a cancel subscription request down to the ASIM.
 *
 * INPUTS:
 * @param request - The SDMDeletesub message whose data will be sent.
 * 
 * RETURNS:
 * @return void
 */
void Sensor::CancelSubscription(SDMDeletesub& request)
{
  if(!m_Ready)
    return;

  if(debug_level>=1)
    printf("%s recieved cancel subscription request.\n",device_name);

  pthread_mutex_lock(&sensor_mutex);
  subscriptions.RemoveSubscription(request);
  pthread_mutex_unlock(&sensor_mutex);

}
