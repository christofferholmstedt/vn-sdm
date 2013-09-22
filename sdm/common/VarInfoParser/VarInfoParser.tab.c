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
#define yyparse VarInfoParserparse
#define yylex   VarInfoParserlex
#define yyerror VarInfoParsererror
#define yylval  VarInfoParserlval
#define yychar  VarInfoParserchar
#define yydebug VarInfoParserdebug
#define yynerrs VarInfoParsernerrs


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
     CLOSE_COEFF_SY = 357
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




/* Copy the first part of user declarations.  */
#line 1 "VarInfoParser.y"

#include <stdio.h>
#include <string.h>
#include "../xTEDS/xTEDSParser.h"


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
#line 40 "VarInfoParser.y"
typedef union YYSTYPE {
	int integer;
	float real;
	char* str;
	struct variable_data* var;
	struct qualifier_data* qual;
	struct coefficient_data* coef;
	struct curve_data* curve;
	struct option_data* curveoption;
	struct drange_data* drange;
} YYSTYPE;
/* Line 191 of yacc.c.  */
#line 307 "VarInfoParser.tab.c"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif



/* Copy the second part of user declarations.  */


/* Line 214 of yacc.c.  */
#line 319 "VarInfoParser.tab.c"

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
#define YYFINAL  7
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   115

/* YYNTOKENS -- Number of terminals. */
#define YYNTOKENS  103
/* YYNNTS -- Number of nonterminals. */
#define YYNNTS  35
/* YYNRULES -- Number of rules. */
#define YYNRULES  74
/* YYNRULES -- Number of states. */
#define YYNSTATES  151

/* YYTRANSLATE(YYLEX) -- Bison symbol number corresponding to YYLEX.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   357

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
      95,    96,    97,    98,    99,   100,   101,   102
};

#if YYDEBUG
/* YYPRHS[YYN] -- Index of the first RHS symbol of rule number YYN in
   YYRHS.  */
static const unsigned char yyprhs[] =
{
       0,     0,     3,     5,     7,    13,    16,    19,    22,    23,
      27,    31,    35,    39,    43,    47,    51,    55,    59,    63,
      67,    71,    75,    79,    83,    86,    88,    91,    92,    94,
      96,    98,   100,   106,   109,   110,   113,   116,   117,   121,
     125,   129,   134,   138,   141,   142,   146,   150,   153,   154,
     158,   164,   167,   168,   172,   176,   180,   184,   189,   193,
     196,   197,   201,   205,   208,   209,   213,   219,   223,   226,
     227,   231,   235,   239,   242
};

/* YYRHS -- A `-1'-separated list of the rules' RHS. */
static const short int yyrhs[] =
{
     104,     0,    -1,   105,    -1,   106,    -1,   107,     4,   110,
      11,     4,    -1,   107,     5,    -1,    10,   108,    -1,   108,
     109,    -1,    -1,    23,     3,    49,    -1,    24,     3,    49,
      -1,    55,     3,    49,    -1,    27,     3,    49,    -1,    25,
       3,    49,    -1,    28,     3,    49,    -1,    57,     3,    49,
      -1,    53,     3,    49,    -1,    63,     3,    49,    -1,    60,
       3,    49,    -1,    52,     3,    49,    -1,    59,     3,    49,
      -1,    56,     3,    49,    -1,    58,     3,    49,    -1,    62,
       3,    49,    -1,   111,   112,    -1,   137,    -1,   112,   113,
      -1,    -1,   121,    -1,   129,    -1,   115,    -1,   116,    -1,
     118,     4,   117,    83,     4,    -1,   118,     5,    -1,    -1,
      82,   119,    -1,   119,   120,    -1,    -1,    23,     3,    49,
      -1,    45,     3,    49,    -1,    59,     3,    49,    -1,   122,
     125,    13,     4,    -1,    12,   123,     4,    -1,   123,   124,
      -1,    -1,    23,     3,    49,    -1,    28,     3,    49,    -1,
     125,   126,    -1,    -1,    14,   127,     5,    -1,    14,   127,
       4,    68,     4,    -1,   127,   128,    -1,    -1,    23,     3,
      49,    -1,    45,     3,    49,    -1,    28,     3,    49,    -1,
      46,     3,    49,    -1,   130,   133,    16,     4,    -1,    15,
     131,     4,    -1,   131,   132,    -1,    -1,    23,     3,    49,
      -1,    28,     3,    49,    -1,   133,   134,    -1,    -1,    17,
     135,     5,    -1,    17,   135,     4,   102,     4,    -1,    17,
     135,     4,    -1,   135,   136,    -1,    -1,    64,     3,    49,
      -1,    45,     3,    49,    -1,    28,     3,    49,    -1,   137,
     114,    -1,    -1
};

/* YYRLINE[YYN] -- source line where rule number YYN was defined.  */
static const unsigned short int yyrline[] =
{
       0,    55,    55,    59,    65,    71,    74,    80,    85,    90,
      97,   104,   111,   119,   126,   133,   140,   147,   154,   161,
     168,   175,   182,   189,   198,   204,   214,   219,   224,   231,
     240,   244,   250,   256,   262,   265,   271,   276,   281,   288,
     295,   304,   313,   319,   324,   329,   336,   345,   350,   355,
     359,   365,   370,   375,   382,   389,   396,   404,   413,   419,
     424,   429,   436,   445,   450,   455,   459,   463,   469,   474,
     479,   486,   493,   501,   506
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
  "STANDALONE_SY", "CLOSE_VARIABLE_REF_SY", "CLOSE_COEFF_SY", "$accept",
  "VARIABLE", "VAR_WITH_SUBELEMENTS", "VAR_NO_SUBELEMENTS", "VAR_HEAD",
  "VAR_ATTRIBUTES", "VAR_ATTRIBUTE", "VAR_ELEMENTS", "VAR_QUALIFIERS",
  "VAR_SUBELEMENTS", "VAR_SUBELEMENT", "QUALIFIERS",
  "QUALIFIERS_WITH_SUBELEMENTS", "QUALIFIERS_NO_SUBELEMENTS",
  "QUALIFIERS_SUBELEMENTS", "QUALIFIERS_HEAD", "QUALIFIERS_ATTRIBUTES",
  "QUALIFIERS_ATTRIBUTE", "DRANGE", "DRANGE_HEAD", "DRANGE_ATTRIBUTES",
  "DRANGE_ATTRIBUTE", "DRANGE_OPTIONS", "DRANGE_OPTION",
  "OPTION_ATTRIBUTES", "OPTION_ATTRIBUTE", "CURVE", "CURVE_HEAD",
  "CURVE_ATTRIBUTES", "CURVE_ATTRIBUTE", "CURVE_COEFFS", "CURVE_COEFF",
  "COEFF_ATTRIBUTES", "COEFF_ATTRIBUTE", "QUALIFIERS_SECTION", 0
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
     355,   356,   357
};
# endif

/* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const unsigned char yyr1[] =
{
       0,   103,   104,   104,   105,   106,   107,   108,   108,   109,
     109,   109,   109,   109,   109,   109,   109,   109,   109,   109,
     109,   109,   109,   109,   110,   111,   112,   112,   113,   113,
     114,   114,   115,   116,   117,   118,   119,   119,   120,   120,
     120,   121,   122,   123,   123,   124,   124,   125,   125,   126,
     126,   127,   127,   128,   128,   128,   128,   129,   130,   131,
     131,   132,   132,   133,   133,   134,   134,   134,   135,   135,
     136,   136,   136,   137,   137
};

/* YYR2[YYN] -- Number of symbols composing right hand side of rule YYN.  */
static const unsigned char yyr2[] =
{
       0,     2,     1,     1,     5,     2,     2,     2,     0,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     2,     1,     2,     0,     1,     1,
       1,     1,     5,     2,     0,     2,     2,     0,     3,     3,
       3,     4,     3,     2,     0,     3,     3,     2,     0,     3,
       5,     2,     0,     3,     3,     3,     3,     4,     3,     2,
       0,     3,     3,     2,     0,     3,     5,     3,     2,     0,
       3,     3,     3,     2,     0
};

/* YYDEFACT[STATE-NAME] -- Default rule to reduce with in state
   STATE-NUM when YYTABLE doesn't specify something else to do.  Zero
   means the default is an error.  */
static const unsigned char yydefact[] =
{
       0,     8,     0,     2,     3,     0,     6,     1,    74,     5,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,     7,     0,    27,    25,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,     0,     0,     0,    24,    37,    73,    30,    31,
       0,     9,    10,    13,    12,    14,    19,    16,    11,    21,
      15,    22,    20,    18,    23,    17,     4,    44,    60,    26,
      28,    48,    29,    64,    35,    34,    33,     0,     0,     0,
       0,     0,     0,     0,    36,     0,    42,     0,     0,    43,
      58,     0,     0,    59,     0,    52,    47,     0,    69,    63,
       0,     0,     0,     0,     0,     0,     0,     0,    41,     0,
      57,     0,    38,    39,    40,    32,    45,    46,    61,    62,
       0,    49,     0,     0,     0,     0,    51,    67,    65,     0,
       0,     0,    68,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    50,    53,    55,    54,    56,    66,    72,    71,
      70
};

/* YYDEFGOTO[NTERM-NUM]. */
static const short int yydefgoto[] =
{
      -1,     2,     3,     4,     5,     6,    25,    26,    27,    45,
      69,    47,    48,    49,    85,    50,    74,    84,    70,    71,
      77,    89,    79,    96,   109,   126,    72,    73,    78,    93,
      80,    99,   111,   132,    28
};

/* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
   STATE-NUM.  */
#define YYPACT_NINF -66
static const yysigned_char yypact[] =
{
      -1,   -66,     5,   -66,   -66,     7,    -5,   -66,   -66,   -66,
      22,    30,    32,    33,    34,    35,    36,    37,    42,    43,
      46,    53,    56,    58,    59,   -66,    52,   -66,   -65,    15,
      16,    17,    18,    19,    20,    21,    23,    24,    25,    26,
      27,    28,    29,    31,    67,    -8,   -66,   -66,   -66,   -66,
       9,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,   -17,   -66,   -66,     4,     6,     2,
      14,    76,    78,    79,   -66,     0,   -66,    81,    82,   -66,
     -66,    83,    84,   -66,    85,   -66,   -66,    86,   -66,   -66,
      39,    44,    45,    87,    47,    48,    49,    50,   -66,    -2,
     -66,    -4,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
      38,   -66,    89,    92,    97,    98,   -66,     1,   -66,    99,
     101,   102,   -66,   103,    60,    61,    62,    63,   104,    64,
      65,    66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
     -66
};

/* YYPGOTO[NTERM-NUM].  */
static const yysigned_char yypgoto[] =
{
     -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,   -66,
     -66,   -66,   -66,   -66,   -66
};

/* YYTABLE[YYPACT[STATE-NUM]].  What to do in state STATE-NUM.  If
   positive, shift that token.  If negative, reduce the rule which
   number is the opposite.  If zero, do what YYDEFACT says.
   If YYTABLE_NINF, syntax error.  */
#define YYTABLE_NINF -1
static const unsigned char yytable[] =
{
     127,   128,   120,   121,    67,     7,    81,    68,    86,     1,
      90,     8,     9,    75,    76,    94,    95,    46,    10,    11,
      12,   122,    13,    14,   129,    29,   123,    87,    82,    91,
      97,    98,    88,    30,    92,    31,    32,    33,    34,    35,
      36,   130,    83,   124,   125,    37,    38,    15,    16,    39,
      17,    18,    19,    20,    21,    22,    40,    23,    24,    41,
     131,    42,    43,    44,    51,    52,    53,    54,    55,    56,
      57,    66,    58,    59,    60,    61,    62,    63,    64,   100,
      65,   101,   102,   103,   104,   105,   106,   107,   112,   108,
     110,   115,   134,   113,   114,   135,   116,   117,   118,   119,
     136,   137,   139,   138,   140,   141,   133,   142,   147,   143,
     144,   145,   146,   148,   149,   150
};

static const unsigned char yycheck[] =
{
       4,     5,     4,     5,    12,     0,    23,    15,     4,    10,
       4,     4,     5,     4,     5,    13,    14,    82,    23,    24,
      25,    23,    27,    28,    28,     3,    28,    23,    45,    23,
      16,    17,    28,     3,    28,     3,     3,     3,     3,     3,
       3,    45,    59,    45,    46,     3,     3,    52,    53,     3,
      55,    56,    57,    58,    59,    60,     3,    62,    63,     3,
      64,     3,     3,    11,    49,    49,    49,    49,    49,    49,
      49,     4,    49,    49,    49,    49,    49,    49,    49,     3,
      49,     3,     3,    83,     3,     3,     3,     3,    49,     4,
       4,     4,     3,    49,    49,     3,    49,    49,    49,    49,
       3,     3,     3,   102,     3,     3,    68,     4,     4,    49,
      49,    49,    49,    49,    49,    49
};

/* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
   symbol of state STATE-NUM.  */
static const unsigned char yystos[] =
{
       0,    10,   104,   105,   106,   107,   108,     0,     4,     5,
      23,    24,    25,    27,    28,    52,    53,    55,    56,    57,
      58,    59,    60,    62,    63,   109,   110,   111,   137,     3,
       3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,    11,   112,    82,   114,   115,   116,
     118,    49,    49,    49,    49,    49,    49,    49,    49,    49,
      49,    49,    49,    49,    49,    49,     4,    12,    15,   113,
     121,   122,   129,   130,   119,     4,     5,   123,   131,   125,
     133,    23,    45,    59,   120,   117,     4,    23,    28,   124,
       4,    23,    28,   132,    13,    14,   126,    16,    17,   134,
       3,     3,     3,    83,     3,     3,     3,     3,     4,   127,
       4,   135,    49,    49,    49,     4,    49,    49,    49,    49,
       4,     5,    23,    28,    45,    46,   128,     4,     5,    28,
      45,    64,   136,    68,     3,     3,     3,     3,   102,     3,
       3,     3,     4,    49,    49,    49,    49,     4,    49,    49,
      49
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
#line 56 "VarInfoParser.y"
    {		
				yyval.var=yyvsp[0].var
;}
    break;

  case 3:
#line 60 "VarInfoParser.y"
    {
				yyval.var=yyvsp[0].var
;}
    break;

  case 4:
#line 66 "VarInfoParser.y"
    {
				yyval.var =  merge_variables(yyvsp[-4].var,yyvsp[-2].var);
;}
    break;

  case 6:
#line 75 "VarInfoParser.y"
    {
				yyval.var= yyvsp[0].var
;}
    break;

  case 7:
#line 81 "VarInfoParser.y"
    {
				yyval.var= merge_variables(yyvsp[-1].var,yyvsp[0].var);
;}
    break;

  case 8:
#line 85 "VarInfoParser.y"
    {
				yyval.var=NULL;
;}
    break;

  case 9:
#line 91 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->name = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 10:
#line 98 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->kind = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 11:
#line 105 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->format = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 12:
#line 112 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->qualifier = yyvsp[0].str;
				printf("Qualifier field has been deprecated!\n");
				yyval.var = temp;
;}
    break;

  case 13:
#line 120 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->id = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 14:
#line 127 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->description = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 15:
#line 134 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->range_min = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 16:
#line 141 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->range_max = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 17:
#line 148 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->length = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 18:
#line 155 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->default_value = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 19:
#line 162 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->precision = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 20:
#line 169 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->units = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 21:
#line 176 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->accuracy = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 22:
#line 183 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->scale_factor = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 23:
#line 190 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->scale_units = yyvsp[0].str;
				yyval.var = temp;
;}
    break;

  case 24:
#line 199 "VarInfoParser.y"
    {
				yyval.var = merge_variables(yyvsp[-1].var,yyvsp[0].var);
;}
    break;

  case 25:
#line 205 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->qualifiers = yyvsp[0].qual;
				yyval.var = temp;
;}
    break;

  case 26:
#line 215 "VarInfoParser.y"
    {
				yyval.var = merge_variables(yyvsp[-1].var,yyvsp[0].var);
;}
    break;

  case 27:
#line 219 "VarInfoParser.y"
    {
				yyval.var = NULL;
;}
    break;

  case 28:
#line 225 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->dranges = yyvsp[0].drange;
				yyval.var = temp;
;}
    break;

  case 29:
#line 232 "VarInfoParser.y"
    {
				variable* temp;
				temp = new_variable();
				temp->curves = yyvsp[0].curve;
				yyval.var = temp;
;}
    break;

  case 30:
#line 241 "VarInfoParser.y"
    {
				yyval.qual=yyvsp[0].qual
;}
    break;

  case 31:
#line 245 "VarInfoParser.y"
    {
				yyval.qual=yyvsp[0].qual
;}
    break;

  case 32:
#line 251 "VarInfoParser.y"
    {
					yyval.qual = yyvsp[-4].qual;
;}
    break;

  case 33:
#line 257 "VarInfoParser.y"
    {
					yyval.qual = yyvsp[-1].qual;
;}
    break;

  case 35:
#line 266 "VarInfoParser.y"
    {
				yyval.qual = yyvsp[0].qual;
;}
    break;

  case 36:
#line 272 "VarInfoParser.y"
    {
				yyval.qual = merge_qualifiers(yyvsp[-1].qual,yyvsp[0].qual);
;}
    break;

  case 37:
#line 276 "VarInfoParser.y"
    {
				yyval.qual = NULL;
;}
    break;

  case 38:
#line 282 "VarInfoParser.y"
    {
				qualifier_type* temp;
				temp = new_qualifier();
				temp->name = yyvsp[0].str;
				yyval.qual = temp;
;}
    break;

  case 39:
#line 289 "VarInfoParser.y"
    {
				qualifier_type* temp;
				temp = new_qualifier();
				temp->value = yyvsp[0].str;
				yyval.qual = temp;
;}
    break;

  case 40:
#line 296 "VarInfoParser.y"
    {
				qualifier_type* temp;
				temp = new_qualifier();
				temp->units = yyvsp[0].str;
				yyval.qual = temp;
;}
    break;

  case 41:
#line 305 "VarInfoParser.y"
    {
				drange* temp;
				temp = new_drange();
				temp->options = yyvsp[-2].curveoption;
				yyval.drange = merge_dranges(yyvsp[-3].drange,temp);
;}
    break;

  case 42:
#line 314 "VarInfoParser.y"
    {
				yyval.drange = yyvsp[-1].drange;
;}
    break;

  case 43:
#line 320 "VarInfoParser.y"
    {
				yyval.drange = merge_dranges(yyvsp[-1].drange,yyvsp[0].drange);
;}
    break;

  case 44:
#line 324 "VarInfoParser.y"
    {
				yyval.drange = NULL;
;}
    break;

  case 45:
#line 330 "VarInfoParser.y"
    {
				drange* temp;
				temp = new_drange();
				temp->name = yyvsp[0].str;
				yyval.drange = temp;
;}
    break;

  case 46:
#line 337 "VarInfoParser.y"
    {
				drange* temp;
				temp = new_drange();
				temp->description = yyvsp[0].str;
				yyval.drange = temp;
;}
    break;

  case 47:
#line 346 "VarInfoParser.y"
    {
				yyval.curveoption = link_options(yyvsp[-1].curveoption,yyvsp[0].curveoption);
;}
    break;

  case 48:
#line 350 "VarInfoParser.y"
    {
				yyval.curveoption = NULL;
;}
    break;

  case 49:
#line 356 "VarInfoParser.y"
    {
				yyval.curveoption = yyvsp[-1].curveoption;
;}
    break;

  case 50:
#line 360 "VarInfoParser.y"
    {
				yyval.curveoption = yyvsp[-3].curveoption;
;}
    break;

  case 51:
#line 366 "VarInfoParser.y"
    {
				yyval.curveoption = merge_options(yyvsp[-1].curveoption,yyvsp[0].curveoption);
;}
    break;

  case 52:
#line 370 "VarInfoParser.y"
    {
				yyval.curveoption = NULL;
;}
    break;

  case 53:
#line 376 "VarInfoParser.y"
    {
				curveoption* temp;
				temp = new_option();
				temp->name = yyvsp[0].str;
				yyval.curveoption = temp;
;}
    break;

  case 54:
#line 383 "VarInfoParser.y"
    {
				curveoption* temp;
				temp = new_option();
				temp->value = yyvsp[0].str;
				yyval.curveoption = temp;
;}
    break;

  case 55:
#line 390 "VarInfoParser.y"
    {
				curveoption* temp;
				temp = new_option();
				temp->description = yyvsp[0].str;
				yyval.curveoption = temp;
;}
    break;

  case 56:
#line 397 "VarInfoParser.y"
    {
				curveoption* temp;
				temp = new_option();
				temp->alarm = yyvsp[0].str;
				yyval.curveoption = temp;
;}
    break;

  case 57:
#line 405 "VarInfoParser.y"
    {
				curve* temp;
				temp = new_curve();
				temp->coefs = yyvsp[-2].coef;
				yyval.curve = merge_curves(yyvsp[-3].curve,temp);
;}
    break;

  case 58:
#line 414 "VarInfoParser.y"
    {
	yyval.curve = yyvsp[-1].curve;
;}
    break;

  case 59:
#line 420 "VarInfoParser.y"
    {
	yyval.curve = merge_curves(yyvsp[-1].curve,yyvsp[0].curve);
;}
    break;

  case 60:
#line 424 "VarInfoParser.y"
    {
	yyval.curve = NULL;
;}
    break;

  case 61:
#line 430 "VarInfoParser.y"
    {
	curve* temp;
				temp = new_curve();
				temp->name = yyvsp[0].str;
				yyval.curve = temp;
;}
    break;

  case 62:
#line 437 "VarInfoParser.y"
    {
	curve* temp;
				temp = new_curve();
				temp->description = yyvsp[0].str;
				yyval.curve = temp;
;}
    break;

  case 63:
#line 446 "VarInfoParser.y"
    {
	yyval.coef = link_coefs(yyvsp[-1].coef,yyvsp[0].coef);
;}
    break;

  case 64:
#line 450 "VarInfoParser.y"
    {
	yyval.coef = NULL;
;}
    break;

  case 65:
#line 456 "VarInfoParser.y"
    {
	yyval.coef = yyvsp[-1].coef;
;}
    break;

  case 66:
#line 460 "VarInfoParser.y"
    {
	yyval.coef = yyvsp[-3].coef;
;}
    break;

  case 67:
#line 464 "VarInfoParser.y"
    {
	yyval.coef = yyvsp[-1].coef;
;}
    break;

  case 68:
#line 470 "VarInfoParser.y"
    {
	yyval.coef = merge_coefs(yyvsp[-1].coef,yyvsp[0].coef);
;}
    break;

  case 69:
#line 474 "VarInfoParser.y"
    {
	yyval.coef = NULL;
;}
    break;

  case 70:
#line 480 "VarInfoParser.y"
    {
	coef* temp;
				temp = new_coef();
				temp->exponent = yyvsp[0].str;
				yyval.coef = temp;
;}
    break;

  case 71:
#line 487 "VarInfoParser.y"
    {
	coef* temp;
				temp = new_coef();
				temp->value = yyvsp[0].str;
				yyval.coef = temp;
;}
    break;

  case 72:
#line 494 "VarInfoParser.y"
    {
	coef* temp;
				temp = new_coef();
				temp->description = yyvsp[0].str;
				yyval.coef = temp;
;}
    break;

  case 73:
#line 502 "VarInfoParser.y"
    {
	yyval.qual= link_qualifiers(yyvsp[-1].qual,yyvsp[0].qual);
;}
    break;

  case 74:
#line 506 "VarInfoParser.y"
    {
	yyval.qual= NULL;
;}
    break;


    }

/* Line 1010 of yacc.c.  */
#line 1968 "VarInfoParser.tab.c"

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


#line 511 "VarInfoParser.y"

