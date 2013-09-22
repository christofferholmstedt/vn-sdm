#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../../../common/message/SDMVarReq.h"
#include "../../../common/message/SDMVarInfo.h"
#include "../../../common/MessageManager/MessageManager.h"
#include "xTEDSPoster.h"

const long myPort = 4756;
enum  {TEST1, TEST2, TEST3, TEST4, TEST5, TEST6, TEST7, TEST8, TEST9, TEST10, TEST11, TEST12};
xTEDSPoster Poster;
const int NUM_TESTS = 12;

const char *Test1Correct = "<Variable name=\"Test1\" kind=\"Time\" format=\"UINT32\" units=\"Seconds\" invalidValue=\"123\"/>";

const char *Test2Correct = "<Variable name=\"Test2\" kind=\"SubS\" format=\"UINT32\" units=\"Counts\" scaleFactor=\".00000002083\" scaleUnits=\"Seconds\"/>";

const char *Test3Correct = "<Variable name=\"Test3\" kind=\"boolean\" format=\"UINT08\">\n\
\t<Drange name=\"SolutionEnum\">\n\
\t\t<Option name=\"Yes\" value=\"1\"/>\n\
\t</Drange>\n\
</Variable>";

const char *Test4Correct = "<Variable name=\"Test4\" kind=\"boolean\" format=\"UINT08\" invalidValue=\"word\">\n\
\t<Drange name=\"SolutionEnum\">\n\
\t\t<Option name=\"Test1\" value=\"1d\"/>\n\
\t\t<Option name=\"Test2\" value=\"177\"/>\n\
\t\t<Option name=\"Test3\" value=\"156\"/>\n\
\t\t<Option name=\"Test4\" value=\"12\"/>\n\
\t\t<Option name=\"Test5\" value=\"1fe\"/>\n\
\t</Drange>\n\
</Variable>";

const char *Test5Correct = "<Variable name=\"Test5\" kind=\"boolean\" format=\"UINT08\">\n\
\t<Drange name=\"SolutionEnum\">\n\
\t\t<Option name=\"Yes\" value=\"1\"/>\n\
\t\t<Option name=\"No\" value=\"0\"/>\n\
\t</Drange>\n\
</Variable>";

const char *Test6Correct = "<Variable name=\"Test6\" kind=\"DataQuality\" format=\"UINT08\" rangeMin=\"-100.0\" rangeMax=\"100.0\" precision=\"2\" accuracy=\".0001\" rLow=\"10.0\" rHigh=\"20.0\" yLow=\"0.0\" yHigh=\"1.0\">\n\
\t<Drange name=\"DataQualityEnum\" description=\"None\">\n\
\t\t<Option name=\"dataBad\" value=\"0\" description=\"data is garbage or NaN.\" alarm=\"1\"/>\n\
\t\t<Option name=\"dataPoor\" value=\"1\"/>\n\
\t\t<Option name=\"dataGood\" value=\"2\" description=\"data is good.\"/>\n\
\t</Drange>\n\
\t<Qualifier name=\"hello\" value=\"3\" />\n\
\t\t<Qualifier name=\"TestQual\" value=\"45\" />\n\
\t\t<Qualifier name=\"TestQual2\" value=\"55\" units=\"FakeUnits\" />\n\
\t<Location x=\"5\" y=\"5\" z=\"-1\" units=\"cm\" />\n\
\t<Orientation axis=\"X\" angle=\"45\" units=\"degrees\" />\n\
\t<Orientation axis=\"Y\" angle=\"45\" units=\"degrees\" />\n\
</Variable>";

const char *Test7Correct = "<Variable name=\"Test7\" kind=\"SunCos\" format=\"FLOAT32\">\n\
\t<Curve name=\"testCurve\" description=\"Used for testing.\">\n\
\t\t<Coef exponent=\"1.0\" value=\"1.0\"/>\n\
\t\t<Coef exponent=\"3.0\" value=\"3.0\"/>\n\
\t</Curve>\n\
\t<Qualifier name=\"TestQual\" value=\"45\" />\n\
\t\t<Qualifier name=\"TestQual2\" value=\"55\" units=\"FakeUnits\" />\n\
\t<Location x=\"5\" y=\"5\" z=\"-1\" units=\"cm\" />\n\
\t<Orientation axis=\"X\" angle=\"45\" units=\"degrees\" />\n\
\t<Orientation axis=\"Y\" angle=\"45\" units=\"degrees\" />\n\
\t<Orientation axis=\"Z\" angle=\"0\" units=\"degrees\" />\n\
</Variable>";

const char *Test8Correct = "<Variable name=\"Test8\" kind=\"SunCos\" format=\"FLOAT32\">\n\
\t<Curve name=\"testCurve\" description=\"Used for testing.\">\n\
\t\t<Coef exponent=\"1.0\" value=\"14.0\"/>\n\
\t\t<Coef exponent=\"3.0\" value=\"3.0\"/>\n\
\t\t<Coef exponent=\"16.0\" value=\"155.0\"/>\n\
\t\t<Coef exponent=\"14.0\" value=\"143.0\"/>\n\
\t\t<Coef exponent=\"13.0\" value=\"1662.0\"/>\n\
\t\t<Coef exponent=\"12.0\" value=\"11.0\"/>\n\
\t</Curve>\n\
\t<Qualifier name=\"TestQual\" value=\"45\" />\n\
\t\t<Qualifier name=\"TestQual2\" value=\"55\" units=\"FakeUnits\" />\n\
\t<Location x=\"5\" y=\"5\" z=\"-1\" units=\"cm\" />\n\
\t<Orientation axis=\"Y\" angle=\"45\" units=\"degrees\" />\n\
\t<Orientation axis=\"Z\" angle=\"0\" units=\"degrees\" />\n\
</Variable>";

const char *Test9Correct = "<Variable name=\"Test9\" kind=\"SunCos\" format=\"FLOAT32\">\n\
\t<Qualifier name=\"TestQual\" value=\"45\" />\n\
\t\t<Qualifier name=\"TestQual2\" value=\"55\" units=\"FakeUnits\" />\n\
\t<Location x=\"5\" y=\"0\" z=\"-1\" units=\"cm\" />\n\
\t<Orientation axis=\"X\" angle=\"-45\" units=\"degrees\" />\n\
\t<Orientation axis=\"Y\" angle=\"45\" units=\"degrees\" />\n\
\t<Orientation axis=\"Z\" angle=\"0\" units=\"degrees\" />\n\
</Variable>";

const char *Test10Correct = "<Variable name=\"Test10\" kind=\"SunCos\" format=\"FLOAT32\">\n\
\t<Location x=\"0\" y=\"5\" z=\"-1\" units=\"cm\" />\n\
\t<Orientation axis=\"X\" angle=\"45\" units=\"degrees\" />\n\
\t<Orientation axis=\"Z\" angle=\"0\" units=\"degrees\" />\n\
</Variable>";

const char *Test11Correct = "<Variable name=\"Test11\" kind=\"SunCos\" format=\"FLOAT32\">\n\
\t<Location x=\"5\" y=\"5\" z=\"1\" units=\"cm\" />\n\
\t<Orientation axis=\"X\" angle=\"45\" units=\"degrees\" />\n\
\t<Orientation axis=\"Y\" angle=\"45\" units=\"degrees\" />\n\
\t<Orientation axis=\"Z\" angle=\"-90\" units=\"degrees\" />\n\
</Variable>";

const char *Test12Correct = "<Variable name=\"Test12\" kind=\"sunLOS\" format=\"FLOAT32\" length=\"2\"/>";


void SigHandler(int);

int main (int argc, char ** argv)
{	
	SDMInit(argc, argv);
	if (Poster.PostxTEDS("xTEDSVariableTests.xml") < 0)
	{
		printf("Error posting xTEDS.\n");
		return 0;
	}
	
	MessageManager mm;
	char buf[BUFSIZE];
	SDMVarInfo varinfo_msg;
	SDMVarReq varreq_msg;
	unsigned char type;
	SDMInit(argc, argv);
	signal(SIGINT,SigHandler);
	char InfoSource[40];
	
	mm.Async_Init(myPort);
	
	printf("-------------------SDMVarReq Tester-------------------\n");
		
	printf("Sending requests...\n");
	
	varreq_msg.destination.setPort(myPort);
	strcpy(varreq_msg.variable, "Test1");
	varreq_msg.id = TEST1;
	varreq_msg.Send();
	strcpy(varreq_msg.variable, "Test2");
	varreq_msg.id = TEST2;
	varreq_msg.Send();
	strcpy(varreq_msg.variable, "Test3");
	varreq_msg.id = TEST3;
	varreq_msg.Send();
	strcpy(varreq_msg.variable, "Test4");
	varreq_msg.id = TEST4;
	varreq_msg.Send();
	strcpy(varreq_msg.variable, "Test5");
	varreq_msg.id = TEST5;
	varreq_msg.Send();
	strcpy(varreq_msg.variable, "Test6");
	varreq_msg.id = TEST6;
	varreq_msg.Send();
	strcpy(varreq_msg.variable, "Test7");
	varreq_msg.id = TEST7;
	varreq_msg.Send();
	strcpy(varreq_msg.variable, "Test8");
	varreq_msg.id = TEST8;
	varreq_msg.Send();
	strcpy(varreq_msg.variable, "Test9");
	varreq_msg.id = TEST9;
	varreq_msg.Send();
	strcpy(varreq_msg.variable, "Test10");
	varreq_msg.id = TEST10;
	varreq_msg.Send();
	strcpy(varreq_msg.variable, "Test11");
	varreq_msg.id = TEST11;
	varreq_msg.Send();
	strcpy(varreq_msg.variable, "Test12");
	varreq_msg.id = TEST12;
	varreq_msg.Send();
	
	int count = 1;
	while (count <= NUM_TESTS)
	{
		type = mm.BlockGetMessage(buf);
		switch (type)
		{
		case SDM_VarInfo:
		{
			long length = varinfo_msg.Unmarshal(buf);
			if (length < 0) continue;
			count ++;
			switch(varinfo_msg.id)
			{
			case TEST1:
				if (strcmp(varinfo_msg.var_xTEDS, Test1Correct))
				{
					printf("***Test1 failed.***\n");
					printf("varinfo_msg.var_xTEDS = \"%s\" \n\nTest1Correct = \"%s\"\n",varinfo_msg.var_xTEDS, Test1Correct);
					return 0;
				}
				else
					printf("Test1 passed.\n");
				break;
			case TEST2:
				if (strcmp(varinfo_msg.var_xTEDS, Test2Correct))
				{
					printf("***Test2 failed.***\n");
					printf("varinfo_msg.var_xTEDS = %s \n\nTest2Correct = %s\n",varinfo_msg.var_xTEDS, Test2Correct);
					return 0;
				}
				else
					printf("Test2 passed.\n");
				break;
			case TEST3:
				if (strcmp(varinfo_msg.var_xTEDS, Test3Correct))
				{
					printf("***Test3 failed.***\n");
					printf("varinfo_msg.var_xTEDS = %s \n\nTest3Correct = %s\n",varinfo_msg.var_xTEDS, Test3Correct);
					return 0;
				}
				else
					printf("Test3 passed.\n");
				break;
			case TEST4:
				if (strcmp(varinfo_msg.var_xTEDS, Test4Correct))
				{
					printf("***Test4 failed.***\n");
					printf("varinfo_msg.var_xTEDS = %s \n\nTest4Correct = %s\n",varinfo_msg.var_xTEDS, Test4Correct);
					return 0;
				}
				else
					printf("Test4 passed.\n");
				break;
			case TEST5:
				if (strcmp(varinfo_msg.var_xTEDS, Test5Correct))
				{
					printf("***Test5 failed.***\n");
					printf("varinfo_msg.var_xTEDS = %s \n\nTest5Correct = %s\n",varinfo_msg.var_xTEDS, Test5Correct);
					return 0;
				}
				else
					printf("Test5 passed.\n");
				break;
			case TEST6:
				if (strcmp(varinfo_msg.var_xTEDS, Test6Correct))
				{
					printf("***Test6 failed.***\n");
					printf("varinfo_msg.var_xTEDS = %s \n\nTest6Correct = %s\n",varinfo_msg.var_xTEDS, Test6Correct);
					return 0;
				}
				else
					printf("Test6 passed.\n");
				break;
			case TEST7:
				if (strcmp(varinfo_msg.var_xTEDS, Test7Correct))
				{
					printf("***Test7 failed.***\n");
					printf("varinfo_msg.var_xTEDS = %s \n\nTest7Correct = %s\n",varinfo_msg.var_xTEDS, Test7Correct);
					return 0;
				}
				else
					printf("Test7 passed.\n");
				break;
			case TEST8:
				if (strcmp(varinfo_msg.var_xTEDS, Test8Correct))
				{
					printf("***Test8 failed.***\n");
					printf("varinfo_msg.var_xTEDS = %s \n\nTest8Correct = %s\n",varinfo_msg.var_xTEDS, Test8Correct);
					return 0;
				}
				else
					printf("Test8 passed.\n");
				break;
			case TEST9:
				if (strcmp(varinfo_msg.var_xTEDS, Test9Correct))
				{
					printf("***Test9 failed.***\n");
					printf("varinfo_msg.var_xTEDS = %s \n\nTest9Correct = %s\n",varinfo_msg.var_xTEDS, Test9Correct);
					return 0;
				}
				else
					printf("Test9 passed.\n");
				break;
			case TEST10:
				if (strcmp(varinfo_msg.var_xTEDS, Test10Correct))
				{
					printf("***Test10 failed.***\n");
					printf("varinfo_msg.var_xTEDS = %s \n\nTest10Correct = %s\n",varinfo_msg.var_xTEDS, Test10Correct);
					return 0;
				}
				else
					printf("Test10 passed.\n");
				break;
			case TEST11:
				if (strcmp(varinfo_msg.var_xTEDS, Test11Correct))
				{
					printf("***Test11 failed.***\n");
					printf("varinfo_msg.var_xTEDS = %s \n\nTest11Correct = %s\n",varinfo_msg.var_xTEDS, Test11Correct);
					return 0;
				}
				else
					printf("Test11 passed.\n");
				break;
			case TEST12:
				if (strcmp(varinfo_msg.var_xTEDS, Test12Correct))
				{
					printf("***Test12 failed.***\n");
					printf("varinfo_msg.var_xTEDS = %s \n\nTest12Correct = %s\n",varinfo_msg.var_xTEDS, Test12Correct);
					return 0;
				}
				else
					printf("Test12 passed.\n");
				break;
			}
			varinfo_msg.source.IDToString(InfoSource, sizeof(InfoSource));
			//printf("(%d) VarInfo received (%s):\n",count++, InfoSource);
			//printf("\t---xTEDS Portion---\n");
			//printf("%s\n\n",varinfo_msg.var_xTEDS);
		}
		break;
		default:
			printf("Unexpected message (%d).\n",type);
		}
	}
	printf("End of SDMVarInfo messages.\n");
	printf("-------------------SDMVarReq Tester Finished-------------------\n");
	return 0;	
}

void SigHandler(int sig)
{
	if (sig == SIGINT)
	{
		Poster.CancelxTEDS();
	}
	_exit(0);
}

