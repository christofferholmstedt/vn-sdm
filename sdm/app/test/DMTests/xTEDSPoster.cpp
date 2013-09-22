#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>

#include "xTEDSPoster.h"
#include "../../../common/message/SDMxTEDS.h"
#include "../../../common/message/SDMCancelxTEDS.h"

const long FAKE_XTEDS_PORT = 4334;
const char *FAKE_XTEDS_PATH = "1.2.3";

xTEDSPoster::xTEDSPoster() {}
xTEDSPoster::~xTEDSPoster() {}

int xTEDSPoster::PostxTEDS(const char *filename)
{
	int fd = open(filename, O_RDONLY);
	if (fd < 0)
		return -1;
	
	SDMxTEDS Xteds;
	char FileBuf[3*BUFSIZE];
	int result;
	
	result = read(fd, FileBuf, sizeof(FileBuf));
	if (result < 0)
		return -1;
	
	Xteds.source.setPort(FAKE_XTEDS_PORT);
	strncpy(Xteds.xTEDS, FileBuf, result);
	strcpy(Xteds.SPA_node, FAKE_XTEDS_PATH);
	
	if ((result=Xteds.Send()) < 0)
	{
		switch (result)
		{
		case SDM_MESSAGE_SEND_ERROR:
			printf("xTEDSPoster::Error: Send Error\n");
			return 0;
			break;
		case SDM_MESSAGE_RECV_ERROR:
			printf("xTEDSPoster::Error: Recv Error\n");
			return 0;
			break;
		case SDM_INVALID_MESSAGE:
			printf("xTEDSPoster::Error: Invalid Message\n");
			return 0;
			break;
		case SDM_UNABLE_TO_REGISTER:
			printf("xTEDSPoster::Error: Unable to Register\n");
			return 0;
			break;
		case SDM_INVALID_XTEDS:
			printf("xTEDSPoster::Error: Invalid xTEDS\n");
			return 0;
			break;
		default:
			printf("xTEDSPoster::Error: Unknown error code %d\n",result);
			return 0;
			break;
		}
	}
  close(fd);
	return 0;
}

int xTEDSPoster::CancelxTEDS()
{
	SDMCancelxTEDS Cancel;
	
	Cancel.source.setPort(FAKE_XTEDS_PORT);
	Cancel.Send();
	return 0;
}
