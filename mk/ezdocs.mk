#------------------------------------------------------
# ezdocs
#------------------------------------------------------

$(EZDOCS_PATH): $(EZDOCS_OBJ)
	@echo
	$(call banner,"build/ezdocs")
	@rm -rf $(EZDOCS_CONTENT_DIR)
	@mkdir -p $(EZDOCS_CONTENT_DIR)
	@cp -r $(EZDOCS_CONTENT_DIR_LOCAL)/* $(EZDOCS_CONTENT_DIR)/
	@mkdir -p $(EZDOCS_DIR)
	@$(CC) $(CFLAGS) -Iinclude/ezdocs $^ -L$(LIB_DIR) -lezcli -o $@
	$(call ok,"ezdocs → $(EZDOCS_PATH)")
	@echo

$(OBJ_DIR)/ezdocs/%.o: $(SRC_DIR)/ezdocs/%.c
	@mkdir -p $(dir $@)
	$(call step,$(BLUE)[ezdocs]$(RESET) $< → $@)
	@$(CC) $(CFLAGS) -Iinclude/ezdocs -c $< -o $@
