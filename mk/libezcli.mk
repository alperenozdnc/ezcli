#------------------------------------------------------
# libezcli
#------------------------------------------------------

LIB_DIR  = lib
LIB_NAME = libezcli.a
LIB_PATH = $(LIB_DIR)/$(LIB_NAME)

# all C files under ezcli/{core,internal,utils}
LIB_SRC := $(shell find ezcli -name '*.c')
LIB_OBJ := $(LIB_SRC:%.c=$(OBJ_DIR)/%.o)

$(LIB_PATH): $(LIB_OBJ)
	@echo
	$(call banner,"build/libezcli")
	@mkdir -p $(LIB_DIR)
	@ar rcs $@ $^
	$(call ok,"libezcli → $(LIB_PATH)")
	@echo
	@echo

