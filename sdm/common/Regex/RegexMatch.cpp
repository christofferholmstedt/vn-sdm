#include "../MemoryUtils.h"
#include "RegexMatch.h"

RegexMatch::RegexMatch() : m_Captures(NULL), m_iNumCaptures(0), m_iCurCaptureIndex(0)
{
}

RegexMatch::RegexMatch(int MaxCaptureSize) : m_Captures(NULL), m_iNumCaptures(0), m_iCurCaptureIndex(0)
{
	SetMaxCaptureSize(MaxCaptureSize);
}

RegexMatch::RegexMatch(const RegexMatch& Right) : m_Captures(NULL), m_iNumCaptures(0), m_iCurCaptureIndex(0)
{
	if (Right.m_iNumCaptures != 0)
	{
		this->m_Captures = new RegexCapture[Right.m_iNumCaptures];
		
		for (int i = 0; i < m_iNumCaptures; i++)
			this->m_Captures[i] = Right.m_Captures[i];
		
		this->m_iCurCaptureIndex = Right.m_iCurCaptureIndex;
	}
}

RegexMatch::~RegexMatch()
{
	DeleteCaptures();
}

RegexMatch& RegexMatch::operator= (const RegexMatch& Right)
{
	DeleteCaptures();
	
	if (Right.m_iNumCaptures != 0)
	{
		this->m_iNumCaptures = Right.m_iNumCaptures;
		this->m_Captures = new RegexCapture[Right.m_iNumCaptures];
		
		for (int i = 0; i < m_iNumCaptures; i++)
			this->m_Captures[i] = Right.m_Captures[i];
		
		this->m_iCurCaptureIndex = Right.m_iCurCaptureIndex;
	}
	return *this;
}

void RegexMatch::DeleteCaptures()
{
	if (m_Captures != NULL)
	{
		delete [] m_Captures;
		m_Captures = NULL;
		m_iNumCaptures = 0;
		m_iCurCaptureIndex = 0;
	}
}

void RegexMatch::SetMaxCaptureSize(int NewSize)
{
	DeleteCaptures();
	
	m_Captures = new RegexCapture[NewSize];
	
	m_iNumCaptures = NewSize;
	m_iCurCaptureIndex = 0;
}

bool RegexMatch::AddCapture(const RegexCapture& NewCapture)
{
	if (m_Captures == NULL)
		return false;
	if (m_iCurCaptureIndex+1 == m_iNumCaptures || m_iCurCaptureIndex < 0)
		return false;
	
	m_Captures[m_iCurCaptureIndex++] = NewCapture;
	return true;
}

const RegexCapture& RegexMatch::operator[] (int Index) const
{
	return m_Captures[Index];
}

int RegexMatch::FillMatchText(char* InputBuffer, int InputBufferSize) const
{
	int CurOffset = 0;
	
	for (int i = 0; i < m_iCurCaptureIndex; i++)
	{
		strncpy(InputBuffer + CurOffset, m_Captures[i].GetCaptureText(), InputBufferSize - CurOffset);
		// +1 assures the null termintor is not overwritten
		CurOffset += strlen(InputBuffer + CurOffset) + 1;
	}
	
	// Double null-terminate the last capture
	if (InputBufferSize - CurOffset >= 1)
		InputBuffer[++CurOffset] = '\0';
	
	return CurOffset;
}

void RegexMatch::Clear()
{
	m_iCurCaptureIndex = 0;
}

