# initialization
include mk/base.mk

# setting up debug/embedded modes
include mk/debug.mk
include mk/embedded.mk

# setting up autocompletions
include mk/autocomp.mk

# compilation and archiving of ezcli
include mk/libezcli.mk

# compilation of testing units
include mk/test.mk

# compilation of ezdocs 
include mk/ezdocs.mk

# compilation of tools 
include mk/tools.mk

# compilation of examples 
include mk/examples.mk

# install/uninstall for ezcli, ezdocs and 'clean' option for build artifacts
include mk/install.mk

#============== generalization ==============

.PHONY: all debug embedded debug-embedded

ifeq ($(EMBEDDED),0)

all: $(EZCLI_LIB_PATH) $(EZDOCS_BIN) $(EXAMPLE_BIN) $(TOOLS_BIN)

else

all: $(EZCLI_LIB_PATH)

endif

debug:
	$(MAKE) BUILD=debug

embedded:
	$(MAKE) EMBEDDED=1

debug-embedded:
	$(MAKE) BUILD=debug EMBEDDED=1
