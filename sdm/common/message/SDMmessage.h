#ifndef __SDM_MESSAGE_H_
#define __SDM_MESSAGE_H_


//#include <byteswap.h>	// Macros for moving bytes around if necessary
#include "../message_defs.h"
#include "../marshall.h"
#include "SDMComponent_ID.h"
#include "../sdmLib.h"
#include "../UDPcom.h"
#ifdef BUILD_WITH_MESSAGE_LOGGING
#  include "../MessageLogger/SDMMessageLogger.h"
#endif

#define SDM_OK		0
#define SDM_MESSAGE_SEND_ERROR -1
#define SDM_MESSAGE_RECV_ERROR -2
#define SDM_INVALID_MESSAGE -3
#define SDM_NO_FURTHER_DATA_PROVIDER -4
#define SDM_COULD_NOT_FORK -5
#define SDM_NO_FURTHER_XTEDS -6
#define SDM_ASYNC_PIPE_ERROR -7
#define SDM_INVALID_SELECT -8
#define SDM_UNABLE_TO_REGISTER -9
#define SDM_INVALID_XTEDS -10
#define SDM_UNKNOWN_XTEDS -11
#define SDM_INVALID_UPDATE -12
#define SDM_UNABLE_TO_UPDATE -13
#define SDM_INVALID_CANCEL -14
#define SDM_PM_NOT_AVAILABLE	-15
//Header size for all SDM* messages
#define HEADER_SIZE	11

enum SDM_TYPE
{
	_INTEGER,
	_LONG,
	_CHAR,
	_BYTE,
	//_STRING,
	_FLOAT
};

extern SDMLIB_API SDMComponent_ID TaskManager;
extern SDMLIB_API SDMComponent_ID DataManager;

extern SDMLIB_API int PID;
extern SDMLIB_API long getPort();
extern SDMLIB_API void SDMInit(int argc,char** argv);

class SDMLIB_API SDMmessage
{
protected:
	char MsgName;				//byte indicating the type of message
	long sec;				//seconds portion of timestamp
	long subsec;				//subseconds portion
	short msg_length;			//msg_length of message not including header (consistant with SPA-U)
	short total_length;			//a known or minimum length for a given message not including the header
public:
	SDMmessage():MsgName('\0'),sec(0),subsec(0),msg_length(0),total_length(0),bound(IP_SOCK_INVALID){}
	virtual ~SDMmessage() {}
	virtual long Marshal(char* buf) =0;
	virtual long Unmarshal(const char* buf)=0;
	virtual int MsgToString(char *str_buf, int length) const =0;
	bool Avail(long port, int timeout) const;
	bool Avail(long port) const;
	long SendTo(const SDMComponent_ID& destination);
	char GetMsgName() const;
	long Forward(const SDMComponent_ID& destination);
	long GetSecondsStamp () const { return sec; }
	long GetSubSecondsStamp () const { return subsec; }
protected:
	long MarshalHeader(char* buf);
	long UnmarshalHeader(const char* buf);
	long SendDM();
	long SendTM();
	long RecvFrom(long port); /*__attribute__ ((deprecated));*/
	long SendTCP(long ip_addr,long port);
	long SendBroadcast(long address=0, unsigned short dest_port=PORT_DM_ELECTION);
	long SendReplyTo(int socket, const struct sockaddr_in* sin, bool tcp);
	// bound is deprecated to be removed with RecvFrom()
	int bound;		//the socket the class currently has access to or -1 if none
#ifdef BUILD_WITH_MESSAGE_LOGGING
	static SDMMessageLogger Logger;
#endif
private:
	long MarshalHeaderOldTimeStamp(char* buf);
};

#endif // __SDM_MESSAGE_H_
