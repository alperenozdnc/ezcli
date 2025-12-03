#include <ezcli/cli.h>
#include <ezcli/freecli.h>

#include <stdlib.h>

void freecli(cli_s *cli) {
    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        if (!opt->allocated) {
            continue;
        }

        int j = 0;

        while (opt->aliases[j]) {
            free(opt->aliases[j]);

            j++;
        }

        free(opt->aliases);

        if (opt->desc)
            free(opt->desc);

        free(cli->opts[i]);
    }

    free(cli->opts);
}
