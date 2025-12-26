#============== embedded mode ==============

PLATFORM_DIR = $(EZCLI_DIR)/platform

PLATFORM ?= linux

ifeq ($(PLATFORM),linux)

PLATFORM = linux

else ifeq ($(PLATFORM),embedded)
	
PLATFORM = embedded

CFLAGS += -DCLI_EMBEDDED

else

PLATFORM = test 

endif

PLATFORM_SRC := $(shell find $(PLATFORM_DIR)/$(PLATFORM) -name '*.c')
