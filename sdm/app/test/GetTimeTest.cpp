#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "../../common/Time/SDMTime.h"

const char* g_strLogFileName = "GetTimeTest.log";

int OpenLogFile();
int CloseLogFile();

int main (int argc, char** argv)
{
  int iFileFd = 0;

  unsigned int uiSeconds = 0, uiUSeconds = 0;
  char strLogMessage[512];
  while (1)
    {
      iFileFd = OpenLogFile();

      SDM_GetTime(&uiSeconds, &uiUSeconds);

      snprintf(strLogMessage, sizeof(strLogMessage),
	       "SDM_GetTime returned %u seconds %u useconds.\n", 
	       uiSeconds, uiUSeconds);

      if (write (iFileFd, strLogMessage, strlen(strLogMessage)) < 0)
	{
	  perror("write:");
	  printf("%d\n", iFileFd);
	  return -1;
	}

      close(iFileFd);
      sleep(1);
    }
  return 0;
}

int OpenLogFile()
{
  int iResult = 0;
  if ((iResult = open (g_strLogFileName, O_RDWR | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR)) < 0)
    {
      perror("open:");
      exit(EXIT_FAILURE);
    }
  return iResult;
}


