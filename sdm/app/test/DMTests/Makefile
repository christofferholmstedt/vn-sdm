include ../../../Makefile.defs

BUILDTARGETS=SegmentedxTEDSTest GenericReqRegTest GenericVarReqTest GenericSearchTest xTEDSQualifierTests xTEDSVariableTests LargexTEDSTest
SUBDIRS=xTEDSRegTests

.PHONY:	all clean distclean

all: $(BUILDTARGETS)
	for dir in $(SUBDIRS); do \
		make -C $$dir; \
	done

SegmentedxTEDSTest: SegmentedxTEDSTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

GenericReqRegTest: GenericReqRegTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

GenericVarReqTest: GenericVarReqTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

GenericSearchTest: GenericSearchTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

xTEDSVariableTests: xTEDSVariableTests.o xTEDSPoster.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

xTEDSQualifierTests: xTEDSQualifierTests.o xTEDSPoster.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

LargexTEDSTest: LargexTEDSTest.o xTEDSPoster.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

xTEDSPoster.o: xTEDSPoster.cpp xTEDSPoster.h
	$(CXX) $(CXXFLAGS) -c $<

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o
	for dir in $(SUBDIRS); do \
		make -C $$dir clean; \
	done

distclean: clean
	rm -f $(BUILDTARGETS) *~
	for dir in $(SUBDIRS); do \
		make -C $$dir distclean; \
	done
