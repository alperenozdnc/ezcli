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

# include all public + internal + ezdocs headers
CFLAGS_DEBUG = -Wall -Wextra -Iinclude -Iinclude/internal -Iinclude/ezdocs -fsanitize=address -g -O0
CFLAGS       = -Wall -Wextra -Werror -Iinclude -Iinclude/internal -Iinclude/ezdocs -O3

BUILD ?= release
ifeq ($(BUILD),debug)
    CFLAGS := $(CFLAGS_DEBUG)
endif

#------------------------------------------------------
# directories / paths
#------------------------------------------------------

OBJ_DIR   = obj
BUILD_DIR = build

EZCLI_WORLD       = /usr/local
INCLUDE_DIR       = $(EZCLI_WORLD)/include
INSTALL_LIB_DIR   = $(EZCLI_WORLD)/lib
INSTALL_BIN_DIR   = $(EZCLI_WORLD)/bin

AUTOCOMP_TEMPLATES_DIR       = ~/.local/ezcli
AUTOCOMP_TEMPLATES_DIR_LOCAL = autocomp

EZDOCS_CONTENT_DIR       = ~/.local/ezdocs
EZDOCS_CONTENT_DIR_LOCAL = docs/docs_program
EZDOCS_COMPLETIONS_BASH  = ~/.local/share/bash-completion/completions/ezdocs
EZDOCS_COMPLETIONS_ZSH   = ~/.local/share/zsh/site-functions/_ezdocs

$(OBJ_DIR)/ezcli/%.o: ezcli/%.c
	@mkdir -p $(dir $@)
	$(call step,$(BLUE)[cc]$(RESET) $< → $@)
	@$(CC) $(CFLAGS) -c $< -o $@
	# autocomp regeneration
	@rm -rf $(AUTOCOMP_TEMPLATES_DIR)
	@mkdir -p $(AUTOCOMP_TEMPLATES_DIR)
	@cp $(AUTOCOMP_TEMPLATES_DIR_LOCAL)/* $(AUTOCOMP_TEMPLATES_DIR)/

$(OBJ_DIR)/ezdocs/%.o: ezdocs/%.c
	@mkdir -p $(dir $@)
	$(call step,$(BLUE)[cc ezdocs]$(RESET) $< → $@)
	@$(CC) $(CFLAGS) -c $< -o $@
