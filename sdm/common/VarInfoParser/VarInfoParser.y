%{
#include <stdio.h>
#include <string.h>
#include "../xTEDS/xTEDSParser.h"
%}


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
%token CLOSE_COEFF_SY

%type<str> STRING
%type<integer> INT
%type<real> FLOAT
%type<var> VAR_ATTRIBUTES VAR_ATTRIBUTE VARIABLE VAR_HEAD VAR_WITH_SUBELEMENTS VAR_NO_SUBELEMENTS VAR_SUBELEMENT VAR_SUBELEMENTS
%type<var> VAR_ELEMENTS VAR_QUALIFIERS
%type<qual> QUALIFIERS_SECTION QUALIFIERS QUALIFIERS_WITH_SUBELEMENTS QUALIFIERS_NO_SUBELEMENTS QUALIFIERS_HEAD 
%type<qual> QUALIFIERS_ATTRIBUTE QUALIFIERS_ATTRIBUTES 
%type<coef> CURVE_COEFFS CURVE_COEFF COEFF_ATTRIBUTES COEFF_ATTRIBUTE
%type<curve> CURVE_HEAD CURVE_ATTRIBUTES CURVE_ATTRIBUTE CURVE
%type<curveoption> DRANGE_OPTIONS DRANGE_OPTION OPTION_ATTRIBUTES OPTION_ATTRIBUTE
%type<drange> DRANGE_HEAD DRANGE_ATTRIBUTES DRANGE_ATTRIBUTE DRANGE

%union
{
	int integer;
	float real;
	char* str;
	struct variable_data* var;
	struct qualifier_data* qual;
	struct coefficient_data* coef;
	struct curve_data* curve;
	struct option_data* curveoption;
	struct drange_data* drange;
}


%%

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
				printf("Qualifier field has been deprecated!\n");
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
			;

QUALIFIERS		:	QUALIFIERS_WITH_SUBELEMENTS
{
				$$=$1
}
			|	QUALIFIERS_NO_SUBELEMENTS
{
				$$=$1
}
			;

QUALIFIERS_WITH_SUBELEMENTS	:	QUALIFIERS_HEAD CLOSE_SY QUALIFIERS_SUBELEMENTS CLOSE_QUALIFIER_SY CLOSE_SY
{
					$$ = $1;
}
				;

QUALIFIERS_NO_SUBELEMENTS	:	QUALIFIERS_HEAD SLASHCLOSE_SY
{
					$$ = $1;
}
				;

QUALIFIERS_SUBELEMENTS	:	/*empty*/
			;

QUALIFIERS_HEAD		:	OPEN_QUALIFIER_SY QUALIFIERS_ATTRIBUTES
{
				$$ = $2;
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
QUALIFIERS_SECTION	:	QUALIFIERS_SECTION QUALIFIERS
{
	$$= link_qualifiers($1,$2);
}
			|	/*empty*/
{
	$$= NULL;
}
			;
			
%%