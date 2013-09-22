include ../../../Makefile.defs


.PHONY:	all clean distclean

BUILDTARGETS=MessageManipulatorTest SDMMessage_IDTest SDMVarTest SubManTest TimeTest MessageTests ProviderSubscriptionListTest

all:  $(BUILDTARGETS)

MessageManipulatorTest: MessageManipulatorTest.o xTEDSPoster.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

SDMMessage_IDTest: SDMMessage_IDTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

SDMVarTest: SDMVarTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

SubManTest: SubManTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

TimeTest: TimeTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

MessageTests: MessageTests.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

ProviderSubscriptionListTest: ProviderSubscriptionListTest.o ../../../dm/ProviderSubscriptionList.o ../../../dm/ProviderSubscription.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

xTEDSPoster.o: ../DMTests/xTEDSPoster.cpp ../DMTests/xTEDSPoster.h
	$(CXX) $(CXXFLAGS) -c $<
		
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o

distclean: clean
	rm -f $(BUILDTARGETS) *~
