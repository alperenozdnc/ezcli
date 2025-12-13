#============== debug mode ==============

BUILD ?= release

ifeq ($(BUILD),debug)
CFLAGS = $(CFLAGS_BASE) -O0 -g -fsanitize=address
else
CFLAGS = $(CFLAGS_BASE) -O3
endif
