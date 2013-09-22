// TCPcom.cpp   TCP communications library

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
#include <errno.h>
#include "sdmLib.h"
#include "TCPcom.h"

#ifdef __VXWORKS__
#include <sockLib.h>
#include <selectLib.h>
#endif

#ifndef WIN32
#define closesocket close
#endif

struct sockaddr_in TCP_fsin;

SDMLIB_API
int TCPpassive (int port, int maxConn)          // setup server passive port
{   struct sockaddr_in sin;
    int sock;
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons (static_cast<u_int16_t>(port));
    sock = socket (PF_INET, SOCK_STREAM, 0);
    const int one = 1;
#ifdef __VXWORKS__
	if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char*)&one, sizeof(int)) == -1)
#else
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (void*)&one, sizeof(int)) == -1)
#endif
    {
	    perror("TCPpassive: setsockopt");
    }
    if (bind (sock, reinterpret_cast<struct sockaddr *>(&sin),sizeof(sin)) < 0)
    {   printf("Unable to bind the socket! (port:%d)\n",port);
	perror("TCPpassive: bind");
        closesocket(sock);
        return IP_SOCK_INVALID;
    }
    if (listen(sock, maxConn) < 0) {
        perror("TCPPassive: listen");
        closesocket(sock);
        return IP_SOCK_INVALID;
    }
    return sock;
}

SDMLIB_API
int TCPaccept (int sock, struct sockaddr_in *sin)
{
	socklen_t alen = sizeof(struct sockaddr_in);
#ifndef __VXWORKS__
    int sock2 = accept (sock, reinterpret_cast<struct sockaddr *>(sin), (socklen_t*)&alen);
#else
	int sock2 = accept (sock, reinterpret_cast<struct sockaddr *>(sin), (int*)&alen);
#endif   
	if (sock2 < 0) {
	//If the sock is invalid, it may have been shutdown prior to an accept, but the thread is live
        if (errno != EINVAL)
		perror("TCPserv_accept");
        return IP_SOCK_INVALID;
    }
    return sock2;
}

SDMLIB_API
int TCPserv_accept (int sock)
{
	return TCPaccept(sock, &TCP_fsin);
}

SDMLIB_API
int TCPserv_recv (int sock, void *buf, size_t length)   // recv from anyone (passive server socket)
{
    socklen_t alen = sizeof(TCP_fsin);
#ifndef __VXWORKS__
    return recvfrom (sock, (char*)buf, length, 0,
		     reinterpret_cast<struct sockaddr *>(&TCP_fsin), (socklen_t*)&alen);
#else
	return recvfrom (sock, (char*)buf, length, 0,
			 reinterpret_cast<struct sockaddr *>(&TCP_fsin), (int*)&alen);
#endif
}

SDMLIB_API
int TCPserv_reply (int sock, const void *buf, size_t length) // reply to last message received on server
{
    return sendto (sock, (char*)buf, length, 0,
		   reinterpret_cast<struct sockaddr *>(&TCP_fsin), sizeof(TCP_fsin));
}

SDMLIB_API
int TCPserv_replyto (int sock, const void* buf, size_t length, const struct sockaddr_in* s) // reply to some previous message received on server
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
int TCPsendto (const char *ipaddr, int port, const void *buf, size_t length)
{   struct sockaddr_in sin;
    int sock, status;
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr ((char*)ipaddr);
    sin.sin_port = htons (static_cast<u_int16_t>(port));
    sock = socket (PF_INET, SOCK_STREAM, 0);
    status = sendto (sock, (char*)buf, length, 0,
		     reinterpret_cast<struct sockaddr *>(&sin), sizeof(sin));
    closesocket (sock);
    return status;
}

SDMLIB_API
int TCPrecvfrom (int port, void *buf, size_t length)   // recv from anyone (unconnected)
{   struct sockaddr_in sin;
    int sock, status;
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = INADDR_ANY;
    sin.sin_port = htons (static_cast<u_int16_t>(port));
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if (bind (sock, reinterpret_cast<struct sockaddr *>(&sin),sizeof(sin)) < 0)
    {   perror ("TCPrecvfrom: ");
	return -1;
    }
    status = recv (sock, (char*)buf, length, 0);
    closesocket (sock);
    return status;
}

/* NOTE: pip must be in network byte order */
SDMLIB_API
int TCPconnect (unsigned int pip, int port)         // connected TCP socket for TCPsend() & TCPrecv()
{   struct sockaddr_in sin;                 // pip is IP address in integer (long) form
    int sock;
    memset (&sin, 0, sizeof(sin));
    sin.sin_family = AF_INET;
    sin.sin_port = htons (static_cast<u_int16_t>(port));
    sin.sin_addr.s_addr = pip;
    sock = socket (PF_INET, SOCK_STREAM, 0);
    if(connect (sock, reinterpret_cast<struct sockaddr *>(&sin),sizeof(sin)) < 0)
    {
		struct in_addr in = {pip};

		printf("Unable to connect to %s:%d\n",inet_ntoa(in),port);
		perror("TCPconnect");
    	return IP_SOCK_INVALID;
    }
    return sock;
}

SDMLIB_API
int TCPconnect (const char *ipaddr, int port)     // connected TCP socket for TCPsend() & TCPrecv()
{
	int sock;
	in_addr_t pip = inet_addr ((char*)ipaddr);     // ipaddr is in number-dot notation
	sock = TCPconnect (pip, port);
	if(sock == IP_SOCK_INVALID)
	{
		printf("Failed to connect to %s:%d\n",ipaddr,port);
	}
	return sock;
}

SDMLIB_API
int TCPsend (int sock, const void *buf, size_t length)   // use with connected TCP socket
{   return send (sock, (char*)buf, length, 0);
}

SDMLIB_API
int TCPrecv (int sock, void *buf, size_t length) // use with connected TCP socket
{
	int iReturn = 0;
	bool bTryAgain = false;
	int iAttemptCount = 0;
	const int MAX_ATTEMPTS = 5;
	do
	{
		bTryAgain = false;
		iReturn = recv (sock, (char*)buf, length, 0);
		if (iReturn == -1)
		{
			if (errno == EINTR)
			{
				bTryAgain = true;
				if (++iAttemptCount >= MAX_ATTEMPTS)
					bTryAgain = false;
			}
		}
	} while (bTryAgain);

	return iReturn;
}

SDMLIB_API
void TCPgetip (struct sockaddr_in *p)
{
    p->sin_addr = TCP_fsin.sin_addr;
    p->sin_port = ntohs(static_cast<u_int16_t>(TCP_fsin.sin_port));
	p->sin_family = TCP_fsin.sin_family;
}

/* NOTE: timeout is in milliseconds */
SDMLIB_API
int TCPavail (int sock, int timeout)
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
	timeoutVal.tv_sec = timeout;
	return (select(sock + 1, &fds, NULL, NULL, &timeoutVal) > 0);
#endif
}

SDMLIB_API
int TCPshutdown (int sock)
{
#ifndef WIN32
    return shutdown(sock, SHUT_RDWR);
#else
    return shutdown(sock, SD_BOTH);
#endif
}

SDMLIB_API
int TCPclose (int sock)
{
    return closesocket(sock);
}
