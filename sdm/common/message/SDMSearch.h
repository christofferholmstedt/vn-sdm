#ifndef __SDM_SEARCH_H_
#define __SDM_SEARCH_H_

#include "SDMmessage.h"

#define SDM_SEARCH_CURRENT 				0
#define SDM_SEARCH_CURRENT_AND_FUTURE			5
#define SDM_SEARCH_CANCEL				11

class SDMLIB_API SDMSearch: public SDMmessage
{
public :
	SDMComponent_ID source;		//optional component_id of the xTEDS provider
	SDMComponent_ID destination;	//the id of the message issuer
	unsigned char reply;		//style of reply desired (see above)
	unsigned short id;		//id of this request
	char reg_expr[BUFSIZE-33];	//buffer containing regular expression
	SDMSearch();
	long Send();
	long Recv(long port); SDM_DEPRECATED
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	int MsgToString(char *buf, int length) const;
};

#endif
