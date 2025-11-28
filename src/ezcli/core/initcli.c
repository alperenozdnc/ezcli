#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/initcli.h>
#include <ezcli/print.h>

#include "../internal/assert.h"
#include "../internal/check_alloc.h"
#include "../internal/help.h"
#include "../internal/opts_size.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void initcli(cli_s *cli, char *cmd, char *desc, char *usage, char *footer,
             opt_s **opts, char *help_aliases[]) {
    CLI_DEBUG_ONLY(cliprint(CLI_HINT, "[ezcli] ", "validating cli"));

    cliassert(strlen(cmd) > 0, "cli->cmd can't be empty");
    cliassert(strlen(desc) > 0, "cli->desc can't be empty");
    cliassert(strlen(usage) > 0, "cli->usage can't be empty");
    cliassert(help_aliases[0], "cli->help_aliases can't be empty");

    cli->cmd = cmd;
    cli->desc = desc;
    cli->usage = usage;
    cli->footer = strlen(footer) > 0 ? footer : NULL;

    cli->opts_len = 0;
    cli->tok_idx = 1;

    cli->help = clihelp;
    cli->help_aliases = help_aliases;

    bool calc_len = true;

    if (!opts[0])
        calc_len = false;

    while (calc_len && opts[cli->opts_len] != NULL) {
        cli->opts_len++;
    }

    cli->opts = malloc(OPTS_SIZE(cli->opts_len));

    CLI_CHECK_ALLOC(cli->opts);

    for (size_t i = 0; i < cli->opts_len; i++) {
        cli->opts[i] = opts[i];
    }

    cli->opts[cli->opts_len] = NULL;
}
