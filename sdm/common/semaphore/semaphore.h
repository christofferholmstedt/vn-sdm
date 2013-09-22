#ifndef __SEM_H_
#define __SEM_H_

#include <pthread.h>
#include <stdint.h>

#include "../sdmLib.h"

class SDMLIB_API Sem
{
 public:
  Sem(int16_t i16InitialValue);
  Sem();
  Sem(const Sem &semRhs);
  ~Sem();
  Sem& operator=(const Sem &semRhs);
  int Signal();
  int Wait();
  int TryWait();
  short GetWaitCount();
  short Getil6Value();

 private:
  int16_t m_i16Value;
  int16_t m_i16WaitCount;
  pthread_mutex_t m_valueMutex;
  pthread_cond_t  m_valueCond;

};

#endif
