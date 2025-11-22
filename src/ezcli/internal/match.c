#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include "expand.h"
#include "match.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool ot_match(struct opt *opt, char *token) {
    char *exp_opt = expand(opt);

    bool ret = strcmp(token, exp_opt) == 0;

    free(exp_opt);

    return ret;
}

struct opt *ot_match_any(struct cli *cli, char *token) {
    for (size_t i = 0; i < cli->opts_len; i++) {
        struct opt *opt = cli->opts[i];

        if (ot_match(opt, token)) {
            return opt;
        }
    }

    return NULL;
}

struct opt *match_nonopt(struct cli *cli) {
    for (size_t i = 0; i < cli->opts_len; i++) {
        struct opt *opt = cli->opts[i];

        if (strcmp(opt->name, EZCLI_NONOPT) == 0) {
            return opt;
        }
    }

    return NULL;
}
