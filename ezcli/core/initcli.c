#include <ezcli/platform.h>

#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/initcli.h>
#include <ezcli/print.h>

#include "internal/assert.h"
#include "internal/check_alloc.h"
#include "internal/help.h"
#include "internal/opts_size.h"
#include "internal/validate.h"

void initcli(cli_s *cli, char *cmd, char *desc, char *usage, char *footer,
             opt_s **opts, char *help_aliases[]) {
    CLI_DEBUG_ONLY(cliprint(CLI_HINT, "[ezcli] ", "validating cli"));

    _assert(c_strlen(cmd) > 0, "cli->cmd can't be empty");
    _assert(c_strlen(desc) > 0, "cli->desc can't be empty");
    _assert(c_strlen(usage) > 0, "cli->usage can't be empty");

#ifndef CLI_EMBEDDED
    _assert(help_aliases[0], "cli->help_aliases can't be empty");
#endif // CLI_EMBEDDED

    CLI_DEBUG_ONLY(cliprint(CLI_HINT, "[ezcli] ", "initializing cli"));

    cli->cmd = cmd;
    cli->desc = desc;
    cli->usage = usage;
    cli->footer = c_strlen(footer) > 0 ? footer : NULL;

    cli->opts_len = 0;
    cli->tok_idx = 1;

    cli->help = help;

#ifndef CLI_EMBEDDED
    cli->help_aliases = help_aliases;
#else
    static char **DISABLE_HELP = {"_____", NULL};

    cli->help_aliases = DISABLE_HELP;
#endif // CLI_EMBEDDED

    bool calc_len = true;

    if (!opts[0])
        calc_len = false;

    while (calc_len && opts[cli->opts_len] != NULL) {
        cli->opts_len++;
    }

#ifdef CLI_EMBEDDED
    cli->opts = opts;

    return;
#endif /* ifdef CLI_EMBEDDED */

    cli->opts = c_malloc(OPTS_SIZE(cli->opts_len));

    CHECK_ALLOC(cli->opts);

    for (size_t i = 0; i < cli->opts_len; i++) {
        validate_opt(cli, opts[i]);

        opts[i]->allocated = false;

        cli->opts[i] = opts[i];
    }

    cli->opts[cli->opts_len] = NULL;
}
