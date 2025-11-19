#ifndef EZCLI_H
#define EZCLI_H

#include <ezcli/cli.h>
#include <ezcli/opt.h>

#include <ezcli/initcli.h>
#include <ezcli/print.h>

#include <stdbool.h>

/*
 * adds an option to the `opts` dynamic array in a `cli` struct.
 */
void cliadd_opt(struct cli *cli_p, struct opt *opt_a);

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
