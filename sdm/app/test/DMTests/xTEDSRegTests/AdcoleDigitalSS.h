#ifndef _ADCOLE_NRL_DIGITAL_SUN_SENSOR_XTEDS_H
#define _ADCOLE_NRL_DIGITAL_SUN_SENSOR_XTEDS_H

#define _STRING_ADCOLE_NRL_DIGITAL_SUN_SENSOR_XTEDS \
"<?xml version=\"1.0\" encoding=\"utf-8\" ?>" \
"<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
"xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"Adcole_Digital_Sun_Sensor\" version=\"1.0\"><!-- plc changed xTEDS schema location -->" \
"<Device name=\"Adcole_NRL_Digital_Sun_Sensor\" kind=\"Sun_Sensor\" modelId=\"DSS\" description=\"Adcole Digital 2-Axis Sun Sensor\"/>" \
"" \
"<Interface name=\"Sun_Sensor_Interface\" id=\"1\"><!-- plc added Interface element -->" \
"" \
"<!-- Timestamp -->" \
"<Variable kind=\"Time\" name=\"Time\" format=\"UINT32\" units=\"Seconds\"><!-- plc changed FORMAT value -->" \
"</Variable>" \
"<Variable kind=\"SubSeconds\" name=\"SubS\" units=\"Counts\" format=\"UINT32\" scaleFactor=\".0001\" scaleUnits=\"Seconds\"><!-- plc changed FORMAT value -->" \
"</Variable>" \
"" \
"" \
"<!-- Data Definitions -->" \
"<Variable name=\"Data_Rate\" id=\"3\" kind=\"Msg_Rate\" rangeMax=\"10000\" rangeMin=\"0\" units=\"Hz\" format=\"INT16\"/><!-- plc changed FORMAT value -->" \
"<Variable name=\"ID\" id=\"4\" kind=\"ID\" format=\"UINT08\"/><!-- plc changed FORMAT value -->" \
"" \
"<Variable name=\"Sensor_Number\" id=\"5\" kind=\"TBD\" units=\"Counts\" format=\"UINT16\"/><!-- plc changed FORMAT value -->" \
"<Variable name=\"Sun_Presence\" id=\"6\" kind=\"TBD\" units=\"Counts\" format=\"UINT16\" rangeMin=\"0\" rangeMax=\"1\"/><!-- plc changed FORMAT value -->" \
"<Variable name=\"Sun_Angle_X\" id=\"7\" kind=\"Angle\" units=\"Degrees\" format=\"FLOAT32\" rangeMin=\"-128\" rangeMax=\"128\" accuracy=\"0.25\" /><!-- plc changed FORMAT value -->" \
"<Variable name=\"Sun_Angle_Y\" id=\"8\" kind=\"Angle\" units=\"Degrees\" format=\"FLOAT32\" rangeMin=\"-128\" rangeMax=\"128\" accuracy=\"0.25\" /><!-- plc changed FORMAT value -->" \
"" \
"<!-- Data Messages -->" \
"" \
"<Notification><!-- plc added Notification element -->" \
"<DataMsg id=\"2\" name=\"Sun_Angle\" msgArrival=\"PERIODIC\" msgRate=\"100\">" \
"<VariableRef name=\"SubS\"/>" \
"<VariableRef name=\"Time\"/>" \
"<VariableRef name=\"Sensor_Number\"/>" \
"<VariableRef name=\"Sun_Presence\"/>" \
"<VariableRef name=\"Sun_Angle_X\"/>" \
"<VariableRef name=\"Sun_Angle_Y\"/>" \
"</DataMsg>" \
"</Notification>" \
"" \
"<!-- Command Messages -->" \
"<Command><!-- plc added Command element -->" \
"<CommandMsg id=\"10\" name=\"Power_Off\"/>" \
"</Command>" \
"" \
"<Command><!-- plc added Command element -->" \
"<CommandMsg id=\"11\" name=\"Power_On\"/>" \
"</Command>" \
"" \
"<Command><!-- plc added Command element -->" \
"<CommandMsg id=\"12\" name=\"Message_Rate\">" \
"<VariableRef name=\"ID\"/>" \
"<VariableRef name=\"Data_Rate\" />" \
"</CommandMsg>" \
"</Command>" \
"" \
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
"<Option name=\"DevPwrOFF\" value=\"0\" />" \
"<Option name=\"DevPwrON\" value=\"1\" />" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"DevPwrStateSet\" kind=\"Power_State\" format=\"UINT08\" id=\"2\">" \
"<Drange name=\"DevPwrStateEnumReference\" >" \
"<Option name=\"DevPwrOFF\" value=\"0\" />" \
"<Option name=\"DevPwrON\" value=\"1\" />" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"modePowers\" kind=\"power\" format=\"FLOAT32\" units=\"W\" length=\"2\" />" \
"<Command>" \
"<CommandMsg name=\"DevPwrSetState\" id=\"1\">" \
"<VariableRef name=\"DevPwrStateSet\" />" \
"</CommandMsg>" \
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
"</xTEDS>" \
""

#endif
