#include <byteswap.h>
#include <string.h>
#include <stdio.h>

#define BSWAP_2(d, s) ((char*)(d))[0] = ((char*)(s))[1], ((char*)(d))[1] = ((char*)(s))[0]
#define BSWAP_4(d, s) ((char*)(d))[0] = ((char*)(s))[3], ((char*)(d))[1] = ((char*)(s))[2], ((char*)(d))[2] = ((char*)(s))[1], ((char*)(d))[3] = ((char*)(s))[0]
#define BSWAP_8(d, s) ((char*)(d))[0] = ((char*)(s))[7], ((char*)(d))[1] = ((char*)(s))[6], ((char*)(d))[2] = ((char*)(s))[5], ((char*)(d))[3] = ((char*)(s))[4], ((char*)(d))[4] = ((char*)(s))[3], ((char*)(d))[5] = ((char*)(s))[2], ((char*)(d))[6] = ((char*)(s))[1], ((char*)(d))[7] = ((char*)(s))[0]

unsigned long long _marshall_get64(const void *pBuf)
{
  unsigned long long i;
  BSWAP_8(&i, pBuf);

  return i;
}

double _marshall_getdouble(const void *pBuf)
{
  double d;
  BSWAP_8(&d, pBuf);

  return d;
}


unsigned long _marshall_get32(const void *pBuf)
{
  unsigned long i;
  BSWAP_4(&i, pBuf);

  return i;
}


float _marshall_getfloat(const void *pBuf)
{
  float f;
  BSWAP_4(&f, pBuf);

  return f;
}


unsigned short _marshall_get16(const void *pBuf)
{
  unsigned short i;
  BSWAP_2(&i, pBuf);

  return i;
}

unsigned char _marshall_get8(const void *pBuf)
{
  return *(unsigned char*)(pBuf);
}

void _marshall_put64(void *pBuf, unsigned long long iVal)
{
  BSWAP_8(pBuf, &iVal);
}

void _marshall_putdouble(void *pBuf, double dVal)
{
  BSWAP_8(pBuf, &dVal);
}

void _marshall_put32(void *pBuf, unsigned long iVal)
{
  BSWAP_4(pBuf, &iVal);
}

void _marshall_putfloat(void *pBuf, float fVal)
{
  BSWAP_4(pBuf, &fVal);
}

void _marshall_put16(void *pBuf, unsigned short iVal)
{
  BSWAP_2(pBuf, &iVal);
}

void _marshall_put8(void *pBuf, unsigned char iVal)
{
  *(unsigned char*)pBuf = iVal;
}
