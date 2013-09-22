#include "RegularExpression.h"


RegularExpression::RegularExpression() : m_CompiledExpression(), m_bExpressionSet(false)
{
}

RegularExpression::~RegularExpression()
{
	FreeExpression();
}

bool RegularExpression::Set(const char* strPattern)
{
	FreeExpression();
	
	int iResult = regcomp(&m_CompiledExpression, strPattern, REG_EXTENDED);
	if (iResult != 0)
		return false;
	
	m_bExpressionSet = true;
	return true;
}

void RegularExpression::FreeExpression()
{
	if (m_bExpressionSet)
	{
		regfree(&m_CompiledExpression);
		m_bExpressionSet = false;
	}
}
