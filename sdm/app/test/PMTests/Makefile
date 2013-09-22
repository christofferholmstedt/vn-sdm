include ../../../Makefile.defs

.PHONY: all clean distclean

BUILD_TARGETS = AppFailSilentTestProducer AppFailSilentTestConsumer AppFailSilentTest

all: $(BUILD_TARGETS)

AppFailSilentTestProducer: AppFailSilentTestProducer.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< -L../../../common/ -lSDM -lpthread

AppFailSilentTestConsumer: AppFailSilentTestConsumer.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< -L../../../common/ -lSDM -lpthread

AppFailSilentTest: AppFailSilentTest.cpp
	$(CXX) $(CXXFLAGS) -o $@ $< -L../../../common/ -lSDM -lpthread

clean:
	rm -f $(BUILD_TARGETS)

distclean: clean