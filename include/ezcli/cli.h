#pragma once

#include <stdbool.h>
#include <stddef.h>

#include <ezcli/opt.h>

/*
 * keeps the information about the general command line interface.
 * `cmd`: name of the command. this is used for parsing and generating help
 * options.
 * `desc`: description of the command.
 * `usage`: usage of the command. kind of like a man page synopsis.
 * `footer`: this is the string that is printed below all options in help.
 * optional, leave NULL if you don't want it.
 * `allow_non_opt`: if `true` it
 * allows non for option-preceded arguments, like `ls /home` where
 * `/home` is the non option-preceded argument. you should create an opt in
 * `opts` that has name `EZCLI_NONOPT` and type `OPTION_BARE` to handle these
 * inputs. `opts`: list of options the command line interface supports.
 * `opts_len`: length of `opts`. this is automatically filled by `initcli()`.
 * note that for this to be accurate, your `opts` MUST terminate with `NULL`.
 * `laidback`: setting this true enables 'laidback' mode where any kind of
 * parsing/requirement error is printed as a warning instead and the program
 * isn't halted. this is pretty useful for creating interactive programs with
 * ezcli.
 */
struct cli {
    char *cmd;
    char *desc;
    char *usage;
    char *footer;

    bool allow_non_opt;
    struct opt **opts;
    size_t opts_len;

    char **help_aliases;
    void (*help)(struct cli *cli, struct opt **opts);

    bool laidback;
};
