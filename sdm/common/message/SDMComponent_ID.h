#ifndef __SDM_COMPONENT_ID_H_
#define __SDM_COMPONENT_ID_H_
#include <arpa/inet.h>

#include "../sdmLib.h"

const unsigned long ADDR_LOCAL_HOST = inet_addr("127.0.0.1");

class SDMLIB_API SDMComponent_ID
{
public:
	SDMComponent_ID();
	SDMComponent_ID(const SDMComponent_ID&);
	~SDMComponent_ID();

	SDMComponent_ID& operator=(const SDMComponent_ID&);
	bool operator==(const SDMComponent_ID&) const;

	int Marshal(char* buf, int start) const;
	int Unmarshal(const char* buf, int start);

	void setSensorID(unsigned long new_sensor_id) { m_ulSensorId = new_sensor_id; }
	void setAddress(unsigned long new_address) { m_ulAddress = new_address; }
	void setPort(unsigned short new_port) { m_usPort = new_port; }
	int IDToString(char *buf, int length) const;

	unsigned long getSensorID() const { return m_ulSensorId; }
	unsigned long getAddress() const { return m_ulAddress; }
	unsigned short getPort() const { return m_usPort; }

	bool isEmpty() const;

private:
	unsigned long m_ulSensorId;	//The sensor_id assigned by the Data Manager or your local id
	unsigned long m_ulAddress;		//The ip address of the node the device or application is running on
	unsigned short m_usPort;		//The port that is being listened on for incoming messages
};

static const SDMComponent_ID COMPONENT_ID_INVALID;

#endif
