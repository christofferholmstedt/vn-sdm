#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../../common/message/SDMDeletesub.h"
#include "../../common/message/SDMSubreqst.h"
#include "../../common/message/SDMCommand.h"
#include "../../common/message/SDMSerreqst.h"
#include "../../common/message/SDMReady.h"
#include "../../common/message/SDMConsume.h"
#include "../../common/message/SDMCancel.h"
#include "../../common/TCPcom.h"



int main(int argc, char ** argv)
{
	int sock;
	int length;
	char msg_buf[BUFSIZE];
	SDMSubreqst sub_msg;
	SDMDeletesub delsub_msg;
	SDMCommand cmd_msg;
	SDMSerreqst ser_msg;
	SDMConsume cons_msg;
	SDMReady ready_msg;
	SDMCancel can_msg;
	char buf[11];
	
	printf("\n**Make sure the DM and SM have debug levels at least one to see the messages received.**\n\n");
	
	printf("Finding data manager...");
	sock = TCPconnect("127.0.0.1", PORT_DM);
	if (sock > 0)
		printf("Done.\n");
	else
	{
		printf("Error.  Try again.\n");
		return -1;
	}
	//
	// Send a consume message
	cons_msg.msg_id.setInterface(5);
	cons_msg.msg_id.setMessage(5);
	length = cons_msg.Marshal(msg_buf);
	printf("Sending SDMConsume message to DM...");
	if (TCPsend (sock, msg_buf, length) > 0)
		printf("Done.\n");
	else
		printf("Error.\n");
	
	//
	// Send a ready message
	sock = TCPconnect("127.0.0.1", PORT_DM);
	length = ready_msg.Marshal(msg_buf);
	printf("Sending SDMReady message to DM...");
	if (TCPsend (sock, msg_buf, length) >=0)
		printf("Done.\n");
	else
		printf("Error.\n");
	
	//
	// Send a ready message in segments
	sock = TCPconnect("127.0.0.1", PORT_DM);
	printf("Sending SDMReady message to DM in segments...");

	if(TCPsend(sock, msg_buf, 8) > 0)
		printf("Sending header done. ...");
	else
		printf("Error sending header. ...");
	
	sleep(1);
	if(TCPsend(sock, msg_buf + 8, 13) >= 0)
		printf("Sending destination done.\n");
	else
		printf("Error sending destination.\n");

	sleep(1);
	if(TCPsend(sock, msg_buf + 21, 10) >= 0)
		printf("Sending destination done.\n");
	else
		printf("Error sending destination.\n");

	//
	// Send a command message
	sock = TCPconnect("127.0.0.1", PORT_DM);
	cmd_msg.command_id.setInterface(5);
	cmd_msg.command_id.setMessage(5);
	length = cmd_msg.Marshal(msg_buf);
	
	printf("Sending SDMCommand message...");
	if (TCPsend (sock, msg_buf, length) >=0)
		printf("Done.\n");
	else
		printf("Error.\n");
	
	sock = TCPconnect("127.0.0.1", PORT_DM);
	can_msg.msg_id.setInterface(5);
	can_msg.msg_id.setMessage(5);
	length = can_msg.Marshal(msg_buf);
	
	printf("Sending SDMSerreqst message...");
	if (TCPsend (sock, msg_buf, length) >=0)
		printf("Done.\n");
	else
		printf("Error.\n");
	
	fflush(NULL);
	
	//TEST SENSOR MANAGER's TCP LISTENER
	
	printf("Finding sensor manager...");
	sock = TCPconnect("127.0.0.1", PORT_SM);
	if (sock >= 0)
		printf("Done.\n");
	else
	{
		printf("Error.  Try again.\n");
		return 1;
	}
	
	sub_msg.msg_id.setInterface(5);
	sub_msg.msg_id.setMessage(5);
	sub_msg.source.setSensorID(1);
	length = sub_msg.Marshal(msg_buf);
	
	printf("Sending SDMSubreqst message to SM...");
	if (TCPsend (sock, msg_buf, length) >=0)
		printf("Done.\n");
	else
		printf("Error.\n");
	
	sock = TCPconnect("127.0.0.1", PORT_SM);
	delsub_msg.msg_id.setInterface(5);
	delsub_msg.msg_id.setMessage(5);
	length = delsub_msg.Marshal(msg_buf);
	
	printf("Sending SDMDeletesub message to SM...");
	if (TCPsend (sock, msg_buf, length) >=0)
		printf("Done.\n");
	else
		printf("Error.\n");
	
	sock = TCPconnect("127.0.0.1", PORT_SM);
	cmd_msg.command_id.setInterface(5);
	cmd_msg.command_id.setMessage(5);
	length = cmd_msg.Marshal(msg_buf);
	
	printf("Sending SDMCommand message to SM...");
	if (TCPsend (sock, msg_buf, length) >=0)
		printf("Done.\n");
	else
		printf("Error.\n");
	
	sock = TCPconnect("127.0.0.1", PORT_SM);
	ser_msg.command_id.setInterface(5);
	ser_msg.command_id.setMessage(5);
	length = ser_msg.Marshal(msg_buf);
	
	printf("Sending SDMSerreqst message to SM...");
	if (TCPsend (sock, msg_buf, length) >=0)
		printf("Done.\n");
	else
		printf("Error.\n");
	
	fflush(NULL);
	return 0;
}
