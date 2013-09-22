#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include "xTEDSSegmentBuilder.h"

#define XTEDS_EMPTY		0
#define XTEDS_RECEIVED		1

/*
 *  Default constructor; initially the linked list of xTEDSSegmentNodes is empty.
 *  The list is built as requests are made.
 *
*/
xTEDSSegmentBuilder::xTEDSSegmentBuilder()
{
}

/*
 *  Destructor; this method is mainly responsible for freeing the xTEDSSegmentNodes list.
 *
 *
*/
xTEDSSegmentBuilder::~xTEDSSegmentBuilder()
{
}

/*
 *  ApplySegment is responsible for copying in the xTEDS of the segment number of the passed
 *  Message.  If there is no xTEDSSegmentNode corresponding to the xTEDS provider, one is
 *  created.  In other words, there is no other function to add a xTEDSSegmentNode, this one
 *  is to be used.
 *	Params:
 *		Message - The xTEDS to apply.
 *	Returns:
 *		bool - True if the xTEDS was applied successfully, false otherwise.
*/
bool xTEDSSegmentBuilder::ApplySegment(const SDMxTEDS &Message)
{
	//Be sure this is a segment first
	if (!IsSegmentedxTEDS(Message))
	{
		printf("xTEDSSegmentBuilder::ApplySegment - xTEDS not segmented.\n");
		return false;
	}
	
	//Get the sequence number and the total segments from the xTEDS
	unsigned char SequenceNumber = Message.xTEDS[0];	//Zero-based sequence number
	unsigned char TotalSegments = Message.xTEDS[1];		//Total number of segments
	
	//If the sequence number is bigger than the advertised number of segments, or out of range
	if (SequenceNumber+1 > TotalSegments || SequenceNumber > MAX_XTEDS_SEQUENCE_VALUE || TotalSegments > MAX_XTEDS_SEQUENCE_VALUE)
	{
		printf("xTEDSSegmentBuilder::ApplySegment - Sequence number out of range.\n");
		return false;
	}
	
	//Get a reference to the xTEDS node
	xTEDSSegmentNode *SegmentNode = FindNodeEntry(Message.source);
	
	//If the node doesn't exist, create it
	if (SegmentNode == NULL)
	{
		//This should be the first sequence number
		if (SequenceNumber != 0)
		{
			printf("xTEDSSegmentBuilder::ApplySegment - Sequence number not zero for new xTEDS.\n");
			return false;
		}
		//Allocate the node
		SegmentNode = AddSegmentNode();
		//If malloc error, return error
		if (SegmentNode == NULL)
		{
			printf("xTEDSSegmentBuilder::ApplySegment - Segment node could not be obtained.\n");
			return false;
		}
		//Save the number of segments
		SegmentNode->NumSegments = static_cast<unsigned int>(TotalSegments);
		//Save the component ID of the xTEDS sender
		SegmentNode->xTEDSID = Message.source;
		//Allocate the buffer to use for the xTEDS, based on the number of segments
		//SegmentNode->xTEDSBuffer = new char[(TotalSegments * SEGMENT_MAX_XTEDS_SIZE)];
		if (sizeof(SegmentNode->xTEDSBuffer) < static_cast<unsigned int>(TotalSegments*SEGMENT_MAX_XTEDS_SIZE))
		{
			printf("xTEDSSegmentBuilder:: xTEDS buffer not large enough for incoming segmented xTEDS, not accepting.\n");
			DeleteNode(Message.source);
			return false;
		}
		//Clear the buffer
		memset(SegmentNode->xTEDSBuffer, 0, sizeof(SegmentNode->xTEDSBuffer));
	}
	//Node exists
	else
	{
		//If this is a timeout response, but the segment was received, no need to reapply, return true
		if(AlreadyReceived(SequenceNumber, SegmentNode))
			return true;
		//Check that this segment number is sent in order
		if (!SentInOrder(SequenceNumber, SegmentNode))
		{
			printf("xTEDSSegmentBuilder::ApplySegment - Segments out of order.\n");
			return false;
		}
	}
	//At this point, apply the segment at the end of the current xTEDS document (this assumes in order message reception)
	strncpy((SegmentNode->xTEDSBuffer + strlen(SegmentNode->xTEDSBuffer)), Message.xTEDS+2, strlen(Message.xTEDS+2));
	//Set this segment as having been received
	SegmentNode->SegmentsReceived[SequenceNumber] = XTEDS_RECEIVED;
	//Return success
	return true;
}

/*
 *  Checks to see if the segmented xTEDS is full and finished.
 *	Params:
 *		Message - The xTEDS with the corresponding provider to check
 *	Returns:
 *		bool - True if the xTEDS is finished, false if it is not finished.
*/
bool xTEDSSegmentBuilder::CheckIsFinished(const SDMxTEDS &Message)
{
	//Get a pointer to the matching node
	xTEDSSegmentNode *SegmentNode = FindNodeEntry(Message.source);
	//If no matching entry, return that it is not finished
	if (SegmentNode == NULL)
		return false;
	//Otherwise, check to see if the full xTEDS is built
	for (unsigned int i = 0; i < SegmentNode->NumSegments; i++)
	{
		//If there is a segment not received, return false
		if (SegmentNode->SegmentsReceived[i] == XTEDS_EMPTY)
			return false;
	}
	//Otherwise all segments have been received, return true
	return true;
}

/*
 *  Returns the full xTEDS for the corresponding xTEDS provider in Message.  A successful call to
 *  this method also frees the xTEDSSegmentNode.
 *	Params:
 *		Message - The provider with which to match the xTEDS
 *		xTEDSOut [OUTPUT] - Pointer to the buffer to store the xTEDS, this must be at least XTEDS_MAX_SIZE
 *		MaxSize - The size of xTEDSOut
 *	Returns:
 *		bool - True upon success, false is some error occurred
*/
bool xTEDSSegmentBuilder::GetFullxTEDS(const SDMxTEDS &Message, char *xTEDSOut, int MaxSize)
{
	//First, be sure that the xTEDS is fully built, and that xTEDSOut is not NULL
	if (!CheckIsFinished(Message) || xTEDSOut == NULL)
		return false;
	
	//Now we can return the xTEDS
	xTEDSSegmentNode *SegmentNode = FindNodeEntry(Message.source);
	//To be safe, see that we have the node (this should have been handled above)
	if (SegmentNode == NULL)
		return false;
	
	//Check to see that the DM's xTEDS buffer will be big enough
	if (strlen(SegmentNode->xTEDSBuffer) > static_cast<unsigned int>(MaxSize))
	{
		printf("Data Manager not built to support xTEDS of size %d (only up to %d) bytes.\n",strlen(SegmentNode->xTEDSBuffer),MaxSize);
		DeleteNode(Message.source);
		return false;
	}
	//Copy the xTEDS
	else
		strcpy(xTEDSOut, SegmentNode->xTEDSBuffer);
	
	//At this point, the xTEDS has been received, release the node
	DeleteNode(Message.source);
	
	return true;
}

/*
 *  Determines whether the Message is of the segmented form.  This is determined by checking the
 *  first two bytes of the xTEDS buffer within the SDMxTEDS message.  If these two bytes are non-
 *  printable (from 0<=BYTE<=15), then this is a segment of an xTEDS.  Otherwise it is a regular 
 *  xTEDS registration.
 *	Params:
 *		Message - the xTEDS message to check.
 *	Returns:
 *		bool - True if the xTEDS is segmented, false otherwise.
 *
 */
bool xTEDSSegmentBuilder::IsSegmentedxTEDS(const SDMxTEDS &Message)
{
	unsigned char SeqNum = Message.xTEDS[0];		//First byte of the xTEDS buffer
	unsigned char NumSegments = Message.xTEDS[1];		//Second byte of the xTEDS buffer
	
	//Check to see if this is a sequence number and a positive number of segments
	if (SeqNum <= MAX_XTEDS_SEQUENCE_VALUE && NumSegments <= MAX_XTEDS_SEQUENCE_VALUE && NumSegments > 0)
		return true;
	return false;
}
/*
 *  Appends an xTEDSSegmentNode to the linked list, and returns a pointer to the node.
 *	Returns:
 *		xTEDSSegmentNode* - Pointer to the added node, or NULL if there was an error
*/
xTEDSSegmentNode* xTEDSSegmentBuilder::AddSegmentNode()
{
	//
	// Search the list to see if any segment nodes are available
	int NodeIndex = 0;
	for ( ; NodeIndex < MAX_SEGMENT_NODES; NodeIndex++)
	{
		if (NodeList[NodeIndex].IsInUse)
			continue;
		else
			break;
	}
	//
	// If no more entries
	if (NodeIndex == MAX_SEGMENT_NODES)
		return NULL;
	//
	// Clear out anything remaining
	memset(NodeList[NodeIndex].xTEDSBuffer, 0, sizeof (NodeList[NodeIndex].xTEDSBuffer));
	NodeList[NodeIndex].NumSegments = 0;
	for (unsigned int i = 0; i < sizeof(NodeList[NodeIndex].SegmentsReceived); i++)
		NodeList[NodeIndex].SegmentsReceived[i] = XTEDS_EMPTY;
	NodeList[NodeIndex].xTEDSID.setSensorID(0);
	NodeList[NodeIndex].xTEDSID.setAddress(0);
	NodeList[NodeIndex].xTEDSID.setPort(0);
	//
	// Set node active
	NodeList[NodeIndex].IsInUse = true;

	return &NodeList[NodeIndex];
}
/*
 *  Finds the node in the list corresponding to the component id.
 *	Params:
 *		xTEDSID - The component id to match the node.
 *	Returns:
 *		xTEDSSegmentNode* - A pointer to the node found, or NULL if not found.
*/
xTEDSSegmentNode* xTEDSSegmentBuilder::FindNodeEntry(const SDMComponent_ID &xTEDSID)
{
	//
	// Traverse the list and find the node
	for (int NodeIndex = 0; NodeIndex < MAX_NUMBER_SEGMENTS; NodeIndex++)
	{
		if (NodeList[NodeIndex].IsInUse && NodeList[NodeIndex].xTEDSID == xTEDSID)
			return &NodeList[NodeIndex];
	}
	//
	// If the node was not found
	return NULL;
}	
/*
 *  Deletes the xTEDSBuilderNode corresponding to the xTEDSID.
 *	Params:
 *		xTEDSID - The identifier corresponding to the xTEDS to delete
 *	Returns:
 *		bool - True if the node was found and deleted, false if an error occurred
*/
bool xTEDSSegmentBuilder::DeleteNode(const SDMComponent_ID &xTEDSID)
{
	//
	// Find the node
	xTEDSSegmentNode *NodeToDelete = FindNodeEntry(xTEDSID);
	
	if (NodeToDelete == NULL) return false;
	//
	// Set the node as inactive
	NodeToDelete->IsInUse = false;
	return true;
}
/*
 *  Determines whether an xTEDS segment was sent in order.  This is necessary to make sure that the xTEDS document
 *  is written such that each segments goes into the document as advertised in the segment numbers.
 *	Params:
 *		SequenceNumber - The sequence number to check
 *		CurrNode - The receiver node to check against
 *	Returns:
 *		bool - True if this packet is in order, false if it is out of order
*/
bool xTEDSSegmentBuilder::SentInOrder(unsigned char SequenceNumber, xTEDSSegmentNode *CurrNode)
{
	//Traverse the flag list
	for (unsigned int i = 0; i < sizeof(CurrNode->SegmentsReceived); i++)
	{
		//If there are empty slots before this current sequence number, this was not sent in order
		if (i < SequenceNumber && CurrNode->SegmentsReceived[i] == XTEDS_EMPTY)
			return false;
		//If there are full slots at or after this sequence number, this was not sent in order
		if (i >= SequenceNumber && CurrNode->SegmentsReceived[i] == XTEDS_RECEIVED)
			return false;
	}
	return true;
}
/*
 *  Determines whether an xTEDS segment was already received.
 *	Params:
 *		SequenceNumber - The sequence number to check
 *		CurrNode - The receiver node to check against
 *	Returns:
 *		bool - True if this packet has already been received, false otherwise
*/
bool xTEDSSegmentBuilder::AlreadyReceived(unsigned char SequenceNumber, xTEDSSegmentNode *CurrNode)
{
	//Be sure the index is not out of bounds
	if (SequenceNumber >= sizeof(CurrNode->SegmentsReceived))
		   return false;
	//Check if we have received this segment
	return (CurrNode->SegmentsReceived[SequenceNumber] == XTEDS_RECEIVED);
}
