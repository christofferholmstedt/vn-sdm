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

/* Written by Richard Stallman by simplifying the original so called
   ``semantic'' parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Using locations.  */
#define YYLSP_NEEDED 0

/* If NAME_PREFIX is specified substitute the variables and functions
   names.  */
#define yyparse xTEDSparse
#define yylex   xTEDSlex
#define yyerror xTEDSerror
#define yylval  xTEDSlval
#define yychar  xTEDSchar
#define yydebug xTEDSdebug
#define yynerrs xTEDSnerrs


/* Tokens.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
   /* Put the tokens into the symbol table, so that GDB and other debuggers
      know about them.  */
   enum yytokentype {
     EQUAL_SY = 258,
     CLOSE_SY = 259,
     SLASHCLOSE_SY = 260,
     OPEN_XML_SY = 261,
     CLOSE_xTEDS_SY = 262,
     OPEN_xTEDS_SY = 263,
     OPEN_APP_SY = 264,
     OPEN_VAR_SY = 265,
     CLOSE_VAR_SY = 266,
     OPEN_DRANGE_SY = 267,
     CLOSE_DRANGE_SY = 268,
     OPEN_OPTION_SY = 269,
     OPEN_CURVE_SY = 270,
     CLOSE_CURVE_SY = 271,
     OPEN_COEFF_SY = 272,
     OPEN_DATA_MSG_SY = 273,
     CLOSE_DATA_MSG_SY = 274,
     OPEN_VARIABLE_REF_SY = 275,
     OPEN_COMMAND_MSG_SY = 276,
     CLOSE_COMMAND_MSG_SY = 277,
     NAME_SY = 278,
     KIND_SY = 279,
     ID_SY = 280,
     CLOSE_ORIENTATION_SY = 281,
     QUALIFIER_SY = 282,
     DESCRIPTION_SY = 283,
     MANUFACTURER_ID_SY = 284,
     VERSION_SY = 285,
     MODEL_ID_SY = 286,
     VERSION_LETTER_SY = 287,
     SERIAL_NUMBER_SY = 288,
     CALIBRATION_DATE_SY = 289,
     SENSITIVITY_AT_REF_SY = 290,
     REF_FREQ_SY = 291,
     REF_TEMP_SY = 292,
     MEASUREMENT_RANGE_SY = 293,
     ELECTRICAL_OUTPUT_SY = 294,
     QUALITY_FACTOR_SY = 295,
     TEMP_COEFF_SY = 296,
     DIRECTION_XYZ_SY = 297,
     CAL_DUE_DATE_SY = 298,
     POWER_REQS_SY = 299,
     VALUE_SY = 300,
     ALARM_SY = 301,
     MSG_ARRIVAL_SY = 302,
     MSG_RATE_SY = 303,
     STRING = 304,
     FLOAT = 305,
     INT = 306,
     PRECISION_SY = 307,
     RANGE_MAX_SY = 308,
     CLOSE_LOCATION_SY = 309,
     FORMAT_SY = 310,
     ACCURACY_SY = 311,
     RANGE_MIN_SY = 312,
     SCALE_FACTOR_SY = 313,
     UNITS_SY = 314,
     DEFAULT_VALUE_SY = 315,
     OPEN_DEVICE_SY = 316,
     SCALE_UNITS_SY = 317,
     LENGTH_SY = 318,
     EXPONENT_SY = 319,
     SCHEMA_LOCATION_SY = 320,
     XMLNS_SY = 321,
     XMLNS_XSI_SY = 322,
     CLOSE_OPTION_SY = 323,
     OPEN_INTERFACE_SY = 324,
     OPEN_COMMAND_SY = 325,
     OPEN_NOTIFICATION_SY = 326,
     OPEN_REQUEST_SY = 327,
     OPEN_FAULT_MSG_SY = 328,
     COMPONENT_KEY_SY = 329,
     SPA_U_HUB_SY = 330,
     SPA_U_PORT_SY = 331,
     EXTENDS_SY = 332,
     CLOSE_COMMAND_SY = 333,
     CLOSE_NOTIFICATION_SY = 334,
     CLOSE_REQUEST_SY = 335,
     CLOSE_FAULT_MSG_SY = 336,
     OPEN_QUALIFIER_SY = 337,
     CLOSE_QUALIFIER_SY = 338,
     CLOSE_APP_SY = 339,
     CLOSE_DEVICE_SY = 340,
     CLOSE_INTERFACE_SY = 341,
     MEMORY_MINIMUM_SY = 342,
     OPERATING_SYSTEM_SY = 343,
     PATH_FOR_ASSEMBLY_SY = 344,
     PATH_ON_SPACECRAFT_SY = 345,
     X_SY = 346,
     Y_SY = 347,
     Z_SY = 348,
     AXIS_SY = 349,
     ANGLE_SY = 350,
     OPEN_LOCATION_SY = 351,
     OPEN_ORIENTATION_SY = 352,
     CLOSE_XML_SY = 353,
     ENCODING_SY = 354,
     STANDALONE_SY = 355,
     CLOSE_VARIABLE_REF_SY = 356,
     CLOSE_COEFF_SY = 357,
     R_LOW_SY = 358,
     R_HIGH_SY = 359,
     Y_LOW_SY = 360,
     Y_HIGH_SY = 361,
     INVALID_VALUE_SY = 362,
     BAD_TERMINAL_SY = 363
   };
#endif
#define EQUAL_SY 258
#define CLOSE_SY 259
#define SLASHCLOSE_SY 260
#define OPEN_XML_SY 261
#define CLOSE_xTEDS_SY 262
#define OPEN_xTEDS_SY 263
#define OPEN_APP_SY 264
#define OPEN_VAR_SY 265
#define CLOSE_VAR_SY 266
#define OPEN_DRANGE_SY 267
#define CLOSE_DRANGE_SY 268
#define OPEN_OPTION_SY 269
#define OPEN_CURVE_SY 270
#define CLOSE_CURVE_SY 271
#define OPEN_COEFF_SY 272
#define OPEN_DATA_MSG_SY 273
#define CLOSE_DATA_MSG_SY 274
#define OPEN_VARIABLE_REF_SY 275
#define OPEN_COMMAND_MSG_SY 276
#define CLOSE_COMMAND_MSG_SY 277
#define NAME_SY 278
#define KIND_SY 279
#define ID_SY 280
#define CLOSE_ORIENTATION_SY 281
#define QUALIFIER_SY 282
#define DESCRIPTION_SY 283
#define MANUFACTURER_ID_SY 284
#define VERSION_SY 285
#define MODEL_ID_SY 286
#define VERSION_LETTER_SY 287
#define SERIAL_NUMBER_SY 288
#define CALIBRATION_DATE_SY 289
#define SENSITIVITY_AT_REF_SY 290
#define REF_FREQ_SY 291
#define REF_TEMP_SY 292
#define MEASUREMENT_RANGE_SY 293
#define ELECTRICAL_OUTPUT_SY 294
#define QUALITY_FACTOR_SY 295
#define TEMP_COEFF_SY 296
#define DIRECTION_XYZ_SY 297
#define CAL_DUE_DATE_SY 298
#define POWER_REQS_SY 299
#define VALUE_SY 300
#define ALARM_SY 301
#define MSG_ARRIVAL_SY 302
#define MSG_RATE_SY 303
#define STRING 304
#define FLOAT 305
#define INT 306
#define PRECISION_SY 307
#define RANGE_MAX_SY 308
#define CLOSE_LOCATION_SY 309
#define FORMAT_SY 310
#define ACCURACY_SY 311
#define RANGE_MIN_SY 312
#define SCALE_FACTOR_SY 313
#define UNITS_SY 314
#define DEFAULT_VALUE_SY 315
#define OPEN_DEVICE_SY 316
#define SCALE_UNITS_SY 317
#define LENGTH_SY 318
#define EXPONENT_SY 319
#define SCHEMA_LOCATION_SY 320
#define XMLNS_SY 321
#define XMLNS_XSI_SY 322
#define CLOSE_OPTION_SY 323
#define OPEN_INTERFACE_SY 324
#define OPEN_COMMAND_SY 325
#define OPEN_NOTIFICATION_SY 326
#define OPEN_REQUEST_SY 327
#define OPEN_FAULT_MSG_SY 328
#define COMPONENT_KEY_SY 329
#define SPA_U_HUB_SY 330
#define SPA_U_PORT_SY 331
#define EXTENDS_SY 332
#define CLOSE_COMMAND_SY 333
#define CLOSE_NOTIFICATION_SY 334
#define CLOSE_REQUEST_SY 335
#define CLOSE_FAULT_MSG_SY 336
#define OPEN_QUALIFIER_SY 337
#define CLOSE_QUALIFIER_SY 338
#define CLOSE_APP_SY 339
#define CLOSE_DEVICE_SY 340
#define CLOSE_INTERFACE_SY 341
#define MEMORY_MINIMUM_SY 342
#define OPERATING_SYSTEM_SY 343
#define PATH_FOR_ASSEMBLY_SY 344
#define PATH_ON_SPACECRAFT_SY 345
#define X_SY 346
#define Y_SY 347
#define Z_SY 348
#define AXIS_SY 349
#define ANGLE_SY 350
#define OPEN_LOCATION_SY 351
#define OPEN_ORIENTATION_SY 352
#define CLOSE_XML_SY 353
#define ENCODING_SY 354
#define STANDALONE_SY 355
#define CLOSE_VARIABLE_REF_SY 356
#define CLOSE_COEFF_SY 357
#define R_LOW_SY 358
#define R_HIGH_SY 359
#define Y_LOW_SY 360
#define Y_HIGH_SY 361
#define INVALID_VALUE_SY 362
#define BAD_TERMINAL_SY 363




/* Copy the first part of user declarations.  */
#line 1 "xTEDS.y"

/*xTEDS 1.0 msg_def parser*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "xTEDSParser.h"

int yylex();

int yydebug=0;
void yyerror(char *s);


/* Enabling traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

#if ! defined (YYSTYPE) && ! defined (YYSTYPE_IS_DECLARED)
#line 38 "xTEDS.y"
typedef union YYSTYPE {
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
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 340 "xTEDS.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 352 "xTEDS.tab.c"

#if ! defined (yyoverflow) || YYERROR_VERBOSE

# ifndef YYFREE
#  define YYFREE free
# endif
# ifndef YYMALLOC
#  define YYMALLOC malloc
# endif

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   define YYSTACK_ALLOC alloca
#  endif
# else
#  if defined (alloca) || defined (_ALLOCA_H)
#   define YYSTACK_ALLOC alloca
#  else
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's `empty if-body' warning. */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
# else
#  if defined (__STDC__) || defined (__cplusplus)
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   define YYSIZE_T size_t
#  endif
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
# endif
#endif /* ! defined (yyoverflow) || YYERROR_VERBOSE */


#if (! defined (yyoverflow) \
     && (! defined (__cplusplus) \
	 || (defined (YYSTYPE_IS_TRIVIAL) && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  short int yyss;
  YYSTYPE yyvs;
  };

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (short int) + sizeof (YYSTYPE))			\
      + YYSTACK_GAP_MAXIMUM)

/* Copy COUNT objects from FROM to TO.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined (__GNUC__) && 1 < __GNUC__
#   define YYCOPY(To, From, Count) \
      __builtin_memcpy (To, From, (Count) * sizeof (*(From)))
#  else
#   define YYCOPY(To, From, Count)		\
      do					\
	{					\
	  register YYSIZE_T yyi;		\
	  for (yyi = 0; yyi < (Count); yyi++)	\
	    (To)[yyi] = (From)[yyi];		\
	}					\
      while (0)
#  endif
# endif

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack)					\
    do									\
      {									\
	YYSIZE_T yynewbytes;						\
	YYCOPY (&yyptr->Stack, Stack, yysize);				\
	Stack = &yyptr->Stack;						\
	yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
	yyptr += yynewbytes / sizeof (*yyptr);				\
      }									\
    while (0)

#endif

#if defined (__STDC__) || defined (__cplusplus)
   typedef signed char yysigned_char;
#else
   typedef short int yysigned_char;
#endif

/* YYFINAL -- State number of the termination state. */
#define YYFINAL  4
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   428

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  109
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  84
/* YYNRULES -- Number of rules. */
#define YYNRULES  215
/* YYNRULES -- Number of states. */
#define YYNSTATES  478

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   363

#define YYTRANSLATE(YYX) 						\
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[YYLEX] -- Bison symbol number corresponding to YYLEX.  */
static const unsigned char yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53,    54,
      55,    56,    57,    58,    59,    60,    61,    62,    63,    64,
      65,    66,    67,    68,    69,    70,    71,    72,    73,    74,
      75,    76,    77,    78,    79,    80,    81,    82,    83,    84,
      85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
      95,    96,    97,    98,    99,   100,   101,   102,   103,   104,
     105,   106,   107,   108
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned short int yyprhs[] =
{
       0,     0,     3,    12,    16,    17,    21,    22,    28,    32,
      35,    36,    40,    44,    48,    52,    56,    60,    62,    64,
      68,    75,    78,    79,    83,    87,    91,    95,    99,   103,
     107,   109,   113,   117,   121,   125,   129,   133,   141,   144,
     145,   147,   149,   151,   154,   155,   157,   161,   165,   169,
     173,   177,   181,   185,   189,   193,   197,   201,   205,   209,
     213,   217,   221,   225,   229,   235,   238,   239,   243,   247,
     251,   255,   259,   265,   268,   269,   273,   277,   281,   284,
     285,   291,   295,   298,   299,   303,   307,   311,   314,   315,
     322,   324,   328,   332,   335,   336,   339,   340,   342,   344,
     346,   350,   354,   358,   362,   365,   366,   368,   370,   372,
     380,   382,   390,   394,   395,   398,   399,   403,   407,   411,
     413,   420,   423,   424,   432,   435,   436,   440,   444,   448,
     452,   456,   458,   465,   468,   469,   477,   481,   484,   485,
     489,   493,   497,   499,   502,   503,   505,   507,   513,   516,
     519,   522,   523,   527,   531,   535,   539,   543,   547,   551,
     555,   559,   563,   567,   571,   575,   579,   583,   587,   591,
     595,   599,   603,   606,   608,   611,   612,   614,   616,   618,
     620,   623,   624,   630,   638,   643,   647,   650,   651,   655,
     659,   662,   663,   667,   673,   676,   677,   681,   685,   689,
     693,   698,   702,   705,   706,   710,   714,   717,   718,   722,
     728,   732,   735,   736,   740,   744
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     110,     0,    -1,     6,    30,     3,    49,   111,   112,    98,
     113,    -1,    99,     3,    49,    -1,    -1,   100,     3,    49,
      -1,    -1,   114,   117,   137,     7,     4,    -1,     8,   115,
       4,    -1,   115,   116,    -1,    -1,    23,     3,    49,    -1,
      30,     3,    49,    -1,    28,     3,    49,    -1,    66,     3,
      49,    -1,    65,     3,    49,    -1,    67,     3,    49,    -1,
     118,    -1,   122,    -1,     9,   119,     5,    -1,     9,   119,
       4,   133,    84,     4,    -1,   119,   121,    -1,    -1,    23,
       3,    49,    -1,    24,     3,    49,    -1,    25,     3,    49,
      -1,    27,     3,    49,    -1,    28,     3,    49,    -1,    29,
       3,    49,    -1,    74,     3,    49,    -1,   120,    -1,    30,
       3,    49,    -1,    87,     3,    49,    -1,    88,     3,    49,
      -1,    89,     3,    49,    -1,    90,     3,    49,    -1,    61,
     125,     5,    -1,    61,   125,     4,   123,    85,     4,   133,
      -1,   123,   124,    -1,    -1,   134,    -1,   127,    -1,   130,
      -1,   125,   126,    -1,    -1,   120,    -1,    31,     3,    49,
      -1,    32,     3,    49,    -1,    33,     3,    49,    -1,    34,
       3,    49,    -1,    35,     3,    49,    -1,    36,     3,    49,
      -1,    37,     3,    49,    -1,    38,     3,    49,    -1,    39,
       3,    49,    -1,    40,     3,    49,    -1,    41,     3,    49,
      -1,    42,     3,    49,    -1,    43,     3,    49,    -1,    44,
       3,    49,    -1,    75,     3,    49,    -1,    76,     3,    49,
      -1,    30,     3,    49,    -1,    96,   128,     5,    -1,    96,
     128,     4,    54,     4,    -1,   128,   129,    -1,    -1,    91,
       3,    49,    -1,    92,     3,    49,    -1,    93,     3,    49,
      -1,    59,     3,    49,    -1,    97,   131,     5,    -1,    97,
     131,     4,    26,     4,    -1,   131,   132,    -1,    -1,    94,
       3,    49,    -1,    95,     3,    49,    -1,    59,     3,    49,
      -1,   133,   134,    -1,    -1,    82,   135,     4,    83,     4,
      -1,    82,   135,     5,    -1,   135,   136,    -1,    -1,    23,
       3,    49,    -1,    45,     3,    49,    -1,    59,     3,    49,
      -1,   137,   138,    -1,    -1,   139,   141,   164,   144,    86,
       4,    -1,   139,    -1,    69,   140,     4,    -1,    69,   140,
       5,    -1,   140,   143,    -1,    -1,   141,   142,    -1,    -1,
     134,    -1,   127,    -1,   130,    -1,    23,     3,    49,    -1,
      77,     3,    49,    -1,    25,     3,    49,    -1,    28,     3,
      49,    -1,   144,   145,    -1,    -1,   158,    -1,   152,    -1,
     146,    -1,    72,     4,   159,   153,   147,    80,     4,    -1,
     148,    -1,    73,   149,     4,   151,   175,    81,     4,    -1,
      73,   149,     5,    -1,    -1,   149,   150,    -1,    -1,    23,
       3,    49,    -1,    25,     3,    49,    -1,    28,     3,    49,
      -1,   133,    -1,    71,     4,   153,   147,    79,     4,    -1,
     153,   154,    -1,    -1,    18,   155,     4,   157,   175,    19,
       4,    -1,   155,   156,    -1,    -1,    23,     3,    49,    -1,
      25,     3,    49,    -1,    47,     3,    49,    -1,    28,     3,
      49,    -1,    48,     3,    49,    -1,   133,    -1,    70,     4,
     159,   147,    78,     4,    -1,   159,   160,    -1,    -1,    21,
     161,     4,   163,   175,    22,     4,    -1,    21,   161,     5,
      -1,   161,   162,    -1,    -1,    23,     3,    49,    -1,    25,
       3,    49,    -1,    28,     3,    49,    -1,   133,    -1,   164,
     165,    -1,    -1,   166,    -1,   167,    -1,   168,     4,   171,
      11,     4,    -1,   168,     5,    -1,    10,   169,    -1,   169,
     170,    -1,    -1,    23,     3,    49,    -1,    24,     3,    49,
      -1,    55,     3,    49,    -1,    27,     3,    49,    -1,    25,
       3,    49,    -1,    28,     3,    49,    -1,    57,     3,    49,
      -1,    53,     3,    49,    -1,    63,     3,    49,    -1,    60,
       3,    49,    -1,    52,     3,    49,    -1,    59,     3,    49,
      -1,    56,     3,    49,    -1,    58,     3,    49,    -1,    62,
       3,    49,    -1,   103,     3,    49,    -1,   104,     3,    49,
      -1,   105,     3,    49,    -1,   106,     3,    49,    -1,   107,
       3,    49,    -1,   172,   173,    -1,   133,    -1,   173,   174,
      -1,    -1,   177,    -1,   185,    -1,   127,    -1,   130,    -1,
     175,   176,    -1,    -1,    20,    23,     3,    49,     5,    -1,
      20,    23,     3,    49,     4,   101,     4,    -1,   178,   181,
      13,     4,    -1,    12,   179,     4,    -1,   179,   180,    -1,
      -1,    23,     3,    49,    -1,    28,     3,    49,    -1,   181,
     182,    -1,    -1,    14,   183,     5,    -1,    14,   183,     4,
      68,     4,    -1,   183,   184,    -1,    -1,    23,     3,    49,
      -1,    45,     3,    49,    -1,    28,     3,    49,    -1,    46,
       3,    49,    -1,   186,   189,    16,     4,    -1,    15,   187,
       4,    -1,   187,   188,    -1,    -1,    23,     3,    49,    -1,
      28,     3,    49,    -1,   189,   190,    -1,    -1,    17,   191,
       5,    -1,    17,   191,     4,   102,     4,    -1,    17,   191,
       4,    -1,   191,   192,    -1,    -1,    64,     3,    49,    -1,
      45,     3,    49,    -1,    28,     3,    49,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    92,    92,   106,   116,   121,   125,   133,   139,   145,
     150,   157,   164,   171,   178,   185,   192,   206,   210,   216,
     220,   229,   234,   239,   246,   253,   260,   268,   275,   282,
     291,   295,   302,   309,   316,   323,   337,   341,   351,   356,
     361,   367,   372,   379,   384,   389,   393,   400,   407,   414,
     421,   428,   435,   442,   449,   456,   463,   470,   477,   484,
     491,   498,   505,   519,   523,   529,   534,   539,   545,   551,
     557,   570,   574,   580,   585,   590,   596,   602,   614,   619,
     624,   628,   634,   639,   644,   651,   658,   672,   677,   682,
     686,   692,   696,   702,   707,   714,   720,   725,   729,   735,
     743,   750,   757,   764,   778,   783,   788,   795,   802,   811,
     826,   832,   838,   843,   848,   853,   858,   865,   872,   881,
     895,   904,   909,   914,   922,   927,   932,   939,   946,   953,
     960,   969,   983,   992,   997,  1002,  1008,  1014,  1019,  1024,
    1031,  1038,  1047,  1061,  1066,  1071,  1075,  1081,  1087,  1090,
    1096,  1101,  1106,  1113,  1120,  1127,  1135,  1142,  1149,  1156,
    1163,  1170,  1177,  1184,  1191,  1198,  1205,  1212,  1219,  1226,
    1233,  1241,  1250,  1256,  1266,  1271,  1276,  1283,  1290,  1297,
    1311,  1316,  1321,  1325,  1336,  1345,  1351,  1356,  1361,  1368,
    1377,  1382,  1387,  1391,  1397,  1402,  1407,  1414,  1421,  1428,
    1442,  1451,  1457,  1462,  1467,  1474,  1483,  1488,  1493,  1497,
    1501,  1507,  1512,  1517,  1524,  1531
};
#endif

#if YYDEBUG || YYERROR_VERBOSE
/* YYTNME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals. */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "EQUAL_SY", "CLOSE_SY", "SLASHCLOSE_SY",
  "OPEN_XML_SY", "CLOSE_xTEDS_SY", "OPEN_xTEDS_SY", "OPEN_APP_SY",
  "OPEN_VAR_SY", "CLOSE_VAR_SY", "OPEN_DRANGE_SY", "CLOSE_DRANGE_SY",
  "OPEN_OPTION_SY", "OPEN_CURVE_SY", "CLOSE_CURVE_SY", "OPEN_COEFF_SY",
  "OPEN_DATA_MSG_SY", "CLOSE_DATA_MSG_SY", "OPEN_VARIABLE_REF_SY",
  "OPEN_COMMAND_MSG_SY", "CLOSE_COMMAND_MSG_SY", "NAME_SY", "KIND_SY",
  "ID_SY", "CLOSE_ORIENTATION_SY", "QUALIFIER_SY", "DESCRIPTION_SY",
  "MANUFACTURER_ID_SY", "VERSION_SY", "MODEL_ID_SY", "VERSION_LETTER_SY",
  "SERIAL_NUMBER_SY", "CALIBRATION_DATE_SY", "SENSITIVITY_AT_REF_SY",
  "REF_FREQ_SY", "REF_TEMP_SY", "MEASUREMENT_RANGE_SY",
  "ELECTRICAL_OUTPUT_SY", "QUALITY_FACTOR_SY", "TEMP_COEFF_SY",
  "DIRECTION_XYZ_SY", "CAL_DUE_DATE_SY", "POWER_REQS_SY", "VALUE_SY",
  "ALARM_SY", "MSG_ARRIVAL_SY", "MSG_RATE_SY", "STRING", "FLOAT", "INT",
  "PRECISION_SY", "RANGE_MAX_SY", "CLOSE_LOCATION_SY", "FORMAT_SY",
  "ACCURACY_SY", "RANGE_MIN_SY", "SCALE_FACTOR_SY", "UNITS_SY",
  "DEFAULT_VALUE_SY", "OPEN_DEVICE_SY", "SCALE_UNITS_SY", "LENGTH_SY",
  "EXPONENT_SY", "SCHEMA_LOCATION_SY", "XMLNS_SY", "XMLNS_XSI_SY",
  "CLOSE_OPTION_SY", "OPEN_INTERFACE_SY", "OPEN_COMMAND_SY",
  "OPEN_NOTIFICATION_SY", "OPEN_REQUEST_SY", "OPEN_FAULT_MSG_SY",
  "COMPONENT_KEY_SY", "SPA_U_HUB_SY", "SPA_U_PORT_SY", "EXTENDS_SY",
  "CLOSE_COMMAND_SY", "CLOSE_NOTIFICATION_SY", "CLOSE_REQUEST_SY",
  "CLOSE_FAULT_MSG_SY", "OPEN_QUALIFIER_SY", "CLOSE_QUALIFIER_SY",
  "CLOSE_APP_SY", "CLOSE_DEVICE_SY", "CLOSE_INTERFACE_SY",
  "MEMORY_MINIMUM_SY", "OPERATING_SYSTEM_SY", "PATH_FOR_ASSEMBLY_SY",
  "PATH_ON_SPACECRAFT_SY", "X_SY", "Y_SY", "Z_SY", "AXIS_SY", "ANGLE_SY",
  "OPEN_LOCATION_SY", "OPEN_ORIENTATION_SY", "CLOSE_XML_SY", "ENCODING_SY",
  "STANDALONE_SY", "CLOSE_VARIABLE_REF_SY", "CLOSE_COEFF_SY", "R_LOW_SY",
  "R_HIGH_SY", "Y_LOW_SY", "Y_HIGH_SY", "INVALID_VALUE_SY",
  "BAD_TERMINAL_SY", "$accept", "XTEDS_DOCUMENT", "ENCODING", "STANDALONE",
  "xTEDS", "OPEN_xTEDS", "xTEDS_ATTRIBUTES", "xTEDS_ATTRIBUTE",
  "APP_DEVICE", "APP_SECTION", "APP_ATTRIBUTES",
  "COMMON_APP_DEVICE_ATTRIBUTE", "APP_ATTRIBUTE", "DEVICE_SECTION",
  "DEVICE_SUBELEMENTS", "DEVICE_SUBELEMENT", "DEVICE_ATTRIBUTES",
  "DEVICE_ATTRIBUTE", "LOCATION_SECTION", "LOCATION_ATTRIBUTES",
  "LOCATION_ATTRIBUTE", "ORIENTATION_SECTION", "ORIENTATION_ATTRIBUTES",
  "ORIENTATION_ATTRIBUTE", "QUALIFIERS_SECTION", "QUALIFIER",
  "QUALIFIERS_ATTRIBUTES", "QUALIFIERS_ATTRIBUTE", "INTERFACES",
  "INTERFACE", "INTERFACE_HEAD", "INTERFACE_ATTRIBUTES",
  "INTERFACE_SUBELEMENTS", "INTERFACE_SUBELEMENT", "INTERFACE_ATTRIBUTE",
  "MESSAGE_SECTION", "MESSAGES", "REQUEST_SECTION", "FAULT_MSG_SECTION",
  "FAULT_MSG", "FAULT_MSG_ATTRIBUTES", "FAULT_MSG_ATTRIBUTE",
  "FAULT_MSG_QUALIFIERS", "NOTIFICATION_SECTION", "DATA_MSG_SECTION",
  "DATA_MSG", "DATA_MSG_ATTRIBUTES", "DATA_MSG_ATTRIBUTE",
  "DATA_MSG_QUALIFIERS", "COMMAND_SECTION", "COMMAND_MSG_SECTION",
  "COMMAND_MSG", "COMMAND_MSG_ATTRIBUTES", "COMMAND_MSG_ATTRIBUTE",
  "COMMAND_MSG_QUALIFIERS", "VAR_SECTION", "VARIABLE",
  "VAR_WITH_SUBELEMENTS", "VAR_NO_SUBELEMENTS", "VAR_HEAD",
  "VAR_ATTRIBUTES", "VAR_ATTRIBUTE", "VAR_ELEMENTS", "VAR_QUALIFIERS",
  "VAR_SUBELEMENTS", "VAR_SUBELEMENT", "VARIABLE_REFS", "VARIABLE_REF",
  "DRANGE", "DRANGE_HEAD", "DRANGE_ATTRIBUTES", "DRANGE_ATTRIBUTE",
  "DRANGE_OPTIONS", "DRANGE_OPTION", "OPTION_ATTRIBUTES",
  "OPTION_ATTRIBUTE", "CURVE", "CURVE_HEAD", "CURVE_ATTRIBUTES",
  "CURVE_ATTRIBUTE", "CURVE_COEFFS", "CURVE_COEFF", "COEFF_ATTRIBUTES",
  "COEFF_ATTRIBUTE", 0
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[YYLEX-NUM] -- Internal token number corresponding to
   token YYLEX-NUM.  */
static const unsigned short int yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308,   309,   310,   311,   312,   313,   314,
     315,   316,   317,   318,   319,   320,   321,   322,   323,   324,
     325,   326,   327,   328,   329,   330,   331,   332,   333,   334,
     335,   336,   337,   338,   339,   340,   341,   342,   343,   344,
     345,   346,   347,   348,   349,   350,   351,   352,   353,   354,
     355,   356,   357,   358,   359,   360,   361,   362,   363
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   109,   110,   111,   111,   112,   112,   113,   114,   115,
     115,   116,   116,   116,   116,   116,   116,   117,   117,   118,
     118,   119,   119,   120,   120,   120,   120,   120,   120,   120,
     121,   121,   121,   121,   121,   121,   122,   122,   123,   123,
     124,   124,   124,   125,   125,   126,   126,   126,   126,   126,
     126,   126,   126,   126,   126,   126,   126,   126,   126,   126,
     126,   126,   126,   127,   127,   128,   128,   129,   129,   129,
     129,   130,   130,   131,   131,   132,   132,   132,   133,   133,
     134,   134,   135,   135,   136,   136,   136,   137,   137,   138,
     138,   139,   139,   140,   140,   141,   141,   142,   142,   142,
     143,   143,   143,   143,   144,   144,   145,   145,   145,   146,
     147,   148,   148,   148,   149,   149,   150,   150,   150,   151,
     152,   153,   153,   154,   155,   155,   156,   156,   156,   156,
     156,   157,   158,   159,   159,   160,   160,   161,   161,   162,
     162,   162,   163,   164,   164,   165,   165,   166,   167,   168,
     169,   169,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   170,   170,   170,   170,   170,   170,   170,   170,
     170,   170,   171,   172,   173,   173,   174,   174,   174,   174,
     175,   175,   176,   176,   177,   178,   179,   179,   180,   180,
     181,   181,   182,   182,   183,   183,   184,   184,   184,   184,
     185,   186,   187,   187,   188,   188,   189,   189,   190,   190,
     190,   191,   191,   192,   192,   192
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     8,     3,     0,     3,     0,     5,     3,     2,
       0,     3,     3,     3,     3,     3,     3,     1,     1,     3,
       6,     2,     0,     3,     3,     3,     3,     3,     3,     3,
       1,     3,     3,     3,     3,     3,     3,     7,     2,     0,
       1,     1,     1,     2,     0,     1,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     5,     2,     0,     3,     3,     3,
       3,     3,     5,     2,     0,     3,     3,     3,     2,     0,
       5,     3,     2,     0,     3,     3,     3,     2,     0,     6,
       1,     3,     3,     2,     0,     2,     0,     1,     1,     1,
       3,     3,     3,     3,     2,     0,     1,     1,     1,     7,
       1,     7,     3,     0,     2,     0,     3,     3,     3,     1,
       6,     2,     0,     7,     2,     0,     3,     3,     3,     3,
       3,     1,     6,     2,     0,     7,     3,     2,     0,     3,
       3,     3,     1,     2,     0,     1,     1,     5,     2,     2,
       2,     0,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     2,     1,     2,     0,     1,     1,     1,     1,
       2,     0,     5,     7,     4,     3,     2,     0,     3,     3,
       2,     0,     3,     5,     2,     0,     3,     3,     3,     3,
       4,     3,     2,     0,     3,     3,     2,     0,     3,     5,
       3,     2,     0,     3,     3,     3
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     0,     0,     0,     1,     0,     4,     0,     6,     0,
       0,     0,     3,     0,     0,     5,    10,     2,     0,     0,
      22,    44,    88,    17,    18,     8,     0,     0,     0,     0,
       0,     0,     9,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    79,    19,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,    30,    21,    39,    36,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,    45,    43,     0,
      94,    87,    96,    11,    13,    12,    15,    14,    16,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       7,     0,   144,    83,     0,    78,    23,    24,    25,    26,
      27,    28,    31,    29,    32,    33,    34,    35,     0,    66,
      74,    38,    41,    42,    40,    62,    46,    47,    48,    49,
      50,    51,    52,    53,    54,    55,    56,    57,    58,    59,
      60,    61,    91,    92,     0,     0,     0,     0,    93,    98,
      99,    97,    95,   105,     0,    20,    79,     0,     0,     0,
       0,     0,     0,   151,     0,   143,   145,   146,     0,     0,
      81,     0,     0,     0,    82,    37,     0,    63,     0,     0,
       0,     0,    65,     0,    71,     0,     0,     0,    73,   100,
     102,   103,   101,   149,     0,     0,     0,     0,   104,   108,
     107,   106,    79,   148,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,   150,   134,   122,
     134,    89,   173,     0,   175,    80,    84,    85,    86,    64,
      70,    67,    68,    69,    72,    77,    75,    76,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,   113,   113,
     122,     0,   172,   152,   153,   156,   155,   157,   162,   159,
     154,   164,   158,   165,   163,   161,   166,   160,   167,   168,
     169,   170,   171,   138,   115,     0,   110,   133,   125,     0,
     121,   113,   147,   187,   203,   178,   179,   174,   176,   191,
     177,   207,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    79,   136,     0,     0,     0,   137,    79,   112,
       0,     0,     0,   114,   132,    79,     0,     0,     0,     0,
       0,   124,   120,     0,   185,     0,     0,   186,   201,     0,
       0,   202,     0,   195,   190,     0,   212,   206,   142,   181,
       0,     0,     0,   119,   181,     0,     0,     0,   131,   181,
       0,     0,     0,     0,     0,   109,     0,     0,     0,     0,
     184,     0,   200,     0,     0,   139,   140,   141,     0,   116,
     117,   118,     0,   126,   127,   129,   128,   130,   188,   189,
     204,   205,     0,   192,     0,     0,     0,     0,   194,   210,
     208,     0,     0,     0,   211,     0,     0,   180,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     135,   111,   123,   193,   196,   198,   197,   199,   209,   215,
     214,   213,     0,     0,     0,   182,     0,   183
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     2,     8,    11,    17,    18,    19,    32,    22,    23,
      33,    56,    57,    24,   102,   141,    34,    78,   142,   177,
     202,   143,   178,   208,    89,   125,   174,   194,    35,    81,
      82,   121,   122,   172,   168,   184,   218,   219,   325,   326,
     343,   363,   394,   220,   299,   330,   345,   371,   399,   221,
     298,   327,   342,   357,   389,   173,   185,   186,   187,   188,
     213,   257,   263,   264,   302,   337,   414,   447,   338,   339,
     348,   377,   350,   384,   411,   438,   340,   341,   349,   381,
     351,   387,   413,   444
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -383
static const short int yypact[] =
{
       8,    -6,    40,    42,  -383,     4,   -44,    58,   -29,    28,
      76,   -17,  -383,    38,   110,  -383,  -383,  -383,    13,    19,
    -383,  -383,  -383,  -383,  -383,  -383,   154,   155,   156,   157,
     158,   160,  -383,     2,    97,     6,   118,   119,   121,   129,
     136,   143,  -383,  -383,   185,   193,   194,   198,   199,   200,
     201,   202,   203,   204,   205,   207,  -383,  -383,  -383,  -383,
     209,   213,   214,   216,   217,   218,   219,   220,   221,   222,
     223,   224,   225,   226,   227,   228,   229,  -383,  -383,   189,
    -383,  -383,     9,  -383,  -383,  -383,  -383,  -383,  -383,   -30,
     184,   187,   188,   191,   192,   195,   196,   197,   206,   208,
     210,   211,    69,   212,   215,   230,   231,   232,   233,   234,
     235,   236,   237,   238,   239,   240,   241,   242,   243,   244,
    -383,    16,   -46,  -383,   245,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,   246,  -383,
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,  -383,   248,   249,   250,   251,  -383,  -383,
    -383,  -383,  -383,   252,   139,  -383,  -383,     5,     0,   247,
     253,   254,   255,  -383,    33,  -383,  -383,  -383,   104,   159,
    -383,   260,   262,   263,  -383,   153,   180,  -383,   264,   265,
     266,   267,  -383,   268,  -383,   269,   270,   271,  -383,  -383,
    -383,  -383,  -383,    10,   272,   273,   274,   291,  -383,  -383,
    -383,  -383,  -383,  -383,   293,   256,   257,   258,   294,   259,
     261,   275,   276,   295,   277,   278,   279,   297,   298,   306,
     308,   309,   310,   311,   312,   313,   314,   315,   316,   317,
     318,   319,   320,   326,   327,   328,   329,  -383,  -383,  -383,
    -383,  -383,   153,   322,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,   285,   286,
     287,   288,   289,   290,   292,   296,   299,   300,   301,   302,
     303,   304,   305,   307,   321,   323,   324,   325,   -13,   -16,
     334,   336,     3,  -383,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,  -383,  -383,   161,  -383,  -383,  -383,   164,
    -383,   -16,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,   186,   190,   338,   152,   339,   167,    84,   151,
     134,    94,  -383,  -383,   341,   343,   344,  -383,  -383,  -383,
     354,   355,   356,  -383,  -383,  -383,   357,   358,   359,   360,
     361,  -383,  -383,   362,  -383,   364,   365,  -383,  -383,   366,
     368,  -383,   371,  -383,  -383,   372,  -383,  -383,   153,  -383,
     330,   331,   332,   153,  -383,   333,   335,   337,   153,  -383,
     340,   342,   345,   346,   347,  -383,   348,   349,   350,   351,
    -383,   141,  -383,    78,    36,  -383,  -383,  -383,    -1,  -383,
    -383,  -383,   130,  -383,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,   170,  -383,   374,   375,   380,   382,  -383,   146,
    -383,   384,   385,   387,  -383,   369,   389,  -383,   397,   398,
     399,   363,   367,   370,   373,   400,   376,   377,   378,   402,
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,   379,   148,   174,  -383,   403,  -383
};

/* YYPGOTO[NTERM-NUM].  */
static const short int yypgoto[] =
{
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,   381,  -383,  -383,  -383,  -383,  -383,  -383,  -121,  -383,
    -383,  -119,  -383,  -383,  -176,   -74,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -288,  -383,
    -383,  -383,  -383,  -383,   -42,  -383,  -383,  -383,  -383,  -383,
      -4,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,  -383,  -383,  -383,  -382,  -383,  -383,  -383,
    -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,  -383,
    -383,  -383,  -383,  -383
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -91
static const short int yytable[] =
{
     195,   169,   328,   170,   203,   204,    42,    43,   323,   196,
     197,   329,   418,    79,     1,   333,   -90,   422,   334,   445,
     162,   163,    20,    25,     3,    44,    45,    46,   144,    47,
      48,    49,    50,   237,   238,   239,   123,   240,   241,   164,
       4,   165,    26,   347,   166,     5,   262,    27,   171,    28,
     139,   140,   123,     6,   124,     7,   445,   324,   446,   205,
     324,     9,   242,   243,   198,   244,   245,   246,   247,   248,
     249,    10,   250,   251,    21,    80,    51,    12,   -90,    13,
     448,    14,   439,   440,    29,    30,    31,    15,   374,    52,
      53,    54,    55,   167,   206,   207,   199,   200,   201,   139,
     140,    58,    59,   214,   215,   216,   441,   375,   222,   223,
     385,   386,   376,   252,   253,   254,   255,   256,    16,   217,
      44,    45,    46,   442,    47,    48,    49,    60,    61,    62,
      63,    64,    65,    66,    67,    68,    69,    70,    71,    72,
      73,    74,   443,   189,   190,   432,   433,   382,   383,   449,
     445,   123,   474,   475,   138,   378,   365,    36,    37,    38,
      39,    40,   191,    41,   434,   139,   140,    83,    84,   435,
      85,    51,    75,    76,   379,   366,   388,   367,    86,   380,
     368,   335,   393,   336,   192,    87,   436,   437,    90,   398,
     352,   353,    88,   120,   358,   359,    91,    92,   193,   369,
     370,    93,    94,    95,    96,    97,    98,    99,   100,   354,
     101,   355,   103,   360,   356,   361,   104,   105,   362,   106,
     107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
     117,   118,   119,   126,   228,   123,   127,   128,   450,   344,
     129,   130,   224,   346,   131,   132,   133,   373,   455,   175,
     176,   179,   180,   181,   182,   134,   300,   135,   331,   136,
     137,   145,   183,   225,   146,   226,   227,   229,   230,   231,
     232,     0,   234,   235,   236,   476,   258,   259,   260,   147,
     148,   149,   150,   151,   152,   153,   154,   155,   156,   157,
     158,   159,   160,   161,   233,   261,   209,   265,   269,   274,
     278,   279,   210,   211,   212,   266,   267,   268,   270,   280,
     271,   281,   282,   283,   284,   285,   286,   287,   288,   289,
     290,   291,   292,   293,   272,   273,   275,   276,   277,   294,
     295,   296,   297,   301,   303,   304,   305,   306,   307,   308,
     332,   309,   364,   372,   390,   310,   391,   392,   311,   312,
     313,   314,   315,   316,   317,   323,   318,   395,   396,   397,
     400,   401,   402,   403,   404,     0,   405,   406,   407,   408,
     319,   409,   320,   321,   322,   410,   412,   451,   452,   415,
     416,   417,   419,   453,   420,   454,   421,   456,   457,   423,
     458,   424,   459,   460,   425,   426,   427,   428,   429,   430,
     431,   461,   462,   463,   468,   472,     0,   477,     0,     0,
       0,     0,   464,     0,     0,    77,   465,     0,     0,   466,
       0,     0,   467,     0,     0,   469,   470,   471,   473
};

static const short int yycheck[] =
{
     176,   122,    18,   122,     4,     5,     4,     5,    21,     4,
       5,   299,   394,     7,     6,    12,     7,   399,    15,    20,
       4,     5,     9,     4,    30,    23,    24,    25,   102,    27,
      28,    29,    30,    23,    24,    25,    82,    27,    28,    23,
       0,    25,    23,   331,    28,     3,   222,    28,   122,    30,
      96,    97,    82,    49,    84,    99,    20,    73,    22,    59,
      73,     3,    52,    53,    59,    55,    56,    57,    58,    59,
      60,   100,    62,    63,    61,    69,    74,    49,    69,     3,
      81,    98,     4,     5,    65,    66,    67,    49,     4,    87,
      88,    89,    90,    77,    94,    95,    91,    92,    93,    96,
      97,     4,     5,    70,    71,    72,    28,    23,     4,     5,
      16,    17,    28,   103,   104,   105,   106,   107,     8,    86,
      23,    24,    25,    45,    27,    28,    29,    30,    31,    32,
      33,    34,    35,    36,    37,    38,    39,    40,    41,    42,
      43,    44,    64,     4,     5,     4,     5,    13,    14,    19,
      20,    82,     4,     5,    85,     4,     4,     3,     3,     3,
       3,     3,    23,     3,    23,    96,    97,    49,    49,    28,
      49,    74,    75,    76,    23,    23,   352,    25,    49,    28,
      28,   302,   358,   302,    45,    49,    45,    46,     3,   365,
       4,     5,    49,     4,     4,     5,     3,     3,    59,    47,
      48,     3,     3,     3,     3,     3,     3,     3,     3,    23,
       3,    25,     3,    23,    28,    25,     3,     3,    28,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,    49,    54,    82,    49,    49,    68,    78,
      49,    49,    83,    79,    49,    49,    49,    80,   102,     4,
       4,     3,     3,     3,     3,    49,   260,    49,   300,    49,
      49,    49,    10,     3,    49,     3,     3,     3,     3,     3,
       3,    -1,     3,     3,     3,   101,     4,     4,     4,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    26,     4,    49,     4,     4,     4,
       3,     3,    49,    49,    49,    49,    49,    49,    49,     3,
      49,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,    49,    49,    49,    49,    49,     3,
       3,     3,     3,    11,    49,    49,    49,    49,    49,    49,
       4,    49,     4,     4,     3,    49,     3,     3,    49,    49,
      49,    49,    49,    49,    49,    21,    49,     3,     3,     3,
       3,     3,     3,     3,     3,    -1,     4,     3,     3,     3,
      49,     3,    49,    49,    49,     4,     4,     3,     3,    49,
      49,    49,    49,     3,    49,     3,    49,     3,     3,    49,
       3,    49,    23,     4,    49,    49,    49,    49,    49,    49,
      49,     4,     4,     4,     4,     3,    -1,     4,    -1,    -1,
      -1,    -1,    49,    -1,    -1,    34,    49,    -1,    -1,    49,
      -1,    -1,    49,    -1,    -1,    49,    49,    49,    49
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,     6,   110,    30,     0,     3,    49,    99,   111,     3,
     100,   112,    49,     3,    98,    49,     8,   113,   114,   115,
       9,    61,   117,   118,   122,     4,    23,    28,    30,    65,
      66,    67,   116,   119,   125,   137,     3,     3,     3,     3,
       3,     3,     4,     5,    23,    24,    25,    27,    28,    29,
      30,    74,    87,    88,    89,    90,   120,   121,     4,     5,
      30,    31,    32,    33,    34,    35,    36,    37,    38,    39,
      40,    41,    42,    43,    44,    75,    76,   120,   126,     7,
      69,   138,   139,    49,    49,    49,    49,    49,    49,   133,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,   123,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       4,   140,   141,    82,    84,   134,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    85,    96,
      97,   124,   127,   130,   134,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,     4,     5,    23,    25,    28,    77,   143,   127,
     130,   134,   142,   164,   135,     4,     4,   128,   131,     3,
       3,     3,     3,    10,   144,   165,   166,   167,   168,     4,
       5,    23,    45,    59,   136,   133,     4,     5,    59,    91,
      92,    93,   129,     4,     5,    59,    94,    95,   132,    49,
      49,    49,    49,   169,    70,    71,    72,    86,   145,   146,
     152,   158,     4,     5,    83,     3,     3,     3,    54,     3,
       3,     3,     3,    26,     3,     3,     3,    23,    24,    25,
      27,    28,    52,    53,    55,    56,    57,    58,    59,    60,
      62,    63,   103,   104,   105,   106,   107,   170,     4,     4,
       4,     4,   133,   171,   172,     4,    49,    49,    49,     4,
      49,    49,    49,    49,     4,    49,    49,    49,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     3,     3,     3,   159,   153,
     159,    11,   173,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    21,    73,   147,   148,   160,    18,   147,
     154,   153,     4,    12,    15,   127,   130,   174,   177,   178,
     185,   186,   161,   149,    78,   155,    79,   147,   179,   187,
     181,   189,     4,     5,    23,    25,    28,   162,     4,     5,
      23,    25,    28,   150,     4,     4,    23,    25,    28,    47,
      48,   156,     4,    80,     4,    23,    28,   180,     4,    23,
      28,   188,    13,    14,   182,    16,    17,   190,   133,   163,
       3,     3,     3,   133,   151,     3,     3,     3,   133,   157,
       3,     3,     3,     3,     3,     4,     3,     3,     3,     3,
       4,   183,     4,   191,   175,    49,    49,    49,   175,    49,
      49,    49,   175,    49,    49,    49,    49,    49,    49,    49,
      49,    49,     4,     5,    23,    28,    45,    46,   184,     4,
       5,    28,    45,    64,   192,    20,    22,   176,    81,    19,
      68,     3,     3,     3,     3,   102,     3,     3,     3,    23,
       4,     4,     4,     4,    49,    49,    49,    49,     4,    49,
      49,    49,     3,    49,     4,     5,   101,     4
};

#if ! defined (YYSIZE_T) && defined (__SIZE_TYPE__)
# define YYSIZE_T __SIZE_TYPE__
#endif
#if ! defined (YYSIZE_T) && defined (size_t)
# define YYSIZE_T size_t
#endif
#if ! defined (YYSIZE_T)
# if defined (__STDC__) || defined (__cplusplus)
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# endif
#endif
#if ! defined (YYSIZE_T)
# define YYSIZE_T unsigned int
#endif

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		(-2)
#define YYEOF		0

#define YYACCEPT	goto yyacceptlab
#define YYABORT		goto yyabortlab
#define YYERROR		goto yyerrorlab


/* Like YYERROR except do call yyerror.  This remains here temporarily
   to ease the transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */

#define YYFAIL		goto yyerrlab

#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)					\
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    {								\
      yychar = (Token);						\
      yylval = (Value);						\
      yytoken = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { 								\
      yyerror ("syntax error: cannot back up");\
      YYERROR;							\
    }								\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

/* YYLLOC_DEFAULT -- Compute the default location (before the actions
   are run).  */

#ifndef YYLLOC_DEFAULT
# define YYLLOC_DEFAULT(Current, Rhs, N)		\
   ((Current).first_line   = (Rhs)[1].first_line,	\
    (Current).first_column = (Rhs)[1].first_column,	\
    (Current).last_line    = (Rhs)[N].last_line,	\
    (Current).last_column  = (Rhs)[N].last_column)
#endif

/* YYLEX -- calling `yylex' with the right arguments.  */

#ifdef YYLEX_PARAM
# define YYLEX yylex (YYLEX_PARAM)
#else
# define YYLEX yylex ()
#endif

/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)			\
do {						\
  if (yydebug)					\
    YYFPRINTF Args;				\
} while (0)

# define YYDSYMPRINT(Args)			\
do {						\
  if (yydebug)					\
    yysymprint Args;				\
} while (0)

# define YYDSYMPRINTF(Title, Token, Value, Location)		\
do {								\
  if (yydebug)							\
    {								\
      YYFPRINTF (stderr, "%s ", Title);				\
      yysymprint (stderr, 					\
                  Token, Value);	\
      YYFPRINTF (stderr, "\n");					\
    }								\
} while (0)

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_stack_print (short int *bottom, short int *top)
#else
static void
yy_stack_print (bottom, top)
    short int *bottom;
    short int *top;
#endif
{
  YYFPRINTF (stderr, "Stack now");
  for (/* Nothing. */; bottom <= top; ++bottom)
    YYFPRINTF (stderr, " %d", *bottom);
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)				\
do {								\
  if (yydebug)							\
    yy_stack_print ((Bottom), (Top));				\
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yy_reduce_print (int yyrule)
#else
static void
yy_reduce_print (yyrule)
    int yyrule;
#endif
{
  int yyi;
  unsigned int yylno = yyrline[yyrule];
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %u), ",
             yyrule - 1, yylno);
  /* Print the symbols being reduced, and their result.  */
  for (yyi = yyprhs[yyrule]; 0 <= yyrhs[yyi]; yyi++)
    YYFPRINTF (stderr, "%s ", yytname [yyrhs[yyi]]);
  YYFPRINTF (stderr, "-> %s\n", yytname [yyr1[yyrule]]);
}

# define YY_REDUCE_PRINT(Rule)		\
do {					\
  if (yydebug)				\
    yy_reduce_print (Rule);		\
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YYDSYMPRINT(Args)
# define YYDSYMPRINTF(Title, Token, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef	YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   SIZE_MAX < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#if defined (YYMAXDEPTH) && YYMAXDEPTH == 0
# undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif



#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined (__GLIBC__) && defined (_STRING_H)
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
#   if defined (__STDC__) || defined (__cplusplus)
yystrlen (const char *yystr)
#   else
yystrlen (yystr)
     const char *yystr;
#   endif
{
  register const char *yys = yystr;

  while (*yys++ != '\0')
    continue;

  return yys - yystr - 1;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined (__GLIBC__) && defined (_STRING_H) && defined (_GNU_SOURCE)
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
#   if defined (__STDC__) || defined (__cplusplus)
yystpcpy (char *yydest, const char *yysrc)
#   else
yystpcpy (yydest, yysrc)
     char *yydest;
     const char *yysrc;
#   endif
{
  register char *yyd = yydest;
  register const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

#endif /* !YYERROR_VERBOSE */



#if YYDEBUG
/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yysymprint (FILE *yyoutput, int yytype, YYSTYPE *yyvaluep)
#else
static void
yysymprint (yyoutput, yytype, yyvaluep)
    FILE *yyoutput;
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  if (yytype < YYNTOKENS)
    {
      YYFPRINTF (yyoutput, "token %s (", yytname[yytype]);
# ifdef YYPRINT
      YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
    }
  else
    YYFPRINTF (yyoutput, "nterm %s (", yytname[yytype]);

  switch (yytype)
    {
      default:
        break;
    }
  YYFPRINTF (yyoutput, ")");
}

#endif /* ! YYDEBUG */
/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

#if defined (__STDC__) || defined (__cplusplus)
static void
yydestruct (int yytype, YYSTYPE *yyvaluep)
#else
static void
yydestruct (yytype, yyvaluep)
    int yytype;
    YYSTYPE *yyvaluep;
#endif
{
  /* Pacify ``unused variable'' warnings.  */
  (void) yyvaluep;

  switch (yytype)
    {

      default:
        break;
    }
}


/* Prevent warnings from -Wmissing-prototypes.  */

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM);
# else
int yyparse ();
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int yyparse (void);
#else
int yyparse ();
#endif
#endif /* ! YYPARSE_PARAM */



/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;

/* Number of syntax errors so far.  */
int yynerrs;



/*----------.
| yyparse.  |
`----------*/

#ifdef YYPARSE_PARAM
# if defined (__STDC__) || defined (__cplusplus)
int yyparse (void *YYPARSE_PARAM)
# else
int yyparse (YYPARSE_PARAM)
  void *YYPARSE_PARAM;
# endif
#else /* ! YYPARSE_PARAM */
#if defined (__STDC__) || defined (__cplusplus)
int
yyparse (void)
#else
int
yyparse ()

#endif
#endif
{
  
  register int yystate;
  register int yyn;
  int yyresult;
  /* Number of tokens to shift before error messages enabled.  */
  int yyerrstatus;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;

  /* Three stacks and their tools:
     `yyss': related to states,
     `yyvs': related to semantic values,
     `yyls': related to locations.

     Refer to the stacks thru separate pointers, to allow yyoverflow
     to reallocate them elsewhere.  */

  /* The state stack.  */
  short int yyssa[YYINITDEPTH];
  short int *yyss = yyssa;
  register short int *yyssp;

  /* The semantic value stack.  */
  YYSTYPE yyvsa[YYINITDEPTH];
  YYSTYPE *yyvs = yyvsa;
  register YYSTYPE *yyvsp;



#define YYPOPSTACK   (yyvsp--, yyssp--)

  YYSIZE_T yystacksize = YYINITDEPTH;

  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;


  /* When reducing, the number of symbols on the RHS of the reduced
     rule.  */
  int yylen;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss;
  yyvsp = yyvs;


  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed. so pushing a state here evens the stacks.
     */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
	/* Give user a chance to reallocate the stack. Use copies of
	   these so that the &'s don't force the real ones into
	   memory.  */
	YYSTYPE *yyvs1 = yyvs;
	short int *yyss1 = yyss;


	/* Each stack pointer address is followed by the size of the
	   data in use in that stack, in bytes.  This used to be a
	   conditional around just the two extra args, but that might
	   be undefined if yyoverflow is a macro.  */
	yyoverflow ("parser stack overflow",
		    &yyss1, yysize * sizeof (*yyssp),
		    &yyvs1, yysize * sizeof (*yyvsp),

		    &yystacksize);

	yyss = yyss1;
	yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyoverflowlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
	goto yyoverflowlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
	yystacksize = YYMAXDEPTH;

      {
	short int *yyss1 = yyss;
	union yyalloc *yyptr =
	  (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
	if (! yyptr)
	  goto yyoverflowlab;
	YYSTACK_RELOCATE (yyss);
	YYSTACK_RELOCATE (yyvs);

#  undef YYSTACK_RELOCATE
	if (yyss1 != yyssa)
	  YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;


      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
		  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
	YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYPACT_NINF)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = YYLEX;
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YYDSYMPRINTF ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yyn == 0 || yyn == YYTABLE_NINF)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */
  YYDPRINTF ((stderr, "Shifting token %s, ", yytname[yytoken]));

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;


  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  yystate = yyn;
  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     `$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 93 "xTEDS.y"
    {
				int compare = 1;
				if(strcmp("1.0",yyvsp[-4].str)!=0)
					compare = 0;
				free(yyvsp[-4].str);
				compare = yyvsp[-3].integer;
				if(compare == 1)
					result = yyvsp[0].xteds;
				else
					result = NULL;
			;}
    break;

  case 3:
#line 107 "xTEDS.y"
    {
				int compare = 1;
				
				if(strcmp("utf-8",yyvsp[0].str)!=0 && strcmp("UTF-8",yyvsp[0].str)!=0)
					compare = 0;
				free(yyvsp[0].str);
				yyval.integer = compare;
			;}
    break;

  case 4:
#line 116 "xTEDS.y"
    {
				yyval.integer = 1;
			;}
    break;

  case 5:
#line 122 "xTEDS.y"
    {
				free(yyvsp[0].str);
			;}
    break;

  case 7:
#line 134 "xTEDS.y"
    {
				yyval.xteds = add_references(yyvsp[-4].xteds,yyvsp[-3].attr,yyvsp[-2].interface);
			;}
    break;

  case 8:
#line 140 "xTEDS.y"
    {
				yyval.xteds=yyvsp[-1].xteds;
			;}
    break;

  case 9:
#line 146 "xTEDS.y"
    {
				yyval.xteds = merge_xteds(yyvsp[-1].xteds,yyvsp[0].xteds);
			;}
    break;

  case 10:
#line 150 "xTEDS.y"
    {
				xteds* temp;
				temp = new_xteds();
				yyval.xteds=temp;
			;}
    break;

  case 11:
#line 158 "xTEDS.y"
    {
				xteds* temp;
				temp = new_xteds();
				temp->name = yyvsp[0].str;
				yyval.xteds = temp;
			;}
    break;

  case 12:
#line 165 "xTEDS.y"
    {
				xteds* temp;
				temp = new_xteds();
				temp->version = yyvsp[0].str;
				yyval.xteds = temp;
			;}
    break;

  case 13:
#line 172 "xTEDS.y"
    {
				xteds* temp;
				temp = new_xteds();
				temp->description = yyvsp[0].str;
				yyval.xteds = temp;
			;}
    break;

  case 14:
#line 179 "xTEDS.y"
    {
				xteds* temp;
				temp = new_xteds();
				temp->xmlns = yyvsp[0].str;
				yyval.xteds = temp;
			;}
    break;

  case 15:
#line 186 "xTEDS.y"
    {
				xteds* temp;
				temp = new_xteds();
				temp->schema_location = yyvsp[0].str;
				yyval.xteds = temp;
			;}
    break;

  case 16:
#line 193 "xTEDS.y"
    {
				xteds* temp;
				temp = new_xteds();
				temp->xmlns_xsi = yyvsp[0].str;
				yyval.xteds = temp;
			;}
    break;

  case 17:
#line 207 "xTEDS.y"
    {
				yyval.attr = yyvsp[0].attr;
			;}
    break;

  case 18:
#line 211 "xTEDS.y"
    {
				yyval.attr = yyvsp[0].attr;
			;}
    break;

  case 19:
#line 217 "xTEDS.y"
    {
				yyval.attr = yyvsp[-1].attr;
			;}
    break;

  case 20:
#line 221 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->qualifiers = yyvsp[-2].qual;
				yyval.attr = merge_app_dev_attr(yyvsp[-4].attr,temp);
			;}
    break;

  case 21:
#line 230 "xTEDS.y"
    {
				yyval.attr = merge_app_dev_attr(yyvsp[-1].attr,yyvsp[0].attr);
			;}
    break;

  case 22:
#line 234 "xTEDS.y"
    {
				yyval.attr = NULL;
			;}
    break;

  case 23:
#line 240 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->name = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 24:
#line 247 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->kind = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 25:
#line 254 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->id = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 26:
#line 261 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->qualifier = yyvsp[0].str;
				printf("Qualifier field has been deprecated!\n");
				yyval.attr = temp;
			;}
    break;

  case 27:
#line 269 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->description = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 28:
#line 276 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->manufacturer_id = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 29:
#line 283 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->componentKey = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 30:
#line 292 "xTEDS.y"
    {
				yyval.attr = yyvsp[0].attr;
			;}
    break;

  case 31:
#line 296 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->version = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 32:
#line 303 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->memory_minimum = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 33:
#line 310 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->operating_system = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 34:
#line 317 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->path_for_assembly = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 35:
#line 324 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->path_on_spacecraft = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 36:
#line 338 "xTEDS.y"
    {
				yyval.attr = yyvsp[-1].attr;
			;}
    break;

  case 37:
#line 342 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->qualifiers = yyvsp[0].qual;
				merge_app_dev_attr(yyvsp[-5].attr,temp);
				yyval.attr = merge_app_dev_attr(yyvsp[-5].attr,yyvsp[-3].attr);
			;}
    break;

  case 38:
#line 352 "xTEDS.y"
    {
				yyval.attr = merge_app_dev_attr(yyvsp[-1].attr,yyvsp[0].attr);
			;}
    break;

  case 39:
#line 356 "xTEDS.y"
    {
				yyval.attr = NULL;
			;}
    break;

  case 40:
#line 362 "xTEDS.y"
    {
				app_dev_attr* temp = new_app_dev_attr();
				temp->qualifiers = yyvsp[0].qual;
				yyval.attr = temp;
			;}
    break;

  case 41:
#line 368 "xTEDS.y"
    {
				delete_location(yyvsp[0].location);	/*Location not used*/
				yyval.attr = NULL;
			;}
    break;

  case 42:
#line 373 "xTEDS.y"
    {
				delete_orientation(yyvsp[0].orientation);	/*Orientation not used*/
				yyval.attr = NULL;
			;}
    break;

  case 43:
#line 380 "xTEDS.y"
    {
				yyval.attr = merge_app_dev_attr(yyvsp[-1].attr,yyvsp[0].attr);
			;}
    break;

  case 44:
#line 384 "xTEDS.y"
    {
				yyval.attr = NULL;
			;}
    break;

  case 45:
#line 390 "xTEDS.y"
    {
				yyval.attr = yyvsp[0].attr;
			;}
    break;

  case 46:
#line 394 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->model_id = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 47:
#line 401 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->version_letter = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 48:
#line 408 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->serial_number = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 49:
#line 415 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->calibration_date = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 50:
#line 422 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->sensitivity_at_reference = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 51:
#line 429 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->reference_frequency = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 52:
#line 436 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->reference_temperature = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 53:
#line 443 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->measurement_range = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 54:
#line 450 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->electrical_output = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 55:
#line 457 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->quality_factor = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 56:
#line 464 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->temperature_coefficient = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 57:
#line 471 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->direction_xyz = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 58:
#line 478 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->cal_due_date = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 59:
#line 485 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->power_requirements = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 60:
#line 492 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->spa_u_hub = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 61:
#line 499 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->spa_u_port = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 62:
#line 506 "xTEDS.y"
    {
				app_dev_attr* temp;
				temp = new_app_dev_attr();
				temp->version = yyvsp[0].str;
				yyval.attr = temp;
			;}
    break;

  case 63:
#line 520 "xTEDS.y"
    {
				yyval.location = yyvsp[-1].location;
			;}
    break;

  case 64:
#line 524 "xTEDS.y"
    {
				yyval.location = yyvsp[-3].location;
			;}
    break;

  case 65:
#line 530 "xTEDS.y"
    {
				yyval.location = merge_locations(yyvsp[-1].location,yyvsp[0].location);
			;}
    break;

  case 66:
#line 534 "xTEDS.y"
    {
				yyval.location = NULL;
			;}
    break;

  case 67:
#line 540 "xTEDS.y"
    {
				location* x_loc = new_location();
				x_loc->x_value = yyvsp[0].str;
				yyval.location = x_loc;
			;}
    break;

  case 68:
#line 546 "xTEDS.y"
    {
				location* y_loc = new_location();
				y_loc->y_value = yyvsp[0].str;
				yyval.location = y_loc;
			;}
    break;

  case 69:
#line 552 "xTEDS.y"
    {
				location* z_loc = new_location();
				z_loc->z_value = yyvsp[0].str;
				yyval.location = z_loc;
			;}
    break;

  case 70:
#line 558 "xTEDS.y"
    {
				location* units_val = new_location();
				units_val->units = yyvsp[0].str;
				yyval.location = units_val;
			;}
    break;

  case 71:
#line 571 "xTEDS.y"
    {
				yyval.orientation = yyvsp[-1].orientation;
			;}
    break;

  case 72:
#line 575 "xTEDS.y"
    {
				yyval.orientation = yyvsp[-3].orientation;
			;}
    break;

  case 73:
#line 581 "xTEDS.y"
    {
				yyval.orientation = merge_orientations(yyvsp[-1].orientation,yyvsp[0].orientation);
			;}
    break;

  case 74:
#line 585 "xTEDS.y"
    {
				yyval.orientation = NULL;
			;}
    break;

  case 75:
#line 591 "xTEDS.y"
    {
				orientation* temp = new_orientation();
				temp->axis_value = yyvsp[0].str;
				yyval.orientation = temp;
			;}
    break;

  case 76:
#line 597 "xTEDS.y"
    {
				orientation* temp = new_orientation();
				temp->angle_value = yyvsp[0].str;
				yyval.orientation = temp;
			;}
    break;

  case 77:
#line 603 "xTEDS.y"
    {
				orientation* temp = new_orientation();
				temp->units_value = yyvsp[0].str;
				yyval.orientation = temp;
			;}
    break;

  case 78:
#line 615 "xTEDS.y"
    {
				yyval.qual= link_qualifiers(yyvsp[-1].qual,yyvsp[0].qual);
			;}
    break;

  case 79:
#line 619 "xTEDS.y"
    {
				yyval.qual= NULL;
			;}
    break;

  case 80:
#line 625 "xTEDS.y"
    {
				yyval.qual=yyvsp[-3].qual
			;}
    break;

  case 81:
#line 629 "xTEDS.y"
    {
				yyval.qual=yyvsp[-1].qual
			;}
    break;

  case 82:
#line 635 "xTEDS.y"
    {
				yyval.qual = merge_qualifiers(yyvsp[-1].qual,yyvsp[0].qual);
			;}
    break;

  case 83:
#line 639 "xTEDS.y"
    {
				yyval.qual = NULL;
			;}
    break;

  case 84:
#line 645 "xTEDS.y"
    {
				qualifier_type* temp;
				temp = new_qualifier();
				temp->name = yyvsp[0].str;
				yyval.qual = temp;
			;}
    break;

  case 85:
#line 652 "xTEDS.y"
    {
				qualifier_type* temp;
				temp = new_qualifier();
				temp->value = yyvsp[0].str;
				yyval.qual = temp;
			;}
    break;

  case 86:
#line 659 "xTEDS.y"
    {
				qualifier_type* temp;
				temp = new_qualifier();
				temp->units = yyvsp[0].str;
				yyval.qual = temp;
			;}
    break;

  case 87:
#line 673 "xTEDS.y"
    {
				yyval.interface = link_interface(yyvsp[-1].interface,yyvsp[0].interface);
			;}
    break;

  case 88:
#line 677 "xTEDS.y"
    {
				yyval.interface = NULL;
			;}
    break;

  case 89:
#line 683 "xTEDS.y"
    {
				yyval.interface = interface_add_references(yyvsp[-5].interface,yyvsp[-4].qual,yyvsp[-3].var,yyvsp[-2].message);
			;}
    break;

  case 90:
#line 687 "xTEDS.y"
    {
				yyval.interface = yyvsp[0].interface;
			;}
    break;

  case 91:
#line 693 "xTEDS.y"
    {
				yyval.interface = yyvsp[-1].interface;
			;}
    break;

  case 92:
#line 697 "xTEDS.y"
    {
				yyval.interface = yyvsp[-1].interface;
			;}
    break;

  case 93:
#line 703 "xTEDS.y"
    {
				yyval.interface = merge_interface(yyvsp[-1].interface,yyvsp[0].interface);
			;}
    break;

  case 94:
#line 707 "xTEDS.y"
    {
				interface* temp;
				temp = new_interface();
				yyval.interface = temp;
			;}
    break;

  case 95:
#line 715 "xTEDS.y"
    {
				/*Only qualifiers will be returned, all others thrown away*/
				yyval.qual = link_qualifiers(yyvsp[-1].qual,yyvsp[0].qual);
			;}
    break;

  case 96:
#line 720 "xTEDS.y"
    {
				yyval.qual = NULL;
			;}
    break;

  case 97:
#line 726 "xTEDS.y"
    {
				yyval.qual = yyvsp[0].qual;
			;}
    break;

  case 98:
#line 730 "xTEDS.y"
    {
				/* Don't need to save location information for an interface*/
				delete_location(yyvsp[0].location);
				yyval.qual = NULL;
			;}
    break;

  case 99:
#line 736 "xTEDS.y"
    {
				/* Don't need to save orientation information for an interface*/
				delete_orientation(yyvsp[0].orientation);
				yyval.qual = NULL;
			;}
    break;

  case 100:
#line 744 "xTEDS.y"
    {
				interface* temp;
				temp = new_interface();
				temp->name = yyvsp[0].str;
				yyval.interface = temp;
			;}
    break;

  case 101:
#line 751 "xTEDS.y"
    {
				interface* temp;
				temp = new_interface();
				temp->extends = yyvsp[0].str;
				yyval.interface = temp;
			;}
    break;

  case 102:
#line 758 "xTEDS.y"
    {
				interface* temp;
				temp = new_interface();
				temp->id = yyvsp[0].str;
				yyval.interface = temp;
			;}
    break;

  case 103:
#line 765 "xTEDS.y"
    {
				interface* temp;
				temp = new_interface();
				temp->description = yyvsp[0].str;
				yyval.interface = temp;
			;}
    break;

  case 104:
#line 779 "xTEDS.y"
    {
				yyval.message = merge_message(yyvsp[-1].message,yyvsp[0].message);
			;}
    break;

  case 105:
#line 783 "xTEDS.y"
    {
				yyval.message = NULL;
			;}
    break;

  case 106:
#line 789 "xTEDS.y"
    {
				message* temp;
				temp = new_message();
				temp->commands = yyvsp[0].command;
				yyval.message = temp;
			;}
    break;

  case 107:
#line 796 "xTEDS.y"
    {
				message* temp;
				temp = new_message();
				temp->notifications = yyvsp[0].notification;
				yyval.message = temp;
			;}
    break;

  case 108:
#line 803 "xTEDS.y"
    {
				message* temp;
				temp = new_message();
				temp->requests = yyvsp[0].request;
				yyval.message = temp;
			;}
    break;

  case 109:
#line 812 "xTEDS.y"
    {
				request* temp;
				temp = new_request();
				temp = request_add_cmd_msg(temp,yyvsp[-4].cmd_msg);
				temp = request_add_data_msg(temp,yyvsp[-3].data_msg);
				yyval.request = request_add_fault_msg(temp,yyvsp[-2].fault_msg);
			;}
    break;

  case 110:
#line 827 "xTEDS.y"
    {
				yyval.fault_msg = yyvsp[0].fault_msg;
			;}
    break;

  case 111:
#line 833 "xTEDS.y"
    {
				fault_msg* result;
				result = merge_fault_msg(yyvsp[-5].fault_msg,yyvsp[-3].fault_msg);
				yyval.fault_msg = fault_add_var_refs(result,yyvsp[-2].var_ref);
			;}
    break;

  case 112:
#line 839 "xTEDS.y"
    {
				yyval.fault_msg = yyvsp[-1].fault_msg;
			;}
    break;

  case 113:
#line 843 "xTEDS.y"
    {
				yyval.fault_msg = NULL;
			;}
    break;

  case 114:
#line 849 "xTEDS.y"
    {
				yyval.fault_msg = merge_fault_msg(yyvsp[-1].fault_msg,yyvsp[0].fault_msg);
			;}
    break;

  case 115:
#line 853 "xTEDS.y"
    {
				yyval.fault_msg = NULL;
			;}
    break;

  case 116:
#line 859 "xTEDS.y"
    {
				fault_msg* temp;
				temp = new_fault_msg();
				temp->name = yyvsp[0].str;
				yyval.fault_msg = temp;
			;}
    break;

  case 117:
#line 866 "xTEDS.y"
    {
				fault_msg* temp;
				temp = new_fault_msg();
				temp->id = yyvsp[0].str;
				yyval.fault_msg = temp;
			;}
    break;

  case 118:
#line 873 "xTEDS.y"
    {
				fault_msg* temp;
				temp = new_fault_msg();
				temp->description = yyvsp[0].str;
				yyval.fault_msg = temp;
			;}
    break;

  case 119:
#line 882 "xTEDS.y"
    {
				fault_msg* temp;
				temp = new_fault_msg();
				temp->qualifiers = yyvsp[0].qual;
				yyval.fault_msg = temp;
			;}
    break;

  case 120:
#line 896 "xTEDS.y"
    {
				notification* temp;
				temp = new_notification();
				temp = notification_add_data_msg(temp,yyvsp[-3].data_msg);
				yyval.notification = notification_add_fault_msg(temp,yyvsp[-2].fault_msg);
			;}
    break;

  case 121:
#line 905 "xTEDS.y"
    {
				yyval.data_msg = link_data_msg(yyvsp[-1].data_msg,yyvsp[0].data_msg);
			;}
    break;

  case 122:
#line 909 "xTEDS.y"
    {
				yyval.data_msg = NULL;
			;}
    break;

  case 123:
#line 915 "xTEDS.y"
    {
				data_msg* result;
				result = merge_data_msg(yyvsp[-5].data_msg,yyvsp[-3].data_msg);
				yyval.data_msg = data_add_var_refs(result,yyvsp[-2].var_ref);
			;}
    break;

  case 124:
#line 923 "xTEDS.y"
    {
				yyval.data_msg=merge_data_msg(yyvsp[-1].data_msg,yyvsp[0].data_msg);
			;}
    break;

  case 125:
#line 927 "xTEDS.y"
    {
				yyval.data_msg=NULL;
			;}
    break;

  case 126:
#line 933 "xTEDS.y"
    {
				data_msg* temp;
				temp = new_data_msg();
				temp->name = yyvsp[0].str;
				yyval.data_msg = temp;
			;}
    break;

  case 127:
#line 940 "xTEDS.y"
    {
				data_msg* temp;
				temp = new_data_msg();
				temp->id = yyvsp[0].str;
				yyval.data_msg = temp;
			;}
    break;

  case 128:
#line 947 "xTEDS.y"
    {
				data_msg* temp;
				temp = new_data_msg();
				temp->msg_arrival = yyvsp[0].str;
				yyval.data_msg = temp;
			;}
    break;

  case 129:
#line 954 "xTEDS.y"
    {
				data_msg* temp;
				temp = new_data_msg();
				temp->description = yyvsp[0].str;
				yyval.data_msg = temp;
			;}
    break;

  case 130:
#line 961 "xTEDS.y"
    {
				data_msg* temp;
				temp = new_data_msg();
				temp->msg_rate = yyvsp[0].str;
				yyval.data_msg = temp;
			;}
    break;

  case 131:
#line 970 "xTEDS.y"
    {
				data_msg* temp;
				temp = new_data_msg();
				temp->qualifiers = yyvsp[0].qual;
				yyval.data_msg = temp;
			;}
    break;

  case 132:
#line 984 "xTEDS.y"
    {
				command* temp;
				temp = new_command();
				temp = command_add_cmd_msg(temp,yyvsp[-3].cmd_msg);
				yyval.command = command_add_fault_msg(temp,yyvsp[-2].fault_msg);
			;}
    break;

  case 133:
#line 993 "xTEDS.y"
    {
				yyval.cmd_msg = link_cmd_msg(yyvsp[-1].cmd_msg,yyvsp[0].cmd_msg);
			;}
    break;

  case 134:
#line 997 "xTEDS.y"
    {
				yyval.cmd_msg = NULL;
			;}
    break;

  case 135:
#line 1003 "xTEDS.y"
    {	
				cmd_msg* result;
				result = merge_cmd_msg(yyvsp[-5].cmd_msg,yyvsp[-3].cmd_msg);
				yyval.cmd_msg = cmd_add_var_refs(result,yyvsp[-2].var_ref);
			;}
    break;

  case 136:
#line 1009 "xTEDS.y"
    {
				yyval.cmd_msg = cmd_add_var_refs(yyvsp[-1].cmd_msg,NULL);
			;}
    break;

  case 137:
#line 1015 "xTEDS.y"
    {
				yyval.cmd_msg = merge_cmd_msg(yyvsp[-1].cmd_msg,yyvsp[0].cmd_msg);
			;}
    break;

  case 138:
#line 1019 "xTEDS.y"
    {
				yyval.cmd_msg=NULL;
			;}
    break;

  case 139:
#line 1025 "xTEDS.y"
    {
				cmd_msg* temp;
				temp = new_cmd_msg();
				temp->name = yyvsp[0].str;
				yyval.cmd_msg = temp;
			;}
    break;

  case 140:
#line 1032 "xTEDS.y"
    {
				cmd_msg* temp;
				temp = new_cmd_msg();
				temp->id = yyvsp[0].str;
				yyval.cmd_msg = temp;
			;}
    break;

  case 141:
#line 1039 "xTEDS.y"
    {
				cmd_msg* temp;
				temp = new_cmd_msg();
				temp->description = yyvsp[0].str;
				yyval.cmd_msg = temp;
			;}
    break;

  case 142:
#line 1048 "xTEDS.y"
    {
				cmd_msg* temp;
				temp = new_cmd_msg();
				temp->qualifiers = yyvsp[0].qual;
				yyval.cmd_msg = temp;
			;}
    break;

  case 143:
#line 1062 "xTEDS.y"
    {
				yyval.var= link_variables(yyvsp[-1].var,yyvsp[0].var);
			;}
    break;

  case 144:
#line 1066 "xTEDS.y"
    {
				yyval.var= NULL;
			;}
    break;

  case 145:
#line 1072 "xTEDS.y"
    {		
				yyval.var=yyvsp[0].var
			;}
    break;

  case 146:
#line 1076 "xTEDS.y"
    {
				yyval.var=yyvsp[0].var
			;}
    break;

  case 147:
#line 1082 "xTEDS.y"
    {
				yyval.var =  merge_variables(yyvsp[-4].var,yyvsp[-2].var);
			;}
    break;

  case 149:
#line 1091 "xTEDS.y"
    {
				yyval.var= yyvsp[0].var
			;}
    break;

  case 150:
#line 1097 "xTEDS.y"
    {
				yyval.var= merge_variables(yyvsp[-1].var,yyvsp[0].var);
			;}
    break;

  case 151:
#line 1101 "xTEDS.y"
    {
				yyval.var=NULL;
			;}
    break;

  case 152:
#line 1107 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->name = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 153:
#line 1114 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->kind = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 154:
#line 1121 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->format = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 155:
#line 1128 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->qualifier = yyvsp[0].str;
				printf("<Variable qualifier attribute has been deprecated!\n");
				yyval.var = temp;
			;}
    break;

  case 156:
#line 1136 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->id = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 157:
#line 1143 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->description = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 158:
#line 1150 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->range_min = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 159:
#line 1157 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->range_max = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 160:
#line 1164 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->length = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 161:
#line 1171 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->default_value = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 162:
#line 1178 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->precision = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 163:
#line 1185 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->units = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 164:
#line 1192 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->accuracy = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 165:
#line 1199 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->scale_factor = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 166:
#line 1206 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->scale_units = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 167:
#line 1213 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->r_low = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 168:
#line 1220 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->r_high = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 169:
#line 1227 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->y_low = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 170:
#line 1234 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->y_high = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 171:
#line 1242 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->invalid_value = yyvsp[0].str;
				yyval.var = temp;
			;}
    break;

  case 172:
#line 1251 "xTEDS.y"
    {
				yyval.var = merge_variables(yyvsp[-1].var,yyvsp[0].var);
			;}
    break;

  case 173:
#line 1257 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->qualifiers = yyvsp[0].qual;
				yyval.var = temp;
			;}
    break;

  case 174:
#line 1267 "xTEDS.y"
    {
				yyval.var = merge_variables(yyvsp[-1].var,yyvsp[0].var);
			;}
    break;

  case 175:
#line 1271 "xTEDS.y"
    {
				yyval.var = NULL;
			;}
    break;

  case 176:
#line 1277 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->dranges = yyvsp[0].drange;
				yyval.var = temp;
			;}
    break;

  case 177:
#line 1284 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->curves = yyvsp[0].curve;
				yyval.var = temp;
			;}
    break;

  case 178:
#line 1291 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->location_data = yyvsp[0].location;
				yyval.var = temp;
			;}
    break;

  case 179:
#line 1298 "xTEDS.y"
    {
				variable* temp;
				temp = new_variable();
				temp->orientation_data = yyvsp[0].orientation;
				yyval.var = temp;
			;}
    break;

  case 180:
#line 1312 "xTEDS.y"
    {
				yyval.var_ref = link_variable_ref(yyvsp[-1].var_ref,yyvsp[0].var_ref);
			;}
    break;

  case 181:
#line 1316 "xTEDS.y"
    {
				yyval.var_ref = NULL;
			;}
    break;

  case 182:
#line 1322 "xTEDS.y"
    {
				yyval.var_ref = new_variable_ref(yyvsp[-1].str);
			;}
    break;

  case 183:
#line 1326 "xTEDS.y"
    {
				yyval.var_ref = new_variable_ref(yyvsp[-3].str);
			;}
    break;

  case 184:
#line 1337 "xTEDS.y"
    {
				drange* temp;
				temp = new_drange();
				temp->options = yyvsp[-2].curveoption;
				yyval.drange = merge_dranges(yyvsp[-3].drange,temp);
			;}
    break;

  case 185:
#line 1346 "xTEDS.y"
    {
				yyval.drange = yyvsp[-1].drange;
			;}
    break;

  case 186:
#line 1352 "xTEDS.y"
    {
				yyval.drange = merge_dranges(yyvsp[-1].drange,yyvsp[0].drange);
			;}
    break;

  case 187:
#line 1356 "xTEDS.y"
    {
				yyval.drange = NULL;
			;}
    break;

  case 188:
#line 1362 "xTEDS.y"
    {
				drange* temp;
				temp = new_drange();
				temp->name = yyvsp[0].str;
				yyval.drange = temp;
			;}
    break;

  case 189:
#line 1369 "xTEDS.y"
    {
				drange* temp;
				temp = new_drange();
				temp->description = yyvsp[0].str;
				yyval.drange = temp;
			;}
    break;

  case 190:
#line 1378 "xTEDS.y"
    {
				yyval.curveoption = link_options(yyvsp[-1].curveoption,yyvsp[0].curveoption);
			;}
    break;

  case 191:
#line 1382 "xTEDS.y"
    {
				yyval.curveoption = NULL;
			;}
    break;

  case 192:
#line 1388 "xTEDS.y"
    {
				yyval.curveoption = yyvsp[-1].curveoption;
			;}
    break;

  case 193:
#line 1392 "xTEDS.y"
    {
				yyval.curveoption = yyvsp[-3].curveoption;
			;}
    break;

  case 194:
#line 1398 "xTEDS.y"
    {
				yyval.curveoption = merge_options(yyvsp[-1].curveoption,yyvsp[0].curveoption);
			;}
    break;

  case 195:
#line 1402 "xTEDS.y"
    {
				yyval.curveoption = NULL;
			;}
    break;

  case 196:
#line 1408 "xTEDS.y"
    {
				curveoption* temp;
				temp = new_option();
				temp->name = yyvsp[0].str;
				yyval.curveoption = temp;
			;}
    break;

  case 197:
#line 1415 "xTEDS.y"
    {
				curveoption* temp;
				temp = new_option();
				temp->value = yyvsp[0].str;
				yyval.curveoption = temp;
			;}
    break;

  case 198:
#line 1422 "xTEDS.y"
    {
				curveoption* temp;
				temp = new_option();
				temp->description = yyvsp[0].str;
				yyval.curveoption = temp;
			;}
    break;

  case 199:
#line 1429 "xTEDS.y"
    {
				curveoption* temp;
				temp = new_option();
				temp->alarm = yyvsp[0].str;
				yyval.curveoption = temp;
			;}
    break;

  case 200:
#line 1443 "xTEDS.y"
    {
				curve* temp;
				temp = new_curve();
				temp->coefs = yyvsp[-2].coef;
				yyval.curve = merge_curves(yyvsp[-3].curve,temp);
			;}
    break;

  case 201:
#line 1452 "xTEDS.y"
    {
				yyval.curve = yyvsp[-1].curve;
			;}
    break;

  case 202:
#line 1458 "xTEDS.y"
    {
				yyval.curve = merge_curves(yyvsp[-1].curve,yyvsp[0].curve);
			;}
    break;

  case 203:
#line 1462 "xTEDS.y"
    {
				yyval.curve = NULL;
			;}
    break;

  case 204:
#line 1468 "xTEDS.y"
    {
				curve* temp;
				temp = new_curve();
				temp->name = yyvsp[0].str;
				yyval.curve = temp;
			;}
    break;

  case 205:
#line 1475 "xTEDS.y"
    {
				curve* temp;
				temp = new_curve();
				temp->description = yyvsp[0].str;
				yyval.curve = temp;
			;}
    break;

  case 206:
#line 1484 "xTEDS.y"
    {
				yyval.coef = link_coefs(yyvsp[-1].coef,yyvsp[0].coef);
			;}
    break;

  case 207:
#line 1488 "xTEDS.y"
    {
				yyval.coef = NULL;
			;}
    break;

  case 208:
#line 1494 "xTEDS.y"
    {
				yyval.coef = yyvsp[-1].coef;
			;}
    break;

  case 209:
#line 1498 "xTEDS.y"
    {
				yyval.coef = yyvsp[-3].coef;
			;}
    break;

  case 210:
#line 1502 "xTEDS.y"
    {
				yyval.coef = yyvsp[-1].coef;
			;}
    break;

  case 211:
#line 1508 "xTEDS.y"
    {
				yyval.coef = merge_coefs(yyvsp[-1].coef,yyvsp[0].coef);
			;}
    break;

  case 212:
#line 1512 "xTEDS.y"
    {
				yyval.coef = NULL;
			;}
    break;

  case 213:
#line 1518 "xTEDS.y"
    {
				coef* temp;
				temp = new_coef();
				temp->exponent = yyvsp[0].str;
				yyval.coef = temp;
			;}
    break;

  case 214:
#line 1525 "xTEDS.y"
    {
				coef* temp;
				temp = new_coef();
				temp->value = yyvsp[0].str;
				yyval.coef = temp;
			;}
    break;

  case 215:
#line 1532 "xTEDS.y"
    {
				coef* temp;
				temp = new_coef();
				temp->description = yyvsp[0].str;
				yyval.coef = temp;
			;}
    break;


    }

/* Line 1010 of yacc.c.  */
#line 3533 "xTEDS.tab.c"

  yyvsp -= yylen;
  yyssp -= yylen;


  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;


  /* Now `shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*------------------------------------.
| yyerrlab -- here on detecting error |
`------------------------------------*/
yyerrlab:
  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (YYPACT_NINF < yyn && yyn < YYLAST)
	{
	  YYSIZE_T yysize = 0;
	  int yytype = YYTRANSLATE (yychar);
	  const char* yyprefix;
	  char *yymsg;
	  int yyx;

	  /* Start YYX at -YYN if negative to avoid negative indexes in
	     YYCHECK.  */
	  int yyxbegin = yyn < 0 ? -yyn : 0;

	  /* Stay within bounds of both yycheck and yytname.  */
	  int yychecklim = YYLAST - yyn;
	  int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
	  int yycount = 0;

	  yyprefix = ", expecting ";
	  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
	    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
	      {
		yysize += yystrlen (yyprefix) + yystrlen (yytname [yyx]);
		yycount += 1;
		if (yycount == 5)
		  {
		    yysize = 0;
		    break;
		  }
	      }
	  yysize += (sizeof ("syntax error, unexpected ")
		     + yystrlen (yytname[yytype]));
	  yymsg = (char *) YYSTACK_ALLOC (yysize);
	  if (yymsg != 0)
	    {
	      char *yyp = yystpcpy (yymsg, "syntax error, unexpected ");
	      yyp = yystpcpy (yyp, yytname[yytype]);

	      if (yycount < 5)
		{
		  yyprefix = ", expecting ";
		  for (yyx = yyxbegin; yyx < yyxend; ++yyx)
		    if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR)
		      {
			yyp = yystpcpy (yyp, yyprefix);
			yyp = yystpcpy (yyp, yytname[yyx]);
			yyprefix = " or ";
		      }
		}
	      yyerror (yymsg);
	      YYSTACK_FREE (yymsg);
	    }
	  else
	    yyerror ("syntax error; also virtual memory exhausted");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror ("syntax error");
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
	 error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* If at end of input, pop the error token,
	     then the rest of the stack, then return failure.  */
	  if (yychar == YYEOF)
	     for (;;)
	       {
		 YYPOPSTACK;
		 if (yyssp == yyss)
		   YYABORT;
		 YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
		 yydestruct (yystos[*yyssp], yyvsp);
	       }
        }
      else
	{
	  YYDSYMPRINTF ("Error: discarding", yytoken, &yylval, &yylloc);
	  yydestruct (yytoken, &yylval);
	  yychar = YYEMPTY;

	}
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

#ifdef __GNUC__
  /* Pacify GCC when the user code never invokes YYERROR and the label
     yyerrorlab therefore never appears in user code.  */
  if (0)
     goto yyerrorlab;
#endif

  yyvsp -= yylen;
  yyssp -= yylen;
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;	/* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (yyn != YYPACT_NINF)
	{
	  yyn += YYTERROR;
	  if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
	    {
	      yyn = yytable[yyn];
	      if (0 < yyn)
		break;
	    }
	}

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
	YYABORT;

      YYDSYMPRINTF ("Error: popping", yystos[*yyssp], yyvsp, yylsp);
      yydestruct (yystos[yystate], yyvsp);
      YYPOPSTACK;
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  if (yyn == YYFINAL)
    YYACCEPT;

  YYDPRINTF ((stderr, "Shifting error token, "));

  *++yyvsp = yylval;


  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#ifndef yyoverflow
/*----------------------------------------------.
| yyoverflowlab -- parser overflow comes here.  |
`----------------------------------------------*/
yyoverflowlab:
  yyerror ("parser stack overflow");
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
  return yyresult;
}


#line 1539 "xTEDS.y"


