#ifndef __SDM_VARIABLE_DEF_H
#define __SDM_VARIABLE_DEF_H
#include "../sdmLib.h"

#include "../message_defs.h"

class SDMLIB_API VariableDef
{
public:
	VariableDef();
	VariableDef(const VariableDef&);
	~VariableDef();

	VariableDef& operator=(const VariableDef&);

	void Join(VariableDef*);
	const char* GetInterfaceName() const { return m_strInterfaceName; }
	const char* GetVariableName() const { return m_strVariableName; }
	const char* GetDefinitions() const { return m_pDef; }
	void SetDefinitions(const char* strNewDefinitions);
	void SetInterfaceName(const char* strNewInterfaceName);
	void SetVariableName(const char* strNewVariableName);
	bool ListContains(const char* strVariableName) const;

	static void ToStringConcatVariableDefs(char* strReturnBuffer,
					       unsigned int uiReturnBufferSize,
					       VariableDef* Defs1,
					       VariableDef* Defs2);
	static void ToStringConcatVariableDefsIgnoreDuplicates(char* strReturnBuffer,
							     unsigned int uiBufferSize,
							     VariableDef* Defs1,
							     VariableDef* Defs2);

	void Print();
private:
	static void ToStringConcatVariableDefs(char* strReturnBuffer, unsigned int uiReturnBufferSize,
			  VariableDef* Defs1, VariableDef* Defs2, bool bIgnoreDulicates);
	char* m_pDef;
	char m_strInterfaceName[33];
	char m_strVariableName[33];
public:
	VariableDef* next;

};


#endif
