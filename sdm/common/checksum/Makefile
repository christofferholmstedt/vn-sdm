# Makefile for CRC check system

include ../../Makefile.common
include ../../$(MAKEFILE_DEFS)

.PHONY:	all clean distclean

all: checksum.o crcmodel.o

checksum.o:	checksum.c 
	$(CC) $(CFLAGS) -fPIC -c $<

crcmodel.o:	crcmodel.c
	$(CC) $(CFLAGS) -fPIC -c $<

clean:
	rm -f *.o *~

distclean: clean
