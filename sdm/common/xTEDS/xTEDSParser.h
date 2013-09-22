#ifndef __XTEDS_PARSER_H
#define __XTEDS_PARSER_H
/*contains support routines for the xTEDS parser*/

#include "../sdmLib.h"

typedef struct qualifier_data
{
	char* name;
	char* value;
	char* units;
	struct qualifier_data* next;
}qualifier_type;

typedef struct coefficient_data
{
	char* exponent;
	char* value;
	char* description;
	struct coefficient_data* next;
}coef;

typedef struct curve_data
{
	char* name;
	char* description;
	coef* coefs;
}curve;

typedef struct option_data
{
	char* name;
	char* value;
	char* description;
	char* alarm;
	struct option_data* next;
}curveoption;

typedef struct drange_data
{
	char* name;
	char* description;
	curveoption* options;
}drange;

typedef struct location_data
{
	char *x_value;
	char *y_value;
	char *z_value;
	char *units;
}location;

typedef struct orientation_data
{
	char *axis_value;
	char *angle_value;
	char *units_value;
	struct orientation_data* next;
}orientation;

typedef struct variable_data
{
	char* length;
	char* kind;
	char* name;
	char* qualifier;
	char* id;
	char* range_min;
	char* range_max;
	char* default_value;
	char* precision;
	char* units;
	char* accuracy;
	char* scale_factor;
	char* scale_units;
	char* format;
	char* description;
	char* interface_name;
	char* interface_id;
	char* r_low;
	char* r_high;
	char* y_low;
	char* y_high;
	char* invalid_value;
	qualifier_type* qualifiers;
	curve* curves;
	drange* dranges;
	struct variable_data* next;
	location* location_data;
	orientation* orientation_data;
} variable;

typedef struct variable_reference
{
	char* name;
	struct variable_reference* next;
} var_ref;

typedef struct fault_message
{
	char* name;
	char* id;
	char* description;
	char* interface_name;
	char* interface_id;
	var_ref* variables;
	qualifier_type* qualifiers;
}fault_msg;

typedef struct data_message
{
	char* name;
	char* id;
	char* msg_arrival;
	char* description;
	char* msg_rate;
	char* interface_name;
	char* interface_id;
	var_ref* variables;
	qualifier_type* qualifiers;
	struct data_message* next;
} data_msg;

typedef struct command_message
{
	char* name;
	char* id;
	char* description;
	char* interface_name;
	char* interface_id;
	var_ref* variables;
	qualifier_type* qualifiers;
	struct command_message* next;
} cmd_msg;

typedef struct command_type
{
	cmd_msg* command_message;
	fault_msg* fault_message;
	char* interface_name;
	char* interface_id;
	struct command_type* next;
}command;

typedef struct notification_type
{
	data_msg* data_message;
	fault_msg* fault_message;
	char* interface_name;
	char* interface_id;
	struct notification_type* next;
}notification;

typedef struct request_type
{
	cmd_msg* command_message;
	data_msg* data_message;
	fault_msg* fault_message;
	char* interface_name;
	char* interface_id;
	struct request_type* next;
}request;

typedef struct message_type
{
	command* commands;
	notification* notifications;
	request* requests;
}message;

typedef struct interface_type
{
	char* name;
	char* extends;
	char* id;
	char* description;
	qualifier_type* qualifiers;
	variable* variables;
	command* commands;
	notification* notifications;
	request* requests;
	struct interface_type* next;
}interface;

typedef struct app_device_attributes
{
	char* name;
	char* kind;
	char* id;
	char* qualifier;
	char* description;
	char* manufacturer_id;
	char* componentKey;
	char* model_id;
	char* version_letter;
	char* version;
	char* serial_number;
	char* calibration_date;
	char* sensitivity_at_reference;
	char* reference_frequency;
	char* reference_temperature;
	char* measurement_range;
	char* electrical_output;
	char* quality_factor;
	char* temperature_coefficient;
	char* direction_xyz;
	char* cal_due_date;
	char* power_requirements;
	char* spa_u_hub;
	char* spa_u_port;
	char* memory_minimum;
	char* operating_system;
	char* path_for_assembly;
	char* path_on_spacecraft;
	qualifier_type* qualifiers;
} app_dev_attr;

typedef struct xteds
{
	char* name;
	char* version;
	char* description;
	char* xmlns;
	char* xmlns_xsi;
	char* schema_location;
	app_dev_attr* header;
	interface* interfaces;
} xteds;

extern xteds* result;

qualifier_type* link_qualifiers(qualifier_type*,qualifier_type*);
qualifier_type* merge_qualifiers(qualifier_type*,qualifier_type*);
qualifier_type* new_qualifier();

coef* link_coefs(coef*,coef*);
coef* merge_coefs(coef*,coef*);
coef* new_coef();

curve* merge_curves(curve*,curve*);
curve* new_curve();

curveoption* link_options(curveoption*,curveoption*);
curveoption* merge_options(curveoption*,curveoption*);
curveoption* new_option();

drange* merge_dranges(drange*,drange*);
drange* new_drange();

location* merge_locations(location*,location*);
location* new_location();

orientation* link_orientations(orientation*, orientation*);
orientation* merge_orientations(orientation*, orientation*);
orientation* new_orientation();

variable* link_variables(variable*,variable*);
variable* merge_variables(variable*,variable*);
variable* new_variable();

var_ref* link_variable_ref(var_ref*,var_ref*);
var_ref* new_variable_ref(char* name);

fault_msg* merge_fault_msg(fault_msg*,fault_msg*);
fault_msg* new_fault_msg();
fault_msg* fault_add_var_refs(fault_msg*,var_ref*);

data_msg* link_data_msg(data_msg*,data_msg*);
data_msg* merge_data_msg(data_msg*,data_msg*);
data_msg* new_data_msg();
data_msg* data_add_var_refs(data_msg*,var_ref*);

cmd_msg* link_cmd_msg(cmd_msg*,cmd_msg*);
cmd_msg* merge_cmd_msg(cmd_msg*,cmd_msg*);
cmd_msg* new_cmd_msg();
cmd_msg* cmd_add_var_refs(cmd_msg*,var_ref*);

command* new_command();
command* command_add_cmd_msg(command*,cmd_msg*);
command* command_add_fault_msg(command*,fault_msg*);
command* link_command(command*,command*);

notification* new_notification();
notification* notification_add_data_msg(notification*,data_msg*);
notification* notification_add_fault_msg(notification*,fault_msg*);
notification* link_notification(notification*,notification*);

request* new_request();
request* request_add_cmd_msg(request*,cmd_msg*);
request* request_add_data_msg(request*,data_msg*);
request* request_add_fault_msg(request*,fault_msg*);
request* link_request(request*,request*);

message* new_message();
message* message_link_command(message*,command*);
message* message_link_notification(message*,notification*);
message* message_link_request(message*,request*);
message* merge_message(message*,message*);

interface* new_interface();
interface* link_interface(interface*,interface*);
interface* merge_interface(interface*,interface*);
interface* interface_add_references(interface*,qualifier_type*,variable*,message*);

xteds* merge_xteds(xteds*,xteds*);
xteds* new_xteds();
xteds* add_references(xteds*,app_dev_attr*,interface*);

app_dev_attr* merge_app_dev_attr(app_dev_attr*,app_dev_attr*);
app_dev_attr* new_app_dev_attr();

int delete_qualifier(qualifier_type*);
int delete_coef(coef*);
int delete_curve(curve*);
int delete_option(curveoption*);
int delete_drange(drange*);
int delete_location(location*);
int delete_orientation(orientation*);
int delete_variable(variable*);
int delete_var_ref(var_ref*);
int delete_fault_msg(fault_msg*);
int delete_data_msg(data_msg*);
int delete_cmd_msg(cmd_msg*);
int delete_command(command*);
int delete_notification(notification*);
int delete_request(request*);
int delete_message(message*);
int delete_interface(interface*);
extern SDMLIB_API int delete_xteds(xteds*);
int delete_app_dev_attr(app_dev_attr*);

SDMLIB_API variable* getParsedVariable();
extern SDMLIB_API xteds* parsexTEDS(char*);
#endif
