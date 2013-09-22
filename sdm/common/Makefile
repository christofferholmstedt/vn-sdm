# Common code Makefile, produces a shared object
include ../Makefile.common
include ../$(MAKEFILE_DEFS)

.PHONY:	all clean distclean

SUBDIRS=message MessageLogger MessageManager MessageManipulator SubscriptionManager task checksum asim semaphore VarInfoParser xTEDS Time Exception Regex

MessageFiles = SDMAck SDMCancel SDMCancelxTEDS SDMCode SDMCommand SDMConsume SDMData SDMDeletesub SDMDMLeader SDMElection SDMError SDMHeartbeat SDMmessage SDMPostTask SDMReady SDMRegInfo SDMReqCode SDMReqReg SDMReqxTEDS SDMSerreqst SDMService SDMSubreqst SDMTask SDMTaskError SDMTaskFinished SDMTat SDMxTEDS SDMxTEDSInfo SDMRegPM SDMComponent_ID SDMMessage_ID SDMSearch SDMSearchReply SDMVarInfo SDMVarReq SDMKill SDMHello SDMRegister SDMID

MessageLoggerFiles = MessageLogger SDMMessageLogger

MessageManagerFiles = MessageManager

MessageManipulatorFiles = MessageManipulator lex.MessageManipulator msgdef.tab message

SubscriptionManagerFiles = SubscriptionManager

TaskFiles = SDMTaskResources

TimeFiles = TimeKeepingLinux SDMTimeLinux TimerList SecTime

ChecksumFiles = checksum crcmodel

AsimFiles = ASIM

SemaphoreFiles = semaphore

VarInfoParserFiles = Variable lex.VarInfoParser VarInfoParser.tab VarInfoParser

xTEDSFiles = lex.xTEDS MessageDef xTEDSCommand xTEDSDataMsg xTEDSItem xTEDSItemTree xTEDSMessage xTEDS xTEDSParser xTEDSQualifierList xTEDSQualifier xTEDS.tab xTEDSVariable xTEDSRequest xTEDSNotification xTEDSCommandMsg xTEDSFaultMsg xTEDSDrange xTEDSOption xTEDSOptionList xTEDSOrientationList xTEDSOrientationItem xTEDSCurve xTEDSCoef xTEDSCoefList xTEDSLocation VariableDef xTEDSVerification xTEDSWrapper xTEDSWrapperList xTEDSVariableList

ExceptionFiles = SDMException SDMRegexException SDMBadIndexException

RegexFiles = Regex RegexResult RegexMatch RegexCapture RegularExpression

BUILDTARGETS=$(addsuffix .o, \
                  $(addprefix ./message/,$(MessageFiles)) \
                  $(addprefix ./MessageLogger/,$(MessageLoggerFiles)) \
                  $(addprefix ./MessageManager/,$(MessageManagerFiles)) \
                  $(addprefix ./MessageManipulator/,$(MessageManipulatorFiles)) \
                  $(addprefix ./SubscriptionManager/,$(SubscriptionManagerFiles)) \
                  $(addprefix ./task/,$(TaskFiles)) \
                  $(addprefix ./Time/,$(TimeFiles)) \
                  $(addprefix ./checksum/,$(ChecksumFiles)) \
                  $(addprefix ./asim/,$(AsimFiles)) \
                  $(addprefix ./semaphore/,$(SemaphoreFiles)) \
                  $(addprefix ./VarInfoParser/,$(VarInfoParserFiles)) \
                  $(addprefix ./xTEDS/,$(xTEDSFiles)) \
                  $(addprefix ./Exception/,$(ExceptionFiles)) \
                  $(addprefix ./Regex/,$(RegexFiles))) \
                UDPcom.o TCPcom.o ErrorUtils.o MemoryUtils.o SDMComHandle.o SDMRegQueue.o SDMCancelQueue.o sdmLib.o 

all:	subdir libSDM.so libSDM.so.1 libSDM.so.1.0 libSDM.a

uclinux: subdir libSDM.a

libSDM.so:	libSDM.so.1.0
	ln -sf $< $@

libSDM.so.1:	libSDM.so.1.0
	ln -sf $< $@

libSDM.so.1.0: $(BUILDTARGETS)
	$(CXX) $(CXXFLAGS) -fPIC -shared -o $@ $^

libSDM.a: $(BUILDTARGETS) marshall.o
	ar rcs $@ $^

subdir:
	for dir in $(SUBDIRS); do \
		make -C $$dir; \
	done	

UDPcom.o: UDPcom.cpp UDPcom.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

TCPcom.o: TCPcom.cpp TCPcom.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

ErrorUtils.o: ErrorUtils.cpp ErrorUtils.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

MemoryUtils.o: MemoryUtils.c MemoryUtils.h
	$(CC) $(CFLAGS) -fPIC -c $<

SDMComHandle.o: SDMComHandle.cpp SDMComHandle.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

SDMRegQueue.o: SDMRegQueue.cpp SDMRegQueue.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

SDMCancelQueue.o: SDMCancelQueue.cpp SDMCancelQueue.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

sdmLib.o: sdmLib.cpp
	$(CXX) $(CXXFLAGS) -I./ -fPIC -c $<

marshall.o: marshall.c marshall.h
	$(CC) $(CCFLAGS) -fPIC -c $<

clean:
	for dir in $(SUBDIRS); do \
		make -C $$dir clean; \
	done
	rm -f *.o *~

distclean:	clean
	for dir in $(SUBDIRS); do \
		make -C $$dir distclean; \
	done
	rm -f libSDM.so.* libSDM.so libSDM.a
