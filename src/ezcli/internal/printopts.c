#include "printopts.h"
#include "context.h"

#include <stdio.h>

void printopt(struct opt *opt) {
    printf("\n");

    printf("%s <%p>: \n", opt->name, &opt->name);

    printf("opt->type = %d\n", opt->type);
    printf("opt->desc = %s\n", opt->desc);
    printf("opt->want_input = %d\n", opt->want_input);
    printf("opt->ctx = %p\n", __CONTEXT(opt));
    printf("opt->body = %p\n", &opt->body);
}

void printopts(struct cli *cli) {
    printf("according to cli->opts_len:\n\n");

    for (size_t i = 0; i < cli->opts_len; i++) {
        struct opt *opt = cli->opts[i];

        printf("------%ld------\n", i);
        printopt(opt);
        printf("\n");
    }

    printf("\n");

    printf("according to NULL:\n");

    int i = 0;

    while (cli->opts[i]) {
        struct opt *opt = cli->opts[i];

        printf("------%d------\n", i);
        printopt(opt);
        printf("\n");

        i++;
    }
}
