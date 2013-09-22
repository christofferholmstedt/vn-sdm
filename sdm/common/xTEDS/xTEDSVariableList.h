#ifndef __SDM_XTEDS_VARIABLE_LIST_H_
#define __SDM_XTEDS_VARIABLE_LIST_H_

//The xTEDSVariableList does not 'own' its items, it is just a way for items to reference other items in the tree
//The xTEDSItemTree however does 'own' its items, and deletes its xTEDSItems in its destructor

#include "xTEDSVariable.h"
#include "xTEDSQualifierList.h"
#include "VariableDef.h"
#include "../message/SDMMessage_ID.h"

class xTEDSVariableListNode
{
public:
	xTEDSVariableListNode(const xTEDSVariable *NewData) : data(NewData), next(NULL) {}
	const xTEDSVariable* data;
	class xTEDSVariableListNode* next;
};

class xTEDSVariableList
{
public:
        enum VarInfoMatchType { MATCH_VAR_NAME, MATCH_ALL };
	xTEDSVariableList();
	xTEDSVariableList(const xTEDSVariableList&);
	~xTEDSVariableList();
	void addItem(const xTEDSVariable*);
	void DeleteItems();
	xTEDSVariableList& operator=(const xTEDSVariableList&);
	void VarReqReg(char* InfoBufferOut, int BufferSize) const;
	void VarRef(char* InfoBufferOut, int BufferSize) const;
	VariableDef* VarInfoRequest(const char* VarName, const SDMMessage_ID& Interface,
				    VarInfoMatchType matchType = MATCH_VAR_NAME) const;
	MessageDef* RegInfo() const;
	bool RegInfoMatch(const char* name, const xTEDSQualifierList&, const char* interface) const;
	bool RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const;
	const xTEDSVariable* Find(const char* name, const char* interface = NULL) const;
	bool IsEmpty() const;
	
	void PrintDebug() const;
private:
	xTEDSVariableListNode* head;
	xTEDSVariableListNode* tail;
};

#endif
