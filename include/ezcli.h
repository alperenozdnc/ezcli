#ifndef EZCLI_H
#define EZCLI_H

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <stdbool.h>

/*
 * initializes a general command line interface struct. see `struct cli` for
 * arguments.
 * `opts` can also be populated with `cliadd_opt`
 * `aliases` can also be populated with `cliadd_alias`
 *
 * ezcli is responsible for allocating but you are responsible to free. make
 * sure you run `freecli` after usage.
 */
void initcli(struct cli *cli_p, char *cmd, char **aliases, bool gen_help,
             struct opt **opts);

/*
 * adds an option to the `opts` dynamic array in a `cli` struct.
 */
void cliadd_opt(struct cli *cli_p, struct opt *opt_a);

/*
 * adds an alias to the cmd name in a`cli` struct.
 */
void cliadd_alias(struct cli *cli_p, char *alias);

/*
 * parses and runs input in accordance to the data in struct `cli_p`
 */
void runcli(struct cli *cli_p, int argc, char *argv[]);

/*
 * frees all allocated memory. this is the only function you need to
 * run for cleanup.
 */
void freecli(struct cli *cli_p);

#endif
