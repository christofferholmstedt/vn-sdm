#ifndef __SDM_XTEDS_QUALIFIER_LIST_H_
#define __SDM_XTEDS_QUALIFIER_LIST_H_

//The xTEDSQualifierList does not 'own' its items, it is just a way for items to reference other items in the tree
#include "../message_defs.h"
#include "xTEDSQualifier.h"
#include <stdio.h>
#include <cstring>

struct xTEDSQualifierListNode
{
	xTEDSQualifier* data;
	struct xTEDSQualifierListNode* next;
};

class xTEDSQualifierList
{
public:
	xTEDSQualifierList();
	xTEDSQualifierList(const xTEDSQualifierList&);
	~xTEDSQualifierList();
	void addQualifier(const xTEDSQualifier &NewQualifier);
	void Parse(const char*);
	xTEDSQualifierList& operator=(const xTEDSQualifierList&);
  void QualifierInfoRequest(char* InfoBufferOut, size_t BufferSize);

	int Size() const;
	bool isEmpty() const;
	const xTEDSQualifier& operator[] (int index) const;
private:
	int itemCount;
	struct xTEDSQualifierListNode* head;
	struct xTEDSQualifierListNode* tail;
};

#endif
