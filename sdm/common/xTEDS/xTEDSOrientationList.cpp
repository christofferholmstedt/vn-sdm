#include <string.h>
#include "xTEDSOrientationList.h"
#include "MessageDef.h"

xTEDSOrientationList::xTEDSOrientationList():Head(NULL)
{
}

xTEDSOrientationList::~xTEDSOrientationList()
{
	DeleteList();
}

void xTEDSOrientationList::AddOrientation(const orientation* NewOrientation)
{
	xTEDSOrientationItemNode *Cur;
	
	if (NewOrientation == NULL) return;
	
	if (Head == NULL)
	{
		Head = new xTEDSOrientationItemNode();
		Head->OrientationData.SetOrientation(NewOrientation);
	}
	else
	{
		for (Cur = Head; Cur->Next != NULL; Cur = Cur->Next)
			;
		xTEDSOrientationItemNode *NewItem = new xTEDSOrientationItemNode();
		NewItem->OrientationData.SetOrientation(NewOrientation);
		Cur->Next = NewItem;
	}
}

void xTEDSOrientationList::SetOrientation(const orientation* OrientationList)
{
	// Add the head first
	AddOrientation(OrientationList);
	// Add the rest
	for (orientation* Cur = OrientationList->next; Cur != NULL; Cur = Cur->next)
	{
		AddOrientation(Cur);
	}
}

void xTEDSOrientationList::DeleteList()
{
	for (xTEDSOrientationItemNode *Cur = Head; Cur != NULL; )
	{
		xTEDSOrientationItemNode *Temp = Cur->Next;
		delete Cur;
		Cur = Temp;
	}
	Head = NULL;
}

void xTEDSOrientationList::VarInfoRequest(char* InfoBufferOut, size_t BufferLength) const
{
	const int MAX_BUF_SIZE = 1024;
	char Buf[MAX_BUF_SIZE];
	size_t BufLength = 0;
	
	Buf[0] = '\0';
	for (xTEDSOrientationItemNode *Cur = Head; Cur != NULL; Cur = Cur->Next)
	{
		BufLength = strlen(Buf);
		strncat(Buf, "\n\t", sizeof(Buf) - BufLength);
		
		BufLength += 2;
		Cur->OrientationData.VarInfoRequest(Buf + BufLength, sizeof(Buf) - BufLength);
	}
	strncat(InfoBufferOut, Buf, BufferLength - 1);
}
