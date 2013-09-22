#ifndef __ASIM_CLASS_H_
#define __ASIM_CLASS_H_

#include "asim_commands.h"
#include "../asim.h"

#include <sys/ioctl.h>
#include <stdio.h>
typedef void * HANDLE;

#include "../sdmLib.h"

class SDMLIB_API ASIM
{
public:
	ASIM();
	ASIM(char*);
	ASIM(const ASIM&);
	ASIM& operator=(const ASIM&);
	bool Open(char*);
	void Close();
	bool Initialize(void);
	bool Reset(void);
	bool SelfTest(void);
	bool ReqData(unsigned char interface_id,unsigned char msg_id,long ip,short port);
	bool ReqData(unsigned char interface_id,unsigned char msg_id);
	bool Cancel(unsigned char interface_id,unsigned char msg_id);
	bool ReqStream(unsigned char interface_id,unsigned char msg_id,long count);
	bool PowerOn(void);
	bool PowerDown(void);
	bool ReqVersion(void);
	bool Command(unsigned char interface_id,unsigned char msg_id,short length,unsigned char* data);
	bool ReqxTEDS(void);
	bool TimeAtTone(long sec,long usec);
	char Read(unsigned short& length,unsigned char* buf,int buflen);
	int RawRead(unsigned char* buf);
	bool VerifyConnection();
	char* USBLocation();
	void SetDebug(int);
private:
	HANDLE handle;
	int debug;
	unsigned char version;
	char usb_location[80];
	char devicename[20];
	FILE* echo;
};

#endif

