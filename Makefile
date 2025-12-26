# initialization
include mk/base.mk

# setting up debug/embedded/test modes
include mk/debug.mk
include mk/platform.mk

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

.PHONY: all debug embedded debug-embedded test run-test

ifeq ($(PLATFORM),linux)

all: $(EZCLI_LIB_PATH) $(EZDOCS_BIN) $(EXAMPLE_BIN) $(TOOLS_BIN)

else

all: $(EZCLI_LIB_PATH)

endif

debug:
	$(MAKE) BUILD=debug

embedded:
	$(MAKE) PLATFORM=embedded

debug-embedded:
	$(MAKE) BUILD=debug PLATFORM=embedded
