#include "VariableDef.h"

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

VariableDef::VariableDef():m_pDef(NULL), m_strInterfaceName(),m_strVariableName(),next(NULL)
{
  m_strInterfaceName[0] = m_strVariableName[0] = '\0';
}

//VariableDef::VariableDef(const VariableDef& b):def(b.def),interface_name(b.interface_name),next(b.next)
//{}

VariableDef::~VariableDef()
{
        if(m_pDef != NULL)
	{
		free(m_pDef);
	}
	if(next != NULL)
	{
		delete next;
	}
}

//VariableDef& VariableDef::operator=(const VariableDef& b)
//{
//	def = b.def;
//	interface_name = b.interface_name;
//	next = b.next;
//	return *this;
//}

void VariableDef::Join(VariableDef* b)
{
	//join the two lists
	VariableDef* cur;
	if(b == NULL)
		return;
	if(next == NULL)
	{
		next = b;
		return;
	}
	for(cur = next;cur->next!=NULL;cur=cur->next);
	cur->next = b;
}

void VariableDef::SetDefinitions(const char* strNewDefinitions)
{
  if (m_pDef != NULL)
    free (m_pDef);

  m_pDef = strdup(strNewDefinitions);
}

void VariableDef::SetInterfaceName(const char* strNewInterfaceName)
{
  strncpy(m_strInterfaceName, strNewInterfaceName, sizeof(m_strInterfaceName));
  m_strInterfaceName[sizeof(m_strInterfaceName) - 1] = '\0';
}

void VariableDef::SetVariableName(const char* strNewVariableName)
{
  strncpy(m_strVariableName, strNewVariableName, sizeof(m_strVariableName));
  m_strVariableName[sizeof(m_strVariableName) - 1] = '\0';
}

void VariableDef::ToStringConcatVariableDefs(char* pReturnBuffer, unsigned int uiBufferSize,
					     VariableDef* pDefs1, VariableDef* pDefs2, bool bIgnoreDuplicates)
{
  unsigned int uiCurSize = 0;
  unsigned int uiCurLength = 0;

  // Either can be Null by itself, but if both null, quit
  if (pDefs1 == NULL && pDefs2 == NULL)
    return;

  for (VariableDef* pCur = pDefs1; pCur != NULL; pCur = pCur->next)
    {
      const char* pCurDefinitions = pCur->GetDefinitions();

      if (pCurDefinitions == NULL)
	  continue;

      uiCurLength = strlen(pCurDefinitions);

      if (uiCurSize + uiCurLength < uiBufferSize)
	{
	  strcat (pReturnBuffer, pCurDefinitions);
	  uiCurSize += uiCurLength;
	}
      else
	  return;
    }

  // Add variables from the second list, if they are already in the first list, continue
  for (VariableDef* pCur = pDefs2; pCur != NULL; pCur = pCur->next)
    {
      if (bIgnoreDuplicates && NULL != pDefs1)
	{
	  if (pDefs1->ListContains(pCur->GetVariableName()))
	    continue;
	}

      const char* pCurDefinitions = pCur->GetDefinitions();

      if (pCurDefinitions == NULL)
	continue;

      uiCurLength = strlen(pCurDefinitions);

      if (uiCurSize + uiCurLength < uiBufferSize)
	{
	  strcat (pReturnBuffer, pCurDefinitions);
	  uiCurSize += uiCurLength;
	}
      else
	return;
    }
}

void VariableDef::ToStringConcatVariableDefs(char* strReturnBuffer, unsigned int uiBufferSize,
					     VariableDef* pDefs1, VariableDef* pDefs2)
{
  ToStringConcatVariableDefs(strReturnBuffer, uiBufferSize, pDefs1, pDefs2, false);
}

void VariableDef::ToStringConcatVariableDefsIgnoreDuplicates(char* pReturnBuffer,
							     unsigned int uiBufferSize,
							     VariableDef* pDefs1,
							     VariableDef* pDefs2)
{
  ToStringConcatVariableDefs(pReturnBuffer, uiBufferSize, pDefs1, pDefs2, true);
}

bool VariableDef::ListContains(const char* strVariableName) const
{
  if (0 == strcmp(this->GetVariableName(), strVariableName))
    return true;

  for (VariableDef* pCur = next; pCur != NULL; pCur = pCur->next)
    {
      if (0 == strcmp(pCur->GetVariableName(), strVariableName))
	{
	  return true;
	}
    }

  return false;
}

void VariableDef::Print()
{
        if (m_pDef == NULL)
                return;

	printf("variable_def: %s interface_name: %s",m_pDef,m_strInterfaceName);
	if(next!=NULL)
		next->Print();
}
