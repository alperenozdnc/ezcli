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
