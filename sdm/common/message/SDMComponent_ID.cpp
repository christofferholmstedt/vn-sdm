#include "SDMComponent_ID.h"
#include "../marshall.h"

#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

SDMComponent_ID::SDMComponent_ID() : m_ulSensorId(0), m_ulAddress(0), m_usPort(0)
{
}

SDMComponent_ID::SDMComponent_ID(const SDMComponent_ID& b) : m_ulSensorId(b.m_ulSensorId), m_ulAddress(b.m_ulAddress), m_usPort(b.m_usPort)
{
}

SDMComponent_ID::~SDMComponent_ID()
{
}

SDMComponent_ID& SDMComponent_ID::operator=(const SDMComponent_ID& b)
{
	m_ulSensorId = b.m_ulSensorId;
	m_ulAddress = b.m_ulAddress;
	m_usPort = b.m_usPort;
	return *this;
}

bool SDMComponent_ID::operator==(const SDMComponent_ID& b) const
{
	if(m_ulSensorId == b.m_ulSensorId)
	{
		if(m_ulAddress == b.m_ulAddress)
		{
			if(m_usPort == b.m_usPort)
			{
				return true;
			}
		}
	}
	return false;
}

int SDMComponent_ID::Marshal(char* buf, int start) const
{
	int cur = 0;

	// Marshal the address.  On either little or big endian archs, m_ulAddress is always in
	// network byte order (big endian), so perform a swap and copy the result into the message
	// buffer using SDM message byte order (little endian).
	unsigned long ulSwappedAddr = bswap_32(m_ulAddress);	// Ip address in little-endian
	*reinterpret_cast<unsigned long* >(&buf[start]) = ulSwappedAddr;
	
	cur += sizeof(ulSwappedAddr);
	PUT_USHORT(&buf[start+cur],m_usPort);
	cur += sizeof(m_usPort);
	PUT_ULONG(&buf[start+cur],m_ulSensorId);
	cur += sizeof(m_ulSensorId);
	return cur;
}

int SDMComponent_ID::Unmarshal(const char* buf, int start)
{
	int cur = 0;
	
	// Unmarshal the address.  On either little or big endian archs, the address in the buffer is
	// in SDM message byte order (little endian), m_ulAddress is to be maintained in network byte
	// order (big endian), so it must be swapped identically for each target.
	unsigned long ulSwappedAddr = static_cast<unsigned long>(*reinterpret_cast<const unsigned long* >(&buf[start]));
	m_ulAddress = bswap_32(ulSwappedAddr);
	
	cur += sizeof(m_ulAddress);
	m_usPort = GET_USHORT(&buf[start+cur]);
	cur += sizeof(m_usPort);
	m_ulSensorId = GET_ULONG(&buf[start+cur]);
	cur += sizeof(m_ulSensorId);
	return cur;
}

/*
NOW INLINE
void SDMComponent_ID::setSensorID(unsigned long new_sensor_id)
{
	m_ulSensorId = new_sensor_id;
}

void SDMComponent_ID::setAddress(unsigned long new_address)
{
	m_ulAddress = new_address;
	BigEndian = true;
}

void SDMComponent_ID::setPort(unsigned short new_port)
{
	m_usPort = new_port;
}

unsigned long SDMComponent_ID::getSensorID() const
{
	return m_ulSensorId;
}

unsigned long SDMComponent_ID::getAddress() const
{
	return m_ulAddress;
}

unsigned short SDMComponent_ID::getPort() const
{
	return m_usPort;
}*/

bool SDMComponent_ID::isEmpty() const
{
	bool result = false;

	if(m_ulSensorId == 0)
	{
		if(m_ulAddress == 0)
		{
			if(m_usPort == 0)
			{
				result = true;
			}
		}
	}
	return result;
}

/*
 *	IDToString() puts the component id into human readable form for debug purposes.
 * 	The length parameter and size of the buffer should be at least 36
 */
int SDMComponent_ID::IDToString(char *buf, int length) const
{
	if (length < 36)
		return 0;
	struct in_addr address;
	address.s_addr = m_ulAddress;
#ifdef WIN32
	sprintf(buf, "%s:%d SID=%ld",inet_ntoa(address), m_usPort, m_ulSensorId);
#else
	snprintf(buf, length,"%s:%d SID=%ld",inet_ntoa(address), m_usPort, m_ulSensorId);
#endif
	return (int)strlen(buf);
}
