#ifndef _SINGLE_REACTION_WHEEL_XTEDS_H
#define _SINGLE_REACTION_WHEEL_XTEDS_H

#define _STRING_SINGLE_REACTION_WHEEL_XTEDS \
"<?xml version=\"1.0\" encoding=\"utf-8\" ?>" \
"<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
"xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"Reaction_Wheel_XTEDS\"" \
"version=\"2.1\">" \
"<Device name=\"Single_Reaction_Wheel\" kind=\"rWheel\" description=\"An xTeds for a single reaction wheel using the 2.0 xTeds schema and the CDD\"/>" \
"" \
"<Interface name=\"RWSingleInterface\" id=\"1\">" \
"<Qualifier name=\"MaxMomentum\" value=\"5.0\" units=\"Nms\" />" \
"<Qualifier name=\"NominalMomentum\" value=\"2.0\" units=\"Nms\" />" \
"<Qualifier name=\"TorqueLossMomentum\" value=\"1.0\" units=\"Nms\"/>" \
"<Qualifier name=\"MaxTorqueAtMaxSpeed\" value=\"10.0\"  units=\"Nm\" />" \
"<Qualifier name=\"MaxTorqueAtNominalSpeed\" value=\"5.0\" units=\"Nm\"/>" \
"<Qualifier name=\"TimeConstant\" value=\"0.1\" units=\"s\" />" \
"<Qualifier name=\"IdlePower\" value=\"1.0\" units=\"W\"/>" \
"<Qualifier name=\"MaxPower\" value=\"10.0\" units=\"W\"/>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable name=\"opMode\" kind=\"mode\" format=\"UINT16\" >" \
"<Drange name=\"enumModes\" >" \
"<Option name=\"idle\" value=\"0\"/>" \
"<Option name=\"operating\" value=\"1\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"dataQuality\" kind=\"DataQuality\" format=\"UINT08\">" \
"<Drange name=\"DataQualityEnum\">" \
"<Option name=\"dataBad\" value=\"0\" description=\"data is garbage or NaN.\" />" \
"<Option name=\"dataPoor\" value=\"1\" description=\"data quality is poor.\" />" \
"<Option name=\"dataGood\" value=\"2\" description=\"data is good.\" />" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"commandedTorque\" kind=\"torque\" format=\"FLOAT32\" units=\"Nm\" description=\"Magnitude of torque requested of this device\" />" \
"<Variable name=\"currentMomentum\" kind=\"angularMomentum\" format=\"FLOAT32\" units=\"Nms\" description=\"The current momentum of this wheel.\" />" \
"<Variable name=\"satPercentage\" kind=\"saturationLevel\" format=\"FLOAT32\" units=\"percent\" description=\"The current percentage of saturation of this wheel.\" />" \
"<Command>" \
"<!-- note: the name of a command uniquely identifies it within the dictionary -->" \
"<CommandMsg name=\"SingleAxisTorqueCmd\" id=\"1\">" \
"<VariableRef name=\"commandedTorque\" />" \
"</CommandMsg>" \
"</Command>" \
"<!-- note: the \"kind\" attribute is the key identifier of a data element in the dictionary -->" \
"<Notification>" \
"<DataMsg name=\"wheelSatLevel\" msgArrival=\"PERIODIC\" msgRate=\"1\" id=\"2\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"dataQuality\" />" \
"<VariableRef name=\"satPercentage\" />" \
"</DataMsg>" \
"</Notification>" \
"<Notification>" \
"<DataMsg name=\"MomentumCurrent\" msgArrival=\"PERIODIC\" msgRate=\"10\" id=\"3\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"dataQuality\" />" \
"<VariableRef name=\"currentMomentum\" />" \
"</DataMsg>" \
"</Notification>" \
"<Command>" \
"<CommandMsg name=\"setOpMode\" id=\"4\">" \
"<VariableRef name=\"opMode\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Notification>" \
"<DataMsg name=\"opModeChanged\" id=\"5\" msgArrival=\"EVENT\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"opMode\"/>" \
"</DataMsg>" \
"</Notification>" \
"</Interface>" \
"" \
"<Interface name=\"DevPwr\" id=\"4\">" \
"<Qualifier name=\"CurrentLoKeepout\" value=\"0.0\" units=\"A\"/>" \
"<Qualifier name=\"CurrentLoWarning\" value=\"0.0\" units=\"A\"/>" \
"<Qualifier name=\"CurrentHiWarning\" value=\"3.5\" units=\"A\"/>" \
"<Qualifier name=\"CurrentHiKeepout\" value=\"3.5\" units=\"A\"/>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable name=\"DevPwrState\" kind=\"Power_State\" format=\"UINT08\">" \
"<Drange name=\"DevPwrStateEnum\">" \
"<Option name=\"DevPwrOFF\" value=\"0\" description=\"All power to device is turned off.\" />" \
"<Option name=\"DevPwrON\" value=\"1\" description=\"Device may draw full power.\" />" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"DevPwrStateSet\" kind=\"Power_State\" format=\"UINT08\" id=\"2\">" \
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
"" \
"</Interface>" \
"" \
"<Interface name=\"CmpSOH\" id=\"5\">" \
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
