#include <ezcli/platform.h>

#include <string.h>

size_t c_strlen(const char *str) {
    return strlen(str);
}

int c_strcmp(const char *a, const char *b) {
    return strcmp(a, b);
}
