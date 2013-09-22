#ifndef __sys_wait_h_
#define __sys_wait_h_

#include <unistd.h>

#define SIGCHLD 33
#include <signal.h>
// The siginfo_t type shall be defined as described in <signal.h> .
union sigval {
	int sival_int;
	void *sival_ptr;
};

typedef struct {
	int si_signo;
	int si_code;
	union sigval si_value;
	int si_errno;
	pid_t si_pid;
	uid_t si_uid;
	void *si_addr;
	int si_status;
	int si_band;
} siginfo_t;


//#include <sys/resource.h>
//The rusage structure shall be defined as described in .
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

struct rusage
{
	struct timeval ru_utime;        /* user time used    */
	struct timeval ru_stime;        /* system time used  */
};

//#define WNOHANG			1 // Do not hang if no status is available; return immediately.
#define WUNTRACED		2 // Report status of stopped child process.
#define WEXITSTATUS		3 // Return exit status.
#define WIFCONTINUED	4 // True if child has been continued.
#define WIFEXITED		5 // True if child exited normally.
#define WIFSIGNALED		6 // True if child exited due to uncaught signal.
#define WIFSTOPPED		7 // True if child is currently stopped.
#define WSTOPSIG		8 // Return signal number that caused process to stop.
#define WTERMSIG		9 // Return signal number that caused process to terminate.
#define WEXITED			10 // Wait for processes that have exited.
#define WSTOPPED		11 // Status is returned for any child that has stopped upon receipt of a signal.
#define WCONTINUED		12 // Status is returned for any child that was stopped and has been continued.
#define WNOHANG			13 // Return immediately if there are no children to wait for.
#define WNOWAIT			14 // Keep the process whose status is returned in infop in a waitable state.

typedef enum { P_ALL, P_PID, P_PGID } idtype_t;
typedef unsigned int id_t;

extern pid_t wait(int * status);

extern int waitid(idtype_t idType, id_t id, siginfo_t * info, int resv);

extern pid_t waitpid(pid_t pid, int * resv1, int resv2);

#endif // __sys_wait_h_
