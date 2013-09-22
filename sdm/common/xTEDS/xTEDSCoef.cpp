#include "xTEDSCoef.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSCoef::xTEDSCoef():m_strDescription(NULL),m_strValue(NULL),m_strExponent(NULL)
{
}

/*(xTEDSCoef::xTEDSCoef(const xTEDSCoef& b):m_strDescription(NULL),m_strValue(NULL),m_strExponent(NULL)
{
	if(m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(b.m_strDescription);
	if(m_strValue!=NULL) free(m_strValue);
	m_strValue = strdup(b.m_strValue);
	if(m_strExponent!=NULL) free(m_strExponent);
	m_strExponent = strdup(b.m_strExponent);
}
xTEDSCoef& xTEDSCoef::operator=(const xTEDSCoef& b)
{
	if(m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(b.m_strDescription);
	if(m_strValue!=NULL) free(m_strValue);
	m_strValue = strdup(b.m_strValue);
	if(m_strExponent!=NULL) free(m_strExponent);
	m_strExponent = strdup(b.m_strExponent);
	return *this;
}*/

xTEDSCoef::~xTEDSCoef()
{
	if(m_strDescription!=NULL) free(m_strDescription);
	if(m_strValue!=NULL) free(m_strValue);
	if(m_strExponent!=NULL) free(m_strExponent);
}

void xTEDSCoef::setDescription(const char* new_description)
{
	if (new_description == NULL) return;
	if(m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(new_description);
}

void xTEDSCoef::setValue(const char* new_value)
{
	if (new_value == NULL) return;
	if(m_strValue!=NULL) free(m_strValue);
	m_strValue = strdup(new_value);
}

void xTEDSCoef::setExponent(const char* new_exponent)
{
	if (new_exponent == NULL) return;
	if(m_strExponent!=NULL) free(m_strExponent);
	m_strExponent = strdup(new_exponent);
}

void xTEDSCoef::setCoef(const coef* NewCoef)
{
	if (NewCoef == NULL) return;
	
	setExponent(NewCoef->exponent);
	setValue(NewCoef->value);
	setDescription(NewCoef->description);
}

void xTEDSCoef::VarInfoRequest( char* InfoBufferOut, size_t BufferSize ) const
{
	const unsigned int MAX_BUF_SIZE = 512;
	char Buf[MAX_BUF_SIZE], TempBuf[MAX_BUF_SIZE];
	
	if (m_strExponent == NULL || m_strValue == NULL) return ;
	
	snprintf(Buf, sizeof(Buf), "<Coef exponent=\"%s\" value=\"%s\"",m_strExponent,m_strValue);
	
	if(m_strDescription!=NULL)
	{
		snprintf(TempBuf, sizeof(TempBuf), " description=\"%s\"/>", m_strDescription);
		
		strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
	}
	else
		strncat(Buf, "/>", sizeof(Buf) - strlen(Buf));
	
	strncat(InfoBufferOut, Buf, BufferSize - 1);
}

