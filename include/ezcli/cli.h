#ifndef EZCLI_CLI_H
#define EZCLI_CLI_H

#include <stdbool.h>

/*
 * keeps the information about the general command line interface.
 * `cmd`: name of the command. this is used for parsing and generating help
 * options.
 * `gen_help`: if `true`, generates a default help option that also
 * allows searching for help on individual options.
 * `opts`: list of options the command line interface supports.
 */
struct cli {
    char *cmd;
    bool gen_help;
    struct opt **opts;
};

#endif
