#include <ezcli/addopt.h>

#include "../internal/check_alloc.h"
#include "../internal/opts_size.h"
#include "../internal/validate.h"

#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void __addopt(cli_s *cli, opt_s *opt_a) {
    validate_opt(opt_a);

    size_t new_len = cli->opts_len + 1;
    opt_s **new_opts = malloc(OPTS_SIZE(new_len));

    CHECK_ALLOC(new_opts);

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        new_opts[i] = opt;
    }

    new_opts[new_len - 1] = opt_a;
    new_opts[new_len] = NULL;

    cli->opts = realloc(cli->opts, OPTS_SIZE(new_len));
    CHECK_ALLOC(cli->opts);

    memcpy(cli->opts, new_opts, OPTS_SIZE(new_len));
    free(new_opts);

    cli->opts_len++;
}

void _addopt(cli_s *cli, ...) {
    va_list args;
    va_start(args, cli);

    while (true) {
        opt_s *opt_a = va_arg(args, opt_s *);

        if (!opt_a)
            break;

        __addopt(cli, opt_a);
    }

    va_end(args);
}
