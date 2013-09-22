#ifndef __SDM_XTEDS_COEF_LIST_H_
#define __SDM_XTEDS_COEF_LIST_H_

#include "xTEDSCoef.h"
extern "C"
{
#include "xTEDSParser.h"
}
#include <stdlib.h>
#include <cstring>

struct xTEDSCoefListNode
{
	xTEDSCoef data;
	struct xTEDSCoefListNode* next;
	xTEDSCoefListNode():data(),next(NULL) {}
	xTEDSCoefListNode(const xTEDSCoefListNode&);
	xTEDSCoefListNode& operator=(const xTEDSCoefListNode&);
};

class xTEDSCoefList
{
public:
	xTEDSCoefList();
	xTEDSCoefList(const xTEDSCoefList&);
	xTEDSCoefList& operator=(const xTEDSCoefList&);
	~xTEDSCoefList();

	void setCoefList(const coef* CoefList);
	void addCoef(const coef* NewCoef);

	bool IsEmpty(void) const;
  void VarInfoRequest(char* InfoBufferOut, size_t BufferSize) const;
private:
	void deleteList();
	struct xTEDSCoefListNode* head;
	struct xTEDSCoefListNode* tail;
};

#endif
