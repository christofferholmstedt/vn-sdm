%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "msgdef.tab.h"
%}

%option nounput

%%

"<"				{return LT_SY;}
"="				{return EQUAL_SY;}
"/"				{return SLASH_SY;}
">"				{return GT_SY;}
":"				{return COLON_SY;}

"DataMsg"			{return DATA_MSG_SY;}
"CommandMsg"			{return CMD_MSG_SY;}
"FaultMsg"			{return FAULT_MSG_SY;}

[dD][aA][tT][aA]_[rR][eE][pP][lL][yY]_[mM][sS][gG]_[nN][aA][mM][eE]	{return REPLY_SY;}
[cC][oO][mM][mM][aA][nN][dD]_[mM][sS][gG]_[nN][aA][mM][eE]		{return REPLY_SY;}
"Request"			{return RQST_SY;}
"Notification"			{return NOTI_SY;}
"Command"			{return CMD_SY;}

"id"				{return ID_SY;}

"name"				{return NAME_SY;}
"Variable"			{return VAR_SY;}
"length"			{return LENGTH_SY;}
"NS"				{return NOT_SPECIFIED_SY;}

"UINT08"|"INT08"|"UINT16"|"INT16"|"UINT32"|"INT32"|"FLOAT32"|"FLOAT64"	{ MessageManipulatorlval.str = strdup(yytext); return DATATYPE; }

\"[^"]*\"			{MessageManipulatorlval.str = strndup(yytext+1, strlen(yytext)-2); return STRING;}
[0-9]*[.][0-9]+			{MessageManipulatorlval.real = atof(yytext); return FLOAT;}
[0-9]+				{MessageManipulatorlval.integer = atoi(yytext); return INT;}


[ ]*|[\t]*|[\n]*		{/*ignore whitespace*/}
.				{printf ("Invalid token\n");}

%%

int yywrap() {return 1;}

void MessageManipulatorerror(const char *str)
{
	fprintf(stderr,"MessageManipulator error: %s on token %s\n",str,yytext);
}
