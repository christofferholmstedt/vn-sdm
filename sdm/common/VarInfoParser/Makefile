include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

.PHONY: all clean distclean

all: lex.VarInfoParser.o VarInfoParser.tab.o Variable.o VarInfoParser.o

#rules for the VarInfoParser class
VarInfoParser.o: VarInfoParser.cpp VarInfoParser.h Variable.h
	$(CXX) $(CXXFLAGS) -fPIC -c $<

#rules for lexical analyzer
lex.VarInfoParser.o: lex.VarInfoParser.c VarInfoParser.tab.c
	$(CC) $(CFLAGS) -fPIC -c $<
	
lex.VarInfoParser.c: VarInfoParser.l
	$(LEX) $(LEXFLAGS) -PVarInfoParser $<
	
#rules for parser
VarInfoParser.tab.o: VarInfoParser.tab.c
	$(CC) $(CFLAGS) -fPIC -c $<

VarInfoParser.tab.c: VarInfoParser.y
	$(YACC) $(YACCFLAGS) -p VarInfoParser $<

#rules for Variable
Variable.o: Variable.c Variable.h
	$(CC) $(CFLAGS) -fPIC -c $<

clean:
	rm -f *.o *~
	
distclean: clean