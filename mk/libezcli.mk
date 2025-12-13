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
