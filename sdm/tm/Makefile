# Makefile for tm system
include ../Makefile.common
include ../$(MAKEFILE_DEFS)

.PHONY:	clean distclean

TMOBJECTS=tm.o pm_record.o pm_record_list.o TMUtils.o task.o tasklist.o

all:	tm tm_monitor

tm:	$(TMOBJECTS)
	$(CXX) $(CXXFLAGS) -L../common -static -o $@ $^ $(BOOSTFLAGS) -lSDM -lpthread

tm_monitor:	tm_monitor.cpp
	$(CXX) $(CXXFLAGS) -L../common -static -o $@ $< $(BOOSTFLAGS) -lSDM -lpthread

tm.o:	tm.cpp ../common/message_defs.h task.h tasklist.h ../common/checksum/checksum.h
	$(CXX) $(CXXFLAGS) -c $<

pm_record.o:	pm_record.cpp pm_record.h
	$(CXX) $(CXXFLAGS) -c $<

pm_record_list.o: pm_record_list.cpp pm_record_list.h
	$(CXX) $(CXXFLAGS) -c $<

TMUtils.o: ../dm/DMUtils.cpp ../dm/DMUtils.h
	$(CXX) $(CXXFLAGS) -c -o $@ $<

clean:
	rm -f *.o *~ SDMMessages* 

distclean: clean
	rm -f tm tm_monitor
