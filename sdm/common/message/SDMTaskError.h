#ifndef __SDM_TASK_ERROR_H_
#define __SDM_TASK_ERROR_H_

#include "SDMmessage.h"

//This class is intended only for use by SDM core components

class SDMLIB_API SDMTaskError : public SDMmessage
{
public:
	SDMComponent_ID source;			//The PM on which the finished task resides
	int status;				//The status of the error
	char filename[MAX_FILENAME_SIZE];	//The name of the task
	unsigned int pid;
	SDMTaskError();
	long Send();
	long Marshal (char* buf);
	long Unmarshal (const char* buf);
	int MsgToString(char *str_buf, int length) const;
};


#endif
