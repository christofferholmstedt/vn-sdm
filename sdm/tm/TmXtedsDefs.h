#ifndef SDM_TM_XTEDS_DEFS_H_
#define SDM_TM_XTEDS_DEFS_H_

#include "../common/message/SDMMessage_ID.h"
#include "../common/message_defs.h"

//
// xTEDS definitions

// Message ids
const SDMMessage_ID NOTI_TM_STATUS(1,1);
const SDMMessage_ID NOTI_TASK_QUEUED(1,2);
const SDMMessage_ID NOTI_TASK_STARTED(1,3);
const SDMMessage_ID NOTI_TASK_FINISHED(1,4);
const SDMMessage_ID CMD_CHANGE_MODE(1,5);
const SDMMessage_ID CMD_START_TASK(1, 8);
const SDMMessage_ID CMD_KILL_TASK(1, 9);
const SDMMessage_ID SER_NAME_TO_PID(1,6);
const SDMMessage_ID SER_NAME_TO_PID_REPLY(1,7);
const SDMMessage_ID SER_GET_TASK_LIST(1, 10);
const SDMMessage_ID SER_TASK_LIST_REPLY(1, 11);
const SDMMessage_ID SER_GET_RUNNING_TASK_LIST(1, 15);
const SDMMessage_ID SER_RUNNING_TASK_LIST_REPLY(1, 16);
const SDMMessage_ID SER_GET_TASK_INFO(1, 12);
const SDMMessage_ID SER_TASK_INFO_REPLY(1, 13);
const SDMMessage_ID NOTI_PERF_COUNTERS(2,13);
const SDMMessage_ID CMD_ENABLE_LOGGING(3,16);
const SDMMessage_ID CMD_DISABLE_LOGGING(3,17);

enum XtedsChangeModeStatusEnum
  {
    MODE_STATUS_SOFT_RESET = 1,
    MODE_STATUS_HARD_RESET = 2
  };
enum XtedsExecutionModeEnum
  {
    EXECUTION_MODE_NORMAL = 1,
    EXECUTION_MODE_ALWAYS_RUNNING = 2
  };
enum XtedsArchitectureTypeEnum
  {
    ARCH_TYPE_INTEL = 1,
    ARCH_TYPE_MICROBLAZE = 2,
	ARCH_TYPE_SPARC = 3
  };
enum XtedsOsTypeEnum
  {
    OS_TYPE_LINUX26 = 1,
    OS_TYPE_WIN32 = 2,
	OS_TYPE_VXWORKS = 3
  };
enum XtedsMemTypeEnum
  {
    MEM_TYPE_64 = 1,
    MEM_TYPE_128 = 2,
    MEM_TYPE_256 = 3,
    MEM_TYPE_512 = 4
  };
enum XtedsTaskStateEnum
  {
    TASK_STATE_QUEUED = 1,
    TASK_STATE_SCHEDULED = 2,
    TASK_STATE_RUNNING = 3,
    TASK_STATE_STOPPED = 4
  };
enum XtedsTaskRetrievelLocation
  {
    TASK_LOCATION_PRIMARY = 1,
    TASK_LOCATION_TEMPORARY = 2,
    TASK_LOCATION_BACKUP = 3
  };

const unsigned int XTEDS_MAX_TASK_NAME_SIZE = MAX_FILENAME_SIZE;

/*xTEDS for the TaskManager*/
#define STR_TASK_MANAGER_XTEDS "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n \
<xTEDS version=\"2.0\" xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\" xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\" name=\"Task_Manager_xTEDS\" xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\">\n \
\t<Application kind=\"Software\" name=\"TaskManager\"/>\n \
\t<Interface name=\"TM_Interface\" id=\"1\">\n \
\t\t<Variable format=\"UINT08\" kind=\"TBD\" name=\"Mode\">\n \
\t\t\t<Drange name=\"TmModeEnum\">\n \
\t\t\t\t<Option value=\"1\" name=\"SoftReset\"/>\n \
\t\t\t\t<Option value=\"2\" name=\"HardReset\"/>\n \
\t\t\t</Drange>\n \
\t\t</Variable>\n \
\t\t<Variable format=\"UINT08\" kind=\"string\" name=\"TaskName\" length=\"128\"/>\n \
\t\t<Variable format=\"INT32\" kind=\"TBD\" name=\"ExitStatus\"/>\n \
\t\t<Variable format=\"UINT32\" kind=\"IP_long\" name=\"SenderAddr\"/>\n \
\t\t<Variable format=\"UINT16\" kind=\" Port_of_Device\" name=\"SenderPort\"/>\n \
\t\t<Variable format=\"UINT32\" kind=\"ID\" name=\"SenderSensorID\"/>\n \
\t\t<Variable format=\"UINT32\" kind=\"ID\" name=\"SDMTaskPID\" invalidValue=\"0\" description=\"The positive SDM process identifier number for a task.\"/>\n \
\t\t<Variable format=\"UINT16\" kind=\"tbd\" name=\"NumTasks\"/>\n \
\t\t<Variable name=\"TaskListBlob\" format=\"UINT08\" length=\"8067\" kind=\"blob\" description=\"A null separated list of UINT32/ASCII text pairs representing the PID and TaskName of tasks in the requested list, respectively, ended with a double null-terminator.\"/>\n \
\t\t<Variable name=\"PmNodeId\" format=\"UINT08\" kind=\"id\"/>\n \
\t\t<Variable name =\"killLevel\" format=\"UINT08\" kind=\"id\" />\n \
\t\t<Variable name=\"ExecutionMode\" format=\"INT08\" kind=\"Mode\" description=\"Task execution mode.\">\n \
\t\t\t<Drange name=\"ExecutionModeEnum\">\n \
\t\t\t\t<Option value=\"1\" name=\"Normal\"/>\n \
\t\t\t\t<Option value=\"2\" name=\"AlwaysRunning\"/>\n \
\t\t\t</Drange>\n \
\t\t</Variable>\n \
\t\t<Variable name=\"ArchitectureType\" format=\"INT08\" kind=\"tbd\">\n \
\t\t\t<Drange name=\"ArchitectureTypeEnum\">\n \
\t\t\t\t<Option name=\"Intel\" value=\"1\"/>\n \
\t\t\t\t<Option name=\"Microblaze\" value=\"2\"/>\n \
\t\t\t</Drange>\n \
\t\t</Variable>\n \
\t\t<Variable name=\"OsType\" format=\"INT08\" kind=\"tbd\">\n \
\t\t\t<Drange name=\"OsTypeEnum\">\n \
\t\t\t\t<Option name=\"Linux26\" value=\"1\"/>\n \
\t\t\t\t<Option name=\"Win32\" value=\"2\"/>\n \
\t\t\t</Drange>\n \
\t\t</Variable>\n \
\t\t<Variable name=\"MemType\" format=\"INT08\" kind=\"tbd\">\n \
\t\t\t<Drange name=\"MemTypeEnum\">\n \
\t\t\t\t<Option name=\"Mem64\" value=\"1\"/>\n \
\t\t\t\t<Option name=\"Mem128\" value=\"2\"/>\n \
\t\t\t\t<Option name=\"Mem256\" value=\"3\"/>\n \
\t\t\t\t<Option name=\"Mem512\" value=\"4\"/>\n \
\t\t\t</Drange>\n \
\t\t</Variable>\n \
\t\t<Variable name=\"TaskState\" format=\"INT08\" kind=\"tbd\">\n \
\t\t\t<Drange name=\"TaskStateEnum\">\n \
\t\t\t\t<Option name=\"Queued\" value=\"1\"/>\n \
\t\t\t\t<Option name=\"Scheduled\" value=\"2\"/>\n \
\t\t\t\t<Option name=\"Running\" value=\"3\"/>\n \
\t\t\t\t<Option name=\"Stopped\" value=\"4\"/>\n \
\t\t\t</Drange>\n \
\t\t</Variable>\n \
\t\t<Variable name=\"TaskRetrievalLocation\" format=\"INT08\" kind=\"tbd\">\n \
\t\t\t<Drange name=\"TaskLoadLocationEnum\">\n \
\t\t\t\t<Option value=\"1\" name=\"PrimaryLocation\"/>\n \
\t\t\t\t<Option value=\"2\" name=\"TemporaryTestLocation\"/>\n \
\t\t\t\t<Option value=\"3\" name=\"BackupLocation\"/>\n \
\t\t\t</Drange>\n \
\t\t</Variable>\n \
\n\t\t<Notification>\n \
\t\t\t<DataMsg name=\"Status\" id=\"1\" msgArrival=\"EVENT\">\n \
\t\t\t\t<VariableRef name=\"Mode\"/>\n \
\t\t\t\t<VariableRef name=\"SenderAddr\"/>\n \
\t\t\t\t<VariableRef name=\"SenderPort\"/>\n \
\t\t\t\t<VariableRef name=\"SenderSensorID\"/>\n \
\t\t\t</DataMsg>\n \
\t\t</Notification>\n \
\t\t<Notification>\n \
\t\t\t<DataMsg name=\"TaskQueued\" id=\"2\" msgArrival=\"EVENT\">\n \
\t\t\t\t<VariableRef name=\"TaskName\"/>\n \
\t\t\t</DataMsg>\n \
\t\t</Notification>\n \
\t\t<Notification>\n \
\t\t\t<DataMsg name=\"TaskStarted\" id=\"3\" msgArrival=\"EVENT\">\n \
\t\t\t\t<VariableRef name=\"TaskName\"/>\n \
\t\t\t\t<VariableRef name=\"SDMTaskPID\"/>\n \
\t\t\t</DataMsg>\n \
\t\t</Notification>\n \
\t\t<Notification>\n \
\t\t\t<DataMsg name=\"TaskFinished\" id=\"4\" msgArrival=\"EVENT\">\n \
\t\t\t\t<VariableRef name=\"TaskName\"/>\n \
\t\t\t\t<VariableRef name=\"SDMTaskPID\"/>\n \
\t\t\t\t<VariableRef name=\"ExitStatus\"/>\n \
\t\t\t</DataMsg>\n \
\t\t</Notification>\n \
\t\t<Request>\n \
\t\t\t<CommandMsg name=\"GetTaskList\" id=\"10\" description=\"Requests entire task list.\"/>\n \
\t\t\t<DataReplyMsg name=\"TaskListReply\" id=\"11\">\n \
\t\t\t\t<VariableRef name=\"NumTasks\"/>\n \
\t\t\t\t<VariableRef name=\"TaskListBlob\"/>\n \
\t\t\t</DataReplyMsg>\n \
\t\t</Request>\n \
\t\t<Request>\n \
\t\t\t<CommandMsg name=\"GetRunningTaskList\" id=\"15\" description=\"Requests a list of running tasks.\"/>\n \
\t\t\t<DataReplyMsg name=\"RunningTaskListReply\" id=\"16\">\n \
\t\t\t\t<VariableRef name=\"NumTasks\"/>\n \
\t\t\t\t<VariableRef name=\"TaskListBlob\"/>\n \
\t\t\t</DataReplyMsg>\n \
\t\t</Request>\n \
\t\t<Request>\n \
\t\t\t<CommandMsg name=\"GetTaskInfo\" id=\"12\">\n \
\t\t\t\t<VariableRef name=\"SDMTaskPID\"/>\n \
\t\t\t</CommandMsg>\n \
\t\t\t<DataReplyMsg name=\"TaskInfoReply\" id=\"13\">\n \
\t\t\t\t<VariableRef name=\"SDMTaskPID\"/>\n \
\t\t\t\t<VariableRef name=\"TaskName\"/>\n \
\t\t\t\t<VariableRef name=\"ArchitectureType\"/>\n \
\t\t\t\t<VariableRef name=\"OsType\"/>\n \
\t\t\t\t<VariableRef name=\"MemType\"/>\n \
\t\t\t\t<VariableRef name=\"PmNodeId\"/>\n \
\t\t\t\t<VariableRef name=\"TaskState\"/>\n \
\t\t\t\t<VariableRef name=\"ExecutionMode\"/>\n \
\t\t\t</DataReplyMsg>\n \
\t\t</Request>\n \
\t\t<Request>\n \
\t\t\t<CommandMsg name=\"NameToPID\" id=\"6\">\n \
\t\t\t\t<VariableRef name=\"TaskName\"/>\n \
\t\t\t</CommandMsg>\n \
\t\t\t<DataReplyMsg name=\"TaskPID\" id=\"7\">\n \
\t\t\t\t<VariableRef name=\"TaskName\"/>\n \
\t\t\t\t<VariableRef name=\"SDMTaskPID\"/>\n \
\t\t\t</DataReplyMsg>\n \
\t\t</Request>\n \
\t\t<Command>\n \
\t\t\t<CommandMsg name=\"ChangeMode\" id=\"5\">\n \
\t\t\t\t<VariableRef name=\"Mode\"/>\n \
\t\t\t\t<VariableRef name=\"SenderAddr\"/>\n \
\t\t\t\t<VariableRef name=\"SenderPort\"/>\n \
\t\t\t\t<VariableRef name=\"SenderSensorID\"/>\n \
\t\t\t</CommandMsg>\n \
\t\t</Command>\n \
\t\t<Command>\n \
\t\t\t<CommandMsg name=\"StartTask\" id=\"8\">\n \
\t\t\t\t<VariableRef name=\"TaskName\"/>\n \
\t\t\t\t<VariableRef name=\"ArchitectureType\"/>\n \
\t\t\t\t<VariableRef name=\"OsType\"/>\n \
\t\t\t\t<VariableRef name=\"MemType\"/>\n \
\t\t\t\t<VariableRef name=\"ExecutionMode\"/>\n \
\t\t\t\t<VariableRef name=\"PmNodeId\"/>\n \
\t\t\t\t<VariableRef name=\"TaskRetrievalLocation\"/>\n \
\t\t\t</CommandMsg>\n \
\t\t</Command>\n \
\t\t<Command>\n \
\t\t\t<CommandMsg name=\"KillTask\" id=\"9\">\n \
\t\t\t\t<VariableRef name=\"SDMTaskPID\"/>\n \
\t\t\t\t<VariableRef name=\"killLevel\"/> \
\t\t\t</CommandMsg>\n \
\t\t</Command>\n \
\t</Interface>\n \
\t<Interface name=\"Msg_Count\" id=\"2\">\n \
\t\t<Variable name=\"Total_Messages_Recd\" kind=\"Total\" format=\"UINT32\"/>\n \
\t\t<Variable name=\"Messages_Last_Second_Recd\" kind=\"Total\" format=\"UINT32\"/>\n \
\t\t<Variable name=\"Total_Messages_Sent\" kind=\"Total\" format=\"UINT32\"/>\n \
\t\t<Variable name=\"Messages_Last_Second_Sent\" kind=\"Total\" format=\"UINT32\"/>\n \
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
</xTEDS>"

#endif // #ifndef SDM_TM_XTEDS_DEFS_H_
