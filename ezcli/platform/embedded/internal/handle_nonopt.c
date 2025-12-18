#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/opt.h>
#include <ezcli/platform.h>
#include <ezcli/print.h>

#include "internal/assert.h"
#include "internal/execopt.h"
#include "internal/handle_nonopt.h"
#include "internal/match.h"

#include <stdbool.h>

bool handle_nonopt(cli_s *cli, char *tok, bool is_unrecog,
                   bool any_option_seen) {
    if (!is_unrecog)
        return false;

    if (!CLI_ALLOW_NONOPT) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX, "%s: unrecognized option '%s'.",
                 cli->cmd, tok);

        c_exit(EXIT_FAILURE);
    }

    if (any_option_seen) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX,
                 "%s: can't chain non-option '%s' after any options.", cli->cmd,
                 tok);

        c_exit(EXIT_FAILURE);
    }

    opt_s *nonopt = oa_match_first(cli, CLI_NONOPT);

    _assert(cli, "you must define a nonopt after"
                 "setting CLI_ALLOW_NONOPT to true");

    execopt(nonopt, tok);

    return true;
}
