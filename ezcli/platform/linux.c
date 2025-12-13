#ifdef CLI_EMBEDDED
#error "ezcli: linux platform can't be compiled in embedded mode"
#endif

#include <ezcli/platform.h>

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

size_t c_strlen(const char *str) {
    return strlen(str);
}

void *c_malloc(size_t n) {
    return malloc(n);
}

void c_free(void *ptr) {
    return free(ptr);
}

void *c_realloc(void *ptr, size_t n) {
    return realloc(ptr, n);
}

int c_fprintf(void *stream, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);

    int ret = vfprintf(stream, format, args);

    va_end(args);

    return ret;
}

void c_exit(int status) {
    exit(status);
}

int c_vprintf(const char *restrict format, va_list ap) {
    return vprintf(format, ap);
}

int c_printf(const char *restrict format, ...) {
    va_list args;
    va_start(args, format);

    int ret = printf(format, args);

    va_end(args);

    return ret;
}

int c_puts(const char *str) {
    return puts(str);
}

int c_strcmp(const char *a, const char *b) {
    return strcmp(a, b);
}

int c_abs(int n) {
    return abs(n);
}
