#ifndef __arpa_inet_h_
#define __arpa_inet_h_

#include <unistd.h>
//#include <stdio.h>

#ifdef _WIN32

#ifndef BYTE
#define BYTE wBYTE
#define CHAR wCHAR
#define FLOAT wFLOAT
#define LONG wLONG
#endif

#define WIN32_LEAN_AND_MEAN
#include "winsock2.h"

#ifdef BYTE
#undef BYTE
#undef CHAR
#undef FLOAT
#undef LONG
#endif

#endif

#define SOCK_STREAM 1


typedef int socklen_t;

extern int setsockopt( int socket, unsigned int level, unsigned int option, void* value, size_t valueSize );

#endif // __arpa_inet_h_
