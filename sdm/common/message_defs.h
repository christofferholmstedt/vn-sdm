// SDM message definitions
//		Rev 0.1		Cannon, 1/05
//		Rev 0.2		Cannon, 1/19
//		Rev 0.71	Sundberg, 13APR2005
#ifndef __MESSAGE_DEFS_H_
#define __MESSAGE_DEFS_H_

//Message types
#define SDM_RegPM		'a'	/*formerly SDM_ReqTask*/
#define SDM_Task		'b'
#define SDM_ReqCode		'c'
#define SDM_Code		'd'
#define SDM_Kill		'e'	/*CMDKillProc*/
#define SDM_Preempt		'f'
#define SDM_ProcStatus		'g'
#define SDM_Heartbeat		'h'
#define SDM_PostTask		'i'	/*CMDPostTask*/
#define SDM_ChgPriority		'j'
#define SDM_ChgMode		'k'
#define SDM_Consume		'l'	/*CMDSubscribe*/
#define SDM_Cancel		'm'	/*CMDCancelSub*/
#define SDM_ReqReg		'n'	/*CMDReqReg*/
#define SDM_RegInfo		'o'	/*CMDRegInfo*/
#define SDM_SubError		'p'
#define SDM_xTEDS		'q'	/*CMDxTEDS*/
#define SDM_CancelxTEDS		'r'	/*CMDCancelxTEDS*/
#define SDM_SensorCtrl		's'
#define SDM_Data		't'	/*CMDPublish*/
#define SDM_Subreqst		'u'	/*CMDSubreqst*/
#define SDM_Deletesub		'v'	/*CMDDeletesub*/
#define SDM_ReqMode		'w'
#define SDM_Service		'x'	/*no equivalent*/
#define SDM_Serreqst		'y'	/*no equivalent*/
#define SDM_Command		'z'	/*no equivalent*/
#define SDM_ReqxTEDS		'A'	/*no equivalent*/
#define SDM_xTEDSInfo		'B'	/*no equivalent*/
#define SDM_Error		'C'	/*no equivalent*/
#define SDM_Ready		'D'	/*no equivalent*/
#define SDM_TaskFinished	'E'	/*no equivalent*/
#define SDM_ReqPort		'F'	/*no equivalent*/
#define SDM_ACK			'G'	/*no equivalent*/
#define SDM_Tat			'H'	/*no equivalent*/
#define SDM_Search		'I'	/*no equivalent*/
#define SDM_SearchReply		'J'	/*no equivalent*/
#define SDM_DMLeader		'K'	/*no equivalent*/
#define SDM_Election		'L'	/*no equivalent*/
#define SDM_xTEDSUpdate		'M'	/*no equivalent*/
#define SDM_VarReq		'N'	/*no equivalent*/
#define SDM_VarInfo		'O'	/*no equivalent*/
#define SDM_Hello       'P'
#define SDM_Register    'Q'
#define SDM_ID          'R'
#define SDM_WritexTEDS		'W'	/*no equivalent*/
#define SDM_TaskError		'T'

//Error codes
#define SDM_ERROR_CODE_NOT_FOUND	0x01
#define SDM_ERROR_SUBSCRIPTION_REJECTED	0x02
#define SDM_ERROR_INVALID_XTEDS		0x03
#define SDM_ERROR_COMMAND_REJECTED	0x04

//TM Mode codes
#define MODE_SOFT_RESET                 1
#define MODE_HARD_RESET			2

//Ports for managers
#define PORT_TM		3510		/*port for Task Manager*/
#define PORT_TM_MONITOR	3511		/*port for Task Manager monitor process*/
#define PORT_DM		3504		/*port for Data Manager*/
#define PORT_DM_ELECTION 3505		/*port for Data Manager elections to take place*/
#define PORT_DM_TEMP	3509		/*temporary port used by the DM for IPC*/
#define PORT_DM_MONITOR	3513		/*port for Data Manager monitor process*/
#define PORT_SM		3506		/*port for Sensor Manager*/
#define PORT_SM_MONITOR	3507		/*port for Sensor Manager monitor process*/
#define PORT_PM		3508		/*port for Process Manager*/
#define PORT_PM_MONITOR	3512		/*port for Process Manager monitor process*/
#define PORT_SPA1_MANAGER 3514  /*port for SPA-1 Manager*/
#define PORT_APP_START	4000		/*the first port assigned to applications*/
#define PORT_APP_MAX	65535		/*the max port number that can be assigned to applications*/

// BUFSIZE is the largest size for a UDP datagram
// LARGE_MSG_BUFSIZE should be used any time SDMxTEDS is to be received in a message buffer
#define BUFSIZE		24288		/*maximum size of a SDM message*/
#if BUFSIZE < 24288
  // If BUFSIZE is relatively small, transmit large xTEDS via TCP, otherwise
  // it is assumed that an xTEDS can fit in a datagram
#  define TCP_TRANSMIT_OF_LARGE_XTEDS	1
#  define LARGE_MSG_BUFSIZE	3*8096		// Upper bound on SDMxTEDS message size
#else // BUFSIZE >= 24288
#  define LARGE_MSG_BUFSIZE	BUFSIZE
#endif // #if BUFSIZE < 24288

#define XTEDS_MAX_ITEM_NAME_SIZE	33
#define MSG_DEF_SIZE	(BUFSIZE-27)/2	/*Max size for a message def*/

//Number of retries for SDMxTEDS and SDMCancelxTEDS
#ifdef __uClinux__
#define NUMRETRIES 99999
#else
#define NUMRETRIES 5
#endif

//Minimum time for heartbeat messages to be sent in seconds
#define HEARTBEAT_INTERVAL 5

#define MAXSTRLEN     8
#define MAX_FILENAME_SIZE 128
#define MAX_TCP_CONNECTIONS 10

//optional compile-time flags

#endif
