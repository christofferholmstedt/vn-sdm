#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#ifndef __VXWORKS__
#include <getopt.h>
#include <sys/poll.h>
#else
#include <ioLib.h>
#include <selectLib.h>
#endif
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include "../common/message/SDMCancel.h"
#include "../common/message/SDMReqReg.h"
#include "../common/message/SDMRegInfo.h"
#include "../common/message/SDMConsume.h"
#include "../common/message/SDMData.h"
#include "../common/message/SDMCode.h"
#include "../common/message/SDMReqCode.h"
#include "../common/semaphore/semaphore.h"
#include "../common/Debug.h"
#include "pm.h"
#include "pm_main.h"

using namespace std;

extern SDMMessage_ID tm_mode_msg_id;
extern unsigned long Address_PM;
extern SDMComponent_ID tm_mode_source;
extern int debug;
extern bool bgTMDetected;
extern unsigned char tm_mode;
extern vector<code_recv> codeReceivers;
extern pthread_mutex_t codeReceiversMutex;
extern Sem g_semLaunchTask;

/*
 *  Cancel the PM's registration subscriptions with the Data Manager.
 */
void CancelReqRegSubs(void)
{
	SDMCancel msgCancel;
	// Cancel the subscription to the TaskManager's mode message
	msgCancel.msg_id = tm_mode_msg_id;
	msgCancel.source = tm_mode_source;
	msgCancel.destination.setPort(PORT_PM);
	msgCancel.destination.setAddress(Address_PM);
	
	msgCancel.Send();
	MessageSent(&msgCancel);
}

/*	
	ReqRegMode puts together and sends an SDMReqReg message for the TaskManager's mode message.  The mode message
	will be used to reset the ProcessManager if the DataManager has failed.
	INPUTS:
		None.
	Returns:
		None.
*/
void ReqRegSubs(void)
{
	SDMReqReg msgReqReg;
	// SDMReqReg for TM's status message
	debug_f(2,"Sending ReqReg for TM's status notification.\n");
	msgReqReg.reply = SDM_REQREG_CURRENT_AND_FUTURE;
	msgReqReg.id = TM_Mode_ID;
	strcpy(msgReqReg.device, "TaskManager");
	strcpy(msgReqReg.interface, "TM_Interface");
	strcpy(msgReqReg.item_name, "Status");
	msgReqReg.destination.setAddress(Address_PM);
	msgReqReg.destination.setPort(PORT_PM);
	
	msgReqReg.Send();
	MessageSent(&msgReqReg);
}


/*	
	RegInfoHandler handles the reception of SDMRegInfo messages.  The ProcessManager expects to receive an SDMRegInfo
	message for the TaskManager's mode message which will be used to reset the PM node upon failure of the DataManager.
	INPUTS:
		buf - The buffer containing the SDMRegInfo message.
	RETURNS:
		None.
*/
void RegInfoHandler (const char *buf)
{
	SDMRegInfo msgRegInfo;
	SDMConsume msgConsume;
	long lResult;
	if ((lResult=msgRegInfo.Unmarshal(buf)) == SDM_INVALID_MESSAGE)
	{
		printf("Invalid SDMRegInfo message received.\n");
		return;
	}
	MessageReceived(&msgRegInfo);
	if (lResult == SDM_NO_FURTHER_DATA_PROVIDER)
		return;

	if (msgRegInfo.id == TM_Mode_ID)
	{
		debug_f(2,"TM status notification found, sending subscribe request.\n");
		msgConsume.source = msgRegInfo.source;
		msgConsume.msg_id = msgRegInfo.msg_id;
		tm_mode_msg_id = msgRegInfo.msg_id.getInterfaceMessagePair();
		tm_mode_source = msgRegInfo.source;
		msgConsume.destination.setPort(PORT_PM);
		msgConsume.Send();
		MessageSent(&msgConsume);
		/*If an SDMRegInfo is received, as a result of the TM restarting after a fault, reregister with the TM */
		if (bgTMDetected)	/*If this is the first series of RegInfo's received, don't reset or re-register (bgTMDetected is false) */
		{
			//DoReset();
			SendRunningTasks();
			RegisterPM();
		}
		else
			bgTMDetected = true;	/*The next RegInfo's received will be because of a fault */
	}
}


/*	
	DataHandler handles the reception of SDMData messages.  The ProcessManager expects to received an SDMData message
	containing the TaskManager's current mode.  The mode is used to reset the PM node upon failure of the DataManager.
	INPUTS:
		buf - The buffer containing the SDMData message.
	RETURNS:
		None.
*/
void DataHandler (const char *buf)
{
	SDMData msgData;
	SDMComponent_ID newDmId;
	unsigned char ucOldMode;
	if (msgData.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMData message.\n");
		return;
	}
	MessageReceived(&msgData);
	
	// If this SDMData message is the TaskManager's mode notification
	if (msgData.msg_id == tm_mode_msg_id)
	{
		// Hang on to the current mode
		ucOldMode = tm_mode;
		tm_mode = msgData.msg[0];

		debug_f(1,"TM Mode change notification received, new mode is %hhd.\n",tm_mode);
		if (tm_mode == MODE_HARD_RESET)
		{
		  debug_f(1, "   Performing a hard reset...\n");
			// The DataManager has failed, get the new DM's address from the message
			newDmId.Unmarshal(&msgData.msg[1], 0);
			DataManager = newDmId;

			debug_f(1,"New DM address is 0x%lx:%hd %ld\n", newDmId.getAddress(), newDmId.getPort(), newDmId.getSensorID());
			// Perform a reset
			DoReset();
			// For a hard reset, reregister the PM's xTEDS
			RegisterXteds();
		}
		else if (tm_mode == MODE_SOFT_RESET)
		  {
		    debug_f(1,"  Performing a soft reset...\n");
		    // Perform the reset
		    DoReset();
		  }
		// Re-set the old mode
		tm_mode = ucOldMode;
	}
}

/*
	HandleCodeMessage handles an incoming code message, determines which child process (if multiples) is waiting for this message
	, and sends the	message to the child process through a pipe that was previously set up.
	INPUTS:
		buf - The buffer containing the SDMCode message.
	RETURNS:
		None.
*/
void HandleCodeMessage(const char *buf)
{
	SDMCode msgCode;
	unsigned int receiver_index;
	if (msgCode.Unmarshal(buf) < 0)
	{
		printf("Invalid SDMCode message.\n");
		return;
	}
	MessageReceived(&msgCode);
	debug_f(1,"Code message received.\n");
	pthread_mutex_lock(&codeReceiversMutex);
	// Find which codeReceiver matches the data message
	for (receiver_index = 0; receiver_index < codeReceivers.size(); receiver_index++)
	{
		if (!strcmp(codeReceivers[receiver_index].filename, msgCode.filename))
			break;
	}
	
	// If the end of the vector was reached before finding the match, an error occurred
	if (receiver_index == codeReceivers.size())
	{
		debug_f(2,"SDMCode message received which does not match any code-consuming process.\n");
		pthread_mutex_unlock(&codeReceiversMutex);
		return;
	}
	// Write the code message to the pipe
	else if (write(codeReceivers[receiver_index].fd_code, buf, BUFSIZE) <= 0)
	{
		perror("Error writing code message to code pipe in HandleCodeMessage().\n");
	}
	pthread_mutex_unlock(&codeReceiversMutex);
}

/*
	The GetCode routine requests executable code from the TM
	INPUTS:
		filename - name of the code desired
		fd_readcode - file descriptor for the pipe to read the code messsage
		fd_writestatus - file descriptor for the pipe to write the status message for the transfer
	RETURN VALUE:
		true - code successfully retrieved
		false - code not retrieved
*/
bool GetCode (const char* strFilename, long pid, int iVersion, int iFdReadCode)
{
	char msgBuffer[BUFSIZE];
	int iLength;
	bool bFinished = false, bValid = true;
	SDMCode msgCode;
	unsigned short usSequenceNumber, usNumSegments;
	const int MAX_CODE_SIZE = sizeof(msgCode.code);
	unsigned short usCurSequenceNumber = 1, usPollMiss = 0;

#ifdef __VXWORKS__
	char fullFilename[MAX_FILENAME_SIZE];
	strcpy(fullFilename, "/ram0/");
	strcat(fullFilename, strFilename);
	strcat(fullFilename, ".vxe");
	g_semLaunchTask.Wait();
	FILE* pFile = fopen(fullFilename, "wb");
   if(pFile == NULL)
	{
		printf("ERROR creating file %s for code transfer: %s\n", fullFilename, strerror( errno ));
	}
#else
	g_semLaunchTask.Wait();
	FILE* pFile = fopen(strFilename, "wb");
   if(pFile == NULL)
	{
		printf("ERROR creating file %s for code transfer: %s\n", strFilename, strerror( errno ));
	}
#endif

#ifndef __VXWORKS__
	if (SetCloseFileOnExec(fileno(pFile)) == -1)
		printf("Error setting new file to close on fork.\n");
#endif
	g_semLaunchTask.Signal();

	SDMReqCode msgRequestCode;
	strncpy(msgRequestCode.filename, strFilename, sizeof(msgRequestCode.filename));
	msgRequestCode.source.setAddress(Address_PM);
	msgRequestCode.source.setPort(PORT_PM);
	msgRequestCode.version = iVersion;

#ifndef __VXWORKS__
	pollfd sPoll;
	sPoll.fd = iFdReadCode;
	sPoll.events = POLLIN | POLLPRI;
#else
	struct fd_set fds;
	
	timeval timeoutVal;
	timeoutVal.tv_sec = 1;
	timeoutVal.tv_usec = 0;
#endif
	while (!bFinished)
	{
		// Request the code
		msgRequestCode.seq_num = usCurSequenceNumber;
		msgRequestCode.Send();
		MessageSent(&msgRequestCode);
		debug_f(2, "Requesting code sequence number %hu\n", usCurSequenceNumber);

#ifndef __VXWORKS__
		if (poll(&sPoll, 1, 250) == 0)
#else
		memset(fds.fds_bits, 0, sizeof(fds.fds_bits));
		FD_SET(iFdReadCode, &fds);

		if(select(iFdReadCode + 1, &fds, NULL, NULL, &timeoutVal) <= 0)
#endif
		{
			if (usPollMiss++ == 10)
			{
				printf("Code transfer failed -- too many retries.\n");
				bValid = false;
				break;
			}
		}
			
		if((iLength = read(iFdReadCode, msgBuffer, sizeof(msgBuffer))) < 0)
		{
			perror("Error reading code message\n");
			bValid = false;
			break;
		}
		
		if (msgBuffer[0] != SDM_Code)
		{
			printf("Received message other than SDMCode, error.\n");
			bValid = false;
			break;
		}
		//
		// Get the message info
		msgCode.Unmarshal(msgBuffer);
		usSequenceNumber = msgCode.seq_num;
		usNumSegments = msgCode.num_segments;

		debug_f(2, " Code message received, sequence number %hu\n", usSequenceNumber);
		if (usSequenceNumber != usCurSequenceNumber)
			continue;
		if (usSequenceNumber > usNumSegments)
		{
			printf("Fatal error, sequence number is greater than number of segments\n");
			fclose(pFile);
			return false;
		}

		//
		// Write the code portion
		fseek(pFile, (msgCode.seq_num-1)*MAX_CODE_SIZE, SEEK_SET);
		fwrite (&msgCode.code, 1, msgCode.code_length, pFile);
		if (usCurSequenceNumber++ >= usNumSegments)
			bFinished = true;
		
	}
	// Perform cleanup, whether success or failure,
	//  1.  Remove this entry from the code receiver list
	//  2.  Close the file handle
	RemoveCodeReceiver(strFilename);
	fclose(pFile);

	if (!bValid)
	{
		unlink(strFilename);
	}
	else
	{
#ifndef __VXWORKS__
		// Make the file executable
		if(chmod (strFilename, S_IRUSR | S_IWUSR | S_IXUSR |
			        S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH) != 0)
    {
      perror("Error changing file permissions to executable\n");
    }
#endif
	}
	return bValid;
}

