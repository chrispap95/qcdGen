# Makefile is a part of the PYTHIA event generator.
# Copyright (C) 2018 Torbjorn Sjostrand.
# PYTHIA is licenced under the GNU GPL v2 or later, see COPYING for details.
# Please respect the MCnet Guidelines, see GUIDELINES for details.
# Author: Philip Ilten, September 2014.
#
# This is is the Makefile used to build PYTHIA examples on POSIX systems.
# Example usage is:
#     make main01
# For help using the make command please consult the local system documentation,
# i.e. "man make" or "make --help".

################################################################################
# VARIABLES: Definition of the relevant variables from the configuration script.
################################################################################

# Set the shell.
SHELL=/usr/bin/env bash

# Include the configuration.
-include Makefile.inc

# Handle GZIP support.
GZIP_INC=
GZIP_FLAGS=
ifeq ($(GZIP_USE),true)
  GZIP_INC+= -DGZIPSUPPORT -I$(GZIP_INCLUDE)
  GZIP_FLAGS+= -L$(GZIP_LIB) -Wl,-rpath,$(GZIP_LIB) -lz
endif

# Check distribution (use local version first, then installed version).
ifneq ("$(wildcard ../lib/libpythia8.*)","")
  PREFIX_LIB=../lib
  PREFIX_INCLUDE=../include
endif
CXX_COMMON:=-I$(PREFIX_INCLUDE) $(CXX_COMMON)
CXX_COMMON+= -L$(PREFIX_LIB) -Wl,-rpath,$(PREFIX_LIB) -lpythia8 -ldl

################################################################################
# RULES: Definition of the rules used to build the PYTHIA examples.
################################################################################

# Rules without physical targets (secondary expansion for specific rules).
.SECONDEXPANSION:
.PHONY: all clean

# All targets (no default behavior).
all: qcdGen

# The Makefile configuration.
Makefile.inc:
	$(error Error: PYTHIA must be configured, please run "./configure"\
                in the top PYTHIA directory)

# PYTHIA libraries.
$(PREFIX_LIB)/libpythia8.a :
	$(error Error: PYTHIA must be built, please run "make"\
                in the top PYTHIA directory)

qcdGen: $$@.cc $(PREFIX_LIB)/libpythia8.a qcdGen.so
ifeq ($(ROOT_USE),true)
	$(CXX) $< qcdGen.so -o $@ -w -I$(ROOT_INCLUDE) $(CXX_COMMON)\
	 `$(ROOT_BIN)/root-config --cflags` -Wl,-rpath,./\
	 -Wl,-rpath,$(ROOT_LIB) `$(ROOT_BIN)/root-config --glibs`
else
	@echo "Error: $@ requires ROOT"
endif
qcdGen.so: qcdGenDct.cc $(PREFIX_LIB)/libpythia8.a
	$(CXX) $< -o $@ -w -I$(ROOT_INCLUDE) $(CXX_SHARED) $(CXX_COMMON)\
	 `$(ROOT_BIN)/root-config --cflags`
qcdGenDct.cc: qcdGen.h qcdGenLinkDef.h
	export LD_LIBRARY_PATH=$$LD_LIBRARY_PATH:$(ROOT_LIB);\
	 $(ROOT_BIN)/rootcint -f $@ -c -I$(PREFIX_INCLUDE) $^

# Clean.
clean:
	@rm -f qcdGen; rm -f qcd.root; rm -f *~; rm -f \#*; rm -f *Dct.*;\
	rm -f *.so; rm -f *Dct_rdict.pcm
