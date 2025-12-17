#============== embedded mode ==============

PLATFORM_DIR = $(EZCLI_DIR)/platform

EMBEDDED ?= 0

ifeq ($(EMBEDDED),0)

PLATFORM = linux

else

PLATFORM = embedded

CFLAGS += -DCLI_EMBEDDED

endif

PLATFORM_SRC := $(shell find $(PLATFORM_DIR)/$(PLATFORM) -name '*.c')
