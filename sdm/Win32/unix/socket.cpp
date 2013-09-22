#include <sys/socket.h>
#include <stdio.h>
#include "sdmLib.h"

int setsockopt( int socket, unsigned int level, unsigned int option, void* value, size_t valueSize )
{
	return setsockopt(socket, level, option, (const char*)value, (int)valueSize );
}
