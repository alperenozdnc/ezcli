#include <ezcli.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "section_categorizer.h"

ret_e _section_categorizer(void *ctx, CLI_IGNORE_TOK) {
    cli_s *cli = ctx;

    char *curr_tok = gettok_offset(cli, 0);
    int curr_tok_len = strlen(curr_tok);

    if (cli->argc < 2)
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

opt_s SECTION_CATEGORIZER_TEMPLATE = {
    .aliases = (char *[]){CLI_COMMON_OPT, NULL},
    .body = _section_categorizer,
    .desc = "section header formatter",
};

void _section_categorizer_add(cli_s *cli) {
    opt_s *opt = malloc(sizeof *opt);

    *opt = SECTION_CATEGORIZER_TEMPLATE;

    opt->ctx = cli;

    addopt(cli, opt);
}
