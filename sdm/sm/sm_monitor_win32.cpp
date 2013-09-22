//*********************************************************************
//sm_monitor
//
//The sm_monitor adds robustness to the SensorManager.  The monitor periodically sends 
//heartbeat messages to the SensorManager module residing on the same node.  If for 
//some reason, the SM fails to respond, the monitor attempts to restart it.
//*********************************************************************

#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <string.h>
#include "../common/message/SDMReady.h"
#include "../common/MessageManager/MessageManager.h"
#include "../common/TCPcom.h"
#include <windows.h>
#include <process.h>

#define NUM_HEARTBEAT_TRIES	2	/*Number of times to miss a response before restarting the SM*/

HANDLE StartSM(char **);
void SigIntHandler(int);

HANDLE sm_handle = NULL;		/* Process handle of the SensorManager */

int main(int argc, char ** argv)
{
	unsigned long result = 0;
	int length = 0;
	int miss_count = 0;
	int num_toget = 0;
	char buf[BUFSIZE];
	SDMReady heartbeat;
	MessageManager mm;
	SDMComponent_ID sm;
	
	//Set monitor process address
	heartbeat.source.setSensorID(0);
	heartbeat.source.setAddress(inet_addr("127.0.0.1"));
	heartbeat.source.setPort(PORT_SM_MONITOR);
	
	//Set SM address
	sm.setAddress(inet_addr("127.0.0.1"));
	sm.setPort(PORT_SM);
	sm.setSensorID(0);
	
	signal(SIGINT, SigIntHandler);
	sm_handle = StartSM(argv);
	mm.Async_Init_Both(PORT_SM+1);
	
	/* If spawn was successful */
	if (sm_handle != NULL)		
	{
		/* Allow the SM to get started up */
		sleep(HEARTBEAT_INTERVAL);
		while (1)
		{
			//Send heartbeats via UDP
			heartbeat.SendTo(sm);
			length = heartbeat.Marshal(buf);
			sleep(HEARTBEAT_INTERVAL);
			
			//If Sensor Manager quit
			if (!GetExitCodeProcess(sm_handle,&result))
				printf("  Monitor:  Invalid handle for retrieving exit code.\n");
			/* If the SensorManager has quit for some reason */
			if (result != STILL_ACTIVE)
			{
				printf("  Monitor:  SM failed, restarting...\n");
				sm_handle = StartSM(argv);
				if (sm_handle != NULL)
				{
					/* Allow the SM to restart */
					sleep(HEARTBEAT_INTERVAL);
					/* Start over at while */
					continue;
				}
				/* Error re-starting SM */
				else
				{
					printf("  Monitor:  Could not restart the SM.\n");
					return -1;
				}
			}
			/* The SM is still running, check for responses to heartbeat messages */
			else if (mm.IsReady())
			{
				//Should respond with one message
				num_toget = 1;
				
				while (mm.IsReady())
				{
					num_toget--;
					/* Message is discarded, we only care that one was received */
					mm.GetMsg(buf);
				}
				if (num_toget > 0)
					miss_count++;
				else
					miss_count = 0;
			}
			/* The SM is still running, but no responses were received */
			else
			{
				//If no messages were received
				miss_count++;
				if (miss_count == NUM_HEARTBEAT_TRIES)
				{
					printf("  Monitor:  SM unresponsive, restarting...\n");
					/* If the Terminate fails and the SM is already dead */
					if (!TerminateProcess(sm_handle,0))
					{
						/* Get its return value */
						GetExitCodeProcess(sm_handle,&result);
					}
					/* Restart the SM */
					sm_handle = StartSM(argv);
					/* Success restarting */
					if (sm_handle != NULL)
					{
						/* Allow SM to get started */
						sleep(HEARTBEAT_INTERVAL);
						/* Start over at while loop */
						continue;
					}
					/* Error restarting */
					else
					{
						printf("  Monitor:  Could not restart the SM.\n");
						return -1;
					}
				}
			}
		}
	}
	else
	{
		printf("  Monitor:  Error starting the SM.\n");
		return -1;
	}
	return 0;
}

/*	
	StartSM starts the SensorManager module of the SDM from the monitor process.  All command line arguments are passed from the
	monitor process.  This function assumes the that both the SensorManager and the monitor binaries reside in the same directory.
	INPUTS:
		argv - The command line arguments passed to the SensorManager.
	RETURNS:
		HANDLE - The handle to the spawned SensorManager, or NULL if an error has occurred.
*/
HANDLE StartSM(char ** argv)
{
	int p_handle;								/* Handle to the spawned process (SensorManager) */
	char proc_name[512];						/* Buffer for command to execute */
	memset(proc_name,'\0',sizeof(proc_name));	/* Clear the char buffer */

	/* Assure that arguments have been passed */
	if (argv)
	{
		/*argv[0] contains the binary name from the command line */
		/*If invoked on command line without .exe */
		if (strstr(argv[0],".exe") == NULL)
			strncpy(proc_name,argv[0],strlen(argv[0])-8);	/* Copying everything but _monitor */
		/*If invoked with .exe */
		else
			strncpy(proc_name,argv[0],strlen(argv[0])-12);	/* Copying everything but _monitor.exe */
		strcat(proc_name,".exe");							/* String is now ...sm.exe */
	}
	/* If no command line arguments, error */
	else
		return NULL;
	/* Start the SensorManager */
	p_handle = _spawnv(_P_NOWAIT,proc_name,argv);
	/* If error */
	if (p_handle == -1)
	{
		perror("");
		return NULL;
	}
	/* Return the handle */
	else
		return (HANDLE)p_handle;
}
/*
	SigIntHandler handles a CTRL+C (SIGINT) signal.  This function will kill the SensorManager and the monitor process.
	INPUTS:
		sig_num - The signal sent.
	RETURNS:
		void - None.
*/
void SigIntHandler(int sig_num)
{
	unsigned long result = 0;
	if (!sm_handle)
		exit(EXIT_SUCCESS);
	sleep(1);
	if (!TerminateProcess(sm_handle,0))
		GetExitCodeProcess(sm_handle,&result);
	exit(EXIT_SUCCESS);
}

