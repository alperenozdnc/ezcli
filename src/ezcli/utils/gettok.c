#include <ezcli/cli.h>
#include <ezcli/gettok.h>

char *gettok_prev(cli_s *cli) {
    // 0th item is the cmd name itself
    if (cli->tok_idx == 1)
        return NULL;

    return cli->argv[cli->tok_idx - 1];
}

char *gettok_next(cli_s *cli) {
    if (cli->tok_idx + 1 == cli->argc)
        return NULL;

    return cli->argv[cli->tok_idx + 1];
}
