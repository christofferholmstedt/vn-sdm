#ifndef _ROBOHUB_8_PORT_XTEDS_H
#define _ROBOHUB_8_PORT_XTEDS_H

#define _STRING_ROBOHUB_8_PORT_XTEDS \
"<?xml version=\"1.0\" encoding=\"utf-8\" ?>" \
"<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"Robo_Hub_xTEDS\" version=\"11.16\">" \
"" \
"<Device name=\"RoboHub_8_Port\" kind=\"Robust_Hub\" modelId=\"0001\" >" \
"<Qualifier name=\"Manufacturer\" value=\"DataDesignCorp\"/>" \
"<Qualifier name=\"Model\" value=\"Gen1\"/>" \
"<Qualifier name=\"SerialNumber\" value=\"12345\"/>" \
"</Device>" \
"" \
"<!-- Panel interface -->" \
"<Interface id=\"1\" name=\"PanelPowerInterface\" description=\"Panel power interface\">" \
"<Qualifier name=\"NumberOfPorts\" value=\"4\"/>" \
"<Qualifier name=\"BreakerTripCurrent\" value=\"30.0\" units=\"Amps\"/>" \
"<Variable name=\"PortReference\" kind=\"PowerPortNumber\" format=\"UINT08\"/>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\"/>" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\"/>" \
"<Variable name=\"PanelVoltage\" kind=\"Voltage\" format=\"INT16\" scaleFactor=\"0.1\" scaleUnits=\"Volts\"/>" \
"<Variable name=\"BreakerCurrentArray\" length=\"4\" kind=\"Current\" format=\"INT16\" scaleFactor=\"1.0\" scaleUnits=\"Amps\">" \
"<Qualifier name=\"Panel\" value=\"Array_4\"/>" \
"</Variable>" \
"<Variable name=\"PortPowerStateArray\" length=\"4\" kind=\"enumeration\" format=\"UINT08\">" \
"<Drange name=\"PowerStateEnum\">" \
"<Option name=\"Open\" value=\"0\"/>" \
"<Option name=\"Closed\" value=\"1\"/>" \
"</Drange>" \
"</Variable>" \
"<Notification>" \
"<DataMsg id=\"1\" name=\"PowerStatus\" msgArrival=\"PERIODIC\" msgRate=\"1\" >" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"PanelVoltage\"/>" \
"<VariableRef name=\"BreakerCurrentArray\"/>" \
"<VariableRef name=\"PortPowerStateArray\"/>" \
"</DataMsg>" \
"</Notification>" \
"<Command>" \
"<CommandMsg id=\"2\" name=\"PortPowerOn\" >" \
"<VariableRef name=\"PortReference\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Command>" \
"<CommandMsg id=\"3\" name=\"PortPowerOff\" >" \
"<VariableRef name=\"PortReference\"/>" \
"</CommandMsg>" \
"</Command>" \
"</Interface>" \
"" \
"<!-- Hub interface -->" \
"<Interface id=\"2\" name=\"RoboHubInterface\" description=\"Interface for robust hub\">" \
"<Qualifier name=\"NumberOfPorts\" value=\"8\"/>" \
"<Qualifier name=\"PortTripCurrent\" value=\"4.5\" units=\"Amps\"/>" \
"<Variable name=\"PortReference\" kind=\"HubPortNumber\" format=\"UINT08\" description=\"Refers to a port for events and commands\"/>" \
"<Variable name=\"PortEnumeration\" kind=\"HubEnumerationStatus\" format=\"UINT08\" description=\"Used to indicate hub enumeration state\"/>" \
"<Variable name=\"PPS_Status\" kind=\"PpsStatus\" format=\"UINT08\" description=\"Used to indicate PPS status\"/>" \
"<Variable name=\"SetTripCurrentVal\" kind=\"TripCurrent\" format=\"INT16\" scaleFactor=\"0.1\" defaultValue=\"10\" scaleUnits=\"Amps\"/>" \
"<Variable name=\"PortPowerState\" kind=\"PortPowerState\" format=\"UINT08\">" \
"<Drange name=\"PowerStateEnum\">" \
"<Option name=\"Open\" value=\"0\"/>" \
"<Option name=\"Closed\" value=\"1\"/>" \
"<Option name=\"HardTrip\" value=\"2\"/>" \
"<Option name=\"SoftTrip\" value=\"3\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable name=\"PortVoltageArray\" length=\"8\" kind=\"Voltage\" format=\"INT16\" scaleFactor=\"0.1\" scaleUnits=\"Volts\">" \
"<Qualifier name=\"HubPort\" value=\"Array_8\"/>" \
"</Variable>" \
"<Variable name=\"PortCurrentArray\" length=\"8\" kind=\"Current\" format=\"INT16\" scaleFactor=\"0.1\" scaleUnits=\"Amps\">" \
"<Qualifier name=\"HubPort\" value=\"Array_8\"/>" \
"</Variable>" \
"<Variable name=\"SoftCurrentLimitArray\" length=\"8\" kind=\"TripCurrent\" format=\"INT16\" scaleFactor=\"0.1\" defaultValue=\"10\" scaleUnits=\"Amps\">" \
"<Qualifier name=\"HubPort\" value=\"Array_8\"/>" \
"</Variable>" \
"<Variable name=\"PortPowerStateArray\" length=\"8\" kind=\"boolean\" format=\"UINT08\">" \
"<Qualifier name=\"HubPort\" value=\"Array_8\"/>" \
"<Drange name=\"PowerStateEnumArray\">" \
"<Option name=\"Open\" value=\"0\"/>" \
"<Option name=\"Closed\" value=\"1\"/>" \
"<Option name=\"HardTrip\" value=\"2\"/>" \
"<Option name=\"SoftTrip\" value=\"3\"/>" \
"</Drange>" \
"</Variable>" \
"<Notification>" \
"<DataMsg id=\"1\" name=\"PortStatus\" msgArrival=\"PERIODIC\" msgRate=\"1\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"PortPowerStateArray\"/>" \
"<VariableRef name=\"PortVoltageArray\"/>" \
"<VariableRef name=\"PortCurrentArray\"/>" \
"</DataMsg>" \
"</Notification>" \
"<Notification>" \
"<DataMsg id=\"2\" name=\"PortTripped\" msgArrival=\"EVENT\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"PortReference\"/>" \
"<VariableRef name=\"PortPowerState\"/>" \
"</DataMsg>" \
"</Notification>" \
"<Command>" \
"<CommandMsg id=\"3\" name=\"ConfigureSoftTrip\">" \
"<VariableRef name=\"PortReference\"/>" \
"<VariableRef name=\"SetTripCurrentVal\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Command>" \
"<CommandMsg id=\"4\" name=\"PortPowerOn\" >" \
"<VariableRef name=\"PortReference\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Command>" \
"<CommandMsg id=\"5\" name=\"PortPowerOff\" >" \
"<VariableRef name=\"PortReference\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Request>" \
"<CommandMsg id=\"6\" name=\"GetHubStatus\"/>" \
"<DataReplyMsg id=\"7\" name=\"HubStatusReply\">" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"PortEnumeration\"/>" \
"<VariableRef name=\"PPS_Status\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg id=\"8\" name=\"GetSoftTripLimits\"/>" \
"<DataReplyMsg id=\"9\" name=\"SoftLimitSettingsReply\">" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"SoftCurrentLimitArray\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"</Interface>" \
"" \
"<!-- Component safety interface -->" \
"<Interface name=\"CmpSafety\" id=\"3\">" \
"<Qualifier name=\"TemperatureLoKeepout\" value=\"-20.0\" units=\"degC\"/>" \
"<Qualifier name=\"TemperatureLoWarning\" value=\"-10.0\" units=\"degC\"/>" \
"<Qualifier name=\"TemperatureHiWarning\" value=\"50.0\" units=\"degC\"/>" \
"<Qualifier name=\"TemperatureHiKeepout\" value=\"60.0\" units=\"degC\"/>" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\"/>" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\"/>" \
"<Variable name=\"DeviceTemperature\" kind=\"temperature\" format=\"INT16\" scaleFactor=\"1.0\" scaleUnits=\"degC\"/>" \
"<Variable name=\"PanelTemperatureArray\" length=\"8\" kind=\"temperature\" format=\"INT16\" scaleFactor=\"1.0\" scaleUnits=\"degC\">" \
"<Qualifier name=\"PanelTemperatureChannel\" value=\"Array_8\"/>" \
"</Variable>" \
"<Notification>" \
"<DataMsg name=\"DeviceTemp\" id=\"1\" msgArrival=\"PERIODIC\" msgRate=\"1\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"DeviceTemperature\"/>" \
"<VariableRef name=\"PanelTemperatureArray\"/>" \
"</DataMsg>" \
"</Notification>" \
"</Interface>" \
"" \
"</xTEDS>" \
""

#endif
