#SubscriptionManager makefile

include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

.PHONY:	all clean distclean

all:	SubscriptionManager.o

SubscriptionManager.o:	SubscriptionManager.cpp SubscriptionManager.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

clean:
	rm -f *.o *~

distclean:	clean