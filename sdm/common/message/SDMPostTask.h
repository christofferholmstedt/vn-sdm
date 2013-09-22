#ifndef __SDM_POSTTASK_H_
#define __SDM_POSTTASK_H_

#include "SDMmessage.h"


class SDMLIB_API SDMPostTask: public SDMmessage
{
public :
	unsigned short resources;		//resource requirements of task
	char priority;				//meaning of priority is TBD
	int sched_interval;			//the time the TM waits until it posts the task
	int mode;
	int version;                            //specify a version number or location to run
	char filename[MAX_FILENAME_SIZE];	//filename of task to be executed
	SDMPostTask();
	long Send();
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *str_buf, int length) const;
};

#endif
