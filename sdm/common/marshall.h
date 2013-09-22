#ifndef __SDM_MARSHALL_H_
#define __SDM_MARSHALL_H_

#ifndef __VXWORKS__
#include <endian.h>	// Determine the byte order of the target CPU
#include <byteswap.h>	//For byteswap macros
#else
#define bswap_32(x) ( ((0x000000FF&x) << 24) | ((0x0000FF00&x) << 8) | ((0x00FF0000&x) >> 8) | ((0xFF000000&x) >> 24) )
#define bswap_16(x) ((((x) >> 8) & 0xff) | (((x) & 0xff) << 8))
#define bswap_64(x) ((((x) & 0xff00000000000000ull) >> 56) \
| (((x) & 0x00ff000000000000ull) >> 40)     \
| (((x) & 0x0000ff0000000000ull) >> 24)     \
| (((x) & 0x000000ff00000000ull) >> 8)      \
| (((x) & 0x00000000ff000000ull) << 8)      \
| (((x) & 0x0000000000ff0000ull) << 24)     \
| (((x) & 0x000000000000ff00ull) << 40)     \
| (((x) & 0x00000000000000ffull) << 56))
#endif
/* SDM network byte order is little endian, which is the reverse of the
 * traditional network order.  Hence, these macros are nontrivial when
 * ntohl(), htonl(), etc. are trivial and vice versa.
 */



#ifndef __uClinux__
#if __BYTE_ORDER == __LITTLE_ENDIAN
#define SDM_ntohs(x)   (x)
#define SDM_htons(x)   (x)
#define SDM_ntohl(x)   (x)
#define SDM_htonl(x)   (x)
#define SDM_ntohll(x)  (x)
#define SDM_htonll(x)  (x)
#else
#define SDM_ntohs(x)   bswap_16 (x)
#define SDM_htons(x)   bswap_16 (x)
#define SDM_ntohl(x)   bswap_32 (x)
#define SDM_htonl(x)   bswap_32 (x)
#define SDM_ntohll(x)  bswap_64 (x)
#define SDM_htonll(x)  bswap_64 (x)
#endif
#endif

#ifndef __VXWORKS__
// Unmarshalling macros - generic
#define GET_TYPE1(type,ptr) (type)(*ptr)
#define GET_TYPE2(type,ptr) (type)(SDM_ntohs(*reinterpret_cast<const type *>(ptr)))
#define GET_TYPE4(type,ptr) (type)(SDM_ntohl(*reinterpret_cast<const type *>(ptr)))
#define GET_TYPE8(type,ptr) (type)(SDM_ntohll(*reinterpret_cast<const type *>(ptr)))

// Unmarshalling macros - these assume a 32-bit architecture
#define GET_CHAR(ptr)   GET_TYPE1 (char, ptr)
#define GET_UCHAR(ptr)  GET_TYPE1 (unsigned char, ptr)
#define GET_SHORT(ptr)  GET_TYPE2 (short, ptr)
#define GET_USHORT(ptr) GET_TYPE2 (unsigned short, ptr)
#define GET_INT(ptr)    GET_TYPE4 (int, ptr)
#define GET_UINT(ptr)   GET_TYPE4 (unsigned int, ptr)
#define GET_LONG(ptr)   GET_TYPE4 (long, ptr)
#define GET_ULONG(ptr)  GET_TYPE4 (unsigned long, ptr)
#define GET_FLOAT(ptr)  GET_TYPE4 (float, ptr)
#define GET_DOUBLE(ptr) GET_TYPE8 (double, ptr)

// Marshalling macros - generic
#define PUT_TYPE1(type,ptr,val) (*ptr) = ((type) val)
#define PUT_TYPE2(type,ptr,val) *reinterpret_cast<type *>(ptr) = SDM_htons(val)
#define PUT_TYPE4(type,ptr,val) *reinterpret_cast<type *>(ptr) = SDM_htonl(val)
#define PUT_TYPE8(type,ptr,val) *reinterpret_cast<type *>(ptr) = SDM_htonll(val)

// Marshalling macros - these assume a 32-bit architecture
#define PUT_CHAR(ptr,val)   PUT_TYPE1 (char,ptr, val)
#define PUT_UCHAR(ptr,val)  PUT_TYPE1 (unsigned char,ptr, val)
#define PUT_SHORT(ptr,val)  PUT_TYPE2 (short,ptr, val)
#define PUT_USHORT(ptr,val) PUT_TYPE2 (unsigned short,ptr, val)
#define PUT_INT(ptr,val)    PUT_TYPE4 (int,ptr, val)
#define PUT_UINT(ptr,val)   PUT_TYPE4 (unsigned int,ptr, val)
#define PUT_LONG(ptr,val)   PUT_TYPE4 (long,ptr, val)
#define PUT_ULONG(ptr,val)  PUT_TYPE4 (unsigned long,ptr, val)
#define PUT_FLOAT(ptr,val)  PUT_TYPE4 (float,ptr, val)
#define PUT_DOUBLE(ptr,val) PUT_TYPE8 (double,ptr, val)


#elif defined(__uClinux__)

#ifdef __cplusplus
extern "C" {
#endif 
extern unsigned long long _marshall_get64(const void *pBuf);
extern double             _marshall_getdouble(const void *pBuf);
extern unsigned long      _marshall_get32(const void *pBuf);
extern float              _marshall_getfloat(const void *pBuf);
extern unsigned short     _marshall_get16(const void *pBuf);
extern unsigned char      _marshall_get8(const void *pBuf);
extern void               _marshall_put64(void *pBuf, unsigned long long iVal);
extern void               _marshall_putdouble(void *pBuf, double dVal);
extern void               _marshall_put32(void *pBuf, unsigned long iVal);
extern void               _marshall_putfloat(void *pBuf, float fVal);
extern void               _marshall_put16(void *pBuf, unsigned short iVal);
extern void               _marshall_put8(void *pBuf, unsigned char iVal);

#define SDM_ntohs(x)   (x)
#define SDM_htons(x)   (x)
#define SDM_ntohl(x)   (x)
#define SDM_htonl(x)   (x)
#define SDM_ntohll(x)  (x)
#define SDM_htonll(x)  (x)

// Unmarshalling macros - these assume a 32-bit architecture
#define GET_CHAR(ptr)   ((char)           _marshall_get8(ptr))
#define GET_UCHAR(ptr)  ((unsigned char)  _marshall_get8(ptr))
#define GET_SHORT(ptr)  ((short)          _marshall_get16(ptr))
#define GET_USHORT(ptr) ((unsigned short) _marshall_get16(ptr))
#define GET_INT(ptr)    ((int)            _marshall_get32(ptr))
#define GET_UINT(ptr)   ((unsigned int)   _marshall_get32(ptr))
#define GET_LONG(ptr)   ((long)           _marshall_get32(ptr))
#define GET_ULONG(ptr)  ((unsigned long)  _marshall_get32(ptr))
#define GET_FLOAT(ptr)  ((float)          _marshall_getfloat(ptr))
#define GET_DOUBLE(ptr) ((double)         _marshall_getdouble(ptr))



// Marshalling macros - these assume a 32-bit architecture
#define PUT_CHAR(ptr,val)   _marshall_put8(ptr, val)
#define PUT_UCHAR(ptr,val)  _marshall_put8(ptr, val)
#define PUT_SHORT(ptr,val)  _marshall_put16(ptr, val)
#define PUT_USHORT(ptr,val) _marshall_put16(ptr, val)
#define PUT_INT(ptr,val)    _marshall_put32(ptr, val)
#define PUT_UINT(ptr,val)   _marshall_put32(ptr, val)
#define PUT_LONG(ptr,val)   _marshall_put32(ptr, val)
#define PUT_ULONG(ptr,val)  _marshall_put32(ptr, val)
#define PUT_FLOAT(ptr,val)  _marshall_putfloat(ptr, val)
#define PUT_DOUBLE(ptr,val) _marshall_putdouble(ptr, val)

#ifdef  __cplusplus
}
#endif

#else
#ifdef __cplusplus
extern "C" {
#endif 
extern unsigned long long _marshall_get64(const void *pBuf);
extern double             _marshall_getdouble(const void *pBuf);
extern unsigned long      _marshall_get32(const void *pBuf);
extern float              _marshall_getfloat(const void *pBuf);
extern unsigned short     _marshall_get16(const void *pBuf);
extern unsigned char      _marshall_get8(const void *pBuf);
extern void               _marshall_put64(void *pBuf, unsigned long long iVal);
extern void               _marshall_putdouble(void *pBuf, double dVal);
extern void               _marshall_put32(void *pBuf, unsigned long iVal);
extern void               _marshall_putfloat(void *pBuf, float fVal);
extern void               _marshall_put16(void *pBuf, unsigned short iVal);
extern void               _marshall_put8(void *pBuf, unsigned char iVal);

#define SDM_ntohs(x)   (x)
#define SDM_htons(x)   (x)
#define SDM_ntohl(x)   (x)
#define SDM_htonl(x)   (x)
#define SDM_ntohll(x)  (x)
#define SDM_htonll(x)  (x)

// Unmarshalling macros - these assume a 32-bit architecture
#define GET_CHAR(ptr)   ((char)           _marshall_get8(ptr))
#define GET_UCHAR(ptr)  ((unsigned char)  _marshall_get8(ptr))
#define GET_SHORT(ptr)  ((short)          _marshall_get16(ptr))
#define GET_USHORT(ptr) ((unsigned short) _marshall_get16(ptr))
#define GET_INT(ptr)    ((int)            _marshall_get32(ptr))
#define GET_UINT(ptr)   ((unsigned int)   _marshall_get32(ptr))
#define GET_LONG(ptr)   ((long)           _marshall_get32(ptr))
#define GET_ULONG(ptr)  ((unsigned long)  _marshall_get32(ptr))
#define GET_FLOAT(ptr)  ((float)          _marshall_getfloat(ptr))
#define GET_DOUBLE(ptr) ((double)         _marshall_getdouble(ptr))



// Marshalling macros - these assume a 32-bit architecture
#define PUT_CHAR(ptr,val)   _marshall_put8(ptr, val)
#define PUT_UCHAR(ptr,val)  _marshall_put8(ptr, val)
#define PUT_SHORT(ptr,val)  _marshall_put16(ptr, val)
#define PUT_USHORT(ptr,val) _marshall_put16(ptr, val)
#define PUT_INT(ptr,val)    _marshall_put32(ptr, val)
#define PUT_UINT(ptr,val)   _marshall_put32(ptr, val)
#define PUT_LONG(ptr,val)   _marshall_put32(ptr, val)
#define PUT_ULONG(ptr,val)  _marshall_put32(ptr, val)
#define PUT_FLOAT(ptr,val)  _marshall_putfloat(ptr, val)
#define PUT_DOUBLE(ptr,val) _marshall_putdouble(ptr, val)

#ifdef  __cplusplus
}
#endif

#endif

#endif
