#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <sys/poll.h>
#include <errno.h>
#include <unistd.h>
#include <ctype.h>
#include <getopt.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include "../common/MessageManipulator/MessageManipulator.h"
#include "../common/message/SDMCancel.h"
#include "../common/message/SDMReqReg.h"
#include "../common/message/SDMRegInfo.h"
#include "../common/message/SDMConsume.h"
#include "../common/message/SDMData.h"
#include "../common/message/SDMCode.h"
#include "../common/message/SDMReqCode.h"
#include "../common/semaphore/semaphore.h"
#include "../common/Debug.h"
#include "PMProcess.h"
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

//  IDS DATA AND DEFINITIONS
#define TM_Mode_ID	1		//ID number used in RegInfo and ReqReg messages for TM's status message
#define IDS_OPEN_HANDLE_ID	2
#define IDS_CLOSE_HANDLE_ID	3
#define IDS_READ_PORTION_ID	4

// IDS Data
SDMMessage_ID IDSIDOpenHandle, IDSIDOpenHandleReply, IDSIDCloseHandle, IDSIDCloseHandleError, IDSIDReadPortion, IDSIDReadPortionReply;
MessageManipulator MMIDSOpenHandle, MMIDSCloseHandle, MMIDSReadPortion;
SDMComponent_ID IDSCompID;
const unsigned char IDS_STATUS_OK = 1;		//Status code for OK
const unsigned long MAX_PORTION_LENGTH = 24248;

pthread_mutex_t IDSFoundMutex = PTHREAD_MUTEX_INITIALIZER;
bool g_bIDSFound = false;

// New IDS functions
bool IDSOpenHandle(const char* strPath, const char *filename, int fd_readcode, unsigned short *HandleOut);
bool IDSReadPortion(unsigned short Handle, unsigned long ByteOffset, unsigned long Length, char *Buffer, unsigned long *LengthOut, int fd_readcode);
bool IDSCloseHandle(unsigned short Handle);
bool PipeReadTimeout(int FileDes, char *Buffer, int BufLen, int *LengthReturn);
void CancelReqRegSubs(void);
PROCESS_HANDLE LaunchTask (char *strTaskFilename, long lSdmPid);
// END IDS DATA AND DEFINITIONS


enum TaskLocationEnum { TASK_LOCATION_PRIMARY = 1, TASK_LOCATION_TEMPORARY = 2,
			TASK_LOCATION_BACKUP = 3 };
#ifdef __uClinux__
# define STR_TASK_LOCATION_PRIMARY "/primary/"
# define STR_TASK_LOCATION_TEMPORARY "/test/"
# define STR_TASK_LOCATION_BACKUP "/backup/"
# define STR_TASK_LOCATION_DEFAULT "/"
#else
# define STR_TASK_LOCATION_PRIMARY "/primary/"
# define STR_TASK_LOCATION_TEMPORARY "/test/"
# define STR_TASK_LOCATION_BACKUP "/backup/"
# define STR_TASK_LOCATION_DEFAULT "/"
#endif // #ifdef __uClinux__


void HandleCodeMessage(const char* buf)
{
	debug_f(0, "SDMCode message not handled\n");
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
	MessageManipulator MM;
	static bool IDSReadFound = false, IDSOpenHandleFound = false, IDSCloseHandleFound = false;
	
	long result = msgRegInfo.Unmarshal(buf);
	MessageReceived(&msgRegInfo);
	
	if (result == SDM_INVALID_MESSAGE || result == SDM_NO_FURTHER_DATA_PROVIDER)
		return;
	
	MM.setMsgDef(msgRegInfo);
	
	switch(msgRegInfo.id)
	{
		case TM_Mode_ID:
		{
			debug_f(2,"TM status message found, subscribing.\n");
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
		break;
		case IDS_OPEN_HANDLE_ID:
		{
			if (msgRegInfo.type == SDM_REGINFO_REGISTRATION)
			{
				IDSIDOpenHandle = MM.getMsgID(COMMANDMSG);
				IDSIDOpenHandleReply = MM.getMsgID(DATAMSG);
				MMIDSOpenHandle.setMsgDef(msgRegInfo);
				
				debug_f(3,"Found IDS Open Handle\n");

				//New IDS found?
				if (!(IDSCompID == msgRegInfo.source))
				{
					IDSCompID = msgRegInfo.source;
				}
				IDSOpenHandleFound = true;
			}
			else if (msgRegInfo.type == SDM_REGINFO_CANCELLATION)
			{
				IDSOpenHandleFound = false;
				debug_f(3,"IDS open handle message cancelled.\n");
			}
		}
		break;
		case IDS_CLOSE_HANDLE_ID:
		{
			if (msgRegInfo.type == SDM_REGINFO_REGISTRATION)
			{
				IDSIDCloseHandle = MM.getMsgID(COMMANDMSG);
				IDSIDCloseHandleError = MM.getMsgID(DATAMSG);
				MMIDSCloseHandle.setMsgDef(msgRegInfo);
				
				debug_f(3,"Found IDS Close Handle\n");
				
				//New IDS found?
				if (!(IDSCompID == msgRegInfo.source))
				{
					IDSCompID = msgRegInfo.source;
				}
				IDSCloseHandleFound = true;
			}
			else if (msgRegInfo.type == SDM_REGINFO_CANCELLATION)
			{
				IDSCloseHandleFound = false;
				debug_f(3,"IDS close handle message cancelled.\n");
			}
		}
		break;
		case IDS_READ_PORTION_ID:
		{
			if (msgRegInfo.type == SDM_REGINFO_REGISTRATION)
			{
				IDSIDReadPortion = MM.getMsgID(COMMANDMSG);
				IDSIDReadPortionReply = MM.getMsgID(DATAMSG);
				MMIDSReadPortion.setMsgDef(msgRegInfo);
				
				debug_f(3, "Found IDS Read Portion\n");

				//New IDS found?
				if (!(IDSCompID == msgRegInfo.source))
				{
					IDSCompID = msgRegInfo.source;
				}
				IDSReadFound = true;
			}
			else if (msgRegInfo.type == SDM_REGINFO_CANCELLATION)
			{
				IDSReadFound = false;
				debug_f(3,"IDS read portion message cancelled.\n");
			}
		}
		break;
	}
	// If all three IDS services have been found, regard the IDS as available
	if (IDSReadFound && IDSOpenHandleFound && IDSCloseHandleFound)
	{
		pthread_mutex_lock(&IDSFoundMutex);
		g_bIDSFound = true;
		pthread_mutex_unlock(&IDSFoundMutex);
	}
	else
	{
		pthread_mutex_lock(&IDSFoundMutex);
		g_bIDSFound = false;
		pthread_mutex_unlock(&IDSFoundMutex);
	}
}
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
	
	// Cancel the subscription to the IDS Open Handle
	msgCancel.msg_id = IDSIDOpenHandle;
	msgCancel.source = IDSCompID;
	msgCancel.Send();
	MessageSent(&msgCancel);
	
	// Cancel the subscription to the IDS Close Handle
	msgCancel.msg_id = IDSIDCloseHandle;
	msgCancel.Send();
	MessageSent(&msgCancel);
	
	// Cancel the subscription to the IDS Open Handle
	msgCancel.msg_id = IDSIDReadPortion;
	msgCancel.Send();
	MessageSent(&msgCancel);
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
	long lResult;
	if ((lResult=msgData.Unmarshal(buf)) < 0)
	{
		printf("Invalid SDMData message.\n");
		return;
	}
	MessageReceived(&msgData);
	debug_f(1,"SDMData message received (0x%x).\n", msgData.msg_id.getInterfaceMessagePair());
	
	// If this SDMData message is the TaskManager's mode notification
	if (msgData.source == TaskManager && msgData.msg_id == tm_mode_msg_id)
	{
		// Hang on to the current mode
		ucOldMode = tm_mode;
		tm_mode = msgData.msg[0];

		debug_f(1,"TM Mode change %d.\n",tm_mode);
		if (tm_mode == MODE_HARD_RESET)
		{
		  debug_f(1, "  Performing a hard reset...\n");
			// The DataManager has failed, get the new DM's address from the message
			newDmId.Unmarshal(&msgData.msg[1], 0);
			DataManager = newDmId;

			debug_f(1,"New DM address is 0x%lx:%hd %ld\n",newDmId.getAddress(), newDmId.getPort(), newDmId.getSensorID());
			// Perform a reset
			DoReset();
			// For a hard reset, reregister the PMs xTEDS
			RegisterXteds();
		}
		else if (tm_mode == MODE_SOFT_RESET)
		  {
		    debug_f(1, "  Performing a soft reset...\n");
		    // Perform the reset
		    DoReset();
		  }
		// Re-set the old mode
		tm_mode = ucOldMode;
	}
	//
	// IDS open handle reply
	else if (msgData.source == IDSCompID && msgData.msg_id == IDSIDOpenHandleReply)
	{
		debug_f(3, "IDSOpenHandle data reply message received.\n");
		// Find the file receiver process which corresponds with this filename
		unsigned int receiver_index = 0;
		int Length;
		char *Filename = (char*)MMIDSOpenHandle.getArray("FileName", msgData, DATAMSG, Length);
		unsigned short IDSHandle = MMIDSOpenHandle.getUINT16Value("FileHandle", msgData, DATAMSG);

		if (Filename == NULL)
		{
			debug_f(2,"Handle reply message received which does not match any code-consuming process (filename NULL).\n");
			return;
		}
		//
		// Find the "code consuming" processing and pipe this code message
		//
		pthread_mutex_lock(&codeReceiversMutex);
		const unsigned int CODE_RECEIVERS_SIZE = codeReceivers.size();
		for (receiver_index = 0; receiver_index < CODE_RECEIVERS_SIZE; receiver_index++)
		{
			if (!strcmp(codeReceivers[receiver_index].filename, Filename))
				break;
		}
		//
		// If no file receiver matched this data message
		if (receiver_index == CODE_RECEIVERS_SIZE)
		{
			debug_f(2,"Handle reply message received which does not match any code-consuming process.\n");
			pthread_mutex_unlock(&codeReceiversMutex);
			return;
		}
		codeReceivers[receiver_index].ids_handle = IDSHandle;
		//
		// Write the code message to the pipe
		if (write(codeReceivers[receiver_index].fd_code, buf, lResult) <= 0)
			perror("Error writing code message to code pipe in HandleCodeMessage().\n");
		pthread_mutex_unlock(&codeReceiversMutex);
	}
	// IDS read portion reply
	else if (msgData.source == IDSCompID && msgData.msg_id == IDSIDReadPortionReply)
	{
		debug_f(3, "IDSReadPortion data reply message received.\n");
		// Find the file receiver process which corresponds to this handle
		unsigned int receiver_index = 0;
		unsigned short MsgHandle = MMIDSReadPortion.getUINT32Value("FileHandle", msgData, DATAMSG);

		pthread_mutex_lock(&codeReceiversMutex);
		const unsigned int CODE_RECEIVERS_SIZE = codeReceivers.size();
		for (receiver_index = 0; receiver_index < CODE_RECEIVERS_SIZE; receiver_index++)
		{
			if (codeReceivers[receiver_index].ids_handle == MsgHandle)
			{
				debug_f(2, "Code message received for %s\n", codeReceivers[receiver_index].filename);
				break;
			}
		}
		// If no file receiver matched this data message
		if (receiver_index == CODE_RECEIVERS_SIZE)
		{
			debug_f(2,"ReadPortion reply message received which does not match any code-consuming process.\n");
			pthread_mutex_unlock(&codeReceiversMutex);
			return;
		}
		// Write the code message to the pipe
		else if (write(codeReceivers[receiver_index].fd_code, buf, lResult) <= 0)
			perror("Error writing code message to code pipe in HandleCodeMessage().\n");
		pthread_mutex_unlock(&codeReceiversMutex);
	}
}

/*
	The GetCode routine requests executable code from the TM
	INPUTS:
		filename - name of the code desired
		fd_readcode - file descriptor for the pipe to read the code messsager
	RETURN VALUE:
		true - code successfully retrieved
		false - code not retrieved
*/
bool GetCode (const char* filename, long pid, int iVersion, int fd_readcode)
{
	bool IsValid=false; 	//true if all CRC checks on the code were successful
	FILE *fp;		//a file pointer to write to
	char FileBuf[BUFSIZE];
	bool FileReceived = false;
	unsigned short IDSHandle;
	
	debug_f(2,"   requesting code (%s)...\n", filename);
	//
	// If the IDS has not yet registered, wait until it does
	pthread_mutex_lock(&IDSFoundMutex);
	bool bIDSFound = g_bIDSFound;
	pthread_mutex_unlock(&IDSFoundMutex);
	while (!bIDSFound)
	{
		sleep(1);
		pthread_mutex_lock(&IDSFoundMutex);
		bIDSFound = g_bIDSFound;
		pthread_mutex_unlock(&IDSFoundMutex);
	}
	//
	// Determine which path to transfer from
	char strPath[128];
	switch (iVersion)
	  {
	  case TASK_LOCATION_PRIMARY:
	    strncpy(strPath, STR_TASK_LOCATION_PRIMARY, sizeof(strPath));
	    debug_f(3, "  Using primary location %s to retrieve task.\n", strPath);
	    break;
	  case TASK_LOCATION_TEMPORARY:
	    strncpy(strPath, STR_TASK_LOCATION_TEMPORARY, sizeof(strPath));
	    debug_f(3, "  Using temporary location %s to retrieve task.\n", strPath);
	    break;
	  case TASK_LOCATION_BACKUP:
	    strncpy(strPath, STR_TASK_LOCATION_BACKUP, sizeof(strPath));
	    debug_f(3, "  Using backup location %s to retrieve task.\n", strPath);
	    break;
	  default:
	    strncpy(strPath, STR_TASK_LOCATION_DEFAULT, sizeof(strPath));
	    debug_f(3, "  Using default location %s to retrieve task.\n", strPath);
	  }
	strPath[sizeof(strPath) - 1] = '\0';

	//Obtain handle
	if (!IDSOpenHandle(strPath, filename, fd_readcode, &IDSHandle))
		return false;
	
	//Open file
	g_semLaunchTask.Wait();
	fp = fopen(filename, "wb");
	if (SetCloseFileOnExec(fileno(fp)) == -1)
		printf("Error setting new file to close on fork.\n");
	g_semLaunchTask.Signal();
	
	unsigned long CurBytesReceived = 0, TotalBytesReceived = 0;
	unsigned long Offset = 0;
	int FailCount = 0;
	const int READ_ATTEMPTS = 10;
	while (!FileReceived)
	{
		memset(FileBuf, 0, sizeof(FileBuf));
		// Request a read portion from the IDS
		if (false == IDSReadPortion(IDSHandle, Offset, MAX_PORTION_LENGTH, 
			FileBuf, &CurBytesReceived, fd_readcode))
		{
			debug_f(3, "   (%s) IDSReadPortion failed.  Trying %d more times\n",
				filename, READ_ATTEMPTS - FailCount);
			if (FailCount++ >= READ_ATTEMPTS)
				break;
		}
		else
		{
			FailCount = 0;
			if (CurBytesReceived == 0)
			{
				// If file reading is done
				FileReceived = true;
				IsValid = true;
				break;
			}

			debug_f(2, "  (%s) IDS Read success.  Writing %lu bytes to file \
				at offset %lu.\n",filename,CurBytesReceived,Offset);
			debug_f(3, "  (%s)   CurBytesReceived is %lu\n", filename,
				CurBytesReceived);

			if (fwrite(FileBuf, 1, CurBytesReceived, fp) == 0)
			{
				printf ("Error with fwrite.\n");
			}
			TotalBytesReceived += CurBytesReceived;
			Offset += CurBytesReceived;

			debug_f(3, "  (%s)   Total bytes received is %lu\n", 
				filename, TotalBytesReceived);
		}
	}
	// Code transfering has finished, whether success or error, perform cleanup
	//   1.  Remove this code receiver entry
	RemoveCodeReceiver (filename);

	//   2.  Close the IDS handle
	IDSCloseHandle(IDSHandle);

	//   3.  Close the file
	fclose (fp);
	
	if (IsValid)
	{
		debug_f(3, "   (%s) Code retrieval success.\n",filename);
		// Make the file executable
		chmod (filename, S_IRUSR | S_IWUSR | S_IXUSR |
			S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH);
		return true;
		
	}
	else //delete bad code
	{
		debug_f(3, "   (%s) Code retrieval failed.\n",filename);
		unlink(filename);
		return false;
	}
	return false; //this point should not be reached
}

/*
 *  Read a portion of a file from the IDS and store it in Buffer (must be at least BUFSIZE)
 */
bool IDSReadPortion(unsigned short Handle, unsigned long ByteOffset, unsigned long Length, char *Buffer, unsigned long *LengthOut, int fd_readcode)
{
	unsigned short IDSHandleReturned = 0;
	unsigned long IDSLengthReturned = 0;
	unsigned long IDSOffsetReturned = 0;
	unsigned char IDSStatusReturned = 0;
	void *IDSFileBufferReturned = NULL;
	int IDSFileBufferLength = 0;
	char MsgBuf[BUFSIZE];
	
	if (Buffer == NULL || LengthOut == NULL)
		return false;
	
	SDMService Request;
	Request.command_id = IDSIDReadPortion;
	Request.destination.setPort(PORT_PM);
	Request.source = IDSCompID;
	if ( !MMIDSReadPortion.setValue("FileHandle", Request, Handle)
		|| !MMIDSReadPortion.setValue("ByteOffset", Request, ByteOffset)
		|| !MMIDSReadPortion.setValue("Length", Request, Length) )
	{
		printf("IDSReadPortion::Error with MessageManipulator.\n");
		return false;
	}
	Request.length = MMIDSReadPortion.getLength(COMMANDMSG);
	Request.Send();
	
	int MsgLength;
	if (!PipeReadTimeout(fd_readcode, MsgBuf, sizeof(MsgBuf), &MsgLength))
		return false;
	
	SDMData Reply;
	if (Reply.Unmarshal(MsgBuf) < 0)
		return false;
	//
	// Some error checking to make sure we received a valid message
	IDSHandleReturned = MMIDSReadPortion.getUINT16Value("FileHandle", Reply, DATAMSG);
	if (IDSHandleReturned != Handle)
	{
		debug_f(1, "%s -- IDS handle returned is invalid.\n", __FUNCTION__);
		return false;
	}
	
	IDSStatusReturned = MMIDSReadPortion.getUINT08Value("StatusCode", Reply, DATAMSG);
	if (IDSStatusReturned != IDS_STATUS_OK)
	{
		debug_f(1, "%s -- IDS status returned is invalid.\n", __FUNCTION__);
		return false;
	}

	IDSLengthReturned = MMIDSReadPortion.getUINT32Value("Length", Reply, DATAMSG);
	if (IDSLengthReturned > BUFSIZE)
	{
		debug_f(1, "%s -- IDS length returned is invalid.\n", __FUNCTION__);
		return false;
	}

	IDSOffsetReturned = MMIDSReadPortion.getUINT32Value("ByteOffset", Reply, DATAMSG);
	if (IDSOffsetReturned != ByteOffset)
	{
		debug_f(1, "%s -- IDS offset returned is invalid.\n", __FUNCTION__);
		return false;
	}
	
	IDSFileBufferReturned = MMIDSReadPortion.getArray("FileBuffer", Reply, DATAMSG, IDSFileBufferLength);
	if (IDSFileBufferReturned == NULL)
	{
		debug_f(1, "%s -- IDS file buffer returned is invalid.\n", __FUNCTION__);
		return false;
	}
	
	// Return the buffer and the length
	memcpy(Buffer, IDSFileBufferReturned, IDSLengthReturned);
	*LengthOut = IDSLengthReturned;
	return true;
}

/*
 *  Request a handle for the specified file from the IDS.
 */
bool IDSOpenHandle(const char* strPath, const char* filename, int fd_readcode, unsigned short *HandleOut)
{
	unsigned short IDSHandle = 0;
	const unsigned char FileMode = 1;		//IDS Filemode ReadOnly
	unsigned char IDSStatus = '\0';
	int length;
	char buf[BUFSIZE];
	const int NUM_RETRIES = 10;
	
	debug_f(2, "IDSOpenHandle for filename %s\n", filename);

	if (HandleOut == NULL)
		return false;
	//
	// Request a file handle for this file
	SDMService Request;
	Request.command_id = IDSIDOpenHandle;
	Request.destination.setPort(PORT_PM);
	Request.source = IDSCompID;

	if ( !MMIDSOpenHandle.setArray("PathName", Request, strPath, strlen(strPath)+1)
		|| !MMIDSOpenHandle.setArray("FileName", Request, filename, strlen(filename)+1)
		|| !MMIDSOpenHandle.setValue("FileFlag", Request, FileMode) )
	{
		printf("IDSFileRequest::Error with MessageManipulator.\n");
		return false;
	}
	Request.length = MMIDSOpenHandle.getLength(COMMANDMSG);

	int iSendCount = 0;
	do
	{	
		Request.Send();
		// Read from the pipe
		if (false == PipeReadTimeout(fd_readcode, buf, sizeof(buf), &length))
		{
			if (length == 0)
			{
				// Read timeout
				iSendCount++;
			}
			else
			{
				// Error
				return false;
			}
		}
		else	
		{
			// Read success
			break;
		}
	} while (iSendCount < NUM_RETRIES);

	if (length <= 0)
	{
		// Read error or no response
		return false;
	}	

	SDMData Reply;
	Reply.Unmarshal(buf);
	IDSStatus = MMIDSOpenHandle.getUINT08Value("StatusCode", Reply, DATAMSG);
	debug_f(2, "IDSOpenHandle reply, status is 0x%hhx\n", IDSStatus);

	if (IDSStatus != IDS_STATUS_OK)
	{
		//File probably doesn't exist
		return false;
	}
	//
	// Get and return the handle
	IDSHandle = MMIDSOpenHandle.getUINT16Value("FileHandle", Reply, DATAMSG);
	if (IDSHandle == 0)
		return false;

	*HandleOut = IDSHandle;
	return true;
}

bool IDSCloseHandle(unsigned short Handle)
{
	SDMCommand Command;
	Command.command_id = MMIDSCloseHandle.getMsgID(COMMANDMSG);
	if ( !MMIDSCloseHandle.setValue("FileHandle", Command, Handle) )
	{
		printf("IDSCloseHandle::Error with MessageManipulator.\n");
		return false;
	}
	Command.length = MMIDSCloseHandle.getLength(COMMANDMSG);
	Command.destination.setPort(PORT_PM);
	Command.source = IDSCompID;
	Command.Send();
	return true;
}

void ReqRegSubs(void)
{
	SDMReqReg Request;
	
	//Request the IDS open handle service
	Request.destination.setPort(PORT_PM);
	Request.id = IDS_OPEN_HANDLE_ID;
	strcpy(Request.interface, "FileAccessInterface");
	strcpy(Request.item_name,"OpenFileHandle");
	Request.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;
	Request.Send();
	MessageSent(&Request);
	
	//Request the IDS close handle service
	Request.id = IDS_CLOSE_HANDLE_ID;
	strcpy(Request.item_name,"CloseFileHandle");
	Request.Send();
	MessageSent(&Request);
	
	//Request the IDS read portion service
	Request.id = IDS_READ_PORTION_ID;
	strcpy(Request.item_name,"ReadPortion");
	Request.Send();
	MessageSent(&Request);
	
	//SDMReqReg for TM's status message
	debug_f(2,"Looking for TM status message.\n");
	Request.reply = SDM_REQREG_CURRENT_AND_FUTURE;
	Request.id = TM_Mode_ID;
	strcpy(Request.device, "TaskManager");
	strcpy(Request.interface, "TM_Interface");
	strcpy(Request.item_name, "Status");
	Request.destination.setAddress(Address_PM);
	Request.destination.setPort(PORT_PM);
	Request.Send();
	MessageSent(&Request);
}
/*
 *  Read a SDM message from a pipe, with a five second timeout imposed.
 *	Params:
 *		FileDes - The pipe file descriptor from which to read
 *		Buffer - The buffer into which to store the message
 *		BufLen - The size in bytes of Buffer, must be at least BUFSIZE
 *		LengthReturn - [Output] The number of bytes stored into Buffer, 0 if timeout, -1 if error
 *	Returns:
 *		bool - True if the read succeeds, false otherwise or upon timeout
 */
bool PipeReadTimeout(int FileDes, char *Buffer, int BufLen, int *LengthReturn)
{
	int BytesRead = 0, MsgLength = BUFSIZE, ReadResult = 0;
	struct pollfd ufd;
	ufd.fd = FileDes;
	ufd.events = POLLIN | POLLPRI;
	bool ReadDone = false;
	
	if (BufLen < BUFSIZE)
	{
		*LengthReturn = -1;
		return false;
	}
	memset(Buffer, 0, BufLen);
	// Wait for the reply
	bool HeaderReceived = false;
	while (!ReadDone)
	{
#ifndef WIN32
		// Wait 5 seconds for a message
		// Win32 doesn't support poll for pipe file descriptors, what should be done here is
		// TBD.  No timeout may be OK for our purposes in Win32.
		if (poll (&ufd, 1U, 5000) > 0)
#endif
		{
			if (!HeaderReceived)
			{
				BytesRead += ReadResult = read(FileDes, Buffer + BytesRead, HEADER_SIZE - BytesRead);
				if (ReadResult < 0)
				{
					*LengthReturn = -1;
					return false;
				}
				if (BytesRead < HEADER_SIZE)
					continue;
				// Get the message length of the SDM message
				MsgLength = GET_USHORT(Buffer+9) + HEADER_SIZE;
				if (MsgLength > BUFSIZE || MsgLength < 0)
				{
					*LengthReturn = -1;
					return false;
				}
				HeaderReceived = true;
			}
			BytesRead += ReadResult = read(FileDes, Buffer + BytesRead, MsgLength - BytesRead);
			if (ReadResult < 0)
			{
				*LengthReturn = -1;
				return false;
			}
			if (MsgLength - BytesRead <= 0)
				ReadDone = true;
		}
#ifndef WIN32
		else
		{
			// Timeout
			*LengthReturn = 0;
			return false;
		}
#endif
	}
	*LengthReturn = BytesRead;
	return true;
}

