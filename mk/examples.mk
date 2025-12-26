#============== examples compilation ==============

.SUFFIXES:

EXAMPLES_BUILD_DIR = $(BUILD_DIR)/$(EXAMPLES_DIR)
EXAMPLES_SRC := $(shell find examples -name '*.c')
EXAMPLE_BIN := $(EXAMPLES_SRC:$(EXAMPLES_DIR)/%.c=$(BUILD_DIR)/$(EXAMPLES_DIR)/%)

examples: $(EXAMPLE_BIN)

$(BUILD_DIR)/$(EXAMPLES_DIR)/%: $(EXAMPLES_DIR)/%.c $(EZCLI_LIB_PATH)
	@mkdir -p $(dir $@)

	@$(CC) $(CFLAGS) -lm $< -L$(LIB_DIR) -lezcli -o $@
