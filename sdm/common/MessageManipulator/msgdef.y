%{
/*xTEDS 1.0 msg_def parser*/
#include <stdio.h>
#include <stdlib.h>
#include "./message.h"

int yylex(void);

void yyerror(const char *str);

int yydebug=0;

%}

/*punctuation*/
%token LT_SY CMD_MSG_SY DATA_MSG_SY NAME_SY EQUAL_SY SLASH_SY GT_SY COLON_SY VAR_SY
%token LENGTH_SY COUNTMAX_SY RATEMAX_SY RQST_SY REPLY_SY ID_SY FAULT_MSG_SY
%token CMD_SY NOTI_SY ID_SY DATATYPE FLOAT INT STRING NOT_SPECIFIED_SY

%union
{
	int integer;
	float real;
	char* str;
	struct variable* var;
	struct node_data* node;
}

%type <str> STRING DATATYPE
%type <integer> INT ATTRIBUTE
%type <real> FLOAT
%type <node> MSG_DEF FAULT_MSG
%type <var> VARIABLES VARIABLE

%start INFO


%%
INFO		: LT_SY RQST_SY GT_SY LT_SY MSG_DEF SLASH_SY GT_SY LT_SY MSG_DEF SLASH_SY GT_SY LT_SY SLASH_SY RQST_SY GT_SY
		{
			setMessage($5,$9,NULL);
		}
		| LT_SY RQST_SY GT_SY LT_SY MSG_DEF SLASH_SY GT_SY LT_SY MSG_DEF SLASH_SY GT_SY LT_SY FAULT_MSG SLASH_SY GT_SY LT_SY SLASH_SY RQST_SY GT_SY
		{
			setMessage($5,$9,$13);
		}
		| LT_SY CMD_SY GT_SY LT_SY MSG_DEF SLASH_SY GT_SY LT_SY SLASH_SY CMD_SY GT_SY
		{
			setMessage($5,NULL,NULL);
		}
		| LT_SY CMD_SY GT_SY LT_SY MSG_DEF SLASH_SY GT_SY LT_SY FAULT_MSG SLASH_SY GT_SY LT_SY SLASH_SY CMD_SY GT_SY
		{
			setMessage($5,NULL,$9);
		}
		| LT_SY NOTI_SY GT_SY LT_SY MSG_DEF SLASH_SY GT_SY LT_SY SLASH_SY NOTI_SY GT_SY
		{
			setMessage(NULL,$5,NULL);
		}
		| LT_SY NOTI_SY GT_SY LT_SY MSG_DEF SLASH_SY GT_SY LT_SY FAULT_MSG SLASH_SY GT_SY LT_SY SLASH_SY NOTI_SY GT_SY
		{
			setMessage(NULL,$5,$9);
		}
		;

FAULT_MSG	: FAULT_MSG_SY NAME_SY EQUAL_SY STRING ID_SY EQUAL_SY STRING VARIABLES ATTRIBUTE
		{
			$$ = newNode($4,FAULTMSG,$9,atoi($7),$8);
			if ($7 != NULL) free($7);
		}
		;
		
MSG_DEF		:CMD_MSG_SY NAME_SY EQUAL_SY STRING ID_SY EQUAL_SY STRING VARIABLES ATTRIBUTE
		{
			$$ = newNode($4,COMMANDMSG,$9,atoi($7),$8);
			if ($7 != NULL) free($7);
		}
		|DATA_MSG_SY NAME_SY EQUAL_SY STRING ID_SY EQUAL_SY STRING VARIABLES ATTRIBUTE
		{
			$$ = newNode($4,DATAMSG,$9,atoi($7),$8);
			if ($7 != NULL) free($7);
		}
		;

VARIABLES	: VARIABLES VARIABLE
		{
			$$ = addVar(&$1,$2);
		}
		| /*empty*/
		{
			$$ = NULL;
		}
		;

VARIABLE	: VAR_SY COLON_SY INT COLON_SY INT COLON_SY FLOAT COLON_SY NOT_SPECIFIED_SY COLON_SY DATATYPE EQUAL_SY STRING
		{	/*Invalid type is not specified*/
			$$ = newVar($13,$3,$5,$11,$7);
		}
		| VAR_SY COLON_SY INT COLON_SY INT COLON_SY FLOAT COLON_SY INT COLON_SY DATATYPE EQUAL_SY STRING
		{	/*Invalid type is an int*/
			$$ = newVarInvalidIsInt($13,$3,$5,$11,$7,$9);
		}
		| VAR_SY COLON_SY INT COLON_SY INT COLON_SY FLOAT COLON_SY FLOAT COLON_SY DATATYPE EQUAL_SY STRING
		{	/*Invalid type is a float*/
			$$ = newVarInvalidIsFloat($13,$3,$5,$11,$7,$9);
		}
		
		;


ATTRIBUTE	: LENGTH_SY EQUAL_SY STRING
		{
			$$ = atoi($3);
			if ($3 != NULL) free($3);
		}
		;
%%
