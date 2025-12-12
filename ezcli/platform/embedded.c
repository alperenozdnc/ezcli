#ifndef CLI_EMBEDDED
#error "ezcli: embedded platform can't be compiled in linux mode"
#endif

#include <ezcli/platform.h>

#include <stddef.h>

size_t c_strlen(const char *str) {
    const char *s = str;

    while (*s) {
        s++;
    }

    return s - str;
}

int c_strcmp(const char *a, const char *b) {
    while (*a && *a == *b) {
        a++;
        b++;
    }

    return *a - *b;
}
