include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

.PHONY: all clean distclean

BUILD_TARGETS=Regex RegexResult RegexMatch RegexCapture RegularExpression

all:	$(addsuffix .o,$(BUILD_TARGETS))

%.o:	%.cpp %.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

clean:
	rm -f *.o

distclean: clean
	rm -f *~
