#pragma once

#include <ezcli/platform.h>
#include <ezcli/print.h>

#define CHECK_ALLOC(ptr)                                                       \
    do {                                                                       \
        if (!(ptr)) {                                                          \
            cliprint(CLI_ERROR, "ezcli: ", "out of memory.");                  \
            c_exit(1);                                                         \
        }                                                                      \
    } while (0)
