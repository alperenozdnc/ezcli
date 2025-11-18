CC = gcc
CFLAGS = -Wall -Wextra -I./include

SRC_DIR = ./src
OBJ_DIR = ./obj
TARGET = ezcli

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all: $(TARGET) run clean
build: $(TARGET)

$(TARGET): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	@./$(TARGET)
	@$(MAKE) clean --no-print-directory

clean:
	@rm -rf $(OBJ_DIR) $(TARGET)
