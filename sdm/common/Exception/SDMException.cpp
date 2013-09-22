#include "SDMException.h"

SDMException::SDMException()
{
	m_strMessage[0] = '\0';
}

SDMException::SDMException(const char* ExceptionMessage)
{
	strncpy(m_strMessage, ExceptionMessage, sizeof(m_strMessage));
}

SDMException::~SDMException()
{}

const char* SDMException::Message() const
{
	return m_strMessage;
}

