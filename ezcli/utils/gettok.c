#include <ezcli/cli.h>
#include <ezcli/gettok.h>

#define ARGV_BEGIN 1
#define ARGV_END cli->argc - 1

char *gettok_prev(cli_s *cli) {
    // 0th item is the cmd name itself
    if (cli->tok_idx == ARGV_BEGIN)
        return NULL;

    return cli->argv[cli->tok_idx - 1];
}

char *gettok_next(cli_s *cli) {
    if (cli->tok_idx == ARGV_END)
        return NULL;

    return cli->argv[cli->tok_idx + 1];
}

char *gettok_offset(cli_s *cli, int n) {
    if (n == CLI_TOK_FIRST)
        return cli->argv[ARGV_BEGIN];

    if (n == CLI_TOK_LAST)
        return cli->argv[ARGV_END];

    int k = cli->tok_idx + n;

    if (k >= ARGV_BEGIN && k <= ARGV_END)
        return cli->argv[k];

    return NULL;
}
