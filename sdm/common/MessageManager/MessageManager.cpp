#include "MessageManager.h"

#include "../message/SDMmessage.h"
#include "../message/SDMCommand.h"

#include "../UDPcom.h"
#include "../TCPcom.h"
#include "../ErrorUtils.h"

#include <pthread.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <signal.h>

//#define DEBUG_MESSAGEMANAGER 1
#define MM_LISTEN_STACKSZ (65536)
pthread_mutex_t message_manager_lock = PTHREAD_MUTEX_INITIALIZER;

MessageManager::MessageManager():m_port(-1),handlerThread(),tcpThread(),forward_component_id(),forward_command_id(0,0),forward_callback(NULL),UDPsock(0),TCPsock(0),queued(0),max_queued(0),UsingTCP(false),UsingUDP(false)/*,both(false)*/,init_success(false),queue_head(NULL),queue_tail(NULL),semMsgWaitQ(0), semStartup(0), semStartupTCP(0)
{
}

//NOTE: the copy constructor preforms a _shallow_ copy of the data, so that if a Listen thread has been begun any messages received will be available in the copy.
MessageManager::MessageManager(const MessageManager& a):m_port(a.m_port),handlerThread(a.handlerThread),tcpThread(a.tcpThread),forward_component_id(a.forward_component_id),forward_command_id(a.forward_command_id),forward_callback(a.forward_callback),UDPsock(a.UDPsock),TCPsock(a.TCPsock),queued(a.queued),max_queued(a.max_queued),UsingTCP(a.UsingTCP),UsingUDP(a.UsingUDP),/*both(a.both),*/init_success(a.init_success),queue_head(a.queue_head),queue_tail(a.queue_tail),semMsgWaitQ(a.semMsgWaitQ), semStartup(a.semStartup), semStartupTCP(a.semStartupTCP)
{}

MessageManager::~MessageManager()
{
#ifdef DEBUG_MESSAGEMANAGER
 	 printf("MessageManager::~MessageManager\n");
#endif

	//Cancel the listener threads
	if (UsingTCP)
	{
		pthread_cancel(tcpThread);
		TCPshutdown(TCPsock);	// stop blocking call so the thread can detect cancellation
    TCPclose(TCPsock);
		pthread_join(handlerThread, NULL);
	}
	if(UsingUDP)
	{
		pthread_cancel(handlerThread);
		UDPshutdown(UDPsock);	// stop blocking call so the thread can detect cancellation
    UDPclose(UDPsock);
		pthread_join(handlerThread, NULL);
	}
}

void* MessageManager::Listen(void* arg)
{
	MessageManager* MM_ptr = (MessageManager*)arg;
	char buf[BUFSIZE];
	long length = -1;
#ifndef WIN32
	sigset_t signal_set;
#endif
	struct sockaddr_in s;

	MM_ptr->init_success = true;
#ifdef DEBUG_MESSAGEMANAGER
	printf("UDP Message Manager binding port %ld\n",MM_ptr->m_port);
#endif
#ifndef WIN32
	sigfillset(&signal_set);
	pthread_sigmask(SIG_BLOCK, &signal_set, NULL);
#endif
	MM_ptr->UDPsock = UDPpassive(MM_ptr->m_port);
	if(MM_ptr->UDPsock == IP_SOCK_INVALID)
		MM_ptr->init_success = false;

	MM_ptr->semStartup.Signal();
	if(MM_ptr->init_success == false)
	{
#ifdef DEBUG_MESSAGEMANAGER
		printf("MM: %s -- Error binding port.\n", __FUNCTION__);
#endif
		return NULL;
	}

	while(1)
	{
		length = UDPserv_recv(MM_ptr->UDPsock, buf, sizeof(buf));
		pthread_testcancel();
		if (length < 0)
			continue;
#ifdef DEBUG_MESSAGEMANAGER
		printf("UDP Message Manger rec'd message 0x%hhx\n", buf[0]);
#endif
		UDPgetip(&s);
		MM_ptr->AddMessage(buf,length,MM_ptr->UDPsock,false,&s);
//		memset(buf,0,sizeof(buf));
	}
	return NULL;
}

void* MessageManager::ListenTCP(void* arg)
{
	MessageManager* MM_ptr = (MessageManager*)arg;
	char buf[LARGE_MSG_BUFSIZE];
	short sSdmLength;
	struct sockaddr_in sin;
	int iStatus, iCurLength;
	int tcpSock = 0;
	bool bError = false;
#ifndef WIN32
	sigset_t signal_set;
#endif

	MM_ptr->init_success = true;
#ifdef DEBUG_MESSAGEMANAGER
	printf("TCP Message Manager binding port %ld\n",MM_ptr->m_port);
#endif
#ifndef WIN32
	sigfillset(&signal_set);
	pthread_sigmask(SIG_BLOCK, &signal_set, NULL);
#endif
	MM_ptr->TCPsock = TCPpassive(MM_ptr->m_port, MAX_TCP_CONNECTIONS);
	if (MM_ptr->TCPsock == IP_SOCK_INVALID)
		MM_ptr->init_success = false;

	MM_ptr->semStartupTCP.Signal();
	if(MM_ptr->init_success == false)
		return NULL;

	while(1)
	{
		tcpSock = TCPaccept(MM_ptr->TCPsock, &sin);
		if (tcpSock == IP_SOCK_INVALID)
			continue;
		pthread_testcancel();
		//
		// Receive the header of the message
		bError = false;
		iCurLength = 0;
		do
		{
			iStatus = TCPrecv(tcpSock, &buf[iCurLength], LARGE_MSG_BUFSIZE - iCurLength);
			if (iStatus < 0)
			{
				perror("TCPrecv");
				bError = true;
			}
			else if (iStatus == 0)
				bError = true;
			else
				iCurLength += iStatus;
		} while(iCurLength < HEADER_SIZE);
		if (bError)
		{
			TCPclose(tcpSock);
			continue;
		}
		sSdmLength = GET_SHORT(&buf[9]);
		//
		// Receive the rest of the SDM message
		while(sSdmLength > iCurLength - HEADER_SIZE)
		{
			iStatus = TCPrecv(tcpSock, &buf[iCurLength], LARGE_MSG_BUFSIZE - iCurLength);
			if (iStatus < 0)
			{
				perror("TCPrecv");
				bError = true;
			}
			else if (iStatus == 0)
				bError = true;
			else
				iCurLength += iStatus;
		}
		if (bError)
		{
			TCPclose(tcpSock);
			continue;
		}
		
		if(sSdmLength != iCurLength - HEADER_SIZE)
			printf("Error: More bytes recv'd than expected!\n");
#ifdef DEBUG_MESSAGEMANAGER
		printf("TCP Message Manger rec'd message\n");
#endif
		MM_ptr->AddMessage(buf,iCurLength,tcpSock,true,&sin);
//		memset(buf,0,sizeof(buf));
	}
	return NULL;
}




//NOTE: the = operator preforms a _shallow_ copy of the data, so that if a Listen thread has been begun any messages received will be available in the copy.
MessageManager& MessageManager::operator=(const MessageManager& a)
{
	handlerThread = a.handlerThread;
	m_port = a.m_port;
	forward_component_id=a.forward_component_id;
	forward_command_id=a.forward_command_id;
	forward_callback=a.forward_callback;
	UDPsock=a.UDPsock;TCPsock=a.TCPsock;queued=a.queued;
	max_queued=a.max_queued;
	queue_head=a.queue_head;
	queue_tail=a.queue_tail;
	semMsgWaitQ=a.semMsgWaitQ;
	semStartup=a.semStartup;
	return *this;
}
/*
 *  Initialize the UDP listener thread for the MessageManager.
 */
bool MessageManager::Async_Init(long port)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr,MM_LISTEN_STACKSZ);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	//If we are already initialized, return
	if(m_port != -1 && (!UsingTCP && !UsingUDP))
	{
		return false;
	}

	m_port = port;
	if (pthread_create(&handlerThread,&attr,&Listen,this) < 0)
	{
		printf("MessageManager::Error creating UDP listener thread.\n");
		return false;
	}
	UsingUDP = true;
	semStartup.Wait();

	return init_success;
}
/*
 *  Initialize the TCP listener thread for the MessageManager.
 */
bool MessageManager::Async_Init_TCP(long port)
{
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_attr_setstacksize(&attr,MM_LISTEN_STACKSZ);
	pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);

	//If we are already initialized, return
	if(m_port != -1 && (!UsingTCP && !UsingUDP))
	{
		return false;
	}

	m_port = port;
	if(pthread_create(&tcpThread,&attr,&ListenTCP,this) < 0)
	{
		printf("MessageManager::Error creating TCP listener thread.\n");
		return false;
	}
	UsingTCP = true;
	semStartupTCP.Wait();
	return init_success;
}
/*
 *  Initialize both the TCP and UDP listener threads for the MessageManager.
 */
bool MessageManager::Async_Init_Both(long port)
{
	if(Async_Init(port)==false)
		return false;
	if(Async_Init_TCP(port)==false)
		return false;
	UsingTCP = UsingUDP = true;
	return true;
}

void MessageManager::SetForwarding(long count,SDMComponent_ID component_id,SDMMessage_ID command_id,short (*callback) (char*,long))
{
	pthread_mutex_lock(&message_manager_lock);

	max_queued = count;
	forward_component_id = component_id;
	forward_command_id = command_id;
	forward_callback = callback;

	pthread_mutex_unlock(&message_manager_lock);
}

bool MessageManager::IsReady()
{
	bool ready = false;

	pthread_mutex_lock(&message_manager_lock);

	if(queued > 0)
	{
		ready = true;
	}

	pthread_mutex_unlock(&message_manager_lock);
	return ready;
}

message_item* MessageManager::GetHeadEntry()
{
	message_item *temp = NULL;

	pthread_mutex_lock(&message_manager_lock);
	if (queue_head != NULL)
	{
		temp = queue_head;
		queue_head = queue_head->next;

		if (queue_head == NULL)
			queue_tail = NULL;
		--queued;
	}
	else
		printf("MessageManager::GetMsgEntry: Unexpected NULL\n");

	pthread_mutex_unlock(&message_manager_lock);
	return temp;
}

#ifdef WIN32
char MessageManager::GetMsg(char *buf, long& length)
#else
char MessageManager::GetMessage(char* buf,long& length)
#endif
{
	char msg_type = 0;
	message_item* temp;
	length = 0;

	if( semMsgWaitQ.TryWait() == 0 )
	{
		temp = GetHeadEntry();
		if (temp != NULL)
		{
			memcpy(buf,temp->msg,temp->length);
			length = temp->length;
			msg_type = buf[0];
	
			delete[] temp->msg;
			delete temp->sin;
			delete temp;
		}
	}
	return msg_type;
}
#ifdef WIN32
char MessageManager::GetMsg(char * buf)
#else
char MessageManager::GetMessage(char* buf)
#endif
{
  long iLength;
#ifdef WIN32
  return GetMsg(buf, iLength);
#else
  return GetMessage(buf, iLength);
#endif
}
#ifdef WIN32
char MessageManager::GetMsg(char* buf,long& length, SDMComHandle& HandleOut)
#else
char MessageManager::GetMessage(char* buf,long& length, SDMComHandle& HandleOut)
#endif
{
	char msg_type = 0;
	message_item* temp;
	length = 0;

	if( semMsgWaitQ.TryWait() == 0 )
	{
		temp = GetHeadEntry();
		if (temp != NULL)
		{
			memcpy(buf,temp->msg,temp->length);
			length = temp->length;
			msg_type = buf[0];

			HandleOut.Set(temp->socket, temp->tcp, temp->sin);
			
			delete[] temp->msg;
			delete temp->sin;
			delete temp;
		}
	}
	return msg_type;
}

char MessageManager::BlockGetMessage(char* buf,long& length)
{
	char msg_type = 0;
	message_item* temp;
	length = 0;

	if( 0 == semMsgWaitQ.Wait() )
	{
		temp = GetHeadEntry();
		if (temp != NULL)
		{
			memcpy(buf,temp->msg,temp->length);
			length = temp->length;
			delete[] temp->msg;
			delete temp->sin;
			delete temp;
			msg_type = buf[0];
		}
	}
	else
	{
		perror("MessageManager::BlockGetMessage::Sem::Wait");
	}

	return msg_type;
}

char MessageManager::BlockGetMessage(char* buf, long& length, SDMComHandle& HandleOut)
{
	char msg_type = 0;
	message_item* temp;
	length = 0;

	if( semMsgWaitQ.Wait() == 0 )
	{
		temp = GetHeadEntry();

		memcpy(buf,temp->msg,temp->length);
		length = temp->length;
		msg_type = buf[0];

		HandleOut.Set(temp->socket, temp->tcp, temp->sin);
		
		delete[] temp->msg;
		delete temp->sin;
		delete temp;
	}
	return msg_type;
}

char MessageManager::BlockGetMessage(char* buf)
{
	long iLength;

	return BlockGetMessage(buf, iLength);
}



void MessageManager::AddMessage(char* buf, long length, int socket, bool tcp, struct sockaddr_in* sin)
{
	pthread_mutex_lock(&message_manager_lock);
	if ((max_queued != 0)&&(queued >= max_queued))
	{
		//forward message
		SDMCommand forward;
		forward.length = (length > (long)sizeof(forward.data) ? (long)sizeof(forward.data) : length);
		if (forward_callback!= NULL)
			forward.length = forward_callback(buf,length);
		forward.source = forward_component_id;
		forward.command_id = forward_command_id;
		memcpy(forward.data,buf,(forward.length > (long)sizeof(forward.data) ? (long)sizeof(forward.data) : forward.length));
		forward.Send();
	}
	else
	{
		//queue message
		message_item* new_msg = new message_item;
		if (new_msg == NULL)
			ErrorUtils::MemoryAllocError(__FUNCTION__);
		
		new_msg->msg = new char[length];
		if (new_msg->msg == NULL)
			ErrorUtils::MemoryAllocError(__FUNCTION__);
		
		memcpy(new_msg->msg,buf,length);
		new_msg->length = length;
		new_msg->socket = socket;
		new_msg->tcp = tcp;
		new_msg->sin = new sockaddr_in;
		if (new_msg->sin == NULL)
			ErrorUtils::MemoryAllocError(__FUNCTION__);
		
		new_msg->sin->sin_family = sin->sin_family;
		new_msg->sin->sin_port = sin->sin_port;
		new_msg->sin->sin_addr = sin->sin_addr;
		new_msg->next = NULL;
		if (NULL == queue_tail)
		{
			queue_tail = new_msg;
			queue_head = queue_tail;
		}
		else
		{
			queue_tail->next = new_msg;
			queue_tail = new_msg;
		}
		semMsgWaitQ.Signal();
		++queued;
	}
	pthread_mutex_unlock(&message_manager_lock);
}
