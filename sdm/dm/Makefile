# Makefile for client/server TCP
include ../Makefile.common
include ../$(MAKEFILE_DEFS)

DMBUILDFLAGS=$(DMBACKUPFLAGS) $(DMMERGEFLAGS) $(DMFAKEBACKUPFLAGS)

.PHONY:	clean distclean

dm:	dm.o  Parse.o xTEDSLibrary.o xTEDSLibraryList.o xTEDSParameters.o Subscription.o SubscriptionList.o backupDMList.o xTEDSSegmentBuilder.o DMUtils.o ProviderSubscription.o ProviderSubscriptionList.o
	$(CXX) $(CXXFLAGS) -L../common -static -o $@ $^ -lSDM -lpthread

dm_monitor: dm_monitor.cpp
	$(CXX) $(CXXFLAGS) -L../common -static -o $@ $^ -lSDM -lpthread

dm.o:	DM.cpp Parse.h
	$(CXX) $(CXXFLAGS) $(DMBUILDFLAGS) -c -o $@ $<

Parse.o:	Parse.cpp Parse.h
	$(CXX) $(CXXFLAGS) $(DMBUILDFLAGS) -c $<

xTEDSLibrary.o:	xTEDSLibrary.cpp xTEDSLibrary.h
	$(CXX) $(CXXFLAGS) -c $<

xTEDSLibraryList.o:	xTEDSLibraryList.cpp xTEDSLibraryList.h
	$(CXX) $(CXXFLAGS) -c $<

xTEDSParameters.o:	xTEDSParameters.cpp xTEDSParameters.h
	$(CXX) $(CXXFLAGS) -c $<

Subscription.o:	Subscription.cpp Subscription.h
	$(CXX) $(CXXFLAGS) -c $<

SubscriptionList.o:	SubscriptionList.cpp SubscriptionList.h
	$(CXX) $(CXXFLAGS) -c $<

backupDMList.o:	backupDMList.cpp backupDMList.h
	$(CXX) $(CXXFLAGS) -c $<

xTEDSSegmentBuilder.o: xTEDSSegmentBuilder.cpp xTEDSSegmentBuilder.h
	$(CXX) $(CXXFLAGS) -c $<

DMUtils.o: DMUtils.cpp DMUtils.h
	$(CXX) $(CXXFLAGS) -c $<

ProviderSubscription.o: ProviderSubscription.cpp ProviderSubscription.h
	$(CXX) $(CXXFLAGS) -c $<

ProviderSubscriptionList.o: ProviderSubscriptionList.cpp ProviderSubscriptionList.h
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o *~ SDMMessages*

distclean: clean
	rm -f dm dm_monitor
