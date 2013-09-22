#ifndef _SDM_REGEX_CAPTURE_H_
#define _SDM_REGEX_CAPTURE_H_

#include "../sdmLib.h"

class SDMLIB_API RegexCapture
{
public:
	RegexCapture();
	~RegexCapture();
	RegexCapture(const RegexCapture& Right);
	RegexCapture& operator=(const RegexCapture& Right);
	
	bool SetCaptureText(const char* NewCaptureText, int Length);
	const char* GetCaptureText() const;
private:
	char* m_strCaptureText;
};

#endif

