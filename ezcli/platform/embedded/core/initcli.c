#include <ezcli/platform.h>

#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/initcli.h>
#include <ezcli/print.h>

#include "internal/assert.h"
#include "internal/help.h"

static char *DISABLE_HELP[] = {"_____", NULL};

void initcli(cli_s *cli, char *cmd, char *desc, char *usage, char *footer,
             opt_s **opts, char *help_aliases[]) {
    (void)help_aliases;

    _assert(c_strlen(cmd) > 0, "cli->cmd can't be empty");
    _assert(c_strlen(desc) > 0, "cli->desc can't be empty");
    _assert(c_strlen(usage) > 0, "cli->usage can't be empty");

    cli->cmd = cmd;
    cli->desc = desc;
    cli->usage = usage;
    cli->footer = c_strlen(footer) > 0 ? footer : NULL;

    cli->opts_len = 0;
    cli->tok_idx = 1;

    cli->help = help;
    cli->help_aliases = DISABLE_HELP;

    bool calc_len = true;

    if (!opts[0])
        calc_len = false;

    while (calc_len && opts[cli->opts_len] != NULL) {
        cli->opts_len++;
    }

    cli->opts = opts;
}
