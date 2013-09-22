#include <string.h>
#include <stdio.h>
#include "SDMComHandle.h"
#include "TCPcom.h"

void CopySockAddrIn(struct sockaddr_in* Target, const struct sockaddr_in* Source)
{
	memset(Target, 0, sizeof(struct sockaddr_in));
	if (Source != NULL)
	{
		Target->sin_family = Source->sin_family;
		Target->sin_port = Source->sin_port;
		Target->sin_addr.s_addr = Source->sin_addr.s_addr;
	}
}

SDMComHandle::SDMComHandle() : m_iSock(IP_SOCK_INVALID), m_bIsTcp(false), m_sinAddress()
{
	memset(&m_sinAddress, 0, sizeof(struct sockaddr_in));
}

// Destructor does not cleanup the com handle, this should be called specifically when the client
// is finished using it
SDMComHandle::~SDMComHandle()
{
}

SDMComHandle::SDMComHandle(int Sock, bool TCP, const sockaddr_in* Address) : m_iSock(Sock), m_bIsTcp(TCP), m_sinAddress()
{
	CopySockAddrIn(&m_sinAddress, Address);
}

SDMComHandle::SDMComHandle(const SDMComHandle& right) : m_iSock(right.m_iSock), m_bIsTcp(right.m_bIsTcp), m_sinAddress()
{
	CopySockAddrIn(&m_sinAddress, &right.m_sinAddress);
}

SDMComHandle& SDMComHandle::operator=(const SDMComHandle& right)
{
	m_iSock = right.m_iSock;
	m_bIsTcp = right.m_bIsTcp;
	CopySockAddrIn(&m_sinAddress, &right.m_sinAddress);
	
	return *this;
}

void SDMComHandle::Set(int Sock, bool Tcp, const sockaddr_in* Address)
{
	m_iSock = Sock;
	m_bIsTcp = Tcp;
	CopySockAddrIn(&m_sinAddress, Address);
}

void SDMComHandle::DoCleanup()
{
	// Only close the ComHandle for TCP sockets
	if (m_bIsTcp && m_iSock != IP_SOCK_INVALID)
	{
		TCPclose(m_iSock);
		m_iSock = IP_SOCK_INVALID;
		m_bIsTcp = false;
	}
}
