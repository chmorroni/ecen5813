#-----------------------------------------------------------------------------
# Copyright (C) 2018
# Christopher Morroni and Matthew Haney
# University of Colorado, Boulder
#
# Redistribution, modification, or use of this software in source or binary
# forms is permitted as long as the files maintain this copyright. Users are
# permitted to modify this and use it to learn about the field of embedded
# software. Christopher Morroni, Matthew Haney, and the University of
# Colorado are not liable for any misuse of this material.
#
#-----------------------------------------------------------------------------

#-----------------------------------------------------------------------------
# Usage: make [TARGET] [OVERRIDES]
#
# Build Targets:
#     <FILE> - Builds <FILE> object file
#     build - Builds and links all source files
#     compile-all - Compiles to object files, but stops before linking
#     clean - Removes all generated files
#     redo - Cleans then rebuilds
#     install - Builds then installs on target
#     uninstall - Uninstalls from target
#     debug - Builds then debugs on target
#     test - Builds and runs cmocka unit tests
#     testclean - Cleans files generated for unit tests
#
# Overrides:
#     PLATFORM - Platform for build (HOST, BBB, KL25Z)
#     VERBOSE - Include extra print statements (TRUE, assumes false)
#
#-----------------------------------------------------------------------------

############################
# PLATFORM-DEPENDENT FLAGS #
############################

# If no platform specified: default to HOST and notify user
ifndef PLATFORM
PLATFORM:=HOST
$(info Defaulting to PLATFORM=HOST (other options: KL25Z, BBB))
endif

# Switch toolchain executables based on compile-time PLATFORM flag
ifeq ($(PLATFORM),KL25Z)
CC:=arm-none-eabi-gcc
CPP:=arm-none-eabi-cpp
AS:=arm-none-eabi-as
LD:=arm-none-eabi-ld
SIZE:=arm-none-eabi-size
PLATFORM_FLAGS:=-mthumb -mcpu=cortex-m0plus -specs=nosys.specs -DPLATFORM_KL25Z
TARGET:=project3-kl25z.srec
SECONDARY_TARGET:=$(TARGET:.srec=.elf)
PLATFORM_LDFLAGS:=-T platform/MKL25Z128xxx4_flash.ld
INCLUDE_FLAGS:=-Iinclude/cmsis -Iinclude/kl25z -Iinclude/common
MAPFILE:=project3.map
INSTALL_FLAGS=-n KL25Z -b $(TARGET)
DEBUG_FLAGS=-b $(SECONDARY_TARGET)
endif

ifeq ($(PLATFORM),BBB)
CC:=arm-linux-gnueabi-gcc
CPP:=arm-linux-gnueabi-cpp
AS:=arm-linux-gnueabi-as
LD:=arm-linux-gnueabi-ld
SIZE:=arm-linux-gnueabi-size
PLATFORM_FLAGS:=-DPLATFORM_BBB
PLATFORM_LDFLAGS:=-static
TARGET:=project3-bbb.elf
INCLUDE_FLAGS:=-Iinclude/common
BBB_ADDRESS:=192.168.7.2
MAPFILE:=project3.map
INSTALL_PATH:=/home/debian/bin
INSTALL_FLAGS=$(BBB_ADDRESS) $(TARGET) $(INSTALL_PATH) # Needs to be recursive
DEBUG_FLAGS=-b $(TARGET)
endif

ifeq ($(PLATFORM),HOST)
CC:=gcc
CPP:=cpp
AS:=as
LD:=ld
SIZE:=size
PLATFORM_FLAGS:=-DPLATFORM_HOST
TARGET:=project3.elf
INCLUDE_FLAGS:=-Iinclude/common
MAPFILE:=project3.map
INSTALL_PATH:=/usr/local/bin
INSTALL_FLAGS=-e $(TARGET) -p $(INSTALL_PATH) -f
DEBUG_FLAGS=-b $(TARGET)
endif

ifeq ($(VERBOSE),TRUE)
PLATFORM_FLAGS+=-DDEBUG
endif

######################
# NORMAL BUILD FLAGS #
######################

# Grab CSRC and SSRC variables from sources.mk
include src/sources.mk
# These sources come from the `src` directory
CSRC:=$(addprefix src/,$(CSRC))
SSRC:=$(addprefix src/,$(SSRC))

# Dependency and preprocessed files can be generated from all sources
DEPFILES:=$(CSRC:.c=.d) $(SSRC:.S=.d)
PREFILES:=$(CSRC:.c=.i) $(SSRC:.S=.i)
# These assembly files are the ones generated from C files and can be cleaned
# Assembly that's handwritten is in SSRC so it isn't cleaned
ASMFILES:=$(CSRC:.c=.asm)
OBJFILES:=$(CSRC:.c=.o) $(SSRC:.S=.o)

# Place output in the `build` directory
TARGET:=$(addprefix build/,$(TARGET))
SECONDARY_TARGET:=$(addprefix build/,$(SECONDARY_TARGET))
MAPFILE:=$(addprefix build/,$(MAPFILE))

# Compiler options
CFLAGS:=-Wall -Werror -g -O0 -std=c99 -DPROJECT3 $(PLATFORM_FLAGS) $(INCLUDE_FLAGS)
LDFLAGS:=-std=c99 -g -O0 $(PLATFORM_LDFLAGS) $(PLATFORM_FLAGS) -Xlinker -Map=$(MAPFILE)
CPPFLAGS:=-std=c99 $(PLATFORM_FLAGS) $(INCLUDE_FLAGS)

# Installation options
SH:=/bin/sh

######################
# UNIT TESTING FLAGS #
######################

TEST_CFLAGS:=-Wall -Werror -g -O0 -std=c99 $(INCLUDE_FLAGS)

# Get TEST_SOURCE from src/test/sources.mk
include src/test/sources.mk
TEST_SOURCE:=$(addprefix src/test/,$(TEST_SOURCE))
TEST_OBJ:=$(TEST_SOURCE:.c=.o)
TEST_DEPS:=$(addprefix src/,$(TEST_DEPS))
TEST_DEP_OBJ:=$(TEST_DEPS:.c=.o)
TEST_DEPS:=$(TEST_SOURCE:.c=.d)

#########
# RULES #
#########

.PHONY: clean redo build compile-all install uninstall test

.SECONDARY: $(SECONDARY_TARGET)

build: $(TARGET)

compile-all: $(OBJFILES)

clean:
	rm -f $(OBJFILES)
	rm -f $(PREFILES)
	rm -f $(ASMFILES)
	rm -f $(DEPFILES)
	rm -f $(MAPFILE)
	rm -f $(SECONDARY_TARGET)
	rm -f $(TARGET)

redo: clean build

install: $(TARGET)
	$(SH) script/install_$(PLATFORM).sh $(INSTALL_FLAGS)

uninstall:
	$(SH) script/install_$(PLATFORM).sh $(INSTALL_FLAGS) -u

debug: $(TARGET)
	$(SH) script/debug_$(PLATFORM).sh $(DEBUG_FLAGS)

test: $(TEST_DEP_OBJ) $(TEST_OBJ)
	$(CC) $(TEST_CFLAGS) $(TEST_OBJ) $(TEST_DEP_OBJ) -o build/test -l cmocka
	build/test

testclean:
	rm -f $(TEST_DEPS)
	rm -f $(TEST_OBJ)
	rm -f $(TEST_DEP_OBJ)
	rm -f $(DEPFILES)
	rm -f build/test

-include $(TEST_DEPS)

# Include auto-generated dependency files if they are available
# This will trigger a rebuild of object files if their sources change
# without needlessly rebuilding object files
-include $(DEPFILES)

# Make object file from C file without generating intermediate files
# Also generate dependency file if the build succeeds
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -M $< -o $*.d

# Make object file from assembly file
%.o: %.S
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(CFLAGS) -M $< -o $*.d

# Make preprocessed file from C file
%.i: %.c
	$(CC) $(CPPFLAGS) -E $< -o $@

# Make preprocessed file from assembly file
%.i: %.S
	$(CC) $(CPPFLAGS) -E $< -o $@

# Make assembly file from C file
%.asm: %.c
	$(CC) $(CFLAGS) -S $< -o $@

%.elf: $(OBJFILES)
	$(CC) $(LDFLAGS) $^ -o $@
	$(SIZE) $@

%.srec: %.elf
	arm-none-eabi-objcopy $< -O srec $@
	$(SIZE) $@
