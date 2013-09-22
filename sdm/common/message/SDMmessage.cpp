#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "SDMmessage.h"
#include "../UDPcom.h"
#include "../TCPcom.h"
#include "../marshall.h"
#include <sys/time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>

#ifndef WIN32
#  include <net/if.h>
#  include <netdb.h>
#endif
#include <sys/stat.h>

#ifdef WIN32
#undef close
#define	close closesocket
#endif

SDMLIB_API SDMComponent_ID TaskManager;
SDMLIB_API SDMComponent_ID DataManager;
int PID;
#ifdef BUILD_WITH_MESSAGE_LOGGING
//Initialize the static member
SDMMessageLogger SDMmessage::Logger;
#endif

SDMLIB_API void SDMInit(int argc,char** argv)
{
	//initialize connection with SDM system
	TaskManager.setPort(PORT_TM);
	DataManager.setPort(PORT_DM);
	if(argc == 1)
	{
		//assume local local
		TaskManager.setAddress(inet_addr("127.0.0.1"));
		DataManager.setAddress(inet_addr("127.0.0.1"));
		PID = 0;
	}
	else
	{
		if (strcmp(argv[1],"local")==0)
			TaskManager.setAddress(inet_addr("127.0.0.1"));
		else
			TaskManager.setAddress(inet_addr(argv[1]));

		if (strcmp(argv[2],"local")==0)
			DataManager.setAddress(inet_addr("127.0.0.1"));
		else
			DataManager.setAddress(inet_addr(argv[2]));
		PID = atoi(argv[3]);
	}
}

SDMLIB_API long getPort()
{
	char msg[5];
	int sock;
	long value = -1;

	msg[0] = SDM_ReqPort;
	sock = UDPconnect("127.0.0.1", PORT_PM);
	if (sock != IP_SOCK_INVALID)
	{
		UDPsend(sock, msg, 1);
		if(UDPrecv(sock, msg, 5) == 5)
		{
			value = GET_LONG (&msg[1]);
		}
		UDPclose(sock);
	}
	//If the Process Manager didn't respond
	if (value < PORT_APP_START || value > 65535)
	{
		return SDM_PM_NOT_AVAILABLE;
	}

	return value;
}

char SDMmessage::GetMsgName() const
{
	return MsgName;
}

// This function is deprecated, to be removed in next major release
long SDMmessage::RecvFrom(long port)
{
	char buf[BUFSIZE];
	long result;
	long unmarshal_result;
	memset(buf,0,sizeof(buf));
	if(bound == IP_SOCK_INVALID)
	{
		bound = UDPpassive(port);
    if(bound == IP_SOCK_INVALID)
    {
	    return bound;
    }
	}
	result = UDPserv_recv(bound,buf,BUFSIZE);
	if (result <= 0)
  {
		return result;
  }
	unmarshal_result = Unmarshal(buf);
	if (result < unmarshal_result) 
  {
    return result;
  }
  return unmarshal_result;
}


long SDMmessage::SendDM()
{
#ifdef BUILD_FOR_PNPSAT
    struct hostent *he;
    unsigned long addr;

    while ((he=gethostbyname("datamanager.spacewire")) == NULL)
    {
        sleep(1);
    }
    memcpy(&addr, he->h_addr, sizeof(addr));

    DataManager.setAddress(addr);
    DataManager.setPort(PORT_DM);
#endif
#ifdef PNP_FAKE
//    struct hostent *he;
//    unsigned long addr;
//
//    while ((he=gethostbyname("datamanager")) == NULL)
//    {
//        sleep(1);
//    }
//    memcpy(&addr, he->h_addr, sizeof(addr));
//
//    DataManager.setAddress(addr);
//    DataManager.setPort(PORT_DM);
#endif
    return SendTo(DataManager);
}

long SDMmessage::SendTM()
{
	return SendTo(TaskManager);
}

long SDMmessage::SendTo(const SDMComponent_ID& destination)
{
	int sock;
	long i;
	long result;
	char buf[LARGE_MSG_BUFSIZE];
	char ack[16];
	long address = destination.getAddress();
	int timeout = 2000;   // 2 sec
	int count = 0;
	short error = 0;

	//fill buffer
	i = Marshal(buf);
	if(i < 0)
		return SDM_MESSAGE_SEND_ERROR;
#ifdef TCP_TRANSMIT_OF_LARGE_XTEDS
	if(i>BUFSIZE)
		return SendTCP(destination.getAddress(),destination.getPort());
#endif
	//send message
	sock = UDPconnect(address,destination.getPort());
  if (sock != IP_SOCK_INVALID) // cleanup issue 26
  {
	  result = UDPsend(sock,buf,i);
	  //Look for SDM_ACK from DM for certain messages
	  if(buf[0] == SDM_xTEDS || buf[0] == SDM_CancelxTEDS)
	  {
		  if(buf[0] == SDM_xTEDS)
		  {
			  timeout = 5000;   // 5 sec
		  }
		  UDPset_recv_timeout(sock, timeout);

		  UDPrecv(sock,&ack,13);
		  while(ack[0]!=SDM_ACK && count < NUMRETRIES)
		  {
			  count++;

			  result = UDPsend(sock,buf,i);
			  UDPrecv(sock,&ack,13);
		  }
		  //remove timeout on sdm_dm_sock
		  UDPset_recv_timeout(sock, 0);

      if(count == NUMRETRIES && ack[0]!=SDM_ACK)
      {
		    result = SDM_UNABLE_TO_REGISTER;
      }
	    else
      {
		    error = GET_SHORT(&ack[11]); 
        if(error < 0)
        {
			    result = error;
        }
      }
    }
	  UDPclose (sock);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	  Logger.MessageSent(*this);
#endif
  }
	return result;
}

/*
    Forward a previously received message unchanged (i.e. without changing the timestamp).

    Implementation notes:  Currently, only messages of maximum size BUFSIZE can be forwarded.
    The only message that won't send as expected is SDMxTEDS.  The reason for this is that
    the DM is the only application that should ever receive SDMxTEDS, and it will never use
    this function.

    Params:
    	destination - The component id to which to forward the message
    Returns:
    	long - The length of the message sent or -1 to indicate failure
*/
long SDMmessage::Forward(const SDMComponent_ID& destination)
{
	char buf[BUFSIZE];

	if (MsgName == SDM_xTEDS)
		return -1;

	// Save the old timestamp
	long OldSeconds = sec;
	long OldSubSeconds = subsec;

	// Marshal the message, this call will assign a new timestamp
	const long MessageLength = Marshal(buf);
	if (MessageLength < 0)
		return MessageLength;

	// Reset the old timestamp
	sec = OldSeconds;
	subsec = OldSubSeconds;

	// Remarshal the header, overwriting previous data, body of message is still intact
	MarshalHeaderOldTimeStamp(buf);

	// Now send the message to the destination component id
	int sock = UDPconnect(destination.getAddress(), destination.getPort());
	if (sock < 0)
		return -1;
	long SendResult = UDPsend(sock, buf, MessageLength);
	UDPclose(sock);

#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageSent(*this);
#endif
	return SendResult;
}

long SDMmessage::SendTCP(long ip_addr,long port)
{
	int sock;
	long i;
	long result;
	char buf[3*BUFSIZE];
	char ack[16];
	short error = 0;

	//fill buffer
	i = Marshal(buf);
	if(i < 0)
		return SDM_MESSAGE_SEND_ERROR;
	//send message
	sock = TCPconnect(ip_addr,port);
  if (sock != IP_SOCK_INVALID)
  {
	  result = TCPsend(sock,buf,i);
	  if(buf[0] == SDM_xTEDS || buf[0] == SDM_CancelxTEDS)
	  {
		  TCPrecv(sock,ack,13);
		  error = GET_SHORT(&ack[HEADER_SIZE]);
		  if(error < 0)
      {
			  result = error;
      }
	  }
	  TCPclose (sock);
#ifdef BUILD_WITH_MESSAGE_LOGGING
	  Logger.MessageSent(*this);
#endif
  }
	return result;
}

//If addr is supplied, it must be in network byte order
long SDMmessage::SendBroadcast(long address, unsigned short dest_port)
{
	int i, result;
	char buf[BUFSIZE];
	long b_cast_address;
	if (address == 0)		//If no address was supplied
		b_cast_address = DataManager.getAddress();
	else
		b_cast_address = address;

	// DANGEROUS: assumes a little-endian machine and a /24 subnet!
	b_cast_address |= 0xFF000000;		//Set the broadcast address's last octet to 255 as xxx.xxx.xxx.255
	i = Marshal(buf);
	if (i < 0)
		return SDM_MESSAGE_SEND_ERROR;

	result = UDPsend_broadcast(b_cast_address, dest_port, buf, i);
	if (result < 0)
		return SDM_MESSAGE_SEND_ERROR;
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageSent(*this);
#endif
	return i;
}

long SDMmessage::SendReplyTo(int socket, const struct sockaddr_in* sin, bool tcp)
{
	long i;
	long result;
	char buf[BUFSIZE];

	if(socket == IP_SOCK_INVALID) //This is a bad socket descriptor and no message should be sent
		return 0;

	i = Marshal(buf);
	if (i < 0)
		return SDM_MESSAGE_SEND_ERROR;

	if(tcp)
		result = TCPserv_replyto(socket,buf,i,sin);
	else
		result = UDPserv_replyto(socket,buf,i,sin);

	if(result < 0)
	{
#ifndef WIN32
		perror("Unable to send reply message: ");
#else
		printf("Unable to send reply message: %d\n",WSAGetLastError());
#endif

		return SDM_MESSAGE_SEND_ERROR;
	}
#ifdef BUILD_WITH_MESSAGE_LOGGING
	Logger.MessageSent(*this);
#endif
	return i;
}

/*
	Marshal the header without reassigning a new timestamp.
*/
long SDMmessage::MarshalHeaderOldTimeStamp(char* buf)
{
	buf[0] = MsgName;
	PUT_LONG(&buf[1],sec);
	PUT_LONG(&buf[5],subsec);
	PUT_USHORT(&buf[9],msg_length);
	return HEADER_SIZE;
}

long SDMmessage::MarshalHeader(char* buf)
{
#ifdef __VXWORKS__
	struct timespec time;
	clock_gettime(CLOCK_REALTIME, &time);
	sec = time.tv_sec;
	subsec = time.tv_nsec/1000;
#else
	struct timeval time;
	gettimeofday(&time,NULL);
	sec = time.tv_sec;
	subsec = time.tv_usec;
#endif
	buf[0] = MsgName;
	PUT_LONG(&buf[1],sec);
	PUT_LONG(&buf[5],subsec);
	PUT_USHORT(&buf[9],msg_length);
	return HEADER_SIZE;
}

long SDMmessage::UnmarshalHeader(const char* buf)
{
	if(buf == NULL || buf[0] != MsgName)
	{
		return SDM_INVALID_MESSAGE;
	}
	sec = GET_LONG(&buf[1]);
	subsec = GET_LONG(&buf[5]);
	msg_length = GET_USHORT(&buf[9]);
	return HEADER_SIZE;
}
