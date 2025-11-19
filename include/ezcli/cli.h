#ifndef EZCLI_CLI_H
#define EZCLI_CLI_H

#include <stdbool.h>

/*
 * keeps the information about the general command line interface.
 * `cmd`: name of the command. this is used for parsing and generating help
 * options.
 * `aliases`: list of possible aliases for `cmd`.
 * `gen_help`: if `true`, generates a default help option that also
 * allows searching for help on individual options.
 * `opts`: list of options the command line interface supports.
 */
struct cli {
    char *cmd;
    char **aliases;
    bool gen_help;
    struct opt **opts;
};

#endif
