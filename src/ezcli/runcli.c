#include <ezcli/cli.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>
#include <ezcli/runcli.h>

#include "internal/expand.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * stands for option_token_match.
 * checks if the given token and option name match.
 */
bool ot_match(struct opt *opt, char *token) {
    char *exp_opt = expand(opt);

    bool ret = strcmp(token, exp_opt) == 0;

    free(exp_opt);

    return ret;
}

/*
 * stands for option_token_match_any.
 * checks if the given token and any option names match. returns the option
 * if any matches are found.
 */
struct opt *ot_match_any(struct cli *cli, char *token) {
    for (size_t i = 0; i < cli->opts_len; i++) {
        struct opt *opt = cli->opts[i];

        if (ot_match(opt, token)) {
            return opt;
        }
    }

    return NULL;
}

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
    // 0-th index is the command name itself
    for (int i = 1; i < argc; i++) {
        char *tok = argv[i];
        struct opt *opt = ot_match_any(cli, tok);
        struct opt *opt_prev = ot_match_any(cli, argv[i - 1]);

        bool is_tok_arg = !opt;
        bool is_prev_tok_arg = !opt_prev;

        if (is_tok_arg && is_prev_tok_arg) {
            cliprint(CLI_ERROR, EZCLI_EMPTY_PREFIX,
                     "%s: unrecognized option '%s'.", cli->cmd, tok);

            exit(EXIT_FAILURE);
        }

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
    }

    printf("\n");
}
