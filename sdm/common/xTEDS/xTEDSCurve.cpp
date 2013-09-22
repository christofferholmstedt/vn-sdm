#include "xTEDSCurve.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSCurve::xTEDSCurve():m_strName(NULL),m_strDescription(NULL),m_xclCoefs()
{
}

/*xTEDSCurve::xTEDSCurve(const xTEDSCurve& b):m_strName(NULL),m_strDescription(NULL),m_xclCoefs()
{
	if(m_strName!=NULL) free(m_strName);
	m_strName = strdup(b.m_strName);
	if(m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(b.m_strDescription);
	//if(coefs!=NULL) free(coefs);
	//coefs = strdup(b.coefs);
}

xTEDSCurve& xTEDSCurve::operator=(const xTEDSCurve& b)
{
	if(m_strName!=NULL) free(m_strName);
	m_strName = strdup(b.m_strName);
	if(m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(b.m_strDescription);
	//if(coefs!=NULL) free(coefs);
	//coefs = strdup(b.coefs);
	return *this;
}*/

xTEDSCurve::~xTEDSCurve()
{
	if(m_strName!=NULL) free(m_strName);
	if(m_strDescription!=NULL) free(m_strDescription);
}

void xTEDSCurve::setCurve(const curve* NewCurve)
{
	if (NewCurve == NULL) return;
	setName(NewCurve->name);
	setDescription(NewCurve->description);
	m_xclCoefs.setCoefList(NewCurve->coefs);
}

void xTEDSCurve::setName(const char* new_name)
{
	if (new_name == NULL) return;
	if(m_strName!=NULL) free(m_strName);
	m_strName = strdup(new_name);
}

void xTEDSCurve::setDescription(const char* new_description)
{
	if (new_description == NULL) return;
	if(m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(new_description);
}

void xTEDSCurve::VarInfoRequest( char* InfoBufferOut, size_t BufferSize ) const
{
	char Buf[MSG_DEF_SIZE];
	
	if (m_strName == NULL)
		return ;
	
	if(m_strDescription != NULL)
	{
		snprintf(Buf, sizeof(Buf), "<Curve name=\"%s\" description=\"%s\"",m_strName, m_strDescription);
	}
	else
	{
		snprintf(Buf, sizeof(Buf), "<Curve name=\"%s\"", m_strName);
	}
	if(m_xclCoefs.IsEmpty())
	{
		strncat(Buf, "/>", sizeof(Buf) - strlen(Buf));
	}
	else
	{
		strncat(Buf, ">", sizeof(Buf) - strlen(Buf));
		
		size_t CurBufLength = strlen(Buf);
		m_xclCoefs.VarInfoRequest(Buf + CurBufLength, sizeof(Buf) - CurBufLength);
		
		strncat(Buf, "\n\t</Curve>", sizeof(Buf) - strlen(Buf));
	}
	strncat(InfoBufferOut, Buf, BufferSize - 1);
}

