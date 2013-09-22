# Makefile for asim test system

include ../$(MAKEFILE_DEFS)

.PHONY:	clean distclean

all: asim_test_gui asim_test

asim_test_gui: asim_test_gui.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -lncurses -L../common -lSDM

asim_test:	asim_test.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread -L../common -lSDM -lboost_regex

asim_test_gui.o: asim_test_gui.cpp
	$(CXX) $(CXXFLAGS) -c $<

asim_test.o:	asim_test.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o *~ *.out

distclean: clean
	rm -f asim_test asim_test_gui

