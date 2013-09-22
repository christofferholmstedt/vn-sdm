#ifndef __unix_fcntl_h_
#define __unix_fcntl_h_

#include <fcntl.h>

// Values for cmd used by fcntl() (the following values are unique) are as follows:

#define F_DUPFD		1	// Duplicate file descriptor.
#define F_GETFD		2	// Get file descriptor flags.
#define F_SETFD		3	// Set file descriptor flags.
#define F_GETFL		4	// Get file status flags and file access modes.
#define F_SETFL		5	// Set file status flags.
#define F_GETLK		6	// Get record locking information.
#define F_SETLK		7	// Set record locking information.
#define F_SETLKW	8	// Set record locking information; wait if blocked.
#define F_GETOWN	9	// Get process or process group ID to receive SIGURG signals.
#define F_SETOWN	10	// Set process or process group ID to receive SIGURG signals.

// File descriptor flags used for fcntl() are as follows:

#define FD_CLOEXEC	11	// Close the file descriptor upon execution of an exec family function.

// Values for l_type used for record locking with fcntl() (the following values are unique) are as follows:

#define F_RDLCK		12	// Shared or read lock.
#define F_UNLCK		13	// Unlock.
#define F_WRLCK		14	// Exclusive or write lock.

// The values used for l_whence, SEEK_SET, SEEK_CUR, and SEEK_END shall be defined as described in <unistd.h>.

// The following values are file creation flags and are used in the oflag value to open(). They shall be bitwise-distinct.

//#define O_CREAT		0x0100	// Create file if it does not exist.
//#define O_EXCL		0x0400	// Exclusive use flag.
#define O_NOCTTY	0x0004	// Do not assign controlling terminal.
//#define O_TRUNC		0x0200	// Truncate flag.

// File status flags used for open() and fcntl() are as follows:

//#define O_APPEND	0x0008	// Set append mode.
#define O_DSYNC		0x0040	// [SIO]  Write according to synchronized I/O data integrity completion.
#define O_NONBLOCK	0x0080	// Non-blocking mode.
#define O_RSYNC		0x0800	// [SIO]  Synchronized read I/O operations.
#define O_SYNC		0x1000	// Write according to synchronized I/O file integrity completion.

// Mask for use with file access modes is as follows:

#define O_ACCMODE	0x0001	// Mask for file access modes.

// File access modes used for open() and fcntl() are as follows:

//#define O_RDONLY	0x0000	// Open for reading only.
//#define O_RDWR		0x0002	// Open for reading and writing.
//#define O_WRONLY	0x0001	// Open for writing only.
// [XSI]  The symbolic names for file modes for use as values of mode_t shall be defined as described in <sys/stat.h>.

// [ADV]  Values for advice used by posix_fadvise() are as follows:

#define POSIX_FADV_NORMAL		1	// The application has no advice to give on its behavior with respect to the specified data. It is the default characteristic if no advice is given for an open file.
#define POSIX_FADV_SEQUENTIAL	2	// The application expects to access the specified data sequentially from lower offsets to higher offsets.
#define POSIX_FADV_RANDOM		3	// The application expects to access the specified data in a random order.
#define POSIX_FADV_WILLNEED		4	// The application expects to access the specified data in the near future.
#define POSIX_FADV_DONTNEED		5	// The application expects that it will not access the specified data in the near future.
#define POSIX_FADV_NOREUSE		6	// The application expects to access the specified data once and then not reuse it thereafter.

#endif __unix_fcntl_h_

