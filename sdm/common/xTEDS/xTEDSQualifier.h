#ifndef __SDM_XTEDS_QUALIFIER_H_
#define __SDM_XTEDS_QUALIFIER_H_

#include "../message_defs.h"
#include <cstring>

class xTEDSQualifier
{
public:
	xTEDSQualifier();
	xTEDSQualifier(char* pName, char* pDescription, char* pUnits);
	xTEDSQualifier(const xTEDSQualifier&);

	virtual ~xTEDSQualifier();

	void setName(const char*);
	void setDescription(const char*);
	void setUnits(const char*);
	const char* getName(void) const;
	const char* getDescription(void) const;
	const char* getUnits(void) const;
	bool Parse(const char*);
  void QualifierInfoRequest(char* InfoBufferOut, size_t BufferSize);

	bool MatchesName(const char* MatchString) const;
	bool MatchesDescription(const char* MatchString) const;

	xTEDSQualifier& operator=(const xTEDSQualifier&);
private:
	char* m_strName;
	char* m_strDescription;
	char* m_strUnits;
};

#endif
