#ifndef _ACTIVITYMANAGER_XTEDS_H
#define _ACTIVITYMANAGER_XTEDS_H

#define _STRING_ACTIVITYMANAGER_XTEDS \
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>" \
"<xTEDS xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
"xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\" name=\"ActivityManagerXTEDS\" description=\"ActivityManager xTEDS\" version=\"3.1\">" \
"" \
"<Application name=\"ActivityManager\" kind=\"AutonomyFlightSoftware\" description=\"Autonomous Tasking Executive (ATE), ActivityManager\"/>" \
"" \
"<Interface name=\"ActivityManagerInterface\" id=\"1\" description=\"Basic interface for scheduling activities and updating their status\">" \
"" \
"<Variable name=\"ActivityId\" kind=\"ID\" format=\"UINT32\"/>" \
"<Variable name=\"ActivityName\" kind=\"String\" format=\"INT08\" length=\"33\"/><!-- 33-byte, null terminated string -->" \
"<Variable name=\"ActivityPriority\" kind=\"tbd\" format=\"UINT08\" rangeMin=\"0\" rangeMax=\"255\"/><!-- 0 is the lowest priority and 255 is the highest -->" \
"<Variable name=\"ActivityBeginTime\" kind=\"Time\" format=\"FLOAT64\" units=\"s\"/>" \
"<Variable name=\"ActivityDuration\" kind=\"Time\" format=\"FLOAT64\" units=\"s\"/>" \
"<Variable name=\"ActivityNotBeforeTime\" kind=\"Time\" format=\"FLOAT64\" units=\"s\"/><!-- Earliest begin time. 0.0 signifies now -->" \
"<Variable name=\"ActivityNotAfterTime\" kind=\"Time\" format=\"FLOAT64\" units=\"s\"/><!-- Latest begin time. 0.0 signifies no limit -->" \
"<Variable name=\"AllowConcurrentActivity\" kind=\"boolean\" format=\"UINT08\">" \
"<Drange name=\"AllowConcurrentActivityEnum\">" \
"<Option value=\"0\" name=\"NO\"/>" \
"<Option value=\"1\" name=\"YES\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"ActivityStatus\" kind=\"Status\" format=\"INT16\">" \
"<Drange name=\"ActivityStatusEnum\">" \
"<Option value=\"0\" name=\"SCHEDULE_FAILURE\"/><!-- The activity could not be scheduled as requested -->" \
"<Option value=\"1\" name=\"WAITING\"/><!-- The activity has been inserted into the schedule -->" \
"<Option value=\"2\" name=\"ENABLED\"/><!-- The activity has been sent a command to execute -->" \
"<Option value=\"3\" name=\"TERMINATED\"/><!-- The activity has been sent a command to abort -->" \
"<Option value=\"4\" name=\"EXECUTING\"/><!-- The activity has indicated that it is currently executing -->" \
"<Option value=\"5\" name=\"DONE_FAILURE\"/><!-- The activity has indicated that it completed abnormally -->" \
"<Option value=\"6\" name=\"DONE_SUCCESS\"/><!-- The activity has indicated that it completed normally -->" \
"<Option value=\"7\" name=\"DONE_NOT_EXECUTED\"/><!-- The activity has indicated that it terminated without executing -->" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"ExecutionStatus\" kind=\"Status\" format=\"INT16\" defaultValue=\"4\">" \
"<Drange name=\"ExecutionStatusEnum\">" \
"<Option value=\"4\" name=\"EXECUTING\"/><!-- The activity is currently executing -->" \
"<Option value=\"5\" name=\"DONE_FAILURE\"/><!-- The activity has completed abnormally -->" \
"<Option value=\"6\" name=\"DONE_SUCCESS\"/><!-- The activity has completed normally -->" \
"<Option value=\"7\" name=\"DONE_NOT_EXECUTED\"/><!-- The activity has terminated without executing -->" \
"</Drange>" \
"</Variable>" \
"" \
"<!-- Variables for resources required are tbd -->" \
"" \
"<Request>" \
"<CommandMsg name=\"ScheduleActivity\" id=\"001\" description=\"Schedule a mission or housekeeping activity\">" \
"<VariableRef name=\"ActivityId\"/>" \
"<VariableRef name=\"ActivityName\"/>" \
"<VariableRef name=\"ActivityPriority\"/>" \
"<VariableRef name=\"ActivityDuration\"/>" \
"<VariableRef name=\"AllowConcurrentActivity\"/>" \
"<VariableRef name=\"ActivityNotBeforeTime\"/>" \
"<VariableRef name=\"ActivityNotAfterTime\"/>" \
"" \
"<!-- VariableRefs for resources are tbd -->" \
"" \
"</CommandMsg>" \
"<DataReplyMsg name=\"ScheduleActivityReply\" id=\"002\">" \
"<VariableRef name=\"ActivityId\"/>" \
"<VariableRef name=\"ActivityStatus\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"" \
"<Request>" \
"<CommandMsg name=\"UpdateActivity\" id=\"003\" description=\"Adjust the properties of a scheduled mission or housekeeping activity\">" \
"<VariableRef name=\"ActivityId\"/>" \
"<VariableRef name=\"ActivityPriority\"/>" \
"<VariableRef name=\"ActivityDuration\"/>" \
"<VariableRef name=\"AllowConcurrentActivity\"/>" \
"<VariableRef name=\"ActivityNotBeforeTime\"/>" \
"<VariableRef name=\"ActivityNotAfterTime\"/>" \
"" \
"<!-- VariableRefs for resources are tbd -->" \
"" \
"</CommandMsg>" \
"<DataReplyMsg name=\"UpdateActivityReply\" id=\"004\">" \
"<VariableRef name=\"ActivityId\"/>" \
"<VariableRef name=\"ActivityStatus\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"" \
"<Command>" \
"<CommandMsg name=\"UpdateActivityStatus\" id=\"005\" description=\"Update activity execution status\">" \
"<VariableRef name=\"ActivityId\"/>" \
"<VariableRef name=\"ExecutionStatus\"/>" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Command>" \
"<CommandMsg name=\"DeleteActivity\" id=\"006\" description=\"Delete a scheduled activity\">" \
"<VariableRef name=\"ActivityId\"/>" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Command>" \
"<CommandMsg name=\"SendActivityStatusMsg\" id=\"007\" description=\"Send the ActivityStatusMsg DataMsg\">" \
"<VariableRef name=\"ActivityId\"/>" \
"</CommandMsg>" \
"</Command>" \
"" \
"<Notification>" \
"<DataMsg name=\"ActivityStatusMsg\" id=\"008\" msgArrival=\"EVENT\">" \
"<Qualifier value=\"1\" name=\"telemetryLevel\"/>" \
"<VariableRef name=\"ActivityId\"/>" \
"<VariableRef name=\"ActivityName\"/>" \
"<VariableRef name=\"ActivityPriority\"/>" \
"<VariableRef name=\"ActivityBeginTime\"/>" \
"<VariableRef name=\"ActivityDuration\"/>" \
"<VariableRef name=\"AllowConcurrentActivity\"/>" \
"<VariableRef name=\"ActivityNotBeforeTime\"/>" \
"<VariableRef name=\"ActivityNotAfterTime\"/>" \
"<VariableRef name=\"ActivityStatus\"/>" \
"</DataMsg>" \
"</Notification>" \
"" \
"</Interface>" \
"" \
"<Interface name=\"ActivityManagerScheduleInterface\" id=\"2\" description=\"Additional messages for schedule maintenance\" >" \
"" \
"<Command>" \
"<CommandMsg name=\"DeleteAllActivities\" id=\"001\" description=\"Delete all scheduled activities\"/>" \
"</Command>" \
"" \
"<!-- Command -->" \
"<!-- CommandMsg name=\"PrepareScheduleFile\" id=\"002\" description=\"Prepare an activities schedule for downlink\" -->" \
"<!-- /Command -->" \
"" \
"</Interface>" \
"" \
"<Interface id=\"3\" name=\"ActivityManagerStatusInterface\">" \
"" \
"<Variable name=\"ActivityManagerStatus\" kind=\"Status\" format=\"INT16\">" \
"<Drange name=\"ActivityManagerStatusEnum\">" \
"<Option value=\"0\" name=\"NOT_INITIALIZED\"/><!-- The ActivityManager has not been successfully initialized -->" \
"<Option value=\"1\" name=\"INITIALIZING\"/><!-- The ActivityManager is in the process of initializing -->" \
"<Option value=\"2\" name=\"RUNNING\"/><!-- The ActivityManager is initialized and is running -->" \
"<Option value=\"3\" name=\"TERMINATING\"/><!-- The ActivityManager is shutting down -->" \
"</Drange>" \
"</Variable>" \
"" \
"<Variable name=\"ActivitiesCurrentlyScheduled\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ActivitiesExecuted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ActivitiesExecutedSuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ActivitiesExecutedFailed\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ActivitiesDeleted\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"ScheduleActivityReceived\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ScheduleActivityAccepted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ScheduleActivitySuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"ScheduleActivityFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"UpdateActivityReceived\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"UpdateActivityAccepted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"UpdateActivitySuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"UpdateActivityFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"UpdateActivityStatusReceived\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"UpdateActivityStatusAccepted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"UpdateActivityStatusSuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"UpdateActivityStatusFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"DeleteActivityReceived\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"DeleteActivityAccepted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"DeleteActivitySuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"DeleteActivityFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<Variable name=\"DeleteAllActivitiesReceived\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"DeleteAllActivitiesAccepted\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"DeleteAllActivitiesSuccess\" kind=\"tbd\" format=\"UINT16\"/>" \
"<Variable name=\"DeleteAllActivitiesFailure\" kind=\"tbd\" format=\"UINT16\"/>" \
"" \
"<!-- Variable name=\"PrepSchedFileReceived\" kind=\"tbd\" format=\"UINT16\"/ -->" \
"<!-- Variable name=\"PrepSchedFileAccepted\" kind=\"tbd\" format=\"UINT16\"/ -->" \
"<!-- Variable name=\"PrepSchedFileSuccess\" kind=\"tbd\" format=\"UINT16\"/ -->" \
"<!-- Variable name=\"PrepSchedFileFailure\" kind=\"tbd\" format=\"UINT16\"/ -->" \
"" \
"<Command>" \
"<CommandMsg name=\"SendActivityManagerStatusMsg\" id=\"001\" description=\"Send the ActivityManagerStatusMsg DataMsg\"/>" \
"</Command>" \
"" \
"<Notification>" \
"<DataMsg name=\"ActivityManagerStatusMsg\" id=\"002\" msgArrival=\"EVENT\">" \
"<Qualifier value=\"1\" name=\"telemetryLevel\"/>" \
"<VariableRef name=\"ActivityManagerStatus\"/>" \
"<VariableRef name=\"ActivitiesCurrentlyScheduled\"/>" \
"<VariableRef name=\"ActivitiesExecuted\"/>" \
"<VariableRef name=\"ActivitiesExecutedSuccess\"/>" \
"<VariableRef name=\"ActivitiesExecutedFailed\"/>" \
"<VariableRef name=\"ActivitiesDeleted\"/>" \
"<VariableRef name=\"ScheduleActivityReceived\"/>" \
"<VariableRef name=\"ScheduleActivityAccepted\"/>" \
"<VariableRef name=\"ScheduleActivitySuccess\"/>" \
"<VariableRef name=\"ScheduleActivityFailure\"/>" \
"<VariableRef name=\"UpdateActivityReceived\"/>" \
"<VariableRef name=\"UpdateActivitySuccess\"/>" \
"<VariableRef name=\"UpdateActivityFailure\"/>" \
"<VariableRef name=\"UpdateActivityStatusReceived\"/>" \
"<VariableRef name=\"UpdateActivityStatusAccepted\"/>" \
"<VariableRef name=\"UpdateActivityStatusSuccess\"/>" \
"<VariableRef name=\"UpdateActivityStatusFailure\"/>" \
"<VariableRef name=\"DeleteActivityReceived\"/>" \
"<VariableRef name=\"DeleteActivityAccepted\"/>" \
"<VariableRef name=\"DeleteActivitySuccess\"/>" \
"<VariableRef name=\"DeleteActivityFailure\"/>" \
"<VariableRef name=\"DeleteAllActivitiesReceived\"/>" \
"<VariableRef name=\"DeleteAllActivitiesAccepted\"/>" \
"<VariableRef name=\"DeleteAllActivitiesSuccess\"/>" \
"<VariableRef name=\"DeleteAllActivitiesFailure\"/>" \
"<!-- VariableRef name=\"PrepSchedFileReceived\"/ -->" \
"<!-- VariableRef name=\"PrepSchedFileAccepted\"/ -->" \
"<!-- VariableRef name=\"PrepSchedFileSuccess\"/ -->" \
"<!-- VariableRef name=\"PrepSchedFileFailure\"/ -->" \
"</DataMsg>" \
"</Notification>" \
"" \
"</Interface>" \
"" \
"<Interface name=\"ICSDebugInterface\" id=\"4\">" \
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
"<Interface name=\"ICSTaskControlInterface\" id=\"5\">" \
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
