#pragma once

#include <stddef.h>
#include <test/integrity/sig_s.h>

#define SIGNALS_SIZE(n) sizeof(sig_s) * (n + 1)

/*
 * holds information about the signal arena, which is just an array of `sig_s`
 * structs allocated in heap.
 */
typedef struct {
    sig_s **signals;
    size_t signals_size;
} sig_arena_s;
