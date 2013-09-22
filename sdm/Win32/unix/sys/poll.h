#ifndef __sys_poll_h_
#define __sys_poll_h_

#include "sdmLib.h"
#include <winsock2.h>

#define POLLIN		0x0001 // Data other than high priority data may be read without blocking.

#define POLLOUT		0x0002 // Data may be written without blocking.

#define POLLPRI		0x0004 // High priority data may be read without blocking.

#define POLLRDNORM	0x0008 // Normal data may be read without blocking.

#define POLLRDBAND	0x0010 // Data with a non-zero priority may be read without blocking.

#define POLLWRNORM	0x0020 // Normal data may be written without blocking.

#define POLLWRBAND	0x0040 // Data with a non-zero priority may be written without blocking.

#define POLLERR		0x0080 // An exceptional condition has occurred on the device or socket.  This flag
						   // is always checked, even if not present in the events bitmask.

#define POLLHUP		0x0100 // The device or socket has been disconnected.  This flag is always checked,
						   // even if not present in the events bitmask.  Note that POLLHUP and POLLOUT
						   // should never be present in the revents bitmask at the same time.  If the
						   // remote end of a socket is closed, poll() returns a POLLIN event, rather than
						   // a POLLHUP.

#define POLLNVAL	0x0200 // The file descriptor is not open.  This flag is always checked, even if not
						   // present in the events bitmask.
#if(_WIN32_WINNT < 0x0501)
struct pollfd
{
	int fd;
	short events;
	short revents;
};
#else

#endif
extern int SDMLIB_API poll(struct pollfd* fd, unsigned int resv, int timeout);

#endif // __sys_poll_h_
