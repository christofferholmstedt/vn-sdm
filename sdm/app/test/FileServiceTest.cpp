#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "../../common/message/SDMCommand.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/message/SDMData.h"
#include "../../common/message/SDMService.h"
#include "../../common/MessageManager/MessageManager.h"

const int FILEPATH_SIZE = 512;
//Status code definitions
const unsigned char SUC_OPERATION_OK = 1;
const unsigned char FLT_INVALID_HANDLE = 2;
const unsigned char FLT_FILE_NOT_AVAILABLE = 3;
const unsigned char FLT_INVALID_OFFSET = 4;
const unsigned char FLT_COULD_NOT_OBTAIN_HANDLE = 5;
const unsigned char FLT_WRITE_FAILURE = 6;
const unsigned char FLT_INVALID_WRITE_MODE = 7;
//File mode flags
const unsigned char READ_ONLY = 1;
const unsigned char WRITE_ONLY_OFFSET = 2;
const unsigned char WRITE_ONLY_APPEND = 3;
const unsigned char READ_WRITE_OFFSET = 4;
const unsigned char READ_WRITE_APPEND = 5;
//Message IDs as defined in the xTEDS
const SDMMessage_ID SerReadPortion(1,6);	//Identifier for reading a portion of the file
const SDMMessage_ID SerWritePortion(1,9);	//Write portion request id
const SDMMessage_ID SerOpenFileHandle(1,1);	//Identifier for open file handle service request message
const SDMMessage_ID RplyOpenFileHandle(1,2);	//Identifier for open file handle response message
const SDMMessage_ID RplyReadReply(1,7);		//Read portion reply id
const SDMMessage_ID RplyWriteReply(1,10);	//Write reply message
const SDMMessage_ID FltHandleOpenFailed(1,3);	//Identifier for open file handle fault
const SDMMessage_ID FltHandleCloseFailed(1,4);	//Identifier for close handle fault
const SDMMessage_ID FltReadPortionError(1,8);	//Read portion fault id
const SDMMessage_ID FltWritePortionError(1,11);	//Write portion error id
const SDMMessage_ID CmdCloseFileHandle(1,4);	//Identifier for close file handle command message

SDMComponent_ID FileServiceID;
MessageManager mm;

void GetFSID();
long GetFileHandle(const char *filename, unsigned char flags);
void CloseFileHandle(long handle);
bool ReadFile(long handle, const char *filename, unsigned int offset, unsigned int length);
bool WriteFile(long handle, const char *filename, unsigned int offset, unsigned int length, const char *buffer, unsigned char mode = 0);

int main(int argc, char ** argv)
{
	if (argc < 4)
	{
		printf("Usage:\n\t%s [DM-Address] [TM-Address] [PID]\n",argv[0]);
		return 0;
	}
	SDMInit(argc, argv);

	mm.Async_Init(4050);
	GetFSID();
	const char file1[] = "tm.cpp";
	const char file2[] = "DM.cpp";
	const char file3[] = "sm.cpp";
	const char file4[] = "pm.cpp";
	const char file5[] = "test_file.txt";
	const char file6[] = "test/test_file2.txt";
	const char file7[] = "test/tm.cpp";
	
	long Handle1 = GetFileHandle(file1, READ_WRITE_OFFSET);
	usleep(200);
	long Handle2 = GetFileHandle(file2, READ_ONLY);
	usleep(200);
	long Handle3 = GetFileHandle(file3, READ_ONLY);
	usleep(200);
	long Handle4 = GetFileHandle(file4, READ_ONLY);
	usleep(200);
	long Handle5 = GetFileHandle(file5, WRITE_ONLY_OFFSET);
	usleep(200);
	long Handle6 = GetFileHandle(file6, READ_ONLY);
	long temp;
	
	if (Handle1 <= 0 || Handle2 <=0 || Handle3 <=0 || Handle4 <=0 || Handle5 <=0 || Handle6 <=0)
	{
		printf("Handle <= 0\n");
		return 0;
	}
	printf("-----------TESTING FILE HANDLE CASES-----------\n");
	printf("Attempting to open %s for reading...",file1);
	temp = GetFileHandle(file1, READ_ONLY);
	if (temp < 0)	printf("failed as expected.\n");
	else	{ printf("\nERROR:  test failed.\n");  return 0;  }
	
	printf("Attempting to open %s for writing...",file2);
	temp = GetFileHandle(file2, WRITE_ONLY_APPEND);
	if (temp < 0)	printf("failed as expected.\n");
	else	{ printf("\nERROR:  test failed.\n");  return 0;  }
	
	printf("Attempting to open %s for reading...",file5);
	temp = GetFileHandle(file5, READ_ONLY);
	if (temp < 0)	printf("failed as expected.\n");
	else	{ printf("\nERROR:  test failed.\n");  return 0;  }
	
	printf("Attempting to open %s for reading and writing...",file4);
	temp = GetFileHandle(file4, READ_WRITE_APPEND);
	if (temp < 0)	printf("failed as expected.\n");
	else	{ printf("\nERROR:  test failed.\n");  return 0;  }
	
	printf("Attempting to open %s for reading...\n",file2);
	temp = GetFileHandle(file2, READ_ONLY);
	if (temp < 0) { printf("Test failed.\n");  return 0;  }
	else {  CloseFileHandle(temp);  printf("\tTest Passed.\n");	}
	printf("-----------DONE TESTING FILE HANDLE CASES-----------\n");
	
	printf("---------TESTING READ OPERATIONS---------\n");
	int offset = 3;
	int length = 10;
	printf("Testing read from %s (offset %d, length %d)\n", file1, offset, length);
	if (ReadFile(Handle1, "", offset, length))
		printf("\tTest Passed.\n");
	else
	{ printf("\tTest Failed.\n");  return 0; }
	
	offset = 300;
	length = 20;
	printf("Testing read from %s (offset %d, length %d)\n", file2, offset, length);
	if (ReadFile(Handle2, "", offset, length))
		printf("\tTest Passed.\n");
	else
	{ printf("\tTest Failed.\n");  return 0; }
	
	offset = 3;
	length = 10;
	printf("Testing read from %s (offset %d, length %d) using filename (shouldn't work)\n", file1, offset, length);
	if (!ReadFile(0, file1, offset, length))
		printf("\tTest Passed.\n");
	else
	{ printf("\tTest Failed.\n");  return 0; }
	
	offset = 3;
	length = 10;
	printf("Testing read from %s (offset %d, length %d) (shouldn't work)\n", file5, offset, length);
	if (!ReadFile(0, file5, offset, length))
		printf("\tTest Passed.\n");
	else
	{ printf("\tTest Failed.\n");  return 0; }
	
	offset = 3;
	length = 10;
	printf("Testing read from %s (offset %d, length %d)\n", file6, offset, length);
	if (ReadFile(Handle6, "", offset, length))
		printf("\tTest Passed.\n");
	else
	{ printf("\tTest Failed.\n");  return 0; }
	printf("---------DONE TESTING READ OPERATIONS---------\n");
	
	printf("---------TESTING WRITE OPERATIONS---------\n");
	offset = 100;
	length = 20;
	printf("Testing read/write for %s (offset %d, length %d)\n", file1, offset, length);
	if (WriteFile(Handle1, "", offset, length, "THIS IS A TEST WRITE"))
	{
		if (ReadFile(Handle1, "", offset, length))
			printf("\tTest passed.\n");
		else
		{	printf("\tTest failed.\n");  return 0;  }
	}
	else
	{	printf("\tTest failed.\n");  return 0;  }
	
	offset = 10;
	length = 20;
	printf("Testing write append for %s (offset %d, length %d)\n", file5, offset, length);
	if (WriteFile(Handle5, "", offset, length, "THIS IS A TEST WRITE"))
		printf("\tTest passed.\n");
	else
	{	printf("\tTest failed.\n");  return 0;  }
	
	offset = 0;
	length = 20;
	printf("Testing write append for %s (offset %d, length %d)\n", file5, offset, length);
	if (WriteFile(Handle5, "", offset, length, "THIS IS A TEST WRITE"))
		printf("\tTest passed.\n");
	else
	{	printf("\tTest failed.\n");  return 0;  }
	
	offset = 100;
	length = 20;
	printf("Testing write by filename for %s (offset %d, length %d) (won't write)\n", file5, offset, length);
	if (!WriteFile(0, file5, offset, length, "THIS IS A TEST WRITE", WRITE_ONLY_APPEND))
		printf("\tTest passed.\n");
	else
	{	printf("\tTest failed.\n");  return 0;  }
	
	offset = 100;
	length = 20;
	printf("Testing write by filename for %s (offset %d, length %d)\n", file7, offset, length);
	if (WriteFile(0, file7, offset, length, "THIS IS A TEST WRITE", WRITE_ONLY_APPEND))
		printf("\tTest passed.\n");
	else
	{	printf("\tTest failed.\n");  return 0;  }
	printf("---------DONE TESTING WRITE OPERATIONS---------\n");
	
	CloseFileHandle(Handle1);
	CloseFileHandle(Handle2);
	CloseFileHandle(Handle3);
	CloseFileHandle(Handle4);
	CloseFileHandle(Handle5);
	CloseFileHandle(Handle6);

	return 0;
}
void GetFSID()
{
	printf("Requesting FileServiceID...");
	SDMReqReg request;
	strcpy(request.interface, "FileServiceInterface");
	strcpy(request.item_name, "OpenFileHandle");
	request.destination.setPort(4050);
	request.Send();
	
	SDMRegInfo info;
	char buffer[BUFSIZE];
	bool found = false;
	while (!found)
	{
		if (mm.IsReady())
		{
			char type = mm.GetMessage(buffer);
			if (type == SDM_RegInfo)
			{
				if (info.Unmarshal(buffer) > 0)
				{
					found = true;
				}
			}
		}
		else
			sleep(1);
	}
	FileServiceID = info.source;
	char buf[256];
	FileServiceID.IDToString(buf, sizeof(buf));
	printf("Found (%s).\n",buf);
}
long GetFileHandle(const char *filename, unsigned char flags)
{
	printf("Requesting file handle...");  fflush(NULL);
	//
	//Obtain a file handle
	SDMService request;
	request.command_id = SerOpenFileHandle;
	request.source = FileServiceID;
	request.destination.setPort(4050);
	strcpy(request.data, filename);
	PUT_UCHAR(&request.data[FILEPATH_SIZE], flags);
	request.length = FILEPATH_SIZE+1;
	request.Send();
	
	SDMData data;
	char buffer[BUFSIZE];
	bool found = false;
	while (!found)
	{
		if (mm.IsReady())
		{
			char type = mm.GetMessage(buffer);
			if (type == SDM_Data)
			{
				if (data.Unmarshal(buffer) > 0)
				{
					found = true;
				}
			}
		}
		else
			sleep(1);
	}
	unsigned short handle;
	if (data.msg_id == RplyOpenFileHandle)
	{
		handle = GET_USHORT(data.msg+FILEPATH_SIZE);
		printf("Handle received for %s (%hu)\n",data.msg,handle);
		return handle;
	}
	else if (data.msg_id == FltHandleOpenFailed)
	{
		unsigned char err_code = GET_UCHAR(data.msg+FILEPATH_SIZE);
		printf("Error receiving handle (%c)\n",err_code);
	}
	return -1;
}
void CloseFileHandle(long handle)
{
	SDMCommand cmd;
	unsigned short Handle_m = (unsigned short) handle;
	printf("Closing file handle %hu\n",Handle_m);
	cmd.source = FileServiceID;
	cmd.destination.setPort(4050);
	cmd.command_id = CmdCloseFileHandle;
	PUT_USHORT(cmd.data, Handle_m);
	cmd.length = 2;
	cmd.Send();
}
bool ReadFile(long handle, const char *filename, unsigned int offset, unsigned int length)
{
	printf("Reading file...\n");
	SDMService request;
	request.command_id = SerReadPortion;
	request.source = FileServiceID;
	request.destination.setPort(4050);
	
	PUT_USHORT(request.data, handle);
	strcpy(request.data+2, filename);
	PUT_UINT(request.data+2+FILEPATH_SIZE, offset);
	PUT_UINT(request.data+2+FILEPATH_SIZE+4, length);
	request.length = 2+FILEPATH_SIZE+4+4;
	request.Send();
	
	SDMData data;
	char buffer[BUFSIZE];
	bool done = false;
	unsigned short num_segments = 0;
	unsigned short cur_segment = 0;
	unsigned int num_received = 0;
	char buf[BUFSIZE];
	unsigned int cur_length = 0;
	while (!done)
	{
		if (mm.IsReady())
		{
			char type = mm.GetMessage(buffer);
			if (type == SDM_Data)
			{
				if (data.Unmarshal(buffer) > 0)
				{
					if (data.msg_id == RplyReadReply)
					{
						if (num_segments == 0) 
						{
							num_segments = GET_USHORT(data.msg+2+2+FILEPATH_SIZE);
							printf("Number of segments is %hu.\n",num_segments);
						}
						num_received++;
						cur_length = GET_UINT(data.msg+FILEPATH_SIZE+6);
						memset(buf, 0, sizeof(buf));
						strncpy(buf, data.msg+FILEPATH_SIZE+10, cur_length);
						cur_segment = GET_USHORT(data.msg+FILEPATH_SIZE+2);
						printf("Received segment %hu length is %u\n",cur_segment,cur_length);
						printf("Contents of segment %hu: %s\n",cur_segment, buf);
						
						if (num_received == num_segments)
							done = true;
					}
					else
						return false;
				}
			}
		}
		else
			sleep(1);
	}
	return true;
}
bool WriteFile(long handle, const char *filename, unsigned int offset, unsigned int length, const char *write_buffer, unsigned char mode)
{
	printf("Writing file...\n");
	SDMService request;
	request.command_id = SerWritePortion;
	request.source = FileServiceID;
	request.destination.setPort(4050);
	
	PUT_USHORT(request.data, handle);
	strcpy(request.data+2, filename);
	PUT_UCHAR(&request.data[2+FILEPATH_SIZE], mode);
	PUT_UINT(request.data+2+FILEPATH_SIZE+1, offset);
	PUT_UINT(request.data+2+FILEPATH_SIZE+5, length);
	strcpy(request.data+11+FILEPATH_SIZE, write_buffer);
	request.length = 11+FILEPATH_SIZE+strlen(write_buffer);
	request.Send();
	
	SDMData data;
	bool done = false;
	char buffer[BUFSIZE];
	char file[FILEPATH_SIZE];
	while (!done)
	{
		if (mm.IsReady())
		{
			char type = mm.GetMessage(buffer);
			if (type == SDM_Data)
			{
				if (data.Unmarshal(buffer) > 0)
				{
					if (data.msg_id == RplyWriteReply)
					{
						unsigned short handle = GET_USHORT(data.msg);
						strcpy(file, data.msg+2);
						unsigned char status = GET_UCHAR(data.msg+FILEPATH_SIZE+2);
						printf("  Success for handle %hu, file %s, status %hhu.\n",handle, file, status);
						done = true;
					}
					else if (data.msg_id == FltWritePortionError)
					{
						unsigned short handle = GET_USHORT(data.msg);
						strcpy(file, data.msg+2);
						unsigned char status = GET_UCHAR(data.msg+FILEPATH_SIZE+2);
						printf("  Error for handle %hu, file %s, status %hhu.\n", handle, file, status);
						return false;
					}
				}
			}
		}
		else
			sleep(1);
	}
	return true;
}
