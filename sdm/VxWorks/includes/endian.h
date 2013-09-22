#ifndef __endian_h_
#define __endian_h_

#ifdef _WIN32
#define __BYTE_ORDER __LITTLE_ENDIAN
#define __LITTLE_ENDIAN
#endif

//This assumes that the VxWorks host being used is big endian (PPC750FX, SPARC LEON3)
#ifdef __VXWORKS__
#define __BIG_ENDIAN
#endif

#endif // __endian_h_

