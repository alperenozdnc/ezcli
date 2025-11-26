#include <ezcli/addopt.h>

#include "../internal/opts_size.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addopt(cli_s *cli, opt_s *opt_a) {
    size_t new_len = cli->opts_len + 1;
    opt_s **new_opts = malloc(OPTS_SIZE(new_len));

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        new_opts[i] = opt;
    }

    new_opts[new_len - 1] = opt_a;
    new_opts[new_len] = NULL;

    cli->opts = realloc(cli->opts, OPTS_SIZE(new_len));
    memcpy(cli->opts, new_opts, OPTS_SIZE(new_len));
    free(new_opts);

    cli->opts_len++;
}
