#include <ezcli.h>
#include <stdio.h>
#include <string.h>

#include "section_categorizer.h"

ret_e _print_section_header(void *ctx, CLI_IGNORE_TOK) {
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

ret_e _print_section_footer(void *ctx, CLI_IGNORE_TOK) {
    cli_s *cli = ctx;

    char *curr_tok = gettok_offset(cli, 0);
    int curr_tok_len = strlen(curr_tok);

    if (cli->argc < 3)
        return RET_NORMAL;

    printf("\n");

    for (int i = 0; i < curr_tok_len * 3; i++)
        putchar('-');

    printf("\n\n");

    return RET_NORMAL;
}

void _section_categorizer_add(cli_s *cli) {
    static char *aliases_header[] = CLI_ALIASES(CLI_COMMON_OPT);
    static char *aliases_footer[] = CLI_ALIASES(CLI_POST_COMMON_OPT);

    opt_s section_header = {
        .aliases = aliases_header,
        .body = _print_section_header,
        .ctx = cli,
    };

    opt_s section_footer = {
        .aliases = aliases_footer,
        .body = _print_section_footer,
        .ctx = cli,
    };

    allocopt(cli, &section_header);
    allocopt(cli, &section_footer);
}
