CSRC:=conversion.c data.c debug.c main.c memory.c project1.c
SSRC:=
ifeq ($(PLATFORM),KL25Z)
CSRC:=$(CSRC) system_MKL25Z4.c
SSRC:=$(SSRC) startup_MKL25Z4.S
endif
