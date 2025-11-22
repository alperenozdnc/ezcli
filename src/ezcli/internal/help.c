#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include "expand.h"
#include "help.h"

#include <stdio.h>
#include <string.h>

void cli_help(struct cli *cli, struct opt **opts) {
    printf("[USAGE]: %s [command] [args]\n", cli->cmd);
    printf("A program to mimick human-like behaviour.\n\n");

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
    printf("\n");

    printf(
        "For online documentation: <https://github.com/alperenozdnc/ezcli>\n");
    printf("For seeing the license: "
           "  <https://www.gnu.org/licenses/gpl-3.0.en.html>\n");
}
