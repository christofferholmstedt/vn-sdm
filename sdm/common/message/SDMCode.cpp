#include <string.h>
#include <stdio.h>
#include "SDMCode.h"
#include "../checksum/checksum.h"
#include "../UDPcom.h"


SDMCode::SDMCode() : seq_num(0), num_segments(0), code_length(0), c_sum(0)
{
	MsgName = SDM_Code;
	filename[0] = '\0';
	total_length = 9;
}

long SDMCode::Marshal(char* buf)
{
	int cur;
	cur = HEADER_SIZE;
	PUT_USHORT(&buf[cur], seq_num);
	cur += sizeof(seq_num);
	PUT_USHORT(&buf[cur], num_segments);
	cur += sizeof(num_segments);
	//
	// Copy the filename
	size_t uiCurLength = strlen(filename);
	strcpy(buf + cur, filename);
	cur += (int)uiCurLength + 1;
	//
	// Copy the code section
	memcpy (&buf[cur], &code, code_length);
	cur += code_length;

	c_sum = checksum(code, code_length);
	PUT_INT (&buf[cur], c_sum);
	cur += sizeof (c_sum);
	msg_length = cur - HEADER_SIZE;
	MarshalHeader(buf);
	return cur;
}

long SDMCode::Unmarshal(const char* buf)
{
	int cur;
	cur = UnmarshalHeader(buf);
	if (cur == SDM_INVALID_MESSAGE)
	{
		return SDM_INVALID_MESSAGE;
	}
	if(total_length>msg_length)
	{
		return SDM_INVALID_MESSAGE;
	}
	seq_num = GET_USHORT(&buf[cur]);
	cur += sizeof(seq_num);
	num_segments = GET_USHORT(&buf[cur]);
	cur += sizeof(num_segments);
	//
	// Get the filename
	size_t uiCurLength = strlen(buf + cur);
	strncpy(filename, buf + cur, sizeof(filename));
	if (uiCurLength > sizeof(filename) - 1)
		filename[sizeof(filename) - 1] = '\0';
	cur += (int)uiCurLength + 1;
	
	memcpy(&code, &buf[cur], msg_length - (strlen(filename)+1) - 8);
	cur += msg_length - (unsigned int)(strlen(filename)+1) - 8;
	code_length = msg_length - (unsigned int)(strlen(filename)+1) - 8;
	c_sum = GET_INT(&buf[cur]);
	cur += sizeof(c_sum);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageReceived(*this);
#endif
	return cur;
}

bool SDMCode::isCorrupt()
{
	long curr_csum = c_sum;
	long msg_csum = checksum(code, code_length);
	return curr_csum == msg_csum ? false : true;
}
int SDMCode::MsgToString(char *str_buf, int length) const
{
	if (length < 8096)
		return 0;
#ifdef WIN32
	sprintf(str_buf,
#else
	snprintf(str_buf,length,
#endif
        "SDMCode %ld:%ld %ld bytes, SeqNum: %d NumSegments: %d Filename: %s [CODE SECTION] Checksum: %d", sec, subsec, msg_length, seq_num, num_segments, filename,c_sum);
	return (int)strlen(str_buf);
}
