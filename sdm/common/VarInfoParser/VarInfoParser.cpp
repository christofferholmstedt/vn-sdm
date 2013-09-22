#include <string.h>
#include "VarInfoParser.h"

VarInfoParser::VarInfoParser():varTree(NULL)
{
}

/*
 *  Destructor should free the varTree object which is a heap-allocated object, using delete_variable.
 */
VarInfoParser::~VarInfoParser()
{
	if (varTree != NULL)
	{
		delete_variable(varTree);
		varTree = NULL;
	}
}
/*
 *  Sets the VarInfo to parse, as returned from a SDMVarInfo message.
 *	PARAMS:
 *		varInfo - The variable information string to parse.
 *	RETURNS:
 *		bool - True upon successful parse, false if a syntax error occurred.
 */
bool VarInfoParser::setVarInfo(char* varInfo)
{
	if (varInfo == NULL) return false;
	//varTree is a heap-allocated object!
	if (varTree)
	{
		delete_variable(varTree);
		varTree = NULL;
	}
	varTree = parseVarInfo(varInfo);
	if (varTree == NULL)
		return false;
	return true;
}

/*******************BEGIN GET ATTRIBUTE FUNCTIONS********************/

/*
 *  These functions get the specified attribute of the variable, through the buffer parameter.
 *	Returns:
 *		bool - True if the parameter was set, false otherwise.
 */
bool VarInfoParser::getLength(char *lengthBuffer)
{
	if (varTree != NULL && varTree->length!=NULL && lengthBuffer!=NULL)
	{
		strcpy(lengthBuffer, varTree->length);
		return true;
	}
	return false;
}
bool VarInfoParser::getKind(char *kindBuffer)
{
	if (varTree != NULL && varTree->kind!=NULL && kindBuffer!=NULL)
	{
		strcpy(kindBuffer, varTree->kind);
		return true;
	}
	return false;
}
bool VarInfoParser::getName(char *nameBuffer)
{
	if (varTree != NULL && varTree->name!=NULL && nameBuffer!=NULL)
	{
		strcpy(nameBuffer, varTree->name);
		return true;
	}
	return false;
}
bool VarInfoParser::getId(char *idBuffer)
{
	if (varTree != NULL && varTree->id!=NULL && idBuffer!=NULL)
	{
		strcpy(idBuffer, varTree->id);
		return true;
	}
	return false;
}
bool VarInfoParser::getRangeMin(char *rminBuffer)
{
	if (varTree != NULL && varTree->range_min!=NULL && rminBuffer!=NULL)
	{
		strcpy(rminBuffer, varTree->range_min);
		return true;
	}
	return false;
}
bool VarInfoParser::getRangeMax(char *rmaxBuffer)
{
	if (varTree != NULL && varTree->range_max!=NULL && rmaxBuffer!=NULL)
	{
		strcpy(rmaxBuffer, varTree->range_max);
		return true;
	}
	return false;
}
bool VarInfoParser::getDefaultValue(char *dvalueBuffer)
{
	if (varTree != NULL && varTree->default_value!=NULL && dvalueBuffer!=NULL)
	{
		strcpy(dvalueBuffer, varTree->default_value);
		return true;
	}
	return false;
}
bool VarInfoParser::getPrecision(char *precisionBuffer)
{
	if (varTree != NULL && varTree->precision!=NULL && precisionBuffer!=NULL)
	{
		strcpy(precisionBuffer, varTree->precision);
		return true;
	}
	return false;
}
bool VarInfoParser::getUnits(char *unitsBuffer)
{
	if (varTree != NULL && varTree->units!=NULL && unitsBuffer!=NULL)
	{
		strcpy(unitsBuffer, varTree->units);
		return true;
	}
	return false;
}
bool VarInfoParser::getAccuracy(char *accBuffer)
{
	if (varTree != NULL && varTree->accuracy!=NULL && accBuffer!=NULL)
	{
		strcpy(accBuffer, varTree->accuracy);
		return true;
	}
	return false;
}
bool VarInfoParser::getScaleFactor(char *sfactorBuffer)
{
	if (varTree != NULL && varTree->scale_factor!=NULL && sfactorBuffer!=NULL)
	{
		strcpy(sfactorBuffer, varTree->scale_factor);
		return true;
	}
	return false;
}
bool VarInfoParser::getScaleUnits(char *sunitsBuffer)
{
	if (varTree != NULL && varTree->scale_units!=NULL && sunitsBuffer!=NULL)
	{
		strcpy(sunitsBuffer, varTree->scale_units);
		return true;
	}
	return false;
}
bool VarInfoParser::getFormat(char *formatBuffer)
{
	if (varTree != NULL && varTree->format!=NULL && formatBuffer!=NULL)
	{
		strcpy(formatBuffer, varTree->format);
		return true;
	}
	return false;
}
bool VarInfoParser::getDescription(char *descBuffer)
{
	if (varTree != NULL && varTree->description!=NULL && descBuffer!=NULL)
	{
		strcpy(descBuffer, varTree->description);
		return true;
	}
	return false;
}
/*******************END GET ATTRIBUTE FUNCTIONS********************/


/*
 *  Finds the value associated with a name for a variable qualifier.  The first matching value is returned.
 *	Params:
 *		valueBuffer - [OUTPUT] The value associated with the given name, this buffer should be at least 33 bytes.
 *		nameBuffer - The name corresponding to the desired value.
 *	Returns:
 *		bool - Returns true if the qualifier was found, false otherwise.
 */
bool VarInfoParser::getQualValueByName(char *valueBuffer, const char *nameBuffer)
{
	if (valueBuffer == NULL || nameBuffer == NULL || varTree == NULL) return false;
	//Search the qualifier list
	for (qualifier_type* Curr = varTree->qualifiers; Curr != NULL; Curr = Curr->next)
	{
		if (Curr->name == NULL) continue;
		if (!strcmp(Curr->name, nameBuffer))
		{
			strcpy(valueBuffer, Curr->value);
			return true;
		}	
	}
	return false;
}
/*
 *  Determines whether the Variable has qualifiers.
 *	Returns:
 *		bool - True if the variables has qualifiers, false otherwise.
 */
bool VarInfoParser::hasQualifiers()
{
	if (varTree == NULL) return false;
	return varTree->qualifiers==NULL ? false : true;
}
/*
 *  Returns the number of option elements that are associated with the variable's discrete range value list.
 *	Returns:
 *		int - The number of option elements, or zero if one exist.
 */
int VarInfoParser::getDrangeSize()
{
	if (varTree == NULL || varTree->dranges == NULL) return 0;
	int count = 0;
	for (curveoption* Curr = varTree->dranges->options; Curr != NULL; Curr = Curr->next, count++)
		;
	return count;
}
/*
 *  Gets a name and a value for an option appearing in the position in the drange list defined by the optNum argument.
 *	Params:
 *		optNum - The one-based position counter of the option to get.
 *		name - A pointer to a buffer for storing the option name.
 *		value - A pointer to a buffer for storing the value of the option.
 *	Returns:
 *		bool - True if the optNum is a valid option number that can return values, false otherwise.
 */
bool VarInfoParser::getOptionNumber(int optNum, char *name, char *value)
{
	if (varTree == NULL || varTree->dranges == NULL || (name == NULL && value == NULL)) return false;
	curveoption* Curr;
	int count = 1;
	//Find the option
	for (Curr = varTree->dranges->options; Curr != NULL && count < optNum; Curr = Curr->next, count++)
		;
	//If the optNum was too large to find
	if (count != optNum || Curr == NULL)
		return false;
	if (name != NULL)
		strcpy(name, Curr->name);
	if (value != NULL)
		strcpy(value, Curr->value);
	return true;
	
}

