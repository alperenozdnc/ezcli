#pragma once

#include <ezcli/cli.h>

/*
 * parses and runs input in accordance to the data in struct `cli_p`.
 * note that `runcli` expects `argv` to start with the command name itself. you
 * should inject command names when injecting non-inputted arguments into
 * runcli.
 */
void runcli(struct cli *cli_p, int argc, char *argv[]);
