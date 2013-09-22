#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "message.h"


 msg* Message;

int clear( var** p);
void PrintVar( var* varlist);

void setLength( nodeData* node, int l)
{
	node->length = l;
}

 var* find(char* name, var* root)
{
	if (root==NULL || name==NULL) return NULL;
	if (strcmp(name,root->name)==0)
		return root;
	if (strcmp(name,root->name)<0)
		return find(name,root->left);
	return find(name,root->right);
}

var* addVar(var** root, var* new_var)
{
	if (new_var==NULL) return *root;
	if(*root==NULL)
	{
		*root=new_var;
		return *root;
	}
	if(strcmp(new_var->name,(*root)->name)<0)
	{
		addVar(&((*root)->left),new_var);
		return *root;
	}
	else
	{
		addVar(&((*root)->right),new_var);
		return *root;
	}
}
/*
	Overload to handle a variable's invalid value of type int.
*/
var* newVarInvalidIsInt(char* p_Name, int p_Start, int p_Length, char* p_Type, float p_ScaleFactor, int p_InvalidValue)
{
	var* NewVar = newVar(p_Name, p_Start, p_Length, p_Type, p_ScaleFactor);
	if (NewVar == NULL)
		return NULL;
	
	NewVar->invalid_data.type = NewVar->type;
	switch(NewVar->type)
	{
		case _UINT08:
			NewVar->invalid_data.value.uint08 = (unsigned char)p_InvalidValue;
			break;
		case _INT08:
			NewVar->invalid_data.value.int08 = (char)p_InvalidValue;
			break;
		case _UINT16:
			NewVar->invalid_data.value.uint16 = (unsigned short)p_InvalidValue;
			break;
		case _INT16:
			NewVar->invalid_data.value.int16 = (short)p_InvalidValue;
			break;
		case _UINT32:
			NewVar->invalid_data.value.uint32 = (unsigned int)p_InvalidValue;
			break;
		case _INT32:
			NewVar->invalid_data.value.int32 = p_InvalidValue;
			break;
		case _FLOAT32:
			NewVar->invalid_data.value.float32 = (float)p_InvalidValue;
			break;
		case _FLOAT64:
			NewVar->invalid_data.value.float64 = (double)p_InvalidValue;
			break;
		case _EMPTY:
			break;
	}
	return NewVar;
}
/*
	Overload to handle a variable's invalid value of type float.
*/
var* newVarInvalidIsFloat(char* p_Name, int p_Start, int p_Length, char* p_Type, float p_ScaleFactor, float p_InvalidValue)
{
	var* NewVar = newVar(p_Name, p_Start, p_Length, p_Type, p_ScaleFactor);
	if (NewVar == NULL)
		return NULL;
	
	NewVar->invalid_data.type = NewVar->type;
	switch(NewVar->type)
	{
		case _FLOAT32:
			NewVar->invalid_data.value.float32 = p_InvalidValue;
			break;
		case _FLOAT64:
			NewVar->invalid_data.value.float64 = (double)p_InvalidValue;
			break;
		default:
			printf("MessageManipulator::Warning - Variable %s received floating point invalid value of %f but is of type %s.\n", p_Name, p_InvalidValue, p_Type);
			break;
	}
	return NewVar;
}
/*
	Allocates a new variable and sets its name, starting location, length, type, and scale factor.
*/
 var* newVar(char* p_Name,int p_Start,int p_Length,char* p_Type,float p_ScaleFactor)
{
	 var* temp;
	temp = ( var*)malloc(sizeof( var));
	memset(temp, 0, sizeof(var));
	temp->name = p_Name;
	temp->start = p_Start;
	temp->length = p_Length;

	/* Set the type */
	if (strcmp(p_Type,"UINT08")==0)
		temp->type = _UINT08;
	else if (strcmp(p_Type,"INT08")==0)
		temp->type = _INT08;
	else if (strcmp(p_Type,"UINT16")==0)
		temp->type = _UINT16;
	else if (strcmp(p_Type,"INT16")==0)
		temp->type = _INT16;
	else if (strcmp(p_Type,"UINT32")==0)
		temp->type = _UINT32;
	else if (strcmp(p_Type,"INT32")==0)
		temp->type = _INT32;
	else if (strcmp(p_Type,"FLOAT32")==0)
		temp->type = _FLOAT32;
	else if (strcmp(p_Type,"FLOAT64")==0)
		temp->type = _FLOAT64;
	
	free(p_Type);
	temp->invalid_data.type = _EMPTY;
	temp->scale_factor = p_ScaleFactor;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

nodeData* newNode(char* name,enum msg_type type,int length,int id, var* list)
{
	nodeData* temp;
	temp = (nodeData*)malloc(sizeof(nodeData));
	memset(temp, 0, sizeof(nodeData));
	setName(temp, name);
	temp->type = type;
	setLength(temp,length);
	temp->id = id;
	temp->list = list;
	return temp;
} 

void setName( nodeData* node, char* n)
{
	node->name = n;
}

void setMessage( nodeData* command,  nodeData* data,  nodeData* fault)
{
	deleteMessage(Message);
	/* Assign the new message nodes */
	Message->command = command;
	Message->data = data;
	Message->fault = fault;
	/* Assign the message type */
	if(Message->data == NULL)
		Message->type = COMMAND;
	else if(Message->command == NULL)
		Message->type = NOTIFICATION;
	else
		Message->type = REQUEST;
}

void printMsg()
{
	switch(Message->type)
	{
		case COMMAND:
			printf("Message type: COMMAND\n");
			break;
		case NOTIFICATION:
			printf("Message type: NOTIFICATION\n");
			break;
		case REQUEST:
			printf("Message type: COMMAND\n");
			break;
		case EMPTY:
			printf("Message type: Message Def has not been parsed yet!\n");
			return;
	}
	if(Message->command != NULL)
		printf("CommandMsg name: %s id: %x length %d\n",Message->command->name,Message->command->id,Message->command->length);
	if(Message->data != NULL)
		printf("DataMsg name: %s id: %x length %d\n",Message->data->name,Message->data->id,Message->data->length);
	if(Message->command != NULL)
		printf("FaultMsg name: %s id: %x length %d\n",Message->fault->name,Message->fault->id,Message->fault->length);
}

void PrintVar( var* varlist)
{
	if(varlist == NULL)
		return;
	printf("Variable name: %s type: %d start: %d length: %d\n",varlist->name,varlist->type,varlist->start,varlist->length);
	PrintVar(varlist->left);
	PrintVar(varlist->right);
}

 msg* parse(char* msg_def, msg* msg_ptr)
{
	extern void *MessageManipulator_scan_string(const char* str);
	extern int MessageManipulatorparse();
	extern void MessageManipulator_delete_buffer(void*);
	void* buffer = NULL;
	int parseResult;

	Message = msg_ptr;
	/* Parse the new message defs */
	buffer = MessageManipulator_scan_string(msg_def);
	parseResult = MessageManipulatorparse();
	MessageManipulator_delete_buffer(buffer);
	if (parseResult==0)
	{
		return Message;
	}
	return NULL;
 }

void deleteMessage(msg* Msg)
{
	if (Msg == NULL) return;
	/* Delete the command message list */
	if(Msg->command != NULL)
	{
		if (Msg->command->name != NULL)
			free (Msg->command->name);
		deleteVarTree(&(Msg->command->list));
		free (Msg->command);
		Msg->command = NULL;
	}
	/* Delete the data message list */ 
	if(Msg->data != NULL)
	{
		if (Msg->data->name != NULL)
			free (Msg->data->name);
		deleteVarTree(&(Msg->data->list));
		free (Msg->data);
		Msg->data = NULL;
	}
	/*Delete the fault message list*/
	if(Msg->fault != NULL)
	{
		if (Msg->fault->name != NULL)
			free (Msg->fault->name);
		deleteVarTree(&(Msg->fault->list));
		free (Msg->fault);
		Msg->fault = NULL;
	}
}

int deleteVarTree( var** p)
{
	if((*p)==NULL) return 0;
	
	/*Free the heap allocated members*/
	if ((*p)->name != NULL)
		free ((*p)->name);
	
	/*Recursively delete the other tree variable members*/
	if((*p)->left!=*p)
		deleteVarTree(&((*p)->left));
	if((*p)->right!=*p)
		deleteVarTree(&((*p)->right));
	free(*p);
	*p=NULL;
	return 1;
}
