/*
 *  The xTEDSSegmentBuilder class is used by the SDM Data Manager to receive xTEDS documents
 *  from connected sensors who do not have the capability for TCP/IP communication, and have
 *  an xTEDS to publish that is larger than the size of a UDP datagram.  Multiple transmissions
 *  can occur simultaneously, however mutual exclusion is assumed to be handled at the layer
 *  above this class.  Each transmission of xTEDS is differentiated based on the sensor's
 *  SDMComponent_ID.
*/

#ifndef _XTEDS_SEGMENT_BUILDER_H_
#define _XTEDS_SEGMENT_BUILDER_H_
#include "../common/message/SDMComponent_ID.h"
#include "../common/message/SDMxTEDS.h"

#define MAX_NUMBER_SEGMENTS	4
#define SEGMENT_MAX_XTEDS_SIZE	8070
#define MAX_SEGMENT_NODES	5

//Structure representing an xTEDS to build, as messages come in
struct xTEDSSegmentNode
{
	bool IsInUse;
	char xTEDSBuffer[MAX_NUMBER_SEGMENTS*SEGMENT_MAX_XTEDS_SIZE];	//Pointer to the xTEDS being built
	unsigned short NumSegments;		//The number of xTEDS segments to receive
	unsigned char SegmentsReceived[16];	//An array of which segments have been received
	SDMComponent_ID xTEDSID;		//Component identifier of the xTEDS provider
	int NextIndex;				//Index position to the next node in the list
	//Initializer
	xTEDSSegmentNode() : IsInUse(false),NumSegments(0),xTEDSID(),NextIndex(-1) {}
	//Declared but not defined:
	xTEDSSegmentNode(const xTEDSSegmentNode &right);
	xTEDSSegmentNode &operator=(const xTEDSSegmentNode &right);
};

class xTEDSSegmentBuilder
{
public:
	xTEDSSegmentBuilder();
	~xTEDSSegmentBuilder();
	xTEDSSegmentBuilder(const xTEDSSegmentBuilder &right);
	xTEDSSegmentBuilder& operator=(const xTEDSSegmentBuilder &right);
	
	bool ApplySegment(const SDMxTEDS &Message);
	bool CheckIsFinished(const SDMxTEDS &Message);
	bool GetFullxTEDS(const SDMxTEDS &Message, char *xTEDSOut, int MaxSize);
	static bool IsSegmentedxTEDS(const SDMxTEDS &Message);
private:
	xTEDSSegmentNode NodeList[MAX_SEGMENT_NODES];
	xTEDSSegmentNode* AddSegmentNode();
	bool DeleteNode(const SDMComponent_ID &xTEDSID);
	xTEDSSegmentNode* FindNodeEntry(const SDMComponent_ID &xTEDSID);
	bool SentInOrder(unsigned char SequenceNumber, xTEDSSegmentNode* CurrNode);
	bool AlreadyReceived(unsigned char SequenceNumber, xTEDSSegmentNode* CurrNode);
};

#endif
