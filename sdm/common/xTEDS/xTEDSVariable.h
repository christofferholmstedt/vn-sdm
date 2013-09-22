#ifndef __SDM_XTEDS_VARIABLE_H_
#define __SDM_XTEDS_VARIABLE_H_

#include "xTEDSItem.h"
#include "SDMDataTypes.h"
#include "xTEDSDrange.h"
#include "xTEDSCurve.h"
#include "xTEDSLocation.h"
#include "xTEDSOrientationList.h"
#include "VariableDef.h"
#include "xTEDSQualifier.h"
extern "C"
{
#include "xTEDSParser.h"
}

#define ATTR_INIT_VALUE	0xFFFFFFFF

class xTEDSVariable:public xTEDSItem
{
public:
  /** default ctor
   *
   * Default ctor sets 0/Null values for all except data Format is SDM_UNIT16 and Length of 1.
   */
  xTEDSVariable();

  /** dtor
   */
  virtual ~xTEDSVariable();

  /** @brief */
  virtual MessageDef* RegInfo() const;
  virtual bool RegInfoMatch(const char* name, const xTEDSQualifierList&, const char* interface) const;

  void VarRegInfo(char* InfoBufferOut, int BufferSize, int& Offset) const;
  void VarRef(char* InfoBufferOut, int BufferSize) const;
  /**
   */
  void SetVariable(const variable* NewVar);
  VariableDef* VarInfo() const;
	
  virtual void PrintDebug() const;

  //--------------------------------------------------------------------------
  // Getter/Setter Methods added for testability
  //--------------------------------------------------------------------------
  
  void setDataFormat(SDMDataTypes& newDataFormat);
  const SDMDataTypes& getDataFormat() const;

  void setLength(int newLength);
  int getLength() const;

  void setKind(const char* newKind);
  const char* getKind() const;

  void setQualifier(const char* newQualifier);
  const char* getQualifier() const;

  void setID(int newID);
  int getID() const;

  void setRangeMin(const char* newRangeMin);
  const char* getRangeMin() const;

  void setRangeMax(const char* newRangeMax);
  const char* getRangeMax() const;

  void setDefaultValue(const char* newDefaultValue);
  const char* getDefaultValue() const;

  void setPrecision(unsigned int newPrecesion);
  unsigned int getPrecision() const;

  void setUnits(const char* newUnits);
  const char* getUnits() const;

  void setAccuracy(const char* newAccuracy);
  const char* getAccuracy() const;

  void setScaleFactor(const char* newScaleFactor);
  const char* getScaleFactor() const;

  void setScaleUnits(const char* newScaleUnits);
  const char* getScaleUnits() const;

  void setRLow(const char* newRLow);
  const char* getRLow() const;

  void setRHigh(const char* newRHigh);
  const char* getRHigh() const;

  void setYLow(const char* newYLow);
  const char* getYLow() const;

  void setYHigh(const char* newYHigh);
  const char* getYHigh() const;

  void setInvalidValue(const char* NewVal);
  const char* getInvalidValue() const;

private:
  /**
   * Copy ctor - not defined to prevent default object copy semantics
   */
  xTEDSVariable(const xTEDSVariable&);

  /**
   * Assignment operator - not defined to prevent default object copy semantics
   */
  xTEDSVariable& operator=(const xTEDSVariable&);

  virtual bool MatchesQualifier(const xTEDSQualifierList&) const;
  bool MatchesQualifier(xTEDSQualifierList*);
  char* VarInfoRequest() const;
  void getFormat(char* strFormatOut, int BufSize) const;
	
  void setLocation(const location *loc);
  void setOrientation(const orientation *orient);
  void setDRange(const drange* range);
  void setCurve(const curve* curves);
	
  /** 
   * Helper for setting string members...
   */
  void setStringMember( char* & memberStrVar, const char* newValue);

  //--------------------------------------------------------------------------
  // Data members
  //--------------------------------------------------------------------------

  SDMDataTypes m_dataFormat;
  int m_iLength;
  char* m_strKind;
  char* m_strQualifier;	 	// NOTE: Variable qualifier has been deprecated, to be removed in next xTEDS schema release
  int m_iID;			// NOTE: Variable ID has been deprecated, to be removed in next xTEDS schema release
  char* m_strRangeMin;
  char* m_strRangeMax;
  char* m_strDefaultValue;
  unsigned int m_iPrecision;
  char* m_strUnits;
  char* m_strAccuracy;
  char* m_strScaleFactor;
  char* m_strScaleUnits;
  xTEDSLocation *m_varLocation;
  xTEDSOrientationList *m_varOrientation;
  xTEDSDrange *m_varDrange;
  xTEDSCurve *m_varCurve;
  char* m_strRLow;
  char* m_strRHigh;
  char* m_strYLow;
  char* m_strYHigh;
  char* m_strInvalidValue;

};

#endif
