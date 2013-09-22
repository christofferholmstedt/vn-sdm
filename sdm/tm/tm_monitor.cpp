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

#define NUM_HEARTBEAT_TRIES	10	/*Number of times to miss a response before restarting the TM*/

int StartTM(char **);
void SigIntHandler(int);

int tm_pid = -1;		//Process id number of the Task Manager

int main(int argc, char ** argv)
{
	int result = -1;
	int length = 0;
	int miss_count = 0;
	int num_toget = 0;
	char buf[BUFSIZE];
	SDMReady heartbeat;
	MessageManager mm;
	SDMComponent_ID tm;
	
	if (argc == 1)
	{
		printf("Usage:\n%s tm_process [tm_process_args...]\n", argv[0]);
		return -1;
	}
	
	// Set up the command line for the child process
	char** nargv = new char*[argc];
	for (int i = 1;  i < argc;  ++i)
		nargv[i-1] = argv[i];
	nargv[argc-1] = NULL;
	
	// Set up TM arguments for a restart after a fault
	char fault_string[3] = "-f";
	char **fault_args = new char*[argc+1];
	for (int i = 1; i < argc; ++i)
		fault_args[i-1] = argv[i];
	fault_args[argc-1] = fault_string;
	fault_args[argc] = NULL;
	
	//Set monitor process address
	heartbeat.source.setSensorID(0);
	heartbeat.source.setAddress(inet_addr("127.0.0.1"));
	heartbeat.source.setPort(PORT_TM_MONITOR);
	
	//Set TM address
	tm.setAddress(inet_addr("127.0.0.1"));
	tm.setPort(PORT_TM);
	tm.setSensorID(0);
	
	signal(SIGINT, SigIntHandler);
	tm_pid = StartTM(nargv);
	mm.Async_Init(PORT_TM_MONITOR);
	
	//If fork/exec was successful
	if (tm_pid > 0)		
	{
		//Allow the TM to get started up
		sleep(HEARTBEAT_INTERVAL);
		while (1)
		{
			
			//Send heartbeats via UDP
			heartbeat.SendTo(tm);
			length = heartbeat.Marshal(buf);
			sleep(HEARTBEAT_INTERVAL);
			
			//If Task Manager quit
			if (waitpid(-1,&result,WNOHANG) == tm_pid)
			{
				printf("  Monitor:  TM failed, restarting...\n");
				tm_pid = StartTM(fault_args);
				if (tm_pid > 0)
				{
					sleep(HEARTBEAT_INTERVAL);
					continue;
				}
				else
				{
					printf("  Monitor:  Could not restart the TM.\n");
					return -1;
				}
			}
			else if (mm.IsReady())
			{
				//Should respond with two messages
				num_toget = 1;
				
				while (mm.IsReady())
				{
					num_toget--;
					mm.GetMessage(buf);
				}
				if (num_toget > 0)
					miss_count++;
				else
					miss_count = 0;
			}
			else
			{
				//If no messages were received
				miss_count++;
				if (miss_count == NUM_HEARTBEAT_TRIES)
				{
					printf("  Monitor:  TM unresponsive, restarting...\n");
					
					if (kill (tm_pid, SIGKILL) == 0)
						wait(&result);
					else
						waitpid(-1, &result, WNOHANG);
					
					tm_pid = StartTM(fault_args);
					if (tm_pid > 0)
					{
						sleep(HEARTBEAT_INTERVAL);
						continue;
					}
					else
					{
						printf("  Monitor:  Could not restart the TM.\n");
						return -1;
					}
					
					
				}
			}
		}
	}
	else
	{
		printf("  Monitor:  Error starting the TM (%d).\n", tm_pid);
		return -1;
	}
	
	
	return 0;
}

int StartTM(char ** argv)
{
	int pid;
	
	pid = vfork();
	//Child Process
	if (pid == 0)
	{
		//Start the Task Manager
		if (execvp(argv[0],argv) < 0)
		{
			printf("  Monitor:  Error exec'ing the TM.\n");
			exit(-1);
		}
		//Here to make the compiler happy, never runs however
		return 0;
	}
	//Parent Process
	else
		return pid;
}

void SigIntHandler(int sig_num)
{
	int result = 0;
	if (kill (SIGINT, tm_pid) == 0)
		wait (&result);
	else
		waitpid(-1,&result,WNOHANG);
	
	exit(EXIT_SUCCESS);
}

