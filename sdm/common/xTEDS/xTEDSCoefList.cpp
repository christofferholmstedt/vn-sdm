#include "xTEDSCoefList.h"
#include "MessageDef.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void xTEDSCoefList::deleteList()
{
	xTEDSCoefListNode *Temp;
	for (xTEDSCoefListNode *Cur = head; Cur != NULL; )
	{
		Temp = Cur->next;
		delete Cur;
		Cur = Temp;
	}
}

xTEDSCoefList::xTEDSCoefList():head(NULL),tail(NULL)
{}

xTEDSCoefList::~xTEDSCoefList()
{
	deleteList();
}

void xTEDSCoefList::setCoefList(const coef* CoefList)
{
	if (CoefList == NULL) return;
	
	addCoef(CoefList);
	for (coef* Cur = CoefList->next; Cur != NULL; Cur = Cur->next)
	{
		addCoef(Cur);
	}
}

void xTEDSCoefList::addCoef(const coef* NewCoef)
{
	if (NewCoef == NULL) return;
	
	xTEDSCoefListNode *NewNode = new xTEDSCoefListNode();
	NewNode->data.setCoef(NewCoef);
	if(head == NULL)
	{
		head = NewNode;
		tail = NewNode;
	}
	else
	{
		xTEDSCoefListNode* Cur;
		for (Cur = head; Cur->next != NULL; Cur = Cur->next)
			;
		Cur->next = NewNode;
		tail = NewNode;
	}
}

bool xTEDSCoefList::IsEmpty() const
{
	return (head == NULL);
}

void xTEDSCoefList::VarInfoRequest( char* InfoBufferOut, size_t BufferSize ) const
{
	const unsigned int MAX_BUF_SIZE = 1024;
	char Buf[MAX_BUF_SIZE];
	
	if (head == NULL)
		return ;
	
	Buf[0] = '\0';
	for (xTEDSCoefListNode* Cur = head; Cur != NULL; Cur = Cur->next)
	{
		strncat (Buf, "\n\t\t", sizeof(Buf) - strlen(Buf));
		
		const size_t CurBufLength = strlen(Buf);
		Cur->data.VarInfoRequest(Buf + CurBufLength, sizeof(Buf) - CurBufLength);
	}
	strncat(InfoBufferOut, Buf, BufferSize - 1);
}


/*  Not used..
xTEDSCoefList::xTEDSCoefList(const xTEDSCoefList& b):head(NULL),tail(NULL)
{
	head = copyList(b.head,&tail);
}
xTEDSCoefList& xTEDSCoefList::operator=(const xTEDSCoefList& b)
{
	deleteList(head);
	head = copyList(b.head,&tail);
	return *this;
}*/
/*struct xTEDSCoefListNode* copyList(struct xTEDSCoefListNode* list,struct xTEDSCoefListNode** tail)
{
	struct xTEDSCoefListNode* p;
	struct xTEDSCoefListNode* head;
	head = (struct xTEDSCoefListNode*)malloc(sizeof(struct xTEDSCoefListNode));
	p = head;
	for(struct xTEDSCoefListNode* cur=list;cur!=NULL;cur=cur->next)
	{
		p->data = cur->data;
		if(cur->next!=NULL)
		{
			p->next = (struct xTEDSCoefListNode*)malloc(sizeof(struct xTEDSCoefListNode));
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

