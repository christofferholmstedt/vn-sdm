#ifndef __VAR_INFO_PARSER_H_
#define __VAR_INFO_PARSER_H_
extern "C"
{
	#include "Variable.h"
	#include "../xTEDS/xTEDSParser.h"
}

/* The VarInfoParser class is a utility class for extracting the variable information data from SDMVarInfo messages. */

class VarInfoParser
{
public:
	VarInfoParser();
	~VarInfoParser();
	VarInfoParser(const VarInfoParser &right);
	VarInfoParser& operator=(const VarInfoParser &right);
	bool setVarInfo(char* varInfo);			//Used to set the VarInfo return string to parse
	bool getLength(char *lengthBuffer);		//Used to get the length attribute of the variable
	bool getKind(char *kindBuffer);			//Used to get the kind attribute of the variable
	bool getName(char *nameBuffer);			//Used to get the name attribute of the variable
	bool getId(char *idBuffer);			//Used to get the id attribute of the variable
	bool getRangeMin(char *rminBuffer);		//Used to get the rangeMin attribute of the variable
	bool getRangeMax(char *rmaxBuffer);		//Used to get the rangeMax attribute of the variable
	bool getDefaultValue(char *dvalueBuffer);	//Used to get the defaultValue attribute of the variable
	bool getPrecision(char *precisionBuffer);	//Used to get the precision attribute of the variable
	bool getUnits(char *unitsBuffer);		//Used to get the units attribute of the variable
	bool getAccuracy(char *accBuffer);		//Used to get the accuracy attribute of the variable
	bool getScaleFactor(char *sfactorBuffer);	//Used to get the scaleFactor attribute of the variable
	bool getScaleUnits(char *sunitsBuffer);		//Used to get the scaleUnits attribute of the variable
	bool getFormat(char *formatBuffer);		//Used to get the format attribute of the variable
	bool getDescription(char *descBuffer);		//Used to get the description attribute of the variable
	bool getQualValueByName(char *valueBuffer, const char *nameBuffer);	//Get qualifier value by name
	bool hasQualifiers();				//Determines whether the variable definition has qualifiers
	int getDrangeSize();				//Returns the number of options associated with a Drange
	bool getOptionNumber(int optNum, char *name, char *value);	//Get option element name/value information
private:
	variable* varTree;
};

#endif

