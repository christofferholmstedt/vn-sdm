#ifndef _SDM_COM_HANDLE_H_
#define _SDM_COM_HANDLE_H_

#include <netinet/in.h>
#include "UDPcom.h"
#include "sdmLib.h"

class SDMLIB_API SDMComHandle
{
public:
	SDMComHandle();
	SDMComHandle(int Sock, bool TCP, const sockaddr_in* Address);
	SDMComHandle(const SDMComHandle& right);
	SDMComHandle& operator=(const SDMComHandle& right);
	~SDMComHandle();
	
	int GetSock () const { return m_iSock; }
	bool IsValidHandle() const { return m_iSock != IP_SOCK_INVALID; }
	bool IsTcp() const { return m_bIsTcp; }
	const struct sockaddr_in* GetAddress() const { return &m_sinAddress; }
	int GetPort() const { return m_sinAddress.sin_port; }
	void Set(int Sock, bool TCP, const sockaddr_in* Address);
	void DoCleanup();
private:
	int m_iSock;
	bool m_bIsTcp;
	struct sockaddr_in m_sinAddress;
};

static const SDMComHandle COM_HANDLE_INVALID;

#endif
