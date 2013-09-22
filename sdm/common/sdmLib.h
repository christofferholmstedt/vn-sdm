#ifndef _SDM_LIB_H_
#define _SDM_LIB_H_

/* Misc. library and API macros*/

#ifdef WIN32
// Function deprecation attributes, empty for a Windows build.
#  define SDM_DEPRECATED
// The following ifdef block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the SDMLIB_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// SDMLIB_API functions as being imported from a DLL, whereas this DLL sees symbols
// defined with this macro as being exported.
#  ifdef SDMLIB_EXPORTS
#    define SDMLIB_API __declspec(dllexport)
#  else
#    define SDMLIB_API __declspec(dllimport)
#  endif
#else
#  define SDMLIB_API
#  define SDM_DEPRECATED /*__attribute__((deprecated));*/
#endif 

#endif 
