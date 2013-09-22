#ifndef __SPA1_QUEUE_H__
#define __SPA1_QUEUE_H__

#include <unistd.h>
#include <string.h>
#include "Spa1Msg.h"
#include "../common/message_defs.h"

/** 
* @class Spa1Queue
*
* @brief Defines the Spa1Queue object for use by the SPA-1 Sensor Manager
* 
* The Spa1Queue is used by the SPA-1 Sensor manager to queue up incoming and
* outgoing messages for each ASIM.  
*
* @author Bryan Hansen
* @date 12/03/2009
*/
class Spa1Queue
{
public:
  Spa1Queue();
  int getMsg(unsigned char* buf, size_t bufSize);
  int putMsg(unsigned char* buf, size_t size);
  int getNumMsgs();

private:
  ///Pointer to the start of the queue
  Spa1Msg* head;

  ///Pointer to the end of the queue
  Spa1Msg* tail;

  ///Number of messages currently in the queue
  int msgsInQueue;
};

#endif