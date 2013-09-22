#include "../../../common/message/SDMxTEDS.h"
#include "../../../common/message/SDMSubreqst.h"
#include "../../../common/message/SDMDeletesub.h"
#include "../../../common/message/SDMCancelxTEDS.h"
#include "../../../common/SubscriptionManager/SubscriptionManager.h"
#include "../../../common/MessageManager/MessageManager.h"
#include "../../../common/message/SDMHeartbeat.h"
#include "../../../common/Time/SDMTime.h"
#include "../../../common/message/SDMHello.h"
#include "../../../common/message/SDMID.h"
#include "../../../common/message/SDMRegister.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

const char* XML_HEADER = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
const char* XTEDS_HEADER = "<xTEDS version=\"2.0\" name=\"Producer_xTEDS\">";
const char* APP_SECTION = "\n\t<Application name=\"producer\" kind=\"data\"/>";
const char* INTERFACE_SECTION = "\n\t<Interface name=\"Producer_Interface\" id=\"1\">";
const char* VAR_DATA_1 = "\n\t<Variable name=\"data\" format=\"UINT16\" ";
const char* VAR_DATA_2 = "kind=\"data\"/>";
const char* NOTIFICATION = "\n\t<Notification>";
const char* MSG_ALL_1 = "\n\t\t<DataMsg name=\"all\" id=\"1\" ";
const char* MSG_ALL_2 = "msgArrival=\"PERIODIC\" msgRate=\"1\">";
const char* MSG_ALL_3 = "\n\t\t\t<VariableRef name=\"data\"/>";
const char* MSG_ALL_4 = "\n\t\t</DataMsg>";
const char* NOTIFICATION_END = "\n\t</Notification>";
const char* INTERFACE_END = "\n\t</Interface>";
const char* XTEDS_END = "\n</xTEDS>\n";

void RegisterxTEDS();
void CancelxTEDS();
void* Publisher(void *);
void* Listener(void *);
double GetCurTime();

SubscriptionManager subscriptions;
pthread_mutex_t subscription_mutex = PTHREAD_MUTEX_INITIALIZER;
long myPort;
SDMID myID;
bool helloReply = false;
bool waitForReg = true;
bool waitForID = true;
const unsigned int THREAD_STACK_SIZE = 128000;

int main(int argc,char** argv)
{
	pthread_t ListenerThread;
	pthread_t PublisherThread;

	SDMInit(argc,argv);
	myPort = getPort();
	if(myPort == SDM_PM_NOT_AVAILABLE)
	{
		printf("No PM is available to get port from!\n");
		printf("Using port 5001\n");
		myPort = 5001;
	}
	
	pthread_attr_t threadAttr;
	pthread_attr_init(&threadAttr);
	pthread_attr_setstacksize(&threadAttr, THREAD_STACK_SIZE);
	
	pthread_create(&ListenerThread,&threadAttr,&Listener,NULL);
	usleep(1000);
	SDMHello hello;
	hello.source.setPort(myPort);
	hello.type = 'A';
	double endTime = 0;
	double timeOut = 5.0;
	while(!helloReply)
	{
		if(GetCurTime() > endTime)
		{
			hello.Send();
			printf("Sending Hello\n");
			endTime = GetCurTime() + timeOut;
		}
		usleep(10000);
	}
	while (waitForReg)
	{
		usleep(10000);
	}
	printf("Registering xTEDS\n");
	RegisterxTEDS();
	pthread_create(&PublisherThread,&threadAttr,&Publisher,NULL);
	pthread_join(PublisherThread,NULL);
	CancelxTEDS();
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
	mm.Async_Init(myPort);
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
			case SDM_ACK:
				printf("SDMAck received\n");
				helloReply = true;
				break;
			case SDM_Register:
				printf("SDMRegister received\n");
				waitForReg = false;
				break;
			case SDM_ID:
				printf("SDMID received\n");
				myID.Unmarshal(buf);
				printf("CompID: \n");
				printf("   SensorID: %li\n", myID.destination.getSensorID());
				printf("    Address: %lx\n", myID.destination.getAddress());
				printf("       Port: %i\n", myID.destination.getPort());
				waitForID = false;					
				break;
			case SDM_Subreqst:
				sub.Unmarshal(buf);
				printf("Subscription Rec'd for %d\n",sub.msg_id.getInterfaceMessagePair());
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
			default:
				printf("Invalid Message found!\n");
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

void RegisterxTEDS()
{
	// create an xTEDS registration message
	SDMxTEDS  xteds;

	// set xTEDS
	strcat (xteds.xTEDS,XML_HEADER);
	strcat (xteds.xTEDS,XTEDS_HEADER);
	strcat (xteds.xTEDS,APP_SECTION);
	strcat (xteds.xTEDS,INTERFACE_SECTION);
	strcat (xteds.xTEDS,VAR_DATA_1);
	strcat (xteds.xTEDS,VAR_DATA_2);
	strcat (xteds.xTEDS,NOTIFICATION);
	strcat (xteds.xTEDS,MSG_ALL_1);
	strcat (xteds.xTEDS,MSG_ALL_2);
	strcat (xteds.xTEDS,MSG_ALL_3);
	strcat (xteds.xTEDS,MSG_ALL_4);
	strcat (xteds.xTEDS,NOTIFICATION_END);
	strcat (xteds.xTEDS,INTERFACE_END);
	strcat (xteds.xTEDS,XTEDS_END);

	// set the id of this application
	xteds.source.setSensorID(1);
	xteds.source.setPort(myPort);
	printf("Registering producer xTEDS on port %ld\n",myPort);
	// register with the SDM
	xteds.Send();
}

void CancelxTEDS()
{
	SDMCancelxTEDS cancel;
	printf("Canceling xTEDS\n");
	cancel.source.setSensorID(1);
	cancel.source.setPort(myPort);
	cancel.Send();
}

double GetCurTime()
{
	struct timespec tv;
	int tv_usec;
	clock_gettime(CLOCK_REALTIME, &tv);
	tv_usec = tv.tv_nsec/1000;
	return tv.tv_sec + ((double)tv_usec/1000000.0);
}
