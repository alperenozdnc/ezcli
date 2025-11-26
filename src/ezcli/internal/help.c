#include <ezcli/cli.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include "expand.h"
#include "help.h"
#include "match.h"

#include <stdio.h>
#include <string.h>

#define PADDING_LEFT "    " // 4 spaces

void __print_header(cli_s *cli) {
    cliprint(CLI_HINT, CLI_EMPTY_PREFIX, "[USAGE]: %s %s", cli->cmd,
             cli->usage);

    printf("%s\n\n", cli->desc);
}

void __print_options(cli_s *cli, opt_s **opts) {
    int i = 0;
    char *blacklist[] = {CLI_NONOPT, CLI_DEFAULT_OPT, NULL};

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
        opt_s *opt = opts[i];

        if (match_str(blacklist, opt->name))
            continue;

        printf(PADDING_LEFT ANSI_BLUE "%s" ANSI_RESET " -> %s", expand(opt),
               opt->desc);

        if (i != cli->opts_len - 1)
            printf("\n");
    }
}

void __print_footer(cli_s *cli) {
    if (!cli->footer)
        return;

    printf("\n\n");
    printf("%s", cli->footer);
}

void clihelp(cli_s *cli, opt_s **opts) {
    __print_header(cli);
    __print_options(cli, opts);
    __print_footer(cli);
}
