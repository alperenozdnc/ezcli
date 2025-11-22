#include <ezcli/cli.h>
#include <ezcli/initcli.h>

#include "internal/opts_size.h"

#include <stdlib.h>
#include <string.h>

void initcli(struct cli *cli, char *cmd, bool allow_non_opt, bool gen_help,
             struct opt **opts) {
    cli->cmd = cmd;
    cli->allow_non_opt = allow_non_opt;
    cli->gen_help = gen_help;
    cli->opts_len = 0;

    while (opts[cli->opts_len] != NULL) {
        cli->opts_len++;
    }

    cli->opts = malloc(opts_size(cli->opts_len));

    for (size_t i = 0; i < cli->opts_len; i++) {
        cli->opts[i] = opts[i];
    }

    cli->opts[cli->opts_len] = NULL;
}
