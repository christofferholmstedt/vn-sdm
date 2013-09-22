#ifndef __SDM_TASK_FINISHED_H_
#define __SDM_TASK_FINISHED_H_

#include "SDMmessage.h"

//This class is intended only for use by SDM core components

class SDMLIB_API SDMTaskFinished : public SDMmessage
{
public:
	SDMComponent_ID source;		//The PM on which the finished task resides
	int result;			//The result value of the task running
	char filename[MAX_FILENAME_SIZE];		//The name of the task finished
	int pid;
	SDMTaskFinished();
	long Send();
	long Marshal (char* buf);
	long Unmarshal (const char* buf);
	int MsgToString(char *str_buf, int length) const;
};


#endif
