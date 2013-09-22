#include "xTEDSQualifierList.h"
#include "xTEDSQualifier.h"
#include "../Exception/SDMBadIndexException.h"

#include <stdlib.h>
#include <string.h>

struct xTEDSQualifierListNode* copyList(struct xTEDSQualifierListNode* list,struct xTEDSQualifierListNode** tail)
{
	struct xTEDSQualifierListNode* p;
	struct xTEDSQualifierListNode* head;
	head = (struct xTEDSQualifierListNode*)malloc(sizeof(struct xTEDSQualifierListNode));
	p = head;
	for(struct xTEDSQualifierListNode* cur=list;cur!=NULL;cur=cur->next)
	{
		p->data = cur->data;
		if(cur->next!=NULL)
		{
			p->next = (struct xTEDSQualifierListNode*)malloc(sizeof(struct xTEDSQualifierListNode));
		}
		else
		{
			p->next = NULL;
			*tail = p;
		}
		p = p->next;
	}
	return head;
}

void deleteList(struct xTEDSQualifierListNode* p)
{
	if(p==NULL) return;
	deleteList(p->next);
	if(p->data!=NULL)
		delete(p->data);
	free(p);
}

xTEDSQualifierList::xTEDSQualifierList():itemCount(0),head(NULL),tail(NULL)
{}

xTEDSQualifierList::xTEDSQualifierList(const xTEDSQualifierList& b):itemCount(0),head(NULL),tail(NULL)
{
	head = copyList(b.head,&tail);
}

xTEDSQualifierList::~xTEDSQualifierList()
{
	deleteList(head);
}

void xTEDSQualifierList::addQualifier(const xTEDSQualifier &NewQualifier)
{
	struct xTEDSQualifierListNode* p = (struct xTEDSQualifierListNode*)malloc(sizeof(struct xTEDSQualifierListNode));
	p->data = new xTEDSQualifier(NewQualifier);
	p->next = NULL;
	if(tail == NULL)
	{
		head = p;
		tail = p;
	}
	else
	{
		tail->next = p;
		tail = p;
	}
	itemCount++;
}

xTEDSQualifierList& xTEDSQualifierList::operator=(const xTEDSQualifierList& b)
{
	deleteList(head);
	head = copyList(b.head,&tail);
	return *this;
}

void xTEDSQualifierList::Parse(const char* quallist)
{
	char quals[256];
	int start = 0,end = 0;
  size_t count = 0;
	bool equalfound = false;
	bool parseValid = false;

	quals[0] = 0;
	count = strlen(quallist);
	for(unsigned int i = 0; i < count; i++)
	{
		if((quallist[i] != '<' && quallist[i] != ' ')&&  end >= start)
		{
			start = i;
		}
		if(start > end && equalfound == false && quallist[i] == '=')
		{
			equalfound = true;
			i++;
			while(quallist[i] == ' '&& i < count)
			{
				i++;
			}
		}
		if(equalfound == true && (quallist[i] == ' ' || quallist[i] == '/'))
		{
			end = i;
		}
		if(end > start)
		{
			xTEDSQualifier m_qual;
			strncpy(quals,&quallist[start],end-start);
			quals[end-start] = 0;
			parseValid = m_qual.Parse(quals);
			if(parseValid == true)
			{
				addQualifier(m_qual);
			}
			else
			{
				printf("!!! Improperly formated Qualifier List !!!\n");
			}
			equalfound = false;
			parseValid = false;
			start = end;
		}
	}
}

void xTEDSQualifierList::QualifierInfoRequest( char* InfoBufferOut, size_t BufferSize )
{
	char Buf[MSG_DEF_SIZE];
	size_t BufLength = 0;
	
	Buf[0] = '\0';
	if(head != NULL)
	{
		// Add the first qualifier
		head->data->QualifierInfoRequest(Buf, sizeof(Buf));
		BufLength = strlen(Buf);
		
		for(struct xTEDSQualifierListNode* cur=head->next; cur != NULL; cur=cur->next)
		{
			// Add the formatting whitespace
			strncat (Buf, "\n\t\t", sizeof(Buf) - BufLength);
			BufLength += 3;
			
			// Add the current qualifier text
			cur->data->QualifierInfoRequest(Buf + BufLength, sizeof(Buf) - BufLength);
			BufLength = strlen(Buf);
		}
	}
	strncat(InfoBufferOut, Buf, BufferSize);
}

int xTEDSQualifierList::Size() const
{
	return itemCount;
}

bool xTEDSQualifierList::isEmpty() const
{
	return (itemCount == 0);
}

// Zero-based index
const xTEDSQualifier& xTEDSQualifierList::operator[](int index) const
{
	if (index < 0 || index >= itemCount)
		throw SDMBadIndexException("xTEDSQualifierList:: operator[] index out of bounds.");
	
	int Count = 0;
	xTEDSQualifierListNode* Cur;
	for (Cur = head; Cur != NULL && Count < index; Cur = Cur->next)
		;
	
	if (Cur == NULL && Cur->data == NULL)
		throw SDMBadIndexException("xTEDSQualifierList:: no data to return.");
	
	return *(Cur->data);
}
