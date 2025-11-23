#pragma once

#include <ezcli/cli.h>

#include <stdbool.h>

/*
 * initializes a general command line interface struct. see `struct cli` for
 * arguments.
 * `opts` can also be populated with `addopt`
 *
 * ezcli is responsible for allocating but you are responsible to free. make
 * sure you run `freecli` after usage. also, make sure any arguments passed to
 * this live for the entire program.
 *
 * NOTE: `opts` MUST be terminated with a NULL.
 */
void initcli(struct cli *cli, char *cmd, char *desc, char *usage, char *footer,
             bool allow_non_opt, struct opt **opts, char *help_aliases[]);
