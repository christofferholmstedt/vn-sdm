// Task classes implementation

#include "task.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Task::Task():pmComponentID(),state('\0'),priority('\0'),pid(PID_INVALID),resources(0),filename(NULL),timeout(0),taskMode(MODE_NORMAL)
{
	InitTask();
}

Task::Task(const Task& a):pmComponentID(a.pmComponentID), state(a.state), priority(a.priority), pid(a.pid), resources(a.resources), filename(strdup(a.filename)),timeout(a.timeout),taskMode(a.taskMode)
{
}

Task::~Task()
{
	if(filename != NULL)
		free(filename);
}

void Task::InitTask()
{
	resources = 0;
	pid = PID_INVALID;
	filename = NULL;
	state = INACTIVE;
	priority = 0;
	pmComponentID.setAddress(0);
	pmComponentID.setSensorID(0);
	pmComponentID.setPort(0);
	timeout = 0;
	taskMode = MODE_NORMAL;
}

void Task::Delete()
{
	if (filename != NULL)
		free(filename);
	InitTask();
}

void Task::SetTask (char s, char pr, unsigned int p, const SDMTaskResources& r, char *f, int atimeout, int aMode)
{
	resources = r;
	free (filename);
	filename = (char *) malloc(strlen(f)+1);
	strcpy (filename, f);
	state = s;
	pid = p;
	priority = pr;
	timeout = atimeout;
	taskMode = aMode;
}

Task& Task::operator= (const Task& t)
{
	Delete();
	SetTask (t.state, t.priority, t.pid, t.resources, t.filename, t.timeout, t.taskMode);
	return *this;
}

void Task::SetPM(const SDMComponent_ID& PM)
{
	pmComponentID = PM;
}
