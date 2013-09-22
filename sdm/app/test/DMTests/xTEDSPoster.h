#ifndef __XTEDS_POSTER_H_
#define __XTEDS_POSTER_H_

#include "../../../common/message/SDMComponent_ID.h"

class xTEDSPoster
{
public:
	xTEDSPoster();
	~xTEDSPoster();
	
	static int PostxTEDS(const char* filename);
	static int CancelxTEDS();
private:
	
};


#endif
