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
