#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include "help.h"

#include <stdio.h>

void cli_help(struct cli *cli, struct opt **opts) {
    printf("help! %s", cli->cmd);
    printf("help! %s", opts[0]->name);
}
