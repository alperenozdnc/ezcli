/*
 * this ran 1,215,737,652 iterations before stack overflow on my machine.
 * goes to show that there's NO memory leaks and runcli() is incredibly
 * cost efficient.
 *
 * the reason for the sheer amount of iterations possible is because repeatedly
 * runcli() calls inside option bodies is not true recursion but
 * 'pseudo-recursion' if you will.
 *
 * this means that the limit of depth is theoretically infinite but practically
 * about your computer's specs.
 */

#include <ezcli.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ret_e recurse_body(void *ctx, char *tok) {
    cli_s *cli = ctx;
    char *self = gettok_offset(cli, 0);

    char *argv[] = {cli->cmd, self, tok, NULL};
    int argc = 3;

    int amount = atoi(tok);

    if (amount <= 0) {
        printf("ended recursion.\n");
    } else {
        int len = log10(amount) + 1;
        char *new_amount = malloc(len + 1);
        snprintf(new_amount, len + 1, "%d", amount - 1);
        new_amount[len] = '\0';

        printf("%d (argv = %s %s %s) \n", amount, cli->cmd, self, tok);

        char *argv_new[] = {cli->cmd, self, new_amount, NULL};

        runcli(cli, argc, argv_new);

        free(new_amount);
    }

    cli->argc = argc;
    cli->argv = argv;

    return RET_NORMAL;
}

opt_s recurse = {
    .aliases = CLI_ALIASES("repeat", "recurse", "-r"),
    .desc = "recurses n times.",
    .want_input = true,
    .body = recurse_body,
};

int main(int argc, char *argv[]) {
    cli_s cli;
    opt_s *opts[] = {NULL};

    initcli(&cli, "recursor", "recurses n times.", "{repeat/recurse/-r} [n]",
            "nice program.\n", opts, CLI_ALIASES("help"));

    recurse.ctx = &cli;

    allocopt(&cli, &recurse);

    runcli(&cli, argc, argv);

    freecli(&cli);

    return 0;
}
