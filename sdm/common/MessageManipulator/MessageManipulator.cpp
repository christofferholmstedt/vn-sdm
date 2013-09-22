#include "MessageManipulator.h"
#include "../marshall.h"

#include <string.h>

pthread_mutex_t MessageManipulator::ParseMutex = PTHREAD_MUTEX_INITIALIZER;

static value_t cast(value_t val,enum value_type val_type)
{
	if(val.type != val_type) //then cast
	{
		switch(val_type)
		{
		case _UINT08:
			switch(val.type)
			{
			case _UINT08:
				val.value.uint08 = (unsigned char)val.value.uint08;
				break;
			case _INT08:
				val.value.uint08 = (unsigned char)val.value.int08;
				break;
			case _UINT16:
				val.value.uint08 = (unsigned char)val.value.uint16;
				break;
			case _INT16:
				val.value.uint08 = (unsigned char)val.value.int16;
				break;
			case _UINT32:
				val.value.uint08 = (unsigned char)val.value.uint32;
				break;
			case _INT32:
				val.value.uint08 = (unsigned char)val.value.int32;
				break;
			case _FLOAT32:
				val.value.uint08 = (unsigned char)val.value.float32;
				break;
			case _FLOAT64:
				val.value.uint08 = (unsigned char)val.value.float64;
				break;
			case _EMPTY:
				break;
			}
			break;
		case _INT08:
			switch(val.type)
			{
			case _UINT08:
				val.value.int08 = (char)val.value.uint08;
				break;
			case _INT08:
				val.value.int08 = (char)val.value.int08;
				break;
			case _UINT16:
				val.value.int08 = (char)val.value.uint16;
				break;
			case _INT16:
				val.value.int08 = (char)val.value.int16;
				break;
			case _UINT32:
				val.value.int08 = (char)val.value.uint32;
				break;
			case _INT32:
				val.value.int08 = (char)val.value.int32;
				break;
			case _FLOAT32:
				val.value.int08 = (char)val.value.float32;
				break;
			case _FLOAT64:
				val.value.int08 = (char)val.value.float64;
				break;
			case _EMPTY:
				break;
			}
			break;
		case _UINT16:
			switch(val.type)
			{
			case _UINT08:
				val.value.uint16 = (unsigned short)val.value.uint08;
				break;
			case _INT08:
				val.value.uint16 = (unsigned short)val.value.int08;
				break;
			case _UINT16:
				val.value.uint16 = (unsigned short)val.value.uint16;
				break;
			case _INT16:
				val.value.uint16 = (unsigned short)val.value.int16;
				break;
			case _UINT32:
				val.value.uint16 = (unsigned short)val.value.uint32;
				break;
			case _INT32:
				val.value.uint16 = (unsigned short)val.value.int32;
				break;
			case _FLOAT32:
				val.value.uint16 = (unsigned short)val.value.float32;
				break;
			case _FLOAT64:
				val.value.uint16 = (unsigned short)val.value.float64;
				break;
			case _EMPTY:
				break;
			}
			break;
		case _INT16:
			switch(val.type)
			{
			case _UINT08:
				val.value.int16 = (short)val.value.uint08;
				break;
			case _INT08:
				val.value.int16 = (short)val.value.int08;
				break;
			case _UINT16:
				val.value.int16 = (short)val.value.uint16;
				break;
			case _INT16:
				val.value.int16 = (short)val.value.int16;
				break;
			case _UINT32:
				val.value.int16 = (short)val.value.uint32;
				break;
			case _INT32:
				val.value.int16 = (short)val.value.int32;
				break;
			case _FLOAT32:
				val.value.int16 = (short)val.value.float32;
				break;
			case _FLOAT64:
				val.value.int16 = (short)val.value.float64;
				break;
			case _EMPTY:
				break;
			}
			break;
		case _UINT32:
			switch(val.type)
			{
			case _UINT08:
				val.value.uint32 = (unsigned long)val.value.uint08;
				break;
			case _INT08:
				val.value.uint32 = (unsigned long)val.value.int08;
				break;
			case _UINT16:
				val.value.uint32 = (unsigned long)val.value.uint16;
				break;
			case _INT16:
				val.value.uint32 = (unsigned long)val.value.int16;
				break;
			case _UINT32:
				val.value.uint32 = (unsigned long)val.value.uint32;
				break;
			case _INT32:
				val.value.uint32 = (unsigned long)val.value.int32;
				break;
			case _FLOAT32:
				val.value.uint32 = (unsigned long)val.value.float32;
				break;
			case _FLOAT64:
				val.value.uint32 = (unsigned long)val.value.float64;
				break;
			case _EMPTY:
				break;
			}
			break;
		case _INT32:
			switch(val.type)
			{
			case _UINT08:
				val.value.int32 = (long)val.value.uint08;
				break;
			case _INT08:
				val.value.int32 = (long)val.value.int08;
				break;
			case _UINT16:
				val.value.int32 = (long)val.value.uint16;
				break;
			case _INT16:
				val.value.int32 = (long)val.value.int16;
				break;
			case _UINT32:
				val.value.int32 = (long)val.value.uint32;
				break;
			case _INT32:
				val.value.int32 = (long)val.value.int32;
				break;
			case _FLOAT32:
				val.value.int32 = (long)val.value.float32;
				break;
			case _FLOAT64:
				val.value.int32 = (long)val.value.float64;
				break;
			case _EMPTY:
				break;
			}
			break;
		case _FLOAT32:
			switch(val.type)
			{
			case _UINT08:
				val.value.float32 = (float)val.value.uint08;
				break;
			case _INT08:
				val.value.float32 = (float)val.value.int08;
				break;
			case _UINT16:
				val.value.float32 = (float)val.value.uint16;
				break;
			case _INT16:
				val.value.float32 = (float)val.value.int16;
				break;
			case _UINT32:
				val.value.float32 = (float)val.value.uint32;
				break;
			case _INT32:
				val.value.float32 = (float)val.value.int32;
				break;
			case _FLOAT32:
				val.value.float32 = (float)val.value.float32;
				break;
			case _FLOAT64:
				val.value.float32 = (float)val.value.float64;
				break;
			case _EMPTY:
				break;
			}
			break;
		case _FLOAT64:
			switch(val.type)
			{
			case _UINT08:
				val.value.float64 = (double)val.value.uint08;
				break;
			case _INT08:
				val.value.float64 = (double)val.value.int08;
				break;
			case _UINT16:
				val.value.float64 = (double)val.value.uint16;
				break;
			case _INT16:
				val.value.float64 = (double)val.value.int16;
				break;
			case _UINT32:
				val.value.float64 = (double)val.value.uint32;
				break;
			case _INT32:
				val.value.float64 = (double)val.value.int32;
				break;
			case _FLOAT32:
				val.value.float64 = (double)val.value.float32;
				break;
			case _FLOAT64:
				val.value.float64 = (double)val.value.float64;
				break;
			case _EMPTY:
				break;
			}
			break;
		case _EMPTY:
			break;
		}
	}
	return val;
}

MessageManipulator::MessageManipulator():Msg(),scaled(false)
{
	memset(&Msg,0,sizeof(msg));
}

MessageManipulator::~MessageManipulator()
{
	//Free the message defs tree
	deleteMessage(&Msg);
}
enum wrapper_type MessageManipulator::setMsgDef(char* msgdef)
{
	pthread_mutex_lock(&ParseMutex);
	parse(msgdef,&Msg);
	pthread_mutex_unlock(&ParseMutex);
	return Msg.type;
}

enum wrapper_type MessageManipulator::setMsgDef(SDMRegInfo& info)
{
	return setMsgDef(info.msg_def);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//             GET FUNCTIONS
//
//////////////////////////////////////////////////////////////////////////////////////////////

int MessageManipulator::getLength(enum msg_type type)
{
	switch(type)
	{
		case COMMANDMSG:
			if (Msg.command == NULL) return -1;
			return Msg.command->length;
			break;
		case DATAMSG:
			if (Msg.data == NULL) return -1;
			return Msg.data->length;
			break;
		case FAULTMSG:
			if (Msg.fault == NULL) return -1;
			return Msg.fault->length;
			break;
	}
	return -1;
}

void* MessageManipulator::getArray(char* name,SDMData& dat,enum msg_type type,int& length)
{
        var* temp = NULL;

	if (type == DATAMSG)
	{
		if (Msg.data == NULL) 
			return NULL;
		else
			temp = find(name,Msg.data->list);
	}
	else if (type == FAULTMSG)
	{
		if (Msg.fault == NULL)
			return NULL;
		else
			temp = find(name,Msg.fault->list);
	}
	
	if(temp != NULL)
	{
		length = temp->length;
		return (void*)(dat.msg + temp->start);
	}
	return NULL;
}

void* MessageManipulator::getArray(char* name,SDMService& ser,int& length)
{
	var* temp;
	
	if (Msg.command == NULL) return NULL;
	temp = find(name,Msg.command->list);
	if (temp != NULL)
	{
		length = temp->length;
		return (void*)(ser.data + temp->start);
	}
	return NULL;
}

void* MessageManipulator::getArray(char* name,SDMCommand& cmd,int& length)
{
	return getArray(name,static_cast<SDMService&>(cmd),length);
}

value_t MessageManipulator::getValue(const char* Buffer, var* Variable, bool* IsValid)
{
	value_t val;
  val.type = _EMPTY;
  val.value.uint32 = 0;

	if (Buffer == NULL || Variable == NULL) 
  {
    return val;
  }

  int start = Variable->start;

	if (IsValid != NULL)
  {
		*IsValid = true;
  }

	switch(Variable->type)
	{
		case _UINT08:
			val.type = _UINT08;
			val.value.uint08 = GET_UCHAR(&(Buffer[start]));
			
			// If the value is equal to its invalid value, and an invalid value has been specified
			if (IsValid != NULL && Variable->invalid_data.type != _EMPTY && val.value.uint08 == Variable->invalid_data.value.uint08)
				*IsValid = false;
			
			// Check if the value should be scaled
			if(scaled)
				val.value.uint08 = static_cast<unsigned char>(val.value.uint08 * Variable->scale_factor);
			break;
		case _INT08:
			val.type = _INT08;
			val.value.int08 = GET_CHAR(&(Buffer[start]));
			
			// If the value is equal to its invalid value, and an invalid value has been specified
			if (IsValid != NULL && Variable->invalid_data.type != _EMPTY && val.value.int08 == Variable->invalid_data.value.int08)
				*IsValid = false;
			
			// Check if the value should be scaled
			if(scaled)
				val.value.int08 = static_cast<char>(val.value.int08 * Variable->scale_factor);
			break;
		case _UINT16:
			val.type = _UINT16;
			val.value.uint16 = GET_USHORT(&(Buffer[start]));
			
			// If the value is equal to its invalid value, and an invalid value has been specified
			if (IsValid != NULL && Variable->invalid_data.type != _EMPTY && val.value.uint16 == Variable->invalid_data.value.uint16)
				*IsValid = false;
			
			// Check if the value should be scaled
			if(scaled)
				val.value.uint16 = static_cast<unsigned short>(val.value.uint16 * Variable->scale_factor);
			break;
		case _INT16:
			val.type = _INT16;
			val.value.int16 = GET_SHORT(&(Buffer[start]));
			
			// If the value is equal to its invalid value, and an invalid value has been specified
			if (IsValid != NULL && Variable->invalid_data.type != _EMPTY && val.value.int08 == Variable->invalid_data.value.int08)
				*IsValid = false;
			
			// Check if the value should be scaled
			if(scaled)
				val.value.int16 = static_cast<short>(val.value.int16 * Variable->scale_factor);
			break;
		case _UINT32:
			val.type = _UINT32;
			val.value.uint32 = GET_ULONG(&(Buffer[start]));
			
			// If the value is equal to its invalid value, and an invalid value has been specified
			if (IsValid != NULL && Variable->invalid_data.type != _EMPTY && val.value.uint32 == Variable->invalid_data.value.uint32)
				*IsValid = false;
			
			// Check if the value should be scaled
			if(scaled)
				val.value.uint32 = static_cast<unsigned long>(val.value.uint32 * Variable->scale_factor);
			break;
		case _INT32:
			val.type = _INT32;
			val.value.int32 = GET_LONG(&(Buffer[start]));
			
			// If the value is equal to its invalid value, and an invalid value has been specified
			if (IsValid != NULL && Variable->invalid_data.type != _EMPTY && val.value.int32 == Variable->invalid_data.value.int32)
				*IsValid = false;
			
			// Check if the value should be scaled
			if(scaled)
				val.value.int32 = static_cast<long>(val.value.int32 * Variable->scale_factor);
			break;
		case _FLOAT32:
			val.type = _FLOAT32;
			val.value.float32 = GET_FLOAT(&(Buffer[start]));
			
			// If the value is equal to its invalid value, and an invalid value has been specified
			if (IsValid != NULL && Variable->invalid_data.type != _EMPTY && val.value.float32 == Variable->invalid_data.value.float32)
				*IsValid = false;
			
			// Check if the value should be scaled
			if(scaled)
				val.value.float32 = static_cast<float>(val.value.float32 * Variable->scale_factor);
			break;
		case _FLOAT64:
			val.type = _FLOAT64;
			val.value.float64 = GET_DOUBLE(&(Buffer[start]));
			
			// If the value is equal to its invalid value, and an invalid value has been specified
			if (IsValid != NULL && Variable->invalid_data.type != _EMPTY && val.value.float64 == Variable->invalid_data.value.float64)
				*IsValid = false;
			
			// Check if the value should be scaled
			if(scaled)
				val.value.float64 = static_cast<double>(val.value.float64 * Variable->scale_factor);
			break;
		case _EMPTY:
			break;
	}
	return val;
}

//////////////////////     Gets for SDMData      //////////////////////

bool MessageManipulator::isMsgValid(const char* MsgBuffer, var* Variable)
{
	if (Variable == NULL || MsgBuffer == NULL)
		return false;
	bool ThisValid=true, LeftValid=true, RightValid=true;
	
	if (Variable->left != NULL)
		LeftValid = isMsgValid(MsgBuffer, Variable->left);
	
	getValue(MsgBuffer, Variable, &ThisValid);
	
	if (Variable->right != NULL)
		RightValid = isMsgValid(MsgBuffer, Variable->right);
	
	return (ThisValid && LeftValid && RightValid);
}

bool MessageManipulator::isMsgValid(const SDMData& DatMsg, enum msg_type type)
{
	bool Result;
	if (type == DATAMSG)
		Result = isMsgValid(DatMsg.msg, Msg.data->list);
	else
		Result = isMsgValid(DatMsg.msg, Msg.fault->list);
	return Result;
}

value_t MessageManipulator::getValue(char* name, SDMData& dat, enum msg_type type,bool* IsValid)
{
	var* temp;

	if(type == DATAMSG)
		temp = find(name,Msg.data->list);
	else
		temp = find(name,Msg.fault->list);
	return getValue(dat.msg, temp, IsValid);
}

unsigned char MessageManipulator::getUINT08Value(char* name,SDMData& dat, enum msg_type type, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,dat,type,IsValid);
	temp = cast(temp,_UINT08);
	return temp.value.uint08;
}

signed char MessageManipulator::getINT08Value(char* name,SDMData& dat, enum msg_type type, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,dat,type,IsValid);
	temp = cast(temp,_INT08);
	return temp.value.int08;
}

unsigned short MessageManipulator::getUINT16Value(char* name,SDMData& dat, enum msg_type type, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,dat,type,IsValid);
	temp = cast(temp,_UINT16);
	return temp.value.uint16;
}

short MessageManipulator::getINT16Value(char* name,SDMData& dat, enum msg_type type, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,dat,type,IsValid);
	temp = cast(temp,_INT16);
	return temp.value.int16;
}

unsigned long MessageManipulator::getUINT32Value(char* name,SDMData& dat, enum msg_type type, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,dat,type,IsValid);
	temp = cast(temp,_UINT32);
	return temp.value.uint32;
}

long MessageManipulator::getINT32Value(char* name,SDMData& dat, enum msg_type type, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,dat,type,IsValid);
	temp = cast(temp,_INT32);
	return temp.value.int32;
}

float MessageManipulator::getFLOAT32Value(char* name,SDMData& dat, enum msg_type type, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,dat,type,IsValid);
	temp = cast(temp,_FLOAT32);
	return temp.value.float32;
}

double MessageManipulator::getFLOAT64Value(char* name,SDMData& dat, enum msg_type type, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,dat,type,IsValid);
	temp = cast(temp,_FLOAT64);
	return temp.value.float64;
}

//////////////////////     Gets for SDMCommand      //////////////////////

bool MessageManipulator::isMsgValid(const SDMCommand& CmdMsg)
{
	return isMsgValid (CmdMsg.data, Msg.command->list);
}

value_t MessageManipulator::getValue(char* name, SDMCommand& com, bool* IsValid)
{
	var* temp;

	temp = find(name,Msg.command->list);
	return getValue(com.data, temp, IsValid);
}

unsigned char MessageManipulator::getUINT08Value(char* name,SDMCommand& com, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,com,IsValid);
	temp = cast(temp,_UINT08);
	return temp.value.uint08;
}

signed char MessageManipulator::getINT08Value(char* name,SDMCommand& com, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,com,IsValid);
	temp = cast(temp,_INT08);
	return temp.value.int08;
}

unsigned short MessageManipulator::getUINT16Value(char* name,SDMCommand& com, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,com,IsValid);
	temp = cast(temp,_UINT16);
	return temp.value.uint16;
}

short MessageManipulator::getINT16Value(char* name,SDMCommand& com, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,com,IsValid);
	temp = cast(temp,_INT16);
	return temp.value.int16;
}

unsigned long MessageManipulator::getUINT32Value(char* name,SDMCommand& com, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,com,IsValid);
	temp = cast(temp,_UINT32);
	return temp.value.uint32;
}

long MessageManipulator::getINT32Value(char* name,SDMCommand& com, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,com,IsValid);
	temp = cast(temp,_INT32);
	return temp.value.int32;
}

float MessageManipulator::getFLOAT32Value(char* name,SDMCommand& com, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,com,IsValid);
	temp = cast(temp,_FLOAT32);
	return temp.value.float32;
}

double MessageManipulator::getFLOAT64Value(char* name,SDMCommand& com, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,com,IsValid);
	temp = cast(temp,_FLOAT64);
	return temp.value.float64;
}

//////////////////////     Gets for SDMSerreqst      //////////////////////

bool MessageManipulator::isMsgValid(const SDMSerreqst& ReqMsg)
{
	return isMsgValid(ReqMsg.data, Msg.command->list);
}

value_t MessageManipulator::getValue(char* name, SDMSerreqst& req, bool* IsValid)
{
	var* temp;
	temp = find(name,Msg.command->list);
	return getValue(req.data, temp, IsValid);
}

unsigned char MessageManipulator::getUINT08Value(char* name,SDMSerreqst& req, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,req,IsValid);
	temp = cast(temp,_UINT08);
	return temp.value.uint08;
}

signed char MessageManipulator::getINT08Value(char* name,SDMSerreqst& req, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,req,IsValid);
	temp = cast(temp,_INT08);
	return temp.value.int08;
}

unsigned short MessageManipulator::getUINT16Value(char* name,SDMSerreqst& req, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,req,IsValid);
	temp = cast(temp,_UINT16);
	return temp.value.uint16;
}

short MessageManipulator::getINT16Value(char* name,SDMSerreqst& req, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,req,IsValid);
	temp = cast(temp,_INT16);
	return temp.value.int16;
}

unsigned long MessageManipulator::getUINT32Value(char* name,SDMSerreqst& req, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,req,IsValid);
	temp = cast(temp,_UINT32);
	return temp.value.uint32;
}

long MessageManipulator::getINT32Value(char* name,SDMSerreqst& req, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,req,IsValid);
	temp = cast(temp,_INT32);
	return temp.value.int32;
}

float MessageManipulator::getFLOAT32Value(char* name,SDMSerreqst& req, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,req,IsValid);
	temp = cast(temp,_FLOAT32);
	return temp.value.float32;
}

double MessageManipulator::getFLOAT64Value(char* name,SDMSerreqst& req, bool* IsValid)
{
	value_t temp;
	temp = getValue(name,req,IsValid);
	temp = cast(temp,_FLOAT64);
	return temp.value.float64;
}

bool MessageManipulator::setValue(char* name,SDMService& request,value_t val)
{
	var* temp;
	temp = find(name,Msg.command->list);
	return setValue(request.data, temp, val);
}

//////////////////////////////////////////////////////////////////////////////////////////////
//
//             SET FUNCTIONS
//
//////////////////////////////////////////////////////////////////////////////////////////////

bool MessageManipulator::setArray(char* name,SDMData& dat,enum msg_type type, const void* buffer,int length)
{
	var* temp;
	
	if (type == DATAMSG)
	{
		if (Msg.data == NULL) return false;
		temp = find (name,Msg.data->list);
	}
	else if (type == FAULTMSG)
	{
		if (Msg.fault == NULL) return false;
		temp = find (name,Msg.fault->list);
	}
	else	//COMMANDMSG is an error
		return false;
	
	if (temp != NULL)
	{
		int MinLength = length < temp->length ? length : temp->length;
		if (MinLength <= temp->length)
			memcpy(dat.msg + temp->start, buffer, MinLength);
		return true;
	}
	
	return false;
}

bool MessageManipulator::setArray(char* name,SDMService& ser, const void* buffer,int length)
{
	var* temp;
	
	if (Msg.command == NULL) return false;
	temp = find (name,Msg.command->list);
	
	if (temp != NULL)
	{
		int MinLength = length < temp->length ? length : temp->length;
		if (MinLength <= temp->length)
			memcpy(ser.data + temp->start, buffer, MinLength);
		return true;
	}
	return false;
}

bool MessageManipulator::setArray(char* name,SDMCommand& cmd, const void* buffer,int length)
{
	return setArray(name,static_cast<SDMService&>(cmd),buffer,length);
}

//////////////////////     Sets for SDMService      //////////////////////

bool MessageManipulator::setValue(char* name,SDMService& request,unsigned char val)
{
	if(Msg.type != REQUEST)
		return false;
	value_t temp;
	temp.value.uint08 = val;
	temp.type = _UINT08;
	return setValue(name,request,temp);
}

bool MessageManipulator::setValue(char* name,SDMService& request,char val)
{
	if(Msg.type != REQUEST)
		return false;
	value_t temp;
	temp.value.int08 = val;
	temp.type = _INT08;
	return setValue(name,request,temp);
}

bool MessageManipulator::setValue(char* name,SDMService& request,unsigned short val)
{
	if(Msg.type != REQUEST)
		return false;
	value_t temp;
	temp.value.uint16 = val;
	temp.type = _UINT16;
	return setValue(name,request,temp);
}

bool MessageManipulator::setValue(char* name,SDMService& request,short val)
{
	if(Msg.type != REQUEST)
		return false;
	value_t temp;
	temp.value.int16 = val;
	temp.type = _INT16;
	return setValue(name,request,temp);
}

bool MessageManipulator::setValue(char* name,SDMService& request,unsigned long val)
{
	if(Msg.type != REQUEST)
		return false;
	value_t temp;
	temp.value.uint32 = val;
	temp.type = _UINT32;
	return setValue(name,request,temp);
}

bool MessageManipulator::setValue(char* name,SDMService& request,long val)
{
	if(Msg.type != REQUEST)
		return false;
	value_t temp;
	temp.value.int32 = val;
	temp.type = _INT32;
	return setValue(name,request,temp);
}

bool MessageManipulator::setValue(char* name,SDMService& request,float val)
{
	if(Msg.type != REQUEST)
		return false;
	value_t temp;
	temp.value.float32 = val;
	temp.type = _FLOAT32;
	return setValue(name,request,temp);
}

bool MessageManipulator::setValue(char* name,SDMService& request,double val)
{
	if(Msg.type != REQUEST)
		return false;
	value_t temp;
	temp.value.float64 = val;
	temp.type = _FLOAT64;
	return setValue(name,request,temp);
}

bool MessageManipulator::setValue(char* Buffer, var* Variable, value_t Value)
{
	if (Buffer == NULL || Variable == NULL) return false;
	// cast if needed
	int start = Variable->start;
	Value = cast(Value, Variable->type);
	switch(Variable->type)
	{
		case _UINT08:
			PUT_UCHAR(&(Buffer[start]),Value.value.uint08);
			break;
		case _INT08:
			PUT_CHAR(&(Buffer[start]),Value.value.int08);
			break;
		case _UINT16:
			PUT_USHORT(&(Buffer[start]),Value.value.uint16);
			break;
		case _INT16:
			PUT_SHORT(&(Buffer[start]),Value.value.int16);
			break;
		case _UINT32:
			PUT_ULONG(&(Buffer[start]),Value.value.uint32);
			break;
		case _INT32:
			PUT_LONG(&(Buffer[start]),Value.value.int32);
			break;
		case _FLOAT32:
			PUT_FLOAT(&(Buffer[start]),Value.value.float32);
			break;
		case _FLOAT64:
			PUT_DOUBLE(&(Buffer[start]),Value.value.float64);
			break;
		case _EMPTY:
			break;
	}
	return true;
}

bool MessageManipulator::setValue(char* name,SDMCommand& command,value_t val)
{
	var* temp;
	temp = find(name,Msg.command->list);
	return setValue(command.data, temp, val);
}

//////////////////////     Sets for SDMCommand      //////////////////////

bool MessageManipulator::setValue(char* name,SDMCommand& command,unsigned char val)
{
	if(Msg.type == NOTIFICATION)
		return false;
	value_t temp;
	temp.value.uint08 = val;
	temp.type = _UINT08;
	return setValue(name,command,temp);
}

bool MessageManipulator::setValue(char* name,SDMCommand& command,char val)
{
	if(Msg.type == NOTIFICATION)
		return false;
	value_t temp;
	temp.value.int08 = val;
	temp.type = _INT08;
	return setValue(name,command,temp);
}

bool MessageManipulator::setValue(char* name,SDMCommand& command,unsigned short val)
{
	if(Msg.type == NOTIFICATION)
		return false;
	value_t temp;
	temp.value.uint16 = val;
	temp.type = _UINT16;
	return setValue(name,command,temp);
}

bool MessageManipulator::setValue(char* name,SDMCommand& command,short val)
{
	if(Msg.type == NOTIFICATION)
		return false;
	value_t temp;
	temp.value.int16 = val;
	temp.type = _INT16;
	return setValue(name,command,temp);
}

bool MessageManipulator::setValue(char* name,SDMCommand& command,unsigned long val)
{
	if(Msg.type == NOTIFICATION)
		return false;
	value_t temp;
	temp.value.uint32 = val;
	temp.type = _UINT32;
	return setValue(name,command,temp);
}

bool MessageManipulator::setValue(char* name,SDMCommand& command,long val)
{
	if(Msg.type == NOTIFICATION)
		return false;
	value_t temp;
	temp.value.int32 = val;
	temp.type = _INT32;
	return setValue(name,command,temp);
}

bool MessageManipulator::setValue(char* name,SDMCommand& command,float val)
{
	if(Msg.type == NOTIFICATION)
		return false;
	value_t temp;
	temp.value.float32 = val;
	temp.type = _FLOAT32;
	return setValue(name,command,temp);
}

bool MessageManipulator::setValue(char* name,SDMCommand& command,double val)
{
	if(Msg.type == NOTIFICATION)
		return false;
	value_t temp;
	temp.value.float64 = val;
	temp.type = _FLOAT64;
	return setValue(name,command,temp);
}

bool MessageManipulator::setValue(char* name,SDMData& data,value_t val,enum msg_type type)
{
	var* temp;

	if(type == DATAMSG)
	{
		//Be sure a data message is defined
		if (Msg.data == NULL)
			return false;
		else
			temp = find(name,Msg.data->list);
	}
	else if (type == FAULTMSG)
	{
		//Be sure a fault message is defined
		if (Msg.fault == NULL)
			return false;
		else
			temp = find(name,Msg.fault->list);
	}
	else	//COMMANDMSG results in an error
		return false;
	
	return setValue(data.msg, temp, val);
}

//////////////////////     Sets for SDMData      //////////////////////

bool MessageManipulator::setValue(char* name,SDMData& data,unsigned char val,enum msg_type type)
{
	value_t temp;
	temp.value.uint08 = val;
	temp.type = _UINT08;
	return setValue(name,data,temp,type);
}

bool MessageManipulator::setValue(char* name,SDMData& data,char val,enum msg_type type)
{
	value_t temp;
	temp.value.int08 = val;
	temp.type = _INT08;
	return setValue(name,data,temp,type);
}

bool MessageManipulator::setValue(char* name,SDMData& data,unsigned short val,enum msg_type type)
{
	value_t temp;
	temp.value.uint16 = val;
	temp.type = _UINT16;
	return setValue(name,data,temp,type);
}

bool MessageManipulator::setValue(char* name,SDMData& data,short val,enum msg_type type)
{
	value_t temp;
	temp.value.int16 = val;
	temp.type = _INT16;
	return setValue(name,data,temp,type);
}

bool MessageManipulator::setValue(char* name,SDMData& data,unsigned long val,enum msg_type type)
{
	value_t temp;
	temp.value.uint32 = val;
	temp.type = _UINT32;
	return setValue(name,data,temp,type);
}

bool MessageManipulator::setValue(char* name,SDMData& data,long val,enum msg_type type)
{
	value_t temp;
	temp.value.int32 = val;
	temp.type = _INT32;
	return setValue(name,data,temp,type);
}

bool MessageManipulator::setValue(char* name,SDMData& data,float val,enum msg_type type)
{
	value_t temp;
	temp.value.float32 = val;
	temp.type = _FLOAT32;
	return setValue(name,data,temp,type);
}

bool MessageManipulator::setValue(char* name,SDMData& data,double val,enum msg_type type)
{
	value_t temp;
	temp.value.float64 = val;
	temp.type = _FLOAT64;
	return setValue(name,data,temp,type);
}

SDMMessage_ID MessageManipulator::getMsgID(enum msg_type type)
{
	SDMMessage_ID Result('\0','\0');
	switch(type)
	{
		case COMMANDMSG:
			if(Msg.command != NULL)
				Result = Msg.command->id;
			return Result;
			break;
		case DATAMSG:
			if(Msg.data != NULL)
				Result = Msg.data->id;
			return Result;
			break;
		case FAULTMSG:
			if(Msg.fault != NULL)
				Result = Msg.fault->id;
			return Result;
			break;
	}
	return Result;
}

void MessageManipulator::applyGetScaleFactor(bool apply)
{
	scaled = apply;
}
