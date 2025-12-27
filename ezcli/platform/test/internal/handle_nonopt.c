#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/opt.h>

#include <test/integrity/assert.h>
#include <test/integrity/emit_signal.h>
#include <test/integrity/handle_nonopt.h>
#include <test/integrity/platform.h>
#include <test/integrity/sig_arena_s.h>

#include "internal/match.h"

#include <stdbool.h>

bool handle_nonopt(cli_s *cli, bool is_unrecog, bool any_option_seen,
                   sig_arena_s *arena) {
    if (!is_unrecog)
        return false;

    if (!CLI_ALLOW_NONOPT) {
        emit_signal(CLI_SIG_ERR_UNRECOG_ARG);

        c_exit(EXIT_FAILURE);

        return true;
    }

    if (any_option_seen) {
        emit_signal(CLI_SIG_ERR_CANT_CHAIN_NONOPT_AFTER_OPTS);

        c_exit(EXIT_FAILURE);

        return true;
    }

    opt_s *nonopt = oa_match_first(cli, CLI_NONOPT);

    _assert_free(cli, nonopt);

    emit_signal(CLI_SIG_EXEC_NONOPT_OPT);

    return true;
}
