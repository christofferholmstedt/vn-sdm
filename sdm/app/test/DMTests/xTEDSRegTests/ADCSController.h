#ifndef _ADCSCONTROLLER_XTEDS_H
#define _ADCSCONTROLLER_XTEDS_H

#define _STRING_ADCSCONTROLLER_XTEDS \
"<?xml version=\"1.0\" encoding=\"utf-8\" ?>" \
"<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
"xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"ADCS_Control_App_xTeds\" version=\"2.1\">" \
"<Application name=\"ADCSController\" version=\"1.0\" kind=\"SHAP\" description=\"Implements the top-level interface to the ADCS\" />" \
"<Interface name=\"ADCSInterface\" id=\"1\">" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable name=\"Rate\" kind=\"attitudeRate\" units=\"rad_s\" format=\"FLOAT64\" length=\"3\" description=\" Desired Angular rates about each primary axis of the vehicle\" >" \
"<Qualifier name=\"representation\" value=\"vector\" />" \
"<Qualifier name=\"frameMeasured\" value=\"SVF\" />" \
"<Qualifier name=\"frameResolved\" value=\"SVF\" />" \
"</Variable>" \
"<Variable name=\"TargetObject\" kind=\"target\" format=\"UINT08\" description=\"Target at which the system should point\" >" \
"<Drange name=\"TargetsEnum\">" \
"<Option name=\"Nadir\" value=\"0\"/>" \
"<Option name=\"Zenith\" value=\"1\"/>" \
"<Option name=\"Sun\" value=\"2\"/>" \
"<Option name=\"Other\" value=\"3\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"TargetPosition\" kind=\"position\" length=\"3\" units=\"km\" format=\"FLOAT64\" description=\"ECI position vector of a target at which we wish to point\">" \
"<Qualifier name=\"representation\" value=\"vector\"/>" \
"<Qualifier name=\"frameMeasured\" value=\"ECIMOD\"/>" \
"<Qualifier name=\"frameResolved\" value=\"ECIMOD\"/>" \
"</Variable>" \
"<Variable name=\"TargetVelocity\" kind=\"velocity\" length=\"3\" units=\"m_s\" format=\"FLOAT64\" description=\"ECI velocity vector of a target at which we wish to point\">" \
"<Qualifier name=\"representation\" value=\"vector\"/>" \
"<Qualifier name=\"frameMeasured\" value=\"ECIMOD\"/>" \
"<Qualifier name=\"frameResolved\" value=\"ECIMOD\"/>" \
"</Variable>" \
"<Variable name=\"TargetAcceleration\" kind=\"acceleration\" length=\"3\" units=\"m_s_s\" format=\"FLOAT64\" description=\"ECI acceleration vector of a target at which we wish to point\">" \
"<Qualifier name=\"representation\" value=\"vector\"/>" \
"<Qualifier name=\"frameMeasured\" value=\"ECIMOD\"/>" \
"<Qualifier name=\"frameResolved\" value=\"ECIMOD\"/>" \
"</Variable>" \
"<Variable name=\"BoresightObject\" kind=\"boresight\" format=\"UINT08\" description=\"Boresight we wish to point\" >" \
"<Drange name=\"BoresightsEnum\">" \
"<Option name=\"SolarPanel\" value=\"0\"/>" \
"<Option name=\"PrimaryPayload\" value=\"1\"/>" \
"<Option name=\"Other\" value=\"2\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"BoresightLOS\" kind=\"LOS\" length=\"3\" format=\"FLOAT64\" description=\"LOS of the Boresight we wish to point\">" \
"<Qualifier name=\"representation\" value=\"vector\"/>" \
"<Qualifier name=\"frameMeasured\" value=\"SVF\"/>" \
"<Qualifier name=\"frameResolved\" value=\"SVF\"/>" \
"</Variable>" \
"<Variable name=\"Offset\" kind=\"rollPitchYaw\" length=\"3\" units=\"rad\" format=\"FLOAT32\" description=\"pushbroom offsets from LVLH [rad]\"/>" \
"<!--Commands for the ADCS System-->" \
"<Command>" \
"<CommandMsg id=\"1\" name=\"SetADCSModeStandby\" description=\"Set the ADCS to standby mode\" />" \
"</Command>" \
"<Command>" \
"<CommandMsg id=\"2\" name=\"SetADCSModeRate\" description=\"Set the ADCS to rate-only mode\">" \
"<VariableRef name=\"Rate\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Command>" \
"<CommandMsg id=\"3\" name=\"SetADCSModeTracking\" description=\"Set the ADCS to tracking mode\">" \
"<VariableRef name=\"BoresightObject\"/>" \
"<VariableRef name=\"TargetObject\"/>" \
"<VariableRef name=\"Offset\"/>" \
"<!-- Boresight LOS only used if BoresightObject is \"other\", send 0's otherwise-->" \
"<VariableRef name=\"BoresightLOS\"/>" \
"<!--Target Specifications only used if TargetObject is \"other\", send 0's otherwise-->" \
"<VariableRef name=\"TargetPosition\"/>" \
"<VariableRef name=\"TargetVelocity\"/>" \
"<VariableRef name=\"TargetAcceleration\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Command>" \
"<CommandMsg id=\"4\" name=\"SetADCSModeMomentumDump\" description=\"Set the ADCS to momentum dumping mode\" />" \
"</Command>" \
"</Interface>" \
"</xTEDS>" \
""

#endif
