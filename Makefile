CC = gcc
CFLAGS = -Wall -Wextra -Iinclude -Iinclude/internal -fsanitize=address -g -O3

SRC_DIR = src
OBJ_DIR = obj
LIB_DIR = lib
EXAMPLES_DIR = examples
EZDOCS_DIR = ezdocs
EZDOCS_CONTENT_DIR = ~/.local/ezdocs
EZDOCS_CONTENT_DIR_LOCAL = docs/docs_program

AUTOCOMP_TEMPLATES_DIR = ~/.local/ezcli
AUTOCOMP_TEMPLATES_DIR_LOCAL = autocomp

LIB_NAME = libezcli.a
LIB_PATH = $(LIB_DIR)/$(LIB_NAME)

EZDOCS_NAME = ezdocs
EZDOCS_PATH = $(EZDOCS_DIR)/$(EZDOCS_NAME)

LIB_SRC := $(shell find $(SRC_DIR)/ezcli -name '*.c')
LIB_OBJ := $(LIB_SRC:$(SRC_DIR)/ezcli/%.c=$(OBJ_DIR)/ezcli/%.o)

EZDOCS_SRC := $(shell find $(SRC_DIR)/ezdocs -name '*.c')
EZDOCS_OBJ := $(EZDOCS_SRC:$(SRC_DIR)/ezdocs/%.c=$(OBJ_DIR)/ezdocs/%.o)

EXAMPLE_SRC := $(shell find $(SRC_DIR)/examples -name '*.c')
EXAMPLE_BIN := $(EXAMPLE_SRC:$(SRC_DIR)/examples/%.c=$(EXAMPLES_DIR)/%)

all: $(LIB_PATH) examples $(EZDOCS_PATH) 

$(LIB_PATH): $(LIB_OBJ)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

$(OBJ_DIR)/ezcli/%.o: $(SRC_DIR)/ezcli/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	@rm -rf $(AUTOCOMP_TEMPLATES_DIR)
	@mkdir $(AUTOCOMP_TEMPLATES_DIR)
	@cp $(AUTOCOMP_TEMPLATES_DIR_LOCAL)/* $(AUTOCOMP_TEMPLATES_DIR)/

$(EZDOCS_PATH): $(EZDOCS_OBJ)
	@rm -rf $(EZDOCS_CONTENT_DIR)
	@mkdir $(EZDOCS_CONTENT_DIR)
	@cp -r $(EZDOCS_CONTENT_DIR_LOCAL)/* $(EZDOCS_CONTENT_DIR)/
	@mkdir -p $(EZDOCS_DIR)
	$(CC) $(CFLAGS) -Iinclude/ezdocs $^ -L$(LIB_DIR) -lezcli -o $@

$(OBJ_DIR)/ezdocs/%.o: $(SRC_DIR)/ezdocs/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iinclude/ezdocs -c $< -o $@

examples: $(EXAMPLE_BIN)

$(EXAMPLES_DIR)/%: $(SRC_DIR)/examples/%.c $(LIB_PATH)
	@mkdir -p $(EXAMPLES_DIR)
	$(CC) $(CFLAGS) -lm $< -L$(LIB_DIR) -lezcli -o $@

PREFIX = /usr/local
INCLUDE_DIR = $(PREFIX)/include
INSTALL_LIB_DIR = $(PREFIX)/lib
INSTALL_BIN_DIR = $(PREFIX)/bin

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

install-docs: $(EZDOCS_PATH)
	@echo "installing ezdocs to $(PREFIX)."
	@cp $(EZDOCS_PATH) $(INSTALL_BIN_DIR)/

uninstall-docs:
	@echo "uninstalling ezdocs"
	@rm -f $(INSTALL_BIN_DIR)/ezdocs

clean:
	rm -rf $(OBJ_DIR) $(LIB_DIR) $(EXAMPLES_DIR) $(EZDOCS_DIR) $(EZDOCS_CONTENT_DIR) $(AUTOCOMP_TEMPLATES_DIR)
