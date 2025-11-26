#include <ezcli/delopt.h>

#include "../internal/opts_size.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void delopt(cli_s *cli, opt_s *opt_d) {
    size_t new_len = cli->opts_len - 1;
    opt_s **new_opts = malloc(OPTS_SIZE(new_len));

    int j = 0;

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        if (strcmp(opt_d->name, opt->name) == 0)
            continue;

        new_opts[j++] = opt;
    }

    new_opts[j] = NULL;

    int k = 0;
    cli->opts = realloc(cli->opts, OPTS_SIZE(new_len));

    while (new_opts[k]) {
        cli->opts[k] = new_opts[k];

        k++;
    }

    cli->opts[k] = NULL;
    cli->opts_len--;

    free(new_opts);
}
