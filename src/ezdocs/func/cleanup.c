#include "../../ezcli/internal/match.h"

#include <ezcli.h>
#include <stdlib.h>

/*
 * frees all pieces of dynamically allocated memory related to entries.
 */
void free_entries(cli_s *cli, char **entries) {
    char **ignore = CLI_ALIASES(CLI_COMMON_OPT, CLI_POST_COMMON_OPT);

    int i = 0;

    while (entries[i]) {
        free(entries[i++]);
    }

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        if (opt->allocated && !match_str(ignore, opt->aliases[0])) {
            free(opt->aliases[0]);
            free(opt->aliases);
            free(opt->desc);
        }
    }

    free(entries);
}

void cleanup(cli_s *cli, char *entries_path, char **entries) {
    free(entries_path);
    free_entries(cli, entries);
    freecli(cli);
}
