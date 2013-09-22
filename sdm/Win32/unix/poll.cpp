#include "sys/poll.h"
#include <stdio.h>
#include <unistd.h>
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>
#include "sdmLib.h"


SDMLIB_API int poll(struct pollfd* fds, unsigned int nfds, int timeout)
{
	int num = 0;
	u_long len;

	for( unsigned int i=0; i<nfds; i++ )
	{
		if ( fds[i].events & (POLLIN|POLLPRI) )
		{
			len = 0;
			ioctlsocket(fds[i].fd,FIONREAD, &len );
			if ( len > 0 )
				num++;
		}
	}
	if ( num == 0 && timeout != 0 && timeout != INFINITE )
		usleep(timeout*1000);
	else
		return num;
	for( unsigned int i=0; i<nfds; i++ )
	{
		if ( fds[i].events & (POLLIN|POLLPRI) )
		{
			len = 0;
			ioctlsocket(fds[i].fd,FIONREAD, &len );
			if ( len > 0 )
				num++;
		}
	}
	return num;
}
