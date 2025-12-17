#include <ezcli/cli.h>
#include <ezcli/external.h>
#include <ezcli/opt.h>
#include <ezcli/print.h>

#include "internal/blacklist.h"
#include "internal/help.h"
#include "internal/match.h"
#include "internal/printaliases.h"

#include <stdio.h>
#include <string.h>

#define PADDING_LEFT "    " // 4 spaces

void __print_header(cli_s *cli) {
    cliprint(CLI_HINT, CLI_EMPTY_PREFIX, "[USAGE]: %s %s", cli->cmd,
             cli->usage);

    printf("%s\n\n", cli->desc);
}

void __print_option(char **aliases, char *desc, bool newline) {
    if (newline)
        printf("\n");

    printf(PADDING_LEFT);
    printaliases(aliases);
    printf(" -> %s", desc);
}

void __print_options(cli_s *cli, opt_s **opts) {
    __print_option(cli->help_aliases, "prints this menu.", false);

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = opts[i];

        if (match_str(BLACKLIST, opt->aliases[0]))
            continue;

        __print_option(opt->aliases, opt->desc, true);
    }
}

void __print_footer(cli_s *cli) {
    if (!cli->footer)
        return;

    printf("\n\n");
    printf("%s", cli->footer);
}

void help(cli_s *cli, opt_s **opts) {
    CLI_DEBUG_ONLY(cliprint(CLI_HINT, "[ezcli] ", "executing help"));

    __print_header(cli);
    __print_options(cli, opts);
    __print_footer(cli);
}
