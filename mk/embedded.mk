#============== embedded mode ==============

PLATFORM_DIR = $(EZCLI_DIR)/platform
EMBEDDED ?= 0

ifeq ($(EMBEDDED),0)
PLATFORM_SRC := $(PLATFORM_DIR)/linux.c
PLATFORM_OBJ := $(OBJ_DIR)/$(EZCLI_DIR)/platform/linux.o
else
PLATFORM_SRC=$(PLATFORM_DIR)/embedded.c
PLATFORM_OBJ := $(OBJ_DIR)/$(EZCLI_DIR)/platform/embedded.o
CFLAGS += -DCLI_EMBEDDED
endif
