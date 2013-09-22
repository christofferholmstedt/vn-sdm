#include <stdlib.h>
#include <string.h>
#include "Variable.h"

/*
 *  Invokes the variable parser and performs a deep copy of the variable object, freeing the one creating by the
 *  parser and returning the pointer to the copied one.
 *	Params:
 *		var_info - The section of the xTEDS containing the variable definitions to parse.
 *	Returns:
 *		variable* - A pointer to the heap-allocated variable object, this must be deallocated by using delete_variable().
 */
variable* parseVarInfo(char *var_info)
{
	extern void* VarInfoParser_scan_string(const char *str);
	extern void VarInfoParser_delete_buffer(void*);
	extern int VarInfoParserparse();
	int parseResult = -1;
	/*Allocate a string buffer*/
	void *buffer = VarInfoParser_scan_string(var_info);
	/*Perform the parse*/
	parseResult = VarInfoParserparse();
	/*Free the string buffer*/
	VarInfoParser_delete_buffer(buffer);
	if (parseResult == 0)	/*If successful*/
	{
		variable *Copy = variableDeepCopy(getParsedVariable());
		delete_variable(getParsedVariable());
		return Copy;
	}
	return NULL;	
}
/*
 *  Performs a deep copy of a variable structure.
 *	Params:
 *		currVariable - The variable to copy.
 *	Returns:
 *		variable* - The heap-allocated pointer of the variable object copied
 */
variable* variableDeepCopy(variable* currVariable)
{
	if (!currVariable)
		return NULL;
	variable* Copy = (variable*) malloc (sizeof(variable));
	memset(Copy, 0, sizeof(variable));
	/*Copy (heap-allocated) all string fields to the new object*/
	if (currVariable->length) 	Copy->length = strdup(currVariable->length);
	if (currVariable->kind) 	Copy->kind = strdup(currVariable->kind);
	if (currVariable->name) 	Copy->name = strdup(currVariable->name);
	if (currVariable->qualifier) 	Copy->qualifier = strdup(currVariable->qualifier);
	if (currVariable->id) 		Copy->id = strdup(currVariable->id);
	if (currVariable->range_min) 	Copy->range_min = strdup(currVariable->range_min);
	if (currVariable->range_max) 	Copy->range_max = strdup(currVariable->range_max);
	if (currVariable->default_value) Copy->default_value = strdup(currVariable->default_value);
	if (currVariable->precision) 	Copy->precision = strdup(currVariable->precision);
	if (currVariable->units) 	Copy->units = strdup(currVariable->units);
	if (currVariable->accuracy) 	Copy->accuracy = strdup(currVariable->accuracy);
	if (currVariable->scale_factor) Copy->scale_factor = strdup(currVariable->scale_factor);
	if (currVariable->scale_units) 	Copy->scale_units = strdup(currVariable->scale_units);
	if (currVariable->format) 	Copy->format = strdup(currVariable->format);
	if (currVariable->description) 	Copy->description = strdup(currVariable->description);
	if (currVariable->interface_name) Copy->interface_name = strdup(currVariable->interface_name);
	if (currVariable->interface_id) Copy->interface_id = strdup(currVariable->interface_id);
	/*Copy the qualifiers*/
	Copy->qualifiers = qualifierDeepCopy(currVariable->qualifiers);
	/*Copy the curves*/
	Copy->curves = curveDeepCopy(currVariable->curves);
	/*Copy the Dranges*/
	Copy->dranges = drangeDeepCopy(currVariable->dranges);
	/*Copy the next variable*/
	Copy->next = variableDeepCopy(currVariable->next);
	return Copy;
}
/*
 *  Performs a deep copy of a qualifier_type structure.
 *	Params:
 *		currQualifier - The qualifier_type to copy.
 *	Returns:
 *		qualifier_type* - The heap-allocated pointer of the qualifier_type object copied
 */
qualifier_type* qualifierDeepCopy(qualifier_type* currQualifier)
{
	if (!currQualifier)
		return NULL;
	qualifier_type* Copy = (qualifier_type*) malloc (sizeof(qualifier_type));
	memset(Copy, 0, sizeof(qualifier_type));
	/*Copy (heap-allocated) all fields to the new object*/
	if (currQualifier->name) Copy->name = strdup(currQualifier->name);
	if (currQualifier->value) Copy->value = strdup(currQualifier->value);
	if (currQualifier->units) Copy->units = strdup(currQualifier->units);
	/*Copy the next qualifier*/
	Copy->next = qualifierDeepCopy(currQualifier->next);
	return Copy;
}
/*
 *  Performs a deep copy of a curve structure.
 *	Params:
 *		currCurve - The curve to copy.
 *	Returns:
 *		curve* - The heap-allocated pointer of the curve object copied
 */
curve* curveDeepCopy(curve* currCurve)
{
	if (!currCurve)
		return NULL;
	curve* Copy = (curve*) malloc(sizeof(curve));
	memset(Copy, 0, sizeof(curve));
	/*Copy (heap-allocated) all fields to the new object*/
	if (currCurve->name) Copy->name = strdup(currCurve->name);
	if (currCurve->description) Copy->description = strdup(currCurve->description);
	/*Copy the coefficient data*/
	Copy->coefs = coefDeepCopy(currCurve->coefs);
	return Copy;
}
/*
 *  Performs a deep copy of a coef structure.
 *	Params:
 *		currCoef - The coef to copy.
 *	Returns:
 *		variable* - The heap-allocated pointer of the coef object copied
 */
coef* coefDeepCopy(coef* currCoef)
{
	if (!currCoef)
		return NULL;
	coef* Copy = (coef*) malloc(sizeof(coef));
	memset(Copy, 0, sizeof(coef));
	/*Copy (heap-allocated) all fields to the new object*/
	if (currCoef->exponent) Copy->exponent = strdup(currCoef->exponent);
	if (currCoef->value) Copy->value = strdup(currCoef->value);
	if (currCoef->description) Copy->description = strdup(currCoef->description);
	/*Copy the next coef*/
	Copy->next = coefDeepCopy(currCoef->next);
	return Copy;
}
/*
 *  Performs a deep copy of a drange structure.
 *	Params:
 *		currDrange - The drange to copy.
 *	Returns:
 *		variable* - The heap-allocated pointer of the drange object copied
 */
drange* drangeDeepCopy(drange* currDrange)
{
	if (!currDrange)
		return NULL;
	drange* Copy = (drange*) malloc(sizeof(drange));
	memset(Copy, 0, sizeof(drange));
	/*Copy (heap-allocated) all fields to the new object*/
	if (currDrange->name) Copy->name = strdup(currDrange->name);
	if (currDrange->description) Copy->description = strdup(currDrange->description);
	/*Copy the options*/
	Copy->options = optionDeepCopy(currDrange->options);
	return Copy;
}
/*
 *  Performs a deep copy of an option structure.
 *	Params:
 *		currOption - The option to copy.
 *	Returns:
 *		option* - The heap-allocated pointer of the option object copied
 */
curveoption* optionDeepCopy(curveoption* currOption)
{
	if (!currOption)
		return NULL;
	curveoption* Copy = (curveoption*) malloc(sizeof(curveoption));
	memset(Copy, 0, sizeof(curveoption));
	/*Copy (heap-allocated) all fields to the new object*/
	if (currOption->name) Copy->name = strdup(currOption->name);
	if (currOption->value) Copy->value = strdup(currOption->value);
	if (currOption->description) Copy->description = strdup(currOption->description);
	if (currOption->alarm) Copy->alarm = strdup(currOption->alarm);
	/*Copy the next option*/
	Copy->next = optionDeepCopy(currOption->next);
	return Copy;
}
