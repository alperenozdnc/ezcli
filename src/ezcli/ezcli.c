#include <ezcli.h>

#include <stdbool.h>
#include <stdio.h>

void initcli(struct cli *cli, char *cmd, char **aliases, bool gen_help,
             struct opt **opts) {
}

void runcli(struct cli *cli, int argc, char *argv[]) {
    printf("argc=%d, ", argc);

    for (int i = 0; i < argc; i++) {
        printf("%s", argv[i]);

        if (i != argc - 1) {
            printf(" ");
        }
    }

    printf("\n");
}

void cliadd_opt(struct cli *cli_p, struct opt *opt_a) {
}

void cliadd_alias(struct cli *cli_p, char *alias) {
}

void freecli(struct cli *cli_p) {
}
