#ifndef _DOWNLINKCONTROLLER_XTEDS_H
#define _DOWNLINKCONTROLLER_XTEDS_H

#define _STRING_DOWNLINKCONTROLLER_XTEDS \
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>" \
"<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
"xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"DownlinkControllerXTEDS\" description=\"DownlinkController xTEDS\" version=\"1.0\">" \
"" \
"<Application name=\"DownlinkController\" kind=\"CommunicationsFlightSoftware\" description=\"Communications Subsystem Uplinked Command Controller\"/>" \
"" \
"<Interface name=\"DownlinkControllerInterface\" id=\"1\" description=\"Basic interface for scheduling activities and updating their status\">" \
"" \
"<Variable name=\"FileID\" kind=\"tbd\" format=\"UINT08\" length=\"256\"/>" \
"" \
"<Command>" \
"<CommandMsg name=\"DownlinkTelemetry\" id=\"002\" description=\"Deliver a unit of telemetry to the downlink\"/>" \
"</Command>" \
"" \
"<Command>" \
"<CommandMsg name=\"DownlinkFile\" id=\"003\" description=\"Prep and begin downlinking the referenced file\">" \
"<VariableRef name=\"FileID\"/>" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Command>" \
"<CommandMsg name=\"DownlinkSSOH\" id=\"004\" description=\"Prep and begin downlinking Stored State of Health\"/>" \
"</Command>" \
"" \
"</Interface>" \
"" \
"<Interface name=\"DownlinkControllerStatusIf\" id=\"2\">" \
"" \
"<Variable name=\"DownlinkControllerStatus\" kind=\"Status\" format=\"UINT08\">" \
"<Drange name=\"DownlinkControllerStatusEnum\">" \
"<Option value=\"0\" name=\"NOT_INITIALIZED\"/>" \
"<Option value=\"1\" name=\"INITIALIZING\"/>" \
"<Option value=\"1\" name=\"RUNNING\"/>" \
"<Option value=\"2\" name=\"TERMINATING\"/>" \
"</Drange>" \
"</Variable>" \
"" \
"<Variable name=\"DataMsgsDownlinked\"          kind=\"tbd\"                format=\"UINT32\"/>" \
"<Variable name=\"DataRequestsReceived\"        kind=\"tbd\"                format=\"UINT32\"/>" \
"<Variable name=\"DataMsgsInBuffer\"            kind=\"tbd\"                format=\"UINT32\"/>" \
"<Variable name=\"ComponentsRegistered\"        kind=\"tbd\"                format=\"UINT16\"/>" \
"<Variable name=\"FilesRequested\"              kind=\"tbd\"                format=\"UINT16\"/>" \
"<Variable name=\"FilesSuccessfullyDownlinked\" kind=\"tbd\"                format=\"UINT16\"/>" \
"<Variable name=\"FilesFailedDownlinked\"       kind=\"tbd\"                format=\"UINT16\"/>" \
"<Variable name=\"CommandsAccepted\"            kind=\"tbd\"                format=\"UINT16\"/>" \
"<Variable name=\"CommandsRejected\"            kind=\"tbd\"                format=\"UINT16\"/>" \
"" \
"<Notification>" \
"<DataMsg name=\"DownlinkControllerStatusMsg\" id=\"001\" msgArrival=\"EVENT\">" \
"<Qualifier value=\"1\" name=\"telemetryLevel\"/>" \
"<VariableRef name=\"DownlinkControllerStatus\"/>" \
"<VariableRef name=\"ComponentsRegistered\"/>" \
"<VariableRef name=\"DataMsgsDownlinked\"/>" \
"<VariableRef name=\"DataRequestsReceived\"/>" \
"<VariableRef name=\"DataMsgsInBuffer\"/>" \
"<VariableRef name=\"CommandsAccepted\"/>" \
"<VariableRef name=\"CommandsRejected\"/>" \
"<VariableRef name=\"FilesRequested\"/>" \
"<VariableRef name=\"FilesSuccessfullyDownlinked\"/>" \
"<VariableRef name=\"FilesFailedDownlinked\"/>" \
"</DataMsg>" \
"</Notification>" \
"" \
"</Interface>" \
"" \
"<Interface name=\"ICSDebugInterface\" id=\"3\">" \
"" \
"<!--" \
"Note: DebugLevel is a bit field with the following assigned values:" \
"DEBUG_ENTRY_AND_EXIT   = 0x01," \
"DEBUG_ENTRY_PARAMETERS = 0x02," \
"DEBUG_EXIT_PARAMETERS  = 0x04," \
"DEBUG_LEVEL_LOW        = 0x08," \
"DEBUG_LEVEL_MEDIUM     = 0x10," \
"DEBUG_LEVEL_HIGH       = 0x20." \
"The values are OR'd to determine the debug information to be logged." \
"-->" \
"" \
"<Variable name=\"DebugLevel\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"CurrentDebugLevel\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"SetDebugLevelReceived\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"SetDebugLevelAccepted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"SetDebugLevelSuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"SetDebugLevelFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Command>" \
"<CommandMsg name=\"SetDebugLevel\" id=\"001\" description=\"Set the debug log verbosity level\">" \
"<VariableRef name=\"DebugLevel\"/>" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Command>" \
"<CommandMsg name=\"SendDebugStatus\" id=\"002\"/>" \
"</Command>" \
"" \
"<Notification>" \
"<DataMsg name=\"DebugStatus\" id=\"003\" msgArrival=\"EVENT\">" \
"<Qualifier value=\"1\" name=\"telemetryLevel\"/>" \
"<VariableRef name=\"CurrentDebugLevel\"/>" \
"<VariableRef name=\"SetDebugLevelReceived\"/>" \
"<VariableRef name=\"SetDebugLevelAccepted\"/>" \
"<VariableRef name=\"SetDebugLevelSuccess\"/>" \
"<VariableRef name=\"SetDebugLevelFailure\"/>" \
"</DataMsg>" \
"</Notification>" \
"" \
"</Interface>" \
"" \
"<Interface name=\"ICSTaskControlInterface\" id=\"4\">" \
"" \
"<Command>" \
"<CommandMsg name=\"DestroyTask\" id=\"001\"/>" \
"</Command>" \
"" \
"<!-- Other possible commands include Suspend, Resume, SetPriority, and SetHeartBeatPeriod -->" \
"<!-- Other possible requests include GetPriority, and GetHeartBeatCount -->" \
"" \
"</Interface>" \
"" \
"</xTEDS>" \
""

#endif
