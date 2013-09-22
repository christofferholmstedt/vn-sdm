#include "asim_win32.h"
#include "../marshall.h"

#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <windows.h>
#define NO_VERSION	0xFF
#define FILE_ECHO	4

#define ASIM_IN_PIPE	0
#define ASIM_OUT_PIPE	1
#define ASIM_IOCTL_INDEX  0x0800
#define FILE_DEVICE_UNKNOWN             0x00000022
#define METHOD_IN_DIRECT                1
#define METHOD_OUT_DIRECT               2
#define FILE_ANY_ACCESS                 0
#define CTL_CODE( DeviceType, Function, Method, Access ) (                 \
    ((DeviceType) << 16) | ((Access) << 14) | ((Function) << 2) | (Method) \
)
// Perform a bulk read from the pipe specified in the first byte of the input buffer
// The length is interpreted from the buffer lengths specified in the call to DeviceIOControl
#define IOCTL_ASIM_BULK_READ                        CTL_CODE(FILE_DEVICE_UNKNOWN,     \
                                                             ASIM_IOCTL_INDEX+3,      \
                                                             METHOD_OUT_DIRECT,       \
                                                             FILE_ANY_ACCESS)

// Perform a bulk write to the pipe specified in the first byte of the input buffer
// The length is interpreted from the buffer lengths specified in the call to DeviceIOControl
#define IOCTL_ASIM_BULK_WRITE                       CTL_CODE(FILE_DEVICE_UNKNOWN,     \
                                                             ASIM_IOCTL_INDEX+4,      \
                                                             METHOD_IN_DIRECT,        \
                                                             FILE_ANY_ACCESS)

ASIM::ASIM():handle(NULL),debug(0),version(NO_VERSION),echo(NULL)
{
}

ASIM::ASIM(char* devicename):handle(NULL),debug(0),version(NO_VERSION),echo(NULL)
{
	Open(devicename);
}

ASIM::ASIM(const ASIM& b):handle(b.handle),debug(b.debug),version(b.version),echo(b.echo)

{
	strncpy(usb_location,b.usb_location,80);
	strncpy(devicename,b.devicename,20);
};

ASIM& ASIM::operator=(const ASIM& b)
{
	handle = b.handle;
	debug = b.debug;
	version = b.version;
	echo = b.echo;
	strncpy(usb_location,b.usb_location,80);
	strncpy(devicename,b.devicename,20);
	return *this;
}

bool ASIM::Open(char* m_devicename)
{
	char echo_name[15];
	strncpy(devicename,m_devicename,19);
	strncpy(echo_name,(m_devicename+5),14);
	sprintf(echo_name,"%s.out",echo_name);
	if(debug>=FILE_ECHO)
	{
		echo = fopen(echo_name,"a");
	}
	handle = CreateFile(devicename, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (handle == INVALID_HANDLE_VALUE)
	{
		if (debug >= FILE_ECHO)
		{
			fprintf(echo,"%s: %s\n",devicename,strerror(errno));
		}
		return false;
	}
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"device: %s (%s)\n",devicename,USBLocation());
		fflush(echo);
	}
	return true;
}

void ASIM::Close(void)
{
	if (handle != NULL)
		CloseHandle(handle);
	handle = NULL;
	if(debug>=FILE_ECHO)
	{
		fclose(echo);
	}
}

bool ASIM::Initialize(void)
{
	char msg[8];
	unsigned long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_INITIALIZE;
	msg[1] = msg[2] = 0;
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 3, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<3;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < 3) return false;
	return true;
}
bool ASIM::Reset(void)
{
	char msg[8];
	unsigned long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_RESET;
	msg[1] = msg[2] = 0;
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 3, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<3;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < 3) return false;
	return true;
}
bool ASIM::SelfTest(void)
{
	char msg[8];
	unsigned long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_SELF_TEST;
	msg[1] = msg[2] = 0;
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 3, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<3;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < 3) return false;
	return true;
}

bool ASIM::ReqData(unsigned char interface_id,unsigned char msg_id,long ip, short port)
{
	unsigned char msg[16];
	short length = 8;
	unsigned long result = 0;

	if (handle < 0)
		return false;
	memset(msg,0,16);
	msg[0] = ASIM_REQ_DATA;
	length = htons(length);	//length needs to be big-endian
	memcpy(&msg[1], &length, 2);
	PUT_UCHAR(&msg[3], interface_id);
	PUT_UCHAR(&msg[4],msg_id);
	PUT_LONG(&msg[5],ip);
	PUT_SHORT(&msg[9],port);
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 11, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<11;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < 4) return false;
	return true;
}

bool ASIM::ReqData(unsigned char interface_id,unsigned char msg_id)
{
	return ReqData(interface_id,msg_id,0,0);
}

bool ASIM::Cancel(unsigned char interface_id,unsigned char msg_id)
{
	unsigned char msg[8];
	short length = 2;
	unsigned long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_CANCEL;
	length = htons(length);	//length needs to be big-endian
	memcpy(msg+1,&length,2);
	msg[3] = interface_id;
	msg[4] = msg_id;
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 5, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<5;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < 4) return false;
	return true;
}
bool ASIM::ReqStream(unsigned char interface_id,unsigned char msg_id,long count)
{
	unsigned char msg[16];
	short length = 6;
	long le_count;			//little endian count
	unsigned long result = 0;
	memset(msg,0,16);
	msg[0] = ASIM_REQ_STREAM;
	length = htons(length);		//length needs to be big-endian
	memcpy(msg+1,&length,2);
	msg[3] = interface_id;
	msg[4] = msg_id;
	le_count = SDM_htonl(count);	//count needs to be little-endian
	memcpy(msg+5,&le_count,4);
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 9, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<9;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < 9) return false;
	return true;
}
bool ASIM::PowerOn(void)
{
	char msg[8];
	unsigned long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_POWER_ON;
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 3, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<3;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < 3) return false;
	return true;
}
bool ASIM::PowerDown(void)
{
	char msg[8];
	unsigned long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_POWER_DOWN;
	msg[1] = msg[2] = 0;
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 3, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<3;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < 3) return false;
	return true;
}
bool ASIM::ReqVersion(void)
{
	char msg[8];
	unsigned long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_REQ_VERSION;
	msg[1] = msg[2] = 0;
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 3, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<3;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < 3) return false;
	return true;
}
bool ASIM::Command(unsigned char interface_id,unsigned char msg_id,short length,unsigned char* data)
{
	unsigned char msg[64];
	short be_length;	//length needs to be big endian in message
	unsigned long result = 0;
	memset(msg,0,64);
	msg[0] = ASIM_COMMAND;
	be_length = length + 2; //add two bytes for interface_id and msg_id
	be_length = htons(be_length);
	memcpy(msg+1,&be_length,2);
	msg[3] = interface_id;
	msg[4] = msg_id;
	memcpy(msg+5,data,length);
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 5+length, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<5+length;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < length+5) return false;
	return true;
}

bool ASIM::ReqxTEDS(void)
{
	char msg[8];
	unsigned long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_REQ_XTEDS;
	msg[1] = msg[2] = 0;
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 3, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<3;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < 3) return false;
	return true;
}

bool ASIM::TimeAtTone(long sec,long usec)
{
	unsigned char msg[16];
	short length = 8;
	unsigned long result = 0;
	memset(msg,0,16);
	msg[0] = ASIM_TIME_AT_TONE;
	length = htons(length);		//length needs to be big-endian
	PUT_SHORT(&msg[1],length);
	PUT_LONG(&msg[3],sec);
	PUT_LONG(&msg[7],usec);
	unsigned char pipenum = ASIM_OUT_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_WRITE, &pipenum, sizeof(pipenum), msg, 11, &result, NULL))
		return false;
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent(%ld): ",result);
		for(int i=0;i<11;i++)
			fprintf(echo,"%hhx ",msg[i]);
		fprintf(echo,"\n");
		fflush(echo);
	}
	if (result < 11) return false;
	return true;
}

int ASIM::RawRead(unsigned char* data)
{
	unsigned char msg[ASIM_MAX_OUT];	//buffer for message
	long result = 0;				//result of a read
	if (handle < 0)
	{
		if(debug>=FILE_ECHO)
		{
			fprintf(echo,"ERROR: Bad handle\n");
		}
		return ASIM_ERROR;
	}
#ifdef WIN32
#else
	result = read(handle,msg,ASIM_MAX_OUT);	//read first data message
#endif

	if (result < 0)
	{
		if(debug>=FILE_ECHO)
		{
			fprintf(echo,"ERROR: %s\n",strerror(errno));
		}
		return -1;
	}
	memcpy(data,msg,result);
	return result;
}

char ASIM::Read(unsigned short& length, unsigned char* data,int buflen)
{
	unsigned char msg[ASIM_MAX_OUT];	//buffer for message
	unsigned char msg_type;			//first character of message
	unsigned long result = 0;			//result of a read
	int bytes_so_far;			//number of bytes read so far
	length = 0;				//if an error occurs before the length field
						//can be read return 0 as the length
	Sleep(1000);

	memset(msg,0,ASIM_MAX_OUT);
	if (handle == NULL)
	{
		if(debug>=FILE_ECHO)
		{
			fprintf(echo,"ERROR: Bad handle\n");
		}
		return ASIM_ERROR;
	}
	unsigned char pipenum = ASIM_IN_PIPE;
	if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_READ, &pipenum, sizeof(pipenum), msg, ASIM_MAX_OUT, &result, NULL))
		return NULL;	/*If there is nothing to read, don't report an error, just return with NULL*/
	if (result < 0)
	{
		if(debug>=FILE_ECHO)
		{
			fprintf(echo,"ERROR: %s\n",strerror(errno));
		}
		if(errno==110)
			return ASIM_TIMEOUT;
		return ASIM_ERROR;
	}
	msg_type = msg[0];			//save message type

	if (msg_type == ASIM_VERSION)		//version needed to know endianness of length
	{
		//set version
		version = msg[3];
	}

	//get length based on version
	if(version != NO_VERSION)
	{
		length = msg[2] + (msg[1] << 8);	//length is big endian, convert to host byte order
	}
	else
	{
		length = msg[1] + (msg[2] << 8);	//length is little endian, convert to host byte order
	}
	bytes_so_far = result - 3;		//bytes read is the total number - header

	if (result >= 3)
		memcpy(data,msg+3,result-3);		//store data bytes

	if (msg_type == ASIM_STATUS)		//status always has length 1
	{					//but may occur before a version
		length = 1;			//possibly giving a wrong value of 256
	}

	while(length > bytes_so_far)		//continue reading data
	{
		Sleep(100);		/*Allow time for the ASIM to get data*/
		pipenum = ASIM_IN_PIPE;
		/*If the ASIM doesn't hasn't gotten around to saying anything, it will return zero as result, and should be read again.*/
		if (!DeviceIoControl(handle, IOCTL_ASIM_BULK_READ, &pipenum, sizeof(pipenum), msg, ASIM_MAX_OUT, &result, NULL))
			continue;
		memcpy(data+bytes_so_far,msg,result);	//store data bytes
		bytes_so_far+=result;
	}

	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message rec'd :");
		for(int i=0;i<length+3;i++)
			fprintf(echo," %hhd",msg[i]);
		fprintf(echo,"\n");
	}
	return msg_type;
}

bool ASIM::VerifyConnection(void)
{
	HANDLE verification_handle = NULL;
	verification_handle = CreateFile(devicename, GENERIC_READ|GENERIC_WRITE, FILE_SHARE_READ|FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 0, NULL);
	if (verification_handle == NULL)
		return false;
	CloseHandle(verification_handle);
	return true;
}

char* ASIM::USBLocation(void)
{
	char temp_usb[80];
	int start_usb_location;
	long result = 0;

	//initialize
	memset(temp_usb,0,80);
	memset(usb_location,0,80);
	//request USB path
#ifndef WIN32
	result = ioctl(handle, ASIM_PATH, temp_usb);
#endif

//strip unnecessary info
	for(int i = 0; i < 80; ++i) // cleanup issue 34
  {
	  if (temp_usb[i]==' ')
    {
        start_usb_location = i;
        break;
    }
  }
  if (start_usb_location > 0)
  {
    ++start_usb_location;
	  //copy to usb member variable
    strncpy(usb_location,temp_usb+start_usb_location,79);
  }
	return usb_location;
}

void ASIM::SetDebug(int d)
{
	debug = d;
}


