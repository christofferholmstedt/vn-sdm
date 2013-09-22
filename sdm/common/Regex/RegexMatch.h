#ifndef _SDM_REGEX_MATCH_H_
#define _SDM_REGEX_MATCH_H_

#include "../sdmLib.h"
#include "RegexCapture.h"

class SDMLIB_API RegexMatch
{
public:
	RegexMatch();
	RegexMatch(int MaxCaptureSize);
	RegexMatch(const RegexMatch& Right);
	~RegexMatch();
	RegexMatch& operator=(const RegexMatch& Right);
	
	void SetMaxCaptureSize(int Size);
	bool AddCapture(const RegexCapture& NewCapture);
	const RegexCapture& operator[] (int index) const;
	int FillMatchText (char* InputBuffer, int InputBufferSize) const;
	void Clear();
private:
	void DeleteCaptures();
	RegexCapture* m_Captures;
	int m_iNumCaptures;
	int m_iCurCaptureIndex;
};

#endif

