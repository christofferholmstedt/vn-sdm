#include "xTEDSOptionList.h"
#include "MessageDef.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*  Not used..
xTEDSOptionList::xTEDSOptionList(const xTEDSOptionList& b):head(NULL),tail(NULL)
{
	head = copyList(b.head,&tail);
}

xTEDSOptionList& xTEDSOptionList::operator=(const xTEDSOptionList& b)
{
	deleteList(head);
	head = copyList(b.head,&tail);
	return *this;
}
struct xTEDSOptionListNode* copyList(struct xTEDSOptionListNode* list,struct xTEDSOptionListNode** tail)
{
	struct xTEDSOptionListNode* p;
	struct xTEDSOptionListNode* head;
	head = (struct xTEDSOptionListNode*)malloc(sizeof(struct xTEDSOptionListNode));
	p = head;
	for(struct xTEDSOptionListNode* cur=list;cur!=NULL;cur=cur->next)
	{
		p->data = cur->data;
		if(cur->next!=NULL)
		{
			p->next = (struct xTEDSOptionListNode*)malloc(sizeof(struct xTEDSOptionListNode));
		}
		else
		{
			p->next = NULL;
			*tail = p;
		}
		p = p->next;
	}
	return head;
}*/

void deleteList(struct xTEDSOptionListNode* p)
{
	for (xTEDSOptionListNode *Cur = p; Cur != NULL; )
	{
		xTEDSOptionListNode *Temp = Cur->next;
		delete Cur;
		Cur = Temp;
	}
}

xTEDSOptionList::xTEDSOptionList():head(NULL),tail(NULL)
{}


xTEDSOptionList::~xTEDSOptionList()
{
	deleteList(head);
}

void xTEDSOptionList::setOptionsList(const curveoption* OptionList)
{
	addOption(OptionList);
	for (curveoption* Cur = OptionList->next; Cur != NULL; Cur = Cur->next)
		addOption(Cur);
}

void xTEDSOptionList::addOption(const curveoption* NewOption)
{
	xTEDSOptionListNode *NewNode = new xTEDSOptionListNode();
	NewNode->data.setOption(NewOption);
	if (head == NULL)
	{
		head = tail = NewNode;
	}
	else
	{
		xTEDSOptionListNode *Cur;
		for (Cur = head; Cur->next != NULL; Cur = Cur->next)
			;
		Cur->next = NewNode;
		tail = NewNode;
	}
}

bool xTEDSOptionList::IsEmpty() const
{
	if(head == NULL)
		return true;
	return false;
}

void xTEDSOptionList::VarInfoRequest( char* InfoBufferOut, size_t BufferSize ) const
{
	const unsigned int MAX_BUF_SIZE = 1024;
	char Buf[MAX_BUF_SIZE];
	if (head == NULL)
		return ;
	
	Buf[0] = '\0';
	for (xTEDSOptionListNode *Cur = head; Cur != NULL; Cur = Cur->next)
	{
		strncat(Buf, "\n\t\t", sizeof(Buf) - strlen(Buf));
		
		const size_t CurBufLength = strlen(Buf);
		Cur->data.VarInfoRequest(Buf + CurBufLength, sizeof(Buf) - CurBufLength);
	}
	strncat(InfoBufferOut, Buf, BufferSize - 1);
}
