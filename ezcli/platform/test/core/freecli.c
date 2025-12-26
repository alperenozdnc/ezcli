#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <test/integrity/emit_signal.h>
#include <test/integrity/freecli.h>
#include <test/integrity/sig_arena_s.h>

#include "internal/free_heap_opt.h"

#include <stdlib.h>

void _freecli(cli_s *cli, sig_arena_s *arena) {
    emit_signal(CLI_SIG_FREE_SELF);

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        if (!opt->allocated)
            continue;

        free_heap_opt(opt);
    }

    free(cli->opts);
}
