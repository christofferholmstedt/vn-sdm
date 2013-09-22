#ifndef __SDM_XTEDS_LIBRARY_LIST_H_
#define __SDM_XTEDS_LIBRARY_LIST_H_

//The xTEDSLibraryList does not 'own' its items, it is just a way for items to reference other items in the tree

#include "xTEDSLibrary.h"
#include "../common/message/SDMComponent_ID.h"
#include <stdio.h>

struct xTEDSLibraryListNode
{
	xTEDSLibrary* data;
	struct xTEDSLibraryListNode* next;
};

/*******************************************************************************************************************

	The xTEDSLibraryList class is a linked list of xTEDSLibrary nodes, used by the DataManager to represent
	registered devices and applications in the SDM.  xTEDSLibrary nodes are dynamically allocated when a
	free position in the list doesn't exists, but are not de-allocated when not used.  Instead they are marked
	as unavailable, which allows the position to be reused.

*******************************************************************************************************************/



class xTEDSLibraryList
{
public:
	xTEDSLibraryList();
	xTEDSLibraryList(const xTEDSLibraryList&);
	~xTEDSLibraryList();
	bool GetDeviceName(const SDMComponent_ID& sdmCompId, char* pBuffer, unsigned int uiBufferSize);
	void addLibrary(xTEDSLibrary*);
	int size();
	xTEDSLibraryList& operator=(const xTEDSLibraryList&);
	struct xTEDSLibraryListNode* head;		//Head of the list
	struct xTEDSLibraryListNode* tail;		//Tail of the list
};

#endif
