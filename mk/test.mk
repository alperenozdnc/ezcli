#============== testing path initializations ==============

TEST_DIR=test
TEST_NAME=test

TEST_BIN = $(BIN_DIR)/$(TEST_NAME)

TEST_SRC := $(shell find $(TEST_DIR) -name '*.c')

TEST_OBJ_DIR = $(OBJ_DIR)/$(TEST_DIR)
TEST_OBJ := $(TEST_SRC:%.c=$(OBJ_DIR)/%.o)

#============== testing compilation ==============

$(TEST_OBJ_DIR)/%.o: $(TEST_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(TEST_BIN): $(EZCLI_LIB_PATH) $(TEST_OBJ)
	@mkdir -p $(dir $@)

	$(CC) $(CFLAGS) $^ -L$(LIB_DIR) -lezcli -o $@

test: $(TEST_BIN)
