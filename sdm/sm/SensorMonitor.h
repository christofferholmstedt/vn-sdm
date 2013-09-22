#ifndef _SENSOR_MONITOR_H_
#define _SENSOR_MONITOR_H_

#include <pthread.h>
#include "SensorRecord.h"
#include "sensor.h"
#include "../common/Time/SDMTime.h"

class SensorMonitor
{
public:
	SensorMonitor();
	~SensorMonitor();
	SensorMonitor(const SensorMonitor&);
	SensorMonitor& operator = (const SensorMonitor&);

	bool InitializeSensors(unsigned int NumSensors, bool Prompt, int DebugLevel);
	bool SensorRegistering(int SensorNum);
	bool SensorRegistered(int SensorNum);
	bool SensorAcked(int SensorNum);
	bool SensorRegConfirmed(int SensorNum);
	unsigned int SetHelloSendTime(int SensorNum);
	unsigned int SetxTEDSSendTime(int SensorNum);
	bool SendxTEDS(int SensorNum);
	Sensor& operator[] (int Index);
private:
	static void* SensorMonitorFunc(void*);

	pthread_t m_SensorMonitorThread;
	int m_NumSensors;
	Sensor* m_Sensors;

	pthread_mutex_t m_SensorDataMutex;
	SensorRecord* m_SensorData;

};


#endif

