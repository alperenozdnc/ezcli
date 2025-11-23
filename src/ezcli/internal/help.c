#include <ezcli/cli.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include "expand.h"
#include "help.h"

#include <stdio.h>
#include <string.h>

#define PADDING_LEFT "    " // 4 spaces

void __print_header(struct cli *cli) {
    cliprint(CLI_HINT, EZCLI_EMPTY_PREFIX, "[USAGE]: %s %s", cli->cmd,
             cli->usage);

    printf("%s\n\n", cli->desc);
}

void __print_options(struct cli *cli, struct opt **opts) {
    int i = 0;

    while (cli->help_aliases[i]) {
        if (i == 0)
            printf(PADDING_LEFT);

        printf(ANSI_BLUE "%s" ANSI_RESET, cli->help_aliases[i]);

        if (cli->help_aliases[i + 1]) {
            printf(", ");
        } else {
            printf(" -> prints this menu.\n");
        }

        i++;
    }

    for (size_t i = 0; i < cli->opts_len; i++) {
        struct opt *opt = opts[i];

        if (strcmp(opt->name, EZCLI_NONOPT) == 0)
            continue;

        printf(PADDING_LEFT ANSI_BLUE "%s" ANSI_RESET " -> %s", expand(opt),
               opt->desc);

        if (i != cli->opts_len - 1)
            printf("\n");
    }
}

void __print_footer(struct cli *cli) {
    if (!cli->footer)
        return;

    printf("\n\n");
    printf("%s", cli->footer);
}

void cli_help(struct cli *cli, struct opt **opts) {
    __print_header(cli);
    __print_options(cli, opts);
    __print_footer(cli);
}
