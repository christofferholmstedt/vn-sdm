#ifndef __SPA1_MSG_H__
#define __SPA1_MSG_H__

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "../common/message_defs.h"
#define MAX_SPA1_MSG_SIZE	256

/**
* @class Spa1Msg
*
* @brief Defines the Spa1Msg object for use by the SPA-1 Queue objects
*
* @author Bryan Hansen
* @date 12/03/2009
*/
class Spa1Msg
{
public:
  Spa1Msg(int size);
  ~Spa1Msg();

  int getMsgSize();
  int setMsgSize(size_t size);

  ///Pointer to the next Spa1Msg when used in a list
  Spa1Msg* next;

  ///Static array containing the message
  unsigned char msg[257];

private:
  ///The size of the current msg 
  int msgSize;
};

#endif
