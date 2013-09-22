#include "../../common/message/SDMmessage.h"
#include "../../common/message/SDMVarReq.h"
#include "../../common/UDPcom.h"
#include "../../common/message_defs.h"
#include "../../common/MessageManager/MessageManager.h"
#include "../../common/message/SDMVarInfo.h"
#include "../../common/message/SDMxTEDS.h"
#include "../../common/message/SDMCancelxTEDS.h"
#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/message/SDMComponent_ID.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void RegisterxTEDS();
void CancelxTEDS();

long my_port = 0;
SDMComponent_ID myId;
const int DRANGE = 1;
const int CURVE = 2;
const int ALL = 3;

int main(int argc, char** argv)
{
	SDMInit(argc,argv);
	my_port = getPort();
	SDMVarReq request;
	SDMVarInfo info;
	SDMReqReg reg;
	SDMRegInfo reginfo;
	MessageManager mm;
	char buf[BUFSIZE];
	bool found = false;
	bool xTEDS = false;
	mm.Async_Init(my_port);
	
	RegisterxTEDS();
	sleep(1);
	//Get my component id
	strcpy(reg.interface,"Drange_Interface");
	reg.source.setPort(my_port);
	reg.destination.setPort(my_port);
	reg.Send();

	while (!found)
	{
		if (mm.IsReady())
		{
			printf(".");
			fflush(NULL);
			char type = mm.GetMessage(buf);
			switch(type)
			{
				case SDM_RegInfo:
					int value = reginfo.Unmarshal(buf);
					if (value != SDM_NO_FURTHER_DATA_PROVIDER || value != SDM_INVALID_MESSAGE)
					{
						myId = reginfo.source;
						found = true;
						printf("ComponentID found.\n");
					}
					break;
			}
		}
		else
		{
			sleep(1);
		}
	}
	CancelxTEDS();
	request.destination.setPort(my_port);
	request.id = 1;
	request.source = myId;
	request.reply = SDM_VARREQ_CURRENT_AND_FUTURE;
	printf("Sending VarReq for Drange data.\n");
	strcpy(request.variable,"data");
	request.id = DRANGE;
	request.msg_id = reginfo.msg_id;
	request.Send();
	printf("Sending VarReq for Curve data.\n");
	strcpy(request.variable,"data");
	request.id = CURVE;
	request.msg_id.setInterface(2);
	request.Send();
	printf("Sending VarReq for all variables named data in xTEDS\n");
	request.id = ALL;
	request.msg_id.setInterface(0);
	request.Send();
	
	found = false;
	int count = 0;
	while (!found)
	{
		if (mm.IsReady())
		{
			char type = mm.GetMessage(buf);
			switch(type)
			{
				case SDM_VarInfo:
					int value = info.Unmarshal(buf);
					if (value != SDM_NO_FURTHER_DATA_PROVIDER && value != SDM_INVALID_MESSAGE)
					{
						if (info.id == CURVE)
						{
							printf("Curve variable is %s\n\n",info.var_xTEDS);
							count ++;
						}
						if (info.id == DRANGE)
						{
							printf("Drange variable is %s\n\n",info.var_xTEDS);
							count ++;
						}
						if(info.id == ALL)
						{
							printf("All data variables is %s\n",info.var_xTEDS);
							count++;
						}
						if (count == 4)
							found = true;
						fflush(NULL);
					}
			}
		}
		else
		{
			sleep(1);
			if(!xTEDS)
			{
				xTEDS = true;
				RegisterxTEDS();
			}
		}
	}
	SDMVarReq var;
	var.reply = SDM_VARREQ_CANCEL;
	var.destination.setPort(my_port);
	var.Send();
	CancelxTEDS();
	return 1;
}

void RegisterxTEDS()
{
	SDMxTEDS  xteds;	// create an xTEDS registration message

	strcpy (xteds.xTEDS,"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n<xTEDS version=\"2.0\" name=\"Drange_and_Curve_xTEDS\">\n\t<Application name=\"Drange/Curve_FaultChecker\" kind=\"data\"/>\n\t<Interface name=\"Drange_Interface\" id=\"1\">\n\t<Variable name=\"data\" format=\"UINT08\" kind=\"data\">\n\t\t<Drange name=\"test1\">\n\t\t\t<Option name=\"hello\" value=\"don't know\" alarm=\"help\" description=\"This is a test\"/>\n\t\t</Drange>\n\t</Variable>\n\t<Notification>\n\t\t<DataMsg name=\"drange_all\" id=\"1\" msgArrival=\"PERIODIC\" msgRate=\"1\">\n\t\t\t<VariableRef name=\"data\"/>\n\t\t</DataMsg>\n\t</Notification>\n\t</Interface>\n\t<Interface name=\"Curve_Interface\" id=\"2\">\n\t<Variable name=\"data\" format=\"UINT16\" kind=\"data\">\n\t<Qualifier name=\"Qual1\" value=\"1\"/>\n\t\t<Curve name=\"Test2\">\n\t\t\t<Coef value=\"nope\" description=\"This is another test\" exponent=\"yep\"/>\n\t\t</Curve>\n\t</Variable>\n\t<Notification>\n\t\t<DataMsg name=\"curve_all\" id=\"1\" msgArrival=\"PERIODIC\" msgRate=\"1\">\n\t\t\t<VariableRef name=\"data\"/>\n\t\t</DataMsg>\n\t</Notification>\n\t</Interface>\n</xTEDS>\n");	// set xTEDS

	xteds.source.setSensorID(1);		// set the id of this application
	xteds.source.setPort(my_port);
	printf("Registering producer xTEDS on port %ld\n",my_port);
	xteds.Send();				// register with the SDM
}

void CancelxTEDS()
{
	SDMCancelxTEDS cancel;
	printf("Canceling xTEDS\n");
	cancel.source.setSensorID(1);
	cancel.source.setPort(my_port);
	cancel.Send();
}

