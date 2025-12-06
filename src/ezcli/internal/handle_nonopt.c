#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include "assert.h"
#include "execopt.h"
#include "handle_nonopt.h"
#include "match.h"
#include "recommend.h"

#include <stdbool.h>
#include <stdlib.h>

bool handle_nonopt(cli_s *cli, char *tok, bool is_unrecog,
                   bool any_option_seen) {
    if (!is_unrecog)
        return false;

    if (!CLI_ALLOW_NONOPT) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX, "%s: unrecognized option '%s'.",
                 cli->cmd, tok);

        if (CLI_MODE_RECOMMEND) {
            char *recommended = recommend_opt(cli, tok);

            if (recommended)
                cliprint(CLI_HINT, CLI_EMPTY_PREFIX,
                         "%s: did you mean to say '%s'?", cli->cmd,
                         recommended);
        }

        exit(EXIT_FAILURE);
    }

    if (any_option_seen) {
        cliprint(CLI_ERROR, CLI_EMPTY_PREFIX,
                 "%s: can't chain non-option '%s' after any options.", cli->cmd,
                 tok);

        exit(EXIT_FAILURE);
    }

    opt_s *nonopt = oa_match_first(cli, CLI_NONOPT);

    _assert_free(cli, nonopt,
                 "you must define a nonopt after"
                 "setting CLI_ALLOW_NONOPT to true");

    CLI_DEBUG_ONLY(cliprint(CLI_HINT, "[ezcli] ", "executing nonopt"));

    execopt(nonopt, tok);

    return true;
}
