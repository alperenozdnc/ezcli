#include <ezcli/addopt.h>

#include "../internal/opts_size.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addopt(struct cli *cli, struct opt *opt_a) {
    struct opt **new_opts = malloc(opts_size(cli->opts_len + 1));

    for (size_t i = 0; i < cli->opts_len; i++) {
        struct opt *opt = cli->opts[i];

        memcpy(&new_opts[i], &opt, sizeof(struct opt *));
    }

    memcpy(&new_opts[cli->opts_len++], &opt_a, sizeof(struct opt *));
    new_opts[cli->opts_len] = NULL;

    cli->opts = realloc(cli->opts, opts_size(cli->opts_len + 1));

    for (size_t i = 0; i < cli->opts_len; i++) {
        struct opt *opt = new_opts[i];

        memcpy(&cli->opts[i], &opt, sizeof(struct opt *));
    }

    free(new_opts);
}
