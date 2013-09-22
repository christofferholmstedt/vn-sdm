#ifndef _INTELLIGENTDATASTORE_XTEDS_H
#define _INTELLIGENTDATASTORE_XTEDS_H

#define _STRING_INTELLIGENTDATASTORE_XTEDS \
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>" \
"<xTEDS name=\"IDSxTEDS\"" \
"xmlns=\"http://www.interfacecontrol.com/SPA/xTEDS\"" \
"xmlns:xsi=\"http://www.w3.org/2001/XMLSchema-instance\"" \
"xsi:schemaLocation=\"http://www.interfacecontrol.com/SPA/xTEDS ../Schema/xTEDS02.xsd\"" \
"version=\"2.0\">" \
"" \
"<Application name=\"IntelligentDataStore\" kind=\"Software\">" \
"<Qualifier name=\"author\" value=\"Ken_Center\"/>" \
"<Qualifier name=\"company\" value=\"Design_Net_Engineering\"/>" \
"</Application>" \
"" \
"<Interface name=\"FileAccessInterface\" id=\"1\">" \
"<Variable name=\"FileHandle\" format=\"UINT16\" kind=\"Handle\" description=\"This field is used to identify file requests.\"/>" \
"<Variable name=\"PathName\" format=\"INT08\" kind=\"PathName_String\" length=\"80\" description=\"This field is the null-terminated path to the file.\"/>" \
"<Variable name=\"FileName\" format=\"INT08\" kind=\"FileName_String\" length=\"80\" description=\"This field is the null-terminated filename of the request.\"/>" \
"<Variable name=\"FileBuffer\" format=\"UINT08\" kind=\"File_Section\" length=\"8047\" description=\"This field is the buffer containing the portion of the file requested.\"/>" \
"<Variable name=\"StatusCode\" format=\"UINT08\" kind=\"Status_Code\" description=\"This field is a status corresponding to a fault.\">" \
"<Drange name=\"StatusCodeTypes\">" \
"<Option name=\"OperationOK\" value=\"1\"/>" \
"<Option name=\"InvalidHandle\" value=\"2\"/>" \
"<Option name=\"FileNotAvailable\" value=\"3\"/>" \
"<Option name=\"InvalidOffset\" value=\"4\"/>" \
"<Option name=\"CouldNotObtainHandle\" value=\"5\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"FileFlag\" format=\"UINT08\" kind=\"Flag\" description=\"This field represents the type of handle to obtain.\">" \
"<Drange name=\"FlagTypes\">" \
"<Option name=\"ReadOnly\" value=\"1\"/>" \
"<Option name=\"WriteOnly\" value=\"2\"/>" \
"<Option name=\"ReadWrite\" value=\"3\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"ByteOffset\" format=\"UINT32\" kind=\"Offset\" description=\"This field is the byte offset for reading and writing to files.\"/>" \
"<Variable name=\"Length\" format=\"UINT32\" kind=\"Length\" description=\"This field is the number of bytes to read/write from the offset.\"/>" \
"<Request>" \
"<CommandMsg name=\"OpenFileHandle\" id=\"1\">" \
"<VariableRef name=\"PathName\"/>" \
"<VariableRef name=\"FileName\"/>" \
"<VariableRef name=\"FileFlag\"/>" \
"</CommandMsg>" \
"<DataReplyMsg name=\"OpenHandleReply\" id=\"2\">" \
"<VariableRef name=\"PathName\"/>" \
"<VariableRef name=\"FileName\"/>" \
"<VariableRef name=\"StatusCode\"/>" \
"<VariableRef name=\"FileHandle\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Command>" \
"<CommandMsg name=\"CloseFileHandle\" id=\"3\">" \
"<VariableRef name=\"FileHandle\"/>" \
"</CommandMsg>" \
"<FaultMsg name=\"CloseFileHandleError\" id=\"4\">" \
"<VariableRef name=\"FileHandle\"/>" \
"<VariableRef name=\"StatusCode\"/>" \
"</FaultMsg>" \
"</Command>" \
"<Request>" \
"<CommandMsg name=\"ReadPortion\" id=\"5\">" \
"<VariableRef name=\"FileHandle\"/>" \
"<VariableRef name=\"ByteOffset\"/>" \
"<VariableRef name=\"Length\"/>" \
"</CommandMsg>" \
"<DataReplyMsg name=\"ReadReply\" id=\"6\">" \
"<VariableRef name=\"FileHandle\"/>" \
"<VariableRef name=\"StatusCode\"/>" \
"<VariableRef name=\"Length\"/>" \
"<VariableRef name=\"FileBuffer\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"WritePortion\" id=\"7\">" \
"<VariableRef name=\"FileHandle\"/>" \
"<VariableRef name=\"ByteOffset\"/>" \
"<VariableRef name=\"Length\"/>" \
"<VariableRef name=\"FileBuffer\"/>" \
"</CommandMsg>" \
"<DataReplyMsg name=\"WriteReply\" id=\"8\">" \
"<VariableRef name=\"FileHandle\"/>" \
"<VariableRef name=\"StatusCode\"/>" \
"<VariableRef name=\"Length\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"</Interface>" \
"" \
"<Interface name=\"FileManagementInterface\" id=\"2\">" \
"<Variable name=\"FileListTextBuffer\" format=\"UINT08\" length=\"8047\" kind=\"Text_Buffer\" description=\"Text buffer containing File Listing\" />" \
"<Variable name=\"FileName\" format=\"INT08\" length=\"80\" kind=\"FileName_String\" description=\"Name of File\" />" \
"<Variable name=\"PathName\" format=\"INT08\" length=\"80\" kind=\"PathName_String\" description=\"File Path Text\" />" \
"<Variable name=\"FromFileName\" format=\"INT08\" length=\"80\" kind=\"FileName_String\" description=\"Name of Originating File\" />" \
"<Variable name=\"FromPathName\" format=\"INT08\" length=\"80\" kind=\"PathName_String\" description=\"Originating File Path Text\" />" \
"<Variable name=\"ToFileName\" format=\"INT08\" length=\"80\" kind=\"FileName_String\" description=\"Name of Destination File\" />" \
"<Variable name=\"ToPathName\" format=\"INT08\" length=\"80\" kind=\"PathName_String\" description=\"Destination File Path Text\" />" \
"<Variable name=\"FileSize\" format=\"UINT32\" kind=\"File_Size_Bytes\" description=\"Size of File in Bytes\" />" \
"<Variable name=\"FileOwner\" format=\"UINT08\" length=\"16\" kind=\"File_Owner\" description=\"File owner text string\" />" \
"<Variable name=\"FileLocked\" format=\"UINT08\" kind=\"File_Lock_State\" description=\"Indicates whether file is in use - 1 is available, 2 is locked\" />" \
"<Variable name=\"FilePermissions\" format=\"UINT08\" length=\"16\" kind=\"File_Permissions\" description=\"File permissions text string\" />" \
"<Variable name=\"StatusCode\" format=\"UINT08\" kind=\"Status_Code\" description=\"Fail code for file management actions\">" \
"<Drange name=\"StatusCodeTypes\">" \
"<Option name=\"OperationOK\" value=\"1\"/>" \
"<Option name=\"InvalidPath\" value=\"2\"/>" \
"<Option name=\"InvalidFile\" value=\"3\"/>" \
"<Option name=\"PathExists\" value=\"4\"/>" \
"<Option name=\"FileExists\" value=\"5\"/>" \
"<Option name=\"InvalidPathAndFile\" value=\"6\"/>" \
"<Option name=\"InsufficientMemory\" value=\"7\"/>" \
"<Option name=\"PathNotEmpty\" value=\"8\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"FileListCode\" format=\"UINT08\" kind=\"File_List_Code\" description=\"Type of File Listing - brief or complete\">" \
"<Drange name=\"FileListCodeTypes\">" \
"<Option name=\"Brief\" value=\"1\"/>" \
"<Option name=\"Complete\" value=\"2\"/>" \
"</Drange>" \
"</Variable>" \
"" \
"<Request>" \
"<CommandMsg name=\"FileList\" id=\"1\">" \
"<VariableRef name=\"PathName\"/>" \
"<VariableRef name=\"FileListCode\"/>" \
"</CommandMsg>" \
"<DataReplyMsg name=\"FileListReply\" id=\"2\">" \
"<VariableRef name=\"PathName\"/>" \
"<VariableRef name=\"StatusCode\"/>" \
"<VariableRef name=\"FileListTextBuffer\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"FileInfo\" id=\"3\">" \
"<VariableRef name=\"PathName\"/>" \
"<VariableRef name=\"FileName\"/>" \
"</CommandMsg>" \
"<DataReplyMsg name=\"FileInfoReply\" id=\"4\">" \
"<VariableRef name=\"PathName\"/>" \
"<VariableRef name=\"FileName\"/>" \
"<VariableRef name=\"StatusCode\"/>" \
"<VariableRef name=\"FileSize\"/>" \
"<VariableRef name=\"FileOwner\"/>" \
"<VariableRef name=\"FileLocked\"/>" \
"<VariableRef name=\"FilePermissions\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"FileCopy\" id=\"5\">" \
"<VariableRef name=\"FromPathName\"/>" \
"<VariableRef name=\"FromFileName\"/>" \
"<VariableRef name=\"ToPathName\"/>" \
"<VariableRef name=\"ToFileName\"/>" \
"</CommandMsg>" \
"<DataReplyMsg name=\"FileCopyReply\" id=\"6\">" \
"<VariableRef name=\"FromPathName\"/>" \
"<VariableRef name=\"FromFileName\"/>" \
"<VariableRef name=\"ToPathName\"/>" \
"<VariableRef name=\"ToFileName\"/>" \
"<VariableRef name=\"StatusCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"FileMove\" id=\"7\">" \
"<VariableRef name=\"FromPathName\"/>" \
"<VariableRef name=\"FromFileName\"/>" \
"<VariableRef name=\"ToPathName\"/>" \
"<VariableRef name=\"ToFileName\"/>" \
"</CommandMsg>" \
"<DataReplyMsg name=\"FileMoveReply\" id=\"8\">" \
"<VariableRef name=\"FromPathName\"/>" \
"<VariableRef name=\"FromFileName\"/>" \
"<VariableRef name=\"ToPathName\"/>" \
"<VariableRef name=\"ToFileName\"/>" \
"<VariableRef name=\"StatusCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"FileDelete\" id=\"9\">" \
"<VariableRef name=\"PathName\"/>" \
"<VariableRef name=\"FileName\"/>" \
"</CommandMsg>" \
"<DataReplyMsg name=\"FileDeleteReply\" id=\"10\">" \
"<VariableRef name=\"PathName\"/>" \
"<VariableRef name=\"FileName\"/>" \
"<VariableRef name=\"StatusCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"PathCreate\" id=\"11\">" \
"<VariableRef name=\"PathName\"/>" \
"</CommandMsg>" \
"<DataReplyMsg name=\"PathCreateReply\" id=\"12\">" \
"<VariableRef name=\"PathName\"/>" \
"<VariableRef name=\"StatusCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"PathDelete\" id=\"13\">" \
"<VariableRef name=\"PathName\"/>" \
"</CommandMsg>" \
"<DataReplyMsg name=\"PathDeleteReply\" id=\"14\">" \
"<VariableRef name=\"PathName\"/>" \
"<VariableRef name=\"StatusCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"</Interface>" \
"" \
"<Interface name=\"BufferInterface\" id=\"3\">" \
"<Variable name=\"BufferName\" format=\"INT08\" length=\"80\" kind=\"Buffer_Name_String\" description=\"Requested name of buffer\" />" \
"<Variable name=\"ElementLength\" format=\"UINT16\" kind=\"Data_Size_Bytes\" description=\"Size of data buffer in Bytes\" />" \
"<Variable name=\"MaxNumElements\" format=\"UINT16\" kind=\"Max_Number_Elements\" description=\"Maximum numer of elements that log can contain\" />" \
"<Variable name=\"RcvSensorID\" format=\"UINT32\" kind=\"Sensor_ID\" description=\"Sensor ID associated with receiving buffer\" />" \
"<Variable name=\"RcvIpAddr\" format=\"UINT32\" kind=\"IP_Address\" description=\"IP Address associated with receiving buffer\" />" \
"<Variable name=\"RcvPortID\" format=\"UINT16\" kind=\"Port_ID\" description=\"Port ID associated with receiving buffer\" />" \
"<Variable name=\"MySensorID\" format=\"UINT32\" kind=\"Sensor_ID\" description=\"Sensor ID of application consuming drain data\" />" \
"<Variable name=\"MyIpAddr\" format=\"UINT32\" kind=\"IP_Address\" description=\"IP Address of application consuming drain data\" />" \
"<Variable name=\"MyPortID\" format=\"UINT16\" kind=\"Port_ID\" description=\"Port ID of application consuming drain data\" />" \
"<Variable name=\"BufferFillLevel\" format=\"FLOAT32\" kind=\"Fill_Level\" description=\"Buffer fill level in percent\" />" \
"<Variable name=\"NumTotalElements\" format=\"UINT32\" kind=\"Num_Elements\" description=\"Number of elements stored in buffer\" />" \
"<Variable name=\"NumReadElements\" format=\"UINT32\" kind=\"Num_Read_Elements\" description=\"Number of elements that have been read but not cleared\" />" \
"<Variable name=\"NumUnreadElements\" format=\"UINT32\" kind=\"Num_Unread_Elements\" description=\"Number of elements that have not been read\" />" \
"<Variable name=\"SourceSensorID\" format=\"UINT32\" kind=\"Sensor_ID\" description=\"Sensor ID of qualified search data\" />" \
"<Variable name=\"SourceIpAddr\" format=\"UINT32\" kind=\"IP_Address\" description=\"IP Address of qualified search data\" />" \
"<Variable name=\"SourcePortID\" format=\"UINT16\" kind=\"Port_ID\" description=\"Port ID of qualified search data\" />" \
"<Variable name=\"DataSource\" format=\"UINT32\" kind=\"Component_ID\" description=\"ComponentID of message origination for buffer searches, -1 indicates no constraint\" />" \
"<Variable name=\"MinTime\" format=\"INT32\" kind=\"Time\" units=\"Seconds\" description=\"Min time range value for buffer searches, -1 indicates no constraint\" />" \
"<Variable name=\"MaxTime\" format=\"INT32\" kind=\"Time\" units=\"Seconds\" description=\"Max time range value for buffer searches, -1 indicates no constraint\" />" \
"<Variable name=\"SourceSearchFlag\" format=\"UINT08\" kind=\"Source_Search_Flag\" description=\"Flag indicating search source data, 1 is all, 2 uses Source data from SourceSensorID/SourceIpAddress/SourcePortID variables\" >" \
"<Drange name=\"SearchFlagCodes\">" \
"<Option name=\"AllSources\" value=\"1\"/>" \
"<Option name=\"SelectSource\" value=\"2\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"ReadMask\" format=\"UINT08\" kind=\"Read_Mask_Mode\" description=\"Defines whether previously read elements are to be saerched\" >" \
"<Drange name=\"ReadMaskCodes\">" \
"<Option name=\"UnreadOnly\" value=\"1\"/>" \
"<Option name=\"ReadOnly\" value=\"2\"/>" \
"<Option name=\"UnreadAndRead\" value=\"3\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"DrainStyle\" format=\"UINT08\" kind=\"Drain_Mode\" description=\"Defines whether to drain the buffer Last-In-First-Out or First-In-First-Out\" >" \
"<Drange name=\"DrainStyleCodes\">" \
"<Option name=\"FIFO\" value=\"1\"/>" \
"<Option name=\"LIFO\" value=\"2\"/>" \
"</Drange>" \
"</Variable>" \
"<Variable name=\"BufferInterfaceResponseCode\" format=\"UINT08\" kind=\"Response_Code\" description=\"Failure Response for Buffer Operations\" >" \
"<Drange name=\"BufferInterfaceResponseCodeTypes\">" \
"<Option name=\"OperationOK\" value=\"1\"/>" \
"<Option name=\"NameInUse\" value=\"2\"/>" \
"<Option name=\"InsufficientMemory\" value=\"3\"/>" \
"<Option name=\"InvalidTimeRange\" value=\"4\"/>" \
"<Option name=\"NoSuchBuffer\" value=\"5\"/>" \
"<Option name=\"NoElementAvailable\" value=\"6\"/>" \
"</Drange>" \
"</Variable>" \
"" \
"<Request>" \
"<CommandMsg name=\"BufferCreate\" id=\"1\">" \
"<VariableRef name=\"BufferName\" />" \
"<VariableRef name=\"ElementLength\" />" \
"<VariableRef name=\"MaxNumElements\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"BufferCreateReply\" id=\"2\">" \
"<VariableRef name=\"BufferName\"/>" \
"<VariableRef name=\"BufferInterfaceResponseCode\"/>" \
"<VariableRef name=\"RcvSensorID\"/>" \
"<VariableRef name=\"RcvIpAddr\"/>" \
"<VariableRef name=\"RcvPortID\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"BufferSetDrainBehavior\" id=\"3\">" \
"<VariableRef name=\"BufferName\" />" \
"<VariableRef name=\"DataSource\" />" \
"<VariableRef name=\"MinTime\" />" \
"<VariableRef name=\"MaxTime\" />" \
"<VariableRef name=\"ReadMask\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"SetDrainFail\" id=\"4\">" \
"<VariableRef name=\"BufferName\" />" \
"<VariableRef name=\"BufferInterfaceResponseCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"BufferGetDrainBehavior\" id=\"5\">" \
"<VariableRef name=\"BufferName\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"GetDrainResponse\" id=\"6\">" \
"<VariableRef name=\"BufferName\" />" \
"<VariableRef name=\"BufferInterfaceResponseCode\"/>" \
"<VariableRef name=\"SourceSearchFlag\" />" \
"<VariableRef name=\"SourceSensorID\" />" \
"<VariableRef name=\"SourceIpAddr\" />" \
"<VariableRef name=\"SourcePortID\" />" \
"<VariableRef name=\"MinTime\" />" \
"<VariableRef name=\"MaxTime\" />" \
"<VariableRef name=\"ReadMask\" />" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"BufferGetStatus\" id=\"7\">" \
"<VariableRef name=\"BufferName\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"GetBufferStatusResponse\" id=\"8\">" \
"<VariableRef name=\"BufferName\" />" \
"<VariableRef name=\"BufferInterfaceResponseCode\"/>" \
"<VariableRef name=\"BufferFillLevel\" />" \
"<VariableRef name=\"NumTotalElements\" />" \
"<VariableRef name=\"NumReadElements\" />" \
"<VariableRef name=\"NumUnreadElements\" />" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"BufferDelete\" id=\"9\">" \
"<VariableRef name=\"BufferName\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"BufferDeleteResponse\" id=\"10\">" \
"<VariableRef name=\"BufferName\" />" \
"<VariableRef name=\"BufferInterfaceResponseCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"BufferGetNextElement\" id=\"11\">" \
"<VariableRef name=\"BufferName\" />" \
"<VariableRef name=\"MySensorID\"/>" \
"<VariableRef name=\"MyIpAddr\"/>" \
"<VariableRef name=\"MyPortID\"/>" \
"<VariableRef name=\"DrainStyle\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"BufferGetNextElementReply\" id=\"12\">" \
"<VariableRef name=\"BufferName\" />" \
"<VariableRef name=\"ElementLength\" />" \
"<VariableRef name=\"BufferInterfaceResponseCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"</Interface>" \
"" \
"<Interface name=\"LoggerInterface\" id=\"4\">" \
"<Variable name=\"LogName\" format=\"INT08\" length=\"80\" kind=\"Logfile_String\" description=\"Requested name of log\" />" \
"<Variable name=\"MaxEntryLength\" format=\"UINT08\" kind=\"Entry_Size_Chars\" description=\"Max size of a log entry in characters\" />" \
"<Variable name=\"MaxEntries\" format=\"UINT32\" kind=\"Max_Log_Entries\" description=\"Maximum number of entries\" />" \
"<Variable name=\"LogFillLevel\" format=\"FLOAT32\" kind=\"Fill_Level\" description=\"Percent of log filled with entries\" />" \
"<Variable name=\"LogTimeSeconds\" format=\"UINT32\" kind=\"Timestamp_Seconds\" description=\"Seconds portion of Log Entry Timestamp\" />" \
"<Variable name=\"LogTimeSubseconds\" format=\"UINT32\" kind=\"Timestamp_Subseconds\" description=\"Subseconds portion of Log Entry Timestamp\" />" \
"<Variable name=\"LogEntry\" format=\"INT08\" length=\"80\" kind=\"String\" description=\"Text data to be saved to Log\" />" \
"<Variable name=\"LogInterfaceResponseCode\" format=\"UINT08\" kind=\"Response_Code\" description=\"Response for Log Interface\" >" \
"<Drange name=\"LogInterfaceResponseCodeTypes\">" \
"<Option name=\"OperationOK\" value=\"1\"/>" \
"<Option name=\"NameInUse\" value=\"2\"/>" \
"<Option name=\"InsufficientMemory\" value=\"3\"/>" \
"<Option name=\"NoSuchLog\" value=\"4\"/>" \
"<Option name=\"LogFull\" value=\"5\"/>" \
"<Option name=\"EntryTooLong\" value=\"6\"/>" \
"<Option name=\"LogAlreadyOpen\" value=\"7\"/>" \
"</Drange>" \
"</Variable>" \
"" \
"<Request>" \
"<CommandMsg name=\"LogCreate\" id=\"1\">" \
"<VariableRef name=\"LogName\" />" \
"<VariableRef name=\"MaxEntryLength\" />" \
"<VariableRef name=\"MaxEntries\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"LogCreateReply\" id=\"2\">" \
"<VariableRef name=\"LogName\"/>" \
"<VariableRef name=\"LogInterfaceResponseCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"LogStatus\" id=\"3\">" \
"<VariableRef name=\"LogName\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"LogStatusReply\" id=\"4\">" \
"<VariableRef name=\"LogName\"/>" \
"<VariableRef name=\"LogFillLevel\"/>" \
"<VariableRef name=\"LogInterfaceResponseCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"LogWrite\" id=\"5\">" \
"<VariableRef name=\"LogName\" />" \
"<VariableRef name=\"LogTimeSeconds\" />" \
"<VariableRef name=\"LogTimeSubseconds\" />" \
"<VariableRef name=\"LogEntry\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"LogWriteReply\" id=\"6\">" \
"<VariableRef name=\"LogName\"/>" \
"<VariableRef name=\"LogInterfaceResponseCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"LogOpen\" id=\"7\">" \
"<VariableRef name=\"LogName\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"LogOpenReply\" id=\"8\">" \
"<VariableRef name=\"LogName\"/>" \
"<VariableRef name=\"LogInterfaceResponseCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"LogClose\" id=\"9\">" \
"<VariableRef name=\"LogName\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"LogCloseReply\" id=\"10\">" \
"<VariableRef name=\"LogName\"/>" \
"<VariableRef name=\"LogInterfaceResponseCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"<Request>" \
"<CommandMsg name=\"LogDelete\" id=\"11\">" \
"<VariableRef name=\"LogName\" />" \
"</CommandMsg>" \
"<DataReplyMsg name=\"LogDeleteReply\" id=\"12\">" \
"<VariableRef name=\"LogName\"/>" \
"<VariableRef name=\"LogInterfaceResponseCode\"/>" \
"</DataReplyMsg>" \
"</Request>" \
"" \
"</Interface>" \
"" \
"</xTEDS>" \
""

#endif
