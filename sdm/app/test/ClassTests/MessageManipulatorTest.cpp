#include "../../../common/MessageManipulator/MessageManipulator.h"
#include "../../../common/MessageManager/MessageManager.h"
#include "../../../common/message/SDMxTEDS.h"
#include "../../../common/message/SDMReqReg.h"
#include "../../../common/message/SDMRegInfo.h"
#include "../DMTests/xTEDSPoster.h"

#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

// Message enumeration values
enum { NDMT=0, NDMTI=1, CCMT=2, CCMTI=3, CFMT=4, CFMTI=5, RCMT=6, RCMTI=7, RDRMT=8, RDRMTI=9, RFMT=10, RFMTI=11 };

// Values to get/set into message buffers
const unsigned char UCHAR_VAL = 0x51;
const char CHAR_VAL = 0x77;
const unsigned short USHORT_VAL = 0x3432;
const short SHORT_VAL = 0x7865;
const unsigned long UINT_VAL = 0x89473244;
const long INT_VAL = 0x75884763;
const float FLOAT_VAL = 3.14159;
const double DOUBLE_VAL = 4.545586599;

const unsigned char UCHAR_INVALID = 13;
const char CHAR_INVALID = 13;
const unsigned short USHORT_INVALID = 13;
const short SHORT_INVALID = 13;
const unsigned long UINT_INVALID = 13;
const long INT_INVALID = 13;
const float FLOAT_INVALID = 13.0f;
const double DOUBLE_INVALID = 13.0;

const long NUM_TESTS = 12;
MessageManipulator Manipulators[NUM_TESTS];

const long myPort = 4256;
bool VerifyBufferData(char* Buffer);
bool VerifyBufferDataFault(char* Buffer);
bool CmdMsgSetAll (SDMCommand &cmd, MessageManipulator& mm);
bool CmdMsgSetAllInvalid (SDMCommand &cmd, MessageManipulator& mm);
bool CmdMsgGetAll (SDMCommand& cmd, MessageManipulator& mm);
bool CmdMsgGetAllInvalid (SDMCommand& cmd, MessageManipulator& mm);
bool CmdMsgSetArray(SDMCommand& cmd, MessageManipulator& mm);

bool DataMsgSetAll (SDMData &dat, MessageManipulator& mm, enum msg_type type);
bool DataMsgSetAllInvalid (SDMData &dat, MessageManipulator& mm, enum msg_type type);
bool DataMsgGetAll (SDMData& dat, MessageManipulator& mm, enum msg_type type);
bool DataMsgGetAllInvalid (SDMData& dat, MessageManipulator& mm, enum msg_type type);

bool SerMsgSetAll (SDMService &ser, MessageManipulator& mm);
bool SerMsgSetAllInvalid (SDMService &ser, MessageManipulator& mm);
bool SerMsgGetAll (SDMSerreqst& ser, MessageManipulator& mm);
bool SerMsgGetAllInvalid (SDMSerreqst& ser, MessageManipulator& mm);

int main(int argc,char** argv)
{
	SDMInit(argc, argv);
	xTEDSPoster poster;
	if (poster.PostxTEDS("MessageManipulatorTest.xml") < 0)
	{
		printf("Could not post xTEDs.\n");
		return 0;
	}
	
	MessageManager mm;
	mm.Async_Init(myPort);
	
	printf("Requesting messages...");
	fflush(NULL);
	SDMReqReg req;
	req.destination.setPort(myPort);
	strcpy(req.device,"MessageManipulatorTest");
	strcpy(req.item_name,"NotDatMsgTest");
	req.Send();
	
	strcpy(req.item_name,"CmdCmdMsgTest");
	req.id = CCMT;
	req.Send();
	
	strcpy(req.item_name,"CmdFaultMsgTest");
	req.id = CFMT;
	req.Send();
	
	strcpy(req.item_name,"ReqCmdMsgTest");
	req.id = RCMT;
	req.Send();
	
	strcpy(req.item_name,"ReqDataRplyMsgTest");
	req.id = RDRMT;
	req.Send();
	
	strcpy(req.item_name,"ReqFaultMsgTest");
	req.id = RFMT;
	req.Send();
	
	strcpy(req.item_name,"NotDatMsgTestInvalid");
	req.id = NDMTI;
	req.Send();
	
	strcpy(req.item_name,"CmdCmdMsgTestInvalid");
	req.id = CCMTI;
	req.Send();
	
	strcpy(req.item_name,"CmdFaultMsgTestInvalid");
	req.id = CFMTI;
	req.Send();
	
	strcpy(req.item_name,"ReqCmdMsgTestInvalid");
	req.id = RCMTI;
	req.Send();
	
	strcpy(req.item_name,"ReqDataRplyMsgTestInvalid");
	req.id = RDRMTI;
	req.Send();
	
	strcpy(req.item_name,"ReqFaultMsgTestInvalid");
	req.id = RFMTI;
	req.Send();
	
	int count = 0;
	char buf[BUFSIZE];
	SDMRegInfo info;
	while (count < NUM_TESTS)
	{
		switch(mm.BlockGetMessage(buf))
		{
		case SDM_RegInfo:
			if (info.Unmarshal(buf) > 0)
			{
				printf("%d ",++count);
				fflush(NULL);
				if (Manipulators[info.id].setMsgDef(info.msg_def) == EMPTY)
				{
					printf("%s\n",info.msg_def);
					return 0;
				}
			}
			break;
		default:
			printf("Unexpected message received.\n");
			break;
		}
	}
	printf("...done.\n");
	
/////////////////////////////////////////////////////////////////////////////////////////////////
	// Testing <Command>
	//
	printf("---------------Testing with <Command><CommandMsg>---------------\n");
	SDMCommand cmd;
	CmdMsgSetAll(cmd, Manipulators[CCMT]);
	if (!VerifyBufferData(cmd.data))
	{
		printf("Buffer mismatch.\n");
		return 0;
	}
	if ( !CmdMsgGetAll(cmd, Manipulators[CCMT]) ||
		!CmdMsgSetAllInvalid(cmd, Manipulators[CCMTI]) ||
		!CmdMsgGetAllInvalid(cmd, Manipulators[CCMTI]) )
		return 0;
	if (!CmdMsgSetArray(cmd,Manipulators[CCMT]) )
		return 0;
	printf("---------------<Command><CommandMsg> test done---------------\n");
	// Test functions for SDMData
	SDMData dat;
	
	printf("---------------Testing with <Command><FaultMsg>---------------\n");
	memset(dat.msg, 0, sizeof(dat.msg));
	
	printf("Testing FaultMsg using DATAMSG (should fail)...\n");
	if (!DataMsgSetAll(dat, Manipulators[CCMT], DATAMSG))
		printf(".......passed.\n");
	else
	{
		printf("failed.\n"); return 0;
	}
	
	if (!DataMsgSetAll(dat, Manipulators[CCMT], FAULTMSG))
		return 0;
	if (!VerifyBufferDataFault(dat.msg))
	{
		printf("Buffer mismatch.\n");
		return 0;
	}
	if ( !DataMsgGetAll(dat, Manipulators[CCMT], FAULTMSG) ||
		!DataMsgSetAllInvalid(dat, Manipulators[CCMTI], FAULTMSG) ||
		!DataMsgGetAllInvalid(dat, Manipulators[CCMTI], FAULTMSG) )
		return 0;
	printf("---------------<Command><FaultMsg> test done---------------\n");
	//
	//</Command>
/////////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////////
	// Testing <Notification>
	//	
	printf("---------------Testing with <DataMsg>---------------\n");
	memset(dat.msg, 0, sizeof(dat.msg));
	DataMsgSetAll(dat, Manipulators[NDMT], DATAMSG);
	if (!VerifyBufferData(dat.msg))
	{
		printf("Buffer mismatch.\n");
		return 0;
	}
	if ( !DataMsgGetAll(dat, Manipulators[NDMT], DATAMSG) ||
		!DataMsgSetAllInvalid(dat, Manipulators[NDMTI], DATAMSG) ||
		!DataMsgGetAllInvalid(dat, Manipulators[NDMTI], DATAMSG) )
		return 0;
	printf("---------------<DataMsg> test done---------------\n");
	
	printf("---------------Testing with <FaultMsg>---------------\n");
	memset(dat.msg, 0, sizeof(dat.msg));
	DataMsgSetAll(dat, Manipulators[NDMT], FAULTMSG);
	if (!VerifyBufferDataFault(dat.msg))
	{
		printf("Buffer mismatch.\n");
		return 0;
	}
	if ( !DataMsgGetAll(dat, Manipulators[NDMT], FAULTMSG) ||
		!DataMsgSetAllInvalid(dat, Manipulators[NDMTI], FAULTMSG) ||
		!DataMsgGetAllInvalid(dat, Manipulators[NDMTI], FAULTMSG) )
		return 0;
	printf("---------------<FaultMsg> test done---------------\n");
	//
	//</Notification>
/////////////////////////////////////////////////////////////////////////////////////////////////
	
/////////////////////////////////////////////////////////////////////////////////////////////////
	// Testing <Request>
	//
	SDMService serv;
	SDMSerreqst serq;
	printf("---------------Testing with <Request><Command>---------------\n");
	memset(cmd.data, 0, sizeof(cmd.data));
	if (!CmdMsgSetAll(cmd, Manipulators[RCMT]))
		return 0;
	if (!VerifyBufferData(cmd.data))
	{
		printf("Buffer mismatch.\n");
		return 0;
	}
	if ( !CmdMsgGetAll(cmd, Manipulators[RCMT]) ||
		!CmdMsgSetAllInvalid(cmd, Manipulators[RCMTI]) ||
		!CmdMsgGetAllInvalid(cmd, Manipulators[RCMTI]) )
		return 0;
	printf("---------------<Request><CommandMsg> test done---------------\n");
	
	printf("---------------Testing with <Request><DataMsg>---------------\n");
	memset(dat.msg, 0, sizeof(dat.msg));
	DataMsgSetAll(dat, Manipulators[RCMT], DATAMSG);
	if (!VerifyBufferData(dat.msg))
	{
		printf("Buffer mismatch.\n");
		return 0;
	}
	if ( !DataMsgGetAll(dat, Manipulators[RCMT], DATAMSG) ||
		!DataMsgSetAllInvalid(dat, Manipulators[RCMTI], DATAMSG) ||
		!DataMsgGetAllInvalid(dat, Manipulators[RCMTI], DATAMSG) )
		return 0;
	printf("---------------<Request><DataMsg> test done---------------\n");
	
	printf("---------------Testing with <Request><FaultMsg>---------------\n");
	memset(dat.msg, 0, sizeof(dat.msg));
	DataMsgSetAll(dat, Manipulators[RCMT], FAULTMSG);
	if (!VerifyBufferDataFault(dat.msg))
	{
		printf("Buffer mismatch.\n");
		return 0;
	}
	if ( !DataMsgGetAll(dat, Manipulators[RCMT], FAULTMSG) ||
		!DataMsgSetAllInvalid(dat, Manipulators[RCMTI], FAULTMSG) ||
		!DataMsgGetAllInvalid(dat, Manipulators[RCMTI], FAULTMSG) )
		return 0;
	printf("---------------<Request><FaultMsg> test done---------------\n");
	//
	//</Request>
/////////////////////////////////////////////////////////////////////////////////////////////////
	return 0;
	
}

bool VerifyBufferData(char* Buffer)
{
	char CompareBuffer[128];
	
	PUT_UCHAR(CompareBuffer, UCHAR_VAL);
	PUT_CHAR(&CompareBuffer[1], CHAR_VAL);
	PUT_USHORT(CompareBuffer+2, USHORT_VAL);
	PUT_SHORT(CompareBuffer+4, SHORT_VAL);
	PUT_ULONG(CompareBuffer+6, UINT_VAL);
	PUT_LONG(CompareBuffer+10, INT_VAL);
	PUT_FLOAT(CompareBuffer+14, FLOAT_VAL);
	PUT_DOUBLE(CompareBuffer+18, DOUBLE_VAL);
	for (int i = 0; i < 26; i++)
		if (Buffer[i] != CompareBuffer[i])
			return false;
	return true;
}

bool VerifyBufferDataFault(char* Buffer)
{
	char CompareBuffer[128];
	
	PUT_DOUBLE(CompareBuffer, DOUBLE_VAL);
	PUT_FLOAT(CompareBuffer+8, FLOAT_VAL);
	PUT_LONG(CompareBuffer+12, INT_VAL);
	PUT_ULONG(CompareBuffer+16, UINT_VAL);
	PUT_SHORT(CompareBuffer+20, SHORT_VAL);
	PUT_USHORT(CompareBuffer+22, USHORT_VAL);
	PUT_CHAR(&CompareBuffer[24], CHAR_VAL);
	PUT_UCHAR(&CompareBuffer[25], UCHAR_VAL);
	for (int i = 0; i < 26; i++)
		if (Buffer[i] != CompareBuffer[i])
			return false;
	return true;
}

bool CmdMsgSetAll (SDMCommand &cmd, MessageManipulator& mm)
{
	printf("Testing setValue with SDMCommand - UINT08...");
	if (mm.setValue("VarUChar", cmd, UCHAR_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMCommand - INT08...");
	if (mm.setValue("VarChar", cmd, CHAR_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMCommand - UINT16...");
	if (mm.setValue("VarUShort", cmd, USHORT_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMCommand - INT16...");
	if (mm.setValue("VarShort", cmd, SHORT_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMCommand - UINT32...");
	if (mm.setValue("VarUInt", cmd, UINT_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMCommand - INT32...");
	if (mm.setValue("VarInt", cmd, INT_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMCommand - FLOAT32...");
	if (mm.setValue("VarFloat", cmd, FLOAT_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMCommand - FLOAT64...");
	if (mm.setValue("VarDouble", cmd, DOUBLE_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	return true;
}

bool CmdMsgGetAll (SDMCommand& cmd, MessageManipulator& mm)
{
	if (mm.isMsgValid(cmd))
		printf("isMsgValid test passed.\n");
	else
		printf("isMsgValid test failed.\n");
	
	printf("Testing getUINT08Value() with SDMCommand...");
	if (mm.getUINT08Value ("VarUChar", cmd) == UCHAR_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	bool Valid;
	printf("Testing getUINT08Value() with SDMCommand with Valid returned...");
	if (mm.getUINT08Value ("VarUChar", cmd, &Valid) == UCHAR_VAL && Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT08Value() with SDMCommand...");
	if (mm.getINT08Value ("VarChar", cmd) == CHAR_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT16Value() with SDMCommand...");
	if (mm.getUINT16Value ("VarUShort", cmd) == USHORT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT16Value() with SDMCommand...");
	if (mm.getINT16Value ("VarShort", cmd) == SHORT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT32Value() with SDMCommand...");
	if (mm.getUINT32Value ("VarUInt", cmd) == UINT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT32Value() with SDMCommand...");
	if (mm.getINT32Value ("VarInt", cmd) == INT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT32Value() with SDMCommand...");
	if (mm.getFLOAT32Value ("VarFloat", cmd) == FLOAT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT64Value() with SDMCommand...");
	if (mm.getFLOAT64Value ("VarDouble", cmd) == DOUBLE_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	return true;
}

bool CmdMsgSetAllInvalid (SDMCommand &cmd, MessageManipulator& mm)
{
	if (!mm.setValue("VarUChar", cmd, UCHAR_INVALID) ||
		!mm.setValue("VarChar", cmd, CHAR_INVALID) ||
		!mm.setValue("VarUShort", cmd, USHORT_INVALID) ||
		!mm.setValue("VarShort", cmd, SHORT_INVALID) ||
		!mm.setValue("VarUInt", cmd, UINT_INVALID) ||
		!mm.setValue("VarInt", cmd, INT_INVALID) ||
		!mm.setValue("VarFloat", cmd, FLOAT_INVALID) ||
		!mm.setValue("VarDouble", cmd, DOUBLE_INVALID) )
	{
		printf("CmdMsgSetAllInvalid failed.\n");
		return false;
	}
	return true;
}

/*
	Returns all of the invalid data, the Valid flag should be set to false for each item.
*/
bool CmdMsgGetAllInvalid (SDMCommand& cmd, MessageManipulator& mm)
{
	bool Valid;
	
	if (!mm.isMsgValid(cmd))
		printf("isMsgValid test passed.\n");
	else
	{
		printf("isMsgValid test failed.\n"); return false;
	}
	
	printf("Testing getUINT08Value() with SDMCommand invalid data...");
	if (mm.getUINT08Value ("VarUChar", cmd, &Valid) == UCHAR_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT08Value() with SDMCommand invalid data...");
	if (mm.getINT08Value ("VarChar", cmd, &Valid) == CHAR_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT16Value() with SDMCommand invalid data...");
	if (mm.getUINT16Value ("VarUShort", cmd, &Valid) == USHORT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT16Value() with SDMCommand invalid data...");
	if (mm.getINT16Value ("VarShort", cmd, &Valid) == SHORT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT32Value() with SDMCommand invalid data...");
	if (mm.getUINT32Value ("VarUInt", cmd, &Valid) == UINT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT32Value() with SDMCommand invalid data...");
	if (mm.getINT32Value ("VarInt", cmd, &Valid) == INT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT32Value() with SDMCommand invalid data...");
	if (mm.getFLOAT32Value ("VarFloat", cmd, &Valid) == FLOAT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT64Value() with SDMCommand invalid data...");
	if (mm.getFLOAT64Value ("VarDouble", cmd, &Valid) == DOUBLE_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	return true;
}

bool CmdMsgSetArray(SDMCommand& cmd, MessageManipulator& mm)
{
	char Array[64];
	char *RecvArray;
	for (unsigned int i = 0; i < sizeof(Array); i++)
		Array[i] = i;
	
	printf("Testing setArray with SDMCommand...");
	if (!mm.setArray("VarArray",cmd,Array,sizeof(Array)))
	{
		printf("failed.\n");
		return false;
	}
	printf("passed.\n");
	
	int Length;
	printf("Testing getArray with SDMCommand...");
	
	RecvArray = (char*)mm.getArray("VarArray",cmd,Length);
	if (RecvArray == NULL)
	{
		printf("failed.\n");
		return false;
	}
	
	for (int i = 0; i < Length; i++)
	{
		if (RecvArray[i] != Array[i])
		{
			printf("Buffer mismatch.\n");
			return false;
		}
	}
	printf("passed.\n");
	return true;
}


bool DataMsgSetAll (SDMData &dat, MessageManipulator& mm, enum msg_type type)
{
	printf("Testing setValue with SDMData - UINT08...");
	if (mm.setValue("VarUChar", dat, UCHAR_VAL, type))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMData - INT08...");
	if (mm.setValue("VarChar", dat, CHAR_VAL, type))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMData - UINT16...");
	if (mm.setValue("VarUShort", dat, USHORT_VAL, type))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMData - INT16...");
	if (mm.setValue("VarShort", dat, SHORT_VAL, type))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMData - UINT32...");
	if (mm.setValue("VarUInt", dat, UINT_VAL, type))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMData - INT32...");
	if (mm.setValue("VarInt", dat, INT_VAL, type))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMData - FLOAT32...");
	if (mm.setValue("VarFloat", dat, FLOAT_VAL, type))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMData - FLOAT64...");
	if (mm.setValue("VarDouble", dat, DOUBLE_VAL, type))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	return true;
}

bool DataMsgSetAllInvalid (SDMData &dat, MessageManipulator& mm, enum msg_type type)
{
	if ( 	!mm.setValue("VarUChar", dat, UCHAR_INVALID, type) ||
		!mm.setValue("VarChar", dat, CHAR_INVALID, type) ||
		!mm.setValue("VarUShort", dat, USHORT_INVALID, type) ||
		!mm.setValue("VarShort", dat, SHORT_INVALID, type) ||
		!mm.setValue("VarUInt", dat, UINT_INVALID, type) ||
		!mm.setValue("VarInt", dat, INT_INVALID, type) ||
		!mm.setValue("VarFloat", dat, FLOAT_INVALID, type) ||
		!mm.setValue("VarDouble", dat, DOUBLE_INVALID, type) )
	{
		printf("DataMsgSetAllInvalid failed.\n");
		return false;
	}
	printf("DataMsgSetAllInvalid passed.\n");
	return true;
}

bool DataMsgGetAll (SDMData& dat, MessageManipulator& mm, enum msg_type type)
{
	if (mm.isMsgValid(dat, type))
		printf("isMsgValid test passed.\n");
	else
		printf("isMsgValid test failed.\n");
	
	printf("Testing getUINT08Value() with SDMData...");
	if (mm.getUINT08Value ("VarUChar", dat, type) == UCHAR_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT08Value() with SDMData...");
	if (mm.getINT08Value ("VarChar", dat, type) == CHAR_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT16Value() with SDMData...");
	if (mm.getUINT16Value ("VarUShort", dat, type) == USHORT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT16Value() with SDMData...");
	if (mm.getINT16Value ("VarShort", dat, type) == SHORT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT32Value() with SDMData...");
	if (mm.getUINT32Value ("VarUInt", dat, type) == UINT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT32Value() with SDMData...");
	if (mm.getINT32Value ("VarInt", dat, type) == INT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT32Value() with SDMData...");
	if (mm.getFLOAT32Value ("VarFloat", dat, type) == FLOAT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT64Value() with SDMData...");
	if (mm.getFLOAT64Value ("VarDouble", dat, type) == DOUBLE_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	return true;
}

bool DataMsgGetAllInvalid (SDMData& dat, MessageManipulator& mm, enum msg_type type)
{
	bool Valid;
	
	if (!mm.isMsgValid(dat, type))
		printf("isMsgValid test passed.\n");
	else
	{
		printf("isMsgValid test failed.\n"); return false;
	}
	
	printf("Testing getUINT08Value() with SDMData invalid data...");
	if (mm.getUINT08Value ("VarUChar", dat, type, &Valid) == UCHAR_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT08Value() with SDMData invalid data...");
	if (mm.getINT08Value ("VarChar", dat, type, &Valid) == CHAR_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT16Value() with SDMData invalid data...");
	if (mm.getUINT16Value ("VarUShort", dat, type, &Valid) == USHORT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT16Value() with SDMData invalid data...");
	if (mm.getINT16Value ("VarShort", dat, type, &Valid) == SHORT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT32Value() with SDMData invalid data...");
	if (mm.getUINT32Value ("VarUInt", dat, type, &Valid) == UINT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT32Value() with SDMData invalid data...");
	if (mm.getINT32Value ("VarInt", dat, type, &Valid) == INT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT32Value() with SDMData invalid data...");
	if (mm.getFLOAT32Value ("VarFloat", dat, type, &Valid) == FLOAT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT64Value() with SDMData invalid data...");
	if (mm.getFLOAT64Value ("VarDouble", dat, type, &Valid) == DOUBLE_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	return true;
}

bool SerMsgSetAll (SDMService &ser, MessageManipulator& mm)
{
	printf("Testing setValue with SDMService - UINT08...");
	if (mm.setValue("VarUChar", ser, UCHAR_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMService - INT08...");
	if (mm.setValue("VarChar", ser, CHAR_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMService - UINT16...");
	if (mm.setValue("VarUShort", ser, USHORT_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMService - INT16...");
	if (mm.setValue("VarShort", ser, SHORT_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMService - UINT32...");
	if (mm.setValue("VarUInt", ser, UINT_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMService - INT32...");
	if (mm.setValue("VarInt", ser, INT_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMService - FLOAT32...");
	if (mm.setValue("VarFloat", ser, FLOAT_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing setValue with SDMService - FLOAT64...");
	if (mm.setValue("VarDouble", ser, DOUBLE_VAL))
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	return true;
}

bool SerMsgSetAllInvalid (SDMService &ser, MessageManipulator& mm)
{
	if (!mm.setValue("VarUChar", ser, UCHAR_INVALID) ||
		!mm.setValue("VarChar", ser, CHAR_INVALID) ||
		!mm.setValue("VarUShort", ser, USHORT_INVALID) ||
		!mm.setValue("VarShort", ser, SHORT_INVALID) ||
		!mm.setValue("VarUInt", ser, UINT_INVALID) ||
		!mm.setValue("VarInt", ser, INT_INVALID) ||
		!mm.setValue("VarFloat", ser, FLOAT_INVALID) ||
		!mm.setValue("VarDouble", ser, DOUBLE_INVALID) )
	{
		printf("SerMsgSetAllInvalid failed.\n");
		return false;
	}
	return true;
}

bool SerMsgGetAll (SDMSerreqst& ser, MessageManipulator& mm)
{
	if (mm.isMsgValid(ser))
		printf("isMsgValid test passed.\n");
	else
		printf("isMsgValid test failed.\n");
	
	printf("Testing getUINT08Value() with SDMSerreqst...");
	if (mm.getUINT08Value ("VarUChar", ser) == UCHAR_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT08Value() with SDMSerreqst...");
	if (mm.getINT08Value ("VarChar", ser) == CHAR_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT16Value() with SDMSerreqst...");
	if (mm.getUINT16Value ("VarUShort", ser) == USHORT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT16Value() with SDMSerreqst...");
	if (mm.getINT16Value ("VarShort", ser) == SHORT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT32Value() with SDMSerreqst...");
	if (mm.getUINT32Value ("VarUInt", ser) == UINT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT32Value() with SDMSerreqst...");
	if (mm.getINT32Value ("VarInt", ser) == INT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT32Value() with SDMSerreqst...");
	if (mm.getFLOAT32Value ("VarFloat", ser) == FLOAT_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT64Value() with SDMSerreqst...");
	if (mm.getFLOAT64Value ("VarDouble", ser) == DOUBLE_VAL)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	return true;
}

bool SerMsgGetAllInvalid (SDMSerreqst& ser, MessageManipulator& mm)
{
	bool Valid;
	
	if (!mm.isMsgValid(ser))
		printf("isMsgValid test passed.\n");
	else
	{
		printf("isMsgValid test failed.\n"); return false;
	}
	
	printf("Testing getUINT08Value() with SDMSerreqst invalid data...");
	if (mm.getUINT08Value ("VarUChar", ser, &Valid) == UCHAR_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT08Value() with SDMSerreqst invalid data...");
	if (mm.getINT08Value ("VarChar", ser, &Valid) == CHAR_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT16Value() with SDMSerreqst invalid data...");
	if (mm.getUINT16Value ("VarUShort", ser, &Valid) == USHORT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT16Value() with SDMSerreqst invalid data...");
	if (mm.getINT16Value ("VarShort", ser, &Valid) == SHORT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getUINT32Value() with SDMSerreqst invalid data...");
	if (mm.getUINT32Value ("VarUInt", ser, &Valid) == UINT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getINT32Value() with SDMSerreqst invalid data...");
	if (mm.getINT32Value ("VarInt", ser, &Valid) == INT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT32Value() with SDMSerreqst invalid data...");
	if (mm.getFLOAT32Value ("VarFloat", ser, &Valid) == FLOAT_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	
	printf("Testing getFLOAT64Value() with SDMSerreqst invalid data...");
	if (mm.getFLOAT64Value ("VarDouble", ser, &Valid) == DOUBLE_INVALID && !Valid)
		printf("passed.\n");
	else
	{
		printf("failed.\n"); return false;
	}
	return true;
}

