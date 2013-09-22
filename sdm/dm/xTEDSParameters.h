#ifndef __XTEDS_PARAMETERS_H_
#define __XTEDS_PARAMETERS_H_

#include "../common/SDMComHandle.h"
#include "../common/message/SDMComponent_ID.h"

/*************************************************************************************************

	The xTEDSParameters class is used to pass data to various xTEDS handling threads and
	functions within the DataManager.  It contains the information needed for the address,
	socket, and buffers containing the needed data.

**************************************************************************************************/

class xTEDSParameters
{
public:
	xTEDSParameters();
	xTEDSParameters(const xTEDSParameters&);
	xTEDSParameters(char* buffer,int length,const SDMComponent_ID& Sender, const SDMComHandle& ComHandle);
	~xTEDSParameters();
	xTEDSParameters& operator=(const xTEDSParameters&);

	const char* getBuffer() const { return m_MessageData; }
	int getSize() const { return m_iDataSize; }
	const SDMComponent_ID& getSenderAddress() const { return m_idSender; }
	
	const SDMComHandle& GetComHandle() const { return m_comHandle; }
	void ComCleanup() { m_comHandle.DoCleanup(); }
private:
	char* m_MessageData;		//Buffer containing the data to pass
	int m_iDataSize;		//Size of the buffer
	SDMComponent_ID m_idSender;
	SDMComHandle m_comHandle;
};

#endif
