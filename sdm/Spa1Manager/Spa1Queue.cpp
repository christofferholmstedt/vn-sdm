#include "Spa1Queue.h"

extern int debug;

/**
* Constructor that creates and intializes a new Spa1Queue object
*/
Spa1Queue::Spa1Queue()
{
   head = NULL;
   tail = NULL;
   msgsInQueue = 0;
}

/**
* Function to retrieve the next message in the queue
*
* @param buf The output buffer the message will be written into
* @param bufSize The size of the output buffer
*
* @return An int containing the size of the msg read into the output buffer,
*         -1 indicates that an error condition has occured
*/
int Spa1Queue::getMsg(/**Output param**/unsigned char* buf, size_t bufSize)
{
   Spa1Msg* curMsg = head;
   int result;
   if (curMsg != NULL) //Check to make sure there is a msg in the queue
   {
      if (bufSize < (unsigned int)curMsg->getMsgSize()) //Check to make sure output buffer is large enough
      {
         printf("Spa1Queue: Error, output buffer not large enough for msg\n");
         result = -1;
      }
      else
      {
         memcpy(buf, curMsg->msg, curMsg->getMsgSize());  //Copy msg into output buffer
         if (head == tail) //If only one msg in queue
         {
            tail = NULL;
         }
         head = head->next;  //Move the head of the list forward
         msgsInQueue--;
         result = curMsg->getMsgSize(); //Set size of data for return

         delete curMsg; // delete the space
      }
   }
   else
   {
      result = 0;  //No bytes to get
   }


   return result;
}

/**
* Function to place a message into the queue
*
* @param buf The buffer containing the message to be added to the queue
* @param bufSize The size of the message to be added in bytes
*
* @return An int to notify success or failure - 0 indicating success, -1 for failure
*/
int Spa1Queue::putMsg(unsigned char* buf, size_t size)
{
   int result = -1;

   if (size <= BUFSIZE) //Check if msg is larger than the max SDM Msg size
   {
      Spa1Msg* newMsg = new Spa1Msg(size);
      memcpy(newMsg->msg, buf, size);
      newMsg->next = NULL;
      newMsg->setMsgSize(size);

      if (tail != NULL)
      {
         tail->next = newMsg;
         tail = newMsg;
      }
      else  //Empty queue
      {
         head = newMsg;
         tail = newMsg;
      }
      msgsInQueue++;
      result = 0;
   }
   return result;
}

/**
* Function to return the number of messages currently in the queue
*
* @return An int containing the number of msgs currently in the queue
*/
int Spa1Queue::getNumMsgs()
{
   return msgsInQueue;
}
