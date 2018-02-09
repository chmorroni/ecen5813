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
PLATFORM_FLAGS:=-mthumb -mcpu=cortex-m0plus -mfpu=fpv4-sp-d16 --specs=nosys.specs -DPLATFORM_KL25Z
TARGET:=project1-kl25z.elf
PLATFORM_LDFLAGS:=-T ../platform/MKL25Z128xxx4_flash.ld
INCLUDE_FLAGS:=-I../include/cmsis -I../include/kl25z -I../include/common
endif

ifeq ($(PLATFORM),BBB)
CC:=arm-linux-gnueabi-gcc
CPP:=arm-linux-gnueabi-cpp
AS:=arm-linux-gnueabi-as
LD:=arm-linux-gnueabi-ld
PLATFORM_FLAGS:=-DPLATFORM_BBB
TARGET:=project1-bbb.elf
INCLUDE_FLAGS:=-I../include/common
endif

ifeq ($(PLATFORM),HOST)
CC:=gcc
CPP:=cpp
AS:=as
LD:=ld
PLATFORM_FLAGS:=-DPLATFORM_HOST
TARGET:=project1-host.elf
INCLUDE_FLAGS:=-I../include/common
endif

# Override Make default GCC toolchain

CFLAGS:=-Wall -Werror -g -O0 -std=c99 -DPROJECT1 $(PLATFORM_FLAGS) $(INCLUDE_FLAGS)
LDFLAGS:=-std=c99  $(PLATFORM_LDFLAGS) $(PLATFORM_FLAGS)
CPPFLAGS:=-std=c99 $(PLATFORM_FLAGS) $(INCLUDE_FLAGS)

# Grab CSRC and SSRC variables from sources.mk
include sources.mk

# Only generate .d/.i files from C files
DEPFILES:=$(CSRC:.c=.d)
PREFILES:=$(CSRC:.c=.i)
# These assembly files are the ones generated from C files and can be cleaned
ASMFILES:=$(CSRC:.c=.asm)
# Assembly that's written on its own is in SSRC so it isn't cleaned
OBJFILES:=$(ASMFILES:.asm=.o) $(SSRC:.S=.o)

.PHONY: clean redo build compile-all

build: compile-all
	$(CC) $(LDFLAGS) $(OBJFILES) -o $(TARGET)

compile-all: $(OBJFILES)

clean:
	rm -f $(OBJFILES)
	rm -f $(PREFILES)
	rm -f $(ASMFILES)
	rm -f $(DEPFILES)
	rm -f project1-host.elf project1-bbb.elf project1-kl25z.elf

redo: clean build

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

# Make preprocessed file from C file
%.i: %.c
	$(CC) $(CPPFLAGS) -E $< -o $@

# Make assembly file from C file
%.asm: %.c
	$(CC) $(CFLAGS) -S $< -o $@

