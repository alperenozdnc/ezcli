#include <ezcli/cli.h>
#include <ezcli/initcli.h>

#include "internal/help.h"
#include "internal/opts_size.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initcli(struct cli *cli, char *cmd, char *desc, char *usage,
             bool allow_non_opt, struct opt **opts, char **help_aliases) {
    cli->cmd = cmd;
    cli->desc = desc;
    cli->usage = usage;
    cli->allow_non_opt = allow_non_opt;
    cli->opts_len = 0;

    cli->help = cli_help;
    cli->help_aliases = help_aliases;

    while (opts[cli->opts_len] != NULL) {
        cli->opts_len++;
    }

    cli->opts = malloc(opts_size(cli->opts_len));

    for (size_t i = 0; i < cli->opts_len; i++) {
        cli->opts[i] = opts[i];
    }

    cli->opts[cli->opts_len] = NULL;
}
