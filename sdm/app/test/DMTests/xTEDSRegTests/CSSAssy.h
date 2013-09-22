#ifndef _COARSE_SUN_SENSOR_ASSEMBLY_XTEDS_H
#define _COARSE_SUN_SENSOR_ASSEMBLY_XTEDS_H

#define _STRING_COARSE_SUN_SENSOR_ASSEMBLY_XTEDS \
"<?xml version=\"1.0\" encoding=\"utf-8\" ?>" \
"<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
"xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"DNet_CoarseSSAssy_xTEDS\"" \
"version=\"2.1\">" \
"<Device name=\"Coarse_sun_sensor_assembly\" kind=\"cssa\" description=\"An assembly of 4 coarse sun sensors\" />" \
"" \
"<Interface id=\"1\" name=\"CSSAssemblyInterface\" description=\"Aggregate-level interface for the assembly\" >" \
"<Qualifier name=\"headID\" value=\"0\"/>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable name=\"SolutionAvailable\" kind=\"boolean\" format=\"UINT08\">" \
"<Drange name=\"SolutionEnum\" >" \
"<Option name=\"Yes\" value=\"1\"/>" \
"<Option name=\"No\" value=\"0\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"dataQuality\" kind=\"DataQuality\" format=\"UINT08\">" \
"<Drange name=\"DataQualityEnum\">" \
"<Option name=\"dataBad\" value=\"0\" description=\"data is garbage or NaN.\" />" \
"<Option name=\"dataPoor\" value=\"1\" description=\"data quality is poor.\" />" \
"<Option name=\"dataGood\" value=\"2\" description=\"data is good.\" />" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"AngleToSun\" kind=\"sunLOS\" format=\"FLOAT32\" length=\"2\" />" \
"<Notification>" \
"<DataMsg id=\"1\" name=\"SunSolution\" msgArrival=\"PERIODIC\" msgRate=\"10\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"SolutionAvailable\"/>" \
"<VariableRef name=\"dataQuality\"/>" \
"<VariableRef name=\"AngleToSun\"/>" \
"</DataMsg>" \
"</Notification>" \
"</Interface>" \
"" \
"<Interface id=\"2\" name=\"CSSAssyHeadInterface\" description=\"Messaging for a single CSS head\" >" \
"<Qualifier name=\"headID\" value=\"1\"/>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable kind=\"ID\" name=\"HeadID\" format=\"UINT08\" />" \
"<Variable kind=\"boresightLOS\" name=\"HeadLOS\" format=\"FLOAT32\" length=\"3\" />" \
"<Variable kind=\"sunCOS\" name=\"SunCos\" format=\"FLOAT32\" />" \
"<Variable name=\"SunPresence\" kind=\"Valid\" format=\"UINT08\">" \
"<Drange name=\"Sun_PresenceEnum\">" \
"<Option name=\"SunPresent\" value=\"1\" description=\"This sensor can see the sun\" />" \
"<Option name=\"SunNotPresent\" value=\"0\" description=\"Sun not visible from this sensor\" />" \
"</Drange>" \
"</Variable>" \
"<Request>" \
"<CommandMsg id=\"1\" name=\"getHeadLOS\" description=\"Returns the orientation of this head in the sensor frame\" />" \
"<DataReplyMsg id=\"2\" name=\"HeadLOSReply\">" \
"<VariableRef name=\"HeadID\"/>" \
"<VariableRef name=\"HeadLOS\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Notification>" \
"<DataMsg id=\"3\" name=\"sunConeAngle\" msgArrival=\"PERIODIC\" msgRate=\"10\"  description=\"Observation of the sun from this sensor head\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"SunPresence\"/>" \
"<VariableRef name=\"SunCos\"/>" \
"</DataMsg>" \
"</Notification>" \
"</Interface>" \
"" \
"<Interface id=\"3\" name=\"CSSAssyHeadInterface\" description=\"Messaging for a single CSS head\" >" \
"<Qualifier name=\"headID\" value=\"2\"/>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable kind=\"ID\" name=\"HeadID\" format=\"UINT08\" />" \
"<Variable kind=\"boresightLOS\" name=\"HeadLOS\" format=\"FLOAT32\" length=\"3\" />" \
"<Variable kind=\"sunCOS\" name=\"SunCos\" format=\"FLOAT32\" />" \
"<Variable name=\"SunPresence\" kind=\"Valid\" format=\"UINT08\">" \
"<Drange name=\"Sun_PresenceEnum\">" \
"<Option name=\"SunPresent\" value=\"1\" description=\"This sensor can see the sun\" />" \
"<Option name=\"SunNotPresent\" value=\"0\" description=\"Sun not visible from this sensor\" />" \
"</Drange>" \
"</Variable>" \
"<Request>" \
"<CommandMsg id=\"1\" name=\"getHeadLOS\" description=\"Returns the orientation of this head in the sensor frame\" />" \
"<DataReplyMsg id=\"2\" name=\"HeadLOSReply\">" \
"<VariableRef name=\"HeadID\"/>" \
"<VariableRef name=\"HeadLOS\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Notification>" \
"<DataMsg id=\"3\" name=\"sunConeAngle\" msgArrival=\"PERIODIC\" msgRate=\"10\"  description=\"Observation of the sun from this sensor head\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"SunPresence\"/>" \
"<VariableRef name=\"SunCos\"/>" \
"</DataMsg>" \
"</Notification>" \
"</Interface>" \
"" \
"<Interface id=\"4\" name=\"CSSAssyHeadInterface\" description=\"Messaging for a single CSS head\" >" \
"<Qualifier name=\"headID\" value=\"3\"/>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable kind=\"ID\" name=\"HeadID\" format=\"UINT08\" />" \
"<Variable kind=\"boresightLOS\" name=\"HeadLOS\" format=\"FLOAT32\" length=\"3\" />" \
"<Variable kind=\"sunCOS\" name=\"SunCos\" format=\"FLOAT32\" />" \
"<Variable name=\"SunPresence\" kind=\"Valid\" format=\"UINT08\">" \
"<Drange name=\"Sun_PresenceEnum\">" \
"<Option name=\"SunPresent\" value=\"1\" description=\"This sensor can see the sun\" />" \
"<Option name=\"SunNotPresent\" value=\"0\" description=\"Sun not visible from this sensor\" />" \
"</Drange>" \
"</Variable>" \
"<Request>" \
"<CommandMsg id=\"1\" name=\"getHeadLOS\" description=\"Returns the orientation of this head in the sensor frame\" />" \
"<DataReplyMsg id=\"2\" name=\"HeadLOSReply\">" \
"<VariableRef name=\"HeadID\"/>" \
"<VariableRef name=\"HeadLOS\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Notification>" \
"<DataMsg id=\"3\" name=\"sunConeAngle\" msgArrival=\"PERIODIC\" msgRate=\"10\"  description=\"Observation of the sun from this sensor head\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"SunPresence\"/>" \
"<VariableRef name=\"SunCos\"/>" \
"</DataMsg>" \
"</Notification>" \
"</Interface>" \
"" \
"<Interface id=\"5\" name=\"CSSAssyHeadInterface\" description=\"Messaging for a single CSS head\" >" \
"<Qualifier name=\"headID\" value=\"4\"/>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable kind=\"ID\" name=\"HeadID\" format=\"UINT08\" />" \
"<Variable kind=\"boresightLOS\" name=\"HeadLOS\" format=\"FLOAT32\" length=\"3\" />" \
"<Variable kind=\"sunCOS\" name=\"SunCos\" format=\"FLOAT32\" />" \
"<Variable name=\"SunPresence\" kind=\"Valid\" format=\"UINT08\">" \
"<Drange name=\"Sun_PresenceEnum\">" \
"<Option name=\"SunPresent\" value=\"1\" description=\"This sensor can see the sun\" />" \
"<Option name=\"SunNotPresent\" value=\"0\" description=\"Sun not visible from this sensor\" />" \
"</Drange>" \
"</Variable>" \
"<Request>" \
"<CommandMsg id=\"1\" name=\"getHeadLOS\" description=\"Returns the orientation of this head in the sensor frame\" />" \
"<DataReplyMsg id=\"2\" name=\"HeadLOSReply\">" \
"<VariableRef name=\"HeadID\"/>" \
"<VariableRef name=\"HeadLOS\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Notification>" \
"<DataMsg id=\"3\" name=\"sunConeAngle\" msgArrival=\"PERIODIC\" msgRate=\"10\"  description=\"Observation of the sun from this sensor head\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"SunPresence\"/>" \
"<VariableRef name=\"SunCos\"/>" \
"</DataMsg>" \
"</Notification>" \
"</Interface>" \
"" \
"<Interface name=\"DevPwr\" id=\"6\">" \
"<Qualifier name=\"CurrentLoKeepout\" value=\"0.0\" units=\"A\"/>" \
"<Qualifier name=\"CurrentLoWarning\" value=\"0.0\" units=\"A\"/>" \
"<Qualifier name=\"CurrentHiWarning\" value=\"0.2\" units=\"A\"/>" \
"<Qualifier name=\"CurrentHiKeepout\" value=\"0.3\" units=\"A\"/>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable name=\"DevPwrState\" kind=\"Power_State\" format=\"UINT08\" >" \
"<Drange name=\"DevPwrStateEnum\">" \
"<Option name=\"DevPwrOFF\" value=\"0\" description=\"All power to device is turned off.\" />" \
"<Option name=\"DevPwrON\" value=\"1\" description=\"Device may draw full power.\" />" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"DevPwrStateSet\" kind=\"Power_State\" format=\"UINT08\" >" \
"<Drange name=\"DevPwrStateEnumReference\" description=\"This should be a reference to DevPwrStateEnumeration.\">" \
"<Option name=\"DevPwrOFF\" value=\"0\" description=\"All power to device is turned off.\" />" \
"<Option name=\"DevPwrON\" value=\"1\" description=\"Device may draw full power.\" />" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"modePowers\" kind=\"power\" format=\"FLOAT32\" units=\"W\" length=\"2\" />" \
"<Command>" \
"<CommandMsg name=\"DevPwrSetState\" id=\"1\">" \
"<VariableRef name=\"DevPwrStateSet\" />" \
"</CommandMsg>" \
"<FaultMsg name=\"DevPwrStateNotSet\" id=\"2\">" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"DevPwrState\" />" \
"<VariableRef name=\"DevPwrStateSet\" />" \
"</FaultMsg>" \
"</Command>" \
"<Notification>" \
"<DataMsg name=\"DevPwrHK\" id=\"3\" msgArrival=\"PERIODIC\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"DevPwrState\" />" \
"<VariableRef name=\"DevPwrStateSet\" />" \
"</DataMsg>" \
"</Notification>" \
"<Request>" \
"<CommandMsg name=\"getPowerInMode\" id=\"4\" />" \
"<DataReplyMsg name=\"powerInMode\" id=\"5\">" \
"<VariableRef name=\"modePowers\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"</Interface>" \
"" \
"<Interface name=\"CmpSafety\" id=\"7\">" \
"<Qualifier name=\"TemperatureLoKeepout\" value=\"-20.0\" units=\"degC\"/>" \
"<Qualifier name=\"TemperatureLoWarning\" value=\"-10.0\" units=\"degC\"/>" \
"<Qualifier name=\"TemperatureHiWarning\" value=\"50.0\" units=\"degC\"/>" \
"<Qualifier name=\"TemperatureHiKeepout\" value=\"60.0\" units=\"degC\"/>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable name=\"DeviceTemperature\" kind=\"temperature\" format=\"FLOAT32\" units=\"degC\" />" \
"<Request>" \
"<CommandMsg name=\"GetDeviceTemperature\" id=\"1\" />" \
"<DataReplyMsg name=\"DeviceTempReply\" id=\"2\">" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"DeviceTemperature\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Notification>" \
"<DataMsg name=\"DeviceTemp\" id=\"3\" msgArrival=\"PERIODIC\" msgRate=\"1\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"DeviceTemperature\"/>" \
"</DataMsg>" \
"</Notification>" \
"</Interface>" \
"" \
"</xTEDS>" \
""

#endif
