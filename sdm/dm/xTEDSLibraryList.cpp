#include "xTEDSLibraryList.h"
#include "xTEDSLibrary.h"
#include <stdlib.h>
#include <string.h>
extern "C"
{
#include "../common/MemoryUtils.h"
}

struct xTEDSLibraryListNode* copyList(struct xTEDSLibraryListNode* list,struct xTEDSLibraryListNode** tail)
{
	struct xTEDSLibraryListNode* p;
	struct xTEDSLibraryListNode* head;
	head = (struct xTEDSLibraryListNode*)SDM_malloc(sizeof(struct xTEDSLibraryListNode));
	p = head;
	for(struct xTEDSLibraryListNode* cur=list;cur!=NULL;cur=cur->next)
	{
		p->data = cur->data;
		if(cur->next!=NULL)
		{
			p->next = (struct xTEDSLibraryListNode*)SDM_malloc(sizeof(struct xTEDSLibraryListNode));
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

void deleteList(struct xTEDSLibraryListNode* p)
{
	if(p==NULL) return;
	deleteList(p->next);
	if(p->data!=NULL)
		delete(p->data);
	free(p);
}

int xTEDSLibraryList::size()
{
	int size = 0;
	for(xTEDSLibraryListNode* p = head; p != NULL; p = p->next)
	{
        size++;
	}
	return size;
}

xTEDSLibraryList::xTEDSLibraryList():head(NULL),tail(NULL)
{}

xTEDSLibraryList::xTEDSLibraryList(const xTEDSLibraryList& b):head(NULL),tail(NULL)
{
	head = copyList(b.head,&tail);
}

xTEDSLibraryList::~xTEDSLibraryList()
{
	deleteList(head);
}

void xTEDSLibraryList::addLibrary(xTEDSLibrary* data)
{
	struct xTEDSLibraryListNode* p = (struct xTEDSLibraryListNode*)SDM_malloc(sizeof(struct xTEDSLibraryListNode));
	p->data = data;
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
}

xTEDSLibraryList& xTEDSLibraryList::operator=(const xTEDSLibraryList& b)
{
	deleteList(head);
	head = copyList(b.head,&tail);
	return *this;
}

// Get the device name for the sensor id specified in sdmCompId and store it in pBuffer.
bool xTEDSLibraryList::GetDeviceName(const SDMComponent_ID& sdmCompId, char* pBuffer, unsigned int uiBufferSize)
{
	unsigned long ulSensorId = sdmCompId.getSensorID();
	bool bFound = false;

	if (ulSensorId == 0 || ulSensorId == 1)
	{
		snprintf(pBuffer, uiBufferSize, "unknown");
		return false;
	}

	xTEDSLibrary* pXteds = NULL;
	for (xTEDSLibraryListNode* pCur = head; pCur != NULL && !bFound ; pCur = pCur->next)
	{
		pXteds = pCur->data;

		pXteds->inUse->Wait();
		if (!pXteds->getAvailable())
		{
			if (pXteds->getComponentID().getSensorID() == ulSensorId)
			{
				snprintf(pBuffer, uiBufferSize, "%s", pXteds->getName());
				bFound = true;
			}
		}
		pXteds->inUse->Signal();
	}
	if (!bFound)
		snprintf(pBuffer, uiBufferSize, "unknown");

	return bFound;
}