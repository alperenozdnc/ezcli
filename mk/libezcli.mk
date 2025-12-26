#============== ezcli compilation ==============

EZCLI_CORE_SRC := $(shell find ezcli/core -name '*.c')
EZCLI_INTERNAL_SRC := $(shell find ezcli/internal -name '*.c')
EZCLI_UTILS_SRC := $(shell find ezcli/utils -name '*.c')

EZCLI_SRC := $(EZCLI_CORE_SRC) $(EZCLI_INTERNAL_SRC) $(EZCLI_UTILS_SRC) $(PLATFORM_SRC) 
EZCLI_OBJ := $(EZCLI_SRC:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

#============== ezcli library archiving ==============

EZCLI_LIB_NAME = libezcli.a
EZCLI_LIB_PATH = $(LIB_DIR)/$(EZCLI_LIB_NAME)

ifeq ($(PLATFORM),linux)

$(EZCLI_LIB_PATH): $(EZCLI_OBJ)
	@mkdir -p $(LIB_DIR)
	@ar rcs $@ $^

	@rm -rf $(COMPLETION_TEMPLATES_DIR)
	@mkdir -p $(COMPLETION_TEMPLATES_DIR)
	@cp $(_COMPLETION_TEMPLATES_DIR)/* $(COMPLETION_TEMPLATES_DIR)/

else ifeq ($(PLATFORM),test)

$(EZCLI_LIB_PATH): $(EZCLI_OBJ)
	@mkdir -p $(LIB_DIR)
	@ar rcs $@ $^

else

$(EZCLI_LIB_PATH): $(EZCLI_OBJ)
	@mkdir -p $(LIB_DIR)
	@ar rcs $@ $^

endif
