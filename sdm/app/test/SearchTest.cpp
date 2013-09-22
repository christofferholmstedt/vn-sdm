#include "../../common/message/SDMSearch.h"
#include "../../common/message/SDMSearchReply.h"
#include "../../common/MessageManager/MessageManager.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <ctype.h>

long my_port;

int main(int argc,char** argv)
{
	SDMSearch s;
	SDMSearchReply reply;
	int result = 0;
	char buf[BUFSIZE];
	long length;
	MessageManager mm;
	int cur = 0;

	SDMInit(argc,argv);
	my_port = getPort();
	mm.Async_Init(my_port);
	sleep(1);

	s.destination.setPort(my_port);
	s.id = 1;

	// Return all interface names only
	strcpy(s.reg_expr,"<Interface[^>]*name=\"([^\"]*)\"[^>]*>");
	s.Send();
	
	// Return the entire <Interface... > tag in the first capture, the interface name
	// in the second capture, and the interface id number in the last capture, for
	// all interfaces
	strcpy(s.reg_expr,"(<Interface name=\"([^\"]*)\"[^<]*(id=\"[0-9]*\")[^<]*>)");
	s.Send();
	
	// This regex returns nothing (not a subexpression)
	strcpy(s.reg_expr,".*");
	s.Send();
	
	// Returns full xTEDS (is a subexpression)
	strcpy(s.reg_expr,"(.*)");
	s.Send();
	
	// invalid regular expression (for testing)
	strcpy(s.reg_expr,"<Interface[^>*name=\"([^\"]*)\"[^>]*>");
	s.Send();
	
	while(1)
	{
		if (mm.IsReady())
		{
			printf("\n");
#ifdef WIN32
			mm.GetMsg(buf, length);
#else
			mm.GetMessage(buf,length);
#endif
			cur = 0;
			result = reply.Unmarshal(buf);
			if(result != SDM_NO_FURTHER_DATA_PROVIDER)
			{
				printf("Match(es) from %lu:%lu:%d\n",reply.source.getSensorID(),reply.source.getAddress(),reply.source.getPort());
				
				bool nullFound = false;
				for (unsigned int i = 0; i < sizeof(reply.captured_matches); i++)
				{
					if (isprint(reply.captured_matches[i]))
					{
						nullFound = false;
						printf("%c", reply.captured_matches[i]);
					}
					else if (reply.captured_matches[i] == '\0')
					{
						// Nulls printed as zero
						printf("0");
						if (nullFound)
						{
							printf("\n");
							break;
						}
						nullFound = true;
					}
				}
			}
		}
		usleep(1000);
	}

	return 0;
}
