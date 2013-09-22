# App Makefile

include ../Makefile.defs

.PHONY:	all clean distclean

SUBDIRS=examples
SUBDIRS_CLEAN= $(SUBDIRS) test

all:
	for dir in $(SUBDIRS); do \
		make -C $$dir; \
	done

clean:
	for dir in $(SUBDIRS_CLEAN); do \
		make -C $$dir clean; \
	done

distclean:
	for dir in $(SUBDIRS_CLEAN); do \
		make -C $$dir distclean; \
	done
