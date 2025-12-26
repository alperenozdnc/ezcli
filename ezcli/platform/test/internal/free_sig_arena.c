#include <test/integrity/free_sig_arena.h>
#include <test/integrity/sig_arena_s.h>
#include <test/integrity/sig_s.h>

#include <stdlib.h>

void free_sig_arena(sig_arena_s *arena) {
    for (size_t i = 0; i < arena->signals_size; i++) {
        sig_s *signal = arena->signals[i];

        free(signal->file);
        free(signal);
    }

    free(arena->signals);
    free(arena);
}
