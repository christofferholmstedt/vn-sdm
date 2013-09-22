include ../Makefile.common
include ../$(MAKEFILE_DEFS)

.PHONY:	all clean distclean

all: sm sm_process

sm_process: sm_process.o sensor.o SensorRecord.o SensorMonitor.o
	$(CXX) $(CXXFLAGS) -L../common -static -o $@ $^ $(BOOSTFLAGS) -lSDM -lpthread

sensor.o: sensor.cpp sensor.h
	$(CXX) $(CXXFLAGS) -c $<

sm_process.o:	sm.cpp sm.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

SensorRecord.o: SensorRecord.cpp SensorRecord.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

SensorMonitor.o: SensorMonitor.cpp SensorMonitor.h SensorRecord.o
	$(CXX) $(CXXFLAGS) -c -o $@ $<

sm:	sm_monitor.cpp
	$(CXX) $(CXXFLAGS) -L../common -static -o $@ $< $(BOOSTFLAGS) -lSDM -lpthread

clean:
	rm -f *.o *~ *.out SDMMessages*

distclean: clean
	rm -f sm sm_process
