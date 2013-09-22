#include <stdio.h>
#include <string.h>
#include "../../../common/message/SDMVarReq.h"
#include "../../../common/message/SDMVarInfo.h"

int main (int argc, char ** argv)
{
	SDMVarReq req;
	SDMVarInfo info;
	char MsgBuf[8096];
	char send_buf[BUFSIZE];
	
	//Set request message info
	req.source.setPort(1020);
	req.destination.setPort(1234);
	req.msg_id.setInterface(11);
	req.id = 4;
	strcpy(req.variable, "TestVar");
	//Set info message info
	info.source.setPort(3443);
	info.id = 44;
	strcpy(info.var_xTEDS, "Test xTEDS");
	
	printf("----SDMVarReq TEST----\n");
	req.MsgToString(MsgBuf, sizeof(MsgBuf));
	printf ("Before any marshalling: ");
	printf("%s\n",MsgBuf);
	req.Marshal(send_buf);
	req.Unmarshal(send_buf);
	printf ("After unmarshalling: ");
	req.MsgToString(MsgBuf, sizeof(MsgBuf));
	printf("%s\n", MsgBuf);
	
	printf("\n\n----SDMVarInfo TEST----\n");
	info.MsgToString(MsgBuf, sizeof(MsgBuf));
	printf ("Before any marshalling: ");
	printf("%s\n",MsgBuf);
	info.Marshal(send_buf);
	info.Unmarshal(send_buf);
	printf ("After unmarshalling: ");
	info.MsgToString(MsgBuf, sizeof(MsgBuf));
	printf("%s\n", MsgBuf);
	
	printf("\n\nFinished.\n");	
	return 0;
}
