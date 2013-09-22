#include "xTEDSVerification.h"

bool xTEDSVerification::VerifyQualifiers(const char* ItemName, const char* Interface, qualifier_type* QualifierList)
{
	if (QualifierList == NULL)
		return false;
	
	for (qualifier_type* CurQual = QualifierList; CurQual != NULL; CurQual = CurQual->next)
	{
		if (CurQual->name == NULL)
		{
			printf("Error: The Qualifier name must be set for %s in Interface %s\n",ItemName,Interface);
			return false;
		}
		if (CurQual->value == NULL)
		{
			printf("Error: The Qualifier %s must have the value field set in %s in Interface %s\n",CurQual->name,ItemName,Interface);
			return false;
		}
	}
	return true;
}

bool xTEDSVerification::VerifyOrientation(const variable* var)
{
	if (var == NULL || var->orientation_data == NULL)
		return false;
	
	if (var->orientation_data->axis_value == NULL || var->orientation_data->angle_value == NULL || var->orientation_data->units_value == NULL)
	{
		printf("Error: Variable %s is missing a required orientation attribute.\n",var->name);
		return false;
	}
	return true;
}

bool xTEDSVerification::VerifyLocation(const variable* var, const location* loc)
{
	if (var == NULL || loc == NULL)
		return false;
	
	if (loc->x_value == NULL || loc->y_value == NULL || loc->z_value == NULL)
	{
		printf("Error: Variable %s is missing a location component.\n",var->name);
		return false;
	}
	if (loc->units == NULL)
	{
		printf("Error: Variable %s is missing the units field in its location element.\n",var->name);
		return false;
	}
	return true;
}

bool xTEDSVerification::VerifyCurve (const variable* var)
{
	if (var == NULL || var->curves == NULL || var->interface_name == NULL || var->name == NULL)
		return false;
	
	if (var->curves->name == NULL)
	{
		printf("Error: The Curve name must be set for Variable %s in Interface %s!\n",var->name, var->interface_name);
		return false;
	}
	if (var->curves->coefs == NULL)
	{
		printf("Error: The Curve %s must have at least 1 Coef in Interface %s!\n",var->curves->name,var->interface_name);
		return false;
	}
	for (coef* CurCoef = var->curves->coefs; CurCoef != NULL; CurCoef = CurCoef->next)
	{
		if (CurCoef->exponent == NULL)
		{
			printf("Error: The Coef must have the exponent field set for Curve %s in Interface %s!\n",var->curves->name,var->interface_name);
				return false;
		}
		if (CurCoef->value == NULL)
		{
			printf("Error: The Coef %s must have the value field set for Curve %s in Interface %s.\n",CurCoef->exponent,var->curves->name,var->interface_name);
				return false;
		}
	}
	return true;
}

bool xTEDSVerification::VerifyDrange (const variable* var)
{
	if (var == NULL || var->dranges == NULL || var->interface_name == NULL || var->name == NULL)
		return false;
	
	// Do some verification checking on the drange and option values
	if (var->dranges->name == NULL)
	{
		printf("Error: The Drange name must be set for Variable %s in Interface %s.\n",var->name,var->interface_name);
		return false;
	}
	// Be sure there is at least one option
	if (var->dranges->options == NULL)
	{
		printf("Error: The Drange %s must have at least 1 Option in Interface %s.\n",var->dranges->name,var->interface_name);
		return false;
	}
	// Check to be sure all options have at least a name and value
	for (curveoption* CurOption = var->dranges->options; CurOption != NULL; CurOption = CurOption->next)
	{
		if (CurOption->name == NULL)
		{
			printf("Error: The option name must be set for Drange %s in Interface %s.\n",var->dranges->name,var->interface_name);
			return false;
		}
		else if (CurOption->value == NULL)
		{
			printf("Error: The option %s must have the value field set for Drange %s in Interface %s.\n",CurOption->name,var->dranges->name,var->interface_name);
			return false;
		}
	}
	return true;
}

bool xTEDSVerification::VerifyVarRefs(const char* MsgName, var_ref* VarRefs)
{
	if (MsgName == NULL || VarRefs == NULL)
		return false;
	
	for (var_ref* Cur = VarRefs; Cur != NULL; Cur = Cur->next)
	{
		if (Cur->name == NULL)
		{
			printf("Variable reference name not specified for message %s.\n",MsgName);
			return false;
		}
	}
	return true;
}

bool xTEDSVerification::VerifyVariable(variable* var)
{
	if (var == NULL)
		return false;
	
	if(var->name == NULL)
	{
		printf("Error: Variable is missing the name field!\n");
		return false;
	}
	if(var->kind == NULL)
	{
		printf("Error: Variable %s is missing the kind field!\n",var->name);
		return false;
	}
	if(var->interface_name == NULL)
	{
		printf("Error: The Variable %s is not within an interface\n",var->name);
		return false;
	}
	if(var->interface_id == NULL)
	{
		printf("Error: The Variable %s is not within an interface\n",var->name);
		return false;
	}
	if(var->format != NULL)
	{
		if( strcmp(var->format,"INT08") !=0 &&
			strcmp(var->format,"UINT08") !=0 &&
			strcmp(var->format,"INT16") !=0 &&
			strcmp(var->format,"UINT16") !=0 &&
			strcmp(var->format,"INT32") !=0 &&
			strcmp(var->format,"UINT32") !=0 &&
			strcmp(var->format,"FLOAT32") !=0 &&
			strcmp(var->format,"FLOAT64") !=0 )
		{
			printf("Error: The format field value %s for Variable %s does not match any defined type in Interface %s!\n",var->format,var->name,var->interface_name);
			return false;
		}
	}
	else
	{
		printf("Error: Variable %s is missing the format field in Interface %s!\n",var->name,var->interface_name);
		return false;
	}
	if (var->qualifiers != NULL)
		if (!VerifyQualifiers(var->name, var->interface_name, var->qualifiers))
			return false;
	
	if(var->dranges!=NULL)
		if (!VerifyDrange (var))
			return false;
	
	if(var->curves!=NULL)
		if (!VerifyCurve (var))
			return false;
	
	if (var->location_data != NULL)
		if (!VerifyLocation (var, var->location_data))
			return false;
	
	if (var->orientation_data != NULL)
		if (!VerifyOrientation (var))
			return false;
	return true;
}

bool xTEDSVerification::VerifyDataMsg(const data_msg* dat)
{
	if (dat == NULL)
		return false;
	
	if(dat->name == NULL)
	{
		printf("Error: The DataMsg or DataReplyMsg is missing the name field!\n");
		return false;
	}
	if(dat->id == NULL)
	{
		printf("Error: The DataMsg or DataReplyMsg %s is missing the id field!\n",dat->name);
		return false;
	}
	if(dat->interface_name == NULL)
	{
		printf("Error: The DataMsg %s is not within an interface\n",dat->name);
		return false;
	}
	if(dat->interface_id == NULL)
	{
		printf("Error: The DataMsg %s is not within an interface\n",dat->name);
		return false;
	}
	if(dat->msg_arrival != NULL)
	{
		if( strcmp(dat->msg_arrival,"EVENT") != 0 && 
			strcmp(dat->msg_arrival,"PERIODIC") != 0 )
		{
			printf("Error:  The msgArrival type %s for DataMsg %s does not match any defined value in Interface %s\n",dat->msg_arrival,dat->name,dat->interface_name);
			return false;
		}
	}
	
	// Add any qualifiers
	if (dat->qualifiers != NULL)
		if (!VerifyQualifiers(dat->name, dat->interface_name, dat->qualifiers))
			return false;
	
	if (dat->variables != NULL)
	{
		if (!VerifyVarRefs(dat->name, dat->variables))
			return false;
	}
	
	return true;
}

bool xTEDSVerification::VerifyCommandMsg(const cmd_msg* cmd)
{
	if (cmd == NULL)
		return false;
	
	if(cmd->name == NULL)
	{
		printf("Error: The CommandMsg is missing the name field!\n");
		return false;
	}
	if(cmd->id == NULL)
	{
		printf("Error:  The CommandMsg %s is missing the id field!\n",cmd->name);
		return false;
	}

	if(cmd->interface_name == NULL)
	{
		printf("Error: The CommandMsg %s is not within an interface\n",cmd->name);
		return false;
	}
	if(cmd->interface_id == NULL)
	{
		printf("Error: The CommandMsg %s is not within an interface\n",cmd->name);
		return false;
	}
	
	// Add any qualifiers
	if (cmd->qualifiers != NULL)
	{
		if (VerifyQualifiers(cmd->name, cmd->interface_name, cmd->qualifiers) == false)
			return false;
	}
	
	if (cmd->variables != NULL)
	{
		if (!VerifyVarRefs(cmd->name, cmd->variables))
			return false;
	}
	return true;
}

bool xTEDSVerification::VerifyFaultMsg(const fault_msg* fault)
{
	if (fault == NULL)
		return false;
	
	if(fault->id == NULL)
	{
		printf("Fault message is missing its id field.\n");
		return false;
	}
	if(fault->name == NULL)
	{
		printf("Fault message is missing the name field.\n");
		return false;
	}
	if(fault->interface_name == NULL)
	{
		printf("Fault message %s is not within an interface.\n",fault->name);
		return false;
	}
	if(fault->interface_id == NULL)
	{
		printf("Could not find the interface id of fault message %s.\n",fault->name);
		return false;
	}
	if(fault->qualifiers != NULL)
	{
		if (!VerifyQualifiers (fault->name, fault->interface_name, fault->qualifiers))
			return false;
	}
	if (fault->variables != NULL)
	{
		if (!VerifyVarRefs(fault->name, fault->variables))
			return false;
	}

	return true;
}

bool xTEDSVerification::VerifyInterface(const interface* Interface)
{
	if (Interface == NULL)
		return false;
	
	if(Interface->name == NULL)
	{
		printf("Error: The Interface has a missing name field that is required!\n");
		return false;
	}
	if(Interface->id == NULL || strcmp(Interface->id,"0") == 0)
	{
		printf("Error: Interface %s has either a interface id of 0 or does not have an interface id!\n",Interface->name);
		return false;
	}
	return true;
}

