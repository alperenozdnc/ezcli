#------------------------------------------------------
# colors & pretty helpers
#------------------------------------------------------

RESET  := \033[0m
BOLD   := \033[1m
DIM    := \033[2m
RED    := \033[31m
GREEN  := \033[32m
YELLOW := \033[33m
BLUE   := \033[34m
MAGENTA:= \033[35m
CYAN   := \033[36m

define banner
	@printf "$(CYAN)───[ $1 ]───$(RESET)\n\n"
endef

define step
	@printf "$(DIM)$1$(RESET)\n"
endef

define ok
	@printf "$(GREEN)✓$(RESET) $1\n"
endef

define err
	@printf "$(RED)✗$(RESET) $1\n"
endef

#------------------------------------------------------
# compiler & flags
#------------------------------------------------------

CC = gcc
CFLAGS_DEBUG = -Wall -Wextra -Iinclude -Iinclude/internal -fsanitize=address -g -O0
CFLAGS =      -Wall -Wextra -Werror -Iinclude -Iinclude/internal -O3

BUILD ?= release

ifeq ($(BUILD),debug)
    CFLAGS := $(CFLAGS_DEBUG)
endif

#------------------------------------------------------
# directories / paths
#------------------------------------------------------

SRC_DIR = src
OBJ_DIR = obj

EZCLI_WORLD       = /usr/local
INCLUDE_DIR       = $(EZCLI_WORLD)/include
INSTALL_LIB_DIR   = $(EZCLI_WORLD)/lib
INSTALL_BIN_DIR   = $(EZCLI_WORLD)/bin

EXAMPLES_DIR      = examples
EXAMPLE_SRC       := $(shell find $(SRC_DIR)/examples -name '*.c')
EXAMPLE_BIN       := $(EXAMPLE_SRC:$(SRC_DIR)/examples/%.c=$(EXAMPLES_DIR)/%)

AUTOCOMP_TEMPLATES_DIR       = ~/.local/ezcli
AUTOCOMP_TEMPLATES_DIR_LOCAL = autocomp

LIB_DIR  = lib
LIB_NAME = libezcli.a
LIB_PATH = $(LIB_DIR)/$(LIB_NAME)

LIB_SRC := $(shell find $(SRC_DIR)/ezcli -name '*.c')
LIB_OBJ := $(LIB_SRC:$(SRC_DIR)/ezcli/%.c=$(OBJ_DIR)/ezcli/%.o)

EZDOCS_NAME          = ezdocs
EZDOCS_DIR           = ezdocs
EZDOCS_PATH          = $(EZDOCS_DIR)/$(EZDOCS_NAME)
EZDOCS_SRC           := $(shell find $(SRC_DIR)/ezdocs -name '*.c')
EZDOCS_OBJ           := $(EZDOCS_SRC:$(SRC_DIR)/ezdocs/%.c=$(OBJ_DIR)/ezdocs/%.o)
EZDOCS_CONTENT_DIR   = ~/.local/ezdocs
EZDOCS_CONTENT_DIR_LOCAL = docs/docs_program
EZDOCS_COMPLETIONS_BASH = ~/.local/share/bash-completion/completions/ezdocs
EZDOCS_COMPLETIONS_ZSH  = ~/.local/share/zsh/site-functions/_ezdocs

#------------------------------------------------------
# build root
#------------------------------------------------------

all: $(LIB_PATH) examples $(EZDOCS_PATH)

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

#------------------------------------------------------
# examples
#------------------------------------------------------

examples: $(EXAMPLE_BIN)

$(EXAMPLES_DIR)/%: $(SRC_DIR)/examples/%.c $(LIB_PATH)
	@mkdir -p $(EXAMPLES_DIR)
	$(call step,$(MAGENTA)[example]$(RESET) $< → $@)
	@$(CC) $(CFLAGS) -lm $< -L$(LIB_DIR) -lezcli -o $@

#------------------------------------------------------
# install / uninstall
#------------------------------------------------------

.PHONY: install uninstall clean debug

install: $(LIB_PATH)
	$(call banner,"install/ezcli")
	@sudo mkdir -p $(INCLUDE_DIR)/ezcli
	@sudo cp include/ezcli.h $(INCLUDE_DIR)/
	@sudo cp include/ezcli/*.h $(INCLUDE_DIR)/ezcli/
	@sudo cp $(LIB_PATH) $(INSTALL_LIB_DIR)/
	$(call ok,"installed")

uninstall:
	$(call banner,"uninstall/ezcli")
	@sudo rm -f $(INCLUDE_DIR)/ezcli.h
	@sudo rm -rf $(INCLUDE_DIR)/ezcli
	@sudo rm -f $(INSTALL_LIB_DIR)/$(LIB_NAME)
	$(call ok,"farewell.")

install-docs: $(EZDOCS_PATH)
	$(call banner,"install/ezdocs")
	@sudo cp $(EZDOCS_PATH) $(INSTALL_BIN_DIR)/
	@sudo -E $(EZDOCS_PATH) autocompletions >/dev/null
	$(call ok,"autocompletions")
	$(call ok,"installed")

uninstall-docs:
	$(call banner,"uninstall/ezdocs")
	@sudo rm -f $(INSTALL_BIN_DIR)/ezdocs
	@sudo rm -f $(EZDOCS_COMPLETIONS_BASH)
	@sudo rm -f $(EZDOCS_COMPLETIONS_ZSH)
	$(call ok,"removed")

#------------------------------------------------------
# clean
#------------------------------------------------------

clean:
	$(call banner,"cleaning")
	@rm -rf $(OBJ_DIR) $(LIB_DIR) $(EXAMPLES_DIR) $(EZDOCS_DIR) \
		   $(EZDOCS_CONTENT_DIR) $(AUTOCOMP_TEMPLATES_DIR) \
		   $(EZDOCS_COMPLETIONS_BASH) $(EZDOCS_COMPLETIONS_ZSH)
	$(call ok,"clean")

#------------------------------------------------------
# debug
#------------------------------------------------------

debug:
	$(call banner,"debug build (asan)")
	@$(MAKE) BUILD=debug
	$(call ok,"debug done")

