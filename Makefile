#
# OMNeT++/OMNEST Makefile for opp_dns_extension
#
# This file was generated with the command:
#  opp_makemake -f -e cpp --deep
#

# Name of target to be created (-o option)
TARGET = opp_dns_extension$(EXE_SUFFIX)

# User interface (uncomment one) (-u option)
USERIF_LIBS = $(ALL_ENV_LIBS) # that is, $(TKENV_LIBS) $(CMDENV_LIBS)
#USERIF_LIBS = $(CMDENV_LIBS)
#USERIF_LIBS = $(TKENV_LIBS)

# C++ include paths (with -I)
INCLUDE_PATH = \
    -I. \
    -Isimulations \
    -Isrc \
    -Isrc/common \
    -Isrc/messages \
    -Isrc/tests \
    -Isrc/tests/unit \
    -Isrc/tests/unit/utils \
    -Isrc/utils

# Additional object and library files to link with
EXTRA_OBJS =

# Additional libraries (-L, -l options)
LIBS =

# Output directory
PROJECT_OUTPUT_DIR = out
PROJECTRELATIVE_PATH =
O = $(PROJECT_OUTPUT_DIR)/$(CONFIGNAME)/$(PROJECTRELATIVE_PATH)

# Object files for local .cpp and .msg files
OBJS = $O/src/utils/DNSTools.o $O/src/messages/DNSPacket_m.o

# Message files
MSGFILES = \
    src/messages/DNSPacket.msg

#------------------------------------------------------------------------------

# Pull in OMNeT++ configuration (Makefile.inc or configuser.vc)

ifneq ("$(OMNETPP_CONFIGFILE)","")
CONFIGFILE = $(OMNETPP_CONFIGFILE)
else
ifneq ("$(OMNETPP_ROOT)","")
CONFIGFILE = $(OMNETPP_ROOT)/Makefile.inc
else
CONFIGFILE = $(shell opp_configfilepath)
endif
endif

ifeq ("$(wildcard $(CONFIGFILE))","")
$(error Config file '$(CONFIGFILE)' does not exist -- add the OMNeT++ bin directory to the path so that opp_configfilepath can be found, or set the OMNETPP_CONFIGFILE variable to point to Makefile.inc)
endif

include $(CONFIGFILE)

# Simulation kernel and user interface libraries
OMNETPP_LIB_SUBDIR = $(OMNETPP_LIB_DIR)/$(TOOLCHAIN_NAME)
OMNETPP_LIBS = -L"$(OMNETPP_LIB_SUBDIR)" -L"$(OMNETPP_LIB_DIR)" -loppmain$D $(USERIF_LIBS) $(KERNEL_LIBS) $(SYS_LIBS)

COPTS = $(CFLAGS)  $(INCLUDE_PATH) -I$(OMNETPP_INCL_DIR)
MSGCOPTS = $(INCLUDE_PATH)

# we want to recompile everything if COPTS changes,
# so we store COPTS into $COPTS_FILE and have object
# files depend on it (except when "make depend" was called)
COPTS_FILE = $O/.last-copts
ifneq ($(MAKECMDGOALS),depend)
ifneq ("$(COPTS)","$(shell cat $(COPTS_FILE) 2>/dev/null || echo '')")
$(shell $(MKPATH) "$O" && echo "$(COPTS)" >$(COPTS_FILE))
endif
endif

#------------------------------------------------------------------------------
# User-supplied makefile fragment(s)
# >>>
# <<<
#------------------------------------------------------------------------------

# Main target
all: $O/$(TARGET)
	$(Q)$(LN) $O/$(TARGET) .

$O/$(TARGET): $(OBJS)  $(wildcard $(EXTRA_OBJS)) Makefile
	@$(MKPATH) $O
	@echo Creating executable: $@
	$(Q)$(CXX) $(LDFLAGS) -o $O/$(TARGET)  $(OBJS) $(EXTRA_OBJS) $(AS_NEEDED_OFF) $(WHOLE_ARCHIVE_ON) $(LIBS) $(WHOLE_ARCHIVE_OFF) $(OMNETPP_LIBS)

.PHONY: all clean cleanall depend msgheaders

.SUFFIXES: .cpp

$O/%.o: %.cpp $(COPTS_FILE)
	@$(MKPATH) $(dir $@)
	$(qecho) "$<"
	$(Q)$(CXX) -c $(CXXFLAGS) $(COPTS) -o $@ $<

%_m.cpp %_m.h: %.msg
	$(qecho) MSGC: $<
	$(Q)$(MSGC) -s _m.cpp $(MSGCOPTS) $?

msgheaders: $(MSGFILES:.msg=_m.h)

clean:
	$(qecho) Cleaning...
	$(Q)-rm -rf $O
	$(Q)-rm -f opp_dns_extension opp_dns_extension.exe libopp_dns_extension.so libopp_dns_extension.a libopp_dns_extension.dll libopp_dns_extension.dylib
	$(Q)-rm -f ./*_m.cpp ./*_m.h
	$(Q)-rm -f simulations/*_m.cpp simulations/*_m.h
	$(Q)-rm -f src/*_m.cpp src/*_m.h
	$(Q)-rm -f src/common/*_m.cpp src/common/*_m.h
	$(Q)-rm -f src/messages/*_m.cpp src/messages/*_m.h
	$(Q)-rm -f src/tests/*_m.cpp src/tests/*_m.h
	$(Q)-rm -f src/tests/unit/*_m.cpp src/tests/unit/*_m.h
	$(Q)-rm -f src/tests/unit/utils/*_m.cpp src/tests/unit/utils/*_m.h
	$(Q)-rm -f src/utils/*_m.cpp src/utils/*_m.h

cleanall: clean
	$(Q)-rm -rf $(PROJECT_OUTPUT_DIR)

depend:
	$(qecho) Creating dependencies...
	$(Q)$(MAKEDEPEND) $(INCLUDE_PATH) -f Makefile -P\$$O/ -- $(MSG_CC_FILES)  ./*.cpp simulations/*.cpp src/*.cpp src/common/*.cpp src/messages/*.cpp src/tests/*.cpp src/tests/unit/*.cpp src/tests/unit/utils/*.cpp src/utils/*.cpp

# DO NOT DELETE THIS LINE -- make depend depends on it.
$O/src/messages/DNSPacket_m.o: src/messages/DNSPacket_m.cpp \
  src/messages/../common/DNS.h \
  src/messages/DNSPacket_m.h
$O/src/utils/DNSTools.o: src/utils/DNSTools.cpp \
  src/utils/../messages/DNSPacket_m.h \
  src/utils/../common/DNS.h \
  src/utils/../messages/../common/DNS.h \
  src/utils/DNSTools.h
