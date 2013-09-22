include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

.PHONY:	all clean distclean

all:	MessageManipulator.o lex.MessageManipulator.o msgdef.tab.o message.o

MessageManipulator.o: MessageManipulator.cpp MessageManipulator.h message.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

msgdefmain.o:	msgdefmain.c
	$(CC) $(CFLAGS) -c $<

lex.MessageManipulator.o:	lex.MessageManipulator.c msgdef.tab.c
	$(CC) $(CFLAGS) -fPIC -c $<

msgdef.tab.o:	msgdef.tab.c message.h
	$(CC) $(CFLAGS) -fPIC -c $<

lex.MessageManipulator.c:	msgdef.l msgdef.tab.c
	$(LEX) $(LEXFLAGS) -PMessageManipulator $<

msgdef.tab.c:	msgdef.y message.h
	$(YACC) $(YACCFLAGS) -p MessageManipulator $<

message.o:	message.c
	$(CC) $(CFLAGS) -fPIC -c $<

clean:
	rm -f *.o *~

distclean: clean
	rm -f msgdef.output
