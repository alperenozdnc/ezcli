#include <ezcli/cli.h>
#include <ezcli/opt.h>
#include <ezcli/runcli.h>

#include "internal/expand.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void runcli(struct cli *cli, int argc, char *argv[]) {
    for (int i = 0; i < argc; i++) {
        char *token = argv[i];

        for (size_t j = 0; j < cli->opts_len; j++) {
            struct opt *opt = cli->opts[j];

            char *exp_opt = expand(opt);

            if (strcmp(token, exp_opt) != 0)
                continue;

            free(exp_opt);

            enum rtype ret;

            if (i + 1 < argc) {
                printf("ezcli: running %s with val %s\n", opt->name,
                       argv[i + 1]);

                ret = opt->body(argv[i + 1]);
            } else {
                printf("ezcli: running %s no val\n", opt->name);

                ret = opt->body(NULL);
            }

            if (ret == RET_FAIL) {
                fprintf(stderr, "%s exited with an error.\n", cli->cmd);

                exit(EXIT_FAILURE);
            }
        }
    }

    printf("\n");
}
