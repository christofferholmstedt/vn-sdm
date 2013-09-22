#ifndef _SENSOR_H_
#define _SENSOR_H_

#define SM_OFFSET	2		// offset of sensor_id from asim number

#include <pthread.h>
#include "../common/SubscriptionManager/SubscriptionManager.h"
#ifdef WIN32
#include "../common/asim/asim_win32.h"
#else
#include "../common/asim/ASIM.h"
#endif
#include "../common/message/SDMSubreqst.h"
#include "../common/message/SDMDeletesub.h"
#include "../common/message/SDMCommand.h"
#include "../common/message/SDMSerreqst.h"
#include "../common/message/SDMComponent_ID.h"

extern void MessageSent(SDMmessage *msg);

class SensorMonitor;
class Sensor
{
public:
  Sensor(void);
  Sensor(long);
  Sensor(const Sensor&);
  ~Sensor();

  // Public operations
  char Read(unsigned short& length, unsigned char* buf, int bufsize);
  void Subscribe(SDMSubreqst&);
  void CancelSubscription(SDMDeletesub&);
  void Service(SDMSerreqst&);
  void Command(SDMCommand&);
  void TimeAtTone(unsigned long seconds,unsigned long useconds);
  void SetDebug(int);
  void ReRegister();
  Sensor& operator=(const Sensor&);
  bool CheckConnection();
  pthread_t* StartUSBMonitor(long, SensorMonitor* Monitor);
  void CancelSensor(bool Disconnected);

  // Public data members
  ASIM device;
  SDMComponent_ID sensor_id;
  char *device_xTEDS;

private:
  // Private methods
  void Cancel();
  bool Register(int sensorIndex);
  static void* USBMonitor(void*);
  bool Open(long);

  // Private data members
  SubscriptionManager subscriptions;
  char device_name[15];
  pthread_mutex_t sensor_mutex;		//Locks ASIM writes and read/write from the subscriptions member
  bool connected;
  bool m_Ready;
  int debug_level;
  pthread_t m_USBMonitorThread;
  SensorMonitor* m_Monitor;
};

class USBMonitorThreadArgs
{
public:
	USBMonitorThreadArgs(Sensor* Sens, SensorMonitor* Mon, int ID) : SensorInstance(NULL), MonitorInstance(NULL), SensorID(-1)
	{ SensorInstance = Sens; MonitorInstance = Mon; SensorID = ID; }
	Sensor* SensorInstance;
	SensorMonitor* MonitorInstance;
	int SensorID;
};

#endif
