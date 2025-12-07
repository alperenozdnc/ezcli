#include <ezcli/cli.h>

#include "internal/blacklist.h"
#include "internal/match.h"
#include "internal/recommend.h"

#include <limits.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

/*
 * counts and returns the amount of steps (addition/modification/deletion)
 * to turn `*str` into `*ref`.
 */
int count_steps(char *ref, char *str) {
    int steps = 0;
    int ref_len = strlen(ref);
    int str_len = strlen(str);

    bool one_char_matches = false;

    steps += abs(ref_len - str_len);

    for (int i = 0; i < ref_len; i++) {
        char ref_c = ref[i];

        if (i <= str_len - 1 && ref_c == str[i]) {
            one_char_matches = true;
            continue;
        }

        steps++;
    }

    if (!one_char_matches)
        return INT_MAX;

    return steps;
}

char *recommend_opt(cli_s *cli, char *input) {
    char *closest_opt = NULL;
    int min_steps = INT_MAX;

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        if (match_str(BLACKLIST, opt->aliases[0]))
            continue;

        int j = 0;

        while (opt->aliases[j]) {
            char *alias = opt->aliases[j];
            int steps = count_steps(input, alias);

            if (steps < min_steps) {
                min_steps = steps;
                closest_opt = alias;
            }

            j++;
        }
    }

    if (min_steps > 3)
        return NULL;

    return closest_opt;
}
