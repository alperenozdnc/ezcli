#ifndef EZCLI_CLI_H
#define EZCLI_CLI_H

#include <stdbool.h>
#include <stddef.h>

#include <ezcli/opt.h>

/*
 * keeps the information about the general command line interface.
 * `cmd`: name of the command. this is used for parsing and generating help
 * options.
 * `desc`: description of the command. this is used for generating help options.
 * `allow_non_opt`: if `true` it allows non for option-preceded
 * arguments, like `ls /home` where
 * `/home` is the non option-preceded argument. you should create an opt in
 * `opts` that has name `EZCLI_NONOPT` and type `OPTION_BARE` to handle these
 * inputs. `opts`: list of options the command line interface supports.
 * `opts_len`: length of `opts`. this is automatically filled by `initcli()`.
 * note that for this to be accurate, your `opts` MUST terminate with `NULL`.
 */
struct cli {
    char *cmd;
    char *desc;
    bool allow_non_opt;
    struct opt **opts;
    size_t opts_len;
    char **help_aliases;
    void (*help)(struct cli *cli, struct opt **opts);
};

#endif
