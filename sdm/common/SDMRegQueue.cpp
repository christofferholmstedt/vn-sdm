#include "SDMRegQueue.h"

void SDMRegQueue::add(SDMComponent_ID toAdd)
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


SDMComponent_ID SDMRegQueue::dequeue(void)
{
   if(headIndex == tailIndex)
   {
      printf("Queue is empty\n");
      SDMComponent_ID empty;
      return empty;
   }

   SDMComponent_ID toReturn = queue[headIndex];
   headIndex++;
   if(headIndex == SIZE - 1)
   {
      headIndex = 0;
   }
   return toReturn;
}

int SDMRegQueue::size(void)
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

bool SDMRegQueue::find(const SDMComponent_ID& toFind)
{
   int first = 0;

   if(headIndex >= 0)
   {
      first = headIndex;
   }

   if(headIndex < tailIndex)  //Check queue, no wrap
   {
      for(int i = first; i < tailIndex; i++)
      {
         if(queue[i] == toFind)
         {
            return true;
         }
      }
   }
   else if(tailIndex < headIndex)   //If you have to wrap around
   {
      for(int i = first; i < SIZE; i++)
      {
         if(queue[i] == toFind)
         {
            return true;
         }
      }
      for(int i = 0; i < tailIndex; i++)
      {
         if(queue[i] == toFind)
         {
            return true;
         }
      }
   }
   return false;
}

