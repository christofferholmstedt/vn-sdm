#include "../../../../common/message/SDMxTEDS.h"
#include "../../../../common/message/SDMSubreqst.h"
#include "../../../../common/message/SDMDeletesub.h"
#include "../../../../common/message/SDMCancelxTEDS.h"
#include "../../../../common/message/SDMReqReg.h"
#include "../../../../common/message/SDMRegInfo.h"
#include "../../../../common/message/SDMData.h"
#include "../../../../common/message/SDMConsume.h"
#include "../../../../common/message/SDMCancel.h"
#include "../../../../common/message/SDMService.h"
#include "../../../../common/SubscriptionManager/SubscriptionManager.h"
#include "../../../../common/MessageManager/MessageManager.h"
#include "../../../../common/message/SDMHeartbeat.h"
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include <string>

using namespace std;

string producerName = "producerone";

void RegisterxTEDS(const string& xteds);
void CancelxTEDS();
void* Publisher(void *);
void* Listener(void *);
void ReqReg();
void ReqRegData();
string GetXtedsString(const char* strApplicationName);
void RequestSensorId();
string GetProviderString();
string GetNameString();
void CancelNotifications();

SubscriptionManager subscriptions;
pthread_mutex_t subscription_mutex = PTHREAD_MUTEX_INITIALIZER;
long my_port;

bool bXtedsRegistered = false;
bool bProducerOne = false;

const unsigned int ID_CHECK_EXISTING_DEVICE = 5;
const unsigned int ID_DATA = 6;
const unsigned int ID_TM_INFO = 7;

SDMComponent_ID dataProvider;
SDMComponent_ID myId;
SDMMessage_ID dataId;
SDMMessage_ID DMPidToSid(1, 8);
SDMMessage_ID DMPidToSidReply(1, 9);
SDMMessage_ID TMStatusMsg(1, 1);

bool bDeviceAlreadyExists = false;
bool bMyIdSet = false;
const unsigned int THREAD_STACK_SIZE = 128000;

int main(int argc,char** argv)
{
	pthread_t ListenerThread;
	pthread_t PublisherThread;

	SDMInit(argc,argv);
	my_port = getPort();
	if(my_port == SDM_PM_NOT_AVAILABLE)
	{
		printf("No PM is available to get port from!\n");
		return 0;
	}
	
	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);
	pthread_attr_setstacksize(&threadAttr, THREAD_STACK_SIZE);
	
	pthread_create(&ListenerThread,&threadAttr,&Listener,NULL);
	usleep(100);
	ReqReg();
	
	//usleep(100);
	pthread_create(&PublisherThread,&threadAttr,&Publisher,NULL);
	pthread_join(PublisherThread,NULL);
	CancelxTEDS();
	CancelNotifications();
	pthread_cancel(ListenerThread);
	pthread_join(ListenerThread,NULL);
}

void* Publisher(void * args)
{
	int published = 0;
	short data;
	while(published < 10)
	{
		data = (short)(rand()&0x00FF);
		char bufdata[2];
		PUT_SHORT(bufdata, data);
		pthread_mutex_lock(&subscription_mutex);
		if (subscriptions.Publish(1,1,bufdata,2))
		{
			published++;
		}
		pthread_mutex_unlock(&subscription_mutex);
		printf("Produced %d\tPublished %d / 10\n",data,published);
		sleep(1);
	}
	return NULL;
}

void* Listener(void * args)
{
	char buf[BUFSIZE];
	SDMSubreqst sub;
	SDMDeletesub del;
	MessageManager mm;
	mm.Async_Init(my_port);
	while(1)
	{
		pthread_testcancel();
		if(mm.IsReady())
		{
			SendHeartbeat();
#ifdef WIN32
			switch(mm.GetMsg(buf))
#else
			switch(mm.GetMessage(buf))
#endif
			{
			case SDM_Subreqst:
				sub.Unmarshal(buf);
				printf("Subscription Rec'd for %d\n",sub.msg_id.getInterfaceMessagePair()); fflush(NULL);
				pthread_mutex_lock(&subscription_mutex);
				subscriptions.AddSubscription(sub);
				pthread_mutex_unlock(&subscription_mutex);
				break;
			case SDM_Deletesub:
				printf("Cancel Rec'd\n");
				del.Unmarshal(buf);
				pthread_mutex_lock(&subscription_mutex);
				subscriptions.RemoveSubscription(del);
				pthread_mutex_unlock(&subscription_mutex);
				break;
			case SDM_RegInfo:
			{
				printf ("SDM_RegInfo\n");
				SDMRegInfo msgRegInfo;
				if (msgRegInfo.Unmarshal(buf) == SDM_NO_FURTHER_DATA_PROVIDER)
				{
					if (!bDeviceAlreadyExists && !bXtedsRegistered)
					{
						bProducerOne = true;
						RegisterxTEDS(GetXtedsString("producerone"));
						RequestSensorId();
					}
				}
				else if (!bXtedsRegistered)
				{
					// The other producer is registered, register ourselves with a
					// different name
					bDeviceAlreadyExists = true;
					RegisterxTEDS(GetXtedsString("producertwo"));
					RequestSensorId();
				}
				else if (msgRegInfo.id == ID_DATA)
				{
					dataProvider = msgRegInfo.source;
					dataId = msgRegInfo.msg_id;
					
					SDMConsume msgConsume;
					msgConsume.source = msgRegInfo.source;
					msgConsume.msg_id = msgRegInfo.msg_id;
					msgConsume.destination = myId;
					msgConsume.Send();
				}
				else if (msgRegInfo.id == ID_TM_INFO)
				{
					printf("Found TM notification, requesting...\n");
					SDMConsume msgConsume;

					TaskManager = msgRegInfo.source;
					msgConsume.destination = myId;
					msgConsume.source = TaskManager;
					msgConsume.msg_id = TMStatusMsg;
					msgConsume.Send();
				}
			}
				break;
			case SDM_Data:
			{
				SDMData msgData;
				printf("%s received data\n", GetNameString().c_str());
				
				msgData.Unmarshal(buf);
				if (msgData.msg_id == DMPidToSidReply)
				{
					unsigned long sid = GET_ULONG(msgData.msg + 4);
					myId.setSensorID(sid);
					myId.setPort(my_port);
					bMyIdSet = true;
					printf("Recieved my sensor id from DM (%lu)\n", sid);
					
					ReqRegData();
				}
				else if (msgData.msg_id == TMStatusMsg)
				{
					printf("TM status message receved.\n");
				}
			}
				break;
			default:
				printf("Invalid Message found!\n");
				fflush(NULL);
				break;
			}
		}
		else
		{
			usleep(100000);
		}
	}
	return NULL;
}

void RegisterxTEDS(const string& xteds)
{
	// create an xTEDS registration message
	SDMxTEDS  msgXteds;

	strcpy(msgXteds.xTEDS, xteds.c_str());

	// set the id of this application
	msgXteds.source.setSensorID(1);
	msgXteds.source.setPort(my_port);
	printf("Registering %s xTEDS on port %ld\n", GetNameString().c_str(), my_port);
	// register with the SDM
	msgXteds.Send();
	
	bXtedsRegistered = true;
}

void CancelxTEDS()
{
	SDMCancelxTEDS cancel;
	printf("Canceling xTEDS\n");
	cancel.source.setSensorID(1);
	cancel.source.setPort(my_port);
	cancel.Send();
}

void CancelNotifications()
{
	SDMCancel msgCancel;
	
	msgCancel.msg_id = TMStatusMsg;
	msgCancel.source = TaskManager;
	msgCancel.destination = myId;
	
	msgCancel.Send();
}

void ReqReg()
{
	printf("ReqReg()\n");
	SDMReqReg msgReqReg;
	
	strcpy(msgReqReg.device, producerName.c_str());
	msgReqReg.destination.setPort(my_port);
	msgReqReg.id = ID_CHECK_EXISTING_DEVICE;
	
	msgReqReg.Send();
}

string GetProviderString()
{
	if (bProducerOne)
		return "producertwo";
	return "producerone";
}

string GetNameString()
{
	if (bProducerOne)
		return "producerone";
	return "producertwo";
}

void ReqRegData()
{
	SDMReqReg msgReqReg;
	
	msgReqReg.destination.setPort(my_port);
	strcpy(msgReqReg.device, GetProviderString().c_str());
	strcpy(msgReqReg.item_name, "all");
	msgReqReg.id = ID_DATA;
	msgReqReg.reply = SDM_REQREG_CURRENT_FUTURE_AND_CANCELLATIONS;

	msgReqReg.Send();
	
	strcpy(msgReqReg.device, "TaskManager");
	strcpy(msgReqReg.item_name, "Status");
	msgReqReg.id = ID_TM_INFO;
	msgReqReg.reply = SDM_REQREG_CURRENT;
	msgReqReg.Send();
}

void RequestSensorId()
{
	SDMService msgService;
	
	msgService.command_id = DMPidToSid;
	msgService.source.setSensorID(1);
	msgService.destination.setPort(my_port);
	PUT_ULONG(msgService.data, PID);
	msgService.length = sizeof(PID);
	
	msgService.Send();
}

string GetXtedsString(const char* strApplicationName)
{
	string appName = strApplicationName;
	string producerXteds = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n \
	<xTEDS version=\"2.0\" name=\"Producer_xTEDS\"> \
	\n\t<Application name=\"" + appName + "\" kind=\"data\"/> \
	\n\t<Interface name=\"Producer_Interface\" id=\"1\"> \
	\n\t<Variable name=\"data\" format=\"UINT16\"  \
	kind=\"data\"/> \
	\n\t<Notification> \
	\n\t\t<DataMsg name=\"all\" id=\"1\"  \
	msgArrival=\"PERIODIC\" msgRate=\"1\"> \
	\n\t\t\t<VariableRef name=\"data\"/> \
	\n\t\t</DataMsg> \
	\n\t</Notification> \
	\n\t</Interface> \
	\n</xTEDS>\n";
	
	return producerXteds;
}

