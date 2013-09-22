include ../Makefile.common
include ../$(MAKEFILE_DEFS)

.PHONY:	all clean distclean
#CXX=/opt/gumstix/build_arm_nofpu/staging_dir/bin/arm-linux-uclibcgnueabi-g++


all: Spa1Manager

Spa1Manager: Spa1Manager.o Spa1Asim.o Spa1Queue.o Spa1Msg.o Spa1AsimTable.o Spa1Translator.o
	$(CXX) $(CXXFLAGS) -L../common -static -o $@ $^ $(BOOSTFLAGS) -lSDM -lpthread

Spa1Manager.o: Spa1Manager.cpp
	$(CXX) $(CXXFLAGS) -c $<

Spa1Asim.o:	Spa1Asim.cpp Spa1Asim.h Spa1Queue.o
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Spa1Queue.o: Spa1Queue.cpp Spa1Queue.h Spa1Msg.o
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Spa1Msg.o: Spa1Msg.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

Spa1AsimTable.o: Spa1AsimTable.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
	
Spa1Translator.o: Spa1Translator.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o *~ *.out

distclean: clean
	rm -f Spa1Manager
