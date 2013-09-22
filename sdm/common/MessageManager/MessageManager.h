#ifndef __MESSAGE_MANAGER_H_
#define __MESSAGE_MANAGER_H_

#include "../message/SDMmessage.h"
#include "../message/SDMComponent_ID.h"
#include "../message/SDMMessage_ID.h"
#include "../semaphore/semaphore.h"
#include "../SDMComHandle.h"
#include "../sdmLib.h"

typedef struct msg_list_node
{
	char* msg;
	int length;
	int socket;
	bool tcp;
	struct sockaddr_in *sin;
	struct msg_list_node* next;
} message_item;

class SDMLIB_API MessageManager
{
public:
	MessageManager();
	MessageManager(const MessageManager&);
	~MessageManager();

	MessageManager& operator=(const MessageManager&);

	bool Async_Init(long port);
	bool Async_Init_TCP(long port);
	bool Async_Init_Both(long port);
	bool IsReady();
/*Windows has a WIN32 API function called GetMessage, so this needs to be renamed under Windows */
#ifdef WIN32
	char GetMsg(char * buf);
	char GetMsg(char * buf, long& length);
	char GetMsg(char* buf,long& length, SDMComHandle& HandleOut /* output param */);
#else
	char GetMessage(char* buf);
	char GetMessage(char* buf,long& length);
	char GetMessage(char* buf,long& length, SDMComHandle& HandleOut /* output param */);
#endif
	char BlockGetMessage(char* buf);
	char BlockGetMessage(char* buf,long& length);
	char BlockGetMessage(char* buf, long& length, SDMComHandle& HandleOut /* output param */);
	void AddMessage(char* buf,long length,int socket,bool tcp,struct sockaddr_in* sin);
	void SetForwarding(long count,SDMComponent_ID component_id,SDMMessage_ID command_id,short (*callback) (char*,long));
	long m_port;
private:
	static void* Listen(void* arg);
	static void* ListenTCP(void* arg);

	pthread_t handlerThread, tcpThread;
	SDMComponent_ID forward_component_id;
	SDMMessage_ID forward_command_id;
	short (*forward_callback) (char*,long);
	int UDPsock;
	int TCPsock;
	int queued;
	int max_queued;
	bool UsingTCP;				//If true, the MM is listening on TCP
	bool UsingUDP;				//If true, the MM is listening on UDP
	bool init_success;
	message_item* queue_head;
	message_item* queue_tail;
	message_item* GetHeadEntry();

	Sem semMsgWaitQ;
	Sem semStartup;
	Sem semStartupTCP;
};

#endif
