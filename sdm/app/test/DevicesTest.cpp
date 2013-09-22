#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

#include "../../common/message/SDMReqReg.h"
#include "../../common/message/SDMRegInfo.h"
#include "../../common/message/SDMConsume.h"
#include "../../common/message/SDMData.h"
#include "../../common/MessageManager/MessageManager.h"

const long my_port = 4123;

int main (int argc, char ** argv)
{
	MessageManager mm;
	SDMInit(argc, argv);
	char buf[BUFSIZE];
	
	mm.Async_Init(my_port);
	
	SDMReqReg request;
	request.destination.setPort(my_port);
	request.reply = SDM_REQREG_CURRENT_AND_FUTURE;
	request.Send();
	
	SDMRegInfo info;
	SDMConsume cons;
	SDMData data;
	
	while (1)
	{
		if (mm.IsReady())
		{
			unsigned char type = mm.GetMessage(buf);
			switch (type)
			{
				case SDM_RegInfo:
				{
					if (info.Unmarshal(buf) > 0)
					{
						if (info.source.getPort() == PORT_PM || info.source.getPort() == PORT_TM || info.source.getPort() == PORT_DM)
							continue;
						cons.source = info.source;
						cons.destination.setPort(my_port);
						cons.msg_id = info.msg_id;
						char provider[256];
						char message[256];
						cons.msg_id.IDToString(message, sizeof(message));
						cons.source.IDToString(provider, sizeof(provider));
						printf("Subscribing to %s from %s\n",message,provider);
						cons.Send();
					}
				}
				break;
				case SDM_Data:
				{
					data.Unmarshal(buf);
					char src[128];
					char id[128];
					data.source.IDToString(src, sizeof(src));
					data.msg_id.IDToString(id, sizeof(id));
					printf("SDMData from %s id %s\n",src,id);
				}
				break;
			}
		}
		else
			sleep(1);
	}
	
	return 0;
}
