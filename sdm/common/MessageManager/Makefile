#MessageManager makefile

include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

.PHONY:	all clean distclean

all:	MessageManager.o

MessageManager.o:	MessageManager.cpp MessageManager.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

clean:
	rm -f *.o *~

distclean:	clean