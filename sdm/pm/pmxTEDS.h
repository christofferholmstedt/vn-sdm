#ifndef _SDM_PM_XTEDS_H_
#define _SDM_PM_XTEDS_H_

const char * xTEDS = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n \
	<xTEDS version=\"2.0\" xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"Process_Manager_xTEDS\">\n \
	\t<Application kind=\"Software\" name=\"ProcessManager\"/>\n \
	\t<Interface name=\"Msg_Count\" id=\"2\">\n \
	\t\t<Variable name=\"Total_Messages_Recd\" kind=\"Total\" format=\"UINT32\"/>\n  \
	\t\t<Variable name=\"Messages_Last_Second_Recd\" kind=\"Total\" format=\"UINT32\"/>\n \
	\t\t<Variable name=\"Total_Messages_Sent\" kind=\"Total\" format=\"UINT32\"/>\n \
	\t\t<Variable name=\"Messages_Last_Second_Sent\" kind=\"Total\" format=\"UINT32\"/>\n \
	\n \
	\t\t<Notification>\n \
	\t\t\t<DataMsg name=\"Message_Count\" id=\"13\" msgArrival=\"PERIODIC\">\n \
	\t\t\t\t<VariableRef name=\"Total_Messages_Recd\"/>\n \
	\t\t\t\t<VariableRef name=\"Messages_Last_Second_Recd\"/>\n \
	\t\t\t\t<VariableRef name=\"Total_Messages_Sent\"/>\n \
	\t\t\t\t<VariableRef name=\"Messages_Last_Second_Sent\"/>\n \
	\t\t\t</DataMsg>\n \
	\t\t</Notification>\n \
	\t</Interface>\n \
	\t<Interface name=\"Message_Log\" id=\"3\">\n \
	\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"Msg_Type\"/>\n \
	\t\t<Variable format=\"UINT32\" kind=\"IP_long\" name=\"Address\"/>\n \
	\t\t<Variable format=\"UINT16\" kind=\"Port_of_Device\" name=\"Port\"/>\n \
	\t\t<Variable format=\"UINT32\" kind=\"ID\" name=\"Sensor_ID\"/>\n \
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
	</xTEDS>";

#endif
