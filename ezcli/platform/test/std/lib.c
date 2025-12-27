#include <ezcli/external.h>

#include <test/integrity/emit_signal.h>
#include <test/integrity/platform.h>
#include <test/integrity/sig_arena_s.h>

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

void _c_exit(int status, sig_arena_s *arena) {
    emit_signal(CLI_SIG_EXIT);

    if (CLI_MODE_LAIDBACK)
        return;

    exit(status);
}

int c_abs(int n) {
    return abs(n);
}
