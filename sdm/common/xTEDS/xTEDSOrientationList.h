#ifndef __SDM_XTEDS_ORIENTATION_H_
#define __SDM_XTEDS_ORIENTATION_H_

#include <stdlib.h>
#include "xTEDSOrientationItem.h"
extern "C"
{
#include "xTEDSParser.h"
}

struct xTEDSOrientationItemNode
{
	xTEDSOrientationItem OrientationData;
	xTEDSOrientationItemNode *Next;
	// The below fixes compile warnings
	xTEDSOrientationItemNode():OrientationData(),Next(NULL) {}
	xTEDSOrientationItemNode(const xTEDSOrientationItemNode&);
	xTEDSOrientationItemNode& operator=(const xTEDSOrientationItemNode&);
};

class xTEDSOrientationList
{
public:
	xTEDSOrientationList();
	~xTEDSOrientationList();
	xTEDSOrientationList(const xTEDSOrientationList&);
	xTEDSOrientationList& operator=(const xTEDSOrientationList&);
	
	void AddOrientation(const orientation*);
	void SetOrientation(const orientation*);
	
	void VarInfoRequest(char* InfoBufferOut, size_t BufferLength) const;
private:
	xTEDSOrientationItemNode *Head;
	void DeleteList();
};

#endif

