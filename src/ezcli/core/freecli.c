#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/freecli.h>
#include <ezcli/print.h>

#include "internal/free_heap_opt.h"

#include <stdlib.h>

void freecli(cli_s *cli) {
    CLI_DEBUG_ONLY(
        cliprint(CLI_HINT, "[ezcli] ", "freeing all allocated memory"));

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        if (!opt->allocated)
            continue;

        free_heap_opt(opt);
    }

    free(cli->opts);
}
