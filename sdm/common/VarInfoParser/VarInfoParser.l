%{
#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef WIN32
#ifndef strndup
#define strndup(s,n) __strndup(s,n)
#endif
#else
#include "unistd.h"
#endif

#include "VarInfoParser.tab.h"
%}

%%

"="						{return EQUAL_SY;}
">"						{return CLOSE_SY;}
"/>"						{return SLASHCLOSE_SY;}

"<Variable"					{return OPEN_VAR_SY;}
"</Variable"					{return CLOSE_VAR_SY;}

"<Drange"					{return OPEN_DRANGE_SY;}
"</Drange"					{return CLOSE_DRANGE_SY;}
"<Option"					{return OPEN_OPTION_SY;}
"</Option"					{return CLOSE_OPTION_SY;}
"<Qualifier"					{return OPEN_QUALIFIER_SY;}
"</Qualifier"					{return CLOSE_QUALIFIER_SY;}

"name"						{return NAME_SY;}
"kind"						{return KIND_SY;}
"id"						{return ID_SY;}
"qualifier"					{return QUALIFIER_SY;}
"description"					{return DESCRIPTION_SY;}
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
"value"						{return VALUE_SY;}

\"[^"]*\"					{VarInfoParserlval.str = strndup(yytext+1,strlen(yytext)-2);return STRING;}
[0-9]*[.][0-9]+					{VarInfoParserlval.real = atof(yytext); return FLOAT;}
[0-9]+						{VarInfoParserlval.integer = atoi(yytext); return INT;}

"<!--"(([^-]*.[^-])*)*"-->"|"<!-- -->"		{/*ignore xteds comments*/}

[ \t\n]*					{/*ignore whitespace*/}
.					{printf ("Invalid token \"%s\"\n",yytext);}

%%

int yywrap() {return 1;}
void VarInfoParsererror(char *s)
{
	printf("Error occurred at token %s (error is %s)\n",yytext, s);
}
