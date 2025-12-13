#============== installation/uninstallation ==============

EZCLI_INCLUDE_DIR= $(INCLUDE_DIR)/ezcli
EZCLI_UMBRELLA_HEADER= $(INCLUDE_DIR)/ezcli.h
EZCLI_COMPLETIONS_CMD = autocompletions

.PHONY: clean install uninstall install-docs uninstall-docs

install:
	sudo mkdir -p $(USR_INCLUDE_DIR)/$(EZCLI_DIR)
	sudo cp $(EZCLI_UMBRELLA_HEADER) $(USR_INCLUDE_DIR)/
	sudo cp $(EZCLI_INCLUDE_DIR)/*.h $(USR_INCLUDE_DIR)/ezcli/
	sudo cp $(EZCLI_LIB_PATH) $(USR_LIB_DIR)/

uninstall:
	sudo rm -f $(EZCLI_UMBRELLA_HEADER)
	sudo rm -rf $(USR_INCLUDE_DIR)/$(EZCLI_DIR)
	sudo rm -f $(USR_LIB_DIR)/$(EZCLI_LIB_NAME)

install-docs: $(EZDOCS_BIN)
	sudo cp $(EZDOCS_BIN) $(USR_BIN_DIR)/$(EZDOCS_NAME)
	sudo -E $(INSTALL_BIN_DIR)/$(EZDOCS_NAME) $(EZCLI_COMPLETIONS_CMD)>/dev/null

uninstall-docs:
	sudo rm -f $(USR_BIN_DIR)/$(EZDOCS_NAME)
	sudo rm -f $(EZDOCS_COMPLETIONS_BASH)
	sudo rm -f $(EZDOCS_COMPLETIONS_ZSH)

clean:
	rm -rf $(BUILD_DIR) $(EZDOCS_COMPLETIONS_BASH) $(EZDOCS_COMPLETIONS_ZSH)
