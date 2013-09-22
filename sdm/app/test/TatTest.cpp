#include "../../common/message/SDMTat.h"

int main (int argc, char** argv)
{
	SDMInit(argc, argv);
	
	SDMTat Tat;
	
	Tat.destination.setSensorID(0);
	Tat.seconds = 1;
	Tat.useconds = 2;
	
	Tat.Send();
	
	return 0;
}
