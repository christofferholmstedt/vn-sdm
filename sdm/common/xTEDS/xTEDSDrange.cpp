#include "xTEDSDrange.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSDrange::xTEDSDrange():m_strName(NULL),m_strDescription(NULL),m_xolOptions()
{
}

/*	Not used..
xTEDSDrange::xTEDSDrange(const xTEDSDrange& b):m_strName(NULL),m_strDescription(NULL),m_xolOptions()
{
	if(b.m_strName!=NULL) free(m_strName);
	m_strName = strdup(b.m_strName);
	if(b.m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(b.m_strDescription);
	//TODO:  Option list not copied
}
xTEDSDrange& xTEDSDrange::operator=(const xTEDSDrange& b)
{
	if(m_strName!=NULL) free(m_strName);
	m_strName = strdup(b.m_strName);
	if(m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(b.m_strDescription);
	//TODO: Option list not copied
	return *this;
}*/


xTEDSDrange::~xTEDSDrange()
{
	if(m_strName!=NULL) free(m_strName);
	if(m_strDescription!=NULL) free(m_strDescription);
}

void xTEDSDrange::setName(const char* new_name)
{
	if (new_name == NULL) return;
	if(m_strName!=NULL) free(m_strName);
	m_strName = strdup(new_name);
}

void xTEDSDrange::setDescription(const char* new_description)
{
	if (new_description == NULL) return;
	if(m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(new_description);
}

void xTEDSDrange::setDRange(const drange* NewRange)
{
	setName(NewRange->name);
	setDescription(NewRange->description);
	m_xolOptions.setOptionsList(NewRange->options);
}

void xTEDSDrange::VarInfoRequest( char* InfoBufferOut, size_t BufferSize ) const
{
	char Buf[MSG_DEF_SIZE], TempBuf[512];
	
	if (m_strName == NULL)
		return ;
	
	snprintf(Buf, sizeof(Buf), "<Drange name=\"%s\"", m_strName);
	
	if (m_strDescription != NULL)
	{
		snprintf(TempBuf, sizeof(TempBuf), " description=\"%s\"", m_strDescription);
		
		strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
	}

	strncat(Buf, ">", sizeof(Buf) - strlen(Buf));

	size_t CurBufLength = strlen(Buf);
	m_xolOptions.VarInfoRequest(Buf + CurBufLength, sizeof(Buf) - CurBufLength);
		
	strncat(Buf, "\n\t</Drange>", sizeof(Buf) - strlen(Buf));
	
	strncat(InfoBufferOut, Buf, BufferSize - 1);
}
