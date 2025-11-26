#include <ezcli/cli.h>
#include <ezcli/freecli.h>

#include <stdlib.h>

void freecli(cli_s *cli) {
    free(cli->opts);
}
