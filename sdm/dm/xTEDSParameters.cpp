#include "xTEDSParameters.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <netinet/in.h>
extern "C"
{
#include "../common/MemoryUtils.h"
}
#ifdef WIN32
#include "unistd.h"
#endif

xTEDSParameters::xTEDSParameters():m_MessageData(NULL),m_iDataSize(0),m_idSender(),m_comHandle()
{
}

xTEDSParameters::xTEDSParameters(const xTEDSParameters& b):m_MessageData(NULL),m_iDataSize(0),m_idSender(),m_comHandle()
{
	m_MessageData = SDM_strndup(b.m_MessageData,b.m_iDataSize);
	m_iDataSize = b.m_iDataSize;
	m_idSender = b.m_idSender;
}

xTEDSParameters::xTEDSParameters(char* buffer, int length, const SDMComponent_ID& Sender, const SDMComHandle& ComHandle) 
	: m_MessageData(NULL),m_iDataSize(length),m_idSender(),m_comHandle(ComHandle)
{
	m_MessageData = (char*)malloc(length + 1);
	if(m_MessageData==NULL)
	{
		printf("Error in mallocing space for the xTEDS or Update!!!\n");
	}
  else
  {
	  memcpy(m_MessageData,buffer,length);
	  m_MessageData[length] = '\0';
  }	
	m_idSender = Sender;
}

xTEDSParameters::~xTEDSParameters()
{
	if(m_MessageData!=NULL) free(m_MessageData);
	m_comHandle.DoCleanup();
}

xTEDSParameters& xTEDSParameters::operator=(const xTEDSParameters& b)
{
	if(m_MessageData!=NULL) free(m_MessageData);
	m_MessageData = SDM_strndup(b.m_MessageData,b.m_iDataSize);
	m_iDataSize = b.m_iDataSize;
	m_idSender = b.m_idSender;
	return *this;
}
