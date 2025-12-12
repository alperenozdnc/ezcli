#include <ezcli/cli.h>
#include <ezcli/opt.h>
#include <ezcli/platform.h>

#include "internal/match.h"

#include <stdbool.h>

bool ot_match(opt_s *opt, char *token) {
    int i = 0;

    while (opt->aliases[i]) {
        char *name = opt->aliases[i];

        if (c_strcmp(token, name) == 0)
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

opt_s *oa_match_first(cli_s *cli, char *alias) {
    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        if (c_strcmp(opt->aliases[0], alias) == 0)
            return opt;
    }

    return NULL;
}

bool match_str(char **arr, char *str) {
    int i = 0;

    while (arr[i]) {
        if (c_strcmp(arr[i], str) == 0)
            return true;

        i++;
    }

    return false;
}

bool match_str_contains(char *str, char *inner) {
    bool str_contains_inner = false;

    size_t len_str = c_strlen(str);
    size_t len_inner = c_strlen(inner);

    size_t idx_inner = 0;

    for (size_t i = 0; i < len_str; i++) {
        char c = str[i];
        char ci = inner[idx_inner];

        if (c != ci) {
            str_contains_inner = false;
            idx_inner = 0;

            continue;
        }

        str_contains_inner = true;

        if (idx_inner == len_inner - 1)
            break;

        idx_inner++;
    }

    return str_contains_inner;
}
