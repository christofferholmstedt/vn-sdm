#ifndef __UDPCOM_H_
#define __UDPCOM_H_

#include <sys/types.h>

#include "sdmLib.h"

//  UDPcom.h  UDP com library header

#ifndef IP_SOCK_INVALID
#define IP_SOCK_INVALID (-1)   // must match the definition in TCPcom.h
#endif
#ifndef UDP_SERV_RECV_SHUTDOWN
#define UDP_SERV_RECV_SHUTDOWN	0	//Returned from recvfrom when a socket has been shutdown
#endif

extern int SDMLIB_API UDPpassive (int port);                       // setup server passive port

extern int SDMLIB_API UDPserv_recv (int sock, void *buf, size_t length);   // recv from anyone (server passive socket)

extern int SDMLIB_API UDPserv_reply (int sock, const void *buf, size_t length); // reply to last message received on server

extern int SDMLIB_API UDPserv_replyto (int sock, const void* buf, size_t length, const struct sockaddr_in* s); // reply to some previous message recieved on server

// send to (unconnected sock)
extern int SDMLIB_API UDPsendto (const char *ipaddr, int port, const void *buf, size_t length);

extern int SDMLIB_API UDPrecvfrom (int port, void *buf, size_t length);   // recv from anyone

extern int SDMLIB_API UDPsend_broadcast(long bcast_addr, int port, const void *buf, size_t length);

extern int SDMLIB_API UDPconnect (const char *ipaddr, int port);     // connected UDP socket for UDPsend() & UDPrecv()
extern int SDMLIB_API UDPconnect (unsigned int pip, int port);

extern int SDMLIB_API UDPsend (int sock, const void *buf, size_t length); // use with connected UDP socket

extern int SDMLIB_API UDPrecv (int sock, void *buf, size_t length); // use with connected UDP socket

extern void SDMLIB_API UDPgetip (struct sockaddr_in *p);	// get the ip of socket currently connected

extern int SDMLIB_API UDPavail (int sock, int timeout = 0); // return nonzero if a message is
					  // waiting on sock; wait for up to
					  // timeout  milliseconds for a
					  // message to arrive

extern int SDMLIB_API UDPset_recv_timeout(int sock, int timeout);

extern int SDMLIB_API UDPshutdown(int sock);

extern int SDMLIB_API UDPclose(int sock);

#endif
