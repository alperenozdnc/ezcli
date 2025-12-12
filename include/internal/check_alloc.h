#pragma once

#ifndef CLI_EMBEDDED
#include <stdio.h>

#define CHECK_ALLOC(ptr)                                                       \
    do {                                                                       \
        if (!(ptr)) {                                                          \
            fprintf(stderr, "ezcli: out of memory.\n");                        \
            c_exit(1);                                                         \
        }                                                                      \
    } while (0)
#else
#define CHECK_ALLOC(ptr)                                                       \
    do {                                                                       \
    } while (0)
#endif // CLI_EMBEDDED
