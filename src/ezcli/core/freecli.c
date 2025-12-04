#include <ezcli/cli.h>
#include <ezcli/freecli.h>

#include "../internal/free_heap_opt.h"

#include <stdlib.h>

void freecli(cli_s *cli) {
    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        if (!opt->allocated)
            continue;

        free_heap_opt(opt);
    }

    free(cli->opts);
}
