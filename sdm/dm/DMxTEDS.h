#ifndef _SDM_DM_XTEDS_H_
#define _SDM_DM_XTEDS_H_

/*The Data Mangers xTED*/
const char *dmxTED = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n \
<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"Data_Manager_xTEDS\" version=\"2.0\">\n \
\t<Application name=\"DataManager\" kind=\"Software\"/>\n \
\t<Interface name=\"DM_Interface\" id=\"1\">\n \
\t\t<Variable name=\"Type\" kind=\"Type_of_Response\" format=\"UINT08\">\n \
\t\t\t<Drange name=\"Type_of_Response_Mode\">\n \
\t\t\t\t<Option name=\"Register\" value=\"1\"/>\n \
\t\t\t\t<Option name=\"Deregister\" value=\"2\"/>\n \
\t\t\t\t<Option name=\"Modification\" value=\"3\"/>\n \
\t\t\t</Drange>\n \
\t\t</Variable>\n \
\t\t<Variable name=\"Sensor_ID\" kind=\"ID\" format=\"UINT32\"/>\n \
\t\t<Variable format=\"UINT08\" name=\"DeviceName\" kind=\"String\" length=\"81\"/>\n \
\t\t<Variable format=\"UINT08\" name=\"SPANodePath\" kind=\"Location_of_Device\" length=\"80\"/>\n \
\t\t<Variable format=\"UINT32\" name=\"pid\" kind=\"Process_ID\"/>\n \
\t\t<Variable format=\"UINT16\" name=\"Port\" kind=\"Port_of_Device\"/>\n \
\t\t<Variable format=\"UINT32\" name=\"Address\" kind=\"IP_long\"/>\n \
\t\t<Variable format=\"UINT08\" name=\"ComponentKey\" kind=\"String\" length=\"129\"/>\n \
\n \
\t\t<Notification>\n \
\t\t\t<DataMsg name=\"Registration\" id=\"1\" msgArrival=\"EVENT\" description=\"Registration Event\">\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t</DataMsg>\n \
\t\t</Notification>\n \
\t\t<Notification>\n \
\t\t\t<DataMsg name=\"Deregistration\" id=\"2\" msgArrival=\"EVENT\" description=\"Deregistration Event\">\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t</DataMsg>\n \
\t\t</Notification>\n \
\t\t<Notification>\n \
\t\t\t<DataMsg name=\"Modification\" id=\"3\" msgArrival=\"EVENT\" description=\"xTEDS Update or Merging after registration event\">\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t</DataMsg>\n \
\t\t</Notification>\n \
\t\t<Notification>\n \
\t\t\t<DataMsg name=\"RegisterChange\" id=\"4\" msgArrival=\"EVENT\" description=\"Any Registration or Deregistration or Modification Change\">\n \
\t\t\t\t<VariableRef name=\"Type\"/>\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t</DataMsg>\n \
\t\t</Notification>\n \
\n \
\t\t<Request>\n \
\t\t\t<CommandMsg name=\"SendSensorID\" id=\"6\">\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t</CommandMsg>\n \
\t\t\t<DataReplyMsg name=\"ConvertedDeviceName\" id=\"5\">\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t\t<VariableRef name=\"DeviceName\"/>\n \
\t\t\t</DataReplyMsg>\n \
\t\t</Request>\n \
\t\t<Request>\n \
\t\t\t<CommandMsg name=\"SensorIDtoSPANode\" id=\"11\">\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t</CommandMsg>\n \
\t\t\t<DataReplyMsg name=\"ConvertedSPANode\" id=\"7\">\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t\t<VariableRef name=\"SPANodePath\"/>\n \
\t\t\t</DataReplyMsg>\n \
\t\t</Request>\n \
\t\t<Request>\n \
\t\t\t<CommandMsg name=\"SendPID\" id=\"8\">\n \
\t\t\t\t<VariableRef name=\"pid\"/>\n \
\t\t\t</CommandMsg>\n \
\t\t\t<DataReplyMsg name=\"ReturnSensorID\" id=\"9\">\n \
\t\t\t\t<VariableRef name=\"pid\"/>\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t</DataReplyMsg>\n \
\t\t</Request>\n \
\t\t<Request>\n \
\t\t\t<CommandMsg name=\"SensorIDtoIP\" id=\"12\">\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t</CommandMsg>\n \
\t\t\t<DataReplyMsg name=\"ConvertedIP\" id=\"10\">\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t\t<VariableRef name=\"Address\"/>\n \
\t\t\t\t<VariableRef name=\"Port\"/>\n \
\t\t\t</DataReplyMsg>\n \
\t\t</Request>\n \
\t\t<Request>\n \
\t\t\t<CommandMsg name=\"ComponentIDtoComponentKey\" id=\"14\">\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t\t<VariableRef name=\"Address\"/>\n \
\t\t\t\t<VariableRef name=\"Port\"/>\n \
\t\t\t</CommandMsg>\n \
\t\t\t<DataReplyMsg name=\"ReturnComponentKey\" id=\"15\">\n \
\t\t\t\t<VariableRef name=\"ComponentKey\"/>\n \
\t\t\t</DataReplyMsg>\n \
\t\t</Request>\n \
\t</Interface>\n \
\n \
\t<Interface name=\"Msg_Count\" id=\"2\">\n \
\t\t<Variable name=\"Total_Messages_Recd\" kind=\"Total\" format=\"UINT32\"/>\n \
\t\t<Variable name=\"Messages_Last_Second_Recd\" kind=\"Total\" format=\"UINT32\"/>\n \
\t\t<Variable name=\"Total_Messages_Sent\" kind=\"Total\" format=\"UINT32\"/>\n \
\t\t<Variable name=\"Messages_Last_Second_Sent\" kind=\"Total\" format=\"UINT32\"/>\n \
\t\t<Variable name=\"DroppedxTEDS\" kind=\"counter\" format=\"UINT32\"/>\n \
\t\t<Variable name=\"DroppedCancelxTEDS\" kind=\"counter\" format=\"UINT32\"/>\n \
\n \
\t\t<Notification>\n \
\t\t\t<DataMsg name=\"Message_Count\" id=\"13\" msgArrival=\"PERIODIC\">\n \
\t\t\t\t<VariableRef name=\"Total_Messages_Recd\"/>\n \
\t\t\t\t<VariableRef name=\"Messages_Last_Second_Recd\"/>\n \
\t\t\t\t<VariableRef name=\"Total_Messages_Sent\"/>\n \
\t\t\t\t<VariableRef name=\"Messages_Last_Second_Sent\"/>\n \
\t\t\t</DataMsg>\n \
\t\t</Notification>\n \
\t\t<Request>\n \
\t\t\t<CommandMsg name=\"GetErrors\" id=\"18\" />\n \
\t\t\t<DataReplyMsg name=\"ErrorReply\" id=\"19\" >\n \
\t\t\t\t<VariableRef name=\"DroppedxTEDS\" />\n \
\t\t\t\t<VariableRef name=\"DroppedCancelxTEDS\" />\n \
\t\t\t</DataReplyMsg>\n \
\t\t</Request>\n \
\t</Interface>\n \
\t<Interface name=\"Message_Log\" id=\"3\">\n \
\t\t<Variable format=\"UINT08\" name=\"Msg_Type\" kind=\"TBD\"/>\n \
\t\t<Variable format=\"UINT32\" name=\"Address\" kind=\"IP_long\"/>\n \
\t\t<Variable format=\"UINT16\" name=\"Port\" kind=\"Port_of_Device\"/>\n \
\t\t<Variable format=\"UINT32\" name=\"Sensor_ID\" kind=\"ID\"/>\n \
\t\t<Command>\n \
\t\t\t<CommandMsg name=\"Enable_Logging\" id=\"16\">\n \
\t\t\t\t<VariableRef name=\"Msg_Type\"/>\n \
\t\t\t\t<VariableRef name=\"Address\"/>\n \
\t\t\t\t<VariableRef name=\"Port\"/>\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t</CommandMsg>\n \
\t\t</Command>\n \
\t\t<Command>\n \
\t\t\t<CommandMsg name=\"Disable_Logging\" id=\"17\">\n \
\t\t\t\t<VariableRef name=\"Msg_Type\"/>\n \
\t\t\t\t<VariableRef name=\"Address\"/>\n \
\t\t\t\t<VariableRef name=\"Port\"/>\n \
\t\t\t\t<VariableRef name=\"Sensor_ID\"/>\n \
\t\t\t</CommandMsg>\n \
\t\t</Command>\n \
\t</Interface>\n \
</xTEDS>\n";

#endif
