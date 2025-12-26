#include <test/integrity/platform.h>
#include <test/integrity/push_sig.h>
#include <test/integrity/sig_arena_s.h>
#include <test/integrity/sig_s.h>

#include <stdlib.h>
#include <string.h>

void push_sig(sig_arena_s *arena, sig_s signal) {
    sig_s *signal_heap = malloc(sizeof(*signal_heap));

    signal_heap->type = signal.type;
    signal_heap->line = signal.line;

    signal_heap->file = strdup(signal.file);

    arena->signals_size++;

    arena->signals = realloc(arena->signals, SIGNALS_SIZE(arena->signals_size));
    arena->signals[arena->signals_size - 1] = signal_heap;
}
