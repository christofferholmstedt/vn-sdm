#ifndef __SDM_DATA_H_
#define __SDM_DATA_H_

#include "SDMmessage.h"
#include "SDMMessage_ID.h"

typedef struct Listener_Args
{
int pipe_out;
long port;
long count;
long forward_sensor_id;
unsigned char forward_command_id;
short (*callback) (char*);
} ListenerArgs;


class SDMLIB_API SDMData: public SDMmessage
{
public :
	SDMComponent_ID source;		//data provider
	SDMMessage_ID msg_id;		//unique id of data message as defined in xTEDS of data provider
	char msg[BUFSIZE-29];		//buffer containing the raw data
	short length;			//length of msg
	short seq_num;			//a sequence number corresponding to seq_num from SDMSerreqst
	SDMData();
	long Send(const SDMComponent_ID& destination,long length);
	long Send(const SDMComponent_ID& destination);
	// Recv() is deprecated, to be removed in next major release
	long Recv(long port,long length); SDM_DEPRECATED
	long Marshal(char* buf,long length);
	long Unmarshal(const char* buf,long length);
	long Marshal(char* buf);
	long Unmarshal(const char* buf);
	void setSocket(int);
	short getInt(long) const;
	long getLong(long) const;
	signed char getChar(long) const;
	unsigned char getByte(long) const;
	char* getString(long) const;
	float getFloat(long) const;
	double getDouble(long) const;
	int MsgToString(char *str_buf, int length) const;
private :
	long pid;			//SDM process id of xTEDS provider
};

#endif
