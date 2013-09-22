include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

.PHONY:	all clean distclean

all:	lex.xTEDS.o xTEDS.tab.o xTEDSParser.o xTEDS.o xTEDSItemTree.o xTEDSItem.o xTEDSCommand.o xTEDSDataMsg.o xTEDSVariableList.o xTEDSMessage.o xTEDSVariable.o MessageDef.o xTEDSQualifier.o xTEDSQualifierList.o xTEDSNotification.o xTEDSCommandMsg.o xTEDSRequest.o xTEDSFaultMsg.o xTEDSDrange.o xTEDSOption.o xTEDSOptionList.o xTEDSCoef.o xTEDSCoefList.o xTEDSCurve.o xTEDSLocation.o xTEDSOrientationList.o xTEDSOrientationItem.o VariableDef.o xTEDSWrapper.o xTEDSWrapperList.o xTEDSVerification.o

test:	test2.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ -lpthread -lboost_regex -L../ -lSDM

xTEDSParser.o:	xTEDSParser.c xTEDSParser.h
	$(CC) $(CFLAGS) -fPIC -c $<

lex.yy.o:	lex.xTEDS.c xTEDS.tab.c
	$(CC) $(CFLAGS) -fPIC -c $<

lex.xTEDS.o: lex.xTEDS.c
	$(CC)$(CFLAGS) -fPIC -c $<

xTEDS.tab.o:	xTEDS.tab.c
	$(CC) $(CFLAGS) -fPIC -c $<

lex.xTEDS.c:	xTEDS.l xTEDS.tab.c
	$(LEX) $(LEXFLAGS) -PxTEDS $<

xTEDS.tab.c:	xTEDS.y xTEDSParser.h
	$(YACC) $(YACCFLAGS) -p xTEDS $<

xTEDS.o: xTEDS.cpp xTEDSParser.h xTEDS.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

%.o:	%.cpp %.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<


clean:
	rm -f *.o *~

distclean: clean
	rm -f test msgdef.output xTEDS.output
