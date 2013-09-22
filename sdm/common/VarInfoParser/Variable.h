#ifndef __VARIABLE_H_
#define __VARIABLE_H_
#include "../xTEDS/xTEDSParser.h"
#include <stdlib.h>
/*
 *Utility functions for parsing and copying a variable definitions section of an xTEDS
 *The user should use the VarInfoParser object, not these functions.
 */

variable* parseVarInfo(char *var_info);
variable* variableDeepCopy(variable* currVariable);
qualifier_type* qualifierDeepCopy(qualifier_type* currQualifier);
curve* curveDeepCopy(curve* currCurve);
coef* coefDeepCopy(coef* currCoef);
drange* drangeDeepCopy(drange* currDrange);
curveoption* optionDeepCopy(curveoption* currOption);

#endif
