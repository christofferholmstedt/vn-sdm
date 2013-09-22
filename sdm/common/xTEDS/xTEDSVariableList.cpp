#include "xTEDSVariableList.h"
#include "xTEDSVariable.h"
#include "MessageDef.h"

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
struct xTEDSItemListNode* copyList(struct xTEDSItemListNode* list,struct xTEDSItemListNode** tail)
{
	struct xTEDSItemListNode* p;
	struct xTEDSItemListNode* head;
	if(list == NULL)
		return NULL;
	head = (struct xTEDSItemListNode*)malloc(sizeof(struct xTEDSItemListNode));
	p = head;
	for(struct xTEDSItemListNode* cur=list;cur!=NULL;cur=cur->next)
	{
		p->data = cur->data;
		if(cur->next!=NULL)
		{
			p->next = (struct xTEDSItemListNode*)malloc(sizeof(struct xTEDSItemListNode));
		}
		else
		{
			p->next = NULL;
			*tail = p;
		}
		p = p->next;
	}
	return head;
}*/

xTEDSVariableList::xTEDSVariableList():head(NULL),tail(NULL)
{}
/*
xTEDSVariableList::xTEDSVariableList(const xTEDSVariableList& b):head(NULL),tail(NULL)
{
	head = copyList(b.head,&tail);
}
*/

/*
 *  Delete only the xTEDSVariableListNode objects, the xTEDSVariables are handled outside
 *  this class.
 */
xTEDSVariableList::~xTEDSVariableList()
{
	if (!IsEmpty())
	{
		for (xTEDSVariableListNode* Cur = head; Cur != NULL; )
		{
			xTEDSVariableListNode* Temp = Cur->next;
			delete Cur;
			Cur = Temp;
		}
		head = tail = NULL;
	}
}

/*
 *  Delete everything in the list.  Both the xTEDSVariableListNode objects, and the xTEDSVariables
 *  they hold a reference to.
 */
void xTEDSVariableList::DeleteItems()
{
	for (xTEDSVariableListNode* Cur = head; Cur != NULL; )
	{
		xTEDSVariableListNode* Temp = Cur->next;
		delete Cur->data;
		delete Cur;
		Cur = Temp;
	}
	head = tail = NULL;
}

void xTEDSVariableList::addItem(const xTEDSVariable* data)
{
	xTEDSVariableListNode* p = new xTEDSVariableListNode(data);
	
	if(tail == NULL)
	{
		head = p;
		tail = p;
	}
	else
	{
		tail->next = p;
		tail = p;
	}
}
/*
xTEDSVariableList& xTEDSVariableList::operator=(const xTEDSItemList& b)
{
	deleteList(head);
	head = copyList(b.head,&tail);
	return *this;
}*/

void xTEDSVariableList::VarReqReg(char* InfoBufferOut, int BufferSize) const
{
	char Buf[MSG_DEF_SIZE];
	int BufLength = 0;
	int StartByte = 0;
	
	Buf[0] = '\0';
	for(xTEDSVariableListNode* cur=head;cur!=NULL;cur=cur->next)
	{
		BufLength = strlen(Buf);
		strncat(Buf, " ", sizeof(Buf) - BufLength);
		
		BufLength += 1;
		cur->data->VarRegInfo(Buf + BufLength, sizeof(Buf) - BufLength, StartByte);
	}
	char TempBuf[128];
	sprintf(TempBuf," length=\"%d\"",StartByte);
	strncat(Buf, TempBuf, sizeof(Buf) - strlen(Buf));
	
	strncat(InfoBufferOut, Buf, BufferSize - 1);
}

void xTEDSVariableList::VarRef(char* InfoBufferOut, int BufferSize) const
{
	char Buf[MSG_DEF_SIZE];
	int BufLength = 0;
	
	Buf[0] = '\0';
	for(struct xTEDSVariableListNode* cur=head; cur != NULL; cur=cur->next)
	{
		BufLength = strlen(Buf);
		if (cur!=head)
		{
			strncat(Buf, "\n\t\t", sizeof(Buf) - BufLength);
			BufLength += 3;
		}
		cur->data->VarRef(Buf + BufLength, sizeof(Buf) - BufLength);
	}
	strncat(InfoBufferOut, Buf, BufferSize - 1);
}

MessageDef* xTEDSVariableList::RegInfo() const
{
	/*char buf[MSG_DEF_SIZE];
	MessageDef* m_def_a = NULL;
	MessageDef* m_def_b;

	memset(buf,0,MSG_DEF_SIZE);
	if(head == NULL)
		return NULL;
	for(struct xTEDSItemListNode* cur=head;cur!=NULL;cur=cur->next)
	{
		if(cur==head)
		{
			m_def_a = cur->data->RegInfo(NULL,NULL); //owner of list already matches
		}
		else
		{
			m_def_b = cur->data->RegInfo(NULL,NULL); //owner of list already matches
			if(m_def_a != NULL)
			{
				m_def_a->Join(m_def_b);
			}
			else
			{
				m_def_a = m_def_b;
			}

		}
	}
	return m_def_a;*/
	return NULL;
}

bool xTEDSVariableList::IsEmpty() const
{
	if(head == NULL)
		return true;
	return false;
}

const xTEDSVariable* xTEDSVariableList::Find(const char* name, const char* interface) const
{
	if (name == NULL) return NULL;
	
	xTEDSVariableListNode* Cur = NULL;
	for (Cur = head; Cur != NULL; Cur = Cur->next)
	{
		if (Cur->data != NULL)
		{
			if (strcmp(Cur->data->getName(), name)==0)
			{
				if (interface == NULL || strcmp(Cur->data->getInterfaceName(), interface)==0)
					return Cur->data;
			}
		}
	}
	return NULL;
}

bool xTEDSVariableList::RegInfoMatch(const char* pname, const xTEDSQualifierList& qualifiers, const char* interface) const
{
	for (xTEDSVariableListNode* Cur = head; Cur != NULL; Cur = Cur->next)
	{
		if (Cur->data != NULL)
		{
			if(Cur->data->RegInfoMatch(pname, qualifiers, interface))
				return true;
		}
	}
	return false;
}

bool xTEDSVariableList::RegexMatch(const char* Pattern, const xTEDSQualifierList& QualList, const char* Interface) const
{
	for (xTEDSVariableListNode* Cur = head; Cur != NULL; Cur = Cur->next)
	{
		if (Cur->data != NULL)
		{
			if(Cur->data->RegexMatch(Pattern, QualList, Interface))
				return true;
		}
	}
	return false;
}

VariableDef* xTEDSVariableList::VarInfoRequest(const char* VarName, const SDMMessage_ID& Interface,
					       VarInfoMatchType matchType) const
{
	VariableDef* VarDef = NULL;
	for (xTEDSVariableListNode* Cur = head; Cur != NULL; Cur = Cur->next)
	{
		if (Cur->data != NULL)
		{
			// If the variable names match
		  if (((matchType == MATCH_VAR_NAME && strcmp(Cur->data->getName(), VarName)==0)) ||
		      matchType == MATCH_ALL)
			{
				// If the interface was not specified(0) or the interface ids match
				if (Interface.getInterface() == 0 || Interface.getInterface() == Cur->data->getInterfaceID())
				{
					if (VarDef == NULL)
						VarDef = Cur->data->VarInfo();
					else
						VarDef->Join(Cur->data->VarInfo());
				}
			}
		}
	}
	return VarDef;
}

#ifndef REMOVE_DEBUG_OUTPUT
void xTEDSVariableList::PrintDebug() const
{
	for (xTEDSVariableListNode* Cur = head; Cur != NULL; Cur = Cur->next)
	{
		if (Cur->data != NULL)
			Cur->data->PrintDebug();
	}
}
#endif


