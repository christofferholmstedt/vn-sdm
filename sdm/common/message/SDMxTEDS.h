#ifndef __SDM_XTEDS_H_
#define __SDM_XTEDS_H_

#include "SDMmessage.h"

#define FILENAME_SIZE 85			// maximum filename length

#define MAX_XTEDS_SEQUENCE_VALUE	15
#define MAX_USB_PATH_SIZE		80
#define MAX_XTEDS_SIZE	(LARGE_MSG_BUFSIZE - 105)


class SDMLIB_API SDMxTEDS: public SDMmessage
{
public :
	SDMComponent_ID source;		//unique sensor id, applications need only set least significant byte
	char active;			//status of the xTEDS (active or inactive), default is active
	char xTEDS[MAX_XTEDS_SIZE];		//the xTEDS to be registered with the SDM system
	char SPA_node[MAX_USB_PATH_SIZE];		//path through USB network to device from sensor manager, NULL for applications
	long pid;			//SDM process id of xTEDS provider
	SDMxTEDS();
	long Send();
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	long getPID(void);
	void setPID(void);
	int MsgToString(char *str_buf, int length) const;
};

#endif
