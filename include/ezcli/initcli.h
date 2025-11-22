#ifndef EZCLI_INITCLI_H
#define EZCLI_INITCLI_H

#include <ezcli/cli.h>

#include <stdbool.h>

/*
 * initializes a general command line interface struct. see `struct cli` for
 * arguments.
 * `opts` can also be populated with `addopt`
 *
 * ezcli is responsible for allocating but you are responsible to free. make
 * sure you run `freecli` after usage.
 *
 * NOTE: `opts` MUST be terminated with a NULL.
 */
void initcli(struct cli *cli, char *cmd, bool allow_non_opt, struct opt **opts,
             char *help_aliases[]);
#endif
