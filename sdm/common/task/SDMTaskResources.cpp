#include "SDMTaskResources.h"

SDMTaskResources::SDMTaskResources() : m_usResources(0)
{
}

SDMTaskResources::SDMTaskResources(unsigned short usResources) : m_usResources(usResources)
{
}

SDMTaskResources::SDMTaskResources(const SDMTaskResources& other) : m_usResources(other.m_usResources)
{
}

SDMTaskResources& SDMTaskResources::operator=(const SDMTaskResources& other)
{
	m_usResources = other.m_usResources;
	return *this;
}

void SDMTaskResources::Set(unsigned short usResources)
{
	m_usResources = usResources;
}

bool SDMTaskResources::MatchResources (const SDMTaskResources& pmResources, const SDMTaskResources& taskResources)
{
	if (taskResources.IsPreferredPmIdSet())
		if (pmResources.GetPreferredPmId() != taskResources.GetPreferredPmId())
			return false;
	
	if (pmResources.GetArch() == taskResources.GetArch())
		if (pmResources.GetMem() >= taskResources.GetMem())
			if (pmResources.GetOs() == taskResources.GetOs())
				return true;
	return false;
}
