#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <test/integrity/delopt.h>
#include <test/integrity/emit_signal.h>
#include <test/integrity/platform.h>
#include <test/integrity/sig_arena_s.h>

#include "internal/free_heap_opt.h"
#include "internal/match.h"
#include "internal/opts_size.h"

#include <stdarg.h>

void __delopt(cli_s *cli, opt_s *opt_d, sig_arena_s *arena) {
    if (!ot_match_any(cli, opt_d->aliases[0])) {
        emit_signal(CLI_SIG_WARN_DEL_NONEXISTENT_OPT);

        return;
    }

    size_t new_len = cli->opts_len - 1;
    opt_s **new_opts = c_malloc(OPTS_SIZE(new_len));

    int j = 0;

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        if (!ot_match(opt_d, opt->aliases[0])) {
            new_opts[j++] = opt;
            continue;
        }

        if (!opt->allocated)
            continue;

        free_heap_opt(opt);
    }

    new_opts[j] = NULL;

    int k = 0;
    cli->opts = c_realloc(cli->opts, OPTS_SIZE(new_len));

    while (new_opts[k]) {
        cli->opts[k] = new_opts[k];

        k++;
    }

    cli->opts[k] = NULL;
    cli->opts_len--;

    c_free(new_opts);

    emit_signal(CLI_SIG_DEL_OPT);
}

void _delopt(cli_s *cli, sig_arena_s *arena, ...) {
    va_list opts;
    va_start(opts, arena);

    while (true) {
        opt_s *opt_d = va_arg(opts, opt_s *);

        if (!opt_d)
            break;

        __delopt(cli, opt_d, arena);
    }

    va_end(opts);
}
