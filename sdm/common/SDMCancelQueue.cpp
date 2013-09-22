#include "SDMCancelQueue.h"

void SDMCancelQueue::add(xTEDSParameters* toAdd)
{
   if(tailIndex + 1 == headIndex || (tailIndex + 1 == SIZE - 1 && headIndex == 0))
   {
      printf("Queue is full\n");
      return;
   }

   if(tailIndex == SIZE - 1)
   {
      tailIndex = 0;
   }
   queue[tailIndex] = toAdd;
   tailIndex++;
}


xTEDSParameters* SDMCancelQueue::dequeue(void)
{
   if(headIndex == tailIndex)
   {
      printf("Queue is empty\n");
		return NULL;
   }

   xTEDSParameters* toReturn = queue[headIndex];
   headIndex++;
   if(headIndex == SIZE - 1)
   {
      headIndex = 0;
   }
   return toReturn;
}


int SDMCancelQueue::size(void)
{
   int size = 0;
   if(headIndex == tailIndex)
   {
      size = 0;
   }
   else if(headIndex < tailIndex)
   {
      size = tailIndex - headIndex;
   }
   else
   {
      size = (SIZE - headIndex) + tailIndex;
   }

   return size;
}
