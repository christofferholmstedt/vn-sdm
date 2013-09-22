#include <sys/time.h>
#include <unistd.h>
#include <string.h>
#include "SensorMonitor.h"
#include "../common/message/SDMHello.h"
#include "../common/message/SDMxTEDS.h"
#ifdef WIN32
# include <winsock2.h>
#endif
//#define DEBUG_MONITOR	1

const int TIMEOUT_INTERVAL = 6; // In seconds
const int SENSOR_CHECK_INTERVAL = 5;


SensorMonitor::SensorMonitor() : m_SensorMonitorThread(), m_NumSensors(0), m_Sensors(NULL), m_SensorDataMutex(), m_SensorData(NULL)
{
	pthread_mutex_init(&m_SensorDataMutex, NULL);
}

SensorMonitor::~SensorMonitor()
{
	delete [] m_Sensors;
	delete [] m_SensorData;

	pthread_mutex_destroy(&m_SensorDataMutex);
}

bool SensorMonitor::InitializeSensors(unsigned int NumSensors, bool Prompt, int DebugLevel)
{
	m_NumSensors = NumSensors;
	m_Sensors = new Sensor[NumSensors];
	m_SensorData = new SensorRecord[NumSensors];

	for(unsigned int i = 0; i < NumSensors; ++i)
	{
		bool init_sensor = true;
		char response;
		if(Prompt)
		{
			printf("Initialize sensor /dev/asim%d (y/n)? ",i);
			scanf("%c",&response);
			getchar();
			if((response == 'Y')||(response == 'y'))
			{
				printf("\tStarting /dev/asim%d\n",i);
			}
			else
			{
				init_sensor = false;
			}
		}
		if(init_sensor)
		{
			m_Sensors[i].StartUSBMonitor(i, this);
			m_Sensors[i].SetDebug(DebugLevel);
		}
	}

	// Start the monitor thread
	if (0 != pthread_create(&m_SensorMonitorThread, NULL, &SensorMonitorFunc, this))
	{
		printf("Error starting sensor monitor thread.\n");
		return false;
	}

	// Detach the monitor thread
	if (0 != pthread_detach(m_SensorMonitorThread))
	{
		printf("Error detaching sensor monitor thread.\n");
		return false;
	}
	return true;
}


unsigned int GetCurSeconds()
{
	struct timeval Time;
	gettimeofday(&Time, NULL);
	return Time.tv_sec;
}

void* SensorMonitor::SensorMonitorFunc(void* SensorMonitorInstance)
{
	SensorMonitor* Monitor = static_cast<SensorMonitor*>(SensorMonitorInstance);

	while (1)
	{
		unsigned int CurSeconds;
		for (int i = 0; i < Monitor->m_NumSensors; i++)
		{
#ifdef DEBUG_MONITOR
			printf("Checking sensor at index: %i\n", i);
#endif
			//
			// First check for registration timeouts
			//
			bool ThreadReset = false;
			pthread_mutex_lock(&Monitor->m_SensorDataMutex);
			if (!Monitor->m_SensorData[i].Registered() && Monitor->m_SensorData[i].StartTime() != SECONDS_INIT_VAL)
			{
				// Check for a registration timeout
            CurSeconds = GetCurSeconds();
				if (CurSeconds > (Monitor->m_SensorData[i].StartTime() + TIMEOUT_INTERVAL))
				{
#ifdef DEBUG_MONITOR
					printf("Sensor registration timeout, restarting.\n");
#endif
					// Registration has timed out
					ThreadReset = true;

					Monitor->m_Sensors[i].CancelSensor(false);
					Monitor->m_Sensors[i].StartUSBMonitor(i, Monitor);
				}
			}
			pthread_mutex_unlock(&Monitor->m_SensorDataMutex);

			//
			// If no reset, make sure the sensor is still connected
			//
			pthread_mutex_lock(&Monitor->m_SensorDataMutex);
			if (!ThreadReset && Monitor->m_SensorData[i].Registered())
			{
#ifdef DEBUG_MONITOR
				printf("Checking connection...\n");
#endif
				if (!Monitor->m_Sensors[i].CheckConnection())
				{
#ifdef DEBUG_MONITOR
					printf("Sensor disconnect, restarting.\n");
#endif
					Monitor->m_Sensors[i].CancelSensor(true);
					Monitor->m_SensorData[i].Registered(false);
					Monitor->m_Sensors[i].StartUSBMonitor(i, Monitor);
				}
			}
			pthread_mutex_unlock(&Monitor->m_SensorDataMutex);


			//
			// Check for sensors who have not been acked after SDMHello msgs have been sent
			//
			pthread_mutex_lock(&Monitor->m_SensorDataMutex);
			if (Monitor->m_SensorData[i].Registered() && !Monitor->m_SensorData[i].Acked())
			{
			   CurSeconds = GetCurSeconds();
				// Check for a hello-ack timeout
				if (Monitor->m_SensorData[i].CheckAckTimeout(CurSeconds))
				{
#ifdef DEBUG_MONITOR
					printf("SDMAck not received after SDMHello, resending Hello for sensorIndex: %i.\n", i);
#endif
					SDMHello helloMsg;
					helloMsg.type = 'D';
					helloMsg.source.setPort(PORT_SM);
					helloMsg.source.setSensorID(i);
					helloMsg.Send();
				}
			}
			pthread_mutex_unlock(&Monitor->m_SensorDataMutex);

         //
			// Check for sensors who have been sent their xTEDS but not yet received confirmation of registration
			//
			pthread_mutex_lock(&Monitor->m_SensorDataMutex);
			if (Monitor->m_SensorData[i].Acked() && !Monitor->m_SensorData[i].RegConfirmed())
			{
			   CurSeconds = GetCurSeconds();
				// Check for a xteds-id timeout
				if (Monitor->m_SensorData[i].CheckIDTimeout(CurSeconds))
				{
#ifdef DEBUG_MONITOR
					printf("SDMID not received after SDMxTEDS, resending xTEDS for sensorIndex: %i.\n", i);
#endif
               Monitor->SendxTEDS(i);
				}
			}
			pthread_mutex_unlock(&Monitor->m_SensorDataMutex);

		}
		sleep(SENSOR_CHECK_INTERVAL);
	}
	return NULL;
}

bool SensorMonitor::SensorRegistering(int SensorNum)
{
	if (SensorNum < 0 || SensorNum >= m_NumSensors)
		return false;

	// Set the new registration start time
	pthread_mutex_lock(&m_SensorDataMutex);
	if (m_SensorData[SensorNum].Registered())
	{
		pthread_mutex_unlock(&m_SensorDataMutex);
		return true;
	}
	m_SensorData[SensorNum].SetStartTime(GetCurSeconds());
	pthread_mutex_unlock(&m_SensorDataMutex);

	return true;
}

bool SensorMonitor::SensorRegistered(int SensorNum)
{
	if (SensorNum < 0 || SensorNum >= m_NumSensors)
		return false;

	// Set the sensor as registered and reset its start time
	pthread_mutex_lock(&m_SensorDataMutex);
	m_SensorData[SensorNum].Registered(true);
	m_SensorData[SensorNum].SetStartTime(SECONDS_INIT_VAL);
	pthread_mutex_unlock(&m_SensorDataMutex);

	return true;
}

bool SensorMonitor::SensorAcked(int SensorNum)
{
	if (SensorNum < 0)
		return false;

	// Set the sensor as acked
	pthread_mutex_lock(&m_SensorDataMutex);
	if(m_SensorData[SensorNum].GetHelloTime() != 0)
	{
		m_SensorData[SensorNum].Acked(true);
	}
	pthread_mutex_unlock(&m_SensorDataMutex);

	return true;
}

bool SensorMonitor::SensorRegConfirmed(int SensorNum)
{
	if (SensorNum < 0)
		return false;

	// Set the sensor as acked
	pthread_mutex_lock(&m_SensorDataMutex);
	m_SensorData[SensorNum].RegConfirmed(true);
	pthread_mutex_unlock(&m_SensorDataMutex);

	return true;
}

unsigned int SensorMonitor::SetHelloSendTime(int SensorNum)
{
   if (SensorNum < 0)
	{
	   return 0;
	}
	// Set the time the Hello was sent
	unsigned int curSecs = GetCurSeconds();

	pthread_mutex_lock(&m_SensorDataMutex);
	m_SensorData[SensorNum].SetHelloTime(curSecs);
	pthread_mutex_unlock(&m_SensorDataMutex);

	return curSecs;
}

unsigned int SensorMonitor::SetxTEDSSendTime(int SensorNum)
{
   if (SensorNum < 0)
		return 0;

	// Set the time thge xTEDS was sent
	unsigned int curSecs = GetCurSeconds();
	pthread_mutex_lock(&m_SensorDataMutex);
	m_SensorData[SensorNum].SetxTEDSTime(curSecs);
	pthread_mutex_unlock(&m_SensorDataMutex);

	return curSecs;
}

bool SensorMonitor::SendxTEDS(int SensorNum)
{
   if (SensorNum < 0)
   {
		return false;
   }

   SDMxTEDS xTEDSMsg;
   strcpy(xTEDSMsg.xTEDS, m_Sensors[SensorNum].device_xTEDS);
   xTEDSMsg.source = m_Sensors[SensorNum].sensor_id;
   strcpy(xTEDSMsg.SPA_node, m_Sensors[SensorNum].device.USBLocation());
   xTEDSMsg.Send();
   MessageSent(&xTEDSMsg);

	// Set the time thge xTEDS was sent
	//pthread_mutex_lock(&m_SensorDataMutex);
	unsigned int sentTime = SetxTEDSSendTime(SensorNum);
	//pthread_mutex_unlock(&m_SensorDataMutex);
#ifdef DEBUG_MONITOR
   printf("xTEDS for sensor index: %i sent at: %i\n", SensorNum, sentTime);
#endif

	return true;
}

Sensor& SensorMonitor::operator [] (int Index)
{
	return m_Sensors[Index];
}

