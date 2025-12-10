#------------------------------------------------------
# examples → build/examples/*
#------------------------------------------------------

EXAMPLE_SRC := $(shell find examples -maxdepth 1 -name '*.c')
EXAMPLE_BIN := $(EXAMPLE_SRC:examples/%.c=$(BUILD_DIR)/examples/%)

.PHONY: examples

examples: $(EXAMPLE_BIN)

$(BUILD_DIR)/examples/%: examples/%.c $(LIB_PATH)
	@mkdir -p $(BUILD_DIR)/examples
	$(call step,$(MAGENTA)[example]$(RESET) $< → $@)
	@$(CC) $(CFLAGS) -lm $< -L$(LIB_DIR) -lezcli -o $@

