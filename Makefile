#============== base initializations ==============

.DEFAULT_GOAL = all

CC = gcc

INC = -Iinclude -Iinclude/internal
CFLAGS_BASE = -Wall -Wextra -Werror $(INC)

HOME_LOCAL_DIR=~/.local
HOME_LOCAL_SHARE_DIR=$(HOME_LOCAL_DIR)/share

USR_LOCAL_DIR=/usr/local
USR_INCLUDE_DIR=$(USR_LOCAL_DIR)/include
USR_LIB_DIR=$(USR_LOCAL_DIR)/lib
USR_BIN_DIR=$(USR_LOCAL_DIR)/bin

EZCLI_DIR=ezcli
INCLUDE_DIR=include

BUILD_DIR=build
EXAMPLES_DIR=examples

LIB_DIR=$(BUILD_DIR)/lib
OBJ_DIR=$(BUILD_DIR)/obj
BIN_DIR=$(BUILD_DIR)/bin

#============== debug mode ==============

BUILD ?= release

ifeq ($(BUILD),debug)
CFLAGS = $(CFLAGS_BASE) -O0 -g -fsanitize=address
else
CFLAGS = $(CFLAGS_BASE) -O3
endif

#============== embedded mode ==============

PLATFORM_DIR = $(EZCLI_DIR)/platform
EMBEDDED ?= 0

ifeq ($(EMBEDDED),0)
PLATFORM_SRC := $(PLATFORM_DIR)/linux.c
PLATFORM_OBJ := $(OBJ_DIR)/$(EZCLI_DIR)/platform/linux.o
else
PLATFORM_SRC=$(PLATFORM_DIR)/embedded.c
PLATFORM_OBJ := $(OBJ_DIR)/$(EZCLI_DIR)/platform/embedded.o
CFLAGS += -DCLI_EMBEDDED
endif

#============== autocompletion path initializations ==============

COMPLETION_TEMPLATES_DIR = $(HOME_LOCAL_DIR)/$(EZCLI_DIR)
_COMPLETION_TEMPLATES_DIR = autocomp

#============== ezcli compilation ==============

EZCLI_CORE_SRC := $(shell find ezcli/core -name '*.c')
EZCLI_INTERNAL_SRC := $(shell find ezcli/internal -name '*.c')
EZCLI_UTILS_SRC := $(shell find ezcli/utils -name '*.c')

EZCLI_OBJ := $(OBJ_DIR)/$(EZCLI_DIR)

EZCLI_CORE_OBJ_DIR := $(EZCLI_OBJ)/core
EZCLI_INTERNAL_OBJ_DIR := $(EZCLI_OBJ)/internal
EZCLI_UTILS_OBJ_DIR := $(EZCLI_OBJ)/utils

EZCLI_CORE_OBJ := $(EZCLI_CORE_SRC:$(EZCLI_DIR)/core/%.c=$(EZCLI_CORE_OBJ_DIR)/%.o)
EZCLI_INTERNAL_OBJ := $(EZCLI_INTERNAL_SRC:$(EZCLI_DIR)/internal/%.c=$(EZCLI_INTERNAL_OBJ_DIR)/%.o)
EZCLI_UTILS_OBJ := $(EZCLI_UTILS_SRC:$(EZCLI_DIR)/utils/%.c=$(EZCLI_UTILS_OBJ_DIR)/%.o)

$(OBJ_DIR)/ezcli/core/%.o: ezcli/core/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/ezcli/internal/%.o: ezcli/internal/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)/ezcli/utils/%.o: ezcli/utils/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

$(PLATFORM_OBJ): $(PLATFORM_SRC)
	@mkdir -p $(dir $@)

	$(CC) $(CFLAGS) -c $< -o $@

EZCLI_OBJ := $(PLATFORM_OBJ) $(EZCLI_CORE_OBJ) $(EZCLI_INTERNAL_OBJ) $(EZCLI_UTILS_OBJ)

#============== ezcli library archiving ==============

EZCLI_LIB_NAME = libezcli.a
EZCLI_LIB_PATH = $(LIB_DIR)/$(EZCLI_LIB_NAME)

ifeq ($(EMBEDDED),0)

$(EZCLI_LIB_PATH): $(EZCLI_OBJ)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

	@rm -rf $(COMPLETION_TEMPLATES_DIR)
	@mkdir -p $(COMPLETION_TEMPLATES_DIR)
	@cp $(_COMPLETION_TEMPLATES_DIR)/* $(COMPLETION_TEMPLATES_DIR)/

else

$(EZCLI_LIB_PATH): $(EZCLI_OBJ)
	@mkdir -p $(LIB_DIR)
	ar rcs $@ $^

endif

#============== ezdocs path initializations ==============

EZDOCS_DIR=ezdocs
EZDOCS_NAME=ezdocs

EZDOCS_BIN = $(BIN_DIR)/$(EZDOCS_NAME)

EZDOCS_SRC := $(shell find $(EZDOCS_DIR) -name '*.c')

EZDOCS_OBJ_DIR = $(OBJ_DIR)/$(EZDOCS_DIR)
EZDOCS_OBJ := $(EZDOCS_SRC:%.c=$(OBJ_DIR)/%.o)

EZDOCS_CONTENT_DIR = $(HOME_LOCAL_DIR)/$(EZDOCS_DIR)
_EZDOCS_CONTENT_DIR = $(EZDOCS_DIR)/content

EZDOCS_COMPLETIONS_BASH = $(HOME_LOCAL_SHARE_DIR)/bash-completion/completions/ezdocs
EZDOCS_COMPLETIONS_ZSH = $(HOME_LOCAL_SHARE_DIR)/zsh/site-functions/_ezdocs

#============== ezdocs compilation ==============

$(EZDOCS_OBJ_DIR)/%.o: $(EZDOCS_DIR)/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -Iinclude/ezdocs -c $< -o $@

$(EZDOCS_BIN): $(EZCLI_LIB_PATH) $(EZDOCS_OBJ)
	@mkdir -p $(dir $@)
	@rm -rf $(EZDOCS_CONTENT_DIR)
	@mkdir -p $(EZDOCS_CONTENT_DIR)
	@cp -r $(_EZDOCS_CONTENT_DIR)/* $(EZDOCS_CONTENT_DIR)/

	$(CC) $(CFLAGS) -Iinclude/ezdocs $^ -L$(LIB_DIR) -lezcli -o $@

#============== examples compilation ==============

.SUFFIXES:

EXAMPLES_BUILD_DIR = $(BUILD_DIR)/$(EXAMPLES_DIR)
EXAMPLES_SRC := $(shell find examples -name '*.c')
EXAMPLE_BIN := $(EXAMPLES_SRC:$(EXAMPLES_DIR)/%.c=$(BUILD_DIR)/$(EXAMPLES_DIR)/%)

examples: $(EXAMPLE_BIN)

$(BUILD_DIR)/$(EXAMPLES_DIR)/%: $(EXAMPLES_DIR)/%.c $(EZCLI_LIB_PATH)
	@mkdir -p $(dir $@)

	$(CC) $(CFLAGS) -lm $< -L$(LIB_DIR) -lezcli -o $@

#============== installation/uninstallation ==============

EZCLI_INCLUDE_DIR= $(INCLUDE_DIR)/ezcli
EZCLI_UMBRELLA_HEADER= $(INCLUDE_DIR)/ezcli.h
EZCLI_COMPLETIONS_CMD = autocompletions

install:
	sudo mkdir -p $(USR_INCLUDE_DIR)/$(EZCLI_DIR)
	sudo cp $(EZCLI_UMBRELLA_HEADER) $(USR_INCLUDE_DIR)/
	sudo cp $(EZCLI_INCLUDE_DIR)/*.h $(USR_INCLUDE_DIR)/ezcli/
	sudo cp $(EZCLI_LIB_PATH) $(USR_LIB_DIR)/

uninstall:
	sudo rm -f $(EZCLI_UMBRELLA_HEADER)
	sudo rm -rf $(USR_INCLUDE_DIR)/$(EZCLI_DIR)
	sudo rm -f $(USR_LIB_DIR)/$(EZCLI_LIB_NAME)

install-docs: $(EZDOCS_BIN)
	sudo cp $(EZDOCS_BIN) $(USR_BIN_DIR)/$(EZDOCS_NAME)
	sudo -E $(INSTALL_BIN_DIR)/$(EZDOCS_NAME) $(EZCLI_COMPLETIONS_CMD)>/dev/null

uninstall-docs:
	sudo rm -f $(USR_BIN_DIR)/$(EZDOCS_NAME)
	sudo rm -f $(EZDOCS_COMPLETIONS_BASH)
	sudo rm -f $(EZDOCS_COMPLETIONS_ZSH)

clean:
	rm -rf $(BUILD_DIR) $(EZDOCS_COMPLETIONS_BASH) $(EZDOCS_COMPLETIONS_ZSH)

#============== generalization ==============

ifeq ($(EMBEDDED),0)
all: $(EZCLI_LIB_PATH) $(EZDOCS_BIN) $(EXAMPLE_BIN)
else
all: $(EZCLI_LIB_PATH) $(EXAMPLE_BIN)
endif

debug:
	$(MAKE) BUILD=debug

embedded:
	$(MAKE) EMBEDDED=1

debug-embedded:
	$(MAKE) BUILD=debug EMBEDDED=1

.PHONY: all debug embedded debug-embedded clean install uninstall install-docs uninstall-docs
