#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <test/integrity/assert.h>
#include <test/integrity/emit_signal.h>
#include <test/integrity/initcli.h>
#include <test/integrity/platform.h>
#include <test/integrity/push_sig.h>
#include <test/integrity/sig_s.h>
#include <test/integrity/validate.h>

#include "internal/help.h"
#include "internal/opts_size.h"

void initcli(cli_s *cli, char *cmd, char *desc, char *usage, char *footer,
             opt_s **opts, char *help_aliases[], sig_arena_s *arena) {
    emit_signal(CLI_SIG_INIT_SELF);

    _assert(c_strlen(cmd) > 0);
    _assert(c_strlen(desc) > 0);
    _assert(c_strlen(usage) > 0);
    _assert(help_aliases[0]);

    cli->cmd = cmd;
    cli->desc = desc;
    cli->usage = usage;
    cli->footer = c_strlen(footer) > 0 ? footer : NULL;

    cli->opts_len = 0;
    cli->tok_idx = 1;

    cli->help = help;
    cli->help_aliases = help_aliases;

    bool calc_len = true;

    if (!opts[0])
        calc_len = false;

    while (calc_len && opts[cli->opts_len] != NULL) {
        cli->opts_len++;
    }

    cli->opts = c_malloc(OPTS_SIZE(cli->opts_len));

    for (size_t i = 0; i < cli->opts_len; i++) {
        validate_opt(cli, opts[i]);

        opts[i]->allocated = false;

        cli->opts[i] = opts[i];
    }

    cli->opts[cli->opts_len] = NULL;
}
