#include <string.h>
#include "xTEDSWrapper.h"

xTEDSWrapper::xTEDSWrapper():Type(WRAPPER_EMPTY),InterfaceName(NULL),InterfaceID(-1)
{
}

xTEDSWrapper::~xTEDSWrapper()
{
	if (InterfaceName != NULL)
		free (InterfaceName);
}

void xTEDSWrapper::setInterfaceName(const char* Name)
{
	if (InterfaceName != NULL)
		free(InterfaceName);
	InterfaceName = strdup(Name);
}

void xTEDSWrapper::setInterfaceID(int ID)
{
	InterfaceID = ID;
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSWrapper::PrintDebug() const
{
	char TypeStr[128];
	
	switch(Type)
	{
		case WRAPPER_NOTIFICATION:	
      strcpy(TypeStr, "WRAPPER_NOTIFICATION"); 
      break;
		case WRAPPER_REQUEST:  		
      strcpy(TypeStr, "WRAPPER_REQUEST"); 
      break;
		case WRAPPER_COMMAND:		
      strcpy(TypeStr, "WRAPPER_COMMAND"); 
      break;
		case WRAPPER_EMPTY:  		
      strcpy(TypeStr, "WRAPPER_EMPTY"); 
      break;
    default:
      break;
	}
	printf("xTEDSWrapper interface %s id %d type %s\n",InterfaceName, InterfaceID, TypeStr);
}
#endif
