#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>
#include <ezcli/runcli.h>

#include "internal/check_ret.h"
#include "internal/execopt.h"
#include "internal/handle_nonopt.h"
#include "internal/match.h"
#include "internal/panic.h"

#include <stdbool.h>

void runcli(cli_s *cli, int argc, char *argv[]) {
    cli->argc = argc;
    cli->argv = argv;

    bool any_option_seen = false;
    bool any_warnings = false;

    if (argc == 1) {
        opt_s *opt_default = ot_match_any(cli, CLI_DEFAULT_OPT);

        if (opt_default)
            execopt(opt_default, NULL);

        return;
    }

    // 0-th index is the command name itself
    for (int i = 1; i < argc; i++, cli->tok_idx++) {
        char *tok = argv[i];
        opt_s *opt = ot_match_any(cli, tok);
        opt_s *opt_prev = ot_match_any(cli, argv[i - 1]);

        bool is_tok_arg = !opt;
        bool is_prev_tok_arg = !opt_prev;
        bool is_unrecog = is_tok_arg && is_prev_tok_arg;

        if (handle_nonopt(cli, tok, is_unrecog, any_option_seen))
            continue;

        if (is_tok_arg && !is_prev_tok_arg && !opt_prev->want_input) {
            cliprint(CLI_ERROR, argv[i - 1],
                     " requires no arguments, but an argument was given.");

            check_ret(panic());

            continue;
        }

        if (is_tok_arg)
            continue;

        if (argc == i + 1 && opt->want_input) {
            cliprint(CLI_ERROR, tok, " requires an argument.");

            check_ret(panic());

            break;
        }

        if (argc == i + 1) {
            execopt(opt, NULL);

            any_option_seen = true;

            break;
        }

        char *tok_next = argv[i + 1];

        if (ot_match_any(cli, tok_next) && opt->want_input) {
            cliprint(CLI_ERROR, tok_next, " is an not an allowed argument.");

            check_ret(panic());

            continue;
        }

        char *arg = opt->want_input ? tok_next : NULL;

        execopt(opt, arg);

        any_option_seen = true;
    }

    if (!any_warnings)
        return;

    if (CLI_MODE_LAIDBACK) {
        cliprint(CLI_WARN, cli->cmd, ": there are some warnings/errors.");

        return;
    }

    cliprint(CLI_WARN, cli->cmd, ": there are some warnings.");
}
