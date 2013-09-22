#ifndef __SDM_XTEDS_OPTION_LIST_H_
#define __SDM_XTEDS_OPTION_LIST_H_
#include <stdlib.h>
#include "xTEDSOption.h"
extern "C"
{
#include "xTEDSParser.h"
}

struct xTEDSOptionListNode
{
	xTEDSOption data;
	struct xTEDSOptionListNode* next;
	xTEDSOptionListNode():data(),next(NULL) {}
	xTEDSOptionListNode(const xTEDSOptionListNode&);
	xTEDSOptionListNode& operator=(const xTEDSOptionListNode&);
};

class xTEDSOptionList
{
public:
	xTEDSOptionList();
	xTEDSOptionList(const xTEDSOptionList&);
	~xTEDSOptionList();
	xTEDSOptionList& operator=(const xTEDSOptionList&);
	
	void setOptionsList(const curveoption* OptionList);
	void addOption(const curveoption* Option);
	bool IsEmpty(void) const;

  void VarInfoRequest(char* InfoBufferOut, size_t BufferSize) const;
private:
	struct xTEDSOptionListNode* head;
	struct xTEDSOptionListNode* tail;
};

#endif
