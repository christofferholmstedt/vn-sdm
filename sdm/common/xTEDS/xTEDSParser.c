#include "xTEDSParser.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

xteds* result;
variable* var_result;
/*
	README:

   This source file contains functions to build an xTEDS tree as the parser encounters the text.
   The functions are, in general, separated into new_*, link_*, merge_*, delete_*, and add_*
   names.

   The new_* functions are used to allocate a structure type and initialize all pointer members to
   NULL.  Also other member types should be initialized to some start value.  Note that all new_*
   functions dynamically allocate the structure, and should be deleted using the corresponding
   delete_* function.

   The link_* functions are used to link items of a list.  Many of the structure types have members
   called "next" which refers to a link list.  The link functions are used to link the instances.

   The merge_* functions are used to add attributes and arbitrarily ordered elements to the structure.
   Notice that on many of the members of a structure, within these functions, there is a "else if"
   clause that prevents a memory leak that occurs if some attribute is specified in the xTEDS multiple
   times.  This cannot be caught by the parser, and the funtions will simply throw away the most recent
   addition.

   The delete_* functions free the dynamically allocated memory allocated by the new_* functions.  If
   the structure member is a linked list, the delete function should recursively delete the list.

   The add_* functions are used to simply add a pointer to a list member of a structure.

*/
qualifier_type* link_qualifiers(qualifier_type* a,qualifier_type* b)
{
	qualifier_type* cur;

	if(a==NULL) return b;
	if(b==NULL) return a;

	for(cur=a;cur->next!=NULL;cur=cur->next);
	cur->next = b;
	return a;
}

qualifier_type* merge_qualifiers(qualifier_type* a,qualifier_type* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;
	
	if(a->name==NULL) a->name = b->name;
	  else if(b->name!=NULL) free(b->name);
	
	if(a->value==NULL) a->value = b->value;
	  else if(b->value!=NULL) free(b->value);
	
	if(a->units==NULL) a->units = b->units;
	  else if(b->units!=NULL) free(b->units);
	
	free(b);
	return a;
}

qualifier_type* new_qualifier()
{
	qualifier_type* temp;

	temp = (qualifier_type*)malloc(sizeof(qualifier_type));
	temp->name= NULL;
	temp->value= NULL;
	temp->units= NULL;
	temp->next= NULL;

	return temp;
}

coef* new_coef()
{
	coef* temp;

	temp = (coef*)malloc(sizeof(coef));
	temp->exponent= NULL;
	temp->value= NULL;
	temp->description= NULL;
	temp->next= NULL;

	return temp;
}

coef* link_coefs(coef* a,coef* b)
{
	coef* cur;

	if(a==NULL) return b;
	if(b==NULL) return a;

	for(cur=a;cur->next!=NULL;cur=cur->next);
	cur->next = b;
	return a;
}

coef* merge_coefs(coef* a,coef* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;
	
	if(a->exponent==NULL) a->exponent = b->exponent;
	  else if(b->exponent!=NULL) free(b->exponent);
	
	if(a->value==NULL) a->value = b->value;
	  else if(b->value!=NULL) free(b->value);
	
	if(a->description==NULL) a->description = b->description;
	  else if(b->description!=NULL) free(b->description);
	
	free(b);
	return a;
}

curve* new_curve()
{
	curve* temp;

	temp = (curve*)malloc(sizeof(curve));
	temp->name= NULL;
	temp->description= NULL;
	temp->coefs= NULL;
	return temp;
}

curve* merge_curves(curve* a,curve* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;
	
	if(a->name==NULL) a->name = b->name;
	  else if(b->name!=NULL) free(b->name);
	
	if(a->description==NULL) a->description = b->description;
	  else if(b->description!=NULL) free(b->description);
	
	if(a->coefs==NULL) a->coefs = b->coefs;
	  else if(b->coefs!=NULL) delete_coef(b->coefs);
	
	free(b);
	return a;
}

curve* curve_add_coefs(curve* curve_type, coef* coefs)
{
	if(curve_type==NULL) return curve_type;
	curve_type->coefs = coefs;
	return curve_type;
}

curveoption* new_option()
{
	curveoption* temp;

	temp = (curveoption*)malloc(sizeof(curveoption));
	temp->name= NULL;
	temp->value= NULL;
	temp->description= NULL;
	temp->alarm= NULL;
	temp->next= NULL;

	return temp;
}

curveoption* link_options(curveoption* a,curveoption* b)
{
	curveoption* cur;

	if(a==NULL) return b;
	if(b==NULL) return a;

	for(cur=a;cur->next!=NULL;cur=cur->next);
	cur->next = b;
	return a;
}

curveoption* merge_options(curveoption* a,curveoption* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;
	
	if(a->name==NULL) a->name = b->name;
	  else if(b->name!=NULL) free(b->name);
	
	if(a->value==NULL) a->value = b->value;
	  else if(b->value!=NULL) free(b->value);
	
	if(a->description==NULL) a->description = b->description;
	  else if(b->description!=NULL) free(b->description);
	
	if(a->alarm==NULL) a->alarm = b->alarm;
	  else if(b->alarm!=NULL) free(b->alarm);
	
	free(b);
	return a;
}

drange* new_drange()
{
	drange* temp;

	temp = (drange*)malloc(sizeof(drange));
	temp->name= NULL;
	temp->description= NULL;
	temp->options= NULL;
	return temp;
}

drange* merge_dranges(drange* a,drange* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;
	
	if(a->name==NULL) a->name = b->name;
	  else if(b->name!=NULL) free(b->name);
	
	if(a->description==NULL) a->description = b->description;
	  else if(b->description!=NULL) free(b->description);
	
	if(a->options==NULL) a->options = b->options;
	  else if(b->options!=NULL) delete_option(b->options);
	
	free(b);
	return a;
}

drange* drange_add_options(drange* drange_type, curveoption* options)
{
	if(drange_type==NULL) return drange_type;
	drange_type->options = options;
	return drange_type;
}

location* new_location()
{
	location* temp;
	
	temp = (location*)malloc(sizeof(location));
	temp->x_value = NULL;
	temp->y_value = NULL;
	temp->z_value = NULL;
	temp->units = NULL;
	return temp;
}

location* merge_locations(location* a,location* b)
{
	if (a == NULL) return b;
	if (b == NULL) return a;
	
	if (a->x_value == NULL) a->x_value = b->x_value;
	 else if (b->x_value != NULL) free(b->x_value);
	 
	if (a->y_value == NULL) a->y_value = b->y_value;
	 else if (b->y_value != NULL) free(b->y_value);
	 
	if (a->z_value == NULL) a->z_value = b->z_value;
	 else if (b->z_value != NULL) free(b->z_value);
	 
	if (a->units == NULL) a->units = b->units;
	 else if (b->units != NULL) free(b->units);

	free(b);
	return a;
}

orientation* link_orientations(orientation* a, orientation* b)
{
	orientation* cur;
	
	if (a == NULL) return b;
	if (b == NULL) return a;
	
	for(cur=a; cur->next!=NULL; cur=cur->next);
	cur->next = b;
	return a;
}

orientation* merge_orientations(orientation* a, orientation* b)
{
	if (a == NULL) return b;
	if (b == NULL) return a;
	
	if (a->axis_value == NULL) a->axis_value = b->axis_value;
	 else if(b->axis_value != NULL) free(b->axis_value);
	
	if (a->angle_value == NULL) a->angle_value = b->angle_value;
	 else if(b->angle_value != NULL) free(b->angle_value);
	
	if (a->units_value == NULL) a->units_value = b->units_value;
	 else if (b->units_value != NULL) free(b->units_value);
	
	free (b);
	return a;
}

orientation* new_orientation()
{
	orientation* temp;
	
	temp = (orientation*)malloc(sizeof(orientation));
	temp->axis_value = NULL;
	temp->angle_value = NULL;
	temp->units_value = NULL;
	temp->next = NULL;
	return temp;
}

variable* link_variables(variable* a,variable* b)
{
	variable* cur;

	if(a==NULL) return b;
	if(b==NULL) return a;

	for(cur=a;cur->next!=NULL;cur=cur->next);
	cur->next = b;
	return a;
}

variable* merge_variables(variable* a,variable* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;
	/* The else if blocks are required to prevent a possible memory leak occuring when a attribute
	 in the xTEDS is specified multiple times, this isn't really enforceable in the xTEDS schema
	 unless an exhaustive list of all permutations of attribute orders was specified in the grammar*/
	if(a->length==NULL) a->length = b->length;
	  else if(b->length!=NULL) free(b->length);
	
	if(a->kind==NULL) a->kind = b->kind;
	  else if(b->kind!=NULL) free(b->kind);
	
	if(a->name==NULL) a->name = b->name;
	  else if(b->name!=NULL) free(b->name);
	
	if(a->qualifier==NULL) a->qualifier = b->qualifier;
	  else if(b->qualifier!=NULL) free(b->qualifier);
	
	if(a->id==NULL) a->id = b->id;
	  else if(b->id!=NULL) free(b->id);
	
	if(a->range_min==NULL) a->range_min = b->range_min;
	  else if(b->range_min!=NULL) free(b->range_min);
	
	if(a->range_max==NULL) a->range_max = b->range_max;
	  else if(b->range_max!=NULL) free(b->range_max);
	
	if(a->default_value==NULL) a->default_value = b->default_value;
	  else if(b->default_value!=NULL) free(b->default_value);
	
	if(a->precision==NULL) a->precision = b->precision;
	  else if(b->precision!=NULL) free(b->precision);
	
	if(a->units==NULL) a->units = b->units;
	  else if(b->units!=NULL) free(b->units);
	
	if(a->accuracy==NULL) a->accuracy = b->accuracy;
	  else if(b->accuracy!=NULL) free(b->accuracy);
	
	if(a->scale_factor==NULL) a->scale_factor = b->scale_factor;
	  else if(b->scale_factor!=NULL) free(b->scale_factor);
	
	if(a->scale_units==NULL) a->scale_units = b->scale_units;
	  else if(b->scale_units!=NULL) free(b->scale_units);
	
	if(a->format==NULL) a->format = b->format;
	  else if(b->format!=NULL) free(b->format);
	
	if(a->description==NULL) a->description = b->description;
	  else if(b->description!=NULL) free(b->description);
	
	if(a->qualifiers==NULL) a->qualifiers = b->qualifiers;
	  else if(b->qualifiers!=NULL) free(b->qualifiers);
	
	if(a->curves==NULL) a->curves = b->curves;
	  else if(b->curves!=NULL) delete_curve(b->curves);
	
	if(a->dranges==NULL) a->dranges = b->dranges;
	  else if(b->dranges!=NULL) delete_drange(b->dranges);
	
	if(a->location_data==NULL) a->location_data = b->location_data;
	  else if(b->location_data!=NULL) delete_location(b->location_data);
	
	if (a->r_low == NULL) a->r_low = b->r_low;
	  else if(b->r_low!=NULL) free(b->r_low);
	
	if (a->r_high == NULL) a->r_high = b->r_high;
	  else if(b->r_high!=NULL) free(b->r_high);
	
	if (a->y_low == NULL) a->y_low = b->y_low;
	  else if(b->y_low!=NULL) free(b->y_low);
	
	if (a->y_high == NULL) a->y_high = b->y_high;
	  else if(b->y_high!=NULL) free(b->y_high);
	
	if (a->invalid_value == NULL) a->invalid_value = b->invalid_value;
	  else if(b->invalid_value!=NULL) free(b->invalid_value);
	
	a->orientation_data = link_orientations(a->orientation_data,b->orientation_data);
	free(b);
	/*Keep a reference to this variable tree for VarInfoParser*/
	var_result = a;
	return a;
}

variable* new_variable()
{
	variable* temp;

	temp = (variable*)malloc(sizeof(variable));
	temp->length = NULL;
	temp->kind= NULL;
	temp->name= NULL;
	temp->qualifier= NULL;
	temp->id= NULL;
	temp->range_min= NULL;
	temp->range_max= NULL;
	temp->default_value= NULL;
	temp->precision= NULL;
	temp->units= NULL;
	temp->accuracy= NULL;
	temp->scale_factor= NULL;
	temp->scale_units= NULL;
	temp->format= NULL;
	temp->description= NULL;
	temp->qualifiers= NULL;
	temp->curves= NULL;
	temp->dranges= NULL;
	temp->next= NULL;
	temp->interface_name= NULL;
	temp->interface_id= NULL;
	temp->location_data = NULL;
	temp->orientation_data = NULL;
	temp->r_low = NULL;
	temp->r_high = NULL;
	temp->y_low = NULL;
	temp->y_high = NULL;
	temp->invalid_value = NULL;
	return temp;
}

var_ref* link_variable_ref(var_ref* a,var_ref* b)
{
	var_ref* cur;

	if(a==NULL) return b;
	if(b==NULL) return a;

	for(cur=a;cur->next!=NULL;cur=cur->next);
	cur->next = b;
	return a;
}

var_ref* new_variable_ref(char* name)
{
	var_ref* temp;

	temp = (var_ref*)malloc(sizeof(var_ref));
	temp->name = name;
	temp->next = NULL;
	return temp;
}

fault_msg* merge_fault_msg(fault_msg* a,fault_msg* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;
	
	if(a->name==NULL) a->name = b->name;
	  else if(b->name!=NULL) free(b->name);
	
	if(a->id==NULL) a->id = b->id;
	  else if(b->id!=NULL) free(b->id);
	
	if(a->description==NULL) a->description = b->description;
	  else if(b->description!=NULL) free(b->description);
	
	if(a->variables==NULL) a->variables = b->variables;
	if(a->qualifiers==NULL) a->qualifiers = b->qualifiers;
	free(b);
	return a;
}

fault_msg* new_fault_msg()
{
	fault_msg* temp;
	temp = (fault_msg*)malloc(sizeof(fault_msg));
	temp->name= NULL;
	temp->id= NULL;
	temp->description= NULL;
	temp->variables= NULL;
	temp->qualifiers= NULL;
	temp->interface_name= NULL;
	temp->interface_id= NULL;
	return temp;
}

fault_msg* fault_add_var_refs(fault_msg* msg,var_ref* ref)
{
	if(msg==NULL) return msg;
	msg->variables = ref;
	return msg;
}

data_msg* link_data_msg(data_msg* a,data_msg* b)
{
	data_msg* cur;

	if(a==NULL) return b;
	if(b==NULL) return a;

	for(cur=a;cur->next!=NULL;cur=cur->next);
	cur->next = b;
	return a;
}

data_msg* merge_data_msg(data_msg* a,data_msg* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;

	if(a->name==NULL) a->name = b->name;
	  else if(b->name!=NULL) free(b->name);
	
	if(a->id==NULL) a->id = b->id;
	  else if(b->id!=NULL) free(b->id);
	
	if(a->description==NULL) a->description = b->description;
	  else if(b->description!=NULL) free(b->description);
	
	if(a->msg_arrival==NULL) a->msg_arrival = b->msg_arrival;
	  else if(b->msg_arrival!=NULL) free(b->msg_arrival);
	
	if(a->msg_rate==NULL) a->msg_rate = b->msg_rate;
	  else if(b->msg_rate!=NULL) free(b->msg_rate);
	
	if(a->qualifiers==NULL) a->qualifiers = b->qualifiers;
	if(a->variables==NULL) a->variables = b->variables;	
	free(b);
	return a;
}

data_msg* new_data_msg()
{
	data_msg* temp;
	temp = (data_msg*)malloc(sizeof(data_msg));
	temp->name= NULL;
	temp->id= NULL;
	temp->description= NULL;
	temp->msg_arrival=NULL;
	temp->msg_rate=NULL;
	temp->variables=NULL;
	temp->qualifiers=NULL;
	temp->next= NULL;
	temp->interface_name= NULL;
	temp->interface_id= NULL;
	return temp;
}

data_msg* data_add_var_refs(data_msg* msg,var_ref* ref)
{
	if(msg==NULL) return msg;
	msg->variables = ref;
	return msg;
}

cmd_msg* link_cmd_msg(cmd_msg* a,cmd_msg* b)
{
	cmd_msg* cur;

	if(a==NULL) return b;
	if(b==NULL) return a;

	for(cur=a;cur->next!=NULL;cur=cur->next);
	cur->next = b;
	return a;
}

cmd_msg* merge_cmd_msg(cmd_msg* a,cmd_msg* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;

	if(a->name==NULL) a->name = b->name;
	  else if(b->name!=NULL) free(b->name);
	
	if(a->id==NULL) a->id = b->id;
	  else if(b->id!=NULL) free(b->id);
	
	if(a->description==NULL) a->description = b->description;
	  else if(b->description!=NULL) free(b->description);
	
	if(a->qualifiers==NULL) a->qualifiers = b->qualifiers;
	if(a->variables==NULL) a->variables = b->variables;
	free(b);
	return a;
}

cmd_msg* new_cmd_msg()
{
	cmd_msg* temp;
	temp = (cmd_msg*)malloc(sizeof(cmd_msg));
	temp->name= NULL;
	temp->id= NULL;
	temp->description= NULL;
	temp->variables=NULL;
	temp->qualifiers=NULL;
	temp->next= NULL;
	temp->interface_name= NULL;
	temp->interface_id= NULL;
	return temp;
}

cmd_msg* cmd_add_var_refs(cmd_msg* msg,var_ref* ref)
{
	if(msg==NULL) return msg;
	msg->variables = ref;
	return msg;
}

command* new_command()
{
	command* temp;
	temp = (command*)malloc(sizeof(command));
	temp->command_message= NULL;
	temp->fault_message= NULL;
	temp->next= NULL;
	temp->interface_name= NULL;
	temp->interface_id= NULL;
	return temp;
}

command* command_add_cmd_msg(command* a ,cmd_msg* b)
{
	if(a==NULL) return a;
	a->command_message = b;
	return a;
}

command* command_add_fault_msg(command* a,fault_msg* b)
{
	if(a==NULL) return a;
	a->fault_message = b;
	return a;
}

command* link_command(command* a, command* b)
{
	command* cur;

	if(a==NULL) return b;
	if(b==NULL) return a;

	for(cur=a;cur->next!=NULL;cur=cur->next);
	cur->next = b;
	return a;
}

notification* new_notification()
{
	notification* temp;
	temp = (notification*)malloc(sizeof(notification));
	temp->data_message= NULL;
	temp->fault_message= NULL;
	temp->next= NULL;
	temp->interface_name= NULL;
	temp->interface_id= NULL;
	return temp;
}

notification* notification_add_data_msg(notification* a,data_msg* b)
{
	if(a==NULL) return a;
	a->data_message = b;
	return a;
}

notification* notification_add_fault_msg(notification* a,fault_msg* b)
{
	if(a==NULL) return a;
	a->fault_message = b;
	return a;
}

notification* link_notification(notification* a, notification* b)
{
	notification* cur;

	if(a==NULL) return b;
	if(b==NULL) return a;

	for(cur=a;cur->next!=NULL;cur=cur->next);
	cur->next = b;
	return a;
}

request* new_request()
{
	request* temp;
	temp = (request*)malloc(sizeof(request));
	temp->command_message= NULL;
	temp->data_message= NULL;
	temp->fault_message= NULL;
	temp->next= NULL;
	temp->interface_name= NULL;
	temp->interface_id= NULL;
	return temp;
}

request* request_add_cmd_msg(request* a,cmd_msg* b)
{
	if(a==NULL) return a;
	a->command_message = b;
	return a;
}

request* request_add_data_msg(request* a,data_msg* b)
{
	if(a==NULL) return a;
	a->data_message = b;
	return a;
}

request* request_add_fault_msg(request* a,fault_msg* b)
{
	if(a==NULL) return a;
	a->fault_message = b;
	return a;
}

request* link_request(request* a, request* b)
{
	request* cur;

	if(a==NULL) return b;
	if(b==NULL) return a;

	for(cur=a;cur->next!=NULL;cur=cur->next);
	cur->next = b;
	return a;
}

message* new_message()
{
	message* temp;
	temp = (message*)malloc(sizeof(message));
	temp->commands= NULL;
	temp->notifications= NULL;
	temp->requests= NULL;
	return temp;
}

message* message_link_command(message* msg,command* cmd)
{
	if(msg==NULL) return msg;
	msg->commands = link_command(msg->commands,cmd);
	return msg;
}

message* message_link_notification(message* msg,notification* not)
{
	if(msg==NULL) return msg;
	msg->notifications = link_notification(msg->notifications,not);
	return msg;
}

message* message_link_request(message* msg,request* req)
{
	if(msg==NULL) return msg;
	msg->requests = link_request(msg->requests,req);
	return msg;
}

message* merge_message(message* a,message* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;
	if(a->commands==NULL)	a->commands = b->commands;
	else	a->commands = link_command(a->commands,b->commands);
	if(a->notifications==NULL)	a->notifications = b->notifications;
	else	a->notifications = link_notification(a->notifications,b->notifications);
	if(a->requests==NULL)	a->requests = b->requests;
	else	a->requests = link_request(a->requests,b->requests);
	free(b);
	return a;
}

interface* new_interface()
{
	interface* temp;
	temp = (interface*)malloc(sizeof(interface));
	temp->name= NULL;
	temp->extends= NULL;
	temp->id= NULL;
	temp->description= NULL;
	temp->qualifiers= NULL;
	temp->variables= NULL;
	temp->commands= NULL;
	temp->notifications= NULL;
	temp->requests= NULL;
	temp->next= NULL;

	return temp;
}

interface* link_interface(interface* a,interface* b)
{
	interface* cur;

	if(a==NULL) return b;
	if(b==NULL) return a;

	for(cur=a;cur->next!=NULL;cur=cur->next);
	cur->next = b;
	return a;
}

interface* merge_interface(interface* a,interface* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;

	if(a->name==NULL) a->name = b->name;
	  else if(b->name!=NULL) free(b->name);
	
	if(a->extends==NULL) a->extends = b->extends;
	  else if(b->extends!=NULL) free(b->extends);
	
	if(a->id==NULL) a->id = b->id;
	  else if(b->id!=NULL) free(b->id);
	
	if(a->description==NULL) a->description = b->description;
	  else if(b->description!=NULL) free(b->description);
	
	/* Note:  the below fields are not added using merge_interface, so it is not possible for
	 both "a" and "b" to contain definitions of the below, so the else clause isn't needed*/
	if(a->qualifiers==NULL) a->qualifiers = b->qualifiers;
	if(a->variables==NULL) a->variables = b->variables;
	if(a->commands==NULL) a->commands = b->commands;
	if(a->notifications==NULL) a->notifications = b->notifications;
	if(a->requests==NULL) a->requests = b->requests;
	free(b);
	return a;
}

interface* interface_add_references(interface* a,qualifier_type* q,variable* v,message* m)
{
	variable* cur_var = NULL;
	command* cur_cmd = NULL;
	notification* cur_not = NULL;
	request* cur_request = NULL;
	if(a==NULL) return a;
	a->qualifiers = q;
	a->variables = v;
	if(a->id==NULL)
	{
		printf("Error: Interface is missing the id field!!\n");
		a->id = strdup("0");
	}
	for(cur_var=a->variables;cur_var!=NULL;cur_var=cur_var->next)
	{
		if(a->name != NULL)
			cur_var->interface_name = strdup(a->name);
		if(a->id != NULL)
			cur_var->interface_id = strdup(a->id);
	}
	if(m != NULL)
	{
		a->commands = m->commands;
		for(cur_cmd=a->commands;cur_cmd!=NULL;cur_cmd=cur_cmd->next)
		{
			if(a->name != NULL)
				cur_cmd->interface_name = strdup(a->name);
			if(a->id != NULL)
				cur_cmd->interface_id = strdup(a->id);
			if(cur_cmd->command_message != NULL)
			{
				if(a->name != NULL)
					cur_cmd->command_message->interface_name = strdup(a->name);
				if(a->id != NULL)
					cur_cmd->command_message->interface_id = strdup(a->id);
			}
			else
				printf("Error:  <Command> wrapper is missing a command message definition.\n");
			if(cur_cmd->fault_message!=NULL)
			{
				cur_cmd->fault_message->interface_name = strdup(a->name);
				cur_cmd->fault_message->interface_id = strdup(a->id);
			}
		}
		a->notifications = m->notifications;
		for(cur_not=a->notifications;cur_not!=NULL;cur_not=cur_not->next)
		{
			if(a->name != NULL)
				cur_not->interface_name = strdup(a->name);
			if(a->id != NULL)
				cur_not->interface_id = strdup(a->id);
			if(cur_not->data_message != NULL)
			{
				if(a->name != NULL)
					cur_not->data_message->interface_name = strdup(a->name);
				if(a->id != NULL)
					cur_not->data_message->interface_id = strdup(a->id);
			}
			else
				printf("Error:  <Notification> wrapper is missing a data message definition.\n");
			if(cur_not->fault_message!=NULL)
			{
				cur_not->fault_message->interface_name = strdup(a->name);
				cur_not->fault_message->interface_id = strdup(a->id);
			}
		}
		a->requests = m->requests;
		for(cur_request=a->requests;cur_request!=NULL;cur_request=cur_request->next)
		{
			if(a->name != NULL)
				cur_request->interface_name = strdup(a->name);
			if(a->id != NULL)
				cur_request->interface_id = strdup(a->id);
			if(cur_request->command_message != NULL)
			{
				if(a->name != NULL)
					cur_request->command_message->interface_name = strdup(a->name);
				if(a->id != NULL)
					cur_request->command_message->interface_id = strdup(a->id);
			}
			else
				printf("Error:  <Request> wrapper is missing a command message definition.\n");
			if(cur_request->data_message != NULL)
			{
				if(a->name != NULL)
					cur_request->data_message->interface_name = strdup(a->name);
				if(a->id != NULL)
					cur_request->data_message->interface_id = strdup(a->id);
			}
			else
				printf("Error:  <Request> wrapper is missing a data message definition.\n");
			if(cur_request->fault_message!=NULL)
			{
				cur_request->fault_message->interface_name = strdup(a->name);
				cur_request->fault_message->interface_id = strdup(a->id);
			}
		}
		free(m);
	}
	return a;
}

xteds* merge_xteds(xteds* a,xteds* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;

	if(a->name==NULL) a->name = b->name;
	if(a->version==NULL) a->version = b->version;
	if(a->description==NULL) a->description = b->description;
	if(a->xmlns==NULL) a->xmlns = b->xmlns;
	if(a->xmlns_xsi==NULL) a->xmlns_xsi = b->xmlns_xsi;
	if(a->schema_location==NULL) a->schema_location = b->schema_location;
	free(b);
	return a;
}

xteds* new_xteds()
{
	xteds* temp;
	temp = (xteds*)malloc(sizeof(xteds));
	temp->name= NULL;
	temp->version= NULL;
	temp->description= NULL;
	temp->xmlns = NULL;
	temp->xmlns_xsi = NULL;
	temp->schema_location = NULL;
	temp->interfaces= NULL;
	return temp;
}

app_dev_attr* merge_app_dev_attr(app_dev_attr* a,app_dev_attr* b)
{
	if(a==NULL) return b;
	if(b==NULL) return a;

	if(a->name==NULL) a->name = b->name;
	if(a->kind==NULL) a->kind = b->kind;
	if(a->id==NULL) a->id = b->id;
	if(a->qualifier==NULL) a->qualifier = b->qualifier;
	if(a->description==NULL) a->description = b->description;
	if(a->manufacturer_id==NULL) a->manufacturer_id = b->manufacturer_id;
	if(a->componentKey==NULL) a->componentKey = b->componentKey;
	if(a->model_id==NULL) a->model_id = b->model_id;
	if(a->version_letter==NULL) a->version_letter = b->version_letter;
	if(a->version==NULL) a->version = b->version;
	if(a->serial_number==NULL) a->serial_number = b->serial_number;
	if(a->calibration_date==NULL) a->calibration_date = b->calibration_date;
	if(a->sensitivity_at_reference==NULL) a->sensitivity_at_reference = b->sensitivity_at_reference;
	if(a->reference_frequency==NULL) a->reference_frequency = b->reference_frequency;
	if(a->reference_temperature==NULL) a->reference_temperature = b->reference_temperature;
	if(a->measurement_range==NULL) a->measurement_range = b->measurement_range;
	if(a->electrical_output==NULL) a->electrical_output = b->electrical_output;
	if(a-> quality_factor==NULL) a->quality_factor = b->quality_factor;
	if(a->temperature_coefficient==NULL) a->temperature_coefficient = b->temperature_coefficient;
	if(a->direction_xyz==NULL) a->direction_xyz = b->direction_xyz;
	if(a->cal_due_date==NULL) a->cal_due_date = b->cal_due_date;
	if(a->power_requirements==NULL) a->power_requirements = b->power_requirements;
	if(a->spa_u_hub==NULL) a->spa_u_hub = b->spa_u_hub;
	if(a->spa_u_port==NULL) a->spa_u_port = b->spa_u_port;
	a->qualifiers = link_qualifiers(a->qualifiers,b->qualifiers);
	if(a->memory_minimum==NULL) a->memory_minimum = b->memory_minimum;
	if(a->operating_system==NULL) a->operating_system = b->operating_system;
	if(a->path_for_assembly==NULL) a->path_for_assembly = b->path_for_assembly;
	if(a->path_on_spacecraft==NULL) a->path_on_spacecraft = b->path_on_spacecraft;
	free(b);
	return a;
}

app_dev_attr* new_app_dev_attr()
{
	app_dev_attr* temp;
	temp = (app_dev_attr*)malloc(sizeof(app_dev_attr));
	temp->name= NULL;
	temp->kind= NULL;
	temp->id= NULL;
	temp->qualifier= NULL;
	temp->description= NULL;
	temp->manufacturer_id= NULL;
	temp->componentKey= NULL;
	temp->model_id= NULL;
	temp->version_letter= NULL;
	temp->version= NULL;
	temp->serial_number= NULL;
	temp->calibration_date= NULL;
	temp->sensitivity_at_reference= NULL;
	temp->reference_frequency= NULL;
	temp->reference_temperature= NULL;
	temp->measurement_range= NULL;
	temp->electrical_output= NULL;
	temp->quality_factor= NULL;
	temp->temperature_coefficient= NULL;
	temp->direction_xyz= NULL;
	temp->cal_due_date= NULL;
	temp->power_requirements= NULL;
	temp->spa_u_hub= NULL;
	temp->spa_u_port= NULL;
	temp->qualifiers= NULL;
	temp->memory_minimum= NULL;
	temp->operating_system= NULL;
	temp->path_for_assembly= NULL;
	temp->path_on_spacecraft= NULL;
	return temp;
}

xteds* add_references(xteds* xTEDS,app_dev_attr* attr,interface* face)
{
	xTEDS->header = attr;
	xTEDS->interfaces = face;
	return xTEDS;
}

int delete_qualifier(qualifier_type* p)
{
	if(p==NULL) return 0;
	delete_qualifier(p->next);
	free(p->name);
	free(p->value);
	free(p->units);
	free(p);
	return 1;
}

int delete_coef(coef* p)
{
	if(p==NULL) return 0;
	delete_coef(p->next);
	free(p->exponent);
	free(p->value);
	free(p->description);
	free(p);
	return 1;
}

int delete_curve(curve* p)
{
	if(p==NULL) return 0;
	delete_coef(p->coefs);
	free(p->name);
	free(p->description);
	free(p);
	return 1;
}

int delete_option(curveoption* p)
{
	if(p==NULL) return 0;
	delete_option(p->next);
	free(p->name);
	free(p->value);
	free(p->description);
	free(p->alarm);
	free(p);
	return 1;
}

int delete_drange(drange* p)
{
	if(p==NULL) return 0;
	delete_option(p->options);
	free(p->name);
	free(p->description);
	free(p);
	return 1;
}

int delete_location(location* p)
{
	if (p==NULL) return 0;
	free(p->x_value);
	free(p->y_value);
	free(p->z_value);
	free(p->units);
	free(p);
	return 1;
}

int delete_orientation(orientation* p)
{
	if (p==NULL) return 0;
	delete_orientation(p->next);
	free(p->axis_value);
	free(p->angle_value);
	free(p->units_value);
	free(p);
	return 1;
}

int delete_variable(variable* p)
{
	if(p==NULL) return 0;
	delete_variable(p->next);
	delete_qualifier(p->qualifiers);
	delete_curve(p->curves);
	delete_drange(p->dranges);
	delete_location(p->location_data);
	delete_orientation(p->orientation_data);
	free(p->length);
	free(p->kind);
	free(p->name);
	free(p->qualifier);
	free(p->id);
	free(p->range_min);
	free(p->range_max);
	free(p->default_value);
	free(p->precision);
	free(p->units);
	free(p->accuracy);
	free(p->scale_factor);
	free(p->scale_units);
	free(p->format);
	free(p->description);
	free(p->interface_name);
	free(p->interface_id);
	free(p->r_low);
	free(p->r_high);
	free(p->y_low);
	free(p->y_high);
	free(p->invalid_value);
	free(p);
	return 1;
}

int delete_var_ref(var_ref* p)
{
	if(p==NULL) return 0;
	delete_var_ref(p->next);
	free(p->name);
	free(p);
	return 1;
}

int delete_fault_msg(fault_msg* p)
{
	if(p==NULL) return 0;
	delete_var_ref(p->variables);
	delete_qualifier(p->qualifiers);
	free(p->name);
	free(p->id);
	free(p->description);
	free(p->interface_name);
	free(p->interface_id);
	free(p);
	return 1;
}

int delete_data_msg(data_msg* p)
{
	if(p==NULL) return 0;
	delete_data_msg(p->next);
	delete_var_ref(p->variables);
	delete_qualifier(p->qualifiers);
	free(p->name);
	free(p->id);
	free(p->msg_arrival);
	free(p->description);
	free(p->msg_rate);
	free(p->interface_name);
	free(p->interface_id);
	free(p);
	return 1;
}

int delete_cmd_msg(cmd_msg* p)
{
	if(p==NULL) return 0;
	delete_cmd_msg(p->next);
	delete_var_ref(p->variables);
	delete_qualifier(p->qualifiers);
	free(p->name);
	free(p->id);
	free(p->description);
	free(p->interface_name);
	free(p->interface_id);
	free(p);
	return 1;
}

int delete_command(command* p)
{
	if(p==NULL) return 0;
	delete_command(p->next);
	delete_cmd_msg(p->command_message);
	delete_fault_msg(p->fault_message);
	free(p->interface_name);
	free(p->interface_id);
	free(p);
	return 1;
}

int delete_notification(notification* p)
{
	if(p==NULL) return 0;
	delete_notification(p->next);
	delete_data_msg(p->data_message);
	delete_fault_msg(p->fault_message);
	free(p->interface_name);
	free(p->interface_id);
	free(p);
	return 1;
}

int delete_request(request* p)
{
	if(p==NULL) return 0;
	delete_request(p->next);
	delete_cmd_msg(p->command_message);
	delete_data_msg(p->data_message);
	delete_fault_msg(p->fault_message);
	free(p->interface_name);
	free(p->interface_id);
	free(p);
	return 1;
}

int delete_message(message* p)
{
	if(p==NULL) return 0;
	delete_command(p->commands);
	delete_notification(p->notifications);
	delete_request(p->requests);
	free(p);
	return 1;
}

int delete_interface(interface* p)
{
	if(p==NULL) return 0;
	delete_interface(p->next);
	delete_qualifier(p->qualifiers);
	delete_variable(p->variables);
	delete_command(p->commands);
	delete_notification(p->notifications);
	delete_request(p->requests);
	free(p->name);
	free(p->extends);
	free(p->id);
	free(p->description);
	free(p);
	return 1;
}

extern SDMLIB_API int delete_xteds(xteds* p)
{
	if(p==NULL) return 0;
	delete_app_dev_attr(p->header);
	delete_interface(p->interfaces);
	free(p->name);
	free(p->version);
	free(p->description);
	free(p->xmlns);
	free(p->xmlns_xsi);
	free(p->schema_location);
	free(p);
	return 1;
}

int delete_app_dev_attr(app_dev_attr* p)
{
	if(p==NULL) return 0;
	delete_qualifier(p->qualifiers);
	free(p->name);
	free(p->kind);
	free(p->id);
	free(p->qualifier);
	free(p->description);
	free(p->manufacturer_id);
	free(p->componentKey);
	free(p->model_id);
	free(p->version_letter);
	free(p->version);
	free(p->serial_number);
	free(p->calibration_date);
	free(p->sensitivity_at_reference);
	free(p->reference_frequency);
	free(p->reference_temperature);
	free(p->measurement_range);
	free(p->electrical_output);
	free(p->quality_factor);
	free(p->temperature_coefficient);
	free(p->direction_xyz);
	free(p->cal_due_date);
	free(p->power_requirements);
	free(p->spa_u_hub);
	free(p->spa_u_port);
	free(p->memory_minimum);
	free(p->operating_system);
	free(p->path_for_assembly);
	free(p->path_on_spacecraft);
	free(p);
	return 1;
}

SDMLIB_API variable* getParsedVariable()
{
	return var_result;
}

extern SDMLIB_API xteds* parsexTEDS(char* text)
{
	extern void *xTEDS_scan_string(const char* str);
	extern int xTEDSparse();
	extern void xTEDS_delete_buffer(void*);
	extern int line_count;

	int parse_result;
	void* buffer;
	line_count = 1;

	buffer = xTEDS_scan_string(text);
	parse_result=xTEDSparse();
	xTEDS_delete_buffer(buffer);
	if(parse_result==0)
	{
		return result;
	}
	return NULL;
}

