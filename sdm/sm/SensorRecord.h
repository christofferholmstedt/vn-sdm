#ifndef _SENSOR_RECORD_H_
#define _SENSOR_RECORD_H_

const unsigned int SECONDS_INIT_VAL = 0;
const int SENSOR_ACK_TIMEOUT = 10;
const int SENSOR_ID_TIMEOUT = 15;

class SensorRecord
{
public:
	SensorRecord();
	~SensorRecord();

	void Registered(bool NewRegistered) { m_Registered = NewRegistered; }
	bool Registered() { return m_Registered; }

	void SetStartTime(unsigned int Seconds) { m_SecondsStart = Seconds; }
	unsigned int StartTime() { return m_SecondsStart; }

	void SetHelloTime(unsigned int seconds) { helloSentTime = seconds; }
	unsigned int GetHelloTime() { return helloSentTime; }
	void SetxTEDSTime(unsigned int seconds) { xTEDSSentTime = seconds; }

	void Acked(bool acked) { ackReceived = acked; }
	bool Acked() { return ackReceived; }
	void RegConfirmed(bool regConf) { regConfirmed = regConf; }
	bool RegConfirmed() { return regConfirmed; }

	bool HasExpired(unsigned int CurSeconds);

	bool CheckAckTimeout(unsigned int curSeconds);
	bool CheckIDTimeout(unsigned int curSeconds);


private:
	bool m_Registered;
	unsigned int m_SecondsStart;
	unsigned int helloSentTime;
	unsigned int xTEDSSentTime;
   bool ackReceived;
	bool regConfirmed;
};

#endif

