#ifndef _POWERCONTROLLER_XTEDS_H
#define _POWERCONTROLLER_XTEDS_H

#define _STRING_POWERCONTROLLER_XTEDS \
"<?xml version=\"1.0\" encoding=\"utf-8\" ?>" \
"<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
"xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"Battery_XTEDS\"" \
"version=\"2.0\">" \
"<Application name=\"PowerController\" kind=\"PowerControl\" description=\"Routine Control of Spacecraft Power\" >" \
"<Qualifier name=\"Author\" value=\"Design_Net\"/>" \
"<Qualifier name=\"Version\" value=\"1.1\"/>" \
"<Qualifier name=\"RevisionDate\" value=\"03-27-2007\"/>" \
"</Application>" \
"" \
"<Interface name=\"PowerStatusInterface\" id=\"1\">" \
"<Variable name=\"Time\" kind=\"Time\" format=\"UINT32\" units=\"Seconds\" />" \
"<Variable name=\"SubS\" kind=\"SubSeconds\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\" />" \
"<Variable name=\"BusVoltage\" kind=\"BusVoltage\" format=\"FLOAT32\" units=\"Volts\" description=\"Spacecraft Bus Voltage\" />" \
"<Variable name=\"EnergyStoreCapacity\" kind=\"Capacity\" format=\"FLOAT32\" units=\"Watt-Hrs\" description=\"Energy Storage Capacity\">" \
"<Qualifier name=\"Scope\" value=\"System\"/>" \
"<Qualifier name=\"Category\" value=\"Max\"/>" \
"</Variable>" \
"<Variable name=\"EnergyStorePowerCapacity\" kind=\"Capacity\" format=\"FLOAT32\" units=\"Watts\" description=\"Energy Storage Power Capacity\">" \
"<Qualifier name=\"Scope\" value=\"System\"/>" \
"<Qualifier name=\"Category\" value=\"Max\"/>" \
"</Variable>" \
"<Variable name=\"CollectionPowerCapacity\" kind=\"Capacity\" format=\"FLOAT32\" units=\"Watts\" description=\"Energy Collection Power Capacity\">" \
"<Qualifier name=\"Scope\" value=\"System\"/>" \
"<Qualifier name=\"Category\" value=\"Max\"/>" \
"</Variable>" \
"<Variable name=\"DissipationPowerCapacity\" kind=\"Capacity\" format=\"FLOAT32\" units=\"Watts\" description=\"Energy Dissipation Power Capacity\">" \
"<Qualifier name=\"Scope\" value=\"System\"/>" \
"<Qualifier name=\"Category\" value=\"Max\"/>" \
"</Variable>" \
"<Variable name=\"StoredEnergy\" kind=\"Quantity\" format=\"FLOAT32\" units=\"Watt-Hrs\" description=\"Energy Store Stored Energy\">" \
"<Qualifier name=\"Scope\" value=\"System\"/>" \
"<Qualifier name=\"Category\" value=\"Instantaneous\"/>" \
"</Variable>" \
"<Variable name=\"EnergyStoreStateOfCharge\" kind=\"Percentage\" format=\"FLOAT32\" units=\"Percent\" description=\"Energy Store State Of Charge\">" \
"<Qualifier name=\"Scope\" value=\"System\"/>" \
"<Qualifier name=\"Category\" value=\"Instantaneous\"/>" \
"</Variable>" \
"<Variable name=\"EnergyStorePower\" kind=\"Power\" format=\"FLOAT32\" units=\"Watts\" description=\"Energy Store Power\">" \
"<Qualifier name=\"Scope\" value=\"System\"/>" \
"<Qualifier name=\"Category\" value=\"Instantaneous\"/>" \
"</Variable>" \
"<Variable name=\"CollectionPower\" kind=\"Power\" format=\"FLOAT32\" units=\"Watts\" description=\"Energy Collection Power\">" \
"<Qualifier name=\"Scope\" value=\"System\"/>" \
"<Qualifier name=\"Category\" value=\"Instantaneous\"/>" \
"</Variable>" \
"<Variable name=\"DissipationPower\" kind=\"Power\" format=\"FLOAT32\" units=\"Watts\" description=\"Energy Dissipation Power\">" \
"<Qualifier name=\"Scope\" value=\"System\"/>" \
"<Qualifier name=\"Category\" value=\"Instantaneous\"/>" \
"</Variable>" \
"<Variable name=\"DevicePower\" kind=\"Power\" format=\"FLOAT32\" units=\"Watts\" description=\"Device Power\">" \
"<Qualifier name=\"Scope\" value=\"System\"/>" \
"<Qualifier name=\"Category\" value=\"Instantaneous\"/>" \
"</Variable>" \
"<Variable name=\"TimeToYellowLimit\" kind=\"Duration\" format=\"UINT32\" units=\"Seconds\" description=\"Time until Yellow Limit Condition is Reached\" >" \
"<Qualifier name=\"Scope\" value=\"PowerController\"/>" \
"<Qualifier name=\"Target\" value=\"PowerAdvisoryCondition\"/>" \
"</Variable>" \
"<Variable name=\"TimeToRedLimit\" kind=\"Duration\" format=\"UINT32\" units=\"Seconds\" description=\"Time until Red Limit Condition is Reached\" >" \
"<Qualifier name=\"Scope\" value=\"PowerManagement\"/>" \
"<Qualifier name=\"Target\" value=\"PowerWarningCondition\"/>" \
"</Variable>" \
"<Variable name=\"SensorId\" kind=\"Identification\" format=\"UINT32\" description=\"Unique identifier of spacecraft component\"/>" \
"<Variable name=\"HubNumber\" kind=\"Identification\" format=\"UINT32\" description=\"Hub number\"/>" \
"<Variable name=\"PortNumber\" kind=\"Identification\" format=\"UINT32\" description=\"Port number\"/>" \
"" \
"<!-- Notifications -->" \
"<Notification>" \
"<DataMsg name=\"PowerState\" description=\"System-Level Power State\" id=\"1\" msgArrival=\"PERIODIC\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"BusVoltage\" />" \
"<VariableRef name=\"EnergyStoreCapacity\" />" \
"<VariableRef name=\"EnergyStorePowerCapacity\" />" \
"<VariableRef name=\"CollectionPowerCapacity\" />" \
"<VariableRef name=\"DissipationPowerCapacity\" />" \
"<VariableRef name=\"StoredEnergy\" />" \
"<VariableRef name=\"EnergyStoreStateOfCharge\" />" \
"<VariableRef name=\"EnergyStorePower\" />" \
"<VariableRef name=\"CollectionPower\" />" \
"<VariableRef name=\"DissipationPower\" />" \
"<VariableRef name=\"DevicePower\" />" \
"</DataMsg>" \
"</Notification>" \
"<Notification>" \
"<DataMsg name=\"YellowLimitState\" description=\"Time remaining until yellow limit event\" id=\"2\" msgArrival=\"PERIODIC\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"TimeToYellowLimit\"/>" \
"</DataMsg>" \
"</Notification>" \
"<Notification>" \
"<DataMsg name=\"RedLimitState\" description=\"Time remaining until red limit event\" id=\"3\" msgArrival=\"PERIODIC\">" \
"<Qualifier name=\"telemetryLevel\" value=\"1\"/>" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"TimeToRedLimit\"/>" \
"</DataMsg>" \
"</Notification>" \
"<Notification>" \
"<DataMsg name=\"YellowLimitEvent\" description=\"Yellow limit condition notification\" id=\"4\" msgArrival=\"EVENT\">" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"EnergyStoreStateOfCharge\" />" \
"</DataMsg>" \
"</Notification>" \
"<Notification>" \
"<DataMsg name=\"RedLimitEvent\" description=\"Red limit condition notification\" id=\"5\" msgArrival=\"EVENT\">" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"EnergyStoreStateOfCharge\" />" \
"</DataMsg>" \
"</Notification>" \
"<Notification>" \
"<DataMsg name=\"PortSoftTripEvent\" description=\"Power hub port soft current trip notification\" id=\"6\" msgArrival=\"EVENT\">" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"SensorId\" />" \
"<VariableRef name=\"HubNumber\" />" \
"<VariableRef name=\"PortNumber\" />" \
"</DataMsg>" \
"</Notification>" \
"<Notification>" \
"<DataMsg name=\"PortHardTripEvent\" description=\"Power hub port hard current trip notification\" id=\"7\" msgArrival=\"EVENT\">" \
"<VariableRef name=\"Time\" />" \
"<VariableRef name=\"SubS\" />" \
"<VariableRef name=\"SensorId\" />" \
"<VariableRef name=\"HubNumber\" />" \
"<VariableRef name=\"PortNumber\" />" \
"</DataMsg>" \
"</Notification>" \
"" \
"<!-- Commands -->" \
"<Command>" \
"<CommandMsg name=\"ResetSoftTrippedPort\" id=\"8\">" \
"<VariableRef name=\"HubNumber\" />" \
"<VariableRef name=\"PortNumber\" />" \
"</CommandMsg>" \
"</Command>" \
"<Command>" \
"<CommandMsg name=\"ResetHardTrippedPort\" id=\"9\">" \
"<VariableRef name=\"HubNumber\" />" \
"<VariableRef name=\"PortNumber\" />" \
"</CommandMsg>" \
"</Command>" \
"</Interface>" \
"" \
"<Interface name=\"PowerPlanningInterface\" id=\"2\">" \
"<Variable name=\"PlanId\" kind=\"Identification\" format=\"UINT32\" description=\"Unique identifier of planning request\"/>" \
"<Variable name=\"Timeout\" kind=\"Duration\" format=\"UINT32\" description=\"Time until plan expires if not acknowledged\"/>" \
"<Variable name=\"NewTimeToYellowLimit\" kind=\"Duration\" format=\"UINT32\" units=\"Seconds\" description=\"Time until Yellow Limit Condition is Reached\" />" \
"<Variable name=\"NewTimeToRedLimit\" kind=\"Duration\" format=\"UINT32\" units=\"Seconds\" description=\"Time until Red Limit Condition is Reached\" />" \
"" \
"<!-- Requests -->" \
"<Request>" \
"<CommandMsg name=\"RequestPower\" id=\"1\">" \
"" \
"</CommandMsg>" \
"<DataReplyMsg name=\"RequestPowerReply\" id=\"2\">" \
"<VariableRef name=\"PlanId\"/>" \
"<VariableRef name=\"NewTimeToYellowLimit\"/>" \
"<VariableRef name=\"NewTimeToRedLimit\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"" \
"<!-- Commands -->" \
"<Command>" \
"<CommandMsg name=\"AcknowledgePlan\" id=\"3\">" \
"<VariableRef name=\"PlanId\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Command>" \
"<CommandMsg name=\"CancelPlan\" id=\"4\">" \
"<VariableRef name=\"PlanId\"/>" \
"</CommandMsg>" \
"</Command>" \
"</Interface>" \
"" \
"</xTEDS>" \
""

#endif
