#include <ezcli/cli.h>
#include <ezcli/initcli.h>

void initcli(struct cli *cli, char *cmd, bool gen_help, struct opt **opts) {
    cli->cmd = cmd;
    cli->gen_help = gen_help;
    cli->opts = opts;
    cli->opts_len = 0;

    while (cli->opts[cli->opts_len] != NULL) {
        cli->opts_len++;
    }
}
