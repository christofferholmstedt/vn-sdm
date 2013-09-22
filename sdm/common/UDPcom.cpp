// UDPcom.cpp   Cannon, UDP communications library

#include <sys/types.h>
#include <sys/socket.h>
#ifndef __VXWORKS__
#include <sys/poll.h>
#endif
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "sdmLib.h"
#include "marshall.h"
#include "UDPcom.h"

#ifdef __VXWORKS__
#include <sockLib.h>
#include <selectLib.h>
#include <endian.h>
#endif

#ifdef USE_SPACEWIRE
char zz[6];
#endif

#ifndef WIN32
#define closesocket close
#endif

struct sockaddr_in fsin;


SDMLIB_API
int UDPpassive (int port)                       // setup server passive port
{   struct sockaddr_in sin;
    int sock;
	bool allow = true;
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons (static_cast<u_int16_t>(port));
    if( (sock = socket (PF_INET, SOCK_DGRAM, 0)) < 0)
	{
#ifdef WIN32
		printf("UDPpassive::socket error %d\n", WSAGetLastError());
#endif
#ifndef WIN32
		perror("UDPpassive::socket error: ");
#endif
		return IP_SOCK_INVALID;
	}
#ifdef __VXWORKS__
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(char*)&allow,sizeof(allow));
	int bufSize = 25600;
	int sizeInt = 4;
	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&bufSize, sizeInt);
#else
	setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(const char*)&allow,sizeof(allow));
#endif
    if (bind (sock, reinterpret_cast<struct sockaddr *>(&sin),sizeof(sin)) < 0)
    {   printf("Unable to bind the socket! (port:%d)\n",port);
	perror("UDPpassive");
        closesocket(sock);
    	return IP_SOCK_INVALID;
    }

	int iRcvBufLen, optLen = sizeof(iRcvBufLen);
#ifndef __VXWORKS__
	if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&iRcvBufLen, (socklen_t*)&optLen) != -1)
#else
	if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, (char*)&iRcvBufLen, (int*)&optLen) != -1)
#endif
	
	iRcvBufLen = 64 * 1024;
#ifdef __VXWORKS__
	setsockopt(sock,(int)SOL_SOCKET,(int)SO_RCVBUF,(char*)&iRcvBufLen, sizeof(iRcvBufLen));
#else
	setsockopt(sock,(int)SOL_SOCKET,(int)SO_RCVBUF,(const char*)&iRcvBufLen, sizeof(iRcvBufLen));
#endif
    return sock;
}


SDMLIB_API
int UDPserv_recv (int sock, void *buf, size_t length)   // recv from anyone (passive server socket)
{
    socklen_t alen = sizeof(fsin);
#ifndef __VXWORKS__
    return recvfrom (sock, (char*)buf, length, 0,
		     reinterpret_cast<struct sockaddr *>(&fsin), (socklen_t*)&alen);
#else
	return recvfrom (sock, (char*)buf, length, 0,
		 reinterpret_cast<struct sockaddr *>(&fsin), (int*)&alen);
#endif
}

SDMLIB_API
int UDPserv_reply (int sock, const void *buf, size_t length) // reply to last message received on server
{
    return sendto (sock, (char*)buf, length, 0,
		   reinterpret_cast<struct sockaddr *>(&fsin), sizeof(fsin));
}
SDMLIB_API
int UDPserv_replyto (int sock, const void* buf, size_t length, const struct sockaddr_in* s) // reply to some previous message received on server
{
	struct sockaddr_in sin;
	memset(&sin,0,sizeof(sin));
	sin.sin_addr = s->sin_addr;
	sin.sin_port = static_cast<u_int16_t>(htons(s->sin_port));
	sin.sin_family = s->sin_family;
	return sendto (sock, (char*)buf, length, 0,
	reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin));
}

// send to (unconnected sock)
SDMLIB_API
int UDPsendto (const char *ipaddr, int port, const void *buf, size_t length)
{   struct sockaddr_in sin;
	int sock, status;
	memset (&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = inet_addr ((char*)ipaddr);
	sin.sin_port = htons (static_cast<u_int16_t>(port));
	sock = socket (PF_INET, SOCK_DGRAM, 0);
	status = sendto (sock, (char*)buf, length, 0,
			reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin));
    	if(status < 0)
	{
		perror("UDPsendto: ");
	}
    	closesocket (sock);
    	return status;
}

SDMLIB_API
int UDPrecvfrom (int port, void *buf, size_t length)   // recv from anyone (unconnected)
{   struct sockaddr_in sin;
    int sock, status;
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons (static_cast<u_int16_t>(port));
    sock = socket (PF_INET, SOCK_DGRAM, 0);
    if (bind (sock, reinterpret_cast<struct sockaddr *>(&sin),sizeof(sin)) < 0)
    {   perror ("UDPrecvfrom: ");
	return -1;
    }
    status = recv (sock, (char*)buf, length, 0);
    closesocket (sock);
    return status;
}


//bcast_addr must be in network byte order
SDMLIB_API
int UDPsend_broadcast(long bcast_addr, int port, const void *buf, size_t length)
{
    int result;
    int sock = -1;
    struct sockaddr_in addr;
    int bcast = 1;

    //Get a UDP socket
    sock = socket(PF_INET,SOCK_DGRAM,0);
    if (sock < 0)
    {
        perror("Unable to get socket descriptor (SDMElection or SDMDMLeader): ");
        return sock;
    }
#ifdef __VXWORKS__
	result = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char*)&bcast, sizeof(bcast));
#else
	result = setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (const char*)&bcast, sizeof(bcast));
#endif

    if (result < 0)
    {
        perror("Error in setsockopt: ");
	closesocket(sock);
        return result;
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = bcast_addr;
    addr.sin_port = htons(port);

    result = sendto(sock, (char*) buf, length, 0,
                    reinterpret_cast<struct sockaddr *>(&addr), sizeof(addr));
    if (result < 0)
    {
        perror("Unable to send broadcast message: ");
	closesocket(sock);
        return result;
    }
  //  fprintf(stderr, "UDPsend_broadcast: sent %d to tmp socket, fd %d\n", length, sock);
    closesocket(sock);
    return length;
}

static unsigned long spaceWireMask = 1;

/* NOTE: pip must be in network byte order */
SDMLIB_API
int UDPconnect (unsigned int pip, int port)         // connected UDP socket for UDPsend() & UDPrecv()
{   
    struct sockaddr_in sin;                 // pip is IP address in integer (long) form
    int sock;
    unsigned int uiSendIpAddr;
    int iSendPort;

    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    uiSendIpAddr = pip;
    iSendPort = port;

#ifdef USE_SPACEWIRE
		// Get the Spacewire netmask
		// if ( spaceWireMask == 1 )
		// {
			// char* netmaskStr = getenv("SpaceWireNetMask");
			// if ( netmaskStr != NULL)
			// {
				// spaceWireMask = inet_addr(netmaskStr);
	// #ifdef WIN32
				// if ( spaceWireMask == INADDR_NONE )
	// #else
				// if ( spaceWireMask == ()in_addr_t)(-1)) )
	// #endif
					// spaceWireMask = 0;
			// }
			// else
				// spaceWireMask = 0;
			//printf("using SpaceWireMask %08x\n",spaceWireMask);
		// }
		// if((pip&spaceWireMask)==pip)
		// If the IP address begins with 10., then forward it to the NM bridge agent on localhost
		// to be sent out the SpaceWire interface.
#ifdef __LITTLE_ENDIAN
		if((pip&0xff)== 0xa)
#else
		if((bswap_32(pip)&0xff)== 0xa)
#endif
		{

		// Warning:  this is not thread safe if multiple threads are sending messages.
		// Nor is it safe for opening multiple sockets using UDPconnect().
		// This is probably OK for testing purposes in the RST, but a more robust solution
		// should be devised if problems are suspected.
	
			zz[3] = (pip>>24)&0xff; zz[2] = (pip>>16)&0xff; zz[1] = (pip>>8)&0xff; zz[0] = pip & 0xff;
			zz[4] = ((port&0xff00)>>8); zz[5] = (port&0xff);
		//printf("UDPconnect..addr=%x, zz=%x,%x,%x,%x\n",pip,zz[0],zz[1],zz[2],zz[3]);
		uiSendIpAddr = inet_addr ("127.0.0.1");     // ipaddr is in number-dot notation
		iSendPort = 7680;
		} 
		else
		{
			zz[0]=0;
		}
#endif

    sin.sin_port = htons (static_cast<u_int16_t>(iSendPort));
    sin.sin_addr.s_addr = uiSendIpAddr;
    sock = socket (PF_INET, SOCK_DGRAM, 0);
	
	int iSndBufLen, optLen = sizeof(iSndBufLen);
	iSndBufLen = 25 * 1024;

#ifdef __VXWORKS__
	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (char*)&iSndBufLen, sizeof(iSndBufLen));
#else
	setsockopt(sock, SOL_SOCKET, SO_SNDBUF, (const char*)&iSndBufLen, sizeof(iSndBufLen));
#endif
		
    if(connect (sock, reinterpret_cast<struct sockaddr *>(&sin),sizeof(sin)) < 0)
    {
        struct in_addr in = {uiSendIpAddr};

        printf("Unable to connect to %s:%d\n",inet_ntoa(in), iSendPort);
        perror("UDPconnect");
        return IP_SOCK_INVALID;
    }
    return sock;
}

SDMLIB_API
int UDPconnect (const char *ipaddr, int port)     // connected UDP socket for UDPsend() & UDPrecv()
{
	int sock;
	in_addr_t pip = inet_addr ((char*)ipaddr);     // ipaddr is in number-dot notation
	sock = UDPconnect (pip, port);
	if(sock == IP_SOCK_INVALID)
	{
		printf("Failed to connect to %s:%d\n",ipaddr,port);
	}
	return sock;
}

SDMLIB_API
int UDPsend (int sock, const void *buf, size_t length)   // use with connected UDP socket
{   
#ifdef USE_SPACEWIRE
	//
	// SPA-S specific code -- If this socket is associated with a SpaceWire bus address,
	// then send the message to the local NM bridge agent.
	if(zz[0] != 0)
	{
		unsigned int i = length;	
		i += 6;
		char* buf1 = (char*)malloc(i);
		memcpy(buf1,zz,6); memcpy(&buf1[6],buf,i-6);
		int result = send(sock,buf1,i,0);
		//printf("UDPSend..result=%x,error=%d\n",result,WSAGetLastError());
		free(buf1);
		return result;
	}
	//
	// End Spacewire specific code
#endif
	int sendResult = send (sock, (char*)buf, length, 0);
	return sendResult;
}

SDMLIB_API
int UDPrecv (int sock, void *buf, size_t length) // use with connected UDP socket
{   return recv (sock, (char*)buf, length, 0);
}

SDMLIB_API
void UDPgetip (struct sockaddr_in *p)
{
    p->sin_addr = fsin.sin_addr;
    p->sin_port = ntohs(static_cast<u_int16_t>(fsin.sin_port));
	p->sin_family = fsin.sin_family;
}

/* NOTE: timeout is in milliseconds */
SDMLIB_API
int UDPavail (int sock, int timeout)
{
#ifndef __VXWORKS__
	struct pollfd ufd;	
	ufd.fd = sock;
	ufd.events = POLLIN | POLLPRI;
    return poll(&ufd, 1U, timeout) > 0;
#else
	struct fd_set fds;
	FD_SET(sock, &fds);
	timeval timeoutVal;
	timeoutVal.tv_usec = timeout;
	return (select(sock + 1, &fds, NULL, NULL, &timeoutVal) > 0);
#endif
}

/* NOTE: timeout is in milliseconds */
SDMLIB_API
int UDPset_recv_timeout (int sock, int timeout)
{
    int result;

#ifdef WIN32
    // timeout is already in milliseconds
    result = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
#else
    struct timeval time;
    time.tv_sec  = timeout / 1000;
    time.tv_usec = (timeout % 1000) * 1000;    
    result = setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char*)&time, sizeof(time));
#endif
    
    return result;
}

SDMLIB_API
int UDPshutdown (int sock)
{
#ifndef WIN32
    return shutdown(sock, SHUT_RDWR);
#else
    return shutdown(sock, SD_BOTH);
#endif
}

SDMLIB_API
int UDPclose (int sock)
{
    return closesocket(sock);
}
