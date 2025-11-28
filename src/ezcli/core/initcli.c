#include <ezcli/cli.h>
#include <ezcli/initcli.h>
#include <ezcli/print.h>

#include "../internal/check_alloc.h"
#include "../internal/help.h"
#include "../internal/opts_size.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initcli(cli_s *cli, char *cmd, char *desc, char *usage, char *footer,
             opt_s **opts, char *help_aliases[]) {
    cli->cmd = cmd;
    cli->desc = desc;
    cli->usage = usage;
    cli->footer = footer ? footer : NULL;

    cli->opts_len = 0;
    cli->tok_idx = 1;

    cli->help = clihelp;
    cli->help_aliases = help_aliases;

    bool count_indices = true;

    if (!opts[0])
        count_indices = false;

    while (count_indices && opts[cli->opts_len] != NULL) {
        cli->opts_len++;
    }

    cli->opts = malloc(OPTS_SIZE(cli->opts_len));

    CLI_CHECK_ALLOC(cli->opts);

    for (size_t i = 0; i < cli->opts_len; i++) {
        cli->opts[i] = opts[i];
    }

    cli->opts[cli->opts_len] = NULL;
}
