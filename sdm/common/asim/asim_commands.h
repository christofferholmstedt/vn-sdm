#ifndef __ASIM_COMMANDS_H
#define __ASIM_COMMANDS_H

//The following are codes for messages to an ASIM
#define ASIM_INITIALIZE		'I'
#define ASIM_RESET		'R'
#define ASIM_SELF_TEST		'T'
#define ASIM_REQ_DATA		'M'
#define ASIM_CANCEL		'C'
#define ASIM_REQ_STREAM		'N'
#define ASIM_POWER_ON		'P'
#define ASIM_POWER_DOWN		'F'
#define ASIM_REQ_VERSION	'U'
#define ASIM_COMMAND		'V'
#define ASIM_REQ_XTEDS		'X'
#define ASIM_TIME_AT_TONE	'O'

//The following are codes for messages from an ASIM
#define ASIM_STATUS		'S'
#define ASIM_XTEDS		'X'
#define ASIM_XTEDS_ID_PAIR	'Y'
#define ASIM_DATA		'D'
#define ASIM_VERSION		'V'

//used to return an error from the ASIM::read function
#define ASIM_ERROR		'e'
#define ASIM_TIMEOUT		't'

#define ASIM_MAX_IN		64

/*Win32 needs a bigger buffer to do ASIM reads*/
#ifdef WIN32
	#define ASIM_MAX_OUT	4096
#else
	#define ASIM_MAX_OUT		64
#endif

#endif
