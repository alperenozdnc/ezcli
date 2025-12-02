#include <ezcli/cli.h>
#include <ezcli/freecli.h>

#include <stdlib.h>

void freecli(cli_s *cli) {
    for (size_t i = 0; i < cli->opts_len; i++) {
        if (cli->opts[i]->allocated) {
            free(cli->opts[i]);
        }
    }

    free(cli->opts);
}
