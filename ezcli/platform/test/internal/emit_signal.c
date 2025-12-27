#include <test/integrity/emit_signal.h>
#include <test/integrity/external.h>
#include <test/integrity/push_sig.h>
#include <test/integrity/sig_arena_s.h>
#include <test/integrity/sig_s.h>

#include <stdio.h>

void _emit_signal(sig_arena_s *arena, sig_type_e type, uint16_t line,
                  char *file) {
    sig_s signal = {
        .type = type,
        .line = line,
        .file = file,
    };

    push_sig(arena, signal);

    if (CLI_SIG_PRINT) {
        printf("test/integrity: emitted '%s' (%s:%d).\n",
               sig_names[signal.type], file, line);
    }
}
