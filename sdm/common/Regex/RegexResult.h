#ifndef _SDM_REGEX_RESULT_H_
#define _SDM_REGEX_RESULT_H_

#include "RegexMatch.h"
#include "../sdmLib.h"

class SDMLIB_API MatchListNode
{
public:
	MatchListNode() : MatchData(), Next(NULL) {}
	MatchListNode(const MatchListNode& Right);
	MatchListNode& operator=(const MatchListNode& Right);
	
	RegexMatch MatchData;
	MatchListNode* Next;
};

class SDMLIB_API RegexResult
{
public:
	RegexResult();
	~RegexResult();
	RegexResult(const RegexResult& Right);
	RegexResult& operator=(const RegexResult& Right);
	
	bool AddMatch(const RegexMatch& NewMatch);
	
	int NumMatches() const { return m_iNumMatches; }
	bool Matched() const { return m_iNumMatches != 0; }
	const RegexMatch& operator[] (int Index) const;
private:
	void DeleteList();
	MatchListNode* m_Head;
	int m_iNumMatches;
};

#endif

