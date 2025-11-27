#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include "match.h"

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool ot_match(opt_s *opt, char *token) {
    int i = 0;

    while (opt->aliases[i]) {
        char *name = opt->aliases[i];

        if (strcmp(token, name) == 0)
            return true;

        i++;
    }

    return false;
}

opt_s *ot_match_any(cli_s *cli, char *token) {
    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        if (ot_match(opt, token))
            return opt;
    }

    return NULL;
}

opt_s *match_nonopt(cli_s *cli) {
    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        if (strcmp(opt->aliases[0], CLI_NONOPT) == 0) {
            return opt;
        }
    }

    return NULL;
}

bool match_str(char **arr, char *str) {
    int i = 0;

    while (arr[i]) {
        if (strcmp(arr[i], str) == 0)
            return true;

        i++;
    }

    return false;
}
