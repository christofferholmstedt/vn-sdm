#ifndef __SDM_REGULAR_EXPRESSION_H_
#define __SDM_REGULAR_EXPRESSION_H_

#include <sys/types.h>
#ifdef  __VXWORKS__
#include "pcreposix.h"
#else
#include <regex.h>
#endif

#include "../message/SDMData.h"

class SDMLIB_API RegularExpression
{
public:
	RegularExpression();
	~RegularExpression();
	
	bool Set(const char* PatternText);

	const regex_t& Get() const { return m_CompiledExpression; }
private:
	void FreeExpression();
	regex_t m_CompiledExpression;

	bool m_bExpressionSet;
};


#endif
