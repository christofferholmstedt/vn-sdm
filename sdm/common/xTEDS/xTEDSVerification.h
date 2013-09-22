#ifndef _SDM_XTEDS_VERIFICATION_H_
#define _SDM_XTEDS_VERIFICATION_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
extern "C"
{
#include "xTEDSParser.h"
}

class SDMLIB_API xTEDSVerification
{
public:
	static bool VerifyQualifiers(const char* ItemName, const char* Interface, qualifier_type* QualifierList);
	static bool VerifyOrientation(const variable* var);
	static bool VerifyLocation(const variable* var, const location* loc);
	static bool VerifyCurve (const variable* var);
	static bool VerifyDrange (const variable* var);
	static bool VerifyVarRefs(const char* MsgName, var_ref* VarRefs);
	static bool VerifyVariable(variable* var);
	static bool VerifyDataMsg(const data_msg* dat);
	static bool VerifyCommandMsg(const cmd_msg* cmd);
	static bool VerifyFaultMsg(const fault_msg* fault);
	static bool VerifyInterface(const interface* Interface);
};


#endif

