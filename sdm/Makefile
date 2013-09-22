# Top-level Makefile

MAKEFILE_DEFS=Makefile.defs
export MAKEFILE_DEFS

include $(MAKEFILE_DEFS)

.PHONY:	all clean distclean package

SUBDIRS=common app dm pm sm tm Spa1Manager

all:
	for dir in $(SUBDIRS); do \
		make -S -C $$dir || exit 1; \
	done

clean:
	for dir in $(SUBDIRS); do \
		make -C $$dir clean; \
	done

distclean:
	for dir in $(SUBDIRS); do \
		make -C $$dir distclean; \
	done

package:	SDMSources.tar.gz SDMSourcesLinux.tar.gz SDMBinaries.tar.gz SDMExamples.tar.gz

ASIMTester.tar.gz:
	tar -cz -X asim_tester_exclude * > $@

SDMExamples.tar.gz:
	tar -cz -X example_package_exclude * > $@

SDMSources.tar.gz:
	tar -cz -X source_package_exclude * > $@

SDMSourcesLinux.tar.gz:
	tar -cz -X source_package_linux_exclude * > $@

SDMBinaries.tar.gz:	all
	mkdir bin
	mkdir lib
	cp ./dm/dm ./bin/.
	cp ./tm/tm ./bin/.
	cp ./tm/tm_process ./bin/.
	cp ./pm/pm ./bin/.
	cp ./sm/sm ./bin/.
	cp ./sm/sm_process ./bin/.
	cp ./common/libSDM.so.1.0 ./lib/libSDM.so
	tar -cz bin lib > $@
	rm ./bin/*
	rm ./lib/*
	rmdir bin
	rmdir lib




