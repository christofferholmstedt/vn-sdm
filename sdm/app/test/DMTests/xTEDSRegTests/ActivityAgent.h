#ifndef _ACTIVITYAGENT_XTEDS_H
#define _ACTIVITYAGENT_XTEDS_H

#define _STRING_ACTIVITYAGENT_XTEDS \
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>" \
"<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
"xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"ActivityAgentXTEDS\" description=\"ActivityAgent xTEDS\" version=\"2.4\">" \
"" \
"<Application name=\"ActivityAgent\" kind=\"AutonomyFlightSoftware\" description=\"Autonomous Tasking Executive (ATE), ActivityAgent\"/>" \
"" \
"<!-- Note: An ActivityAgent must implement the ActivityInterface and should implement the ActivityAgentStatusInterface. -->" \
"" \
"<Interface name=\"ActivityInterface\" id=\"1\"><!-- This is a template for an ActivityAgent Interface. Unique activity parameters must be added as necessary. -->" \
"" \
"<Variable name=\"ActivityName\" kind=\"String\" format=\"INT08\" length=\"33\"/><!-- 33-byte, null terminated string -->" \
"<Variable name=\"ActivityId\" kind=\"ID\" format=\"UINT32\"/>" \
"<Variable name=\"ActivityStatus\" kind=\"Status\" format=\"INT16\">" \
"<Drange name=\"ActivityStatusEnum\">" \
"<Option value=\"0\" name=\"SCHEDULE_FAILURE\"/><!-- The activity could not be scheduled as requested -->" \
"<Option value=\"1\" name=\"WAITING\"/><!-- The activity has been inserted into the schedule -->" \
"<Option value=\"2\" name=\"ENABLED\"/><!-- The activity has been sent a command to execute -->" \
"<Option value=\"3\" name=\"TERMINATED\"/><!-- The activity has been sent a command to abort -->" \
"<Option value=\"4\" name=\"EXECUTING\"/><!-- The activity is currently executing -->" \
"<Option value=\"5\" name=\"DONE_FAILURE\"/><!-- The activity has completed abnormally -->" \
"<Option value=\"6\" name=\"DONE_SUCCESS\"/><!-- The activity has completed normally -->" \
"<Option value=\"7\" name=\"DONE_NOT_EXECUTED\"/><!-- The activity has terminated without executing -->" \
"</Drange>" \
"</Variable>" \
"" \
"<!-- Add Variables for the unique activity parameters -->" \
"" \
"<Command> <!-- Provides the capability to request an Activity from the ground -->" \
"<CommandMsg name=\"RequestActivityCmd\" id=\"001\" description=\"Determine activity state variables and request to be scheduled\">" \
"<VariableRef name=\"ActivityId\"/><!-- Use 0 for on-board requests. The ActivityId will then be assigned by the ActivityManager -->" \
"" \
"<!-- Add VariableRefs for the unique activity parameters -->" \
"" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Request>" \
"<CommandMsg name=\"RequestActivity\" id=\"002\" description=\"Determine activity state variables and request to be scheduled\">" \
"<VariableRef name=\"ActivityId\"/><!-- Use 0 for on-board requests. The ActivityId will then be assigned by the ActivityManager -->" \
"" \
"<!-- Add VariableRefs for the unique activity parameters -->" \
"" \
"</CommandMsg>" \
"<DataReplyMsg name=\"RequestActivityReply\" id=\"003\">" \
"<VariableRef name=\"ActivityId\"/>" \
"<VariableRef name=\"ActivityStatus\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"" \
"<Command> <!-- Provides the capability to update an Activity from the ground -->" \
"<CommandMsg name=\"UpdateRequestCmd\" id=\"004\" description=\"Update activity state variables and request a schedule update if necessary\">" \
"<VariableRef name=\"ActivityId\"/>" \
"" \
"<!-- Add VariableRefs for the unique activity parameters -->" \
"" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Request>" \
"<CommandMsg name=\"UpdateRequest\" id=\"005\" description=\"Update activity state variables and request a schedule update if necessary\">" \
"<VariableRef name=\"ActivityId\"/>" \
"" \
"<!-- Add VariableRefs for the unique activity parameters -->" \
"" \
"</CommandMsg>" \
"<DataReplyMsg name=\"UpdateRequestReply\" id=\"006\">" \
"<VariableRef name=\"ActivityId\"/>" \
"<VariableRef name=\"ActivityStatus\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"" \
"<Command>" \
"<CommandMsg name=\"Reschedule\" id=\"007\" description=\"The activity has been removed from the schedule and needs to be rescheduled\">" \
"<VariableRef name=\"ActivityId\"/>" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Command>" \
"<CommandMsg name=\"Delete\" id=\"008\" description=\"Delete the activity\">" \
"<VariableRef name=\"ActivityId\"/>" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Command>" \
"<CommandMsg name=\"Execute\" id=\"009\" description=\"Execute the activity\">" \
"<VariableRef name=\"ActivityId\"/>" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Command>" \
"<CommandMsg name=\"Abort\" id=\"010\" description=\"Abort execution of the activity\">" \
"<VariableRef name=\"ActivityId\"/>" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Command>" \
"<CommandMsg name=\"SendActivityStatusMsg\" id=\"011\" description=\"Send the ActivityStatusMsg DataMsg\">" \
"<VariableRef name=\"ActivityId\"/>" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Notification>" \
"<DataMsg name=\"ActivityStatusMsg\" id=\"012\" msgArrival=\"EVENT\">" \
"<Qualifier value=\"1\" name=\"telemetryLevel\"/>" \
"<VariableRef name=\"ActivityId\"/>" \
"<VariableRef name=\"ActivityName\"/>" \
"<VariableRef name=\"ActivityStatus\"/>" \
"</DataMsg>" \
"</Notification>" \
"" \
"</Interface>" \
"" \
"<Interface name=\"ActivityAgentStatusInterface\" id=\"2\">" \
"" \
"<Variable name=\"ActivityAgentStatus\" kind=\"Status\" format=\"INT16\">" \
"<Drange name=\"ActivityAgentStatusEnum\">" \
"<Option value=\"0\" name=\"NOT_INITIALIZED\"/><!-- The ActivityAgent has not been successfully initialized -->" \
"<Option value=\"1\" name=\"INITIALIZING\"/><!-- The ActivityAgent is in the process of initializing -->" \
"<Option value=\"2\" name=\"RUNNING\"/><!-- The ActivityAgent is initialized and is running -->" \
"<Option value=\"3\" name=\"TERMINATING\"/><!-- The ActivityAgent is shutting down -->" \
"</Drange>" \
"</Variable>" \
"" \
"<Variable name=\"ActivityAgentName\" kind=\"tbd\" format=\"UINT08\" length=\"33\"/><!-- 33-byte, null terminated string -->" \
"" \
"<Variable name=\"ActivitiesCurrentlyScheduled\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"ActivitiesExecuted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ActivitiesExecutedSuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ActivitiesExecutedFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ActivitiesDeleted\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"RequestActivityReceived\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"RequestActivityAccepted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"RequestActivitySuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"RequestActivityFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"UpdateRequestReceived\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"UpdateRequestAccepted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"UpdateRequestSuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"UpdateRequestFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"ExecuteReceived\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ExecuteAccepted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ExecuteSuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ExecuteFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"RescheduleReceived\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"RescheduleAccepted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"RescheduleSuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"RescheduleFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"DeleteReceived\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"DeleteAccepted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"DeleteSuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"DeleteFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Command>" \
"<CommandMsg name=\"SendActivityAgentStatusMsg\" id=\"001\" description=\"Send the ActivityAgentStatusMsg DataMsg\"/>" \
"</Command>" \
"" \
"<Notification>" \
"<DataMsg name=\"ActivityAgentStatusMsg\" id=\"002\" msgArrival=\"EVENT\">" \
"<Qualifier value=\"1\" name=\"telemetryLevel\"/>" \
"<VariableRef name=\"ActivityAgentStatus\"/>" \
"<VariableRef name=\"ActivityAgentName\"/>" \
"<VariableRef name=\"ActivitiesCurrentlyScheduled\"/>" \
"<VariableRef name=\"ActivitiesExecuted\"/>" \
"<VariableRef name=\"ActivitiesExecutedSuccess\"/>" \
"<VariableRef name=\"ActivitiesExecutedFailure\"/>" \
"<VariableRef name=\"ActivitiesDeleted\"/>" \
"<VariableRef name=\"RequestActivityReceived\"/>" \
"<VariableRef name=\"RequestActivityAccepted\"/>" \
"<VariableRef name=\"RequestActivitySuccess\"/>" \
"<VariableRef name=\"RequestActivityFailure\"/>" \
"<VariableRef name=\"UpdateRequestReceived\"/>" \
"<VariableRef name=\"UpdateRequestAccepted\"/>" \
"<VariableRef name=\"UpdateRequestSuccess\"/>" \
"<VariableRef name=\"UpdateRequestFailure\"/>" \
"<VariableRef name=\"ExecuteReceived\"/>" \
"<VariableRef name=\"ExecuteAccepted\"/>" \
"<VariableRef name=\"ExecuteSuccess\"/>" \
"<VariableRef name=\"ExecuteFailure\"/>" \
"<VariableRef name=\"RescheduleReceived\"/>" \
"<VariableRef name=\"RescheduleAccepted\"/>" \
"<VariableRef name=\"RescheduleSuccess\"/>" \
"<VariableRef name=\"RescheduleFailure\"/>" \
"<VariableRef name=\"DeleteReceived\"/>" \
"<VariableRef name=\"DeleteAccepted\"/>" \
"<VariableRef name=\"DeleteSuccess\"/>" \
"<VariableRef name=\"DeleteFailure\"/>" \
"</DataMsg>" \
"</Notification>" \
"" \
"</Interface>" \
"" \
"<Interface name=\"ATEDebugInterface\" id=\"3\">" \
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
"<Interface name=\"TaskControlInterface\" id=\"4\">" \
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
