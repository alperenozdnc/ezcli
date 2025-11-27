#pragma once

#include <ezcli/cli.h>

/*
 * parses and runs input in accordance to the data in struct `cli_p`.
 * note that `runcli` expects `argv` to start with the command name itself. you
 * should inject command a comamnd name at `argv[0]` when injecting non-inputted
 * arguments into runcli.
 */
void runcli(cli_s *cli_p, int argc, char *argv[]);
