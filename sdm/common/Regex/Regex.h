#ifndef _SDM_REGEX_H_
#define _SDM_REGEX_H_

#include "../sdmLib.h"
#include "RegexResult.h"
#include "RegularExpression.h"

#ifdef  __VXWORKS__
#include "pcreposix.h"
#endif

// The maximum number of captures to return
const int MAX_CAPTURES = 6;

// Do not change the below value(s)
const int INVALID_CAPTURE = -1;


SDMLIB_API
RegexResult RegexSearchCapturesOnly(const char* SourceText, const RegularExpression& Pattern);
SDMLIB_API
bool DoesRegexMatch(const char* SourceText, const char* Pattern);
SDMLIB_API
bool IsPatternValid(const char* PatternText);

#endif
