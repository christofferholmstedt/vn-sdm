#ifndef __SDM_CODE_H_
#define __SDM_CODE_H_

#include "SDMmessage.h"

//This class is intended only for use by SDM core components

class SDMLIB_API SDMCode : public SDMmessage
{
	public:
	unsigned short seq_num;		//A sequence number to reorder packets in
	unsigned short num_segments;	//The total number of packets the code is split into
	char filename[MAX_FILENAME_SIZE];		//The name of the code
	unsigned short code_length;	//The length of the code
	int c_sum;			//The checksum for the code
	char code[BUFSIZE - MAX_FILENAME_SIZE - 21];	//The buffer for the piece of code
	SDMCode();
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	bool isCorrupt();
	int MsgToString(char *str_buf, int length) const;
};



#endif
