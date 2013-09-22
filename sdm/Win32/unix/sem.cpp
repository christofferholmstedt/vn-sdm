#include "sys/sem.h"
#include <stdio.h>
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <errno.h>
#include <stdarg.h>
#include "sdmLib.h"


typedef struct sem
{
	HANDLE handle;
	int value, maxValue;;
} Sem;


static Sem* *semaphores = NULL;
static int numSemaphores = 1;

#define INITIAL_VALUE 0
#define MAX_VALUE 1

extern int semctl(int semid, int semnum, int cmd, ...)
{
	if ( semid >= numSemaphores || semnum > 0 )
	{
		errno = ERANGE;
		return -1;
	}
	Sem* sem = semaphores[semid];
	if ( sem == NULL )
	{
		errno = EINVAL;
		return -1;
	}
	long prevCount = 0;

	switch ( cmd )
	{
	case GETVAL:
		printf("semctl(%d,%d,%d, ...)\n",semid, semnum, cmd);
		break;
	case SETVAL://Set the value of semval to arg.val, where arg is the value of the fourth argument to semctl(). When this command is successfully executed, the semadj value corresponding to the specified semaphore in all processes is cleared. Requires alter permission, see IPC.
		int value;
		va_list marker;
		va_start( marker, cmd );     /* Initialize variable arguments. */
		value = va_arg( marker, int);
		va_end( marker );              /* Reset variable arguments.      */
		if ( value > sem->value )
		{
			ReleaseSemaphore( sem->handle, value - sem->value, &prevCount );
			sem->value = value;
		}
		else
		{
			while ( sem->value > value )
			{
				WaitForSingleObject( sem->handle, 0 );
				sem->value--;
			}
		}
		break;
	case GETPID://Return the value of sempid. Requires read permission.
	case GETNCNT://Return the value of semncnt. Requires read permission.
	case GETZCNT://Return the value of semzcnt. Requires read permission.

//The following values of cmd operate on each semval in the set of semaphores:
	case GETALL://Return the value of semval for each semaphore in the semaphore set and place into the array pointed to by arg.array, where arg is the fourth argument to semctl(). Requires read permission.
	case SETALL://Set the value of semval for each semaphore in the semaphore set according to the array pointed to by arg.array, where arg is the fourth argument to semctl(). When this command is successfully executed, the semadj values corresponding to each specified semaphore in all processes are cleared. Requires alter permission.

//The following values of cmd are also available:
	case IPC_STAT://Place the current value of each member of the semid_ds data structure associated with semid into the structure pointed to by arg.buf, where arg is the fourth argument to semctl(). The contents of this structure are defined in <sys/sem.h>. Requires read permission.
	case IPC_SET://Set the value of the following members of the semid_ds data structure associated with semid to the corresponding value found in the structure pointed to by arg.buf, where arg is the fourth argument to semctl():
					// sem_perm.uid
					//	sem_perm.gid
					//	sem_perm.mode
					//	The mode bits specified in IPC are copied into the corresponding bits of the sem_perm.mode associated with semid. The stored values of any other bits are unspecified. This command can only be executed by a process that has an effective user ID equal to either that of a process with appropriate privileges or to the value of sem_perm.cuid or sem_perm.uid in the semid_ds data structure associated with semid.
		printf("semctl(%d,%d,%d, ...)\n",semid, semnum, cmd);
		break;
	case IPC_RMID://Remove the semaphore-identifier specified by semid from the system and destroy the set of semaphores and semid_ds data structure associated with it. This command can only be executed by a process that has an effective user ID equal to either that of a process with appropriate privileges or to the value of sem_perm.cuid or sem_perm.uid in the semid_ds data structure associated with semid.
		CloseHandle(sem->handle);
		free(sem);
		semaphores[semid] = NULL;
		break;
	}
	return 0;
}

extern int semget(key_t key, int numSems, unsigned int flags)
{
	char name[32];
	itoa(key,name,10);
	Sem* sem = (Sem*)malloc(sizeof(Sem));
	sem->value = INITIAL_VALUE;
	sem->maxValue = MAX_VALUE;
	sem->handle = CreateSemaphore(NULL, sem->value, sem->maxValue, name);
	semaphores = (Sem**)realloc(semaphores,(numSemaphores+1)*sizeof(Sem));
	semaphores[numSemaphores] = sem;
	return numSemaphores++;
}

extern int semop(int semid, struct sembuf *sops, size_t nsops)
{
	if ( semid >= numSemaphores || nsops != 1 || sops[0].sem_num >= numSemaphores )
	{
		errno = ERANGE;
		return -1;
	}
	Sem* sem = semaphores[semid];
	if ( sem == NULL )
	{
		errno = EINVAL;
		return -1;
	}

	int i = 0; // Someday utilize the group of semaphores
	if ( sops[i].sem_op > 0 )
	{
		long prevCount;
		sem->value++;
		ReleaseSemaphore( sem->handle, 1, &prevCount );
	}
	else if ( sops[i].sem_op < 0 )
	{
		sem->value--;
		WaitForSingleObject( sem->handle, INFINITE );
	}
	return 0;
}

