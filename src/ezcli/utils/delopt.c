#include <ezcli/cli.h>
#include <ezcli/delopt.h>
#include <ezcli/external.h>
#include <ezcli/print.h>

#include "../internal/check_alloc.h"
#include "../internal/free_heap_opt.h"
#include "../internal/match.h"
#include "../internal/opts_size.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __delopt(cli_s *cli, opt_s *opt_d) {
    if (!ot_match_any(cli, opt_d->aliases[0])) {
        CLI_DEBUG_ONLY(
            cliprint(CLI_WARN, "[ezcli] ",
                     "option %s doesn't exist in opts array, skipping...",
                     opt_d->aliases[0]));

        return;
    }

    size_t new_len = cli->opts_len - 1;
    opt_s **new_opts = malloc(OPTS_SIZE(new_len));
    CHECK_ALLOC(new_opts);

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
    cli->opts = realloc(cli->opts, OPTS_SIZE(new_len));
    CHECK_ALLOC(cli->opts);

    while (new_opts[k]) {
        cli->opts[k] = new_opts[k];

        k++;
    }

    cli->opts[k] = NULL;
    cli->opts_len--;

    free(new_opts);
}

void _delopt(cli_s *cli, ...) {
    va_list opts;
    va_start(opts, cli);

    while (true) {
        opt_s *opt_d = va_arg(opts, opt_s *);

        if (!opt_d)
            break;

        __delopt(cli, opt_d);
    }

    va_end(opts);
}
