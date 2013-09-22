#ifndef __MESSAGE_H_
#define __MESSAGE_H_

enum value_type
{
	_EMPTY,_UINT08,_INT08,_UINT16,_INT16,_UINT32,_INT32,_FLOAT32,_FLOAT64
};

union _value
{
	unsigned char uint08;
	char int08;
	unsigned short uint16;
	short int16;
	unsigned long uint32;
	signed long int32;
	float float32;
	double float64;
};

typedef struct value_s
{
	enum value_type type;
	union _value value;
}value_t;

typedef struct variable
{
	char* name;
	int start;
	int length;
	enum value_type type;
	float scale_factor;
	value_t invalid_data;
	struct variable* left;
	struct variable* right;
}var;

enum msg_type
{
	COMMANDMSG, DATAMSG, FAULTMSG
};

typedef struct node_data
{
	char* name;
	enum msg_type type;
	int length,countmax,id;
	float ratemax;
	var* list;
}nodeData;

enum wrapper_type
{
	EMPTY, COMMAND, NOTIFICATION, REQUEST
};

typedef struct msg_data
{
	enum wrapper_type type;
	nodeData* command;
	nodeData* data;
	nodeData* fault;
}msg;

void setLength(nodeData*,int);
var* addVar(var** root,var* new_var);
var* newVar(char* p_Name,int p_Start,int p_Length,char* p_Type,float p_ScaleFactor);
var* newVarInvalidIsInt(char* p_Name, int p_Start, int p_Length, char* p_Type, float p_ScaleFactor, int p_InvalidValue);
var* newVarInvalidIsFloat(char* p_Name, int p_Start, int p_Length, char* p_Type, float p_ScaleFactor, float p_InvalidValue);
nodeData* newNode(char*,enum msg_type,int,int,var*);
void setName(nodeData*,char*);
void setMessage(nodeData*, nodeData*, nodeData*);
int deleteVarTree( var** p);
void deleteMessage(msg*);

void printMsg();
var* find(char* name,var* root);
msg* parse(char* msg_def,msg*);

#endif
