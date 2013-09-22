/* A Bison parser, made by GNU Bison 1.875d.  */

/* Skeleton parser for Yacc-like parsing with Bison,
   Copyright (C) 1984, 1989, 1990, 2000, 2001, 2002, 2003, 2004 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     LT_SY = 258,
     CMD_MSG_SY = 259,
     DATA_MSG_SY = 260,
     NAME_SY = 261,
     EQUAL_SY = 262,
     SLASH_SY = 263,
     GT_SY = 264,
     COLON_SY = 265,
     VAR_SY = 266,
     LENGTH_SY = 267,
     COUNTMAX_SY = 268,
     RATEMAX_SY = 269,
     RQST_SY = 270,
     REPLY_SY = 271,
     ID_SY = 272,
     FAULT_MSG_SY = 273,
     CMD_SY = 274,
     NOTI_SY = 275,
     DATATYPE = 276,
     FLOAT = 277,
     INT = 278,
     STRING = 279,
     NOT_SPECIFIED_SY = 280
   };
#endif
#define LT_SY 258
#define CMD_MSG_SY 259
#define DATA_MSG_SY 260
#define NAME_SY 261
#define EQUAL_SY 262
#define SLASH_SY 263
#define GT_SY 264
#define COLON_SY 265
#define VAR_SY 266
#define LENGTH_SY 267
#define COUNTMAX_SY 268
#define RATEMAX_SY 269
#define RQST_SY 270
#define REPLY_SY 271
#define ID_SY 272
#define FAULT_MSG_SY 273
#define CMD_SY 274
#define NOTI_SY 275
#define DATATYPE 276
#define FLOAT 277
#define INT 278
#define STRING 279
#define NOT_SPECIFIED_SY 280




#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 21 "msgdef.y"
typedef union YYSTYPE {
	int integer;
	float real;
	char* str;
	struct variable* var;
	struct node_data* node;
} YYSTYPE;
/* Line 1285 of yacc.c.  */
#line 95 "msgdef.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE MessageManipulatorlval;



