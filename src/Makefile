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
PLATFORM_FLAGS:=-mthumb -mcpu=cortex-m0plus -mfpu=fpv4-sp-d16 --specs=nosys.specs -map=project1.map
TARGET:=project1-kl25z.elf
PLATFORM_LDFLAGS:=-T ../include/kl25z/MKL25Z128xxx4_flash.ld
INCLUDE_FLAGS:=-I../include/cmsis -I../include/kl25z -I../include/common
endif

ifeq ($(PLATFORM),BBB)
CC:=arm-linux-gnueabi-gcc
CPP:=arm-linux-gnueabi-cpp
AS:=arm-linux-gnueabi-as
LD:=arm-linux-gnueabi-ld
TARGET:=project1-bbb.elf
INCLUDE_FLAGS:=-I../include/common
endif

ifeq ($(PLATFORM),HOST)
CC:=gcc
CPP:=cpp
AS:=as
LD:=ld
TARGET:=project1-host.elf
INCLUDE_FLAGS:=-I../include/common
endif

# Override Make default GCC toolchain

CFLAGS:=-Wall -Werror -g -O0 -std=c99 $(PLATFORM_FLAGS) $(INCLUDE_FLAGS)
LDFLAGS:=-std=c99  $(PLATFORM_LDFLAGS) $(PLATFORM_FLAGS)
CPPFLAGS:=-std=c99 $(PLATFORM_FLAGS)

# Grab SOURCES variable from sources.mk
include sources.mk

DEPFILES:=$(SOURCES:.c=.d)
PREFILES:=$(SOURCES:.c=.i)
ASMFILES:=$(SOURCES:.c=.S)
OBJFILES:=$(ASMFILES:.S=.o)

.PHONY: clean redo build compile-all

compile-all: $(OBJFILES)

build: compile-all
	$(CC) $(CFLAGS) $(OBJFILES) -o $(TARGET)

clean:
	rm -f $(OBJFILES)
	rm -f $(PREFILES)
	rm -f $(ASMFILES)
	rm -f $(DEPFILES)
	rm -f $(TARGET)

redo: clean build

# Include auto-generated dependency files if they are available
# This will trigger a rebuild of object files if their sources change
# without needlessly rebuilding object files
-include $(DEPFILES)

# Make object file from C file without generating intermediate files
# Also generate dependency file if the build succeeds
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	$(CC) $(INCLUDE_FLAGS) -M $< -o $*.d

# Make preprocessed file from C file
%.i: %.c
	$(CC) $(CPPFLAGS) -E $< -o $@

# Make assembly file from C file
%.asm: %.c
	$(CC) $(CFLAGS) -S $< -o $@

