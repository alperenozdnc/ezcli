#pragma once

#include <stdbool.h>
#include <stddef.h>

#include <ezcli/opt.h>

#ifndef CLI_EMBEDDED
#define CLI_DEBUG_ONLY(fn)                                                     \
    if (CLI_MODE_DEBUG)                                                        \
        fn;
#else
#define CLI_DEBUG_ONLY(fn)
#endif

/*
 * keeps the information about the general command line interface.
 * `cmd`: name of the command. this is used for parsing and generating help
 * options.
 * `desc`: description of the command.
 * `usage`: usage of the command. kind of like a man page synopsis.
 * `footer`: this is the string that is printed below all options in help.
 * optional, leave NULL if you don't want it.
 * `opts`: list of options the command line interface supports.
 * `opts_len`: length of `opts`. this is automatically filled by `initcli()`.
 * note that for this to be accurate, your `opts` MUST terminate with `NULL`.
 *
 * `CLI_MODE_LAIDBACK`: setting this true enables 'laidback' mode where any
 * kind of parsing/requirement error is printed as a warning instead and the
 * program isn't halted. this is pretty useful for creating interactive programs
 * with ezcli.
 *
 * `CLI_ALLOW_NONOPT`: setting for the allowing of non option-preceded
 * arguments, (positional options). like `ls /home` where `/home` is the non
 * option-preceded argument. you should create an opt in `opts` that has alias
 * `CLI_NONOPT` to handle these inputs.
 *
 * do not touch `tok_idx`, `argc`, and `argv`. these are internal, and you might
 * get some unexpected behaviour if you decide to play with them.
 * */
typedef struct __cli_s {
    char *cmd;
    char *desc;
    char *usage;
    char *footer;

    int tok_idx;
    int argc;
    char **argv;

    opt_s **opts;
    size_t opts_len;

    char **help_aliases;
    void (*help)(struct __cli_s *cli, opt_s **opts);
} cli_s;
