#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include "../../../common/SubscriptionManager/SubscriptionManager.h"
#include "../../../common/message/SDMSubreqst.h"
#include "../../../common/message/SDMDeletesub.h"
#include "../../../common/message/SDMSerreqst.h"


int main(int argc, char ** argv)
{
	SubscriptionManager sm;
	SDMSubreqst sub_msg;
	SDMSerreqst ser_msg;
	SDMDeletesub del_msg;
	
	sub_msg.msg_id.setInterface(1);
	sub_msg.msg_id.setMessage(2);
	sub_msg.destination.setAddress(inet_addr("127.0.0.1"));
	sub_msg.destination.setPort(4050);
	sm.AddSubscription(sub_msg) ? printf("First added\n") : printf("First not added\n");
	sm.AddSubscription(sub_msg) ? printf("Second added\n") : printf("Second not added\n");
	
	ser_msg.reply_id.setInterface(1);
	ser_msg.reply_id.setMessage(3);
	sub_msg.destination.setAddress(inet_addr("127.0.0.1"));
	sub_msg.destination.setPort(4050);
	sm.AddSubscription(ser_msg) ? printf("Third added\n") : printf("Third not added\n");
	sub_msg.destination.setPort(4051);
	sm.AddSubscription(ser_msg) ? printf("Fourth added\n") : printf("Fourth not added\n");
	
	sm.Publish(1,3,"A",1);
	return 0;
}
