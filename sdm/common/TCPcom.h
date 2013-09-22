#ifndef __TCPCOM_H_
#define __TCPCOM_H_

#include <sys/types.h>

#include "sdmLib.h"

//  TCPcom.h  TCP com library header

#ifndef IP_SOCK_INVALID
#define IP_SOCK_INVALID (-1)   // must match the definition in UDPcom.h
#endif
#ifndef TCP_RECV_SHUTDOWN
#define TCP_RECV_SHUTDOWN	0	//Returned from recvfrom when a socket has been shutdown
#endif

extern int SDMLIB_API TCPpassive (int port, int maxConn);                       // setup server passive port

extern int SDMLIB_API TCPaccept (int sock, struct sockaddr_in *sin);        // accept a connection

extern int SDMLIB_API TCPserv_accept (int sock);                            // accept a connection

extern int SDMLIB_API TCPserv_recv (int sock, void *buf, size_t length);   // recv from anyone (server passive socket)

extern int SDMLIB_API TCPserv_reply (int sock, const void *buf, size_t length); // reply to last message received on server

extern int SDMLIB_API TCPserv_replyto (int sock, const void* buf, size_t length, const struct sockaddr_in* s); // reply to some previous message recieved on server

// send to (unconnected sock)
extern int SDMLIB_API TCPsendto (const char *ipaddr, int port, const void *buf, size_t length);

extern int SDMLIB_API TCPrecvfrom (int port, void *buf, size_t length);   // recv from anyone

extern int SDMLIB_API TCPconnect (const char *ipaddr, int port);     // connected TCP socket for TCPsend() & TCPrecv()
extern int SDMLIB_API TCPconnect (unsigned int pip, int port);

extern int SDMLIB_API TCPsend (int sock, const void *buf, size_t length); // use with connected TCP socket

extern int SDMLIB_API TCPrecv (int sock, void *buf, size_t length); // use with connected TCP socket

extern void SDMLIB_API TCPgetip (struct sockaddr_in *p);	// get the ip of socket currently connected

extern int SDMLIB_API TCPavail (int sock, int timeout = 0); // return nonzero if a message is
					  // waiting on sock; wait for up to
					  // timeout  milliseconds for a
					  // message to arrive

extern int SDMLIB_API TCPshutdown(int sock);

extern int SDMLIB_API TCPclose(int sock);

#endif
