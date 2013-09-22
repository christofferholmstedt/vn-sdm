%{
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WIN32
# ifndef strndup
#  include "../MemoryUtils.h"
# endif
#else
# include "unistd.h"
#endif

#include "xTEDS.tab.h"
int line_count = 1;
%}

%option nounput

%%

"="						{return EQUAL_SY;}
">"						{return CLOSE_SY;}
"/>"						{return SLASHCLOSE_SY;}
"?>"						{return CLOSE_XML_SY;}

"<?xml"						{return OPEN_XML_SY;}
"</xTEDS"					{return CLOSE_xTEDS_SY;}
"<xTEDS"					{return OPEN_xTEDS_SY;}
"<Application"					{return OPEN_APP_SY;}
"</Application"					{return CLOSE_APP_SY;}
"<Variable"					{return OPEN_VAR_SY;}
"</Variable"					{return CLOSE_VAR_SY;}
"<Drange"					{return OPEN_DRANGE_SY;}
"</Drange"					{return CLOSE_DRANGE_SY;}
"<Option"					{return OPEN_OPTION_SY;}
"</Option"					{return CLOSE_OPTION_SY;}
"<Curve"					{return OPEN_CURVE_SY;}
"</Curve"					{return CLOSE_CURVE_SY;}
"<Coef"						{return OPEN_COEFF_SY;}
"</Coef"					{return CLOSE_COEFF_SY;}
"<DataMsg"|"<DataReplyMsg"			{return OPEN_DATA_MSG_SY;}
"</DataMsg"|"</DataReplyMsg"			{return CLOSE_DATA_MSG_SY;}
"<VariableRef"					{return OPEN_VARIABLE_REF_SY;}
"</VariableRef"					{return CLOSE_VARIABLE_REF_SY;}
"<CommandMsg"					{return OPEN_COMMAND_MSG_SY;}
"</CommandMsg"					{return CLOSE_COMMAND_MSG_SY;}
"<Device"					{return OPEN_DEVICE_SY;}
"</Device"					{return CLOSE_DEVICE_SY;}
"<Interface"					{return OPEN_INTERFACE_SY;}
"</Interface"					{return CLOSE_INTERFACE_SY;}
"<Command"					{return OPEN_COMMAND_SY;}
"</Command"					{return CLOSE_COMMAND_SY;}
"<Notification"					{return OPEN_NOTIFICATION_SY;}
"</Notification"				{return CLOSE_NOTIFICATION_SY;}
"<Request"					{return OPEN_REQUEST_SY;}
"</Request"					{return CLOSE_REQUEST_SY;}
"<FaultMsg"					{return OPEN_FAULT_MSG_SY;}
"</FaultMsg"					{return CLOSE_FAULT_MSG_SY;}
"<Qualifier"					{return OPEN_QUALIFIER_SY;}
"</Qualifier"					{return CLOSE_QUALIFIER_SY;}
"<Location"					{return OPEN_LOCATION_SY;}
"</Location"					{return CLOSE_LOCATION_SY;}
"<Orientation"					{return OPEN_ORIENTATION_SY;}
"</Orientation"					{return CLOSE_ORIENTATION_SY;}

"invalidValue"					{return INVALID_VALUE_SY;
/* Because "id" is a substring of "invalidValue", the following pattern will
catch a misspelling of "invalidValue" without matching "id".  This prevents the
parser from incorrectly reducing grammar rules that were intended for "invalidValue"
but instead "id" was matched -- specifically with <Variable> attributes.*/}
[^ \t\n]"id"|"id"[^ \t\n=]			{return BAD_TERMINAL_SY;}
"name"						{return NAME_SY;}
"kind"						{return KIND_SY;}
"id"						{return ID_SY;}
"qualifier"					{return QUALIFIER_SY;}
"description"					{return DESCRIPTION_SY;}
"manufacturerId"				{return MANUFACTURER_ID_SY;}
"version"					{return VERSION_SY;}
"modelId"					{return MODEL_ID_SY;}
"versionLetter"					{return VERSION_LETTER_SY;}
"serialNumber"					{return SERIAL_NUMBER_SY;}
"calibrationDate"				{return CALIBRATION_DATE_SY;}
"sensitivityAtReference"			{return SENSITIVITY_AT_REF_SY;}
"referenceFrequency"				{return REF_FREQ_SY;}
"referenceTemperature"				{return REF_TEMP_SY;}
"measurementRange"				{return MEASUREMENT_RANGE_SY;}
"electricalOutput"				{return ELECTRICAL_OUTPUT_SY;}
"qualityFactor"					{return QUALITY_FACTOR_SY;}
"temperatureCoefficient"			{return TEMP_COEFF_SY;}
"directionXYZ"					{return DIRECTION_XYZ_SY;}
"calDueDate"					{return CAL_DUE_DATE_SY;}
"powerRequirements"				{return POWER_REQS_SY;}
"value"						{return VALUE_SY;}
"alarm"						{return ALARM_SY;}
"msgArrival"					{return MSG_ARRIVAL_SY;}
"msgRate"					{return MSG_RATE_SY;}
"precision"					{return PRECISION_SY;}
"rangeMax"					{return RANGE_MAX_SY;}
"format"					{return FORMAT_SY;}
"accuracy"					{return ACCURACY_SY;}
"rangeMin"					{return RANGE_MIN_SY;}
"scaleFactor"					{return SCALE_FACTOR_SY;}
"units"						{return UNITS_SY;}
"defaultValue"					{return DEFAULT_VALUE_SY;}
"scaleUnits"					{return SCALE_UNITS_SY;}
"length"					{return LENGTH_SY;}
"exponent"					{return EXPONENT_SY;}
"componentKey"					{return COMPONENT_KEY_SY;}
"SPA_U_hub"|"spaUHub"				{return SPA_U_HUB_SY;}
"SPA_U_port"|"spaUPort"				{return SPA_U_PORT_SY;}
"extends"					{return EXTENDS_SY;}
"memoryMinimum"					{return MEMORY_MINIMUM_SY;}
"operatingSystem"				{return OPERATING_SYSTEM_SY;}
"pathForAssembly"				{return PATH_FOR_ASSEMBLY_SY;}
"pathOnSpacecraft"				{return PATH_ON_SPACECRAFT_SY;}
"x"						{return X_SY;}
"y"						{return Y_SY;}
"z"						{return Z_SY;}
"axis"						{return AXIS_SY;}
"angle"						{return ANGLE_SY;}
"encoding"					{return ENCODING_SY;}
"standalone"					{return STANDALONE_SY;}
"rLow"						{return R_LOW_SY;}
"rHigh"						{return R_HIGH_SY;}
"yLow"						{return Y_LOW_SY;}
"yHigh"						{return Y_HIGH_SY;}

"xmlns"						{return XMLNS_SY;}
"xmlns:xsi"					{return XMLNS_XSI_SY;}
"xsi:schemaLocation"				{return SCHEMA_LOCATION_SY;}


\"[^"]*\"					{xTEDSlval.str = strndup(yytext+1,strlen(yytext)-2);return STRING;}
[0-9]*[.][0-9]+					{xTEDSlval.real = atof(yytext); return FLOAT;}
[0-9]+						{xTEDSlval.integer = atoi(yytext); return INT;}

"<!--"(([^-]*.[^-])*)*"-->"|"<!-- -->"		{/*ignore xteds comments*/}

[ \t]*						{/*ignore whitespace*/}

"\n"						{line_count++;}

.                                               {/* catch all, don't print invalid chars*/}

%%

int yywrap() {return 1;}
void xTEDSerror(char *s)
{
	printf("   Syntax error in xTEDS on line %d at token \"%s\".\n",line_count,yytext);
}
