#include "printopts.h"
#include "context.h"
#include "printaliases.h"

#include <stdio.h>

void printopt(opt_s *opt) {
    printf("\n");

    printaliases(opt->aliases);
    printf(" <%p>: \n", &opt);

    printf("opt->desc = %s\n", opt->desc);
    printf("opt->want_input = %d\n", opt->want_input);
    printf("opt->ctx = %p\n", __CONTEXT(opt));
    printf("opt->body = %p\n", &opt->body);

    printf("\n");
}

void printopts(cli_s *cli) {
    printf("according to cli->opts_len:\n\n");

    for (size_t i = 0; i < cli->opts_len; i++) {
        opt_s *opt = cli->opts[i];

        printf("------%ld------\n", i);
        printopt(opt);
    }

    printf("\n");

    printf("according to NULL:\n");

    int i = 0;

    while (cli->opts[i]) {
        opt_s *opt = cli->opts[i];

        printf("------%d------\n", i);
        printopt(opt);

        i++;
    }
}
