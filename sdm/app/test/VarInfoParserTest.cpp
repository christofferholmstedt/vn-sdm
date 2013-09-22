#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../common/VarInfoParser/VarInfoParser.h"

int main(int argc, char ** argv)
{
	VarInfoParser parser;
	char variable[] = "<Variable format=\"UINT08\" kind=\"Component\" name=\"ComponentKey\" length=\"129\" description=\"The component key for a device\" rangeMin=\"3.2\" rangeMax=\"5.5\" defaultValue=\"df1\" precision=\".0001\" units=\"text\" accuracy=\".01011\" scaleFactor=\"3.2\" scaleUnits=\"sU\">\n\t<Qualifier name=\"Qual1\" value=\"13\"/>\n\t<Qualifier name=\"Qual2\" value=\"14\"/>\n\t<Qualifier name=\"Qual3\" value=\"15\"/>\n\t<Qualifier name=\"Qual4\" value=\"16\"/>\n\t<Drange name=\"amActivityPriorityEnum\">\n\t\t<Option value=\"0\" name=\"LOW\"/>\n\t\t<Option value=\"1\" name=\"MEDIUM\"/>\n\t\t<Option value=\"2\" name=\"HIGH\"/>\n\t</Drange>\n</Variable>";
	//char variable[] = "<Variable name=\"amActivityPriority\" kind=\"tbd\" format=\"UINT16\"></Variable>";
	//char variable[] = " <Variable name=\"myVar\" kind=\"tbd\" format=\"UINT16\"> <Qualifier name=\"Qual1\" value=\"13\"/> <Qualifier name=\"Qual2\" value=\"14\"/> <Qualifier name=\"Qual3\" value=\"15\"/> <Qualifier name=\"Qual4\" value=\"16\"/> </Variable> ";
	
	printf("Parsing this variable definition: \n%s\n\n",variable);
	
	if (parser.setVarInfo(variable))
		printf("Parse succedded.\n");
	else
		printf("Parse failed.\n");
	//
	//Output the info about the variable
	//
	char buf[128];
	if (parser.getName(buf))
		printf("Name is %s\n",buf);
	if (parser.getLength(buf))
		printf("Length is %s\n",buf);
	if (parser.getKind(buf))
		printf("Kind is %s\n",buf);
	if (parser.getId(buf))
		printf("Id is %s\n",buf);
	if (parser.getRangeMax(buf))
		printf("RangeMax is %s\n",buf);
	if (parser.getRangeMin(buf))
		printf("RangeMin is %s\n",buf);
	if (parser.getDefaultValue(buf))
		printf("Default value is %s\n",buf);
	if (parser.getPrecision(buf))
		printf("Precision is %s\n",buf);
	if (parser.getUnits(buf))
		printf("Units is %s\n",buf);
	if (parser.getAccuracy(buf))
		printf("Accuracy is %s\n",buf);
	if (parser.getScaleFactor(buf))
		printf("Scale factor is %s\n",buf);
	if (parser.getScaleUnits(buf))
		printf("Scale units is %s\n",buf);
	if (parser.getFormat(buf))
		printf("Format is %s\n",buf);
	if (parser.getDescription(buf))
		printf("Description is %s\n",buf);
	//
	//Check for qualifiers
	//
	if (parser.hasQualifiers())
	{
		char value[33];
		parser.getQualValueByName(value,"Qual1");
		printf("Value associated with Qual1 is %s\n",value);
		parser.getQualValueByName(value,"Qual2");
		printf("Value associated with Qual2 is %s\n",value); 
		parser.getQualValueByName(value,"Qual3");
		printf("Value associated with Qual3 is %s\n",value); 
		parser.getQualValueByName(value,"Qual4");
		printf("Value associated with Qual4 is %s\n",value); 
	}
	if (parser.getDrangeSize() > 0)
	{
		printf("Variable has %d option elements\n",parser.getDrangeSize());
		char nameBuf[33];
		char valueBuf[33];
		//Loop going under/over the bounds of the range to assure the function won't return anything
		for (int i = -3; i <= parser.getDrangeSize()+3; i++)
		{
			if (parser.getOptionNumber(i, nameBuf, valueBuf))
				printf("Option %d - Name is %s value is %s\n", i, nameBuf, valueBuf);
		}
	}
	//Re-parse if running valgrind to check for memory leaks
	parser.setVarInfo(variable);
	
	return 0;
}
