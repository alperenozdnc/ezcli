#include <ezcli/cli.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include "help.h"
#include "match.h"
#include "printaliases.h"

#include <stdio.h>
#include <string.h>

#define PADDING_LEFT "    " // 4 spaces

void __print_header(cli_s *cli) {
    cliprint(CLI_HINT, CLI_EMPTY_PREFIX, "[USAGE]: %s %s", cli->cmd,
             cli->usage);

    printf("%s\n\n", cli->desc);
}

void __print_option(char **aliases, char *desc) {
    printf(PADDING_LEFT);
    printaliases(aliases);
    printf(" -> %s", desc);
}

void __print_options(cli_s *cli, opt_s **opts) {
    char *blacklist[] = {CLI_NONOPT, CLI_DEFAULT_OPT, CLI_COMMON_OPT, NULL};

    __print_option(cli->help_aliases, "prints this menu.\n");

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = opts[i];

        if (match_str(blacklist, opt->aliases[0]))
            continue;

        __print_option(opt->aliases, opt->desc);

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

void help(cli_s *cli, opt_s **opts) {
    __print_header(cli);
    __print_options(cli, opts);
    __print_footer(cli);
}
