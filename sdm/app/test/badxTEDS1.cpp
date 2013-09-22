#include "../../common/message/SDMmessage.h"
#include "../../common/message/SDMxTEDS.h"
#include "../../common/message/SDMCancelxTEDS.h"
#include "../../common/UDPcom.h"
#include "../../common/message_defs.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void nullxteds_withclass();
void nullxteds_raw();
void nullxteds_incomplete();
void garbagexteds();
void repeatingxteds();
void invalidxteds();

int main(int argc, char** argv)
{
	SDMInit(argc,argv);
	nullxteds_withclass();
	nullxteds_raw();
	nullxteds_incomplete();
	garbagexteds();
	repeatingxteds();
	invalidxteds();
}

//Sends a NULL xTEDS using the SDMxTEDS class
void nullxteds_withclass()
{
	SDMxTEDS xted;
	xted.source.setSensorID(1);
	xted.source.setPort(4000);
	memset(xted.xTEDS,0,10);
	printf("Starting null xTEDS (with class) test\n");
	xted.Send();
	sleep(5);
	puts("Test Done");
}

//Sends a NULL xTEDS avoiding the SDMxTEDS class
void nullxteds_raw()
{
	char msg[BUFSIZE];
	char geo_location;
	long id;

	memset(msg,0,BUFSIZE);
	id = 2;
	msg[0] = SDM_xTEDS;
	memcpy(msg+1,&id,4);
	id = 4001;
	memcpy(msg+5,&id,4);
	geo_location = 0;
	memcpy(msg+9,&geo_location,1);
	memcpy(msg+10,&id,4);
	printf("Starting null xTEDS (raw) test\n");
	struct in_addr inaddr;
	inaddr.s_addr = DataManager.getAddress();
	UDPsendto(inet_ntoa(inaddr),PORT_DM,msg,BUFSIZE);
	sleep(5);
	puts("Test Done");
}

//Inserts a null character into a valid xTEDS at a random location then sends it
void nullxteds_incomplete()
{
	SDMxTEDS xted;
	xted.source.setSensorID(1);
	xted.source.setPort(4000);
	int pos;
	char* xted_text = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<xTEDS version=\"2.0\" name=\"Task_Manager_xTEDS2\">\n\t<Application kind=\"Software\" name=\"TaskManager2\"/>\n\t<Interface name=\"TM_Interface\" id=\"1\">\n\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"Mode\"/>\n\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"TaskName\" length=\"16\"/>\n\t\t<Variable format=\"INT32\" kind=\"TBD\" name=\"ExitStatus\"/>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"Status\" id=\"1\" msgArrival=\"EVENT\">\n\t\t\t\t<VariableRef name=\"Mode\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"TaskQueued\" id=\"2\" msgArrival=\"EVENT\">\n\t\t\t\t<VariableRef name=\"TaskName\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"TaskStarted\" id=\"3\" msgArrival=\"EVENT\">\n\t\t\t\t<VariableRef name=\"TaskName\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"TaskFinished\" id=\"4\" msgArrival=\"EVENT\">\n\t\t\t\t<VariableRef name=\"TaskName\"/>\n\t\t\t\t<VariableRef name=\"ExitStatus\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Command>\n\t\t\t<CommandMsg name=\"ChangeMode\" id=\"5\">\n\t\t\t\t<VariableRef name=\"Mode\"/>\n\t\t\t</CommandMsg>\n\t\t</Command>\n\t</Interface>\n\t<Interface name=\"Msg_Count\" id=\"2\">\n\t\t<Variable name=\"Total_Messages_Recd\" kind=\"Total\" format=\"UINT16\"/>\n\t\t<Variable name=\"Messages_Last_Second_Recd\" kind=\"Total\" format=\"UINT16\"/>\n\t\t<Variable name=\"Total_Messages_Sent\" kind=\"Total\" format=\"UINT16\"/>\n\t\t<Variable name=\"Messages_Last_Second_Sent\" kind=\"Total\" format=\"UINT16\"/>\n\n\t\t<Notification>\n\t\t\t<DataMsg name=\"Message_Count\" id=\"13\" msgArrival=\"PERIODIC\">\n\t\t\t\t<VariableRef name=\"Total_Messages_Recd\"/>\n\t\t\t\t<VariableRef name=\"Messages_Last_Second_Recd\"/>\n\t\t\t\t<VariableRef name=\"Total_Messages_Sent\"/>\n\t\t\t\t<VariableRef name=\"Messages_Last_Second_Sent\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t</Interface>\n\t<Interface name=\"Message_Log\" id=\"3\">\n\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"Msg_Type\"/>\n\t\t<Command>\n\t\t\t<CommandMsg name=\"Enable_Logging\" id=\"16\">\n\t\t\t\t<VariableRef name=\"Msg_Type\"/>\n\t\t\t</CommandMsg>\n\t\t</Command>\n\t\t<Command>\n\t\t\t<CommandMsg name=\"Disable_Logging\" id=\"17\">\n\t\t\t\t<VariableRef name=\"Msg_Type\"/>\n\t\t\t</CommandMsg>\n\t\t</Command>\n\t</Interface>\n</xTEDS>";

	printf("Starting null xTEDS (incomplete) test\n");
	for(int i=0;i<5;i++)
	{
		printf("%d.",i);
		pos = (rand() % 300) + 10;
		strcpy(xted.xTEDS,xted_text);
		xted.xTEDS[pos] = '\0';
		xted.Send();
	}
	sleep(5);
	puts("\nTest Done");
}

//Sends garbage bytes as an xTEDS
void garbagexteds()
{
	SDMxTEDS xted;
	xted.source.setSensorID(1);
	xted.source.setPort(4000);

	printf("Starting garbage xTEDS test\n");
	for(int i=0;i<5;i++)
	{
		for(int j=0;j<500;j++)
			xted.xTEDS[j] = (char)((rand() % 255) + 1);
		printf("%d.",i);
		xted.Send();
	}
	sleep(5);
	puts("\nTest Done");
}

//Sends multiple xTEDS in an effort to fill the DM's xTED buffer
void repeatingxteds()
{
	SDMxTEDS xted;
	SDMCancelxTEDS cancel;
	cancel.source.setSensorID(1);
	cancel.source.setPort(4000);
	xted.source.setSensorID(1);
	xted.source.setPort(4000);
	char* xted_text = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<xTEDS version=\"2.0\" name=\"Task_Manager_xTEDS\">\n\t<Application kind=\"Software\" name=\"TaskManager\"/>\n\t<Interface name=\"TM_Interface\" id=\"1\">\n\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"Mode\"/>\n\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"TaskName\" length=\"16\"/>\n\t\t<Variable format=\"INT32\" kind=\"TBD\" name=\"ExitStatus\"/>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"Status\" id=\"1\" msgArrival=\"EVENT\">\n\t\t\t\t<VariableRef name=\"Mode\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"TaskQueued\" id=\"2\" msgArrival=\"EVENT\">\n\t\t\t\t<VariableRef name=\"TaskName\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"TaskStarted\" id=\"3\" msgArrival=\"EVENT\">\n\t\t\t\t<VariableRef name=\"TaskName\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"TaskFinished\" id=\"4\" msgArrival=\"EVENT\">\n\t\t\t\t<VariableRef name=\"TaskName\"/>\n\t\t\t\t<VariableRef name=\"ExitStatus\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Command>\n\t\t\t<CommandMsg name=\"ChangeMode\" id=\"5\">\n\t\t\t\t<VariableRef name=\"Mode\"/>\n\t\t\t</CommandMsg>\n\t\t</Command>\n\t</Interface>\n\t<Interface name=\"Msg_Count\" id=\"2\">\n\t\t<Variable name=\"Total_Messages_Recd\" kind=\"Total\" format=\"UINT16\"/>\n\t\t<Variable name=\"Messages_Last_Second_Recd\" kind=\"Total\" format=\"UINT16\"/>\n\t\t<Variable name=\"Total_Messages_Sent\" kind=\"Total\" format=\"UINT16\"/>\n\t\t<Variable name=\"Messages_Last_Second_Sent\" kind=\"Total\" format=\"UINT16\"/>\n\n\t\t<Notification>\n\t\t\t<DataMsg name=\"Message_Count\" id=\"13\" msgArrival=\"PERIODIC\">\n\t\t\t\t<VariableRef name=\"Total_Messages_Recd\"/>\n\t\t\t\t<VariableRef name=\"Messages_Last_Second_Recd\"/>\n\t\t\t\t<VariableRef name=\"Total_Messages_Sent\"/>\n\t\t\t\t<VariableRef name=\"Messages_Last_Second_Sent\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t</Interface>\n\t<Interface name=\"Message_Log\" id=\"3\">\n\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"Msg_Type\"/>\n\t\t<Command>\n\t\t\t<CommandMsg name=\"Enable_Logging\" id=\"16\">\n\t\t\t\t<VariableRef name=\"Msg_Type\"/>\n\t\t\t</CommandMsg>\n\t\t</Command>\n\t\t<Command>\n\t\t\t<CommandMsg name=\"Disable_Logging\" id=\"17\">\n\t\t\t\t<VariableRef name=\"Msg_Type\"/>\n\t\t\t</CommandMsg>\n\t\t</Command>\n\t</Interface>\n</xTEDS>";

	strcpy(xted.xTEDS,xted_text);

	printf("Starting repeating xTEDS test\n");
	for(int i=0;i<20;i++)
	{
		printf("%d.",i);
		xted.Send();
	}
	sleep(5);
	cancel.Send();
	puts("\nTest Done");
}
void invalidxteds()
{
	SDMxTEDS xted;
	SDMCancelxTEDS cancel;
	cancel.source.setSensorID(1);
	cancel.source.setPort(4004);
	xted.source.setSensorID(1);
	xted.source.setPort(4004);
	//Invalid xTEDS "<VariaeRef" should be "<VariableRef"
	char* xted_text = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<xTEDS version=\"2.0\" name=\"Task_Manager_xTEDS2\">\n\t<Application kind=\"Software\" name=\"TaskManager2\"/>\n\t<Interface name=\"TM_Interface\" id=\"1\">\n\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"Mode\"/>\n\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"TaskName\" length=\"16\"/>\n\t\t<Variable format=\"INT32\" kind=\"TBD\" name=\"ExitStatus\"/>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"Status\" id=\"1\" msgArrival=\"EVENT\">\n\t\t\t\t<VariaeRef name=\"Mode\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"TaskQueued\" id=\"2\" msgArrival=\"EVENT\">\n\t\t\t\t<VariableRef name=\"TaskName\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"TaskStarted\" id=\"3\" msgArrival=\"EVENT\">\n\t\t\t\t<VariableRef name=\"TaskName\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Notification>\n\t\t\t<DataMsg name=\"TaskFinished\" id=\"4\" msgArrival=\"EVENT\">\n\t\t\t\t<VariableRef name=\"TaskName\"/>\n\t\t\t\t<VariableRef name=\"ExitStatus\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t\t<Command>\n\t\t\t<CommandMsg name=\"ChangeMode\" id=\"5\">\n\t\t\t\t<VariableRef name=\"Mode\"/>\n\t\t\t</CommandMsg>\n\t\t</Command>\n\t</Interface>\n\t<Interface name=\"Msg_Count\" id=\"2\">\n\t\t<Variable name=\"Total_Messages_Recd\" kind=\"Total\" format=\"UINT16\"/>\n\t\t<Variable name=\"Messages_Last_Second_Recd\" kind=\"Total\" format=\"UINT16\"/>\n\t\t<Variable name=\"Total_Messages_Sent\" kind=\"Total\" format=\"UINT16\"/>\n\t\t<Variable name=\"Messages_Last_Second_Sent\" kind=\"Total\" format=\"UINT16\"/>\n\n\t\t<Notification>\n\t\t\t<DataMsg name=\"Message_Count\" id=\"13\" msgArrival=\"PERIODIC\">\n\t\t\t\t<VariableRef name=\"Total_Messages_Recd\"/>\n\t\t\t\t<VariableRef name=\"Messages_Last_Second_Recd\"/>\n\t\t\t\t<VariableRef name=\"Total_Messages_Sent\"/>\n\t\t\t\t<VariableRef name=\"Messages_Last_Second_Sent\"/>\n\t\t\t</DataMsg>\n\t\t</Notification>\n\t</Interface>\n\t<Interface name=\"Message_Log\" id=\"3\">\n\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"Msg_Type\"/>\n\t\t<Command>\n\t\t\t<CommandMsg name=\"Enable_Logging\" id=\"16\">\n\t\t\t\t<VariableRef name=\"Msg_Type\"/>\n\t\t\t</CommandMsg>\n\t\t</Command>\n\t\t<Command>\n\t\t\t<CommandMsg name=\"Disable_Logging\" id=\"17\">\n\t\t\t\t<VariableRef name=\"Msg_Type\"/>\n\t\t\t</CommandMsg>\n\t\t</Command>\n\t</Interface>\n</xTEDS>";

	strcpy(xted.xTEDS,xted_text);
	printf("Invalid xTEDS test.\n");
	xted.Send();
	sleep(5);
	cancel.Send();
	puts("\nTest Done");
}


