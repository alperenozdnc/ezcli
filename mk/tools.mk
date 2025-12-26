#============== tools compilation ==============

.SUFFIXES:

TOOLS_BUILD_DIR = $(BUILD_DIR)/$(TOOLS_DIR)
TOOLS_SRC := $(shell find $(TOOLS_DIR) -name '*.c')
TOOLS_BIN := $(TOOLS_SRC:$(TOOLS_DIR)/%.c=$(BUILD_DIR)/$(TOOLS_DIR)/%)

tools: $(TOOLS_BIN)

$(BUILD_DIR)/$(TOOLS_DIR)/%: $(TOOLS_DIR)/%.c $(EZCLI_LIB_PATH)
	@mkdir -p $(dir $@)

	@$(CC) $(CFLAGS) -lm $< -L$(LIB_DIR) -lezcli -o $@
