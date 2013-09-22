#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>
#include "../Exception/SDMRegexException.h"
#include "Regex.h"

#ifdef __VXWORKS__
#include "pcreposix.h"
#endif

RegexResult RegexSearchCapturesOnly(const char* SourceText, const RegularExpression& Pattern)
{
	regmatch_t Match[MAX_CAPTURES]; // Information for each match
	RegexResult TheResult;
	RegexCapture CurCapture;
	RegexMatch CurMatch(MAX_CAPTURES);
	int SourceOffset = 0;
	bool CaptureAdded = false;
	while (regexec(&Pattern.Get(), SourceText + SourceOffset, MAX_CAPTURES, Match, 0) == 0)
	{
		if (Match[0].rm_so == 0 && Match[0].rm_eo == 0)
			break;
		//
		// Index i starts at 1, which is the start of the captures, index 0 is the entire match
		CaptureAdded = false;
		for (int i = 1; i < MAX_CAPTURES; i++)
		{
			if (Match[i].rm_so == INVALID_CAPTURE)
				break;

			CurCapture.SetCaptureText(SourceText + SourceOffset + Match[i].rm_so, Match[i].rm_eo - Match[i].rm_so);
			if (!CurMatch.AddCapture(CurCapture))
				printf("%s - Error adding capture %d!\n", __FUNCTION__, i);
			else
				CaptureAdded = true;
		}
		if (CaptureAdded)
		{
			TheResult.AddMatch(CurMatch);
			CurMatch.Clear();
		}
		// Match[0] is the matching for the entire regular expression
		// we want to skip ever looking at it again
		SourceOffset += Match[0].rm_eo;
	}
	return TheResult;
}

bool DoesRegexMatch(const char* SourceText, const char* PatternText)
{
	regex_t CompiledExpression;
	if (0 != regcomp(&CompiledExpression, PatternText, REG_EXTENDED))
		throw SDMRegexException("Invalid regular expression specified.\n");

	regmatch_t Match;
	bool Matched = false;
	if (regexec(&CompiledExpression, SourceText, 1, &Match, 0) == 0)
		Matched = true;

	regfree(&CompiledExpression);
	return Matched;
}

bool IsPatternValid(const char* PatternText)
{
	regex_t CompiledExpression;
	if (0 != regcomp(&CompiledExpression, PatternText, REG_EXTENDED))
		return false;
	regfree(&CompiledExpression);
	return true;
}
