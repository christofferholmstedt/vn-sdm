#include "xTEDSQualifier.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSQualifier::xTEDSQualifier(): m_strName(NULL), m_strDescription(NULL), m_strUnits(NULL)
{
}

xTEDSQualifier::xTEDSQualifier(char* pName, char* pDescription, char* pUnits): m_strName(NULL), m_strDescription(NULL), m_strUnits(NULL)
{
	setName(pName);
	setDescription(pDescription);
	setUnits(pUnits);
}

xTEDSQualifier::xTEDSQualifier(const xTEDSQualifier& right): m_strName(NULL), m_strDescription(NULL), m_strUnits(NULL)
{
	if (right.m_strName != NULL)
		m_strName = strdup(right.m_strName);
	if (right.m_strDescription != NULL)
		m_strDescription = strdup(right.m_strDescription);
	if (right.m_strUnits != NULL)
		m_strUnits = strdup(right.m_strUnits);
}

xTEDSQualifier::~xTEDSQualifier()
{
	if (m_strName != NULL)
		free (m_strName);
	if (m_strDescription != NULL)
		free (m_strDescription);
	if (m_strUnits != NULL)
		free (m_strUnits);
}

void xTEDSQualifier::setName(const char* new_name)
{
	if (new_name == NULL) return;
	if (m_strName != NULL) free(m_strName);
	m_strName = strdup(new_name);
}

void xTEDSQualifier::setDescription(const char* new_description)
{
	if (new_description == NULL) return;
	if (m_strDescription != NULL) free(m_strDescription);
	m_strDescription = strdup(new_description);
}

void xTEDSQualifier::setUnits(const char* new_units)
{
	if (new_units == NULL) return;
	if (m_strUnits != NULL) free(m_strUnits);
	m_strUnits = strdup(new_units);
}

const char* xTEDSQualifier::getName(void) const
{
	return m_strName;
}

const char* xTEDSQualifier::getDescription(void) const
{
	return m_strDescription;
}

const char* xTEDSQualifier::getUnits(void) const
{
	return m_strUnits;
}

bool xTEDSQualifier::MatchesName(const char* MatchString) const
{
	if (MatchString != NULL && strcmp(MatchString, m_strName)==0)
		return true;
	return false;
}

bool xTEDSQualifier::MatchesDescription(const char* MatchString) const
{
	if (MatchString != NULL && strcmp(MatchString, m_strDescription)==0)
		return true;
	return false;
}

/*xTEDSQualifier& xTEDSQualifier::operator=(const xTEDSQualifier& b)
{
	if(name!=NULL) free(name);
	name = strdup(b.name);
	if(description!=NULL) free(description);
	description = strdup(b.description);
	return *this;
}
xTEDSQualifier::xTEDSQualifier(const xTEDSQualifier& b)
{
	m_strName[0] = m_strDescription[0] = m_strUnits[0] = '\0';
	setName(b.m_strName);
	setDescription(b.m_strDescription);
	setUnits(b.m_strUnits);
}*/

bool xTEDSQualifier::Parse(const char* quals)
{
	char temp[128];
	size_t start = 0;
  size_t count = 0;
  size_t end = 0;

	int i;
	bool valid = false;

	count = strlen(quals);
	i=0;
	while(quals[i] != ' ' && quals[i] != '=' && quals[i] != '\0')
	{
		i++;
	}
	if(quals[i] != '\0')
		valid = true;
	end = i;
	if(valid)
	{
		strncpy(temp,quals,end);
		temp[end] = 0;
		setName(temp);
	}
	start = end;
	end = count;

	while(quals[start] != '"' && quals[start] != '\0')
	{
			start++;
	}
	if(quals[start] == '\0')
		valid = false;
	else
		start += 1;
	while(quals[end] != '"' && end > start)
	{
			end--;
	}
	if(end == start)
		valid = false;
	if(valid)
	{
		strncpy(temp,&quals[start],end-start);
		temp[end-start] = 0;
		setDescription(temp);
	}
	return valid;
}

void xTEDSQualifier::QualifierInfoRequest( char* InfoBufferOut, size_t BufferSize )
{
	char Buf[MSG_DEF_SIZE], TempBuf[512];
	size_t BufLength = 0;
	if (m_strName == NULL || m_strDescription == NULL)
		return ;
	
	BufLength = snprintf(Buf, sizeof(Buf), "<Qualifier name=\"%s\" value=\"%s\"", m_strName, m_strDescription);
	
	// Add units, if given
	if(m_strUnits != NULL)
	{
		snprintf(TempBuf, sizeof(TempBuf), " units=\"%s\"", m_strUnits);
		
		strncat(Buf, TempBuf, sizeof(Buf) - BufLength);
		BufLength = strlen(Buf);
	}
	// Close off the tag
	strncat(Buf, " />", sizeof(Buf) - BufLength);
	
	strncat(InfoBufferOut, Buf, BufferSize - 1);
}
