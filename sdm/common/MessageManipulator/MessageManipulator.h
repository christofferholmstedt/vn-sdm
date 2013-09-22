#ifndef __MESSAGE_MANIPULATOR_H_
#define __MESSAGE_MANIPULATOR_H_
#include <pthread.h>
#include "../message/SDMData.h"
#include "../message/SDMRegInfo.h"
#include "../message/SDMService.h"
#include "../message/SDMCommand.h"
#include "../message/SDMSerreqst.h"
#include "../message/SDMMessage_ID.h"

extern "C"
{
#include "message.h"
}

/*The SDMMessageManipulator class is intended to marshall and unmarshal arbitrary SDM messages based on a message def*/

class SDMLIB_API MessageManipulator
{
public:
	MessageManipulator();
	~MessageManipulator();

	enum wrapper_type setMsgDef(char* msgdef);
	enum wrapper_type setMsgDef(SDMRegInfo&);

	int getLength(enum msg_type type);

	bool isMsgValid(const SDMData& DatMsg, enum msg_type type);
	unsigned char getUINT08Value(char* name, SDMData&, enum msg_type type, bool* IsValid = NULL);
	signed char getINT08Value(char* name, SDMData&, enum msg_type type, bool* IsValid = NULL);
	unsigned short getUINT16Value(char* name, SDMData&, enum msg_type type, bool* IsValid = NULL);
	short getINT16Value(char* name, SDMData&, enum msg_type type, bool* IsValid = NULL);
	unsigned long getUINT32Value(char* name, SDMData&, enum msg_type type, bool* IsValid = NULL);
	long getINT32Value(char* name, SDMData& ,enum msg_type type, bool* IsValid = NULL);
	float getFLOAT32Value(char* name, SDMData&, enum msg_type type, bool* IsValid = NULL);
	double getFLOAT64Value(char* name, SDMData&, enum msg_type type, bool* IsValid = NULL);
	
	bool isMsgValid(const SDMCommand& CmdMsg);
	unsigned char getUINT08Value(char* name, SDMCommand&, bool* IsValid = NULL);
	signed char getINT08Value(char* name, SDMCommand&, bool* IsValid = NULL);
	unsigned short getUINT16Value(char* name, SDMCommand&, bool* IsValid = NULL);
	short getINT16Value(char* name, SDMCommand&, bool* IsValid = NULL);
	unsigned long getUINT32Value(char* name, SDMCommand&, bool* IsValid = NULL);
	long getINT32Value(char* name, SDMCommand&, bool* IsValid = NULL);
	float getFLOAT32Value(char* name, SDMCommand&, bool* IsValid = NULL);
	double getFLOAT64Value(char* name, SDMCommand&, bool* IsValid = NULL);
	
	bool isMsgValid(const SDMSerreqst& ReqMsg);
	unsigned char getUINT08Value(char* name, SDMSerreqst&, bool* IsValid = NULL);
	signed char getINT08Value(char* name, SDMSerreqst&, bool* IsValid = NULL);
	unsigned short getUINT16Value(char* name, SDMSerreqst&, bool* IsValid = NULL);
	short getINT16Value(char* name, SDMSerreqst&, bool* IsValid = NULL);
	unsigned long getUINT32Value(char* name, SDMSerreqst&, bool* IsValid = NULL);
	long getINT32Value(char* name, SDMSerreqst&, bool* IsValid = NULL);
	float getFLOAT32Value(char* name, SDMSerreqst&, bool* IsValid = NULL);
	double getFLOAT64Value(char* name, SDMSerreqst&, bool* IsValid = NULL);
	
	void* getArray(char* name, SDMData &, enum msg_type type,int &length);
	void* getArray(char* name, SDMService &, int &length);
	void* getArray(char* name, SDMCommand &, int &length);
	
	bool setArray(char* name, SDMData &, enum msg_type type, const void* buffer, int length);
	bool setArray(char* name, SDMService &, const void* buffer, int length);
	bool setArray(char* name, SDMCommand &, const void* buffer, int length);

	bool setValue(char* name, SDMService&, unsigned char value);
	bool setValue(char* name, SDMService&, char value);
	bool setValue(char* name, SDMService&, unsigned short value);
	bool setValue(char* name, SDMService&, short value);
	bool setValue(char* name, SDMService&, unsigned long value);
	bool setValue(char* name, SDMService&, long value);
	bool setValue(char* name, SDMService&, float value);
	bool setValue(char* name, SDMService&, double value);
	
	bool setValue(char* name, SDMCommand&, unsigned char value);
	bool setValue(char* name, SDMCommand&, char value);
	bool setValue(char* name, SDMCommand&, unsigned short value);
	bool setValue(char* name, SDMCommand&, short value);
	bool setValue(char* name, SDMCommand&, unsigned long value);
	bool setValue(char* name, SDMCommand&, long value);
	bool setValue(char* name, SDMCommand&, float value);
	bool setValue(char* name, SDMCommand&, double value);
	
	bool setValue(char* name, SDMData&, unsigned char value, enum msg_type type);
	bool setValue(char* name, SDMData&, char value, enum msg_type type);
	bool setValue(char* name, SDMData&, unsigned short value, enum msg_type type);
	bool setValue(char* name, SDMData&, short value, enum msg_type type);
	bool setValue(char* name, SDMData&, unsigned long value, enum msg_type type);
	bool setValue(char* name, SDMData&, long value ,enum msg_type type);
	bool setValue(char* name, SDMData&, float value, enum msg_type type);
	bool setValue(char* name, SDMData&, double value, enum msg_type type);
	
	SDMMessage_ID getMsgID(enum msg_type type);
	enum wrapper_type getType() { return Msg.type; }
	
	void applyGetScaleFactor(bool apply);
private:
	value_t getValue(char* name,SDMData&,enum msg_type type, bool* IsValid);
	value_t getValue(char* name,SDMCommand&, bool* IsValid);
	value_t getValue(char* name,SDMSerreqst&, bool* IsValid);
	value_t getValue(const char* Buffer, var* Variable, bool* IsValid);
	bool setValue(char* name,SDMService& request,value_t val);
	bool setValue(char* name,SDMCommand& command,value_t val);
	bool setValue(char* name,SDMData& data,value_t val,enum msg_type type);
	bool setValue(char* Buffer, var* Variable, value_t Value);
	bool isMsgValid(const char* Buffer, var* Variable);
	msg Msg;
	bool scaled;
	static pthread_mutex_t ParseMutex;
};

#endif
