include ../../../../Makefile.defs


.PHONY:	all clean distclean

all:  xTEDSRegTest

xTEDSRegTest: xTEDSRegTest.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../../common -lSDM

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $<

clean:
	rm -f *.o

distclean: clean
	rm -f xTEDSRegTest *~
