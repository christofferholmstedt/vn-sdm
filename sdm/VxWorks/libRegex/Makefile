# Wind River Workbench generated Makefile.
# Do not edit!!!
#
# The file ".wrmakefile" is the template used by the Wind River Workbench to
# generate the makefiles of this project. Add user-specific build targets and
# make rules only(!) in this project's ".wrmakefile" file. These will then be
# automatically dumped into the makefiles.

WIND_HOME := $(subst \,/,$(WIND_HOME))
WIND_BASE := $(subst \,/,$(WIND_BASE))
WIND_USR := $(subst \,/,$(WIND_USR))

all : pre_recursion subdirs_all post_recursion pre_build main_all post_build

TRACE=0
TRACEON=$(TRACE:0=@)
TRACE_FLAG=$(TRACEON:1=)

MAKEFILE := Makefile

BUILD_SPEC = PPC32gnu_RTP
DEBUG_MODE = 1
SRC_DIR := .
BUILD_ROOT_DIR := 
PRJ_ROOT_DIR := C:/Temp/Test/VxWorks/libRegex
WS_ROOT_DIR := C:/WindRiver/workspace

ALL_BUILD_SPECS := ARMARCH5diab_RTP ARMARCH5diabbe_RTP ARMARCH5gnu_RTP ARMARCH5gnube_RTP \
	 ARMARCH6diab_RTP ARMARCH6diabbe_RTP ARMARCH6gnu_RTP ARMARCH6gnube_RTP \
	 MIPS32sfdiab_RTP MIPS32sfdiable_RTP MIPS32sfgnu_RTP MIPS32sfgnule_RTP \
	 MIPS64diab_RTP MIPS64diable_RTP MIPS64gnu_RTP MIPS64gnule_RTP \
	 PENTIUM2diab_RTP PENTIUM2gnu_RTP PENTIUM3diab_RTP PENTIUM3gnu_RTP \
	 PENTIUM4diab_RTP PENTIUM4gnu_RTP PENTIUMdiab_RTP PENTIUMgnu_RTP \
	 PPC32diab_RTP PPC32gnu_RTP PPC32sfdiab_RTP PPC32sfgnu_RTP \
	 SH32diab_RTP SH32diable_RTP SH32gnu_RTP SH32gnule_RTP \
	 SIMPENTIUMdiab_RTP SIMPENTIUMgnu_RTP SIMSPARCSOLARISdiab_RTP SIMSPARCSOLARISgnu_RTP \
	 XSCALEdiab_RTP XSCALEdiabbe_RTP XSCALEgnu_RTP XSCALEgnube_RTP
ENABLED_BUILD_SPECS := $(ALL_BUILD_SPECS)

ifeq ($(BUILD_SPEC),ARMARCH5diab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH5diab_RTP_DEBUG
else
OBJ_DIR := ARMARCH5diab_RTP
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH5diabbe_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH5diabbe_RTP_DEBUG
else
OBJ_DIR := ARMARCH5diabbe_RTP
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH5gnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH5gnu_RTP_DEBUG
else
OBJ_DIR := ARMARCH5gnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH5gnube_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH5gnube_RTP_DEBUG
else
OBJ_DIR := ARMARCH5gnube_RTP
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH6diab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH6diab_RTP_DEBUG
else
OBJ_DIR := ARMARCH6diab_RTP
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH6diabbe_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH6diabbe_RTP_DEBUG
else
OBJ_DIR := ARMARCH6diabbe_RTP
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH6gnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH6gnu_RTP_DEBUG
else
OBJ_DIR := ARMARCH6gnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),ARMARCH6gnube_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ARMARCH6gnube_RTP_DEBUG
else
OBJ_DIR := ARMARCH6gnube_RTP
endif
endif
ifeq ($(BUILD_SPEC),MIPS32sfdiab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS32sfdiab_RTP_DEBUG
else
OBJ_DIR := MIPS32sfdiab_RTP
endif
endif
ifeq ($(BUILD_SPEC),MIPS32sfdiable_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS32sfdiable_RTP_DEBUG
else
OBJ_DIR := MIPS32sfdiable_RTP
endif
endif
ifeq ($(BUILD_SPEC),MIPS32sfgnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS32sfgnu_RTP_DEBUG
else
OBJ_DIR := MIPS32sfgnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),MIPS32sfgnule_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS32sfgnule_RTP_DEBUG
else
OBJ_DIR := MIPS32sfgnule_RTP
endif
endif
ifeq ($(BUILD_SPEC),MIPS64diab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS64diab_RTP_DEBUG
else
OBJ_DIR := MIPS64diab_RTP
endif
endif
ifeq ($(BUILD_SPEC),MIPS64diable_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS64diable_RTP_DEBUG
else
OBJ_DIR := MIPS64diable_RTP
endif
endif
ifeq ($(BUILD_SPEC),MIPS64gnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS64gnu_RTP_DEBUG
else
OBJ_DIR := MIPS64gnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),MIPS64gnule_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := MIPS64gnule_RTP_DEBUG
else
OBJ_DIR := MIPS64gnule_RTP
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM2diab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM2diab_RTP_DEBUG
else
OBJ_DIR := PENTIUM2diab_RTP
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM2gnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM2gnu_RTP_DEBUG
else
OBJ_DIR := PENTIUM2gnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM3diab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM3diab_RTP_DEBUG
else
OBJ_DIR := PENTIUM3diab_RTP
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM3gnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM3gnu_RTP_DEBUG
else
OBJ_DIR := PENTIUM3gnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM4diab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM4diab_RTP_DEBUG
else
OBJ_DIR := PENTIUM4diab_RTP
endif
endif
ifeq ($(BUILD_SPEC),PENTIUM4gnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUM4gnu_RTP_DEBUG
else
OBJ_DIR := PENTIUM4gnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),PENTIUMdiab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUMdiab_RTP_DEBUG
else
OBJ_DIR := PENTIUMdiab_RTP
endif
endif
ifeq ($(BUILD_SPEC),PENTIUMgnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PENTIUMgnu_RTP_DEBUG
else
OBJ_DIR := PENTIUMgnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),PPC32diab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC32diab_RTP_DEBUG
else
OBJ_DIR := PPC32diab_RTP
endif
endif
ifeq ($(BUILD_SPEC),PPC32gnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := ../bin/regex_DEBUG
else
OBJ_DIR := ../bin/regex
endif
endif
ifeq ($(BUILD_SPEC),PPC32sfdiab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC32sfdiab_RTP_DEBUG
else
OBJ_DIR := PPC32sfdiab_RTP
endif
endif
ifeq ($(BUILD_SPEC),PPC32sfgnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := PPC32sfgnu_RTP_DEBUG
else
OBJ_DIR := PPC32sfgnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),SH32diab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SH32diab_RTP_DEBUG
else
OBJ_DIR := SH32diab_RTP
endif
endif
ifeq ($(BUILD_SPEC),SH32diable_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SH32diable_RTP_DEBUG
else
OBJ_DIR := SH32diable_RTP
endif
endif
ifeq ($(BUILD_SPEC),SH32gnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SH32gnu_RTP_DEBUG
else
OBJ_DIR := SH32gnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),SH32gnule_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SH32gnule_RTP_DEBUG
else
OBJ_DIR := SH32gnule_RTP
endif
endif
ifeq ($(BUILD_SPEC),SIMPENTIUMdiab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SIMPENTIUMdiab_RTP_DEBUG
else
OBJ_DIR := SIMPENTIUMdiab_RTP
endif
endif
ifeq ($(BUILD_SPEC),SIMPENTIUMgnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SIMPENTIUMgnu_RTP_DEBUG
else
OBJ_DIR := SIMPENTIUMgnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SIMSPARCSOLARISdiab_RTP_DEBUG
else
OBJ_DIR := SIMSPARCSOLARISdiab_RTP
endif
endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := SIMSPARCSOLARISgnu_RTP_DEBUG
else
OBJ_DIR := SIMSPARCSOLARISgnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),XSCALEdiab_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := XSCALEdiab_RTP_DEBUG
else
OBJ_DIR := XSCALEdiab_RTP
endif
endif
ifeq ($(BUILD_SPEC),XSCALEdiabbe_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := XSCALEdiabbe_RTP_DEBUG
else
OBJ_DIR := XSCALEdiabbe_RTP
endif
endif
ifeq ($(BUILD_SPEC),XSCALEgnu_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := XSCALEgnu_RTP_DEBUG
else
OBJ_DIR := XSCALEgnu_RTP
endif
endif
ifeq ($(BUILD_SPEC),XSCALEgnube_RTP)
ifeq ($(DEBUG_MODE),1)
OBJ_DIR := XSCALEgnube_RTP_DEBUG
else
OBJ_DIR := XSCALEgnube_RTP
endif
endif

DEP_FILES := $(OBJ_DIR)/pcre_get.d $(OBJ_DIR)/pcre_ucd.d $(OBJ_DIR)/pcre_ord2utf8.d \
	 $(OBJ_DIR)/pcre_newline.d $(OBJ_DIR)/pcre_xclass.d $(OBJ_DIR)/pcre_chartables.d \
	 $(OBJ_DIR)/pcre_globals.d $(OBJ_DIR)/pcre_compile.d $(OBJ_DIR)/pcre_exec.d \
	 $(OBJ_DIR)/pcre_info.d $(OBJ_DIR)/pcrecpp.d $(OBJ_DIR)/pcre_config.d \
	 $(OBJ_DIR)/pcre_dfa_exec.d $(OBJ_DIR)/pcre_refcount.d $(OBJ_DIR)/pcreposix.d \
	 $(OBJ_DIR)/pcre_tables.d $(OBJ_DIR)/pcre_maketables.d $(OBJ_DIR)/pcre_version.d \
	 $(OBJ_DIR)/pcre_try_flipped.d $(OBJ_DIR)/pcre_study.d $(OBJ_DIR)/pcre_fullinfo.d \
	 $(OBJ_DIR)/pcre_valid_utf8.d
-include $(DEP_FILES)

ifeq ($(BUILD_SPEC),ARMARCH5diab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH5diabbe_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH5gnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH5gnube_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH6diab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH6diabbe_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH6gnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),ARMARCH6gnube_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS32sfdiab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS32sfdiable_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS32sfgnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS32sfgnule_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS64diab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS64diable_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS64gnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),MIPS64gnule_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM2diab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM2gnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM3diab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM3gnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM4diab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUM4gnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUMdiab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PENTIUMgnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC32diab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC32gnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC32sfdiab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),PPC32sfgnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SH32diab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SH32diable_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SH32gnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SH32gnule_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SIMPENTIUMdiab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SIMPENTIUMgnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),XSCALEdiab_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),XSCALEdiabbe_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),XSCALEgnu_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif
ifeq ($(BUILD_SPEC),XSCALEgnube_RTP)
SUBDIRS := "C:/Temp/Test/VxWorks/libRegex/.svn"
OBJECTS := $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho $(OBJ_DIR)/pcre_ord2utf8.sho \
	 $(OBJ_DIR)/pcre_newline.sho $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho $(OBJ_DIR)/pcre_exec.sho \
	 $(OBJ_DIR)/pcre_info.sho $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho $(OBJ_DIR)/pcreposix.sho \
	 $(OBJ_DIR)/pcre_tables.sho $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho $(OBJ_DIR)/pcre_fullinfo.sho \
	 $(OBJ_DIR)/pcre_valid_utf8.sho

PROJECT_TARGETS := $(OBJ_DIR)/libRegex.a

SUB_OBJECTS :=
SUB_TARGETS :=
endif

PROJECT_TYPE = SL
DEFINES = -DHAVE_CONFIG_H
DO_STRIP = 0
SHAREDLIB_VERSION = 
EXPAND_DBG = 0

ifeq ($(BUILD_SPEC),ARMARCH5diab_RTP)
VX_CPU_FAMILY = arm
CPU = ARMARCH5
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tARMV5LS:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),ARMARCH5diabbe_RTP)
VX_CPU_FAMILY = arm
CPU = ARMARCH5
TOOL_FAMILY = diab
TOOL = diabbe
TOOL_PATH = 
CC_ARCH_SPEC = -tARMV5ES:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),ARMARCH5gnu_RTP)
VX_CPU_FAMILY = arm
CPU = ARMARCH5
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -t5
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),ARMARCH5gnube_RTP)
VX_CPU_FAMILY = arm
CPU = ARMARCH5
TOOL_FAMILY = gnu
TOOL = gnube
TOOL_PATH = 
CC_ARCH_SPEC = -t5be  -Wa,-EB
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),ARMARCH6diab_RTP)
VX_CPU_FAMILY = arm
CPU = ARMARCH6
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tARMV6LS:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),ARMARCH6diabbe_RTP)
VX_CPU_FAMILY = arm
CPU = ARMARCH6
TOOL_FAMILY = diab
TOOL = diabbe
TOOL_PATH = 
CC_ARCH_SPEC = -tARMV6ES:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),ARMARCH6gnu_RTP)
VX_CPU_FAMILY = arm
CPU = ARMARCH6
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -t5
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),ARMARCH6gnube_RTP)
VX_CPU_FAMILY = arm
CPU = ARMARCH6
TOOL_FAMILY = gnu
TOOL = gnube
TOOL_PATH = 
CC_ARCH_SPEC = -t5be  -Wa,-EB
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),MIPS32sfdiab_RTP)
VX_CPU_FAMILY = mips
CPU = MIPS32
TOOL_FAMILY = diab
TOOL = sfdiab
TOOL_PATH = 
CC_ARCH_SPEC = -tMIPS2FS:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),MIPS32sfdiable_RTP)
VX_CPU_FAMILY = mips
CPU = MIPS32
TOOL_FAMILY = diab
TOOL = sfdiable
TOOL_PATH = 
CC_ARCH_SPEC = -tMIPS2MS:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),MIPS32sfgnu_RTP)
VX_CPU_FAMILY = mips
CPU = MIPS32
TOOL_FAMILY = gnu
TOOL = sfgnu
TOOL_PATH = 
CC_ARCH_SPEC = -G 0 -mno-branch-likely -mips2 -EB
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),MIPS32sfgnule_RTP)
VX_CPU_FAMILY = mips
CPU = MIPS32
TOOL_FAMILY = gnu
TOOL = sfgnule
TOOL_PATH = 
CC_ARCH_SPEC = -G 0 -mno-branch-likely -mips2 -EL
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),MIPS64diab_RTP)
VX_CPU_FAMILY = mips
CPU = MIPS64
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tMIPS3XH:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),MIPS64diable_RTP)
VX_CPU_FAMILY = mips
CPU = MIPS64
TOOL_FAMILY = diab
TOOL = diable
TOOL_PATH = 
CC_ARCH_SPEC = -tMIPS3ZH:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),MIPS64gnu_RTP)
VX_CPU_FAMILY = mips
CPU = MIPS64
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -G 0 -mno-branch-likely -mips3 -mabi=o64 -mgp64 -EB
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),MIPS64gnule_RTP)
VX_CPU_FAMILY = mips
CPU = MIPS64
TOOL_FAMILY = gnu
TOOL = gnule
TOOL_PATH = 
CC_ARCH_SPEC = -G 0 -mno-branch-likely -mips3 -mabi=o64 -mgp64 -EL
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PENTIUM2diab_RTP)
VX_CPU_FAMILY = pentium
CPU = PENTIUM2
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPENTIUM2LH:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PENTIUM2gnu_RTP)
VX_CPU_FAMILY = pentium
CPU = PENTIUM2
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mtune=i486 -march=i486
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PENTIUM3diab_RTP)
VX_CPU_FAMILY = pentium
CPU = PENTIUM3
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPENTIUM3LH:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PENTIUM3gnu_RTP)
VX_CPU_FAMILY = pentium
CPU = PENTIUM3
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mtune=i486 -march=i486
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PENTIUM4diab_RTP)
VX_CPU_FAMILY = pentium
CPU = PENTIUM4
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPENTIUM4LH:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PENTIUM4gnu_RTP)
VX_CPU_FAMILY = pentium
CPU = PENTIUM4
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mtune=i486 -march=i486
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PENTIUMdiab_RTP)
VX_CPU_FAMILY = pentium
CPU = PENTIUM
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPENTIUMLH:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PENTIUMgnu_RTP)
VX_CPU_FAMILY = pentium
CPU = PENTIUM
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mtune=i486 -march=i486
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PPC32diab_RTP)
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPCEH:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PPC32gnu_RTP)
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mhard-float -mstrict-align -mregnames
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PPC32sfdiab_RTP)
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = diab
TOOL = sfdiab
TOOL_PATH = 
CC_ARCH_SPEC = -tPPCES:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),PPC32sfgnu_RTP)
VX_CPU_FAMILY = ppc
CPU = PPC32
TOOL_FAMILY = gnu
TOOL = sfgnu
TOOL_PATH = 
CC_ARCH_SPEC = -msoft-float -mstrict-align -mregnames
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),SH32diab_RTP)
VX_CPU_FAMILY = sh
CPU = SH32
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tSH4EH:rtp -Xunderscore-leading
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),SH32diable_RTP)
VX_CPU_FAMILY = sh
CPU = SH32
TOOL_FAMILY = diab
TOOL = diable
TOOL_PATH = 
CC_ARCH_SPEC = -tSH4LH:rtp -Xunderscore-leading
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),SH32gnu_RTP)
VX_CPU_FAMILY = sh
CPU = SH32
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -m4 -D__sh
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),SH32gnule_RTP)
VX_CPU_FAMILY = sh
CPU = SH32
TOOL_FAMILY = gnu
TOOL = gnule
TOOL_PATH = 
CC_ARCH_SPEC = -m4 -ml -Wl,-EL -D__sh
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),SIMPENTIUMdiab_RTP)
VX_CPU_FAMILY = simpentium
CPU = SIMPENTIUM
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tX86LH:rtpsim
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),SIMPENTIUMgnu_RTP)
VX_CPU_FAMILY = simpentium
CPU = SIMPENTIUM
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -mtune=i486 -march=i486
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab_RTP)
VX_CPU_FAMILY = simso
CPU = SIMSPARCSOLARIS
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tSPARCFH:rtpsim
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu_RTP)
VX_CPU_FAMILY = simso
CPU = SIMSPARCSOLARIS
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = 
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),XSCALEdiab_RTP)
VX_CPU_FAMILY = arm
CPU = XSCALE
TOOL_FAMILY = diab
TOOL = diab
TOOL_PATH = 
CC_ARCH_SPEC = -tARMXLS:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),XSCALEdiabbe_RTP)
VX_CPU_FAMILY = arm
CPU = XSCALE
TOOL_FAMILY = diab
TOOL = diabbe
TOOL_PATH = 
CC_ARCH_SPEC = -tARMXES:rtp
LIBPATH = 
LIBS = -lstlstd

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),XSCALEgnu_RTP)
VX_CPU_FAMILY = arm
CPU = XSCALE
TOOL_FAMILY = gnu
TOOL = gnu
TOOL_PATH = 
CC_ARCH_SPEC = -txscale
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif

ifeq ($(BUILD_SPEC),XSCALEgnube_RTP)
VX_CPU_FAMILY = arm
CPU = XSCALE
TOOL_FAMILY = gnu
TOOL = gnube
TOOL_PATH = 
CC_ARCH_SPEC = -txscalebe  -Wa,-EB
LIBPATH = 
LIBS = -lstdc++

IDE_INCLUDES = -I$(WIND_USR)/h -I$(WIND_USR)/h/wrn/coreip -IC:/Temp/Test/VxWorks/libRegex 
endif


ifeq ($(BUILD_SPEC),ARMARCH5diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5diabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall -msoft-float -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall -msoft-float -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2  -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2  -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2  -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32diable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32gnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMPENTIUMdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMPENTIUMgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsparc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C-Compiler = -g
else
DEBUGFLAGS_C-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.c
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_C-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5diabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall -msoft-float -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall -msoft-float -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall -msoft-float -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall -msoft-float -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall -msoft-float -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall -msoft-float -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall -msoft-float -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall -msoft-float -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++mips $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2  -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2  -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2  -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++ppc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32diable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32gnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sh $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMPENTIUMdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMPENTIUMgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++pentium $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sparc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sparc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sparc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++sparc $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dplus $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -Xansi -Xforce-declarations  -Xmake-dependency=0xd -Xpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_C++-Compiler = -g
else
DEBUGFLAGS_C++-Compiler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cpp
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.C
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cxx
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.cc
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)c++arm $(DEBUGFLAGS_C++-Compiler) $(CC_ARCH_SPEC) -ansi -mrtp -Wall  -MD -MP -fpic $(ADDED_C++FLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5diabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH5gnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6diabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),ARMARCH6gnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfdiable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS32sfgnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL -DSOFT_FLOAT  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64diable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),MIPS64gnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccmips $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DMIPSEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM2gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM3gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2  -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUM4gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2  -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PENTIUMgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2  -fno-builtin 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),PPC32sfgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccppc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xalign-power2 -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32diable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xalign-power2 -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SH32gnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsh $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -D_SH7750  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMPENTIUMdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space -Wa,-Xmnem-mit -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMPENTIUMgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fno-builtin -fno-defer-pop
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccpentium $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccsparc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEL  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEdiabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -XO 
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dcc $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -Xansi -Xpreprocess-assembly -Xcpp-no-space  -Xmake-dependency=0xd -Xpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL) -DARMEB  $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif
ifeq ($(BUILD_SPEC),XSCALEgnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_Assembler = -g
else
DEBUGFLAGS_Assembler = -O2 -fstrength-reduce -fno-builtin
endif
$(OBJ_DIR)/%.sho : $(SRC_DIR)/%.s
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ccarm $(DEBUGFLAGS_Assembler) $(CC_ARCH_SPEC) -ansi -mrtp -P -xassembler-with-cpp -MD -MP -fpic $(ADDED_CFLAGS) $(IDE_INCLUDES) $(ADDED_INCLUDES) -DCPU=$(CPU) -DTOOL_FAMILY=$(TOOL_FAMILY) -DTOOL=$(TOOL)   $(DEFINES) -o "$@" -c "$<"

endif

ifeq ($(BUILD_SPEC),ARMARCH5diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),ARMARCH5diabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),ARMARCH5gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ararm crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),ARMARCH5gnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ararm crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),ARMARCH6diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),ARMARCH6diabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),ARMARCH6gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ararm crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),ARMARCH6gnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ararm crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),MIPS32sfdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),MIPS32sfdiable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),MIPS32sfgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)armips crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),MIPS32sfgnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)armips crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),MIPS64diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),MIPS64diable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),MIPS64gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)armips crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),MIPS64gnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)armips crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PENTIUM2diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PENTIUM2gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)arpentium crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PENTIUM3diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PENTIUM3gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)arpentium crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PENTIUM4diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PENTIUM4gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)arpentium crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PENTIUMdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PENTIUMgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)arpentium crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PPC32diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PPC32gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)arppc crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PPC32sfdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),PPC32sfgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)arppc crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),SH32diab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),SH32diable_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),SH32gnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)arsh crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),SH32gnule_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)arsh crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),SIMPENTIUMdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),SIMPENTIUMgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)arpentium crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),SIMSPARCSOLARISgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)arsparc crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),XSCALEdiab_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),XSCALEdiabbe_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)dar crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),XSCALEgnu_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ararm crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif
ifeq ($(BUILD_SPEC),XSCALEgnube_RTP)
ifeq ($(DEBUG_MODE),1)
DEBUGFLAGS_libRegex = 
else
DEBUGFLAGS_libRegex = 
endif
OBJECTS_TARGETS_libRegex = $(OBJ_DIR)/pcre_get.sho $(OBJ_DIR)/pcre_ucd.sho \
	 $(OBJ_DIR)/pcre_ord2utf8.sho $(OBJ_DIR)/pcre_newline.sho \
	 $(OBJ_DIR)/pcre_xclass.sho $(OBJ_DIR)/pcre_chartables.sho \
	 $(OBJ_DIR)/pcre_globals.sho $(OBJ_DIR)/pcre_compile.sho \
	 $(OBJ_DIR)/pcre_exec.sho $(OBJ_DIR)/pcre_info.sho \
	 $(OBJ_DIR)/pcrecpp.sho $(OBJ_DIR)/pcre_config.sho \
	 $(OBJ_DIR)/pcre_dfa_exec.sho $(OBJ_DIR)/pcre_refcount.sho \
	 $(OBJ_DIR)/pcreposix.sho $(OBJ_DIR)/pcre_tables.sho \
	 $(OBJ_DIR)/pcre_maketables.sho $(OBJ_DIR)/pcre_version.sho \
	 $(OBJ_DIR)/pcre_try_flipped.sho $(OBJ_DIR)/pcre_study.sho \
	 $(OBJ_DIR)/pcre_fullinfo.sho $(OBJ_DIR)/pcre_valid_utf8.sho
$(OBJ_DIR)/libRegex.a : $(OBJECTS_TARGETS_libRegex)
	$(TRACE_FLAG)echo "building $@"; $(TOOL_PATH)ararm crus "$@" $(OBJECTS_TARGETS_libRegex)

target_libRegex : check_objectdir $(OBJ_DIR)/libRegex.a
endif



WIND_SCOPETOOLS_BASE := $(subst \,/,$(WIND_SCOPETOOLS_BASE))


-include *.makefile

main_all : check_objectdir external_build $(PROJECT_TARGETS)
	@echo "make: built targets of `pwd`"

check_objectdir :
	@if [ ! -d "$(OBJ_DIR)" ]; then\
		mkdir -p $(OBJ_DIR);\
	fi

# entry point for extending the build
external_build ::
	@echo ""

# main entry point for pre processing prior to the recursion
pre_recursion ::
	@echo ""

# main entry point for post processing after the recursion
post_recursion ::
	@echo ""

# main entry point for pre processing prior to the build
pre_build :: $(PRE_BUILD_STEP) generate_sources
	@echo ""

# entry point for generating sources prior to the build
generate_sources ::
	@echo ""

# main entry point for post processing after the build
post_build :: $(POST_BUILD_STEP) deploy_output
	@echo ""

# entry point for deploying output after the build
deploy_output ::
	@echo ""

# recursive make in SUBDIRS
subdirs_all :
	@_PWD=`pwd`;\
	for dir in _dummy_ $(SUBDIRS); do\
		if [ "$$dir" = "_dummy_" ]; then\
			continue ;\
		fi;\
		if [ ! -d "$$dir" ]; then\
			continue ;\
		fi;\
		echo "Recursive make: Changing to Directory '$$dir'";\
		cd "$$dir";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) all || exit;\
		echo "Recursive make: Changing back to Directory '$$_PWD'";\
		cd "$$_PWD";\
	done

clean ::
	@_PWD=`pwd`;\
	for dir in _dummy_ $(SUBDIRS); do\
		if [ "$$dir" = "_dummy_" ]; then\
			continue ;\
		fi;\
		if [ ! -d "$$dir" ]; then\
			continue ;\
		fi;\
		echo "Recursive make: Changing to Directory '$$dir'";\
		cd "$$dir";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) $@ || exit;\
		echo "Recursive make: Changing back to Directory '$$_PWD'";\
		cd "$$_PWD";\
	done

clean :: external_clean $(CLEAN_STEP) _clean

# entry point for extending the build clean
external_clean ::
	@echo ""

_clean :
	@echo "make: removing targets and objects of `pwd`";\
	rm -f $(OBJECTS) $(PROJECT_TARGETS) $(DEP_FILES) $(wildcard $(OBJ_DIR)/*.unstripped) $(wildcard $(OBJ_DIR)/ctdt.*)

build_all_specs :
	@echo "building target default for ALL build-specs";\
	for spec in _dummy_ $(ALL_BUILD_SPECS); do\
		if [ "$$spec" = "_dummy_" ]; then\
			continue ;\
		fi;\
		echo " ";\
		echo "building all for build-spec '$$spec'";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) BUILD_SPEC=$$spec DEBUG_MODE=$(DEBUG_MODE) TRACE=$(TRACE) || exit;\
	done

clean_all_specs :
	@echo "building target clean for ALL build-specs";\
	for spec in _dummy_ $(ALL_BUILD_SPECS); do\
		if [ "$$spec" = "_dummy_" ]; then\
			continue ;\
		fi;\
		echo " ";\
		echo "building clean for build-spec '$$spec'";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) BUILD_SPEC=$$spec DEBUG_MODE=$(DEBUG_MODE) TRACE=$(TRACE) clean || exit;\
	done

build_enabled_specs :
	@echo "building target default for ENABLED build-specs";\
	for spec in _dummy_ $(ENABLED_BUILD_SPECS); do\
		if [ "$$spec" = "_dummy_" ]; then\
			continue ;\
		fi;\
		echo " ";\
		echo "building all for build-spec '$$spec'";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) BUILD_SPEC=$$spec DEBUG_MODE=$(DEBUG_MODE) TRACE=$(TRACE) || exit;\
	done

clean_enabled_specs :
	@echo "building target clean for ENABLED build-specs";\
	for spec in _dummy_ $(ENABLED_BUILD_SPECS); do\
		if [ "$$spec" = "_dummy_" ]; then\
			continue ;\
		fi;\
		echo " ";\
		echo "building clean for build-spec '$$spec'";\
		"$(MAKE)" -f "$(MAKEFILE)" $(MFLAGS) BUILD_SPEC=$$spec DEBUG_MODE=$(DEBUG_MODE) TRACE=$(TRACE) clean || exit;\
	done
