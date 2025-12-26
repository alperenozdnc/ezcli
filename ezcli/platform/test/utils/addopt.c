#include <test/integrity/addopt.h>
#include <test/integrity/emit_signal.h>
#include <test/integrity/platform.h>
#include <test/integrity/sig_arena_s.h>

#include "internal/opts_size.h"
#include "internal/validate.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void __addopt(cli_s *cli, opt_s *opt_a, sig_arena_s *arena) {
    validate_opt(cli, opt_a);

    size_t new_len = cli->opts_len + 1;
    opt_s **new_opts = c_malloc(OPTS_SIZE(new_len));

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        new_opts[i] = opt;
    }

    new_opts[new_len - 1] = opt_a;
    new_opts[new_len] = NULL;

    cli->opts = c_realloc(cli->opts, OPTS_SIZE(new_len));

    memcpy(cli->opts, new_opts, OPTS_SIZE(new_len));
    c_free(new_opts);

    cli->opts_len++;

    emit_signal(CLI_SIG_INIT_OPT);
}

void _addopt(cli_s *cli, sig_arena_s *arena, ...) {
    va_list opts;
    va_start(opts, arena);

    while (true) {
        opt_s *opt_a = va_arg(opts, opt_s *);

        if (!opt_a)
            break;

        __addopt(cli, opt_a, arena);
    }

    va_end(opts);
}
