#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

static char* ReadFile(const char* strFileName)
{
  FILE *pFile;
  int iSize = 8192;
  int iRead = 0;
  char *strFile;

  pFile = fopen(strFileName, "r");
  if(pFile == NULL)
    {
      return NULL;
    }

  strFile = (char*)malloc(iSize);
  
  do
    {
      if(iRead == iSize-1)
	{
	  iSize *= 2;
	  strFile = (char*)realloc(strFile, iSize);
	}

      iRead += fread( &strFile[iRead], 1, iSize-iRead-1, pFile );
    } while(!feof(pFile) && !ferror(pFile));

  strFile[iRead] = '\0';

  if(ferror(pFile))
    {
      free(strFile);
      fclose(pFile);
      return NULL;
    }

  fclose(pFile);
  return strFile;
}

static char* Strip(char* strIn)
{
  int iStart;
  int iEnd;
  char *strOut;

  for(iStart=0; iStart < strlen(strIn) && !isgraph(strIn[iStart]); iStart++);
  for(iEnd=strlen(strIn); iEnd > iStart && !isgraph(strIn[iEnd]); iEnd--);

  strOut = malloc(iEnd-iStart+2);
  memcpy(strOut, &strIn[iStart], iEnd-iStart+1);
  strOut[iEnd-iStart+1] = 0;

  free(strIn);

  return strOut;
}

static char* Replace(char* strIn, char* strFrom, char* strTo)
{
  int iCnt;
  int iWritten;

  char* pCur;
  char* pMatch;
  char* strOut;

  for(iCnt = 0, pMatch=strIn; 
      NULL != (pMatch=strstr(pMatch, strFrom)); 
      iCnt++, pMatch+=strlen(strFrom));

  strOut = malloc(1 + strlen(strIn) + (iCnt * ( strlen(strTo) - strlen(strFrom) )));

  pCur = strIn;
  pMatch = strIn;
  iWritten = 0;

  while(NULL != (pMatch = strstr(pMatch, strFrom)))
    {
      memcpy(&strOut[iWritten], pCur, pMatch-pCur);
      iWritten += pMatch-pCur;
      pCur     += pMatch-pCur;

      memcpy(&strOut[iWritten], strTo, strlen(strTo));
      iWritten += strlen(strTo);

      pMatch += strlen(strFrom);
      pCur   += strlen(strFrom);
    }

  memcpy(&strOut[iWritten], pCur, &strIn[strlen(strIn)] - pCur + 1);

  free(strIn);
  return strOut;
}

static char** Split(char* strIn)
{
  char** aStrOut;
  char* pCur;
  char* pMatch;
  int iCnt;

  for(pMatch=strIn, iCnt=0; NULL != (pMatch=strchr(pMatch, '\n')); pMatch++, iCnt++);
  iCnt++; /* We counted new lines, so add 1 for actual lines */

  aStrOut = malloc( (1+iCnt) * sizeof(char*) );
  aStrOut[iCnt] = NULL;

  pCur = strIn;
  pMatch = strIn;
  iCnt = 0;

  while( NULL != (pMatch=strchr(pMatch, '\n')) )
    {
      aStrOut[iCnt] = malloc(1 + pMatch - pCur);
      memcpy(aStrOut[iCnt], pCur, pMatch-pCur);
      aStrOut[iCnt][pMatch-pCur] = '\0';
      pMatch++;
      pCur += pMatch-pCur;
      iCnt++;
    }

  aStrOut[iCnt] = malloc(1 + &strIn[strlen(strIn)]-pCur);
  memcpy(aStrOut[iCnt], pCur, 1 + &strIn[strlen(strIn)]-pCur);

  return aStrOut;
}

static char* ToUpper(char* strIn)
{
  char* strOut;
  int iCur;

  strOut = malloc(strlen(strIn)+1);
  for(iCur=0; strIn[iCur] != '\0'; iCur++)
    {
      strOut[iCur] = toupper(strIn[iCur]);
    }
  strOut[iCur] = '\0';

  free(strIn);

  return strOut;
}

static char* GetElement(const char* strElement, const char* strXml)
{
  char* pMatch  = NULL;
  char* pEnd    = NULL;
  char* pStart  = NULL;
  char* strOut  = NULL;

  pMatch = strstr(strXml, strElement);
  while(pMatch != NULL)
    {
      pStart = pMatch-1;
      while(pStart > strXml)
	{
	  if( *pStart == '<' ) break;
	  else if( isgraph(*pStart) ) break;
	  pStart--;
	}
      
      if( *pStart == '<' ) break;
      else pMatch = strstr(pMatch+1, strElement);
    }

  if(pMatch == NULL) return NULL;

  pEnd = strchr(pMatch, '>');

  if(NULL == pEnd) return NULL;

  pEnd++;

  strOut = malloc( pEnd-pStart + 1 );

  memcpy(strOut, pStart, pEnd-pStart);
  strOut[pEnd-pStart] = '\0';

  return strOut;
}

static char* GetAttribute(const char* strAttribute, const char* strElement)
{
  char* pMatch;
  char* pEnd;
  char* strOut;

  pMatch = strstr(strElement, strAttribute);

  if(NULL == pMatch) return NULL;

  pMatch = strchr(pMatch, '=');

  if(NULL == pMatch) return NULL;

  pMatch = strchr(pMatch, '\"');

  if(NULL == pMatch) return NULL;
  pMatch++;

  pEnd = strchr(pMatch, '\"');

  if(NULL == pEnd) return NULL;

  strOut = malloc(pEnd - pMatch + 1);
  memcpy(strOut, pMatch, pEnd-pMatch);
  strOut[pEnd-pMatch] = '\0';

  return strOut; 
}

static char* GetName(const char* strXteds)
{
  char* strElement;
  char* strAttribute;

  strElement = GetElement("Device", strXteds);
  if( NULL == strElement )
    {
      strElement = GetElement("Application", strXteds);
    }

  if(NULL == strElement) return NULL;

  strAttribute = GetAttribute("name", strElement);
  
  free(strElement);
  return strAttribute;
}

static int Convert(char* strInFile)
{
  char* strXteds;
  char** aSplitXteds;
  char* strName;

  int iCurLine;

  strXteds = ReadFile(strInFile);
  if(NULL == strXteds)
    {
      fprintf(stderr, "Failed to read %s\n", strInFile);
      return 1;
    }

  strName = GetName(strXteds);
  if(NULL == strName)
    {
      fprintf(stderr, "Could not find Application or Device name in file %s\n", strInFile);
      free(strXteds);
      return 1;
    }

  strName = Strip(strName);
  strName = Replace(strName, " ", "_");
  strName = ToUpper(strName);

  strXteds = Strip(strXteds);
  strXteds = Replace(strXteds, "\r\n", "\n");
  strXteds = Replace(strXteds, "\r", "\n");
  strXteds = Replace(strXteds, "\"", "\\\"");

  aSplitXteds = Split(strXteds);

  printf("#ifndef _%s_XTEDS_H\n", strName);
  printf("#define _%s_XTEDS_H\n", strName);
  printf("\n");
  printf("#define _STRING_%s_XTEDS \\\n", strName);
  for(iCurLine=0; aSplitXteds[iCurLine] != NULL; iCurLine++)
    {
      aSplitXteds[iCurLine] = Strip(aSplitXteds[iCurLine]);
      printf("\"%s\" \\\n", aSplitXteds[iCurLine]);
      free(aSplitXteds[iCurLine]);
    }
  free(aSplitXteds);

  printf("\"\"\n");

  printf("\n");
  printf("#endif\n");

  free(strName);
  free(strXteds);

  return 0;
}


int main(int argc, char** argv)
{
  if(argc < 2)
    {
      printf("Usage: %s infile\n", argv[0]);
      return 0;
    }

  return Convert(argv[1]);
}
