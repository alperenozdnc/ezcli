#ifndef EZCLI_RUNCLI_H
#define EZCLI_RUNCLI_H

#include <ezcli/cli.h>

/*
 * parses and runs input in accordance to the data in struct `cli_p`
 */
void runcli(struct cli *cli_p, int argc, char *argv[]);

#endif
