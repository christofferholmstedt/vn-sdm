#ifndef __SDM_SEARCHREPLY_H_
#define __SDM_SEARCHREPLY_H_

#include "SDMmessage.h"

class SDMLIB_API SDMSearchReply: public SDMmessage
{
public :
	SDMComponent_ID source;			//unique id of xTEDS provider
	unsigned short id;			//the id of the SDMReqReg resulting in this SDMSearchReply
	char captured_matches[BUFSIZE-23];	//the captured matches from the search
	SDMSearchReply();
	long Send(const SDMComponent_ID& destination);
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	long MarshalEmpty(char* buf);
	long SendEmpty(const SDMComponent_ID& destination);
	int MsgToString(char *buf, int length) const;

private:
	bool emptyflag;			//This flag is set for sending and empty SDMSearchReply message
};

#endif

