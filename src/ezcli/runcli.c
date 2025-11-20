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
 * checks if the given token and option name match.
 */
bool is_opt(struct opt *opt, char *token) {
    char *exp_opt = expand(opt);

    bool ret = strcmp(token, exp_opt) == 0;

    free(exp_opt);

    return ret;
}

/*
 * checks if the given token and any option names match. returns the option
 * if any matches are found.
 */
struct opt *is_any_opt(struct cli *cli, char *token) {
    for (size_t i = 0; i < cli->opts_len; i++) {
        struct opt *opt = cli->opts[i];

        if (is_opt(opt, token)) {
            return opt;
        }
    }

    return NULL;
}

void runcli(struct cli *cli, int argc, char *argv[]) {
    // 0-th index is the command name itself
    for (int i = 1; i < argc; i++) {
        char *token = argv[i];
        struct opt *opt = is_any_opt(cli, token);
        enum rtype ret;

        if (!opt) {
            if (!is_any_opt(cli, argv[i - 1])) {
                cliprint(CLI_ERROR, EZCLI_EMPTY_PREFIX,
                         "%s: unrecognized option '%s'.", cli->cmd, token);

                exit(EXIT_FAILURE);
            }

            continue;
        }

        if (argc == i + 1) {
            cliprint(CLI_HINT, "ezcli: ", "%s -> NULL", opt->name);

            ret = opt->body(NULL);
        } else {
            char *next_token = argv[i + 1];

            if (is_any_opt(cli, next_token)) {
                cliprint(CLI_ERROR, EZCLI_EMPTY_PREFIX,
                         "%s: unallowed argument '%s'.", cli->cmd, next_token);

                exit(EXIT_FAILURE);
            }

            cliprint(CLI_HINT, "ezcli: ", "%s -> %s", opt->name, next_token);

            ret = opt->body(next_token);
        }

        if (ret == RET_FAIL) {
            cliprint(CLI_ERROR, EZCLI_EMPTY_PREFIX, "%s: exited with an error.",
                     cli->cmd);

            exit(EXIT_FAILURE);
        } else if (ret == RET_WARN) {
            cliprint(CLI_WARN, EZCLI_EMPTY_PREFIX,
                     "%s: there are some warnings.", cli->cmd);
        }
    }

    printf("\n");
}
