#include "pm_record.h"

pm_record::pm_record():component_id(),resources(0),tasks(0),in_use(false)
{
}

pm_record::pm_record(const pm_record & b):component_id(b.component_id),resources(b.resources),tasks(b.tasks),in_use(b.in_use)
{
}
pm_record::~pm_record()
{
}

pm_record& pm_record::operator= (const pm_record& b)
{
	resources = b.resources;
	tasks = b.tasks;
	in_use = b.in_use;
	component_id = b.component_id;
	return *this;
}
