#Time makefile

include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

CXXFLAGS += -I../

.PHONY: all clean distclean

all: SDMTimeLinux.o TimerList.o SecTime.o TimeKeepingLinux.o

SDMTimeLinux.o: SDMTimeLinux.cpp SDMTimeLinux.h
	$(CXX) $(CXXFLAGS) $(TIMEFLAGS) -fPIC -c $<

TimerList.o: TimerList.cpp TimerList.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

SecTime.o: SecTime.cpp SecTime.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

TimeKeepingLinux.o: TimeKeepingLinux.cpp TimeKeeping.h
	$(CXX) $(CXXFLAGS) $(TIMEFLAGS) -fPIC -c $<

clean:
	rm -f *.o *~

distclean: clean
