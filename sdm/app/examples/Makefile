include ../../Makefile.defs

.PHONY:	clean distclean

all: consumer converter producer copy

producer: producer.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

converter: converter.o
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

consumer: consumer.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(BOOSTFLAGS) -lpthread -L../../common -lSDM

%.o:	%.cpp
	$(CXX) $(CXXFLAGS) -c $<

copy:
	cp producer ../../tm
	cp consumer ../../tm
	cp converter ../../tm

clean:
	rm -f *.o *~

distclean: clean
	rm -f consumer converter producer
	rm -f ../../tm/consumer ../../tm/converter ../../tm/producer
	rm -f ../../pm/consumer ../../pm/converter ../../pm/producer
