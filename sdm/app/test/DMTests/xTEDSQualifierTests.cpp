#include <string.h>
#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include "../../../common/message/SDMReqReg.h"
#include "../../../common/message/SDMRegInfo.h"
#include "../../../common/MessageManager/MessageManager.h"
#include "xTEDSPoster.h"

const long myPort = 4556;
enum  {TEST1, TEST2, TEST3, TEST4, TEST5, TEST6, TEST7, TEST8, TEST9, TEST10, TEST11, TEST12};
xTEDSPoster Poster;
const int NUM_TESTS = 10;

const char *Test1Correct = "<Notification>\n\t<DataMsg name=\"Test1\" id=\"257\" msgArrival=\"PERIODIC\" msgRate=\"1.000000\">\n\t\t<Qualifier name=\"telemetryLevel1\" value=\"1\" />\n\t\t<VariableRef name=\"Time\"/>\n\t\t<VariableRef name=\"SubS\"/>\n\t\t<VariableRef name=\"HCB_Current\"/>\n\t\t<VariableRef name=\"HCB_State\"/>\n\t</DataMsg>\n</Notification>";

const char *Test2Correct = "<Notification>\n\t<DataMsg name=\"Test2\" id=\"258\" msgArrival=\"EVENT\">\n\t\t<Qualifier name=\"telemetryLevel2\" value=\"2\" />\n\t\t<VariableRef name=\"Time\"/>\n\t\t<VariableRef name=\"SubS\"/>\n\t\t<VariableRef name=\"HCB_State\"/>\n\t</DataMsg>\n</Notification>";

const char *Test3Correct = "<Command>\n\t<CommandMsg name=\"Test3\" id=\"259\">\n\t\t<Qualifier name=\"telemetryLevel3\" value=\"3\" />\n\t\t<VariableRef name=\"HCB_ID\"/>\n\t\t<VariableRef name=\"Cmd_State\"/>\n\t</CommandMsg>\n</Command>";

const char *Test4Correct = "<Notification>\n\t<DataMsg name=\"Test4\" id=\"513\" msgArrival=\"PERIODIC\" msgRate=\"1.000000\">\n\t\t<Qualifier name=\"telemetryLevel\" value=\"1\" />\n\t\t<VariableRef name=\"Time\"/>\n\t\t<VariableRef name=\"SubS\"/>\n\t\t<VariableRef name=\"EndpointPowerState\"/>\n\t\t<VariableRef name=\"EndpointVoltage\"/>\n\t\t<VariableRef name=\"EndpointCurrent\"/>\n\t</DataMsg>\n</Notification>";

const char *Test5Correct = "<Notification>\n\t<DataMsg name=\"Test5\" id=\"514\" msgArrival=\"EVENT\">\n\t\t<Qualifier name=\"telemetryLevel\" value=\"1\" />\n\t\t<VariableRef name=\"Time\"/>\n\t\t<VariableRef name=\"SubS\"/>\n\t\t<VariableRef name=\"EndpointPowerState\"/>\n\t</DataMsg>\n</Notification>";

const char *Test6Correct = "<Command>\n\t<CommandMsg name=\"Test6\" id=\"515\">\n\t\t<Qualifier name=\"TestQual\" value=\"val\" />\n\t\t<Qualifier name=\"TestQual2\" value=\"val2\" />\n\t\t<VariableRef name=\"EndpointID\"/>\n\t\t<VariableRef name=\"SoftCurrentLimit\"/>\n\t</CommandMsg>\n\t<FaultMsg name=\"TestFault\" id=\"546\" description=\"This tests fault messages.\">\n\t</FaultMsg>\n</Command>";

const char *Test7Correct = "<Command>\n\t<CommandMsg name=\"Test7\" id=\"516\">\n\t\t<Qualifier name=\"TestQual\" value=\"val\" />\n\t\t<Qualifier name=\"TestQual2\" value=\"val2\" />\n\t\t<Qualifier name=\"TestQual3\" value=\"val3\" />\n\t\t<Qualifier name=\"TestQual4\" value=\"val4\" />\n\t\t<VariableRef name=\"EndpointID\"/>\n\t\t<VariableRef name=\"SetCurrent\"/>\n\t</CommandMsg>\n</Command>";

const char *Test8Correct = "<Request>\n\t<CommandMsg name=\"Test8\" id=\"1025\">\n\t\t<Qualifier name=\"TestQual\" value=\"val\" />\n\t\t<Qualifier name=\"TestQual2\" value=\"val2\" />\n\t</CommandMsg>\n\t<DataMsg name=\"Test9\" id=\"1026\" msgArrival=\"EVENT\">\n\t\t<Qualifier name=\"TestQual\" value=\"val\" />\n\t\t<Qualifier name=\"TestQual2\" value=\"val2\" />\n\t\t<VariableRef name=\"Time\"/>\n\t\t<VariableRef name=\"SubS\"/>\n\t\t<VariableRef name=\"TempRH\"/>\n\t\t<VariableRef name=\"TempRE\"/>\n\t</DataMsg>\n\t<FaultMsg name=\"ReqFault\" id=\"1046\" description=\"testing request fault\">\n\t\t<Qualifier name=\"FaultQual\" value=\"45\" />\n\t\t<VariableRef name=\"SubS\"/>\n\t</FaultMsg>\n</Request>";

const char *Test9Correct = "<Request>\n\t<CommandMsg name=\"Test8\" id=\"1025\">\n\t\t<Qualifier name=\"TestQual\" value=\"val\" />\n\t\t<Qualifier name=\"TestQual2\" value=\"val2\" />\n\t</CommandMsg>\n\t<DataMsg name=\"Test9\" id=\"1026\" msgArrival=\"EVENT\">\n\t\t<Qualifier name=\"TestQual\" value=\"val\" />\n\t\t<Qualifier name=\"TestQual2\" value=\"val2\" />\n\t\t<VariableRef name=\"Time\"/>\n\t\t<VariableRef name=\"SubS\"/>\n\t\t<VariableRef name=\"TempRH\"/>\n\t\t<VariableRef name=\"TempRE\"/>\n\t</DataMsg>\n\t<FaultMsg name=\"ReqFault\" id=\"1046\" description=\"testing request fault\">\n\t\t<Qualifier name=\"FaultQual\" value=\"45\" />\n\t\t<VariableRef name=\"SubS\"/>\n\t</FaultMsg>\n</Request>";

const char *Test10Correct = "<Notification>\n\t<DataMsg name=\"Test10\" id=\"1027\" msgArrival=\"PERIODIC\" msgRate=\"1.000000\">\n\t\t<Qualifier name=\"telemetryLevel\" value=\"1\" />\n\t\t<VariableRef name=\"Time\"/>\n\t\t<VariableRef name=\"SubS\"/>\n\t\t<VariableRef name=\"TempRH\"/>\n\t\t<VariableRef name=\"TempRE\"/>\n\t</DataMsg>\n</Notification>";

void SigHandler(int);

int main (int argc, char ** argv)
{	
	SDMInit(argc, argv);
	if (Poster.PostxTEDS("xTEDSQualifierTests.xml") < 0)
	{
		printf("Error posting xTEDS.\n");
		return 0;
	}
	sleep(1);
	MessageManager mm;
	char buf[BUFSIZE];
	SDMRegInfo reginfo_msg;
	SDMReqReg reqreg_msg;
	unsigned char type;
	SDMInit(argc, argv);
	signal(SIGINT,SigHandler);
	char InfoSource[40];
	
	mm.Async_Init(myPort);
	
	printf("-------------------Qualifiers Tester-------------------\n");
		
	printf("Sending requests...\n");
	strcpy(reqreg_msg.device,"xTEDSQualifierTests");
	reqreg_msg.destination.setPort(myPort);
	strcpy(reqreg_msg.item_name, "Test1");
	reqreg_msg.id = TEST1;
	reqreg_msg.Send();
	strcpy(reqreg_msg.item_name, "Test2");
	reqreg_msg.id = TEST2;
	reqreg_msg.Send();
	strcpy(reqreg_msg.item_name, "Test3");
	reqreg_msg.id = TEST3;
	reqreg_msg.Send();
	strcpy(reqreg_msg.item_name, "Test4");
	reqreg_msg.id = TEST4;
	reqreg_msg.Send();
	strcpy(reqreg_msg.item_name, "Test5");
	reqreg_msg.id = TEST5;
	reqreg_msg.Send();
	strcpy(reqreg_msg.item_name, "Test6");
	reqreg_msg.id = TEST6;
	reqreg_msg.Send();
	strcpy(reqreg_msg.item_name, "Test7");
	reqreg_msg.id = TEST7;
	reqreg_msg.Send();
	strcpy(reqreg_msg.item_name, "Test8");
	reqreg_msg.id = TEST8;
	reqreg_msg.Send();
	strcpy(reqreg_msg.item_name, "Test9");
	reqreg_msg.id = TEST9;
	reqreg_msg.Send();
	strcpy(reqreg_msg.item_name, "Test10");
	reqreg_msg.id = TEST10;
	reqreg_msg.Send();
	
	int count = 1;
	while (count <= NUM_TESTS)
	{
		type = mm.BlockGetMessage(buf);
		switch (type)
		{
		case SDM_RegInfo:
		{
			long length = reginfo_msg.Unmarshal(buf);
			if (length < 0) continue;
			count ++;
			switch(reginfo_msg.id)
			{
			case TEST1:
				if (strcmp(reginfo_msg.xTEDS_section, Test1Correct))
				{
					printf("***Test1 failed.***\n");
					printf("reginfo_msg.xTEDS_section = \"%s\" \n\nTest1Correct = \"%s\"\n",reginfo_msg.xTEDS_section, Test1Correct);
					return 0;
				}
				else
					printf("Test1 passed.\n");
				break;
			case TEST2:
				if (strcmp(reginfo_msg.xTEDS_section, Test2Correct))
				{
					printf("***Test2 failed.***\n");
					printf("reginfo_msg.xTEDS_section = %s \n\nTest2Correct = %s\n",reginfo_msg.xTEDS_section, Test2Correct);
					return 0;
				}
				else
					printf("Test2 passed.\n");
				break;
			case TEST3:
				if (strcmp(reginfo_msg.xTEDS_section, Test3Correct))
				{
					printf("***Test3 failed.***\n");
					printf("reginfo_msg.xTEDS_section = %s \n\nTest3Correct = %s\n",reginfo_msg.xTEDS_section, Test3Correct);
					return 0;
				}
				else
					printf("Test3 passed.\n");
				break;
			case TEST4:
				if (strcmp(reginfo_msg.xTEDS_section, Test4Correct))
				{
					printf("***Test4 failed.***\n");
					printf("reginfo_msg.xTEDS_section = %s \n\nTest4Correct = %s\n",reginfo_msg.xTEDS_section, Test4Correct);
					return 0;
				}
				else
					printf("Test4 passed.\n");
				break;
			case TEST5:
				if (strcmp(reginfo_msg.xTEDS_section, Test5Correct))
				{
					printf("***Test5 failed.***\n");
					printf("reginfo_msg.xTEDS_section = %s \n\nTest5Correct = %s\n",reginfo_msg.xTEDS_section, Test5Correct);
					return 0;
				}
				else
					printf("Test5 passed.\n");
				break;
			case TEST6:
				if (strcmp(reginfo_msg.xTEDS_section, Test6Correct))
				{
					printf("***Test6 failed.***\n");
					printf("reginfo_msg.xTEDS_section = %s \n\nTest6Correct = %s\n",reginfo_msg.xTEDS_section, Test6Correct);
					return 0;
				}
				else
					printf("Test6 passed.\n");
				break;
			case TEST7:
				if (strcmp(reginfo_msg.xTEDS_section, Test7Correct))
				{
					printf("***Test7 failed.***\n");
					printf("reginfo_msg.xTEDS_section = %s \n\nTest7Correct = %s\n",reginfo_msg.xTEDS_section, Test7Correct);
					return 0;
				}
				else
					printf("Test7 passed.\n");
				break;
			case TEST8:
				if (strcmp(reginfo_msg.xTEDS_section, Test8Correct))
				{
					printf("***Test8 failed.***\n");
					printf("reginfo_msg.xTEDS_section = %s \n\nTest8Correct = %s\n",reginfo_msg.xTEDS_section, Test8Correct);
					return 0;
				}
				else
					printf("Test8 passed.\n");
				break;
			case TEST9:
				if (strcmp(reginfo_msg.xTEDS_section, Test9Correct))
				{
					printf("***Test9 failed.***\n");
					printf("reginfo_msg.xTEDS_section = %s \n\nTest9Correct = %s\n",reginfo_msg.xTEDS_section, Test9Correct);
					return 0;
				}
				else
					printf("Test9 passed.\n");
				break;
			case TEST10:
				if (strcmp(reginfo_msg.xTEDS_section, Test10Correct))
				{
					printf("***Test10 failed.***\n");
					printf("reginfo_msg.xTEDS_section = %s \n\nTest10Correct = %s\n",reginfo_msg.xTEDS_section, Test10Correct);
					return 0;
				}
				else
					printf("Test10 passed.\n");
				break;
			
			}
			reginfo_msg.source.IDToString(InfoSource, sizeof(InfoSource));

		}
		break;
		default:
			printf("Unexpected message (%d).\n",type);
		}
	}
	printf("End of SDMRegInfo messages.\n");
	printf("-------------------Qualifiers Tester Finished-------------------\n");
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

