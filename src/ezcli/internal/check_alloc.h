#pragma once

#define CLI_CHECK_ALLOC(ptr)                                                   \
    do {                                                                       \
        if (!(ptr)) {                                                          \
            fprintf(stderr, "ezcli: out of memory.\n");                        \
            exit(1);                                                           \
        }                                                                      \
    } while (0)
