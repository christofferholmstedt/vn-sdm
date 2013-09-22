#ifndef _VEHICLEINFORMATIONSERVICE_XTEDS_H
#define _VEHICLEINFORMATIONSERVICE_XTEDS_H

#define _STRING_VEHICLEINFORMATIONSERVICE_XTEDS \
"<?xml version=\"1.0\" encoding=\"utf-8\" ?>" \
"<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
"xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS xTEDS02.xsd\" name=\"Adcole_NRL_Digital_Sun_Sensor_\"" \
"version=\"2.0\">" \
"<Application name=\"VehicleInformationService\" version=\"1.0\" kind=\"VSERV\" description=\"Broker of all device packaging and calibration information\" />" \
"" \
"<Interface name=\"PackagingInterface\" id=\"1\" description=\"Used to update and request location and orientation about components\">" \
"<Variable name=\"Position\" kind=\"position\" length=\"3\" format=\"FLOAT32\" units=\"m\" description=\"Location of component frame origin in spacecraft frame.\">" \
"<Qualifier name=\"representation\" value=\"vector\"/>" \
"<Qualifier name=\"frameMeasured\" value=\"SVF\"/>" \
"<Qualifier name=\"frameResolved\" value=\"SVF\"/>" \
"</Variable>" \
"<Variable name=\"Orientation\" kind=\"attitude\" length=\"4\" format=\"FLOAT32\" description=\"Orientaiton of device frame within spacecraft frame\" >" \
"<Qualifier name=\"representation\" value=\"quaternion\"/>" \
"<Qualifier name=\"frameFrom\" value=\"SVF\"/>" \
"<Qualifier name=\"frameTo\" value=\"DVF\"/>" \
"</Variable>" \
"<Variable name=\"updateType\" format=\"UINT08\" kind=\"mode\" description=\"The type of update subscription being requested\">" \
"<Drange name=\"updateTypeEnum\">" \
"<Option name=\"Current\" value=\"0\"/>" \
"<Option name=\"CurrentAndFuture\" value=\"1\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"sensor_ID\" kind=\"ID\" format=\"UINT32\" description=\"sensor ID portion of component ID\" />" \
"<Variable name=\"ip\" kind=\"ipaddress\" format=\"UINT32\" description=\"IP address portion of sensor ID\" />" \
"<Variable name=\"port\" kind=\"port\" format=\"UINT16\" description=\"port portion of component ID\" />" \
"" \
"<Notification>" \
"<DataMsg name=\"PackagingInfoUpdate\" id=\"1\" msgArrival=\"EVENT\" description=\"Notifies all interested parties about a change of packaging info for a component\">" \
"<VariableRef name=\"sensor_ID\"/>" \
"<VariableRef name=\"ip\"/>" \
"<VariableRef name=\"port\"/>" \
"<VariableRef name=\"Position\"/>" \
"<VariableRef name=\"Orientation\"/>" \
"</DataMsg>" \
"</Notification>" \
"<Command>" \
"<CommandMsg name=\"UpdatePackagingInfo\" id=\"2\" description=\"Updates packaging info of the given component\">" \
"<VariableRef name=\"sensor_ID\"/>" \
"<VariableRef name=\"ip\"/>" \
"<VariableRef name=\"port\"/>" \
"<VariableRef name=\"Position\"/>" \
"<VariableRef name=\"Orientation\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Command>" \
"<CommandMsg name=\"UpdateMyPackagingInfo\" id=\"3\" description=\"Updates the packaging info of the component initiating the command\">" \
"<VariableRef name=\"Position\"/>" \
"<VariableRef name=\"Orientation\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Request>" \
"<CommandMsg name=\"GetPackagingInfo\" id=\"4\" description=\"Requests an update on the packaging info for the given component\">" \
"<VariableRef name=\"sensor_ID\"/>" \
"<VariableRef name=\"ip\"/>" \
"<VariableRef name=\"port\"/>" \
"<VariableRef name=\"updateType\"/>" \
"</CommandMsg>" \
"<DataReplyMsg name=\"PackagingInfoReply\" id=\"5\" description=\"Reply to a request for device packaging info\">" \
"<VariableRef name=\"sensor_ID\"/>" \
"<VariableRef name=\"ip\"/>" \
"<VariableRef name=\"port\"/>" \
"<VariableRef name=\"Position\"/>" \
"<VariableRef name=\"Orientation\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Command>" \
"<CommandMsg name=\"SubscribeToPackagingUpdates\" id=\"6\" description=\"Subscribes the sender to all updates for the given component\">" \
"<VariableRef name=\"sensor_ID\"/>" \
"<VariableRef name=\"ip\"/>" \
"<VariableRef name=\"port\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Command>" \
"<CommandMsg name=\"CancelPackagingUpdates\" id=\"7\" description=\"Cancels the sender's subscription to updates for the given component\">" \
"<VariableRef name=\"sensor_ID\"/>" \
"<VariableRef name=\"ip\"/>" \
"<VariableRef name=\"port\"/>" \
"</CommandMsg>" \
"</Command>" \
"<Command>" \
"<CommandMsg name=\"CancelAllPackagingUpdates\" id=\"8\" description=\"Cancels all packaging info update subscriptions held by the sender\" />" \
"</Command>" \
"</Interface>" \
"" \
"</xTEDS>" \
""

#endif
