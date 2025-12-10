.PHONY: install uninstall install-docs uninstall-docs

#------------------------------------------------------
# install / uninstall libezcli
#------------------------------------------------------

install: $(LIB_PATH)
	$(call banner,"install/ezcli")
	@sudo mkdir -p $(INCLUDE_DIR)/ezcli
	@sudo cp include/ezcli.h $(INCLUDE_DIR)/
	@sudo cp include/ezcli/*.h $(INCLUDE_DIR)/ezcli/
	@sudo cp $(LIB_PATH) $(INSTALL_LIB_DIR)/
	$(call ok,"installed")

uninstall:
	$(call banner,"uninstall/ezcli")
	@sudo rm -f $(INCLUDE_DIR)/ezcli.h
	@sudo rm -rf $(INCLUDE_DIR)/ezcli
	@sudo rm -f $(INSTALL_LIB_DIR)/$(LIB_NAME)
	$(call ok,"farewell.")

#------------------------------------------------------
# install / uninstall ezdocs (binary + completions)
#------------------------------------------------------

install-docs: $(EZDOCS_BIN)
	$(call banner,"install/ezdocs")
	@sudo cp $(EZDOCS_BIN) $(INSTALL_BIN_DIR)/ezdocs
	@sudo -E $(INSTALL_BIN_DIR)/ezdocs autocompletions >/dev/null
	$(call ok,"autocompletions")
	$(call ok,"installed")

uninstall-docs:
	$(call banner,"uninstall/ezdocs")
	@sudo rm -f $(INSTALL_BIN_DIR)/ezdocs
	@sudo rm -f $(EZDOCS_COMPLETIONS_BASH)
	@sudo rm -f $(EZDOCS_COMPLETIONS_ZSH)
	$(call ok,"removed")

