#ifndef __SDM_TASK_H_
#define __SDM_TASK_H_

#include "SDMmessage.h"

//This class is intended only for use by SDM core components

class SDMLIB_API SDMTask: public SDMmessage
{
public :
	SDMComponent_ID source;			//The source of the SDMTask message
	char priority;				//The priority level of the task (tbd)
	char filename[MAX_FILENAME_SIZE];	//The name of the task
	long pid;				//The process id of the task as assigned by the task manager
	int version;                            //Some identifying version number, if needed
	SDMTask();
	long Send(const SDMComponent_ID& destination);
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *buf, int length) const;
};

#endif
