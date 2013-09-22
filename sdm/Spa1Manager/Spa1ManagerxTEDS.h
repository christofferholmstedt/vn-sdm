#ifndef __SPA1_XTEDS_H__
#define __SPA1_XTEDS_H__

const char* spa1ManagerxTEDS = "<?xml version=\"1.0\" encoding=\"utf-8\" ?>\n\
<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"\n\
 xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"Spa1Manager\" version=\"1.0\">\n\
\t<Application name=\"Spa1Manager\" kind=\"Software\" description=\"SDM Core component used to manage a SPA-1 network\" />\n\
\t<Interface name=\"AsimInfo\" id=\"1\" description=\"Data relating to the SPA-1 ASIMs registered with the Spa1Manager\" >\n\
\t\t<Variable name=\"numRegistered\" kind=\"counter\" format=\"UINT32\" description=\"Number of SPA-1 ASIMs currently registered\" />\n\
\t\t<Variable name=\"sensorID\" kind=\"ID\" format=\"UINT32\" description=\"The sensorID of a SPA-1 ASIM\" />\n\
\t\t<Variable name=\"name\" kind=\"string\" format=\"INT08\" length=\"25\" />\n\
\t\t<Variable name=\"i2cAddress\" kind=\"index\" format=\"UINT08\" description=\"The I2C address an ASIM is currently registered on\" />\n\
\t\t<Variable name=\"guid\" kind=\"ID\" format=\"UINT32\" description=\"GUID used by an ASIM for I2C arbitration\" />\n\
\t\t<Variable name=\"regType\" kind=\"status\" format=\"UINT08\" description=\"0 for registrations, 1 for deregestrations\" />\n\
\t\t<Variable name=\"xTEDS\" kind=\"string\" format=\"INT08\" />\n\
\t\t<Variable name=\"xTEDSSize\" kind=\"counter\" format=\"UINT16\" />\n\
\t\t<Notification>\n\
\t\t\t<DataMsg name=\"RegistrationChange\" description=\"Change in ASIM registrations\" id=\"1\" msgArrival=\"EVENT\" >\n\
\t\t\t\t<VariableRef name=\"regType\" />\n\
\t\t\t\t<VariableRef name=\"sensorID\" />\n\
\t\t\t</DataMsg>\n\
\t\t</Notification>\n\
\t\t<Request>\n\
\t\t\t<CommandMsg name=\"xTEDSById\" description=\"Get an xTEDS for an ASIM by its SensorID\" id=\"2\" >\n\
\t\t\t\t<VariableRef name=\"sensorID\" />\n\
\t\t\t</CommandMsg>\n\
\t\t\t<DataReplyMsg name=\"xTEDSReply\" description=\"Contains the requested xTEDS\" id=\"3\" >\n\
\t\t\t\t<VariableRef name=\"xTEDSSize\" />\n\
\t\t\t\t<VariableRef name=\"xTEDS\" />\n\
\t\t\t</DataReplyMsg>\n\
\t\t</Request>\n\
\t\t<Request>\n\
\t\t\t<CommandMsg name=\"GetAsimDetails\" description=\"Retreive details about a registered SPA-1 ASIM\" id=\"4\" >\n\
\t\t\t\t<VariableRef name=\"sensorID\" />\n\
\t\t\t</CommandMsg>\n\
\t\t\t<DataReplyMsg name=\"AsimDetails\" id=\"5\" >\n\
\t\t\t\t<VariableRef name=\"sensorID\" />\n\
\t\t\t\t<VariableRef name=\"i2cAddress\" />\n\
\t\t\t\t<VariableRef name=\"guid\" />\n\
\t\t\t\t<VariableRef name=\"name\" />\n\
\t\t\t</DataReplyMsg>\n\
\t\t</Request>\n\
\t</Interface>\n\
\t<Interface name=\"Bus\" id=\"2\" description=\"Data and controls pertaining to the SPA-1 Bus\" >\n\
\t\t<Command>\n\
\t\t\t<CommandMsg name=\"ResetBus\" id=\"1\" />\n\
\t\t</Command>\n\
\t</Interface>\n\
</xTEDS>"; 

#endif
