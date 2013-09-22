#ifndef __SPA1_TRANSLATOR_H__
#define __SPA1_TRANSLATOR_H__

#include "Spa1Asim.h"
#include "../common/Debug.h"
#include "../common/message/SDMSerreqst.h"
#include "../common/message/SDMCommand.h"
#include "../common/message/SDMSubreqst.h"
#include "../common/message/SDMDeletesub.h"

#define SECONDARY_HEADER_LEN	2

#define SPA1_ASIM_COMMAND		'V'
#define SPA1_ASIM_DATAREQ		'M'
#define SPA1_ASIM_CANCEL_DATA	'C'
#define SPA1_ASIM_TAT			'O'

/**
* @class Spa1Translator
*
* @brief Defines the Spa1Translator object for use by the SPA-1 Sensor Manager
*
* The Spa1Translator takes a message in SDM format and translates that message into
* its equivalent SPA-1 protocol form.  It is also used for packaging SPA-1 messages
* to cancel a data stream.
*
* @author Bryan Hansen
* @date 1/13/2010
*/
class Spa1Translator
{
public:
	Spa1Translator();

	int translateToSpa1(unsigned char* inBuf, unsigned char* outBuf, size_t outBufSize);
	int packageCancelData(unsigned char intId, unsigned char msgId, unsigned char* outBuf, size_t outBufSize);

private:
	int translateSerreqst(unsigned char* inBuf, unsigned char* outBuf, size_t outBufSize);
	int translateCommand(unsigned char* inBuf, unsigned char* outBuf, size_t outBufSize);
	int translateSubreqst(unsigned char* inBuf, unsigned char* outBuf, size_t outBufSize);
	int translateTat(unsigned char* inBuf, unsigned char* outBuf, size_t outBufSize);

};

#endif
