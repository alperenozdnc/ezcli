CC = gcc
CFLAGS = -Wall -Wextra -Iinclude

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
EXAMPLES_DIR = examples

LIB_NAME = libezcli.a
LIB_PATH = $(LIB_DIR)/$(LIB_NAME)

LIB_SRC := $(shell find $(SRC_DIR)/ezcli -name '*.c')
LIB_OBJ := $(LIB_SRC:$(SRC_DIR)/ezcli/%.c=$(OBJ_DIR)/ezcli/%.o)

EXAMPLE_SRC := $(shell find $(SRC_DIR)/examples -name '*.c')
EXAMPLE_BIN := $(EXAMPLE_SRC:$(SRC_DIR)/examples/%.c=$(EXAMPLES_DIR)/%)

all: $(LIB_PATH) examples

$(LIB_PATH): $(LIB_OBJ)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/ezcli/%.o: $(SRC_DIR)/ezcli/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

examples: $(EXAMPLE_BIN)

$(EXAMPLES_DIR)/%: $(SRC_DIR)/examples/%.c $(LIB_PATH)
	@mkdir -p $(EXAMPLES_DIR)
	$(CC) $(CFLAGS) $< -L$(LIB_DIR) -lezcli -o $@

PREFIX = /usr/local
INCLUDE_DIR = $(PREFIX)/include
INSTALL_LIB_DIR = $(PREFIX)/lib

.PHONY: install uninstall clean

install: $(LIB_PATH)
	@echo "installing ezcli to $(PREFIX)."
	@mkdir -p $(INCLUDE_DIR)/ezcli
	@cp include/ezcli.h $(INCLUDE_DIR)/
	@cp include/ezcli/*.h $(INCLUDE_DIR)/ezcli/
	@cp $(LIB_PATH) $(INSTALL_LIB_DIR)/

uninstall:
	@echo "uninstalling ezcli."
	@rm -f $(INCLUDE_DIR)/ezcli.h
	@rm -rf $(INCLUDE_DIR)/ezcli
	@rm -f $(INSTALL_LIB_DIR)/$(LIB_NAME)

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(EXAMPLES_DIR)
