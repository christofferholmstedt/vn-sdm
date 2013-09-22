#include "Spa1Msg.h"

extern int debug;

/**
* Constructor that creates a Spa1Msg object with a msg buffer of the size
* passed in as a parameter
*
* @param size The size of a msg, must be less than or equal to 256 bytes
*/
Spa1Msg::Spa1Msg(int size) : msgSize (0)
{
   if (size > MAX_SPA1_MSG_SIZE)
   {
      printf("Spa1Msg: Error, requested msg larger than the maximum SPA-1 msg size\n");
		msgSize = MAX_SPA1_MSG_SIZE;
   }
   else
   {
      msgSize = size;
   }
}

/**
* Destructor
*/
Spa1Msg::~Spa1Msg()
{
}

/**
* Returns the size of the Spa1Msg objects msg buffer
*
* @return An int containing the size of the msg buffer
*/
int Spa1Msg::getMsgSize()
{
   return msgSize;
}

/**
 * Sets the message size of a Spa1Msg
 *
 * @param  size Specifies the size of the buffer to allocate, should be
 *         between 0 and 256 bytes.
 * @return An int, 0 indicating success, -1 indicating a failure
 */
int Spa1Msg::setMsgSize(size_t size)
{
   int status = -1;
   if (size < MAX_SPA1_MSG_SIZE && size >= 0)
   {
      msgSize = size;
      status = 0;
   }
   return status;
}
