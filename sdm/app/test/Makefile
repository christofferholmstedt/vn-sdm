include ../../Makefile.defs

BUILDTARGETS=badxTEDS1 magnetometer_test magtest \
	  ReqRegTest ReqxTEDStest ServicePID StressxTEDtest\
	  badReqReg1 TestDMService TestRegEx testSDMTat\
	  messagecountconsumer MessageLogAddAll MessageLogRemoveAll\
	  xTEDSPoster SearchTest MessageClassTest ReqReg1.4Test DMServicesTest TMSubsTest TCPTester \
	  SearchSubTest ModificationSearchSubTest MinimalxTEDSgetIP\
	  FaultMsgtest BreadBoardTest VarInfoParserTest VarReq FileServiceTest DevicesTest RoboHubTest KillTester TatTest TaskPostTest GetTimeTest

.PHONY:	all clean distclean

SUBDIRS=DMTests PMTests ClassTests

all: $(BUILDTARGETS)
	for dir in $(SUBDIRS); do \
		make -C $$dir; \
	done

DNET_IRU_400_test: DNET_IRU_400_test.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

DNET_Reaction_Wheel_4NM_test: DNET_Reaction_Wheel_4NM_test.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

badxTEDS1: badxTEDS1.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

badReqReg1: badReqReg1.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

ReqxTEDStest: ReqxTEDStest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

ReqRegTest: ReqRegTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

magnetometer_test: magnetometer_test.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

magtest: magtest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

StressxTEDtest: StressxTEDtest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

ServicePID: ServicePID.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

TestDMService: TestDMService.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

TestRegEx: TestRegEx.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

testSDMTat: testSDMTat.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

test2: test2.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

messagecountconsumer: messagecountconsumer.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

MessageLogAdd: MessageLogAdd.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
	
MessageLogAddAll: MessageLogAddAll.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

MessageLogRemove: MessageLogRemove.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
	
MessageLogRemoveAll: MessageLogRemoveAll.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

xTEDSPoster: xTEDSPoster.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

SearchTest: SearchTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

MessageClassTest: MessageClassTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

ReqReg1.4Test: ReqReg1.4Test.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
	
DMServicesTest: DMServicesTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

TMSubsTest: TMSubsTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
	
TCPTester: TCPTester.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

SearchSubTest:	SearchSubTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
		
BreadBoardTest:	BreadBoardTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
	
RoboHubTest: RoboHubTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
		
ModificationSearchSubTest:	ModificationSearchSubTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
		
MinimalxTEDSgetIP:	MinimalxTEDSgetIP.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
		
FaultMsgtest:	FaultMsgtest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
	
VarInfoParserTest: VarInfoParserTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
		
VarReq: VarReq.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
	
FileServiceTest: FileServiceTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

DevicesTest: DevicesTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
		
MessageManipulatorTest: MessageManipulatorTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM
		
KillTester: KillTester.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

TatTest: TatTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

TaskPostTest: TaskPostTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

GetTimeTest: GetTimeTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread  -L../../common -lSDM

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o *~
	for dir in $(SUBDIRS); do \
		make -C $$dir clean; \
	done

distclean: clean
	rm -f $(BUILDTARGETS)
	rm -f SDMMessages*log
	for dir in $(SUBDIRS); do \
		make -C $$dir distclean; \
	done

