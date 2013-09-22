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
/* Line 1285 of yacc.c.  */
#line 253 "VarInfoParser.tab.h"
# define yystype YYSTYPE /* obsolescent; will be withdrawn */
# define YYSTYPE_IS_DECLARED 1
# define YYSTYPE_IS_TRIVIAL 1
#endif

extern YYSTYPE VarInfoParserlval;



