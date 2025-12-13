include mk/base.mk
include mk/debug.mk
include mk/embedded.mk
include mk/autocomp.mk
include mk/libezcli.mk
include mk/ezdocs.mk
include mk/examples.mk
include mk/install.mk

#============== generalization ==============

ifeq ($(EMBEDDED),0)
all: $(EZCLI_LIB_PATH) $(EZDOCS_BIN) $(EXAMPLE_BIN)
else
all: $(EZCLI_LIB_PATH) $(EXAMPLE_BIN)
endif

debug:
	$(MAKE) BUILD=debug

embedded:
	$(MAKE) EMBEDDED=1

debug-embedded:
	$(MAKE) BUILD=debug EMBEDDED=1

.PHONY: all debug embedded debug-embedded clean install uninstall install-docs uninstall-docs
