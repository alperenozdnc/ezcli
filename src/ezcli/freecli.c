#include <ezcli/cli.h>
#include <ezcli/freecli.h>

#include <stdlib.h>

void freecli(struct cli *cli_p) {
    free(cli_p->opts);
}
