#include <iostream>
#include "../../common/message/SDMTat.h"
#include "../../common/message/SDMmessage.h"

int main(int argc, char *argv[])
{
	SDMTat tat;

	SDMInit(argc,argv);
	tat.seconds = 35;
	tat.useconds = 2;
	tat.destination.setSensorID(2);
	printf("Sending Tat\n");
	tat.Send();
	printf("Finished testSDMTat\n");
}
