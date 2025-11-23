#include <ezcli/cli.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>
#include <ezcli/runcli.h>

#include "internal/handle_nonopt.h"
#include "internal/match.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * prints/exits appropriately for warnings/errors.
 */
void check_ret(struct cli *cli, enum rtype ret) {
    if (ret == RET_FAIL) {
        cliprint(CLI_ERROR, EZCLI_EMPTY_PREFIX, "%s: exited with an error.",
                 cli->cmd);

        exit(EXIT_FAILURE);
    }

    if (ret == RET_WARN) {
        cliprint(CLI_WARN, EZCLI_EMPTY_PREFIX, "%s: there are some warnings.",
                 cli->cmd);
    }
}

void runcli(struct cli *cli, int argc, char *argv[]) {
    bool any_option_seen = false;

    // not a return point because the default case also needs the printf("\n")
    // on the bottom. the for loop is omitted anyways.
    if (argc == 1) {
        struct opt *opt_default = ot_match_any(cli, EZCLI_DEFAULT_OPT);

        if (opt_default) {
            opt_default->body(NULL);
        } else {
            cli->help(cli, cli->opts);
        }
    }

    // 0-th index is the command name itself
    for (int i = 1; i < argc; i++) {
        char *tok = argv[i];
        struct opt *opt = ot_match_any(cli, tok);
        struct opt *opt_prev = ot_match_any(cli, argv[i - 1]);

        bool is_tok_arg = !opt;
        bool is_prev_tok_arg = !opt_prev;
        bool is_unrecog = is_tok_arg && is_prev_tok_arg;

        if (i == 1 && match_str(cli->help_aliases, tok)) {
            cli->help(cli, cli->opts);

            break;
        }

        if (handle_nonopt(cli, tok, is_unrecog, any_option_seen))
            continue;

        if (is_tok_arg && !is_prev_tok_arg && !opt_prev->want_input) {
            cliprint(CLI_ERROR, EZCLI_EMPTY_PREFIX,
                     "%s: '%s' cannot be passed to '%s' as it requires no "
                     "arguments.",
                     cli->cmd, tok, opt_prev->name);

            exit(EXIT_FAILURE);
        }

        if (is_tok_arg)
            continue;

        if (argc == i + 1 && opt->want_input) {
            cliprint(CLI_ERROR, EZCLI_EMPTY_PREFIX,
                     "%s: '%s' requires an argument.", cli->cmd, tok);

            exit(EXIT_FAILURE);
        }

        if (argc == i + 1) {
            cliprint(CLI_HINT, "ezcli: ", "%s -> NULL", opt->name);

            check_ret(cli, opt->body(NULL));
            any_option_seen = true;

            break;
        }

        char *tok_next = argv[i + 1];

        if (ot_match_any(cli, tok_next) && opt->want_input) {
            cliprint(CLI_ERROR, EZCLI_EMPTY_PREFIX,
                     "%s: unallowed argument '%s'.", cli->cmd, tok_next);

            exit(EXIT_FAILURE);
        }

        char *arg = opt->want_input ? tok_next : NULL;

        cliprint(CLI_HINT, "ezcli: ", "%s -> %s", opt->name,
                 arg ? arg : "NULL");

        check_ret(cli, opt->body(arg));
        any_option_seen = true;
    }

    printf("\n");
}
