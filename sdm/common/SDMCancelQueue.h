#ifndef SDM_CANCEL_QUEUE_H
#define SDM_CANCEL_QUEUE_H

#include <stdio.h>
#include <string.h>
#include "../dm/xTEDSParameters.h"

#define SIZE   100

//Used to queue up incoming xTEDS cancelations
class SDMLIB_API SDMCancelQueue
{
   public:
      SDMCancelQueue(): headIndex(0), tailIndex(0)
      {
      }

      void add(xTEDSParameters* toAdd);
      xTEDSParameters* dequeue(void);
      int size(void);

   private:
      xTEDSParameters* queue[SIZE];
      int headIndex;
      int tailIndex;
};

#endif
