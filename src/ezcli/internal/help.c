#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include "expand.h"
#include "help.h"

#include <stdio.h>
#include <string.h>

void cli_help(struct cli *cli, struct opt **opts) {
    printf("[USAGE]: %s %s\n", cli->cmd, cli->usage);
    printf("%s\n\n", cli->desc);

    for (size_t i = 0; i < cli->opts_len; i++) {
        if (strcmp(opts[i]->name, EZCLI_NONOPT) == 0) {
            continue;
        }

        printf("    ");
        printf("%s -> desc", expand(opts[i]));

        if (i != cli->opts_len - 1) {
            printf("\n");
        }
    }

    printf("\n");

    if (cli->footer) {
        printf("\n");
        printf("%s", cli->footer);
    }
}
