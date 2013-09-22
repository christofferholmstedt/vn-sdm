// sdmLib.cpp : Defines the entry point for the DLL application.
//

#include <winsock2.h>
#include "sdmLib.h"
BOOL APIENTRY DllMain( HANDLE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	unsigned short wVersionRequested;
	WSADATA wsaData;
	int err;
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		wVersionRequested = MAKEWORD( 2, 2 );
		err = WSAStartup( wVersionRequested, &wsaData );
		if ( err != 0 ) {
			// Tell the user that we could not find a usable WinSock DLL.
			return -1;
		}
		break;
	case DLL_THREAD_ATTACH:
		break;
	case DLL_THREAD_DETACH:
		break;
	case DLL_PROCESS_DETACH:
		WSACleanup();
		break;
	}
    return TRUE;
}

// This is an example of an exported variable
SDMLIB_API int nsdmLib=0;

// This is an example of an exported function.
SDMLIB_API int fnsdmLib(void)
{
	return 42;
}

// This is the constructor of a class that has been exported.
// see sdmLib.h for the class definition
//CsdmLib::CsdmLib()
//{
//	return;
//}
