#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <errno.h>

#include <unistd.h>		/*Needed to handle open() and write() file I/O*/

#include "MessageLogger.h"
#include "../message_defs.h"
#include "../message/SDMxTEDS.h"
#include "../message/SDMCancelxTEDS.h"
#include "../message/SDMSubreqst.h"
#include "../message/SDMDeletesub.h"
#include "../message/SDMData.h"
#include "../message/SDMReqCode.h"
#include "../message/SDMConsume.h"
#include "../message/SDMReqReg.h"
#include "../message/SDMRegInfo.h"
#include "../message/SDMRegPM.h"
#include "../message/SDMCancel.h"
#include "../message/SDMService.h"
#include "../message/SDMSerreqst.h"
#include "../message/SDMCommand.h"
#include "../message/SDMReqxTEDS.h"
#include "../message/SDMxTEDSInfo.h"
#include "../message/SDMError.h"
#include "../message/SDMReady.h"
#include "../message/SDMTat.h"
#include "../message/SDMTask.h"
#include "../message/SDMTaskFinished.h"
#include "../message/SDMSearch.h"
#include "../message/SDMSearchReply.h"
#include "../message/SDMHeartbeat.h"
#include "../message/SDMDMLeader.h"
#include "../message/SDMVarReq.h"
#include "../message/SDMTaskError.h"
#include "../message/SDMVarInfo.h"

MessageLogger::MessageLogger():numTypes(0), fd(-1), init_done(false), LogIdListHead(NULL)
{
}
MessageLogger::~MessageLogger()
{
	if (fd > 0)
		close(fd);
}

bool MessageLogger::AddMessageType(const SDMCommand *msg)
{
	unsigned char msg_type;
	LogID nextID;
	SDMComponent_ID id;

	msg_type = GET_UCHAR(&msg->data[0]);
	id.Unmarshal(msg->data, 1);

	for(LogID* cur = LogIdListHead; cur != NULL; cur = cur->next)
	{
		if(cur->msg_type == msg_type && cur->component == id)
		{
			return false;
		}
	}
	nextID.msg_type = msg_type;
	nextID.component = id;
	nextID.next = LogIdListHead;
	LogIdListHead = &nextID;
	numTypes++;
	return true;
}

bool MessageLogger::RemoveMessageType(const SDMCommand *msg)
{
	unsigned char msg_type;
	SDMComponent_ID id;
	bool ignore_sid = false;
	LogID* prevPtr = NULL;
	LogID* cur;

	msg_type = GET_UCHAR(&msg->data[0]);
	id.Unmarshal(msg->data, 1);

	if (id.getAddress() == 0 && id.getPort() == 0 && id.getSensorID() == 0 && msg_type == '\0')	//Remove all messages
	{
		LogIdListHead = NULL;
		numTypes = 0;
		return true;
	}
	else if (id.getAddress() == 0 && id.getPort() == 0 && id.getSensorID() == 0)
	{
		ignore_sid = true;
	}

	for(cur = LogIdListHead; cur != NULL; cur = cur->next)
	{
		if (cur->msg_type == msg_type && (ignore_sid || cur->component == id))	//Find the item to remove
		{
			break;
		}
		prevPtr = cur;
	}
	
	if (cur == NULL)				//Item not found
	{
		return false;
	}
	else
	{
		if(prevPtr != NULL)
		{
			prevPtr->next = cur->next;
		}
		else
		{
			LogIdListHead = cur->next;
		}
	}
	numTypes--;
	return true;
}

bool MessageLogger::Contains(char msg_type)
{
	for(LogID* cur = LogIdListHead; cur != NULL; cur = cur->next)
	{
		if (cur->msg_type == msg_type || cur->msg_type == '\0')
			return true;
	}
	return false;
}

bool MessageLogger::Contains(char msg_type, SDMComponent_ID id)
{
	bool match_sensorid = true;
	bool match_ipaddr = true;
	bool match_port = true;
	for(LogID* cur = LogIdListHead; cur != NULL; cur = cur->next)
	{
		//Test which parts of the component ID should be matched
		if (cur->component.getSensorID() == 0)
			match_sensorid = false;
		if (cur->component.getAddress() == 0)
			match_ipaddr = false;
		if (cur->component.getPort() == 0)
			match_port = false;

		if (cur->msg_type == msg_type || cur->msg_type == '\0')
			if (!match_sensorid || (cur->component.getSensorID() == id.getSensorID()))
				if (!match_ipaddr || (cur->component.getAddress() == id.getAddress()))
					if (!match_port || (cur->component.getPort() == id.getPort()))
						return true;

	}
	return false;
}

bool MessageLogger::Contains(char msg_type, SDMComponent_ID id1, SDMComponent_ID id2)
{
	bool match_sensorid = true;
	bool match_ipaddr = true;
	bool match_port = true;
	for(LogID* cur = LogIdListHead; cur != NULL; cur = cur->next)
	{
		//Test which parts of the component ID should be matched
		if (cur->component.getSensorID() == 0)
			match_sensorid = false;
		if (cur->component.getAddress() == 0)
			match_ipaddr = false;
		if (cur->component.getPort() == 0)
			match_port = false;

		if (cur->msg_type == msg_type || cur->msg_type == '\0')
			if (!match_sensorid || (cur->component.getSensorID() == id1.getSensorID()) || (cur->component.getSensorID() == id2.getSensorID()))
				if (!match_ipaddr || (cur->component.getAddress() == id1.getAddress()) || (cur->component.getAddress() == id2.getAddress()))
					if (!match_port || (cur->component.getPort() == id1.getPort()) || (cur->component.getPort() == id2.getPort()))
						return true;

	}
	return false;
}

bool MessageLogger::IsEmpty()
{
	return (numTypes == 0);
}

bool MessageLogger::MessageReceived(const SDMmessage *msg)
{
	char msg_type = msg->GetMsgName();
	char message_buf[3*BUFSIZE];
	char comp_id_buf[22];
	SDMComponent_ID compid1;
	SDMComponent_ID compid2;
	int num_ids = 0;
	bool contains = false;

	GetCompIDs(msg, comp_id_buf, num_ids);

	if (fd < 0)
		return false;
	if (num_ids == 0)
		contains = this->Contains(msg_type);
	else if (num_ids == 1)
	{
		compid1.Unmarshal(comp_id_buf, 0);
		contains = this->Contains(msg_type, compid1);
	}
	else if (num_ids == 2)
	{
		compid1.Unmarshal(comp_id_buf, 0);
		compid2.Unmarshal(comp_id_buf, HEADER_SIZE);
		contains = this->Contains(msg_type, compid1, compid2);
	}

	if (contains)
	{
		msg->MsgToString(message_buf, sizeof(message_buf));
		return WriteLogMessage("IN   ", message_buf);
	}

	return false;
}

bool MessageLogger::MessageSent(const SDMmessage *msg)
{
	unsigned char msg_type = msg->GetMsgName();
	char message_buf[3*BUFSIZE];
	char comp_id_buf[22];
	SDMComponent_ID compid1;
	SDMComponent_ID compid2;
	int num_ids = 0;
	bool contains = false;

	GetCompIDs(msg, comp_id_buf, num_ids);

	if (fd < 0)
		return false;
	if (num_ids == 0)
		contains = this->Contains(msg_type);
	else if (num_ids == 1)
	{
		compid1.Unmarshal(comp_id_buf, 0);
		contains = this->Contains(msg_type, compid1);
	}
	else if (num_ids == 2)
	{
		compid1.Unmarshal(comp_id_buf, 0);
		compid2.Unmarshal(comp_id_buf, HEADER_SIZE);
		contains = this->Contains(msg_type, compid1, compid2);
	}

	if (contains)
	{
		msg->MsgToString(message_buf, sizeof(message_buf));
		return WriteLogMessage("OUT  ", message_buf);
	}

	return false;
}

void MessageLogger::SetLogFile(const char *header, const char *filename)
{
	int length;

#ifndef WIN32
	fd = open(filename, O_TRUNC | O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
#else
	fd = open(filename, O_TRUNC | O_CREAT| O_RDWR);
#endif

	if (fd < 0)
		perror("Error occurred while opening logfile:");
	else
	{
		length = write(fd, header, strlen(header));
		if (length < 0)
			perror("Write failed: ");
		init_done = true;
	}
}

bool MessageLogger::WriteLogMessage(char *prefix, char *msg_buf)
{
	int length;
	char newline = '\n';

	if (fd < 0)
		return false;
	write(fd, prefix, strlen(prefix));
	length = write(fd, msg_buf, strlen(msg_buf));
	write(fd, &newline, 1);

	if (length < 0)
		return false;
	else
		return true;
}

void MessageLogger::GetCompIDs(const SDMmessage *msg, char *buf, int &num_ids)
{
	unsigned char msg_type = msg->GetMsgName();
	SDMComponent_ID id1;
	SDMComponent_ID id2;

	switch(msg_type)
	{
		case SDM_ACK:
		{
			num_ids = 0;
			break;
		}
		case SDM_Cancel:
		{
			SDMCancel *message = (SDMCancel*) msg;
			num_ids = 2;
			id1 = message->source;
			id2 = message->destination;
			break;
		}
		case SDM_CancelxTEDS:
		{
			SDMCancelxTEDS *message = (SDMCancelxTEDS*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_Code:
		{
			num_ids = 0;
			break;
		}
		case SDM_Command:
		{
			SDMCommand *message = (SDMCommand*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}

		case SDM_Consume:
		{
			SDMConsume*message = (SDMConsume*) msg;
			num_ids = 2;
			id1 = message->source;
			id2 = message->destination;
			break;
		}
		case SDM_Deletesub:
		{
			SDMDeletesub *message = (SDMDeletesub*) msg;
			num_ids = 2;
			id1 = message->source;
			id2 = message->destination;
			break;
		}
		case SDM_Data:
		{
			SDMData *message = (SDMData*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_DMLeader:
		{
			SDMDMLeader *message = (SDMDMLeader*)msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_Election:
		{
			num_ids = 0;
			break;
		}
		case SDM_Error:
		{
			SDMError *message = (SDMError*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_Heartbeat:
		{
			SDMHeartbeat *message = (SDMHeartbeat*)msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_Kill:
		{
			num_ids = 0;
			break;
		}
		case SDM_PostTask:
		{
			num_ids = 0;
			break;
		}
		case SDM_Ready:
		{
			SDMReady *message = (SDMReady*) msg;
			num_ids = 2;
			id1 = message->source;
			id2 = message->destination;
			break;
		}
		case SDM_Search:
		{
			SDMSearch *message = (SDMSearch*) msg;
			num_ids = 2;
			id1 = message->source;
			id2 = message->destination;
			break;
		}
		case SDM_SearchReply:
		{
			SDMSearchReply *message = (SDMSearchReply*)msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_RegInfo:
		{
			SDMRegInfo *message = (SDMRegInfo*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_RegPM:
		{
			SDMRegPM *message = (SDMRegPM*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_ReqCode:
		{
			SDMReqCode *message = (SDMReqCode*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_ReqReg:
		{
			SDMReqReg *message = (SDMReqReg*) msg;
			num_ids = 2;
			id1 = message->source;
			id2 = message->destination;
			break;
		}
		case SDM_ReqxTEDS:
		{
			SDMReqxTEDS *message = (SDMReqxTEDS*) msg;
			num_ids = 2;
			id1 = message->source;
			id2 = message->destination;
			break;
		}
		case SDM_Serreqst:
		{
			SDMSerreqst *message = (SDMSerreqst*) msg;
			num_ids = 2;
			id1 = message->source;
			id2 = message->destination;
			break;
		}
		case SDM_Service:
		{
			SDMService *message = (SDMService *) msg;
			num_ids = 2;
			id1 = message->source;
			id2 = message->destination;
			break;
		}
		case SDM_Subreqst:
		{
			SDMSubreqst *message = (SDMSubreqst*) msg;
			num_ids = 2;
			id1 = message->source;
			id2 = message->destination;
			break;
		}
		case SDM_Task:
		{
			SDMTask *message = (SDMTask*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_TaskError:
		{
			SDMTaskError *message = (SDMTaskError*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_TaskFinished:
		{
			SDMTaskFinished *message = (SDMTaskFinished*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_Tat:
		{
			SDMTat *message = (SDMTat*) msg;
			num_ids = 1;
			id1 = message->destination;
			break;
		}
		case SDM_VarInfo:
		{
			SDMVarInfo *message = (SDMVarInfo*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_VarReq:
		{
			SDMVarReq *message = (SDMVarReq*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_xTEDSInfo:
		{
			SDMxTEDSInfo *message = (SDMxTEDSInfo*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
		case SDM_xTEDS:
		{	SDMxTEDS *message = (SDMxTEDS*) msg;
			num_ids = 1;
			id1 = message->source;
			break;
		}
	}
	if (num_ids == 1)
	{
		id1.Marshal(buf, 0);
	}
	else if (num_ids == 2)
	{
		id1.Marshal(buf, 0);
		id2.Marshal(buf, HEADER_SIZE);
	}
}
bool MessageLogger::NeedsInit()
{
	return !init_done;
}

void MessageLogger::LogAllMessageTypes()
{
	unsigned char msg_type = '\0';
	LogID nextID;
	SDMComponent_ID id;
	//Make sure this operation hasn't already been called
	for(LogID* cur = LogIdListHead; cur != NULL; cur = cur->next)
	{
		if(cur->msg_type == msg_type && cur->component == id)
			return;
	}
	nextID.msg_type = msg_type;
	nextID.component = id;
	nextID.next = LogIdListHead;
	LogIdListHead = &nextID;
	numTypes++;
}
