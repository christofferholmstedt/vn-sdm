#ifndef SDM_REG_QUEUE_H
#define SDM_REG_QUEUE_H

#include <stdio.h>
#include <string.h>
#include "message/SDMComponent_ID.h"

#define SIZE   100

//Used to queue up incoming requests to register with the SDM
class SDMLIB_API SDMRegQueue
{
   public:
      SDMRegQueue(): headIndex(0), tailIndex(0)
      {
      }

      void add(SDMComponent_ID toAdd);
      SDMComponent_ID dequeue(void);
      int size(void);
      bool find(const SDMComponent_ID& toFind);

   private:
      SDMComponent_ID queue[SIZE];
      int headIndex;
      int tailIndex;
};

#endif
