.PHONY: install uninstall install-docs uninstall-docs

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

install-docs: $(EZDOCS_PATH)
	$(call banner,"install/ezdocs")
	@sudo cp $(EZDOCS_PATH) $(INSTALL_BIN_DIR)/
	@sudo -E $(EZDOCS_PATH) autocompletions >/dev/null
	$(call ok,"autocompletions")
	$(call ok,"installed")

uninstall-docs:
	$(call banner,"uninstall/ezdocs")
	@sudo rm -f $(INSTALL_BIN_DIR)/ezdocs
	@sudo rm -f $(EZDOCS_COMPLETIONS_BASH)
	@sudo rm -f $(EZDOCS_COMPLETIONS_ZSH)
	$(call ok,"removed")
