#include <test/integrity/platform.h>

#include <stdio.h>

int c_fprintf(void *stream, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);

    int ret = vfprintf(stream, format, args);

    va_end(args);

    return ret;
}

int c_vprintf(const char *restrict format, va_list ap) {
    return vprintf(format, ap);
}

int c_printf(const char *restrict format, ...) {
    va_list args;
    va_start(args, format);

    int ret = vprintf(format, args);

    va_end(args);

    return ret;
}

int c_puts(const char *str) {
    return puts(str);
}
