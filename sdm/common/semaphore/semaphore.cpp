#include <stdio.h>
#include <errno.h>

#include "semaphore.h"

//#define DEBUG_SEMAPHORE 1

Sem::Sem(int16_t i16InitialValue):m_i16Value(i16InitialValue),m_i16WaitCount(0),m_valueMutex(),m_valueCond()
{
  pthread_mutex_init(&m_valueMutex, NULL);
  pthread_cond_init(&m_valueCond, NULL);


#ifdef DEBUG_SEMAPHORE
  printf("Sem::Sem::Initialized semaphore with value %d\n", m_i16Value);
#endif
}

Sem::Sem ():m_i16Value(0),m_i16WaitCount(0),m_valueMutex(),m_valueCond()
{
  Sem(0);
}

Sem::Sem(const Sem &semRhs):m_i16Value(0),m_i16WaitCount(0),m_valueMutex(semRhs.m_valueMutex),m_valueCond()
{

  pthread_mutex_lock(&m_valueMutex);

  m_i16Value   = semRhs.m_i16Value;
  m_valueCond  = semRhs.m_valueCond;

  pthread_mutex_unlock(&m_valueMutex);
}

Sem::~Sem()
{
  pthread_mutex_destroy(&m_valueMutex);
  pthread_cond_destroy(&m_valueCond);
}

Sem& Sem::operator=(const Sem& semRhs)
{
  if (this != &semRhs) 
  { 
    m_i16Value = semRhs.m_i16Value;
    m_valueCond = semRhs.m_valueCond;
    m_i16WaitCount = semRhs.m_i16WaitCount;
  }
  return *this;
}

int Sem::Signal()
{
  pthread_mutex_lock(&m_valueMutex);
  m_i16Value ++;
#ifdef DEBUG_SEMAPHORE
  printf("Sem::Signal::Value After%d WaitCount: %d\n", m_i16Value, m_i16WaitCount);
#endif
  if(m_i16Value > 0)
    {
      pthread_cond_signal(&m_valueCond);
      m_i16WaitCount--;
    }
  pthread_mutex_unlock(&m_valueMutex);
  return 0;
}

int Sem::Wait()
{
  pthread_mutex_lock(&m_valueMutex);
  m_i16WaitCount++;
#ifdef DEBUG_SEMAPHORE
  printf("Sem::Wait::Value Before %d WaitCount: %d\n", m_i16Value, m_i16WaitCount);
#endif
  while(m_i16Value <= 0)
    {
      pthread_cond_wait(&m_valueCond, &m_valueMutex);
    }
  m_i16Value --;
  pthread_mutex_unlock(&m_valueMutex);
  return 0;
}

int Sem::TryWait()
{
  int iRetVal;

  iRetVal = -1;
  pthread_mutex_lock(&m_valueMutex);
#ifdef DEBUG_SEMAPHORE
  printf("Sem::TryWait::Value Before %d\n", m_i16Value);
#endif
  if(m_i16Value > 0)
    {
      m_i16Value --;
      iRetVal = 0;
    }
  pthread_mutex_unlock(&m_valueMutex);
  return iRetVal;
}

short Sem::GetWaitCount()
{
  pthread_mutex_lock(&m_valueMutex);
  short iRetVal = m_i16WaitCount;
  pthread_mutex_unlock(&m_valueMutex);
  return iRetVal;
}
