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
#include "../common/message/SDMReqReg.h"
#include "../common/message/SDMRegInfo.h"
#include "../common/message/SDMCommand.h"
#include "../common/MessageManager/MessageManager.h"
#include "../common/TCPcom.h"

#define DEBUG_DM_MONITOR	1

#define NUM_HEARTBEAT_TRIES	12	/*Number of times to miss a response before restarting the DM*/

// TODO:
const unsigned int RESET_SECURITY_KEY = 1234;
const char* STR_RESET_DEVICE_NAME = "PowerController";
const char* STR_RESET_DEVICE_INTERFACE = "PowerStatusInterface";
const char* STR_RESET_DEVICE_ITEM = "SystemWarmBoot";

SDMComponent_ID idResetDevice;
SDMMessage_ID idCmdReset;

bool bResetDeviceFound = false;
const int ID_RESET_COMMAND = 3;

int StartDM(char **);
void SigIntHandler(int);
void DMFailure();
void SendReqReg();
void RegInfoHandler(const char* msgBuf);

int dm_pid = -1;		//Process id number of the Data Manager

int main(int argc, char ** argv)
{
	int result = -1;
	int miss_count = 0;
	char buf[BUFSIZE];
	SDMReady heartbeat;
	MessageManager mm;
	
	if (argc == 1)
	{
		printf("Usage:\n%s dm_process [dm_process_args...]\n", argv[0]);
		return -1;
	}
	
	// Set up the command line for the child process
	char** nargv = new char*[argc];
	for (int i = 1;  i < argc;  ++i)
		nargv[i-1] = argv[i];
	nargv[argc-1] = NULL;
	
	//Set monitor process address
	heartbeat.destination.setSensorID(0);
	heartbeat.destination.setAddress(inet_addr("127.0.0.1"));
	heartbeat.destination.setPort(PORT_DM_MONITOR);
	
	//Set DM address
	DataManager.setAddress(inet_addr("127.0.0.1"));
	DataManager.setPort(PORT_DM);
	DataManager.setSensorID(0);
	
	signal(SIGINT, SigIntHandler);
	dm_pid = StartDM(nargv);
	mm.Async_Init(PORT_DM_MONITOR);
	
	//If fork/exec was successful
	if (dm_pid > 0)		
	{
		unsigned char ucType;
		bool bHeartbeatReceived = false;
		//Allow the DM to get started up
		sleep(HEARTBEAT_INTERVAL);
		
		// Request the reset device
		SendReqReg();
		while (1)
		{
			bHeartbeatReceived = false;
			//Send heartbeats via UDP
			heartbeat.SendTo(DataManager);
			sleep(HEARTBEAT_INTERVAL);
			
			//If Data Manager quit
			if (waitpid(-1,&result,WNOHANG) == dm_pid)
			{
				printf("  Monitor:  DM failed...\n");
				DMFailure();
			}
			while (mm.IsReady())
			{
				ucType = mm.GetMessage(buf);
				switch(ucType)
				{
					case SDM_Ready:
					{
						miss_count = 0;
						bHeartbeatReceived = true;
					}
						break;
					case SDM_RegInfo:
					{
						RegInfoHandler(buf);
					}
						break;
					default:
						printf("  Monitor:  Unexpected message 0x%hhx\n", ucType);
						break;
				}
			}
			
			if (!bHeartbeatReceived)
			{
				//If no messages were received
				miss_count++;
				if (miss_count >= NUM_HEARTBEAT_TRIES)
				{
					printf("  Monitor:  DM unresponsive...\n");
					DMFailure();
				}
			}
		}
	}
	else
	{
		printf("  Monitor:  Error starting the DM (%d).\n", dm_pid);
		return -1;
	}

	return 0;
}

void SendReqReg()
{
	SDMReqReg msgReqReg;
	
	msgReqReg.destination.setPort(PORT_DM_MONITOR);
	strncpy(msgReqReg.device, STR_RESET_DEVICE_NAME, sizeof(msgReqReg.device));
	strncpy(msgReqReg.interface, STR_RESET_DEVICE_INTERFACE, sizeof(msgReqReg.interface));
	strncpy(msgReqReg.item_name, STR_RESET_DEVICE_ITEM, sizeof(msgReqReg.item_name));
	msgReqReg.id = ID_RESET_COMMAND;
	msgReqReg.reply = SDM_REQREG_CURRENT_AND_FUTURE;
	
	msgReqReg.Send();
#ifdef DEBUG_DM_MONITOR
	printf("  Monitor: ReqReg sent for reset device.\n");
#endif
}

void RegInfoHandler(const char* msgBuf)
{
	SDMRegInfo msgRegInfo;
	long lResult = 0;
	if ((lResult = msgRegInfo.Unmarshal(msgBuf)) == SDM_NO_FURTHER_DATA_PROVIDER)
		return;
	else if (lResult < 0)
	{
		printf("  Monitor: received invalid SDMRegInfo message.\n");
		return;
	}
	
	if (msgRegInfo.id == ID_RESET_COMMAND && msgRegInfo.type == SDM_REGINFO_REGISTRATION)
	{
		idResetDevice = msgRegInfo.source;
		idCmdReset = msgRegInfo.msg_id;
		bResetDeviceFound = true;
#ifdef DEBUG_DM_MONITOR
		printf("  Monitor: Reset device found.\n");
#endif
	}
	else if (msgRegInfo.id == ID_RESET_COMMAND && msgRegInfo.type == SDM_REGINFO_CANCELLATION)
	{
		bResetDeviceFound = false;
#ifdef DEBUG_DM_MONITOR
		printf("  Monitor: Reset device cancelled.\n");
#endif
	}
}

void DMFailure()
{
#ifdef DEBUG_DM_MONITOR
	printf("  Monitor: %s()\n", __FUNCTION__);
#endif
	if (!bResetDeviceFound)
	{
		printf("  Monitor: Reset device not found.\n");
		return;
	}
	
	SDMCommand msgCommand;
	
	msgCommand.command_id = idCmdReset;
	msgCommand.source = idResetDevice;
	PUT_UINT(msgCommand.data, RESET_SECURITY_KEY);
	msgCommand.length = sizeof(RESET_SECURITY_KEY);
	
	msgCommand.Send(idResetDevice);
	
	sleep(1);
	fflush(NULL);
	exit(EXIT_FAILURE);
}

int StartDM(char ** argv)
{
	int pid;
	
	pid = vfork();
	//Child Process
	if (pid == 0)
	{
		//Start the Data Manager
		if (execvp(argv[0],argv) < 0)
		{
			printf("  Monitor:  Error exec'ing the DM.\n");
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
	if (kill (SIGINT, dm_pid) == 0)
		wait (&result);
	else
		waitpid(-1,&result,WNOHANG);
	
	exit(EXIT_SUCCESS);
}

