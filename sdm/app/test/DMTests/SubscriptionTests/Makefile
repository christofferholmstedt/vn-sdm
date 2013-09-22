include ../../../../Makefile.defs

.PHONY: all clean distclean

BUILDTARGETS=SubCancelProducer SubCancelTest

all: $(BUILDTARGETS)

SubCancelTest: SubCancelTest.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< -L../../../../common -lSDM -lpthread

SubCancelProducer: SubCancelProducer.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< -L../../../../common -lSDM -lpthread

clean:

distclean: clean
	rm -f $(BUILDTARGETS) *~