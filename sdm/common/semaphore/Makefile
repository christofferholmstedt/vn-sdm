#semaphore makefile

include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

.PHONY: all clean distclean

all:	semaphore.o

semaphore.o:	semaphore.cpp semaphore.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

clean:
	rm -f *.o *~

distclean:	clean