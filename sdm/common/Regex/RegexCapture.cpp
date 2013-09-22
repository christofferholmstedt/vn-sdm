#include <string.h>
#include <stdlib.h>
#include "RegexCapture.h"
extern "C"
{
#include "../MemoryUtils.h"
}
#ifdef WIN32
#  include "unistd.h"
#endif

RegexCapture::RegexCapture() : m_strCaptureText(NULL)
{
}

RegexCapture::~RegexCapture()
{
	if (m_strCaptureText != NULL)
		free(m_strCaptureText);
}

RegexCapture::RegexCapture(const RegexCapture& Right) : m_strCaptureText(NULL)
{
	if (Right.m_strCaptureText != NULL)
		//this->m_strCaptureText = SDM_strdup(Right.m_strCaptureText);
		this->m_strCaptureText = strdup(Right.m_strCaptureText);
}

RegexCapture& RegexCapture::operator= (const RegexCapture& Right)
{
	if (this->m_strCaptureText != NULL)
		free(this->m_strCaptureText);
	this->m_strCaptureText = NULL;
	
	if (Right.m_strCaptureText != NULL)
		//this->m_strCaptureText = SDM_strdup(Right.m_strCaptureText);
		this->m_strCaptureText = strdup(Right.m_strCaptureText);
	return *this;
}

bool RegexCapture::SetCaptureText(const char* NewCaptureText, int Length)
{
	if (m_strCaptureText != NULL)
		free(m_strCaptureText);
	
	m_strCaptureText = SDM_strndup(NewCaptureText, Length);
	return true;
}

const char* RegexCapture::GetCaptureText() const
{
	return m_strCaptureText;
}

