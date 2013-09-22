# Makefile for pm system

include ../Makefile.common
include ../$(MAKEFILE_DEFS)

.PHONY:	clean distclean

all: pm pm_ids pm_monitor

# Version of the PM to use the TM
pm:	pm_main.o pm.o PMProcess.o PMProcessList.o PendingTask.o
	$(CXX) $(CXXFLAGS) -L../common -static -o $@ $^ -lSDM -lpthread

# Version of the PM to use the IDS
pm_ids: pm_ids.o pm_main_ids.o PMProcess.o PMProcessList.o PendingTask.o
	$(CXX) $(CXXFLAGS) -L../common -static -o $@ $^ -lSDM -lpthread

pm_monitor: pm_monitor.o
	$(CXX) $(CXXFLAGS) -L../common -static -o $@ $^ -lSDM -lpthread

PMProcess.o: PMProcess.cpp PMProcess.h
	$(CXX) $(CXXFLAGS) -c $<

PMProcessList.o: PMProcessList.cpp PMProcessList.h
	$(CXX) $(CXXFLAGS) -c $<

PendingTask.o: PendingTask.cpp PendingTask.h
	$(CXX) $(CXXFLAGS) -c $<

pm_main_ids.o: pm_main.cpp pm.h
	$(CXX) $(CXXFLAGS) -c -o $@ -DBUILD_FOR_IDS $<

pm_main.o: pm_main.cpp pm.h
	$(CXX) $(CXXFLAGS) -c $<

pm.o: pm.cpp pm.h
	$(CXX) $(CXXFLAGS) -c $<

pm_ids.o: pm_ids.cpp pm_ids.h
	$(CXX) $(CXXFLAGS) -c -DBUILD_FOR_IDS $<

pm_monitor.o: pm_monitor.cpp
	$(CXX) $(CXXFLAGS) -c $<

#%.o: %.cpp %.h
#	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o *.log SDMMessages*
	rm -f consumer converter producer

distclean: clean
	rm -f pm pm_ids *~ pm_monitor
