#ifndef __SDM_TASK_RESOURCES_H_
#define __SDM_TASK_RESOURCES_H_

#include "taskdefs.h"
#include "../sdmLib.h"

class SDMLIB_API SDMTaskResources
{
public:
	SDMTaskResources();
	SDMTaskResources(unsigned short usResources);
	SDMTaskResources(const SDMTaskResources& other);
	
	void Set(unsigned short usResources);
	void SetPreferredPmNodeId(unsigned short newPmId) 
		{ m_usResources &= (ARCHMASK|MEMMASK|OSMASK); m_usResources |= PM_ID(newPmId); }
	SDMTaskResources& operator=(const SDMTaskResources& other);
	
	bool IsPreferredPmIdSet() const { return ((m_usResources & PMIDMASK) != 0); }
	unsigned short GetPreferredPmId() const { return (m_usResources & PMIDMASK); }
	unsigned char GetPreferredPmIdNum() const { return ((m_usResources & PMIDMASK) >> 8); }
	unsigned short GetArch() const { return (m_usResources & ARCHMASK); }
	unsigned short GetMem() const { return (m_usResources & MEMMASK); }
	unsigned short GetOs() const { return (m_usResources & OSMASK); }
	unsigned short GetIgnorePmId() const { return (m_usResources & (ARCHMASK|MEMMASK|OSMASK)); }
	unsigned short GetUShort() const { return m_usResources; }

	void SetArch(unsigned short usArch)
	{ m_usResources &= (PMIDMASK|MEMMASK|OSMASK); m_usResources|= (usArch&ARCHMASK); }
	void SetMem(unsigned short usMem)
	{ m_usResources &= (PMIDMASK|ARCHMASK|OSMASK); m_usResources |= (usMem&MEMMASK); }
	void SetOs(unsigned short usOs)
	{ m_usResources &= (PMIDMASK|ARCHMASK|MEMMASK); m_usResources |= (usOs&OSMASK); }
	
	static bool MatchResources (const SDMTaskResources& Pm, const SDMTaskResources& Task);
private:
	unsigned short m_usResources;
};

#endif

