#------------------------------------------------------
# ezdocs → build/ezdocs/ezdocs
#------------------------------------------------------

EZDOCS_NAME = ezdocs
EZDOCS_BIN  = $(BUILD_DIR)/ezdocs/$(EZDOCS_NAME)

EZDOCS_SRC := $(shell find ezdocs -name '*.c')
EZDOCS_OBJ := $(EZDOCS_SRC:%.c=$(OBJ_DIR)/%.o)

$(EZDOCS_BIN): $(LIB_PATH) $(EZDOCS_OBJ)
	@echo
	$(call banner,"build/ezdocs")
	@rm -rf $(EZDOCS_CONTENT_DIR)
	@mkdir -p $(EZDOCS_CONTENT_DIR)
	@cp -r $(EZDOCS_CONTENT_DIR_LOCAL)/* $(EZDOCS_CONTENT_DIR)/

	@mkdir -p $(BUILD_DIR)/ezdocs
	@$(CC) $(CFLAGS) $^ -L$(LIB_DIR) -lezcli -o $@

	$(call ok,"ezdocs → $(EZDOCS_BIN)")
	@echo

