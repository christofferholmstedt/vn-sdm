#ifndef SDM_PM_RECORD
#define SDM_PM_RECORD

#include "../common/message/SDMComponent_ID.h"
#include "../common/task/SDMTaskResources.h"

class pm_record
{
public:
	pm_record();
	pm_record(const pm_record &b);
	pm_record& operator=(const pm_record& b);
	~pm_record();
	SDMComponent_ID component_id;
	SDMTaskResources resources;
	short tasks;
	bool in_use;
};

#endif
