#include "ASIM.h"
#include "../marshall.h"
#include "../Time/SDMTime.h"

#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>

#ifdef __VXWORKS__
#include <ioLib.h>
#endif

#define NO_VERSION	0xFF
#define FILE_ECHO	4

ASIM::ASIM():handle(-1),debug(0),version(NO_VERSION),echo(NULL)
{
}

ASIM::ASIM(char* devicename):handle(-1),debug(0),version(NO_VERSION),echo(NULL)
{
	Open(devicename);
}

ASIM::ASIM(const ASIM& b):handle(b.handle),debug(b.debug),version(b.version),echo(b.echo)

{
	strncpy(usb_location,b.usb_location,80);
	strncpy(devicename,b.devicename,20);
}

ASIM::~ASIM()
{
  if(handle>0)
		close(handle);
	handle = -1;

	if(debug>=FILE_ECHO)
	{
		fclose(echo);
	}
}  

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
	handle=open (devicename, O_RDWR);
	if (handle < 0)
	{
		if (errno!=ENOENT)
			perror(devicename);
		if(debug>=FILE_ECHO)
		{
			fprintf(echo,"%s: %s\n",devicename,strerror(errno));
		}
		return false;
	}
	ioctl(handle, ASIM_TIMEOUT_SEC, 10);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"device: %s (%s)\n",devicename,USBLocation());
		fflush(echo);
	}
	return true;
}

void ASIM::Close(void)
{
	if(handle>0)
		close(handle);
	handle = -1;

	if(debug>=FILE_ECHO)
	{
		fclose(echo);
	}
}

bool ASIM::Initialize(void)
{
	char msg[8];
	long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_INITIALIZE;
	msg[1] = msg[2] = 0;
	result = write(handle,msg,3);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_RESET;
	msg[1] = msg[2] = 0;
	result =write(handle,msg,3);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_SELF_TEST;
	msg[1] = msg[2] = 0;
	result =write(handle,msg,3);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	long result = 0;

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
	result =write(handle,msg,11);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_CANCEL;
	length = htons(length);	//length needs to be big-endian
	memcpy(msg+1,&length,2);
	msg[3] = interface_id;
	msg[4] = msg_id;
	result =write(handle,msg,5);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	long result = 0;
	memset(msg,0,16);
	msg[0] = ASIM_REQ_STREAM;
	length = htons(length);		//length needs to be big-endian
	memcpy(msg+1,&length,2);
	msg[3] = interface_id;
	msg[4] = msg_id;
	le_count = SDM_htonl(count);	//count needs to be little-endian
	memcpy(msg+5,&le_count,4);
	result =write(handle,msg,9);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_POWER_ON;
	result = write(handle,msg,3);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_POWER_DOWN;
	msg[1] = msg[2] = 0;
	result = write(handle,msg,3);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_REQ_VERSION;
	msg[1] = msg[2] = 0;
	result =write(handle,msg,3);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	const unsigned short DataOffset = 5;
	short be_length;	//length needs to be big endian in message
	long result = 0;
	if (static_cast<unsigned int>(length + DataOffset) > sizeof(msg) || length < 0)
		return false;
	memset(msg,0,64);
	msg[0] = ASIM_COMMAND;
	be_length = length + 2; //add two bytes for interface_id and msg_id
	be_length = htons(be_length);
	memcpy(msg+1,&be_length,2);
	msg[3] = interface_id;
	msg[4] = msg_id;
	memcpy(msg+5,data,length);
	result =write(handle,msg,5+length);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	long result = 0;
	memset(msg,0,8);
	msg[0] = ASIM_REQ_XTEDS;
	msg[1] = msg[2] = 0;
	result =write(handle,msg,3);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	long result = 0;
	memset(msg,0,16);
	msg[0] = ASIM_TIME_AT_TONE;
	length = htons(length);		//length needs to be big-endian
	PUT_SHORT(&msg[1],length);
	PUT_LONG(&msg[3],sec);
	PUT_LONG(&msg[7],usec);
	result = write(handle,msg,11);
	if(debug>=FILE_ECHO)
	{
		fprintf(echo,"message sent  (%c,%ld): ",msg[0],result);
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
	result = read(handle,msg,ASIM_MAX_OUT);	//read first data message
	if (result < 0)
	{
		if(debug>=FILE_ECHO)
		{
			fprintf(echo,"ERROR: %s\n",strerror(errno));
		}
		if(errno==110)
			return -1;
		return -1;
	}
	memcpy(data,msg,result);
	return result;
}

char ASIM::Read(unsigned short& length, unsigned char* data, unsigned int buflength)
{
	unsigned char msg[ASIM_MAX_OUT];	//buffer for message
	unsigned char msg_type;			//first character of message
	unsigned char header_buf[3];		//save the header for debug output
	long result = 0;			//result of a read
	int bytes_so_far;			//number of bytes read so far
	int bytes_received = 0;
	length = 0;				//if an error occurs before the length field
						//can be read return 0 as the length

	memset(msg,0,ASIM_MAX_OUT);
	if (handle < 0)
	{
		if(debug>=FILE_ECHO)
		{
			fprintf(echo,"ERROR: Bad handle\n");
		}
		return ASIM_ERROR;
	}
	// Be sure that we at least get a header
	while (bytes_received < 3)
	{
		result = read(handle,msg+bytes_received,ASIM_MAX_OUT-bytes_received);	//read first data message
		if (result <= 0)
		{
			if(debug>=FILE_ECHO)
			{
				fprintf(echo,"ERROR: %s\n",strerror(errno));
			}
			//Some version of the ASIM driver will return zero bytes
			if(result == 0 || errno==110)
				return ASIM_TIMEOUT;
			return ASIM_ERROR;
		}
		else
			bytes_received += result;
	}
	msg_type = msg[0];			//save message type
	// Save the header for debug output
	for (unsigned int i = 0; i < sizeof(header_buf); i++)
		header_buf[i] = msg[i];

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
	bytes_so_far = bytes_received - 3;		//bytes read is the total number - header

	if (bytes_received >= 3)
		memcpy(data,msg+3,bytes_received-3);		//store data bytes

	if (msg_type == ASIM_STATUS)		//status always has length 1
	{					//but may occur before a version
		length = 1;			//possibly giving a wrong value of 256
	}
	if (length > buflength)
	{
		if (debug >= FILE_ECHO)
			fprintf(echo, "ERROR:  Produced message with invalid length %d bytes.",length);
		return ASIM_ERROR;
	}
	while(length > bytes_so_far)		//continue reading data
	{
		result = read(handle,msg,ASIM_MAX_OUT);
		if (result <= 0)
		{
			if(debug>=FILE_ECHO)
			{
				fprintf(echo,"ERROR: %s\n",strerror(errno));
			}
			if(errno==110)
				return ASIM_TIMEOUT;
			//Some versions of the ASIM driver will return zero bytes
			if (result == 0)
			{
				usleep(100);
				continue;
			}
			return ASIM_ERROR;
		}
		memcpy(data+bytes_so_far,msg,result);	//store data bytes
		bytes_so_far+=result;
	}

	if(debug>=FILE_ECHO)
	{
		// Output header
		fprintf(echo,"message rec'd (%c,%hu): %hhx %hhx %hhx ",header_buf[0], length+3, header_buf[0], header_buf[1], header_buf[2]);
		// Output body
		for(int i=0;i<length;i++)
		{
			if ((msg_type == ASIM_XTEDS || msg_type == ASIM_XTEDS_ID_PAIR) && (isprint(data[i]) || isspace(data[i])))
				fprintf(echo,"%c",data[i]);
			else
				fprintf(echo," %hhx",data[i]);
		}
		fprintf(echo,"\n");
		fflush(echo);
	}
	return msg_type;
}

bool ASIM::VerifyConnection(void)
{
	int status,product;
	long verification_handle;
	verification_handle = open (devicename, O_RDWR);
	if (verification_handle < 0)
	{
		close(verification_handle);
		return false;
	}
	status = ioctl (verification_handle, ASIM_PRODUCT_ID, &product);
	close(verification_handle);
	if (verification_handle < 0) return false;
	//if (product == 2) return false;
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
	result = ioctl(handle, ASIM_PATH, temp_usb);
	//strip unnecessary info
	for(start_usb_location = 0;start_usb_location<80;++start_usb_location)
		if (temp_usb[start_usb_location]==' ') break;
	++start_usb_location;
	//copy to usb member variable
	strncpy(usb_location,temp_usb+start_usb_location,79);
	return usb_location;
}

void ASIM::SetDebug(int d)
{
	debug = d;
}


