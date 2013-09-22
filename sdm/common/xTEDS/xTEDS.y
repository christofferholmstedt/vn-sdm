%{
/*xTEDS 1.0 msg_def parser*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xTEDSParser.h"

int yylex();

int yydebug=0;
void yyerror(char *s);
%}

/*%pure-parser*/
/*punctuation*/

%token EQUAL_SY CLOSE_SY SLASHCLOSE_SY OPEN_XML_SY CLOSE_xTEDS_SY OPEN_xTEDS_SY OPEN_APP_SY
%token OPEN_VAR_SY CLOSE_VAR_SY OPEN_DRANGE_SY CLOSE_DRANGE_SY OPEN_OPTION_SY OPEN_CURVE_SY
%token CLOSE_CURVE_SY OPEN_COEFF_SY OPEN_DATA_MSG_SY CLOSE_DATA_MSG_SY OPEN_VARIABLE_REF_SY
%token OPEN_COMMAND_MSG_SY CLOSE_COMMAND_MSG_SY NAME_SY KIND_SY ID_SY CLOSE_ORIENTATION_SY
%token QUALIFIER_SY DESCRIPTION_SY MANUFACTURER_ID_SY VERSION_SY MODEL_ID_SY VERSION_LETTER_SY
%token SERIAL_NUMBER_SY CALIBRATION_DATE_SY SENSITIVITY_AT_REF_SY REF_FREQ_SY REF_TEMP_SY
%token MEASUREMENT_RANGE_SY ELECTRICAL_OUTPUT_SY QUALITY_FACTOR_SY TEMP_COEFF_SY DIRECTION_XYZ_SY
%token CAL_DUE_DATE_SY POWER_REQS_SY VALUE_SY ALARM_SY MSG_ARRIVAL_SY MSG_RATE_SY 
%token STRING FLOAT INT PRECISION_SY RANGE_MAX_SY CLOSE_LOCATION_SY CLOSE_ORIENTATION_SY
%token FORMAT_SY ACCURACY_SY RANGE_MIN_SY SCALE_FACTOR_SY UNITS_SY DEFAULT_VALUE_SY
%token OPEN_DEVICE_SY SCALE_UNITS_SY LENGTH_SY EXPONENT_SY SCHEMA_LOCATION_SY XMLNS_SY XMLNS_XSI_SY
%token CLOSE_OPTION_SY OPEN_INTERFACE_SY OPEN_COMMAND_SY OPEN_NOTIFICATION_SY OPEN_REQUEST_SY
%token OPEN_FAULT_MSG_SY COMPONENT_KEY_SY SPA_U_HUB_SY SPA_U_PORT_SY EXTENDS_SY
%token CLOSE_COMMAND_SY CLOSE_NOTIFICATION_SY CLOSE_REQUEST_SY CLOSE_FAULT_MSG_SY OPEN_QUALIFIER_SY
%token CLOSE_QUALIFIER_SY CLOSE_APP_SY CLOSE_DEVICE_SY CLOSE_INTERFACE_SY MEMORY_MINIMUM_SY
%token OPERATING_SYSTEM_SY PATH_FOR_ASSEMBLY_SY PATH_ON_SPACECRAFT_SY X_SY Y_SY Z_SY AXIS_SY ANGLE_SY
%token OPEN_LOCATION_SY OPEN_ORIENTATION_SY CLOSE_XML_SY ENCODING_SY STANDALONE_SY CLOSE_VARIABLE_REF_SY
%token CLOSE_COEFF_SY R_LOW_SY R_HIGH_SY Y_LOW_SY Y_HIGH_SY INVALID_VALUE_SY BAD_TERMINAL_SY

%union
{
	int integer;
	float real;
	char* str;
	struct variable_data* var;
	struct variable_reference* var_ref;
	struct qualifier_data* qual;
	struct coefficient_data* coef;
	struct curve_data* curve;
	struct option_data* curveoption;
	struct drange_data* drange;
	struct location_data* location;
	struct orientation_data* orientation;
	struct fault_message* fault_msg;
	struct data_message* data_msg;
	struct command_message* cmd_msg;
	struct command_type* command;
	struct notification_type* notification;
	struct request_type* request;
	struct message_type* message;
	struct interface_type* interface;
	struct xteds* xteds;
	struct app_device_attributes* attr;
}

%type<str> STRING
%type<integer> INT ENCODING
%type<real> FLOAT
%type<var> VAR_ATTRIBUTES VAR_ATTRIBUTE VAR_SECTION VARIABLE VAR_HEAD VAR_WITH_SUBELEMENTS VAR_NO_SUBELEMENTS VAR_SUBELEMENT VAR_SUBELEMENTS
%type<var> VAR_ELEMENTS VAR_QUALIFIERS
%type<var_ref> VARIABLE_REFS VARIABLE_REF
%type<qual> QUALIFIERS_SECTION QUALIFIER 
%type<qual> QUALIFIERS_ATTRIBUTE QUALIFIERS_ATTRIBUTES INTERFACE_SUBELEMENTS INTERFACE_SUBELEMENT
%type<coef> CURVE_COEFFS CURVE_COEFF COEFF_ATTRIBUTES COEFF_ATTRIBUTE
%type<curve> CURVE_HEAD CURVE_ATTRIBUTES CURVE_ATTRIBUTE CURVE
%type<curveoption> DRANGE_OPTIONS DRANGE_OPTION OPTION_ATTRIBUTES OPTION_ATTRIBUTE
%type<drange> DRANGE_HEAD DRANGE_ATTRIBUTES DRANGE_ATTRIBUTE DRANGE
%type<location> LOCATION_SECTION LOCATION_ATTRIBUTES LOCATION_ATTRIBUTE
%type<orientation> ORIENTATION_SECTION ORIENTATION_ATTRIBUTES ORIENTATION_ATTRIBUTE
%type<fault_msg> FAULT_MSG_SECTION FAULT_MSG FAULT_MSG_ATTRIBUTES FAULT_MSG_ATTRIBUTE FAULT_MSG_QUALIFIERS
%type<data_msg> DATA_MSG_SECTION DATA_MSG DATA_MSG_ATTRIBUTES DATA_MSG_ATTRIBUTE DATA_MSG_QUALIFIERS
%type<cmd_msg> COMMAND_MSG_SECTION COMMAND_MSG COMMAND_MSG_ATTRIBUTES COMMAND_MSG_ATTRIBUTE COMMAND_MSG_QUALIFIERS
%type<command>	COMMAND_SECTION
%type<notification> NOTIFICATION_SECTION
%type<request>	REQUEST_SECTION
%type<message> MESSAGE_SECTION MESSAGES
%type<interface> INTERFACE INTERFACES INTERFACE_HEAD INTERFACE_ATTRIBUTES INTERFACE_ATTRIBUTE
%type<xteds> xTEDS OPEN_xTEDS xTEDS_ATTRIBUTES xTEDS_ATTRIBUTE
%type<attr> APP_DEVICE APP_SECTION DEVICE_SECTION APP_ATTRIBUTES COMMON_APP_DEVICE_ATTRIBUTE
%type<attr> DEVICE_ATTRIBUTES DEVICE_ATTRIBUTE APP_ATTRIBUTE DEVICE_SUBELEMENTS DEVICE_SUBELEMENT

%start XTEDS_DOCUMENT

%%
XTEDS_DOCUMENT		:	OPEN_XML_SY VERSION_SY EQUAL_SY STRING ENCODING STANDALONE CLOSE_XML_SY xTEDS
			{
				int compare = 1;
				if(strcmp("1.0",$4)!=0)
					compare = 0;
				free($4);
				compare = $5;
				if(compare == 1)
					result = $8;
				else
					result = NULL;
			}
			;
			
ENCODING		:	ENCODING_SY EQUAL_SY STRING
			{
				int compare = 1;
				
				if(strcmp("utf-8",$3)!=0 && strcmp("UTF-8",$3)!=0)
					compare = 0;
				free($3);
				$$ = compare;
			}
			|	/*empty*/
			{
				$$ = 1;
			}
			;
			
STANDALONE		:	STANDALONE_SY EQUAL_SY STRING
			{
				free($3);
			}
			|	/*empty*/
			;
/////////////////////////////////////////////////////////////////////////////////
//
//                 Productions pertaining to xTEDS structure in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

xTEDS			:	OPEN_xTEDS APP_DEVICE INTERFACES CLOSE_xTEDS_SY CLOSE_SY
			{
				$$ = add_references($1,$2,$3);
			}
			;

OPEN_xTEDS		:	OPEN_xTEDS_SY xTEDS_ATTRIBUTES CLOSE_SY
			{
				$$=$2;
			}
			;

xTEDS_ATTRIBUTES	:	xTEDS_ATTRIBUTES xTEDS_ATTRIBUTE
			{
				$$ = merge_xteds($1,$2);
			}
			|	/*empty*/
			{
				xteds* temp;
				temp = new_xteds();
				$$=temp;
			}
			;

xTEDS_ATTRIBUTE		:	NAME_SY EQUAL_SY STRING
			{
				xteds* temp;
				temp = new_xteds();
				temp->name = $3;
				$$ = temp;
			}
			|	VERSION_SY EQUAL_SY STRING
			{
				xteds* temp;
				temp = new_xteds();
				temp->version = $3;
				$$ = temp;
			}
			|	DESCRIPTION_SY EQUAL_SY STRING
			{
				xteds* temp;
				temp = new_xteds();
				temp->description = $3;
				$$ = temp;
			}
			|	XMLNS_SY EQUAL_SY STRING
			{
				xteds* temp;
				temp = new_xteds();
				temp->xmlns = $3;
				$$ = temp;
			}
			|	SCHEMA_LOCATION_SY EQUAL_SY STRING
			{
				xteds* temp;
				temp = new_xteds();
				temp->schema_location = $3;
				$$ = temp;
			}
			|	XMLNS_XSI_SY EQUAL_SY STRING
			{
				xteds* temp;
				temp = new_xteds();
				temp->xmlns_xsi = $3;
				$$ = temp;
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//          Productions pertaining to application definition in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

APP_DEVICE		:	APP_SECTION
			{
				$$ = $1;
			}
			|	DEVICE_SECTION
			{
				$$ = $1;
			}
			;

APP_SECTION		:	OPEN_APP_SY APP_ATTRIBUTES SLASHCLOSE_SY
			{
				$$ = $2;
			}
			|	OPEN_APP_SY APP_ATTRIBUTES CLOSE_SY QUALIFIERS_SECTION CLOSE_APP_SY CLOSE_SY
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->qualifiers = $4;
				$$ = merge_app_dev_attr($2,temp);
			}
			;

APP_ATTRIBUTES		:	APP_ATTRIBUTES APP_ATTRIBUTE
			{
				$$ = merge_app_dev_attr($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

COMMON_APP_DEVICE_ATTRIBUTE: 	NAME_SY EQUAL_SY STRING			
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->name = $3;
				$$ = temp;
			}
			|	KIND_SY EQUAL_SY STRING			
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->kind = $3;
				$$ = temp;
			}
			|	ID_SY EQUAL_SY STRING			
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->id = $3;
				$$ = temp;
			}
			|	QUALIFIER_SY EQUAL_SY STRING			
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->qualifier = $3;
				printf("Qualifier field has been deprecated!\n");
				$$ = temp;
			}
			|	DESCRIPTION_SY EQUAL_SY STRING			
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->description = $3;
				$$ = temp;
			}
			|	MANUFACTURER_ID_SY EQUAL_SY STRING			
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->manufacturer_id = $3;
				$$ = temp;
			}
			|	COMPONENT_KEY_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->componentKey = $3;
				$$ = temp;
			}
			;

APP_ATTRIBUTE		:	COMMON_APP_DEVICE_ATTRIBUTE	
			{
				$$ = $1;
			}
			|	VERSION_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->version = $3;
				$$ = temp;
			}
			|	MEMORY_MINIMUM_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->memory_minimum = $3;
				$$ = temp;
			}
			|	OPERATING_SYSTEM_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->operating_system = $3;
				$$ = temp;
			}
			|	PATH_FOR_ASSEMBLY_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->path_for_assembly = $3;
				$$ = temp;
			}
			|	PATH_ON_SPACECRAFT_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->path_on_spacecraft = $3;
				$$ = temp;
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//            Productions pertaining to device definition in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

DEVICE_SECTION		:	OPEN_DEVICE_SY DEVICE_ATTRIBUTES SLASHCLOSE_SY
			{
				$$ = $2;
			}
			|	OPEN_DEVICE_SY DEVICE_ATTRIBUTES CLOSE_SY DEVICE_SUBELEMENTS CLOSE_DEVICE_SY CLOSE_SY QUALIFIERS_SECTION
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->qualifiers = $7;
				merge_app_dev_attr($2,temp);
				$$ = merge_app_dev_attr($2,$4);
			}
			;

DEVICE_SUBELEMENTS	:	DEVICE_SUBELEMENTS DEVICE_SUBELEMENT
			{
				$$ = merge_app_dev_attr($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

DEVICE_SUBELEMENT	:	QUALIFIER
			{
				app_dev_attr* temp = new_app_dev_attr();
				temp->qualifiers = $1;
				$$ = temp;
			}
			|	LOCATION_SECTION
			{
				delete_location($1);	//Location not used
				$$ = NULL;
			}
			|	ORIENTATION_SECTION
			{
				delete_orientation($1);	//Orientation not used
				$$ = NULL;
			}
			;

DEVICE_ATTRIBUTES	:	DEVICE_ATTRIBUTES DEVICE_ATTRIBUTE
			{
				$$ = merge_app_dev_attr($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

DEVICE_ATTRIBUTE	:	COMMON_APP_DEVICE_ATTRIBUTE
			{
				$$ = $1;
			}
			|	MODEL_ID_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->model_id = $3;
				$$ = temp;
			}
			|	VERSION_LETTER_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->version_letter = $3;
				$$ = temp;
			}
			|	SERIAL_NUMBER_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->serial_number = $3;
				$$ = temp;
			}
			|	CALIBRATION_DATE_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->calibration_date = $3;
				$$ = temp;
			}
			|	SENSITIVITY_AT_REF_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->sensitivity_at_reference = $3;
				$$ = temp;
			}
			|	REF_FREQ_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->reference_frequency = $3;
				$$ = temp;
			}
			|	REF_TEMP_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->reference_temperature = $3;
				$$ = temp;
			}
			|	MEASUREMENT_RANGE_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->measurement_range = $3;
				$$ = temp;
			}
			|	ELECTRICAL_OUTPUT_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->electrical_output = $3;
				$$ = temp;
			}
			|	QUALITY_FACTOR_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->quality_factor = $3;
				$$ = temp;
			}
			|	TEMP_COEFF_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->temperature_coefficient = $3;
				$$ = temp;
			}
			|	DIRECTION_XYZ_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->direction_xyz = $3;
				$$ = temp;
			}
			|	CAL_DUE_DATE_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->cal_due_date = $3;
				$$ = temp;
			}
			|	POWER_REQS_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->power_requirements = $3;
				$$ = temp;
			}
			|	SPA_U_HUB_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->spa_u_hub = $3;
				$$ = temp;
			}
			|	SPA_U_PORT_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->spa_u_port = $3;
				$$ = temp;
			}
			|	VERSION_SY EQUAL_SY STRING
			{
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->version = $3;
				$$ = temp;
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//         Productions pertaining to location definition in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

LOCATION_SECTION	:	OPEN_LOCATION_SY LOCATION_ATTRIBUTES SLASHCLOSE_SY
			{
				$$ = $2;
			}
			|	OPEN_LOCATION_SY LOCATION_ATTRIBUTES CLOSE_SY CLOSE_LOCATION_SY CLOSE_SY
			{
				$$ = $2;
			}
			;

LOCATION_ATTRIBUTES	:	LOCATION_ATTRIBUTES LOCATION_ATTRIBUTE
			{
				$$ = merge_locations($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

LOCATION_ATTRIBUTE	:	X_SY EQUAL_SY STRING
			{
				location* x_loc = new_location();
				x_loc->x_value = $3;
				$$ = x_loc;
			}
			|	Y_SY EQUAL_SY STRING
			{
				location* y_loc = new_location();
				y_loc->y_value = $3;
				$$ = y_loc;
			}
			|	Z_SY EQUAL_SY STRING
			{
				location* z_loc = new_location();
				z_loc->z_value = $3;
				$$ = z_loc;
			}
			|	UNITS_SY EQUAL_SY STRING
			{
				location* units_val = new_location();
				units_val->units = $3;
				$$ = units_val;
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//         Productions pertaining to orientation definition in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

ORIENTATION_SECTION	:	OPEN_ORIENTATION_SY ORIENTATION_ATTRIBUTES SLASHCLOSE_SY
			{
				$$ = $2;
			}
			|	OPEN_ORIENTATION_SY ORIENTATION_ATTRIBUTES CLOSE_SY CLOSE_ORIENTATION_SY CLOSE_SY
			{
				$$ = $2;
			}
			;

ORIENTATION_ATTRIBUTES	:	ORIENTATION_ATTRIBUTES ORIENTATION_ATTRIBUTE
			{
				$$ = merge_orientations($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

ORIENTATION_ATTRIBUTE	:	AXIS_SY EQUAL_SY STRING
			{
				orientation* temp = new_orientation();
				temp->axis_value = $3;
				$$ = temp;
			}
			|	ANGLE_SY EQUAL_SY STRING
			{
				orientation* temp = new_orientation();
				temp->angle_value = $3;
				$$ = temp;
			}
			| 	UNITS_SY EQUAL_SY STRING
			{
				orientation* temp = new_orientation();
				temp->units_value = $3;
				$$ = temp;
			}
/////////////////////////////////////////////////////////////////////////////////
//
//         Productions pertaining to qualifier definition in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////
			;
QUALIFIERS_SECTION	:	QUALIFIERS_SECTION QUALIFIER
			{
				$$= link_qualifiers($1,$2);
			}
			|	/*empty*/
			{
				$$= NULL;
			}
			;

QUALIFIER		:	OPEN_QUALIFIER_SY QUALIFIERS_ATTRIBUTES CLOSE_SY CLOSE_QUALIFIER_SY CLOSE_SY
			{
				$$=$2
			}
			|	OPEN_QUALIFIER_SY QUALIFIERS_ATTRIBUTES SLASHCLOSE_SY
			{
				$$=$2
			}
			;

QUALIFIERS_ATTRIBUTES	:	QUALIFIERS_ATTRIBUTES QUALIFIERS_ATTRIBUTE
			{
				$$ = merge_qualifiers($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

QUALIFIERS_ATTRIBUTE	:	NAME_SY EQUAL_SY STRING
			{
				qualifier_type* temp;
				temp = new_qualifier();
				temp->name = $3;
				$$ = temp;
			}
			|	VALUE_SY EQUAL_SY STRING
			{
				qualifier_type* temp;
				temp = new_qualifier();
				temp->value = $3;
				$$ = temp;
			}
			|	UNITS_SY EQUAL_SY STRING
			{
				qualifier_type* temp;
				temp = new_qualifier();
				temp->units = $3;
				$$ = temp;
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//           Productions pertaining to interface definition in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

INTERFACES		: 	INTERFACES INTERFACE
			{
				$$ = link_interface($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

INTERFACE		:	INTERFACE_HEAD INTERFACE_SUBELEMENTS VAR_SECTION MESSAGE_SECTION CLOSE_INTERFACE_SY CLOSE_SY
			{
				$$ = interface_add_references($1,$2,$3,$4);
			}
			|	INTERFACE_HEAD
			{
				$$ = $1;
			}
			;

INTERFACE_HEAD		:	OPEN_INTERFACE_SY INTERFACE_ATTRIBUTES CLOSE_SY
			{
				$$ = $2;
			}
			|	OPEN_INTERFACE_SY INTERFACE_ATTRIBUTES SLASHCLOSE_SY
			{
				$$ = $2;
			}
			;

INTERFACE_ATTRIBUTES	: 	INTERFACE_ATTRIBUTES INTERFACE_ATTRIBUTE
			{
				$$ = merge_interface($1,$2);
			}
			|	/*empty*/
			{
				interface* temp;
				temp = new_interface();
				$$ = temp;
			}
			;

INTERFACE_SUBELEMENTS	:	INTERFACE_SUBELEMENTS INTERFACE_SUBELEMENT
			{
				//Only qualifiers will be returned, all others thrown away
				$$ = link_qualifiers($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

INTERFACE_SUBELEMENT	:	QUALIFIER
			{
				$$ = $1;
			}
			|	LOCATION_SECTION
			{
				// Don't need to save location information for an interface
				delete_location($1);
				$$ = NULL;
			}
			|	ORIENTATION_SECTION
			{
				// Don't need to save orientation information for an interface
				delete_orientation($1);
				$$ = NULL;
			}
			;

INTERFACE_ATTRIBUTE	:	NAME_SY EQUAL_SY STRING
			{
				interface* temp;
				temp = new_interface();
				temp->name = $3;
				$$ = temp;
			}
			|	EXTENDS_SY EQUAL_SY STRING
			{
				interface* temp;
				temp = new_interface();
				temp->extends = $3;
				$$ = temp;
			}
			|	ID_SY EQUAL_SY STRING
			{
				interface* temp;
				temp = new_interface();
				temp->id = $3;
				$$ = temp;
			}
			|	DESCRIPTION_SY EQUAL_SY STRING
			{
				interface* temp;
				temp = new_interface();
				temp->description = $3;
				$$ = temp;
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//            Productions pertaining to message definition in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

MESSAGE_SECTION		:	MESSAGE_SECTION MESSAGES
			{
				$$ = merge_message($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

MESSAGES		:	COMMAND_SECTION
			{
				message* temp;
				temp = new_message();
				temp->commands = $1;
				$$ = temp;
			}
			|	NOTIFICATION_SECTION
			{
				message* temp;
				temp = new_message();
				temp->notifications = $1;
				$$ = temp;
			}
			|	REQUEST_SECTION
			{
				message* temp;
				temp = new_message();
				temp->requests = $1;
				$$ = temp;
			}
			;

REQUEST_SECTION		:	OPEN_REQUEST_SY CLOSE_SY COMMAND_MSG_SECTION DATA_MSG_SECTION FAULT_MSG_SECTION CLOSE_REQUEST_SY CLOSE_SY
			{
				request* temp;
				temp = new_request();
				temp = request_add_cmd_msg(temp,$3);
				temp = request_add_data_msg(temp,$4);
				$$ = request_add_fault_msg(temp,$5);
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//             Productions pertaining to fault messages in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

FAULT_MSG_SECTION	:	FAULT_MSG
			{
				$$ = $1;
			}
			;

FAULT_MSG		:	OPEN_FAULT_MSG_SY FAULT_MSG_ATTRIBUTES CLOSE_SY FAULT_MSG_QUALIFIERS VARIABLE_REFS CLOSE_FAULT_MSG_SY CLOSE_SY
			{
				fault_msg* result;
				result = merge_fault_msg($2,$4);
				$$ = fault_add_var_refs(result,$5);
			}
			|	OPEN_FAULT_MSG_SY FAULT_MSG_ATTRIBUTES SLASHCLOSE_SY
			{
				$$ = $2;
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

FAULT_MSG_ATTRIBUTES	:	FAULT_MSG_ATTRIBUTES FAULT_MSG_ATTRIBUTE
			{
				$$ = merge_fault_msg($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

FAULT_MSG_ATTRIBUTE	:	NAME_SY EQUAL_SY STRING
			{
				fault_msg* temp;
				temp = new_fault_msg();
				temp->name = $3;
				$$ = temp;
			}
			|	ID_SY EQUAL_SY STRING
			{
				fault_msg* temp;
				temp = new_fault_msg();
				temp->id = $3;
				$$ = temp;
			}
			|	DESCRIPTION_SY EQUAL_SY STRING
			{
				fault_msg* temp;
				temp = new_fault_msg();
				temp->description = $3;
				$$ = temp;
			}
			;

FAULT_MSG_QUALIFIERS	:	QUALIFIERS_SECTION
			{
				fault_msg* temp;
				temp = new_fault_msg();
				temp->qualifiers = $1;
				$$ = temp;
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//      Productions pertaining to data and notification messages in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

NOTIFICATION_SECTION	:	OPEN_NOTIFICATION_SY CLOSE_SY DATA_MSG_SECTION FAULT_MSG_SECTION CLOSE_NOTIFICATION_SY CLOSE_SY
			{
				notification* temp;
				temp = new_notification();
				temp = notification_add_data_msg(temp,$3);
				$$ = notification_add_fault_msg(temp,$4);
			}
			;

DATA_MSG_SECTION	:	DATA_MSG_SECTION DATA_MSG
			{
				$$ = link_data_msg($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

DATA_MSG		:	OPEN_DATA_MSG_SY DATA_MSG_ATTRIBUTES CLOSE_SY DATA_MSG_QUALIFIERS VARIABLE_REFS CLOSE_DATA_MSG_SY CLOSE_SY
			{
				data_msg* result;
				result = merge_data_msg($2,$4);
				$$ = data_add_var_refs(result,$5);
			}
			;

DATA_MSG_ATTRIBUTES	:	DATA_MSG_ATTRIBUTES DATA_MSG_ATTRIBUTE
			{
				$$=merge_data_msg($1,$2);
			}
			|	/*empty*/
			{
				$$=NULL;
			}
			;

DATA_MSG_ATTRIBUTE	:	NAME_SY EQUAL_SY STRING
			{
				data_msg* temp;
				temp = new_data_msg();
				temp->name = $3;
				$$ = temp;
			}
			|	ID_SY EQUAL_SY STRING
			{
				data_msg* temp;
				temp = new_data_msg();
				temp->id = $3;
				$$ = temp;
			}
			|	MSG_ARRIVAL_SY EQUAL_SY STRING
			{
				data_msg* temp;
				temp = new_data_msg();
				temp->msg_arrival = $3;
				$$ = temp;
			}
			|	DESCRIPTION_SY EQUAL_SY STRING
			{
				data_msg* temp;
				temp = new_data_msg();
				temp->description = $3;
				$$ = temp;
			}
			|	MSG_RATE_SY EQUAL_SY STRING
			{
				data_msg* temp;
				temp = new_data_msg();
				temp->msg_rate = $3;
				$$ = temp;
			}
			;

DATA_MSG_QUALIFIERS	:	QUALIFIERS_SECTION
			{
				data_msg* temp;
				temp = new_data_msg();
				temp->qualifiers = $1;
				$$ = temp;
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//            Productions pertaining to command messages in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

COMMAND_SECTION		:	OPEN_COMMAND_SY CLOSE_SY COMMAND_MSG_SECTION FAULT_MSG_SECTION CLOSE_COMMAND_SY CLOSE_SY
			{
				command* temp;
				temp = new_command();
				temp = command_add_cmd_msg(temp,$3);
				$$ = command_add_fault_msg(temp,$4);
			}
			;

COMMAND_MSG_SECTION	:	COMMAND_MSG_SECTION COMMAND_MSG
			{
				$$ = link_cmd_msg($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

COMMAND_MSG		:	OPEN_COMMAND_MSG_SY COMMAND_MSG_ATTRIBUTES CLOSE_SY COMMAND_MSG_QUALIFIERS VARIABLE_REFS CLOSE_COMMAND_MSG_SY CLOSE_SY
			{	
				cmd_msg* result;
				result = merge_cmd_msg($2,$4);
				$$ = cmd_add_var_refs(result,$5);
			}
			|	OPEN_COMMAND_MSG_SY COMMAND_MSG_ATTRIBUTES SLASHCLOSE_SY
			{
				$$ = cmd_add_var_refs($2,NULL);
			}
			;

COMMAND_MSG_ATTRIBUTES	:	COMMAND_MSG_ATTRIBUTES COMMAND_MSG_ATTRIBUTE
			{
				$$ = merge_cmd_msg($1,$2);
			}
			|	/*empty*/
			{
				$$=NULL;
			}
			;

COMMAND_MSG_ATTRIBUTE	:	NAME_SY EQUAL_SY STRING
			{
				cmd_msg* temp;
				temp = new_cmd_msg();
				temp->name = $3;
				$$ = temp;
			}
			|	ID_SY EQUAL_SY STRING
			{
				cmd_msg* temp;
				temp = new_cmd_msg();
				temp->id = $3;
				$$ = temp;
			}
			|	DESCRIPTION_SY EQUAL_SY STRING
			{
				cmd_msg* temp;
				temp = new_cmd_msg();
				temp->description = $3;
				$$ = temp;
			}
			;

COMMAND_MSG_QUALIFIERS	:	QUALIFIERS_SECTION
			{
				cmd_msg* temp;
				temp = new_cmd_msg();
				temp->qualifiers = $1;
				$$ = temp;
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//            Productions pertaining to variable definition in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

VAR_SECTION		:	VAR_SECTION VARIABLE
			{
				$$= link_variables($1,$2);
			}
			|	/*empty*/
			{
				$$= NULL;
			}
			;

VARIABLE		:	VAR_WITH_SUBELEMENTS
			{		
				$$=$1
			}
			|	VAR_NO_SUBELEMENTS
			{
				$$=$1
			}
			;

VAR_WITH_SUBELEMENTS	:	VAR_HEAD CLOSE_SY VAR_ELEMENTS CLOSE_VAR_SY CLOSE_SY
			{
				$$ =  merge_variables($1,$3);
			}
			;

VAR_NO_SUBELEMENTS	:	VAR_HEAD SLASHCLOSE_SY
			;

VAR_HEAD		:	OPEN_VAR_SY VAR_ATTRIBUTES
			{
				$$= $2
			}
			;

VAR_ATTRIBUTES		:	VAR_ATTRIBUTES VAR_ATTRIBUTE
			{
				$$= merge_variables($1,$2);
			}
			|	/*empty*/
			{
				$$=NULL;
			}		
			;

VAR_ATTRIBUTE		:	NAME_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->name = $3;
				$$ = temp;
			}
			|	KIND_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->kind = $3;
				$$ = temp;
			}
			|	FORMAT_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->format = $3;
				$$ = temp;
			}
			|	QUALIFIER_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->qualifier = $3;
				printf("<Variable qualifier attribute has been deprecated!\n");
				$$ = temp;
			}
			|	ID_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->id = $3;
				$$ = temp;
			}
			|	DESCRIPTION_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->description = $3;
				$$ = temp;
			}
			|	RANGE_MIN_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->range_min = $3;
				$$ = temp;
			}
			|	RANGE_MAX_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->range_max = $3;
				$$ = temp;
			}	
			|	LENGTH_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->length = $3;
				$$ = temp;
			}
			|	DEFAULT_VALUE_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->default_value = $3;
				$$ = temp;
			}
			|	PRECISION_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->precision = $3;
				$$ = temp;
			}
			|	UNITS_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->units = $3;
				$$ = temp;
			}
			|	ACCURACY_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->accuracy = $3;
				$$ = temp;
			}
			|	SCALE_FACTOR_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->scale_factor = $3;
				$$ = temp;
			}
			|	SCALE_UNITS_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->scale_units = $3;
				$$ = temp;
			}
			|	R_LOW_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->r_low = $3;
				$$ = temp;
			}
			|	R_HIGH_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->r_high = $3;
				$$ = temp;
			}
			|	Y_LOW_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->y_low = $3;
				$$ = temp;
			}
			|	Y_HIGH_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->y_high = $3;
				$$ = temp;
			}
			|
				INVALID_VALUE_SY EQUAL_SY STRING
			{
				variable* temp;
				temp = new_variable();
				temp->invalid_value = $3;
				$$ = temp;
			}
			;

VAR_ELEMENTS		: 	VAR_QUALIFIERS VAR_SUBELEMENTS
			{
				$$ = merge_variables($1,$2);
			}
			;

VAR_QUALIFIERS		:	QUALIFIERS_SECTION
			{
				variable* temp;
				temp = new_variable();
				temp->qualifiers = $1;
				$$ = temp;
			}
			;
	

VAR_SUBELEMENTS		:	VAR_SUBELEMENTS VAR_SUBELEMENT
			{
				$$ = merge_variables($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

VAR_SUBELEMENT		:	DRANGE
			{
				variable* temp;
				temp = new_variable();
				temp->dranges = $1;
				$$ = temp;
			}
			|	CURVE
			{
				variable* temp;
				temp = new_variable();
				temp->curves = $1;
				$$ = temp;
			}
			|	LOCATION_SECTION
			{
				variable* temp;
				temp = new_variable();
				temp->location_data = $1;
				$$ = temp;
			}
			|	ORIENTATION_SECTION
			{
				variable* temp;
				temp = new_variable();
				temp->orientation_data = $1;
				$$ = temp;
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//         Variable references for command, fault, and data messages
//
/////////////////////////////////////////////////////////////////////////////////

VARIABLE_REFS		:	VARIABLE_REFS VARIABLE_REF
			{
				$$ = link_variable_ref($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

VARIABLE_REF		:	OPEN_VARIABLE_REF_SY NAME_SY EQUAL_SY STRING SLASHCLOSE_SY
			{
				$$ = new_variable_ref($4);
			}
			|	OPEN_VARIABLE_REF_SY NAME_SY EQUAL_SY STRING CLOSE_SY CLOSE_VARIABLE_REF_SY CLOSE_SY
			{
				$$ = new_variable_ref($4);
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//   Productions pertaining to discrete range variable definition in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

DRANGE			:	DRANGE_HEAD DRANGE_OPTIONS CLOSE_DRANGE_SY CLOSE_SY
			{
				drange* temp;
				temp = new_drange();
				temp->options = $2;
				$$ = merge_dranges($1,temp);
			}
			;

DRANGE_HEAD		:	OPEN_DRANGE_SY DRANGE_ATTRIBUTES CLOSE_SY
			{
				$$ = $2;
			}
			;

DRANGE_ATTRIBUTES	:	DRANGE_ATTRIBUTES DRANGE_ATTRIBUTE
			{
				$$ = merge_dranges($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

DRANGE_ATTRIBUTE	:	NAME_SY EQUAL_SY STRING
			{
				drange* temp;
				temp = new_drange();
				temp->name = $3;
				$$ = temp;
			}
			|	DESCRIPTION_SY EQUAL_SY STRING
			{
				drange* temp;
				temp = new_drange();
				temp->description = $3;
				$$ = temp;
			}
			;

DRANGE_OPTIONS		:	DRANGE_OPTIONS DRANGE_OPTION
			{
				$$ = link_options($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

DRANGE_OPTION		:	OPEN_OPTION_SY OPTION_ATTRIBUTES SLASHCLOSE_SY
			{
				$$ = $2;
			}
			|	OPEN_OPTION_SY OPTION_ATTRIBUTES CLOSE_SY CLOSE_OPTION_SY CLOSE_SY
			{
				$$ = $2;
			}
			;

OPTION_ATTRIBUTES	:	OPTION_ATTRIBUTES OPTION_ATTRIBUTE
			{
				$$ = merge_options($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

OPTION_ATTRIBUTE	:	NAME_SY EQUAL_SY STRING			
			{
				curveoption* temp;
				temp = new_option();
				temp->name = $3;
				$$ = temp;
			}
			|	VALUE_SY EQUAL_SY STRING
			{
				curveoption* temp;
				temp = new_option();
				temp->value = $3;
				$$ = temp;
			}
			|	DESCRIPTION_SY EQUAL_SY STRING
			{
				curveoption* temp;
				temp = new_option();
				temp->description = $3;
				$$ = temp;
			}
			|	ALARM_SY EQUAL_SY STRING
			{
				curveoption* temp;
				temp = new_option();
				temp->alarm = $3;
				$$ = temp;
			}
			;
/////////////////////////////////////////////////////////////////////////////////
//
//        Productions pertaining to curve variable definition in xTEDS
//
/////////////////////////////////////////////////////////////////////////////////

CURVE			:	CURVE_HEAD CURVE_COEFFS CLOSE_CURVE_SY CLOSE_SY
			{
				curve* temp;
				temp = new_curve();
				temp->coefs = $2;
				$$ = merge_curves($1,temp);
			}
			;

CURVE_HEAD		:	OPEN_CURVE_SY CURVE_ATTRIBUTES CLOSE_SY
			{
				$$ = $2;
			}
			;

CURVE_ATTRIBUTES	:	CURVE_ATTRIBUTES CURVE_ATTRIBUTE
			{
				$$ = merge_curves($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

CURVE_ATTRIBUTE		:	NAME_SY EQUAL_SY STRING
			{
				curve* temp;
				temp = new_curve();
				temp->name = $3;
				$$ = temp;
			}
			|	DESCRIPTION_SY EQUAL_SY STRING
			{
				curve* temp;
				temp = new_curve();
				temp->description = $3;
				$$ = temp;
			}
			;

CURVE_COEFFS		:	CURVE_COEFFS CURVE_COEFF
			{
				$$ = link_coefs($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

CURVE_COEFF		:	OPEN_COEFF_SY COEFF_ATTRIBUTES SLASHCLOSE_SY
			{
				$$ = $2;
			}
			|	OPEN_COEFF_SY COEFF_ATTRIBUTES CLOSE_SY CLOSE_COEFF_SY CLOSE_SY
			{
				$$ = $2;
			}
			|	OPEN_COEFF_SY COEFF_ATTRIBUTES CLOSE_SY
			{
				$$ = $2;
			}
			;

COEFF_ATTRIBUTES	:	COEFF_ATTRIBUTES COEFF_ATTRIBUTE
			{
				$$ = merge_coefs($1,$2);
			}
			|	/*empty*/
			{
				$$ = NULL;
			}
			;

COEFF_ATTRIBUTE		:	EXPONENT_SY EQUAL_SY STRING
			{
				coef* temp;
				temp = new_coef();
				temp->exponent = $3;
				$$ = temp;
			}
			|	VALUE_SY EQUAL_SY STRING
			{
				coef* temp;
				temp = new_coef();
				temp->value = $3;
				$$ = temp;
			}
			|	DESCRIPTION_SY EQUAL_SY STRING
			{
				coef* temp;
				temp = new_coef();
				temp->description = $3;
				$$ = temp;
			}
			;
%%
