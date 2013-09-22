#ifndef __netinet_in_h_
#define __netinet_in_h_

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

typedef unsigned int in_addr_t;

#endif // __netinet_in_h_
