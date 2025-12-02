#include <ezcli.h>
#include <stdio.h>
#include <string.h>

#include "section_categorizer.h"

ret_e _section_categorizer(void *ctx, CLI_IGNORE_TOK) {
    cli_s *cli = ctx;

    char *curr_tok = gettok_offset(cli, 0);
    int curr_tok_len = strlen(curr_tok);

    if (cli->argc < 3)
        return RET_NORMAL;

    if (cli->tok_idx > 1)
        printf("\n");

    for (int i = 0; i < curr_tok_len * 3; i++)
        putchar('-');

    printf("\n%*s\n", curr_tok_len * 2, curr_tok);

    for (int i = 0; i < curr_tok_len * 3; i++)
        putchar('-');

    printf("\n\n");

    return RET_NORMAL;
}

void _section_categorizer_add(cli_s *cli) {
    static char *aliases[] = CLI_ALIASES(CLI_COMMON_OPT);

    opt_s section_categorizer = {
        .aliases = aliases,
        .body = _section_categorizer,
        .desc = "section header formatter",
    };

    section_categorizer.ctx = cli;

    allocopt(cli, &section_categorizer);
}
