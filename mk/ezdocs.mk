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
