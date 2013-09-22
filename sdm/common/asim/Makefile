#asim makefile

include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

.PHONY:	all clean distclean

all:	ASIM.o

ASIM.o:	ASIM.cpp ASIM.h asim_commands.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

clean:
	rm -f *.o *~

distclean:	clean