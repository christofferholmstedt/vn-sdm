#include "SensorRecord.h"

SensorRecord::SensorRecord() : m_Registered(false), m_SecondsStart(SECONDS_INIT_VAL), ackReceived(false), regConfirmed(false), helloSentTime(SECONDS_INIT_VAL), xTEDSSentTime(SECONDS_INIT_VAL)
{}

SensorRecord::~SensorRecord()
{}

bool SensorRecord::HasExpired(unsigned int CurSeconds)
{
	if (CurSeconds == SECONDS_INIT_VAL)
		return false;

	return CurSeconds > m_SecondsStart ? true : false;
}

bool SensorRecord::CheckAckTimeout(unsigned int curSeconds)
{
   if(curSeconds == SECONDS_INIT_VAL)
   {
      return false;
   }
   else if(curSeconds > helloSentTime + SENSOR_ACK_TIMEOUT)
   {
      return true;
   }
   else
   {
      return false;
   }
}


bool SensorRecord::CheckIDTimeout(unsigned int curSeconds)
{
   if(curSeconds == SECONDS_INIT_VAL)
   {
      return false;
   }
   else if(curSeconds > xTEDSSentTime + SENSOR_ID_TIMEOUT)
   {
      return true;
   }
   else
   {
      return false;
   }
}

