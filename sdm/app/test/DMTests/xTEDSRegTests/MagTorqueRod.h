#ifndef _BASICMAGNETICTORQUEROD_XTEDS_H
#define _BASICMAGNETICTORQUEROD_XTEDS_H

#define _STRING_BASICMAGNETICTORQUEROD_XTEDS \
"<?xml version=\"1.0\" encoding=\"utf-8\" ?>" \
"<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
"xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS xTEDS02.xsd\" name=\"MagneticTorqueRodxTeds\"" \
"version=\"2.0\">" \
"<Device name=\"BasicMagneticTorqueRod\" kind=\"mtr\" description=\"Basic (on/off + polarity) magnetic torquer\" />" \
"<Interface name=\"MagTorquerBasic\" id=\"1\">" \
"<Qualifier name=\"headID\" value=\"0\"/>" \
"<Variable name=\"polarity\" kind=\"polarity\" units=\"0_1\" format=\"UINT08\">" \
"<Drange name=\"PolarityEnum\">" \
"<Option name=\"North\" value=\"0\" description=\"North polarity of device dipole\" />" \
"<Option name=\"South\" value=\"1\" description=\"South polarity of device dipole\" />" \
"</Drange>" \
"</Variable>" \
"<Command>" \
"<CommandMsg name=\"MTROnCmd\" id=\"1\">" \
"<VariableRef name=\"polarity\" />" \
"</CommandMsg>" \
"</Command>" \
"<Command>" \
"<CommandMsg name=\"MTROffCmd\" id=\"2\" />" \
"</Command>" \
"</Interface>" \
"" \
"<Interface name=\"DevPwr\" id=\"2\">" \
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
"</Interface>" \
"" \
"<Interface name=\"CmpSOH\" id=\"3\">" \
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
"</xTEDS>" \
""

#endif
