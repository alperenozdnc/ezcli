#------------------------------------------------------
# libezcli
#------------------------------------------------------

$(LIB_PATH): $(LIB_OBJ)
	@echo
	$(call banner,"build/libezcli")
	@mkdir -p $(LIB_DIR)
	@ar rcs $@ $^
	$(call ok,"libezcli → $(LIB_PATH)")
	@echo
	@echo

$(OBJ_DIR)/ezcli/%.o: $(SRC_DIR)/ezcli/%.c
	@mkdir -p $(dir $@)
	$(call step,$(BLUE)[ezcli]$(RESET) $< → $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	@rm -rf $(AUTOCOMP_TEMPLATES_DIR)
	@mkdir -p $(AUTOCOMP_TEMPLATES_DIR)
	@cp $(AUTOCOMP_TEMPLATES_DIR_LOCAL)/* $(AUTOCOMP_TEMPLATES_DIR)/
