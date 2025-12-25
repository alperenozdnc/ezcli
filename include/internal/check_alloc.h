#pragma once

#define CHECK_ALLOC(ptr)                                                       \
    do {                                                                       \
        if (!(ptr)) {                                                          \
            fprintf(stderr, "ezcli: out of memory.\n");                        \
            c_exit(1);                                                         \
        }                                                                      \
    } while (0)
