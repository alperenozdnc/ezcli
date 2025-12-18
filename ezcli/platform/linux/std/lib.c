#include <ezcli/platform.h>

#include <stdlib.h>

void *c_malloc(size_t n) {
    return malloc(n);
}

void c_free(void *ptr) {
    return free(ptr);
}

void *c_realloc(void *ptr, size_t n) {
    return realloc(ptr, n);
}

void c_exit(int status) {
    exit(status);
}

int c_abs(int n) {
    return abs(n);
}
