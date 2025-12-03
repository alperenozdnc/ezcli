#include <ezcli/addopt.h>
#include <ezcli/allocopt.h>
#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void allocopt(cli_s *cli, const opt_s *opt_stack) {
    opt_s *opt = malloc(sizeof *opt);
    size_t aliases_len = 0;

    while (opt_stack->aliases[aliases_len])
        aliases_len++;

    opt->aliases = malloc(sizeof(char *) * (aliases_len + 1));

    for (size_t i = 0; i < aliases_len; i++) {
        opt->aliases[i] = strdup(opt_stack->aliases[i]);
    }

    opt->aliases[aliases_len] = NULL;

    opt->body = opt_stack->body;
    opt->ctx = opt_stack->ctx;

    if (opt_stack->desc) {
        opt->desc = strdup(opt_stack->desc);
    } else {
        opt->desc = NULL;
    }

    opt->want_input = opt_stack->want_input;
    opt->allocated = true;

    addopt(cli, opt);
}
