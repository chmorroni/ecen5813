CSRC:=conversion.c data.c debug.c main.c memory.c memory_opt.c project4.c circbuf.c profile.c log.c
SSRC:=
ifeq ($(PLATFORM),KL25Z)
CSRC:=$(CSRC) system_MKL25Z4.c platform.c gpio.c uart.c arch_arm32.c dma.c spi.c
SSRC:=$(SSRC) startup_MKL25Z4.S
endif
ifeq ($(PLATFORM),BBB)
CSRC:=$(CSRC) arch_arm32.c
endif
