#include "../MemoryUtils.h"
#include "RegexResult.h"
#include "../Exception/SDMBadIndexException.h"

RegexResult::RegexResult() : m_Head(NULL), m_iNumMatches(0)
{
}

RegexResult::~RegexResult()
{
	DeleteList();
}

RegexResult::RegexResult(const RegexResult& Right) : m_Head(NULL), m_iNumMatches(Right.m_iNumMatches)
{
	DeleteList();
	
	MatchListNode* PrevNode = NULL, *CurLeft = NULL;
	for (MatchListNode* CurRight = Right.m_Head; CurRight != NULL; CurRight = CurRight->Next)
	{
		if (PrevNode == NULL)
		{
			CurLeft = m_Head = new MatchListNode();
			//if (CurLeft == NULL)
			//	SDMMemoryAllocError(__FUNCTION__);
		}
		else
		{
			CurLeft = new MatchListNode();
			//if (CurLeft == NULL)
			//	SDMMemoryAllocError(__FUNCTION__);
			PrevNode->Next = CurLeft;
		}
		
		CurLeft->MatchData = CurRight->MatchData;
		PrevNode = CurLeft;
	}
}

RegexResult& RegexResult::operator=(const RegexResult& Right)
{
	DeleteList();
	
	MatchListNode* PrevNode = NULL, *CurLeft = NULL;
	for (MatchListNode* CurRight = Right.m_Head; CurRight != NULL; CurRight = CurRight->Next)
	{
		if (PrevNode == NULL)
		{
			CurLeft = m_Head = new MatchListNode();
			//if (CurLeft == NULL)
			//	SDMMemoryAllocError(__FUNCTION__);
		}
		else
		{
			CurLeft = new MatchListNode();
			//if (CurLeft == NULL)
			//	SDMMemoryAllocError(__FUNCTION__);
			PrevNode->Next = CurLeft;
		}
		
		CurLeft->MatchData = CurRight->MatchData;
		PrevNode = CurLeft;
	}
	this->m_iNumMatches = Right.m_iNumMatches;
	return *this;
}

void RegexResult::DeleteList()
{
	for (MatchListNode* Cur = m_Head; Cur != NULL; )
	{
		MatchListNode* Next = Cur->Next;
		delete Cur;
		Cur = Next;
	}
	m_Head = NULL;
}

bool RegexResult::AddMatch(const RegexMatch& NewMatch)
{
	if (m_Head == NULL)
	{
		m_Head = new MatchListNode();
		//if (m_Head == NULL)
		//	SDMMemoryAllocError(__FUNCTION__);
		
		m_Head->MatchData = NewMatch;
	}
	else
	{
		// Find the insert position
		MatchListNode* Tail = NULL;
		for (Tail = m_Head; Tail->Next != NULL; Tail = Tail->Next)
			;
		
		Tail->Next = new MatchListNode();
		//if (Tail->Next == NULL)
		//	SDMMemoryAllocError(__FUNCTION__);
		
		Tail->Next->MatchData = NewMatch;
	}
	m_iNumMatches++;
	return true;
}

const RegexMatch& RegexResult::operator[] (int Index) const
{
	int Count = 0;
	MatchListNode* Cur = NULL;
	for (Cur = m_Head; Cur != NULL; Cur = Cur->Next, Count++)
	{
		if (Count == Index)
			break;
	}
	
	if (Cur == NULL)
		throw SDMBadIndexException("Bad index in call to RegexResult::operator[]");
	
	return Cur->MatchData;
}

