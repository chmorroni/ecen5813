# Switch toolchain executables based on compile-time PLATFORM flag
ifndef PLATFORM
$(error Specify a platform through the PLATFORM flag. Options are KL25Z, BBB, and HOST)
endif

ifeq ($(PLATFORM),KL25Z)
CC:=arm-none-eabi-gcc
CPP:=arm-none-eabi-cpp
AS:=arm-none-eabi-as
LD:=arm-none-eabi-ld
PLATFORM_FLAGS:=-mthumb -mcpu=cortex-m0plus -mfpu=fpv4-sp-d16 --specs=nosys.specs -map=project1.map
TARGET:=project1-kl25z.elf
endif

ifeq ($(PLATFORM),BBB)
CC:=arm-linux-gnueabi-gcc
CPP:=arm-linux-gnueabi-cpp
AS:=arm-linux-gnueabi-as
LD:=arm-linux-gnueabi-ld
TARGET:=project1-bbb.elf
endif

ifeq ($(PLATFORM),HOST)
CC:=gcc
CPP:=cpp
AS:=as
LD:=ld
TARGET:=project1-host.elf
endif


# Override Make default GCC toolchain

CFLAGS=-Wall -Werror -g -O0 -std=c99 $(PLATFORM_FLAGS)
LDFLAGS=-std=c99 $(PLATFORM_FLAGS)
CPPFLAGS=-std=c99 $(PLATFORM_FLAGS)

# Grab SOURCES variable from sources.mk
include sources.mk

DEPFILES:=$(SOURCES:.c=.d)
PREFILES:=$(SOURCES:.c=.i)
ASMFILES:=$(SOURCES:.c=.S)
OBJFILES:=$(ASMFILES:.S=.o)

.PHONY: all clean redo build compile-all

all: compile-all

compile-all: $(OBJFILES)

build: compile-all
	$(CC) $(CFLAGS) $(OBJFILES) -o $(TARGET)

clean:
	rm -f $(OBJFILES)
	rm -f $(PREFILES)
	rm -f $(ASMFILES)
	rm -f $(TARGET)

redo: clean all

# Make dependency files from C files
%.d: %.c
	$(CC) -M $< -o $@

# Make object files from C files without generating intermediate files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Make preprocessed files from C files
%.i: %.c
	$(CC) $(CPPFLAGS) -E $< -o $@

# Make assembly files from C files
%.asm: %.c
	$(CC) $(CFLAGS) -S $< -o $@

