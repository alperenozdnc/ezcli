#------------------------------------------------------
# examples
#------------------------------------------------------

examples: $(EXAMPLE_BIN)

$(EXAMPLES_DIR)/%: $(SRC_DIR)/examples/%.c $(LIB_PATH)
	@mkdir -p $(EXAMPLES_DIR)
	$(call step,$(MAGENTA)[example]$(RESET) $< → $@)
	@$(CC) $(CFLAGS) -lm $< -L$(LIB_DIR) -lezcli -o $@
