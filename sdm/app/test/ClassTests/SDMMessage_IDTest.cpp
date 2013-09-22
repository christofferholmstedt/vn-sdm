#include <stdio.h>
#include "../../../common/message/SDMMessage_ID.h"

int main (int argc, char ** argv)
{
	printf ("***STARTING TEST***\n");
	SDMMessage_ID testId1(188, 4);
	SDMMessage_ID testId2(188, 4);
	SDMMessage_ID testId3;
	
	printf("Id1.getInterface() = %d\n",testId1.getInterface());
	printf("Id1.getMessage() = %d\n",testId1.getMessage());
	if (testId1 == testId2)
		printf("operator== test passed.\n");
	else
	{
		printf("operator== test failed.\n");
		return 0;
	}
	testId3 = testId1;
	if (testId3 == testId1)
		printf("operator= test passed.\n");
	else
	{
		printf("operator= test failed.\n");
		return 0;
	}
	testId3.setInterface(1);
	if (testId3.getInterface() == 1)
		printf("set/getInterface() test passed.\n");
	else
	{
		printf("set/getInterface() test failed.\n");
		return 0;
	}
	testId3.setMessage(50);
	if (testId3.getMessage() == 50)
		printf("set/getMessage() test passed.\n");
	else
	{
		printf("set/getMessage() test failed.\n");
		return 0;
	}
	
	char buf[2];
	int result = testId3.Marshal(buf,0);
	if (buf[0] == 1 && buf[1] == 50 && result == 2)
		printf("marshal test passed.\n");
	else
	{
		printf("marshal test failed.\n");
		return 0;
	}
	testId2.Unmarshal(buf, 0);
	if (testId2 == testId3)
 		printf("unmarshal test passed.\n");
	else
	{
		printf("unmarshal test failed.\n");
		return 0;
	}
	
	printf("***TEST COMPLETE***\n");
	
}
