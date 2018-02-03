SOURCES:=conversion.c data.c debug.c main.c memory.c project1.c
ifeq ($(PLATFORM),KL25Z)
SOURCES:=$(SOURCES) startup_MKL25Z4.S system_MKL25Z4.c
endif
