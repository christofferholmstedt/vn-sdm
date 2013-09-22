#MessageLogger makefile

include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

.PHONY: all clean distclean

all: MessageLogger.o SDMMessageLogger.o

MessageLogger.o: MessageLogger.cpp MessageLogger.h
	$(CXX) $(CXXFLAGS) $(MESSAGELOGGINGFLAGS) -fPIC -c $<

SDMMessageLogger.o: SDMMessageLogger.cpp SDMMessageLogger.h
	$(CXX) $(CXXFLAGS) $(MESSAGELOGGINGFLAGS) -fPIC -c $<

clean:
	rm -f *.o *~

distclean: clean