#ifndef __sys_sem_h_
#define __sys_sem_h_

#include <unistd.h>
#include <time.h>

#define SEM_OP_BLOCK	-1
#define SEM_OP_ADD		1

struct sembuf
{
	unsigned short sem_num;
	short  sem_op;
	short  sem_flg;
};
union semun
{
	int val;				// value for SETVAL
	struct semid_ds *buf;   // buffer for IPC_STAT & IPC_SET
	unsigned short *array;  // array for GETALL & SETALL
	struct seminfo *__buf;  // buffer for IPC_INFO
	void *__pad;
};
struct ipc_perm {
	unsigned short user;
	unsigned short group;
	unsigned short other;
};

struct semid_ds {
	struct ipc_perm sem_perm;       /* permissions .. see ipc.h */
	time_t          sem_otime;      /* last semop time */
	time_t          sem_ctime;      /* last change time */
	struct sem      *sem_base;      /* ptr to first semaphore in array */
	struct wait_queue *eventn;
	struct wait_queue *eventz;
	struct sem_undo  *undo;         /* undo requests on this array */
	ushort          sem_nsems;      /* no. of semaphores in array */
	};

// Cmd values
#define GETVAL   1 //Return the value of semval, see <sys/sem.h>. Requires read permission.
#define SETVAL   2 //Set the value of semval to arg.val, where arg is the value of the fourth argument to semctl(). When this command is successfully executed, the semadj value corresponding to the specified semaphore in all processes is cleared. Requires alter permission, see IPC.
#define GETPID   3 //Return the value of sempid. Requires read permission.
#define GETNCNT  4 //Return the value of semncnt. Requires read permission.
#define GETZCNT  5 //Return the value of semzcnt. Requires read permission.

//The following values of cmd operate on each semval in the set of semaphores:
#define GETALL   6 //Return the value of semval for each semaphore in the semaphore set and place into the array pointed to by arg.array, where arg is the fourth argument to semctl(). Requires read permission.
#define SETALL   7 //Set the value of semval for each semaphore in the semaphore set according to the array pointed to by arg.array, where arg is the fourth argument to semctl(). When this command is successfully executed, the semadj values corresponding to each specified semaphore in all processes are cleared. Requires alter permission.

//The following values of cmd are also available:
#define IPC_STAT 8 //Place the current value of each member of the semid_ds data structure associated with semid into the structure pointed to by arg.buf, where arg is the fourth argument to semctl(). The contents of this structure are defined in <sys/sem.h>. Requires read permission.
#define IPC_SET  9 //Set the value of the following members of the semid_ds data structure associated with semid to the corresponding value found in the structure pointed to by arg.buf, where arg is the fourth argument to semctl():
//	sem_perm.uid
//	sem_perm.gid
//	sem_perm.mode
//	The mode bits specified in IPC are copied into the corresponding bits of the sem_perm.mode associated with semid. The stored values of any other bits are unspecified. This command can only be executed by a process that has an effective user ID equal to either that of a process with appropriate privileges or to the value of sem_perm.cuid or sem_perm.uid in the semid_ds data structure associated with semid.
#define IPC_RMID 10 //Remove the semaphore-identifier specified by semid from the system and destroy the set of semaphores and semid_ds data structure associated with it. This command can only be executed by a process that has an effective user ID equal to either that of a process with appropriate privileges or to the value of sem_perm.cuid or sem_perm.uid in the semid_ds data structure associated with semid.

extern int semctl(int semid, int semnum, int cmd, ...);
extern int semget(key_t key, int numSems, unsigned int flags);
extern int semop(int semid, struct sembuf *sops, size_t nsops);

#endif // __sys_sem_h_
