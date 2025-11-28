#include <ezcli/addopt.h>

#include "../internal/assert.h"
#include "../internal/check_alloc.h"
#include "../internal/opts_size.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addopt(cli_s *cli, opt_s *opt_a) {
    cliassert(opt_a->aliases && opt_a->aliases[0],
              "an option must have at least one alias");
    cliassert(opt_a->body, "an option must have a body");
    cliassert(opt_a->desc && strlen(opt_a->desc) > 0,
              "an option must have a description");

    size_t new_len = cli->opts_len + 1;
    opt_s **new_opts = malloc(OPTS_SIZE(new_len));

    CLI_CHECK_ALLOC(new_opts);

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        new_opts[i] = opt;
    }

    new_opts[new_len - 1] = opt_a;
    new_opts[new_len] = NULL;

    cli->opts = realloc(cli->opts, OPTS_SIZE(new_len));
    CLI_CHECK_ALLOC(cli->opts);

    memcpy(cli->opts, new_opts, OPTS_SIZE(new_len));
    free(new_opts);

    cli->opts_len++;
}
