include mk/global.mk
include mk/libezcli.mk
include mk/ezdocs.mk
include mk/examples.mk
include mk/install.mk

.PHONY: all clean debug

#------------------------------------------------------
# build root
#------------------------------------------------------

all: $(LIB_PATH) $(EZDOCS_BIN) examples

#------------------------------------------------------
# clean
#------------------------------------------------------

clean:
	$(call banner,"cleaning")
	@rm -rf $(OBJ_DIR) $(LIB_DIR) $(BUILD_DIR) \
		   $(EZDOCS_CONTENT_DIR) $(AUTOCOMP_TEMPLATES_DIR) \
		   $(EZDOCS_COMPLETIONS_BASH) $(EZDOCS_COMPLETIONS_ZSH)
	$(call ok,"clean")

#------------------------------------------------------
# debug
#------------------------------------------------------

debug:
	$(call banner,"build/debug")
	@$(MAKE) all BUILD=debug
	$(call ok,"debug done")
	@echo

