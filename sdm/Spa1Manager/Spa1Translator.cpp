#include "Spa1Translator.h"

extern int debug;

/**
* Defualt constructor for the Spa1Translator
*/
Spa1Translator::Spa1Translator()
{
}

/**
* Function used to translate an SDM message into its SPA-1 equivalent.
*
* This function is mainly responsible to act as the public gateway to dish off
* the work to the appropriate private member function.
*
* @param inBuf A buffer containing a marshalled SDM message
* @param outBuf The buffer which will have the SPA-1 message written into it
* @param outBufSize The size of the output buffer
*
* @return An int containing the size in bytes of the SPA-1 message written into outBuf
*/
int Spa1Translator::translateToSpa1(unsigned char* inBuf, unsigned char* outBuf, size_t outBufSize)
{
	int msgSize = 0;
	switch(inBuf[0])
	{
		case SDM_Serreqst:
			msgSize = translateSerreqst(inBuf, outBuf, outBufSize);
         break;
      case SDM_Command:
			msgSize = translateCommand(inBuf, outBuf, outBufSize);
         break;
      case SDM_Subreqst:
			msgSize = translateSubreqst(inBuf, outBuf, outBufSize);
         break;
      case SDM_Tat:
			msgSize = translateTat(inBuf, outBuf, outBufSize);
         break;
	}
	return msgSize;
}

/**
* Function used to translate an SDMSerreqst into a SPA-1 Command Msg
*
* @param inBuf A buffer containing a marshalled SDM message
* @param outBuf The buffer which will have the SPA-1 message written into it
* @param outBufSize The size of the output buffer
*
* @return An int containing the size in bytes of the SPA-1 message written into outBuf
*/
int Spa1Translator::translateSerreqst(unsigned char* inBuf, unsigned char* outBuf, size_t outBufSize)
{
	SDMSerreqst serReqstMsg;
	size_t totalSize;
	unsigned short msgSize;

	serReqstMsg.Unmarshal((const char*)inBuf);

	totalSize = SPA1_HEADER_SIZE + SECONDARY_HEADER_LEN + serReqstMsg.length;	//3 Byte header + 2 bytes for int/msg id + data length
	msgSize = totalSize - SPA1_HEADER_SIZE;		//Length in msg sent to ASIM does not include header

	if(totalSize > outBufSize)
	{
		printf("Spa1Manager: Error, output buffer not large enough to hold translated Spa1 serreqst msg\n");
		return -1;
	}

	outBuf[0] = SPA1_ASIM_COMMAND;
	SDM_htons(msgSize);	//Make sure the length is little endian
	memcpy(&outBuf[1], &msgSize, sizeof(msgSize));
	outBuf[3] = serReqstMsg.command_id.getInterface();
	outBuf[4] = serReqstMsg.command_id.getMessage();
	memcpy(&outBuf[5], serReqstMsg.data, serReqstMsg.length);
	debug_f(2, "Spa1Manager: Translated SDMSerreqst msg destined for ASIM %hu\n", serReqstMsg.destination.getSensorID() & 0x00ff);

	return totalSize;
}

/**
* Function used to translate an SDMCommand into a SPA-1 Command Msg
*
* @param inBuf A buffer containing a marshalled SDM message
* @param outBuf The buffer which will have the SPA-1 message written into it
* @param outBufSize The size of the output buffer
*
* @return An int containing the size in bytes of the SPA-1 message written into outBuf
*/
int Spa1Translator::translateCommand(unsigned char* inBuf, unsigned char* outBuf, size_t outBufSize)
{
	SDMCommand commandMsg;
	size_t totalSize;
	unsigned short msgSize;

	commandMsg.Unmarshal((const char*)inBuf);

	totalSize = SPA1_HEADER_SIZE + SECONDARY_HEADER_LEN + commandMsg.length;	//3 Byte header + 2 bytes for int/msg id + data length
	msgSize = totalSize - SPA1_HEADER_SIZE;		//Length in msg sent to ASIM does not include header

	if(totalSize > outBufSize)
	{
		printf("Spa1Manager: Error, output buffer not large enough to hold translated Spa1 command msg\n");
		return -1;
	}

	outBuf[0] = SPA1_ASIM_COMMAND;
	SDM_htons(msgSize);	//Make sure the length is little endian
	memcpy(&outBuf[1], &msgSize, sizeof(msgSize));
	outBuf[3] = commandMsg.command_id.getInterface();
	outBuf[4] = commandMsg.command_id.getMessage();
	memcpy(&outBuf[5], commandMsg.data, commandMsg.length);
	debug_f(2, "Spa1Manager: Translated SDMCommand msg destined for ASIM %hu\n", commandMsg.destination.getSensorID() & 0x00ff);

	return totalSize;
}

/**
* Function used to translate an SDMSubreqst into a SPA-1 Data Request Msg
*
* @param inBuf A buffer containing a marshalled SDM message
* @param outBuf The buffer which will have the SPA-1 message written into it
* @param outBufSize The size of the output buffer
*
* @return An int containing the size in bytes of the SPA-1 message written into outBuf
*/
int Spa1Translator::translateSubreqst(unsigned char* inBuf, unsigned char* outBuf, size_t outBufSize)
{
	SDMSubreqst subReqstMsg;
	size_t totalSize;
	unsigned short msgSize;

	subReqstMsg.Unmarshal((const char*)inBuf);

	totalSize = SPA1_HEADER_SIZE + SECONDARY_HEADER_LEN;	//3 Byte header + 2 bytes for int/msg id
	msgSize = totalSize - SPA1_HEADER_SIZE;		//Length in msg sent to ASIM does not include header

	if(totalSize > outBufSize)
	{
		printf("Spa1Manager: Error, output buffer not large enough to hold translated Spa1 request data msg\n");
		return -1;
	}

	outBuf[0] = SPA1_ASIM_DATAREQ;
	SDM_htons(msgSize);	//Make sure the length is little endian
	memcpy(&outBuf[1], &msgSize, sizeof(msgSize));
	outBuf[3] = subReqstMsg.msg_id.getInterface();
	outBuf[4] = subReqstMsg.msg_id.getMessage();

	debug_f(2, "Spa1Manager: Translated SDMSubreqst msg destined for ASIM %hu\n", subReqstMsg.source.getSensorID() & 0x00ff);

	return totalSize;
}

/**
* Function used to package up a SPA-1 Cancel Data Message
*
* @param intId The interface id of the data to cancel
* @param msgId The message id of the data to cancel
* @param outBuf The buffer which will have the SPA-1 message written into it
* @param outBufSize The size of the output buffer
*
* @return An int containing the size in bytes of the SPA-1 message written into outBuf
*/
int Spa1Translator::packageCancelData(unsigned char intId, unsigned char msgId, unsigned char* outBuf, size_t outBufSize)
{
	size_t totalSize;
	unsigned short msgSize;
	totalSize = SPA1_HEADER_SIZE + SECONDARY_HEADER_LEN;	//3 Byte header + 2 bytes for int/msg id
	msgSize = totalSize - SPA1_HEADER_SIZE;

	if(totalSize > outBufSize)
	{
		printf("Spa1Manager: Error, output buffer not large enough to hold translated Spa1 cancel data msg\n");
		return -1;
	}

	outBuf[0] = SPA1_ASIM_CANCEL_DATA;
	SDM_htons(msgSize);	//Make sure the length is little endian
	memcpy(&outBuf[1], &msgSize, sizeof(msgSize));
	outBuf[3] = intId;
	outBuf[4] = msgId;

	return totalSize;
}

/**
* Function used to translate an SDMTat msg into a SPA-1 Tat Msg
*
* @param inBuf A buffer containing a marshalled SDM message
* @param outBuf The buffer which will have the SPA-1 message written into it
* @param outBufSize The size of the output buffer
*
* @return An int containing the size in bytes of the SPA-1 message written into outBuf
*/
int Spa1Translator::translateTat(unsigned char* inBuf, unsigned char* outBuf, size_t outBufSize)
{
	//TODO
	return 0;
}
