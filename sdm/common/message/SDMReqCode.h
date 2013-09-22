#ifndef __SDM_REQCODE_H_
#define __SDM_REQCODE_H_

#include "SDMmessage.h"

//This class is intended only for use by SDM core components

class SDMLIB_API SDMReqCode : public SDMmessage
{
	public:
	char filename[MAX_FILENAME_SIZE];	//The name of the file wanted
	SDMComponent_ID source;			//The originator of the message
	unsigned short seq_num;		//The sequence from which code should be transferred
	int version;                    //Version of the code to request
	SDMReqCode();
	long Send();
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int length) const;
};

#endif
