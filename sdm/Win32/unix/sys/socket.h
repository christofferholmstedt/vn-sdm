#ifndef __sys_socket_h_
#define __sys_socket_h_

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

extern int setsockopt( int socket, unsigned int level, unsigned int option, void* value, size_t valueSize );

#endif // __sys_socket_h_
