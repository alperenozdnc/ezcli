#include <ezcli/cli.h>
#include <ezcli/extern.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include "context.h"
#include "handle_nonopt.h"
#include "match.h"

#include <stdbool.h>
#include <stdlib.h>

bool handle_nonopt(cli_s *cli, char *tok, bool is_unrecog,
                   bool any_option_seen) {
    if (!is_unrecog)
        return false;

    if (!CLI_ALLOW_NONOPT) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX, "%s: unrecognized option '%s'.",
                 cli->cmd, tok);

        exit(EXIT_FAILURE);
    }

    if (any_option_seen) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX,
                 "%s: can't chain non-option '%s' after any options.", cli->cmd,
                 tok);

        exit(EXIT_FAILURE);
    }

    opt_s *nonopt = match_nonopt(cli);

    nonopt->body(__CONTEXT(nonopt), tok);

    return true;
}
