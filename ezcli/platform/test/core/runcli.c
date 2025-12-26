#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <test/integrity/emit_signal.h>
#include <test/integrity/handle_nonopt.h>
#include <test/integrity/runcli.h>
#include <test/integrity/sig_arena_s.h>
#include <test/integrity/sig_s.h>

#include "internal/match.h"

#include <stdbool.h>

void _runcli(cli_s *cli, int argc, char *argv[], sig_arena_s *arena) {
    cli->argc = argc;
    cli->argv = argv;

    bool any_option_seen = false;

    if (argc == 1) {
        opt_s *opt_default = ot_match_any(cli, CLI_DEFAULT_OPT);

        if (opt_default) {
            emit_signal(CLI_SIG_EXEC_DEF_OPT);
        } else {
            emit_signal(CLI_SIG_EXEC_HELP_OPT);
        }

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

        if (i == 1 && match_str(cli->help_aliases, tok)) {
            emit_signal(CLI_SIG_EXEC_HELP_OPT);

            break;
        }

        if (handle_nonopt(cli, is_unrecog, any_option_seen, arena))
            continue;

        if (is_tok_arg && !is_prev_tok_arg && !opt_prev->want_input) {
            emit_signal(CLI_SIG_ERR_PASS_NO_WANT_ARGS);

            continue;
        }

        if (is_tok_arg) {
            emit_signal(CLI_SIG_CONSUME_TOK);

            continue;
        }

        if (argc == i + 1 && opt->want_input) {
            emit_signal(CLI_SIG_ERR_NOT_PASS_BUT_WANT_ARGS);

            break;
        }

        if (argc == i + 1) {
            emit_signal(CLI_SIG_EXEC_PARSED_OPT_NO_TOK);

            any_option_seen = true;

            break;
        }

        char *tok_next = argv[i + 1];

        if (ot_match_any(cli, tok_next) && opt->want_input) {
            emit_signal(CLI_SIG_ERR_UNALLOWED_ARG);

            continue;
        }

        char *arg = opt->want_input ? tok_next : NULL;

        if (arg) {
            emit_signal(CLI_SIG_EXEC_PARSED_OPT);
        } else {
            emit_signal(CLI_SIG_EXEC_PARSED_OPT_NO_TOK);
        }

        any_option_seen = true;
    }
}
