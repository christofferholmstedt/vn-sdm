#include <stdlib.h>
#include <string.h>

#include "xTEDS.h"
extern "C"
{
#include "xTEDSParser.h"
}
#include "xTEDSVariable.h"
#include "xTEDSDataMsg.h"
#include "xTEDSCommandMsg.h"
#include "xTEDSQualifierList.h"
#include "MessageDef.h"
#include "xTEDSRequest.h"
#include "xTEDSNotification.h"
#include "xTEDSCommand.h"
#include "xTEDSVerification.h"

//#define DEBUG_OUTPUT_XTEDS_TREE	1

xTEDS::xTEDS():m_TreeRoot(),m_strDeviceName(NULL),m_strComponentKey(NULL),m_strSPAUHub(NULL),m_strSPAUPort(NULL)
{}

xTEDS::xTEDS(const xTEDS& b):m_TreeRoot(b.m_TreeRoot),m_strDeviceName(NULL),m_strComponentKey(NULL),m_strSPAUHub(NULL),m_strSPAUPort(NULL)
{
	m_strDeviceName = strdup(b.m_strDeviceName);
	m_strComponentKey = strdup(b.m_strComponentKey);
	m_strSPAUHub = strdup(b.m_strSPAUHub);
	m_strSPAUPort = strdup(b.m_strSPAUPort);
}

xTEDS::~xTEDS()
{
	if(m_strDeviceName!=NULL)
		free(m_strDeviceName);
	if(m_strComponentKey!=NULL)
		free(m_strComponentKey);
	if(m_strSPAUHub!=NULL)
		free(m_strSPAUHub);
	if(m_strSPAUPort!=NULL)
		free(m_strSPAUPort);
}

xTEDS& xTEDS::operator=(const xTEDS&b)
{
	m_TreeRoot = b.m_TreeRoot;
	m_strDeviceName = strdup(b.m_strDeviceName);
	m_strComponentKey = strdup(b.m_strComponentKey);
	m_strSPAUHub = strdup(b.m_strSPAUHub);
	m_strSPAUPort = strdup(b.m_strSPAUPort);
	return *this;
}

bool addVariable(xTEDSItemTree* root,variable* var)
{	
	if (!xTEDSVerification::VerifyVariable(var))
		return false;
	// Otherwise, everything is valid
	root->AddVariable(var);
	return true;
}

bool addCommand(xTEDSItemTree* root,const command* cmd)
{
	if (cmd == NULL || root == NULL)
		return false;
	// Add the required command message
	if (!xTEDSVerification::VerifyCommandMsg(cmd->command_message))
	{
		printf("Invalid command message in <Command> in interface %s\n",cmd->interface_name);
		return false;
	}
	
	// Add the optional fault message
	if(cmd->fault_message != NULL)
	{
		if (!xTEDSVerification::VerifyFaultMsg(cmd->fault_message))
		{
			printf("Invalid fault message in <Command> in interface %s\n",cmd->interface_name);
			return false;
		}
	}
	
	return root->AddCommand(cmd);
}

bool addRequest(xTEDSItemTree* root,request* svc)
{
	// Add the required data message
	if (!xTEDSVerification::VerifyDataMsg(svc->data_message))
	{
		printf("Invalid data message in <Request> in interface %s\n",svc->interface_name);
		return false;
	}
	
	if (!xTEDSVerification::VerifyCommandMsg(svc->command_message))
	{
		printf("Invalid command message in <Request> in interface %s\n",svc->interface_name);
		return false;
	}
		
	// Add the optional fault message
	if(svc->fault_message != NULL)
	{
		if (!xTEDSVerification::VerifyFaultMsg(svc->fault_message))
		{
			printf("Invalid fault message in <Request> in interface %s\n",svc->interface_name);
			return false;
		}
	}
	
	return root->AddRequest(svc);
}

bool addNotification(xTEDSItemTree* root,notification* noti)
{
	// Add the required data message
	if (!xTEDSVerification::VerifyDataMsg(noti->data_message))
	{
		printf("Invalid data message in <Notification> in interface %s\n",noti->interface_name);
		return false;
	}
	
	// Add the optional fault message
	if(noti->fault_message != NULL)
	{
		if (!xTEDSVerification::VerifyFaultMsg(noti->fault_message))
		{
			printf("Invalid fault message in <Notification> in interface %s\n",noti->interface_name);
			return false;
		}
		
	}
	return root->AddNotification(noti);
}

bool addInterface(xTEDSItemTree* root, interface* face)
{
	bool result = true;
	if(face->name == NULL)
	{
		printf("Error no name field in the interface tag!\n");
		return false;
	}
	//add variables
	for(variable* cur_var=face->variables;cur_var!=NULL;cur_var=cur_var->next)
	{
		result = addVariable(root,cur_var);
		if(result == false)
			return false;
	}
	//add data messages
	for(command* cur_cmd=face->commands;cur_cmd!=NULL;cur_cmd=cur_cmd->next)
	{
		result = addCommand(root,cur_cmd);
		if(result == false)
			return false;
	}
	//add command messages
	for(notification* cur_not=face->notifications;cur_not!=NULL;cur_not=cur_not->next)
	{
		result = addNotification(root,cur_not);
		if(result == false)
			return false;
	}
	//add requests
	for(request* cur_request=face->requests;cur_request!=NULL;cur_request=cur_request->next)
	{
		result = addRequest(root,cur_request);
		if(result == false)
			return false;
	}
	return true;
}

bool xTEDS::Parse(char* xteds_text)
{
	bool result = true;
	xteds* parsedXtedsTree = parsexTEDS(xteds_text);
	if(parsedXtedsTree == NULL) return false;	//syntax error in xTEDS
	if(parsedXtedsTree->name == NULL)
	{
		printf("Error xTEDS tag is missing the name field that is required!\n");
		delete_xteds(parsedXtedsTree);
		return false;
	}
	//fill in member data
	//TODO add other header fields of importance
	if(parsedXtedsTree->header->name!=NULL)
	{
		if(m_strDeviceName!=NULL) free(m_strDeviceName);	//to prevent a memory leak if Parse is called twice
		m_strDeviceName = strdup(parsedXtedsTree->header->name);
		if(parsedXtedsTree->header->componentKey!=NULL)
			m_strComponentKey = strdup(parsedXtedsTree->header->componentKey);
		if(parsedXtedsTree->header->spa_u_hub!=NULL)
			m_strSPAUHub = strdup(parsedXtedsTree->header->spa_u_hub);
		if(parsedXtedsTree->header->spa_u_port!=NULL)
			m_strSPAUPort = strdup(parsedXtedsTree->header->spa_u_port);
	}
	else
	{
		printf("Error Device or Application tag is missing the name field!\n");
		result = false;
	}
	if(parsedXtedsTree->header->kind == NULL)
	{
		printf("Error Device or Application tag is missing the kind field!\n");
		result = false;
	}
	//add interfaces
	if(result == true)
	{
		for(interface* cur_interface=parsedXtedsTree->interfaces;cur_interface!=NULL;cur_interface=cur_interface->next)
		{
			if (!xTEDSVerification::VerifyInterface(cur_interface))
			{
				result = false;
				break;
			}
			result = addInterface(&m_TreeRoot,cur_interface);
			if(result == false)
				break;
		}
		if(parsedXtedsTree->interfaces == NULL)
		{
			printf("Error: At least one interface is required!\n");
			result = false;
		}
	}
	//delete temporary structure
	delete_xteds(parsedXtedsTree);
#if  (defined (DEBUG_OUTPUT_XTEDS_TREE) && !defined (REMOVE_DEBUG_OUTPUT))
	if (result == true)
	{
		printf("********************  Device %s  ********************\n",m_strDeviceName);
		m_TreeRoot.PrintDebug();
		printf("************************************************************\n");
		fflush(NULL);
	}
#endif
	return result;
}

MessageDef* xTEDS::RegInfo(const char* ItemName, const char* Qualifiers, const char* Device, const char* Interface)
{
	xTEDSQualifierList QualList;
	if(Device==NULL || strcmp(Device,m_strDeviceName)==0)
	{
		QualList.Parse(Qualifiers);
		return m_TreeRoot.ExactRegInfo(ItemName, QualList, Interface);
	}
	else
		return NULL;
}

MessageDef* xTEDS::AllRegInfo(const char* Qualifiers, const char* Device, const char* Interface)
{
	xTEDSQualifierList QualList;
	if(Device==NULL || strcmp(Device,m_strDeviceName)==0)
	{
		QualList.Parse(Qualifiers);
		return m_TreeRoot.AllRegInfo(QualList, Interface);
	}
	else
		return NULL;
}

MessageDef* xTEDS::RegexRegInfo(const char* Pattern, const char* Qualifiers, const char* Device, const char* Interface)
{
	xTEDSQualifierList QualList;
	if(Device==NULL || strcmp(Device,m_strDeviceName)==0)
	{
		QualList.Parse(Qualifiers);
		return m_TreeRoot.RegexRegInfo(Pattern, QualList, Interface);
	}
	else
		return NULL;
}

SDMMessage_ID xTEDS::getServiceDataMsgID(const SDMMessage_ID& CommandID) const
{
	return m_TreeRoot.GetServiceDataID(CommandID);
}

SDMMessage_ID xTEDS::getServiceFaultMsgID(const SDMMessage_ID& CommandID) const
{
	return m_TreeRoot.GetServiceFaultID(CommandID);
}

SDMMessage_ID xTEDS::getCommandFaultMsgID(const SDMMessage_ID& CommandID) const
{
	return m_TreeRoot.GetCommandFaultID(CommandID);
}

SDMMessage_ID xTEDS::getNotificationFaultMsgID(const SDMMessage_ID& DataID) const
{
	return m_TreeRoot.GetNotificationFaultID(DataID);
}

bool xTEDS::isCommandIdValid(const SDMMessage_ID& RequestedId) const
{
	return m_TreeRoot.IsCommandIdValid(RequestedId);
}

bool xTEDS::isServiceIdValid(const SDMMessage_ID& RequestedId) const
{
	return m_TreeRoot.IsServiceIdValid(RequestedId);
}

VariableDef* xTEDS::getVarInfo(const char* strVariableName, const SDMMessage_ID& idInterface) const
{
	return m_TreeRoot.VarInfoRequest(strVariableName, idInterface);
}

