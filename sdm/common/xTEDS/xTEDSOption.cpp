#include "xTEDSOption.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSOption::xTEDSOption():m_strName(NULL),m_strDescription(NULL),m_strValue(NULL),m_strAlarm(NULL)
{
}

/*xTEDSOption::xTEDSOption(const xTEDSOption& b):m_strName(NULL),m_strDescription(NULL),m_strValue(NULL),m_strAlarm(NULL)
{
	if(m_strName!=NULL) free(m_strName);
	m_strName = strdup(b.m_strName);
	if(m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(b.m_strDescription);
	if(m_strValue!=NULL) free(m_strValue);
	m_strValue = strdup(b.m_strValue);
	if(m_strAlarm!=NULL) free(m_strAlarm);
	m_strAlarm = strdup(b.m_strAlarm);
}

xTEDSOption& xTEDSOption::operator=(const xTEDSOption& b)
{
	if(m_strName!=NULL) free(m_strName);
	m_strName = strdup(b.m_strName);
	if(m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(b.m_strDescription);
	if(m_strValue!=NULL) free(m_strValue);
	m_strValue = strdup(b.m_strValue);
	if(m_strAlarm!=NULL) free(m_strAlarm);
	m_strAlarm = strdup(b.m_strAlarm);
	return *this;
}
*/

xTEDSOption::~xTEDSOption()
{
	if(m_strName!=NULL) free(m_strName);
	if(m_strDescription!=NULL) free(m_strDescription);
	if(m_strValue!=NULL) free(m_strValue);
	if(m_strAlarm!=NULL) free(m_strAlarm);
}

void xTEDSOption::setName(const char* new_name)
{
	if (new_name == NULL) return;
	if(m_strName!=NULL) free(m_strName);
	m_strName = strdup(new_name);
}

void xTEDSOption::setDescription(const char* new_description)
{
	if (new_description == NULL) return;
	if(m_strDescription!=NULL) free(m_strDescription);
	m_strDescription = strdup(new_description);
}

void xTEDSOption::setValue(const char* new_value)
{
	if (new_value == NULL) return;
	if(m_strValue!=NULL) free(m_strValue);
	m_strValue = strdup(new_value);
}

void xTEDSOption::setAlarm(const char* new_alarm)
{
	if (new_alarm == NULL) return;
	if(m_strAlarm!=NULL) free(m_strAlarm);
	m_strAlarm = strdup(new_alarm);
}

void xTEDSOption::setOption(const curveoption* Option)
{
	if (Option == NULL) return;
	setName(Option->name);
	setValue(Option->value);
	setDescription(Option->description);
	setAlarm(Option->alarm);
}

void xTEDSOption::VarInfoRequest( char* InfoBufferOut, size_t BufferSize ) const
{
	const unsigned int MAX_BUF_SIZE = 512;
	char Buf[MAX_BUF_SIZE], TempBuf[MAX_BUF_SIZE];
	
	if (m_strName == NULL || m_strValue == NULL) return ;
	
	snprintf(Buf, sizeof(Buf), "<Option name=\"%s\" value=\"%s\"",m_strName,m_strValue);
	
	if (m_strDescription != NULL)
	{
		snprintf(TempBuf, sizeof(TempBuf), " description=\"%s\"", m_strDescription);
		strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
	}
	if (m_strAlarm != NULL)
	{
		snprintf(TempBuf, sizeof(TempBuf), " alarm=\"%s\"", m_strAlarm);
		strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
	}
	strncat(Buf, "/>", sizeof(Buf) - strlen(Buf));
	
	strncat(InfoBufferOut, Buf, BufferSize - 1);
}

