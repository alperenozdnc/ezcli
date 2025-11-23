#include <ezcli/addopt.h>

#include "../internal/opts_size.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addopt(struct cli *cli, struct opt *opt_a) {
    size_t new_len = cli->opts_len + 1;
    struct opt **new_opts = malloc(opts_size(new_len));

    for (size_t i = 0; i < cli->opts_len; i++) {
        struct opt *opt = cli->opts[i];

        new_opts[i] = opt;
    }

    new_opts[new_len - 1] = opt_a;
    new_opts[new_len] = NULL;

    cli->opts = realloc(cli->opts, opts_size(new_len));
    memcpy(cli->opts, new_opts, opts_size(new_len));
    free(new_opts);

    cli->opts_len++;
}
