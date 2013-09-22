#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "SDMMessageLogger.h"

/*
 *  Default constructor, set the log file to a default name and to log all messages.
 *
 */
SDMMessageLogger::SDMMessageLogger():Logger()
{
#ifdef WIN32
	//
	// WINDOWS
	//
	//Get the process pid
	int pid = GetCurrentProcessId();
	//Create a unique filename
	char Filename[64];
	sprintf(Filename, "SDMMessages%d.log",pid);
	Logger.SetLogFile("--------Log of SDM Messages Sent and Received--------\n" \
			  "-----------------------------------------------------", Filename);
	Logger.LogAllMessageTypes();
#else
	//
	//  LINUX
	//
	//Get the process pid
	int pid = getpid();
	//Create a unique filename
	char Filename[64];
	sprintf(Filename, "SDMMessages%d.log",pid);
	Logger.SetLogFile("--------Log of SDM Messages Sent and Received--------\n" \
			  "-----------------------------------------------------", Filename);
	Logger.LogAllMessageTypes();
#endif
}
