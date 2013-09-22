
include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

.PHONY: all clean distclean

all:	SDMTaskResources.o

SDMTaskResources.o:	SDMTaskResources.cpp SDMTaskResources.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

clean:
	rm -f *.o *~

distclean:	clean