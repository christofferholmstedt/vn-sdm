#include "xTEDSVariable.h"
#include "MessageDef.h"
#include "../Exception/SDMBadIndexException.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifdef WIN32
#  include "unistd.h"
#endif

xTEDSVariable::xTEDSVariable():
  m_dataFormat(SDM_UINT16),
  m_iLength(1),
  m_strKind(NULL),
  m_strQualifier(NULL),
  m_iID(-1),
  m_strRangeMin(NULL),
  m_strRangeMax(NULL),
  m_strDefaultValue(NULL),
  m_iPrecision(ATTR_INIT_VALUE),
  m_strUnits(NULL),
  m_strAccuracy(NULL),
  m_strScaleFactor(NULL),
  m_strScaleUnits(NULL),
  m_varLocation(NULL),
  m_varOrientation(NULL),
  m_varDrange(NULL),
  m_varCurve(NULL),
  m_strRLow(NULL),
  m_strRHigh(NULL),
  m_strYLow(NULL),
  m_strYHigh(NULL),
  m_strInvalidValue(NULL)
{
	m_ItemType = TYPE_VARIABLE;
	//Initial invalidValue is NS for Not Specified
	m_strInvalidValue = strdup("NS");
}

xTEDSVariable::~xTEDSVariable()
{
  if(m_strKind!=NULL) free(m_strKind);
  if(m_strQualifier!=NULL) free(m_strQualifier);
  if(m_strDefaultValue!=NULL) free(m_strDefaultValue);
  if(m_strUnits!=NULL) free(m_strUnits);
  if(m_strScaleUnits!=NULL) free(m_strScaleUnits);
  if(m_strRangeMin != NULL) free(m_strRangeMin);
  if(m_strRangeMax != NULL) free(m_strRangeMax);
  if(m_strAccuracy != NULL) free(m_strAccuracy);
  if(m_strScaleFactor != NULL) free(m_strScaleFactor);
  if(m_strRLow != NULL) free(m_strRLow);
  if(m_strRHigh != NULL) free(m_strRHigh);
  if(m_strYLow != NULL) free(m_strYLow);
  if(m_strYHigh != NULL) free(m_strYHigh);
  if(m_strInvalidValue != NULL) free(m_strInvalidValue);
  if(m_varDrange!=NULL) delete(m_varDrange);
  if(m_varCurve!=NULL) delete(m_varCurve);
  if (m_varLocation != NULL) delete(m_varLocation);
  if (m_varOrientation != NULL) delete(m_varOrientation);
}

void xTEDSVariable::SetVariable(const variable* NewVar)
{
  if (NewVar == NULL) return;
  if (NewVar->name            != NULL) setName(NewVar->name);
  if (NewVar->kind            != NULL) m_strKind = strdup(NewVar->kind);
  if (NewVar->interface_name  != NULL) setInterfaceName(NewVar->interface_name);
  if (NewVar->interface_id    != NULL) setInterfaceID(atoi(NewVar->interface_id));
  if (NewVar->length          != NULL) m_iLength = atoi(NewVar->length);
  if (NewVar->qualifier       != NULL) m_strQualifier = strdup(NewVar->qualifier);
  if (NewVar->id              != NULL) m_iID = atoi(NewVar->id);
  if (NewVar->range_min       != NULL) m_strRangeMin = strdup(NewVar->range_min);
  if (NewVar->range_max       != NULL) m_strRangeMax = strdup(NewVar->range_max);
  if (NewVar->default_value   != NULL) m_strDefaultValue = strdup(NewVar->default_value);
  if (NewVar->precision       != NULL) m_iPrecision = (unsigned int)atoi(NewVar->precision);
  if (NewVar->units           != NULL) m_strUnits = strdup(NewVar->units);
  if (NewVar->accuracy        != NULL) m_strAccuracy = strdup(NewVar->accuracy);
  if (NewVar->scale_factor    != NULL) m_strScaleFactor = strdup(NewVar->scale_factor);
  if (NewVar->scale_units     != NULL) m_strScaleUnits = strdup(NewVar->scale_units);
  if (NewVar->description     != NULL) setDescription(NewVar->description);
  if (NewVar->r_low           != NULL) m_strRLow = strdup(NewVar->r_low);
  if (NewVar->r_high          != NULL) m_strRHigh = strdup(NewVar->r_high);
  if (NewVar->y_low           != NULL) m_strYLow = strdup(NewVar->y_low);
  if (NewVar->y_high          != NULL) m_strYHigh = strdup(NewVar->y_high);
  if (NewVar->invalid_value   != NULL) setInvalidValue(NewVar->invalid_value);
	
  if (NewVar->format != NULL)
  {
    if(     strcmp(NewVar->format,"INT08"  )==0)
      m_dataFormat = SDM_INT08;
    else if(strcmp(NewVar->format,"UINT08" )==0)
      m_dataFormat = SDM_UINT08;
    else if(strcmp(NewVar->format,"INT16"  )==0)
      m_dataFormat = SDM_INT16;
    else if(strcmp(NewVar->format,"UINT16" )==0)
      m_dataFormat = SDM_UINT16;
    else if(strcmp(NewVar->format,"INT32"  )==0)
      m_dataFormat = SDM_INT32;
    else if(strcmp(NewVar->format,"UINT32" )==0)
      m_dataFormat = SDM_UINT32;
    else if(strcmp(NewVar->format,"FLOAT32")==0)
      m_dataFormat = SDM_FLOAT32;
    else if(strcmp(NewVar->format,"FLOAT64")==0)
      m_dataFormat = SDM_FLOAT64;
  }

  if (NewVar->qualifiers != NULL)
  {
    for (qualifier_type* CurQual = NewVar->qualifiers; 
	 CurQual != NULL; 
	 CurQual = CurQual->next)
      addQualifier (xTEDSQualifier(CurQual->name, CurQual->value, CurQual->units));
  }

  if (NewVar->dranges          != NULL) setDRange(NewVar->dranges);
  if (NewVar->curves           != NULL) setCurve(NewVar->curves);
  if (NewVar->orientation_data != NULL) setOrientation(NewVar->orientation_data);
  if (NewVar->location_data    != NULL) setLocation(NewVar->location_data);

}

MessageDef* xTEDSVariable::RegInfo() const
{
  return NULL;
}

void xTEDSVariable::VarRegInfo(char* InfoBufferOut, int BufferSize, int& start_byte) const
{
  char strBuf[MSG_DEF_SIZE];
  char strScale[32];
	
  if(m_strScaleFactor == NULL)
    snprintf(strScale, sizeof(strScale), "1.0");
  else
    snprintf(strScale, sizeof(strScale), "%s", m_strScaleFactor);

  switch(m_dataFormat)
  {
  case SDM_INT08:
    snprintf(strBuf, sizeof(strBuf), "Variable:%d:%d:%s:%s:INT08=\"%s\"", start_byte, m_iLength, strScale, m_strInvalidValue, m_strItemName);
    start_byte+=1*m_iLength;
    break;
  case SDM_UINT08:
    snprintf(strBuf, sizeof(strBuf), "Variable:%d:%d:%s:%s:UINT08=\"%s\"", start_byte, m_iLength, strScale, m_strInvalidValue, m_strItemName);
    start_byte+=1*m_iLength;
    break;
  case SDM_INT16:
    snprintf(strBuf, sizeof(strBuf), "Variable:%d:%d:%s:%s:INT16=\"%s\"", start_byte, m_iLength, strScale, m_strInvalidValue, m_strItemName);
    start_byte+=2*m_iLength;
    break;
  case SDM_UINT16:
    snprintf(strBuf, sizeof(strBuf), "Variable:%d:%d:%s:%s:UINT16=\"%s\"", start_byte, m_iLength, strScale, m_strInvalidValue, m_strItemName);
    start_byte+=2*m_iLength;
    break;
  case SDM_INT32:
    snprintf(strBuf, sizeof(strBuf), "Variable:%d:%d:%s:%s:INT32=\"%s\"", start_byte, m_iLength, strScale, m_strInvalidValue, m_strItemName);
    start_byte+=4*m_iLength;
    break;
  case SDM_UINT32:
    snprintf(strBuf, sizeof(strBuf), "Variable:%d:%d:%s:%s:UINT32=\"%s\"", start_byte, m_iLength, strScale, m_strInvalidValue, m_strItemName);
    start_byte+=4*m_iLength;
    break;
  case SDM_FLOAT32:
    snprintf(strBuf, sizeof(strBuf), "Variable:%d:%d:%s:%s:FLOAT32=\"%s\"", start_byte, m_iLength, strScale, m_strInvalidValue, m_strItemName);
    start_byte+=4*m_iLength;
    break;
  case SDM_FLOAT64:
    snprintf(strBuf, sizeof(strBuf), "Variable:%d:%d:%s:%s:FLOAT64=\"%s\"", start_byte, m_iLength, strScale, m_strInvalidValue, m_strItemName);
    start_byte+=8*m_iLength;
    break;
  }
  strncat(InfoBufferOut, strBuf, BufferSize - 1);
}

void xTEDSVariable::VarRef(char* InfoBufferOut, int BufferSize) const
{
  char Buf[MSG_DEF_SIZE];
	
  Buf[0] = '\0';
  snprintf(Buf, sizeof(Buf), "<VariableRef name=\"%s\"/>", m_strItemName);
	
  strncat(InfoBufferOut, Buf, BufferSize - 1);
}

VariableDef* xTEDSVariable::VarInfo() const
{
  char buf[MSG_DEF_SIZE] = "";
  char* temp = NULL;
  VariableDef* pVariableDef = new VariableDef();
	
  temp = VarInfoRequest();
	
  size_t str_length = strlen(temp);
  if (m_varDrange == NULL && m_varCurve == NULL && m_ItemQualifiers == NULL && m_varLocation == NULL)
  {
    if (str_length + 2 <= sizeof(buf))
    {
      strcpy(buf, temp);
      strcat(buf, "/>");
    }
  }
  else
  {
    size_t TempLength;
    if (str_length + 1 <= sizeof(buf))
    {
      strcpy(buf, temp);
      strcat(buf, ">");
      str_length += 1;
    }
    if (m_varDrange != NULL)
    {
      TempLength = strlen(buf);
      strncat(buf, "\n\t", sizeof(buf) - TempLength);
			
      TempLength += 2;
      m_varDrange->VarInfoRequest(buf + TempLength, sizeof(buf) - TempLength);
    }
    else if (m_varCurve != NULL)
    {
      TempLength = strlen(buf);
      strncat(buf, "\n\t", sizeof(buf) - TempLength);
			
      TempLength += 2;
      m_varCurve->VarInfoRequest(buf + TempLength, sizeof(buf) - TempLength);
    }
    if (m_ItemQualifiers != NULL)
    {
      TempLength = strlen(buf);
      strncat(buf, "\n\t", sizeof(buf) - TempLength);
			
      TempLength += 2;
      m_ItemQualifiers->QualifierInfoRequest(buf + TempLength, sizeof(buf) - TempLength);
    }
    if (m_varLocation != NULL)
    {
      TempLength = strlen(buf);
      strncat(buf, "\n\t", sizeof(buf) - TempLength);
			
      TempLength += 2;
      m_varLocation->VarInfoRequest(buf + TempLength, sizeof(buf) - TempLength);
    }
    if (m_varOrientation != NULL)
    {
      TempLength = strlen(buf);

      m_varOrientation->VarInfoRequest(buf + TempLength, sizeof(buf) - TempLength);
    }
    if (str_length + 12 <= sizeof(buf))
    {
      strcat(buf, "\n</Variable>");
    }
  }
  free (temp);
	
	
  pVariableDef->SetDefinitions(buf);
  pVariableDef->SetVariableName(m_strItemName);
  pVariableDef->SetInterfaceName(m_strItemInterfaceName);

  return pVariableDef;
}

bool xTEDSVariable::MatchesQualifier(const xTEDSQualifierList& QualList) const
{
  if(QualList.isEmpty())
    return true;
	
  char id_str[8], format_str[8], length_str[8], precision_str[8];
  snprintf(length_str, sizeof(length_str), "%d", m_iLength);
  snprintf(id_str, sizeof(id_str), "%d", m_iID);
  snprintf(precision_str, sizeof(precision_str), "%u", m_iPrecision);
	
  switch(m_dataFormat)
  {
  case SDM_INT08: strncpy(format_str, "INT08", sizeof(format_str)); break;
  case SDM_UINT08: strncpy(format_str, "UINT08", sizeof(format_str)); break;
  case SDM_INT16: strncpy(format_str, "INT16", sizeof(format_str)); break;
  case SDM_UINT16: strncpy(format_str, "UINT16", sizeof(format_str)); break;
  case SDM_INT32: strncpy(format_str, "INT32", sizeof(format_str)); break;
  case SDM_UINT32: strncpy(format_str, "UINT32", sizeof(format_str)); break;
  case SDM_FLOAT32: strncpy(format_str, "FLOAT32", sizeof(format_str)); break;
  case SDM_FLOAT64: strncpy(format_str, "FLOAT64", sizeof(format_str)); break;
  }
	
  //check entire qualifier list
  for (int i = 0; i < QualList.Size(); i++)
  {
    try
    {
      const xTEDSQualifier& CurQual = QualList[i];
      if (CurQual.MatchesName("name"))
      {
	if (!CurQual.MatchesDescription(m_strItemName))
	  return false;
      }
      else if (CurQual.MatchesName("description"))
      {
	if (!CurQual.MatchesDescription(m_strItemDescription))
	  return false;
      }
      else if (CurQual.MatchesName("id"))
      {
	if (!CurQual.MatchesDescription(id_str))
	  return false;
      }
      else if (CurQual.MatchesName("length"))
      {
	if (!CurQual.MatchesDescription(length_str))
	  return false;
      }
      else if (CurQual.MatchesName("format"))
      {
	if (!CurQual.MatchesDescription(format_str))
	  return false;
      }
      else if (CurQual.MatchesName("kind"))
      {
	if (!CurQual.MatchesDescription(m_strKind))
	  return false;
      }
      else if (CurQual.MatchesName("rangeMin"))
      {
	if (!CurQual.MatchesDescription(m_strRangeMin))
	  return false;
      }
      else if (CurQual.MatchesName("rangeMax"))
      {
	if (!CurQual.MatchesDescription(m_strRangeMax))
	  return false;
      }
      else if (CurQual.MatchesName("defaultValue"))
      {
	if (!CurQual.MatchesDescription(m_strDefaultValue))
	  return false;
      }
      else if (CurQual.MatchesName("m_iPrecision"))
      {
	if (!CurQual.MatchesDescription(precision_str))
	  return false;
      }
      else if (CurQual.MatchesName("units"))
      {
	if (!CurQual.MatchesDescription(m_strUnits))
	  return false;
      }
      else if (CurQual.MatchesName("accuracy"))
      {
	if (!CurQual.MatchesDescription(m_strAccuracy))
	  return false;
      }
      else if (CurQual.MatchesName("scaleFactor"))
      {
	if (!CurQual.MatchesDescription(m_strScaleFactor))
	  return false;
      }
      else if (CurQual.MatchesName("scaleUnits"))
      {
	if (!CurQual.MatchesDescription(m_strScaleUnits))
	  return false;
      }
      else if (CurQual.MatchesName("rLow"))
      {
	if (!CurQual.MatchesDescription(m_strRLow))
	  return false;
      }
      else if (CurQual.MatchesName("rHigh"))
      {
	if (!CurQual.MatchesDescription(m_strRHigh))
	  return false;
      }
      else if (CurQual.MatchesName("yLow"))
      {
	if (!CurQual.MatchesDescription(m_strYLow))
	  return false;
      }
      else if (CurQual.MatchesName("yHigh"))
      {
	if (!CurQual.MatchesDescription(m_strYHigh))
	  return false;
      }
      else if (CurQual.MatchesName("invalidValue"))
      {
	if (!CurQual.MatchesDescription(m_strInvalidValue))
	  return false;
      }
      else
	return false;
    }
    catch (SDMBadIndexException& ex)
    {
      printf("Error %s\n", ex.Message());
      return false;
    }
  }
  return true;
}

char* xTEDSVariable::VarInfoRequest() const
{
  char Buf[MSG_DEF_SIZE] = "", TempBuf[512] = "";
	
  char strVarFormat[8];
  getFormat(strVarFormat, sizeof(strVarFormat));
  snprintf(Buf, sizeof(Buf), "<Variable name=\"%s\" kind=\"%s\" format=\"%s\"", m_strItemName, m_strKind, strVarFormat);
	
  if(m_strQualifier != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " qualifier=\"%s\"", m_strQualifier);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_iID != -1)
  {
    snprintf(TempBuf, sizeof(TempBuf), " id=\"%d\"", m_iID);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strRangeMin != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " rangeMin=\"%s\"", m_strRangeMin);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strRangeMax != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " rangeMax=\"%s\"", m_strRangeMax);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strDefaultValue != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " defaultValue=\"%s\"", m_strDefaultValue);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_iPrecision != ATTR_INIT_VALUE)
  {
    snprintf(TempBuf, sizeof(TempBuf), " m_iPrecision=\"%u\"", m_iPrecision);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strUnits != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " units=\"%s\"", m_strUnits);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strAccuracy != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " accuracy=\"%s\"", m_strAccuracy);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strScaleFactor != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " scaleFactor=\"%s\"", m_strScaleFactor);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strScaleUnits != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " scaleUnits=\"%s\"", m_strScaleUnits);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_iLength > 1)
  {
    snprintf(TempBuf, sizeof(TempBuf), " length=\"%d\"", m_iLength);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strItemDescription!=NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " description=\"%s\"", m_strItemDescription);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strRLow != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " rLow=\"%s\"", m_strRLow);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strRHigh != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " rHigh=\"%s\"", m_strRHigh);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strYLow != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " yLow=\"%s\"", m_strYLow);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strYHigh != NULL)
  {
    snprintf(TempBuf, sizeof(TempBuf), " yHigh=\"%s\"", m_strYHigh);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  if(m_strInvalidValue!=NULL && strcmp(m_strInvalidValue,"NS")!=0)
  {
    snprintf(TempBuf, sizeof(TempBuf), " invalidValue=\"%s\"", m_strInvalidValue);
    strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
  }
  return strdup(Buf);
}

void xTEDSVariable::getFormat(char* strFormatOut, int BufSize) const
{
  if (BufSize < 8)
    return ;
	
  switch(m_dataFormat)
  {
  case SDM_INT08:
    sprintf(strFormatOut,"INT08");
    break;
  case SDM_UINT08:
    sprintf(strFormatOut,"UINT08");
    break;
  case SDM_INT16:
    sprintf(strFormatOut,"INT16");
    break;
  case SDM_UINT16:
    sprintf(strFormatOut,"UINT16");
    break;
  case SDM_INT32:
    sprintf(strFormatOut,"INT32");
    break;
  case SDM_UINT32:
    sprintf(strFormatOut,"UINT32");
    break;
  case SDM_FLOAT32:
    sprintf(strFormatOut,"FLOAT32");
    break;
  case SDM_FLOAT64:
    sprintf(strFormatOut,"FLOAT64");
    break;
  }
}

void xTEDSVariable::setLocation(const location *loc)
{
  if (loc == NULL) return;
  if (m_varLocation == NULL)
    m_varLocation = new xTEDSLocation();
  m_varLocation->setLocation(loc);
}

void xTEDSVariable::setOrientation(const orientation *orient)
{
  if (orient == NULL) return;
  if (m_varOrientation == NULL)
    m_varOrientation = new xTEDSOrientationList();
  m_varOrientation->SetOrientation(orient);
}

void xTEDSVariable::setDRange(const drange* range)
{
  if (range == NULL) return;
  if (m_varDrange == NULL)
    m_varDrange = new xTEDSDrange();
  m_varDrange->setDRange(range);
}

void xTEDSVariable::setCurve(const curve* curves)
{
  if (curves == NULL) return;
  if (m_varCurve == NULL)
    m_varCurve = new xTEDSCurve();
  m_varCurve->setCurve(curves);
}

bool xTEDSVariable::RegInfoMatch(const char* pname, const xTEDSQualifierList& qualifiers, const char* interface) const
{
  if (pname == NULL || strcmp(m_strItemName, pname)==0)
  {
    if (interface == NULL || strcmp(m_strItemInterfaceName, interface)==0)
    {
      if (MatchesQualifier(qualifiers))
	return true;
    }
  }
  return false;
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSVariable::PrintDebug() const
{
  printf("     ");
  xTEDSItem::PrintDebug();
  char* VariableStr = VarInfoRequest();
  printf("     %s/>\n",VariableStr);
  printf("\n");
  free(VariableStr);
}
#endif

//--------------------------------------------------------------------------
// Getter/Setter Methods added for testability
//--------------------------------------------------------------------------

void xTEDSVariable::setStringMember( char* & memberStrVar, const char* newValue )
{
  if (newValue == NULL)
    return;

  if (memberStrVar)
  {
    free(memberStrVar);
  }

  memberStrVar = strdup(newValue);
}

/**
* setter for data format
*
* @param newDataFormat - new value for data format
*/
void xTEDSVariable::setDataFormat( SDMDataTypes& newDataFormat )
{
  m_dataFormat = newDataFormat;
}

const SDMDataTypes& xTEDSVariable::getDataFormat() const
{
  return m_dataFormat;
}

void xTEDSVariable::setLength( int newLength )
{
  m_iLength = newLength;
}

int xTEDSVariable::getLength() const
{
  return m_iLength;
}

void xTEDSVariable::setKind( const char* newKind )
{
  setStringMember(m_strKind, newKind);
}

const char* xTEDSVariable::getKind() const
{
  return m_strKind;
}

void xTEDSVariable::setQualifier( const char* newQualifier )
{
  setStringMember(m_strQualifier, newQualifier);
}

const char* xTEDSVariable::getQualifier() const
{
  return m_strQualifier;
}

void xTEDSVariable::setID( int newID )
{
  m_iID = newID;
}

int xTEDSVariable::getID() const
{
  return m_iID;
}

void xTEDSVariable::setRangeMin( const char* newRangeMin )
{
  setStringMember(m_strRangeMin, newRangeMin);
}

const char* xTEDSVariable::getRangeMin() const
{
  return m_strRangeMin;
}

void xTEDSVariable::setRangeMax( const char* newRangeMax )
{
  setStringMember(m_strRangeMax, newRangeMax);
}

void xTEDSVariable::setDefaultValue( const char* newDefaultValue )
{
  setStringMember(m_strDefaultValue, newDefaultValue);
}

const char* xTEDSVariable::getDefaultValue() const
{
  return m_strDefaultValue;
}

void xTEDSVariable::setPrecision( unsigned int newPrecesion )
{
  m_iPrecision = newPrecesion;
}

unsigned int xTEDSVariable::getPrecision() const
{
  return m_iPrecision;
}

void xTEDSVariable::setUnits( const char* newUnits )
{
  setStringMember(m_strUnits, newUnits);
}

const char* xTEDSVariable::getUnits() const
{
  return m_strUnits;
}

void xTEDSVariable::setAccuracy( const char* newAccuracy )
{
  setStringMember(m_strAccuracy, newAccuracy);
}

const char* xTEDSVariable::getAccuracy() const
{
  return m_strAccuracy;
}

void xTEDSVariable::setScaleFactor( const char* newScaleFactor )
{
  setStringMember(m_strScaleFactor, newScaleFactor);
}

const char* xTEDSVariable::getScaleFactor() const
{
  return m_strScaleFactor;
}

void xTEDSVariable::setScaleUnits( const char* newScaleUnits )
{
  setStringMember(m_strScaleUnits, newScaleUnits);
}

const char* xTEDSVariable::getScaleUnits() const
{
  return m_strScaleUnits;
}

void xTEDSVariable::setRLow( const char* newRLow )
{
  setStringMember( m_strRLow, newRLow );
}

const char* xTEDSVariable::getRLow() const
{
  return m_strRLow;
}

void xTEDSVariable::setRHigh( const char* newRHigh )
{
  setStringMember( m_strRHigh, newRHigh );
}

const char* xTEDSVariable::getRHigh() const
{
  return m_strRHigh;
}

void xTEDSVariable::setYLow( const char* newYLow )
{
  setStringMember( m_strYLow, newYLow );
}

const char* xTEDSVariable::getYLow() const
{
  return m_strYLow;
}

void xTEDSVariable::setYHigh( const char* newYHigh )
{
  setStringMember( m_strYHigh, newYHigh );
}

const char* xTEDSVariable::getYHigh() const
{
  return m_strYHigh;
}

void xTEDSVariable::setInvalidValue(const char* newInvalidValue)
{
  setStringMember(m_strInvalidValue, newInvalidValue);
}

const char* xTEDSVariable::getInvalidValue() const
{
  return m_strInvalidValue;
}







