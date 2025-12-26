#============== testing path initializations ==============

TEST_DIR=test
TEST_NAME=test

SANITY_BIN = $(BIN_DIR)/test/sanity
INTEGRITY_BIN = $(BIN_DIR)/test/integrity

TEST_SRC := $(shell find $(TEST_DIR) -name '*.c')

#============== testing compilation ==============

$(SANITY_BIN): $(TEST_DIR)/sanity.c
	@echo ===== SANITY TEST =====
	@echo

	@$(MAKE) PLATFORM=linux --no-print-directory
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $< -L$(LIB_DIR) -lezcli -o $@
	
	@$(SANITY_BIN)

	@$(MAKE) clean --no-print-directory

	@echo
	@echo ===== END SANITY TEST =====

	@echo

$(INTEGRITY_BIN): $(TEST_DIR)/integrity.c
	@echo ===== INTEGRITY TEST =====
	@echo

	@$(MAKE) clean --no-print-directory
	@mkdir -p $(dir $@)
	@$(MAKE) PLATFORM=test --no-print-directory

	@$(CC) $(CFLAGS) $< -L$(LIB_DIR) -lezcli -o $@
	
	@$(INTEGRITY_BIN)

	@$(MAKE) clean --no-print-directory

	@echo
	@echo ===== END INTEGRITY TEST =====

test: $(SANITY_BIN) $(INTEGRITY_BIN)
