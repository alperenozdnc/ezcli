#include "match.h"
#include "expand.h"

#include <stdbool.h>
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
